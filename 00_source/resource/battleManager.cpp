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

// TODO：ちらつきがないかの検証
#if 1
#include "object2D.h"
#endif

#include "userdataManager.h"
#include "playerStatus.h"
#include "frame2D.h"
#include "battleCommandUI.h"
#include "battleNameUI.h"
#include "battleLifeUI.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	// TODO：ちらつきがないかの検証
#if 1
	namespace soul
	{
		const char*		PATH		= "data\\TEXTURE\\spr_heart_0.png";	// ソウルのテクスチャパス
		const int		PRIO_NORMAL	= 6;								// ソウルの優先順位（通常時）
		const int		PRIO_FADE	= 8;								// ソウルの優先順位（フェード時）
		const VECTOR3	SIZE		= VECTOR3(25.5f, 25.5f, 0.0f);		// ソウルの大きさ
	}
#endif
}

//************************************************************
//	親クラス [CBattleManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBattleManager::CBattleManager() :
	m_pState		(nullptr),	// 状態
	m_pPlayer		(nullptr),	// プレイヤー情報
	m_pFrame		(nullptr),	// フレーム情報
	m_pCommandUI	(nullptr),	// コマンド表示
	m_pNameUI		(nullptr),	// 名前表示
	m_pLifeUI		(nullptr)	// 体力表示
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
	m_pState	 = nullptr;	// 状態
	m_pPlayer	 = nullptr;	// プレイヤー情報
	m_pFrame	 = nullptr;	// フレーム情報
	m_pCommandUI = nullptr;	// コマンド表示
	m_pNameUI	 = nullptr;	// 名前表示
	m_pLifeUI	 = nullptr;	// 体力表示

	// TODO：ちらつきがないかの検証
#if 1
	// ソウルの生成
	m_pPlayer = CObject2D::Create
	( // 引数
		VEC3_ZERO,	// 位置
		soul::SIZE	// 大きさ
	);
	if (m_pPlayer == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ソウルテクスチャを割当
	m_pPlayer->BindTexture(soul::PATH);

	// ラベルを設定
	m_pPlayer->SetLabel(CObject::LABEL_UI);

	// 優先順位を設定
	m_pPlayer->SetPriority(soul::PRIO_FADE);
#endif

	// ステータスの読込
	CUserDataManager* pUserData = CUserDataManager::GetInstance();	// ユーザーデータ情報
	CPlayerStatus     status;	// ステータス情報
	if (FAILED(pUserData->LoadPlayerStatus(&status)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// テキストボックスの生成
	m_pFrame = CFrame2D::Create(CFrame2D::PRESET_BATTLE_TEXT);
	if (m_pFrame == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// コマンド表示の生成
	m_pCommandUI = CBattleCommandUI::Create(m_pPlayer);
	if (m_pCommandUI == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 名前表示の生成
	m_pNameUI = CBattleNameUI::Create(status.GetName(), status.GetLove());
	if (m_pNameUI == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 体力表示の生成
	m_pLifeUI = CBattleLifeUI::Create(status.GetMaxHP(), status.GetHP());
	if (m_pLifeUI == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// コマンド選択状態にする
	ChangeState(new CBattleStateCommand);

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
