//============================================================
//
//	�t�B�[���h���j���[�}�l�[�W���[���� [menuManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "menuManager.h"
#include "menuUI.h"

//************************************************************
//	�e�N���X [CMenuManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CMenuManager::CMenuManager() :
	m_pMenu	(nullptr)	// �t�B�[���h���j���[���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CMenuManager::~CMenuManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CMenuManager::Init(void)
{
	// �����o�ϐ���������
	m_pMenu = nullptr;	// �t�B�[���h���j���[���

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CMenuManager::Uninit(void)
{

}

//============================================================
//	�X�V����
//============================================================
void CMenuManager::Update(const float fDeltaTime)
{
	// �I�𒆂̏ꍇ������
	if (IsChoiceSelect()) { return; }

	if (input::FieldMenu())
	{
		// �t�B�[���h���j���[�̕\����؂�ւ�
		SetEnableDrawMenu(!IsDrawMenu());
	}

	if (input::Cancel())
	{
		// �t�B�[���h���j���[�̏I��
		SetEnableDrawMenu(false);
	}
}

//============================================================
//	�t�B�[���h���j���[�̕`��ݒ菈��
//============================================================
void CMenuManager::SetEnableDrawMenu(const bool bDraw)
{
	if (bDraw)
	{ // �`����J�n����ꍇ

		// �����ς݂̏ꍇ������
		if (m_pMenu != nullptr) { return; }

		// �t�B�[���h���j���[�̐���
		m_pMenu = CMenuUI::Create();
	}
	else
	{ // �`����I������ꍇ

		// �t�B�[���h���j���[�̏I��
		SAFE_UNINIT(m_pMenu);
	}
}

//============================================================
//	�I�𒆏󋵂̎擾����
//============================================================
bool CMenuManager::IsChoiceSelect(void) const
{
	// ���j���[�����Ă���ꍇ������
	if (m_pMenu == nullptr) { return false; }

	// �I�𒆏󋵂�Ԃ�
	return m_pMenu->IsChoiceSelect();
}

//============================================================
//	��������
//============================================================
CMenuManager *CMenuManager::Create(void)
{
	// �t�B�[���h���j���[�}�l�[�W���[�̐���
	CMenuManager *pMenuManager = new CMenuManager;
	if (pMenuManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �t�B�[���h���j���[�}�l�[�W���[�̏�����
		if (FAILED(pMenuManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �t�B�[���h���j���[�}�l�[�W���[�̔j��
			SAFE_DELETE(pMenuManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pMenuManager;
	}
}

//============================================================
//	�j������
//============================================================
void CMenuManager::Release(CMenuManager *&prMenuManager)
{
	// �t�B�[���h���j���[�}�l�[�W���[�̏I��
	assert(prMenuManager != nullptr);
	prMenuManager->Uninit();

	// �������J��
	SAFE_DELETE(prMenuManager);
}