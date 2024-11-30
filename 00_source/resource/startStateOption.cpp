//============================================================
//
//	�����ݒ��ԏ��� [startStateOption.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startStateOption.h"
#include "startManager.h"
#include "optionManager.h"

//************************************************************
//	�q�N���X [CStartStateOption] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateOption::CStartStateOption() :
	m_pOptionManager	(nullptr)	// �ݒ�}�l�[�W���[
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CStartStateOption::~CStartStateOption()
{

}

//============================================================
//	����������
//============================================================
HRESULT CStartStateOption::Init()
{
	// �����o�ϐ���������
	m_pOptionManager = nullptr;	// �ݒ�}�l�[�W���[

	// �ݒ�}�l�[�W���[�̐���
	m_pOptionManager = COptionManager::Create();
	if (m_pOptionManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CStartStateOption::Uninit()
{
	// �ݒ�}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pOptionManager);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CStartStateOption::Update(const float fDeltaTime)
{
	// �ݒ�}�l�[�W���[�̍X�V
	assert(m_pOptionManager != nullptr);
	if (m_pOptionManager->Update(fDeltaTime))
	{ // ��ԑJ�ڂ̑��삪�s��ꂽ�ꍇ

		// �`���[�g���A����Ԃɂ���
		m_pContext->ChangeState(new CStartStateTutorial);
	}
}
