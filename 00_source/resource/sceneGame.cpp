//============================================================
//
//	ゲーム画面処理 [sceneGame.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "sceneGame.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"

#include "gameManager.h"
#include "menuManager.h"
#include "pause.h"
#include "stage.h"
#include "player.h"

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CGameManager* CSceneGame::m_pGameManager = nullptr;	// ゲームマネージャー
CMenuManager* CSceneGame::m_pMenuManager = nullptr;	// メニューマネージャー
CPause* CSceneGame::m_pPause = nullptr;	// ポーズ情報
CStage* CSceneGame::m_pStage = nullptr;	// ステージ情報

//************************************************************
//	子クラス [CSceneGame] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSceneGame::CSceneGame(const EMode mode) : CScene(mode)
{

}

//============================================================
//	デストラクタ
//============================================================
CSceneGame::~CSceneGame()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSceneGame::Init(void)
{
	//--------------------------------------------------------
	//	初期生成
	//--------------------------------------------------------
	// シーンの初期化
	if (FAILED(CScene::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// ゲームマネージャーの生成
	m_pGameManager = CGameManager::Create();
	if (m_pGameManager == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// メニューマネージャーの生成
	m_pMenuManager = CMenuManager::Create();
	if (m_pMenuManager == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// ポーズの生成
	m_pPause = CPause::Create();
	if (m_pPause == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

#if 1
	// TODO：プレイヤーの生成
	CPlayer::Create(VECTOR3(0.0f, 0.0f, -1.0f));
#endif

	// ステージの生成
	m_pStage = CStage::Create();
	if (m_pStage == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 追従カメラにする
	CCamera* pCamera = GET_MANAGER->GetCamera();	// カメラ情報
	pCamera->SetState(CCamera::STATE_FOLLOW);		// 追従状態を設定

	// BGMの再生
	PLAY_SOUND(CSound::LABEL_BGM_GENERAL);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSceneGame::Uninit(void)
{
	// ゲームマネージャーの破棄
	SAFE_REF_RELEASE(m_pGameManager);

	// メニューマネージャーの破棄
	SAFE_REF_RELEASE(m_pMenuManager);

	// ポーズの破棄
	SAFE_REF_RELEASE(m_pPause);

	// ステージの破棄
	SAFE_REF_RELEASE(m_pStage);

	// シーンの終了
	CScene::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSceneGame::Update(const float fDeltaTime)
{
	// フェード中の場合抜ける
	if (GET_MANAGER->GetFade()->IsFade()) { return; }

	// ゲームマネージャーの更新
	assert(m_pGameManager != nullptr);
	m_pGameManager->Update(fDeltaTime);

	// メニューマネージャーの更新
	assert(m_pMenuManager != nullptr);
	m_pMenuManager->Update(fDeltaTime);

	if (m_pGameManager->GetState() == CGameManager::STATE_NORMAL)
	{ // ゲームが通常状態の場合

		// ポーズの更新
		assert(m_pPause != nullptr);
		m_pPause->Update(fDeltaTime);
	}

	if (!m_pPause->IsPause())
	{ // ポーズ中ではない場合

		// シーンの更新
		CScene::Update(fDeltaTime);
	}

#ifdef _DEBUG

	else
	{ // ポーズ中の場合

		if (GET_MANAGER->GetCamera()->GetState() == CCamera::STATE_CONTROL)
		{ // カメラが操作状態の場合

			// カメラの更新
			GET_MANAGER->GetCamera()->Update(fDeltaTime);
		}
	}

#endif	// _DEBUG
}

//============================================================
//	ゲームマネージャー取得処理
//============================================================
CGameManager* CSceneGame::GetGameManager(void)
{
	// インスタンス未使用
	assert(m_pGameManager != nullptr);

	// ゲームマネージャーのポインタを返す
	return m_pGameManager;
}

//============================================================
//	メニューマネージャー取得処理
//============================================================
CMenuManager* CSceneGame::GetMenuManager(void)
{
	// インスタンス未使用
	assert(m_pMenuManager != nullptr);

	// メニューマネージャーのポインタを返す
	return m_pMenuManager;
}

//============================================================
//	ポーズ取得処理
//============================================================
CPause* CSceneGame::GetPause(void)
{
	// インスタンス未使用
	assert(m_pPause != nullptr);

	// ポーズのポインタを返す
	return m_pPause;
}

//============================================================
//	ステージ取得処理
//============================================================
CStage* CSceneGame::GetStage(void)
{
	// インスタンス未使用
	assert(m_pStage != nullptr);

	// ステージのポインタを返す
	return m_pStage;
}

//============================================================
//	プレイヤー取得処理
//============================================================
CPlayer* CSceneGame::GetPlayer(void)
{
	CListManager<CPlayer>* pListManager = CPlayer::GetList();	// プレイヤーリストマネージャー
	if (pListManager == nullptr)		{ return nullptr; }		// リスト未使用の場合抜ける
	if (pListManager->GetNumAll() != 1)	{ return nullptr; }		// プレイヤーが1人ではない場合抜ける
	CPlayer* pPlayer = pListManager->GetList().front();			// プレイヤー情報

	// インスタンス未使用
	assert(pPlayer != nullptr);

	// プレイヤーのポインタを返す
	return pPlayer;
}
