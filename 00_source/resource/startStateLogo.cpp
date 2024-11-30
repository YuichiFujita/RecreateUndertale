//============================================================
//
//	���S�\����ԏ��� [startStateLogo.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startStateLogo.h"
#include "inputManager.h"
#include "startManager.h"
#include "logoManager.h"

//************************************************************
//	�q�N���X [CStartStateLogo] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateLogo::CStartStateLogo() :
	m_pLogoManager	(nullptr)	// ���S�}�l�[�W���[
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CStartStateLogo::~CStartStateLogo()
{

}

//============================================================
//	����������
//============================================================
HRESULT CStartStateLogo::Init()
{
	// �����o�ϐ���������
	m_pLogoManager = nullptr;	// ���S�}�l�[�W���[

	// ���S�}�l�[�W���[�̐���
	m_pLogoManager = CLogoManager::Create();
	if (m_pLogoManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CStartStateLogo::Uninit()
{
	// ���S�}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pLogoManager);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CStartStateLogo::Update(const float fDeltaTime)
{
	// ���S�}�l�[�W���[�̍X�V
	assert(m_pLogoManager != nullptr);
	m_pLogoManager->Update(fDeltaTime);

	if (input::Decide())
	{
		// �`���[�g���A����Ԃɂ���
		m_pContext->ChangeState(new CStartStateTutorial);
	}
}
