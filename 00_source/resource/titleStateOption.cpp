//============================================================
//
//	�ݒ��ԏ��� [titleStateOption.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "titleStateOption.h"
#include "titleManager.h"
#include "optionManager.h"

//************************************************************
//	�q�N���X [CTitleStateOption] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTitleStateOption::CTitleStateOption() :
	m_pOptionManager	(nullptr)	// �ݒ�}�l�[�W���[
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CTitleStateOption::~CTitleStateOption()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTitleStateOption::Init()
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
void CTitleStateOption::Uninit()
{
	// �ݒ�}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pOptionManager);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CTitleStateOption::Update(const float fDeltaTime)
{
	// �ݒ�}�l�[�W���[�̍X�V
	assert(m_pOptionManager != nullptr);
	if (m_pOptionManager->Update(fDeltaTime))
	{ // ��ԑJ�ڂ̑��삪�s��ꂽ�ꍇ

		// �J�ڑI����Ԃɂ���
		m_pContext->ChangeState(new CTitleStateSelect);
	}
}
