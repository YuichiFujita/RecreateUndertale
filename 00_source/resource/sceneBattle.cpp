//============================================================
//
//	バトル画面処理 [sceneBattle.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "sceneBattle.h"
#include "manager.h"
#include "texture.h"
#include "sound.h"
#include "camera.h"
#include "battleManager.h"

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CBattleManager* CSceneBattle::m_pBattleManager = nullptr;	// バトルマネージャー

//************************************************************
//	子クラス [CSceneBattle] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSceneBattle::CSceneBattle(const EMode mode) : CScene(mode)
{

}

//============================================================
//	デストラクタ
//============================================================
CSceneBattle::~CSceneBattle()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSceneBattle::Init()
{
	// シーンの初期化
	if (FAILED(CScene::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// バトルマネージャーの生成
	m_pBattleManager = CBattleManager::Create();
	if (m_pBattleManager == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 固定カメラにする
	CCamera* pCamera = GET_MANAGER->GetCamera();	// カメラ情報
	pCamera->SetState(CCamera::STATE_NONE);			// 固定状態を設定

	// BGMの再生
	//PLAY_SOUND(CSound::LABEL_BGM_GENERAL);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSceneBattle::Uninit()
{
	// バトルマネージャーの破棄
	SAFE_REF_RELEASE(m_pBattleManager);

	// シーンの終了
	CScene::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSceneBattle::Update(const float fDeltaTime)
{
	// バトルマネージャーの更新
	assert(m_pBattleManager != nullptr);
	m_pBattleManager->Update(fDeltaTime);

	// シーンの更新
	CScene::Update(fDeltaTime);
}

//============================================================
//	バトルマネージャー取得処理
//============================================================
CBattleManager* CSceneBattle::GetBattleManager()
{
	// インスタンス未使用
	assert(m_pBattleManager != nullptr);

	// バトルマネージャーを返す
	return m_pBattleManager;
}
