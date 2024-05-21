//============================================================
//
//	イントロ状態処理 [introState.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "introState.h"
#include "manager.h"

// TODO
#include "introManager.h"
#include "object2D.h"
#include "scroll2D.h"
#include "scrollText2D.h"

//************************************************************
//	親クラス [CIntroContext] のメンバ関数
//************************************************************
//============================================================
//	更新処理処理
//============================================================
void CIntroContext::Update(const float fDeltaTime)
{
	// 状態の更新
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	状態の変更処理
//============================================================
void CIntroContext::Change(CIntroState *pState)
{
	// 自身のインスタンスを破棄
	assert(pState != nullptr);
	SAFE_DELETE(m_pState);

	// 自身のインスタンスを変更
	assert(m_pState == nullptr);
	m_pState = pState;
}

//************************************************************
//	子クラス [CIntroStateLogo] のメンバ関数
//************************************************************
//============================================================
//	更新処理
//============================================================
void CIntroStateLogo::Update(const float fDeltaTime)
{
	if (m_pContext->m_pIntro->WaitTime(fDeltaTime, 4.0f))
	{ // 待機終了した場合

		// タイトルロゴの自動描画をOFFにする
		m_pContext->m_pIntro->m_pLogo->SetEnableDraw(false);

		// ストーリーの自動描画をONにする
		m_pContext->m_pIntro->m_pStory->SetEnableDraw(true);

		// 文字送りを開始する
		m_pContext->m_pIntro->m_pText->SetEnableScroll(true);

		// 文字送り状態にする
		m_pContext->Change(new CIntroStateText(m_pContext));
	}
}

//************************************************************
//	子クラス [CIntroStateText] のメンバ関数
//************************************************************
//============================================================
//	更新処理
//============================================================
void CIntroStateText::Update(const float fDeltaTime)
{
	if (!m_pContext->m_pIntro->m_pText->IsScroll())
	{ // 文字送りが終了した場合

		// 待機状態にする
		m_pContext->Change(new CIntroStateWait(m_pContext));
	}
}

//************************************************************
//	子クラス [CIntroStateWait] のメンバ関数
//************************************************************
//============================================================
//	更新処理
//============================================================
void CIntroStateWait::Update(const float fDeltaTime)
{
	if (m_pContext->m_pIntro->WaitTime(fDeltaTime, 2.0f))
	{ // 待機終了した場合

		// 物語と状態を遷移させる
		m_pContext->m_pIntro->NextStory();
	}
}

//************************************************************
//	子クラス [CIntroStateEnd] のメンバ関数
//************************************************************
//============================================================
//	更新処理
//============================================================
void CIntroStateEnd::Update(const float fDeltaTime)
{
	// タイトルにロードせず遷移
	GET_MANAGER->SetScene(CScene::MODE_TITLE);
}
