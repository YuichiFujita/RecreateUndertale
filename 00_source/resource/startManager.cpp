//============================================================
//
//	スタートマネージャー処理 [startManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "startManager.h"
#include "startState.h"

//************************************************************
//	親クラス [CStartManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartManager::CStartManager() :
	m_pState	(nullptr)	// 状態
{

}

//============================================================
//	デストラクタ
//============================================================
CStartManager::~CStartManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CStartManager::Init()
{
	// メンバ変数を初期化
	m_pState = nullptr;	// 状態

	// ロゴ表示状態にする
	ChangeState(new CStartStateLogo);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CStartManager::Uninit()
{
	// 状態の終了
	SAFE_UNINIT(m_pState);
}

//============================================================
//	更新処理
//============================================================
void CStartManager::Update(const float fDeltaTime)
{
	// 状態ごとの更新
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	状態の変更処理
//============================================================
HRESULT CStartManager::ChangeState(CStartState* pState)
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
CStartManager* CStartManager::Create()
{
	// スタートマネージャーの生成
	CStartManager* pStartManager = new CStartManager;
	if (pStartManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// スタートマネージャーの初期化
		if (FAILED(pStartManager->Init()))
		{ // 初期化に失敗した場合

			// スタートマネージャーの破棄
			SAFE_DELETE(pStartManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pStartManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CStartManager::Release(CStartManager*& prStartManager)
{
	// スタートマネージャーの終了
	assert(prStartManager != nullptr);
	prStartManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prStartManager);
}
