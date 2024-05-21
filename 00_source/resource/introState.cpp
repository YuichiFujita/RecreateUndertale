//============================================================
//
//	�C���g����ԏ��� [introState.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introState.h"
#include "manager.h"

// TODO
#include "introManager.h"
#include "object2D.h"
#include "scroll2D.h"
#include "scrollText2D.h"

//************************************************************
//	�e�N���X [CIntroContext] �̃����o�֐�
//************************************************************
//============================================================
//	�X�V��������
//============================================================
void CIntroContext::Update(const float fDeltaTime)
{
	// ��Ԃ̍X�V
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	��Ԃ̕ύX����
//============================================================
void CIntroContext::Change(CIntroState *pState)
{
	// ���g�̃C���X�^���X��j��
	assert(pState != nullptr);
	SAFE_DELETE(m_pState);

	// ���g�̃C���X�^���X��ύX
	assert(m_pState == nullptr);
	m_pState = pState;
}

//************************************************************
//	�q�N���X [CIntroStateLogo] �̃����o�֐�
//************************************************************
//============================================================
//	�X�V����
//============================================================
void CIntroStateLogo::Update(const float fDeltaTime)
{
	if (m_pContext->m_pIntro->WaitTime(fDeltaTime, 4.0f))
	{ // �ҋ@�I�������ꍇ

		// �^�C�g�����S�̎����`���OFF�ɂ���
		m_pContext->m_pIntro->m_pLogo->SetEnableDraw(false);

		// �X�g�[���[�̎����`���ON�ɂ���
		m_pContext->m_pIntro->m_pStory->SetEnableDraw(true);

		// ����������J�n����
		m_pContext->m_pIntro->m_pText->SetEnableScroll(true);

		// ���������Ԃɂ���
		m_pContext->Change(new CIntroStateText(m_pContext));
	}
}

//************************************************************
//	�q�N���X [CIntroStateText] �̃����o�֐�
//************************************************************
//============================================================
//	�X�V����
//============================================================
void CIntroStateText::Update(const float fDeltaTime)
{
	if (!m_pContext->m_pIntro->m_pText->IsScroll())
	{ // �������肪�I�������ꍇ

		// �ҋ@��Ԃɂ���
		m_pContext->Change(new CIntroStateWait(m_pContext));
	}
}

//************************************************************
//	�q�N���X [CIntroStateWait] �̃����o�֐�
//************************************************************
//============================================================
//	�X�V����
//============================================================
void CIntroStateWait::Update(const float fDeltaTime)
{
	if (m_pContext->m_pIntro->WaitTime(fDeltaTime, 2.0f))
	{ // �ҋ@�I�������ꍇ

		// ����Ə�Ԃ�J�ڂ�����
		m_pContext->m_pIntro->NextStory();
	}
}

//************************************************************
//	�q�N���X [CIntroStateEnd] �̃����o�֐�
//************************************************************
//============================================================
//	�X�V����
//============================================================
void CIntroStateEnd::Update(const float fDeltaTime)
{
	// �^�C�g���Ƀ��[�h�����J��
	GET_MANAGER->SetScene(CScene::MODE_TITLE);
}
