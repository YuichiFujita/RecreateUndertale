//============================================================
//
//	名前決定状態処理 [startStateDecideName.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "startStateDecideName.h"
#include "startManager.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* PATH = "data\\TXT\\TEXT\\naming.txt";	// テキストパス
}

//************************************************************
//	子クラス [CStartStateDecideName] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartStateDecideName::CStartStateDecideName() :
	m_pNearNameManager	(nullptr)	// 名前接近マネージャー
{

}

//============================================================
//	デストラクタ
//============================================================
CStartStateDecideName::~CStartStateDecideName()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CStartStateDecideName::Init()
{
	// メンバ変数を初期化
	m_pNearNameManager = nullptr;	// 名前接近マネージャー

	// 名前接近マネージャーの生成
	const std::string& rName = m_pContext->GetName();	// 命名文字列
	m_pNearNameManager = CNearNameManager::Create
	( // 引数
		rName,									// 表示名
		loadtext::LoadText(PATH, rName.c_str())	// タイトル割当テキスト
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
void CStartStateDecideName::Uninit()
{
	// 名前接近マネージャーの破棄
	SAFE_REF_RELEASE(m_pNearNameManager);

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CStartStateDecideName::Update(const float fDeltaTime)
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
void CStartStateDecideName::UpdateDecide(const CNearNameManager::ESelect select)
{
	// 選択肢に応じて遷移先を変更
	switch (select)
	{ // 現在の選択肢ごとの処理
	case CNearNameManager::SELECT_NO:

		// 命名状態にする
		m_pContext->ChangeState(new CStartStateCreateName);
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
