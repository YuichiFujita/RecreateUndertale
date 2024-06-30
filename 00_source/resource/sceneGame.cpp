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
#include "pause.h"
#include "hitStop.h"

// TODO
#include "mapTile.h"
#include "objectChara2D.h"

// TODO
CObjectChara2D *g_pChara;

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CGameManager	*CSceneGame::m_pGameManager	= nullptr;	// ゲームマネージャー
CPause			*CSceneGame::m_pPause		= nullptr;	// ポーズ
CHitStop		*CSceneGame::m_pHitStop		= nullptr;	// ヒットストップ

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

	// ポーズの生成
	m_pPause = CPause::Create();
	if (m_pPause == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// ヒットストップの生成
	m_pHitStop = CHitStop::Create();
	if (m_pHitStop == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	初期設定
	//--------------------------------------------------------
	// TODO
	CMapTile::Create(CMapTile::TYPE_FALL_POINT, VEC3_ZERO);

	// TODO
	g_pChara = CObjectChara2D::Create(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	g_pChara->SetLabel(CObject::LABEL_DEBUG);
	g_pChara->BindCharaData("data\\CHARACTER\\frisk.txt");
	g_pChara->SetMotion(0);

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

	// ポーズの破棄
	SAFE_REF_RELEASE(m_pPause);

	// ヒットストップの破棄
	SAFE_REF_RELEASE(m_pHitStop);

	// シーンの終了
	CScene::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSceneGame::Update(const float fDeltaTime)
{
	// ゲームマネージャーの更新
	assert(m_pGameManager != nullptr);
	m_pGameManager->Update(fDeltaTime);

	// ヒットストップの更新
	assert(m_pHitStop != nullptr);
	m_pHitStop->Update(fDeltaTime);

	if (m_pGameManager->GetState() == CGameManager::STATE_NORMAL && !m_pHitStop->IsStop())
	{ // ゲームが通常状態の場合

		// ポーズの更新
		assert(m_pPause != nullptr);
		m_pPause->Update(fDeltaTime);
	}

	if (!m_pPause->IsPause()
	&&  !m_pHitStop->IsStop())
	{ // ポーズ中・ヒットストップ中ではない場合

		// シーンの更新
		CScene::Update(fDeltaTime);
	}
	else if (m_pHitStop->IsStop())
	{ // ヒットストップ中の場合

		// カメラの更新
		GET_MANAGER->GetCamera()->Update(fDeltaTime);
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

	// TODO
	D3DXVECTOR3 posChara = g_pChara->GetVec3Position();
	if (GET_INPUTKEY->IsPress(DIK_LEFT))
	{
		posChara.x -= 180.0f * fDeltaTime;

		if (g_pChara->GetMotion() != 2)
		g_pChara->SetMotion(2);
	}
	if (GET_INPUTKEY->IsPress(DIK_RIGHT))
	{
		posChara.x += 180.0f * fDeltaTime;

		if (g_pChara->GetMotion() != 3)
		g_pChara->SetMotion(3);
	}
	if (GET_INPUTKEY->IsPress(DIK_UP))
	{
		posChara.y += 180.0f * fDeltaTime;

		if (g_pChara->GetMotion() != 0)
		g_pChara->SetMotion(0);
	}
	if (GET_INPUTKEY->IsPress(DIK_DOWN))
	{
		posChara.y -= 180.0f * fDeltaTime;

		if (g_pChara->GetMotion() != 1)
		g_pChara->SetMotion(1);
	}
	g_pChara->SetVec3Position(posChara);
}

//============================================================
//	ゲームマネージャー取得処理
//============================================================
CGameManager *CSceneGame::GetGameManager(void)
{
	// インスタンス未使用
	assert(m_pGameManager != nullptr);

	// ゲームマネージャーのポインタを返す
	return m_pGameManager;
}

//============================================================
//	ポーズ取得処理
//============================================================
CPause *CSceneGame::GetPause(void)
{
	// インスタンス未使用
	assert(m_pPause != nullptr);

	// ポーズのポインタを返す
	return m_pPause;
}

//============================================================
//	ヒットストップ取得処理
//============================================================
CHitStop *CSceneGame::GetHitStop(void)
{
	// インスタンス未使用
	assert(m_pHitStop != nullptr);

	// ヒットストップのポインタを返す
	return m_pHitStop;
}
