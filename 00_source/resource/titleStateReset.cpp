//============================================================
//
//	リセット状態処理 [titleStateReset.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "titleStateReset.h"
#include "titleManager.h"
#include "loadtext.h"
#include "userdataManager.h"
#include "playerStatus.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* PATH = "data\\TEXT\\title.txt";	// テキストパス
}

//************************************************************
//	子クラス [CTitleStateReset] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTitleStateReset::CTitleStateReset() :
	m_pNearNameManager	(nullptr)	// 名前接近マネージャー
{

}

//============================================================
//	デストラクタ
//============================================================
CTitleStateReset::~CTitleStateReset()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTitleStateReset::Init()
{
	CUserDataManager* pUserData = CUserDataManager::GetInstance();	// ユーザーデータマネージャー
	CPlayerStatus status;	// ステータス情報

	// メンバ変数を初期化
	m_pNearNameManager = nullptr;	// 名前接近マネージャー

	// プレイヤーステータス情報の読込
	pUserData->LoadPlayerStatus(&status);

	// 名前接近マネージャーの生成
	m_pNearNameManager = CNearNameManager::Create
	( // 引数
		status.GetName(),	// 表示名
		loadtext::LoadText(PATH, CTitleManager::TEXT_RESET_TITLE)	// タイトル割当テキスト
	);
	if (m_pNearNameManager == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CTitleStateReset::Uninit()
{
	// 名前接近マネージャーの破棄
	SAFE_REF_RELEASE(m_pNearNameManager);

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CTitleStateReset::Update(const float fDeltaTime)
{
	// 名前接近マネージャーの更新
	assert(m_pNearNameManager != nullptr);
	CNearNameManager::ESelect select = m_pNearNameManager->Update(fDeltaTime);	// 選択肢の取得

	if (select != CNearNameManager::SELECT_NONE)
	{ // 選択操作が行われた場合

		// 決定の更新
		UpdateDecide(select);
	}
}

//============================================================
//	決定の更新処理
//============================================================
void CTitleStateReset::UpdateDecide(const CNearNameManager::ESelect select)
{
	// 選択肢に応じて遷移先を変更
	switch (select)
	{ // 現在の選択肢ごとの処理
	case CNearNameManager::SELECT_NO:

		// 遷移選択状態にする
		m_pContext->ChangeState(new CTitleStateSelect);
		break;

	case CNearNameManager::SELECT_YES:

		// ゲーム画面に遷移する
		assert(m_pNearNameManager != nullptr);
		m_pNearNameManager->TransGame();
		break;

	default:
		assert(false);
		break;
	}
}
