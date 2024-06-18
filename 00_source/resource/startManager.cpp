//============================================================
//
//	�X�^�[�g�}�l�[�W���[���� [startManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startManager.h"
#include "startState.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{

}

//************************************************************
//	�e�N���X [CStartManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartManager::CStartManager() :
	m_pState	(nullptr)	// ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CStartManager::~CStartManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CStartManager::Init(void)
{
	// �����o�ϐ���������
	m_pState = nullptr;	// ���

	// ���S�\����Ԃɂ���
	ChangeState(new CStartStateLogo);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CStartManager::Uninit(void)
{
	// ��Ԃ̏I��
	SAFE_UNINIT(m_pState);
}

//============================================================
//	�X�V����
//============================================================
void CStartManager::Update(const float fDeltaTime)
{
	// ��Ԃ��Ƃ̍X�V
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	��Ԃ̕ύX����
//============================================================
HRESULT CStartManager::ChangeState(CStartState *pState)
{
	// ��Ԃ̐����Ɏ��s���Ă���ꍇ������
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// ��ԃC���X�^���X���I��
	SAFE_UNINIT(m_pState);

	// ��ԃC���X�^���X��ύX
	assert(m_pState == nullptr);
	m_pState = pState;

	// ��ԂɃR���e�L�X�g��ݒ�
	m_pState->SetContext(this);

	// ��ԃC���X�^���X��������
	if (FAILED(m_pState->Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	��������
//============================================================
CStartManager *CStartManager::Create(void)
{
	// �X�^�[�g�}�l�[�W���[�̐���
	CStartManager *pStartManager = new CStartManager;
	if (pStartManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �X�^�[�g�}�l�[�W���[�̏�����
		if (FAILED(pStartManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �X�^�[�g�}�l�[�W���[�̔j��
			SAFE_DELETE(pStartManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pStartManager;
	}
}

//============================================================
//	�j������
//============================================================
void CStartManager::Release(CStartManager *&prStartManager)
{
	// �X�^�[�g�}�l�[�W���[�̏I��
	assert(prStartManager != nullptr);
	prStartManager->Uninit();

	// �������J��
	SAFE_DELETE(prStartManager);
}
