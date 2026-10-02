//============================================================
//
//	バトルマネージャー処理 [battleManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "battleManager.h"
#include "battleState.h"

//************************************************************
//	親クラス [CBattleManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBattleManager::CBattleManager() :
	m_pState	(nullptr)	// 状態
{

}

//============================================================
//	デストラクタ
//============================================================
CBattleManager::~CBattleManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBattleManager::Init()
{
	// メンバ変数を初期化
	m_pState = nullptr;	// 状態

	// 通常状態にする
	ChangeState(new CBattleStateNormal);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBattleManager::Uninit()
{
	// 状態の終了
	SAFE_UNINIT(m_pState);
}

//============================================================
//	更新処理
//============================================================
void CBattleManager::Update(const float fDeltaTime)
{
	// 状態ごとの更新
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	状態の変更処理
//============================================================
HRESULT CBattleManager::ChangeState(CBattleState* pState)
{
	// 状態の生成に失敗している場合抜ける
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// 状態インスタンスを終了
	SAFE_UNINIT(m_pState);

	// 状態インスタンスを変更
	assert(m_pState == nullptr);
	m_pState = pState;

	// 状態にコンテキストを設定
	m_pState->SetContext(this);

	// 状態インスタンスを初期化
	if (FAILED(m_pState->Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	生成処理
//============================================================
CBattleManager* CBattleManager::Create()
{
	// バトルマネージャーの生成
	CBattleManager* pBattleManager = new CBattleManager;
	if (pBattleManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// バトルマネージャーの初期化
		if (FAILED(pBattleManager->Init()))
		{ // 初期化に失敗した場合

			// バトルマネージャーの破棄
			SAFE_DELETE(pBattleManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pBattleManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CBattleManager::Release(CBattleManager*& prBattleManager)
{
	// バトルマネージャーの終了
	assert(prBattleManager != nullptr);
	prBattleManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prBattleManager);
}
