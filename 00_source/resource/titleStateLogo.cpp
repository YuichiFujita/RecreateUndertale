//============================================================
//
//	ロゴ表示状態処理 [titleStateLogo.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "titleStateLogo.h"
#include "titleManager.h"
#include "logoManager.h"

//************************************************************
//	子クラス [CTitleStateLogo] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTitleStateLogo::CTitleStateLogo() :
	m_pLogoManager	(nullptr)	// ロゴマネージャー
{

}

//============================================================
//	デストラクタ
//============================================================
CTitleStateLogo::~CTitleStateLogo()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTitleStateLogo::Init()
{
	// メンバ変数を初期化
	m_pLogoManager = nullptr;	// ロゴマネージャー

	// ロゴマネージャーの生成
	m_pLogoManager = CLogoManager::Create();
	if (m_pLogoManager == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CTitleStateLogo::Uninit()
{
	// ロゴマネージャーの破棄
	SAFE_REF_RELEASE(m_pLogoManager);

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CTitleStateLogo::Update(const float fDeltaTime)
{
	// ロゴマネージャーの更新
	assert(m_pLogoManager != nullptr);
	if (m_pLogoManager->Update(fDeltaTime))
	{ // 状態遷移の操作が行われた場合

		// 遷移選択状態にする
		m_pContext->ChangeState(new CTitleStateSelect);
	}
}
