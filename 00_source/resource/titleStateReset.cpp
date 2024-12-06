//============================================================
//
//	���Z�b�g��ԏ��� [titleStateReset.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "titleStateReset.h"
#include "titleManager.h"
#include "loadtext.h"
#include "userdataManager.h"
#include "playerStatus.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* PATH = "data\\TEXT\\title.txt";	// �e�L�X�g�p�X
}

//************************************************************
//	�q�N���X [CTitleStateReset] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTitleStateReset::CTitleStateReset() :
	m_pNearNameManager	(nullptr)	// ���O�ڋ߃}�l�[�W���[
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CTitleStateReset::~CTitleStateReset()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTitleStateReset::Init()
{
	CUserDataManager* pUserData = CUserDataManager::GetInstance();	// ���[�U�[�f�[�^�}�l�[�W���[
	CPlayerStatus status;	// �X�e�[�^�X���

	// �����o�ϐ���������
	m_pNearNameManager = nullptr;	// ���O�ڋ߃}�l�[�W���[

	// �v���C���[�X�e�[�^�X���̓Ǎ�
	pUserData->LoadPlayerStatus(&status);

	// ���O�ڋ߃}�l�[�W���[�̐���
	m_pNearNameManager = CNearNameManager::Create
	( // ����
		status.GetName(),	// �\����
		loadtext::LoadText(PATH, CTitleManager::TEXT_RESET_TITLE)	// �^�C�g�������e�L�X�g
	);
	if (m_pNearNameManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CTitleStateReset::Uninit()
{
	// ���O�ڋ߃}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pNearNameManager);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CTitleStateReset::Update(const float fDeltaTime)
{
	// ���O�ڋ߃}�l�[�W���[�̍X�V
	assert(m_pNearNameManager != nullptr);
	CNearNameManager::ESelect select = m_pNearNameManager->Update(fDeltaTime);	// �I�����̎擾

	if (select != CNearNameManager::SELECT_NONE)
	{ // �I�𑀍삪�s��ꂽ�ꍇ

		// ����̍X�V
		UpdateDecide(select);
	}
}

//============================================================
//	����̍X�V����
//============================================================
void CTitleStateReset::UpdateDecide(const CNearNameManager::ESelect select)
{
	// �I�����ɉ����đJ�ڐ��ύX
	switch (select)
	{ // ���݂̑I�������Ƃ̏���
	case CNearNameManager::SELECT_NO:

		// �J�ڑI����Ԃɂ���
		m_pContext->ChangeState(new CTitleStateSelect);
		break;

	case CNearNameManager::SELECT_YES:

		// �Q�[����ʂɑJ�ڂ���
		assert(m_pNearNameManager != nullptr);
		m_pNearNameManager->TransGame();
		break;

	default:
		assert(false);
		break;
	}
}
