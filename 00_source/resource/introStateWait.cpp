//============================================================
//
//	待機状態処理 [introStateWait.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "introStateWait.h"
#include "introManager.h"

//************************************************************
//	子クラス [CIntroStateWait] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CIntroStateWait::CIntroStateWait(const float fEndTime) :
	m_fEndTime	(fEndTime),	// 待機の終了時間
	m_fCurTime	(0.0f)		// 現在の待機時間
{

}

//============================================================
//	デストラクタ
//============================================================
CIntroStateWait::~CIntroStateWait()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CIntroStateWait::Init()
{
	// メンバ変数を初期化
	m_fCurTime = 0.0f;	// 現在の待機時間

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CIntroStateWait::Uninit()
{
	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CIntroStateWait::Update(const float fDeltaTime)
{
	// 待機時刻を進める
	m_fCurTime += fDeltaTime;
	if (m_fCurTime >= m_fEndTime)
	{ // 待機終了した場合

		// 待機時間を初期化
		m_fCurTime = 0.0f;

		if (m_pContext->GetStoryIdx() >= (int)CIntroManager::STORY_MAX - 1)
		{ // 最後の物語の場合

			// 物語スクロール状態にする
			m_pContext->ChangeState(new CIntroStateScroll);
		}
		else
		{ // 物語がまだある場合

			// フェード状態にする
			m_pContext->ChangeState(new CIntroStateFade);
		}
	}
}
