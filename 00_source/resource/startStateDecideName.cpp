//============================================================
//
//	���O�����ԏ��� [startStateDecideName.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startStateDecideName.h"
#include "startManager.h"
#include "loadtext.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* PATH = "data\\TXT\\TEXT\\naming.txt";	// �e�L�X�g�p�X
}

//************************************************************
//	�q�N���X [CStartStateDecideName] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateDecideName::CStartStateDecideName() :
	m_pNearNameManager	(nullptr)	// ���O�ڋ߃}�l�[�W���[
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CStartStateDecideName::~CStartStateDecideName()
{

}

//============================================================
//	����������
//============================================================
HRESULT CStartStateDecideName::Init()
{
	// �����o�ϐ���������
	m_pNearNameManager = nullptr;	// ���O�ڋ߃}�l�[�W���[

	// ���O�ڋ߃}�l�[�W���[�̐���
	const std::string& rName = m_pContext->GetName();	// ����������
	m_pNearNameManager = CNearNameManager::Create
	( // ����
		rName,									// �\����
		loadtext::LoadText(PATH, rName.c_str())	// �^�C�g�������e�L�X�g
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
void CStartStateDecideName::Uninit()
{
	// ���O�ڋ߃}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pNearNameManager);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CStartStateDecideName::Update(const float fDeltaTime)
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
void CStartStateDecideName::UpdateDecide(const CNearNameManager::ESelect select)
{
	// �I�����ɉ����đJ�ڐ��ύX
	switch (select)
	{ // ���݂̑I�������Ƃ̏���
	case CNearNameManager::SELECT_NO:

		// ������Ԃɂ���
		m_pContext->ChangeState(new CStartStateCreateName);
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
