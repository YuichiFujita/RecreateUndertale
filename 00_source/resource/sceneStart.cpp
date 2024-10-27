//============================================================
//
//	スタート画面処理 [sceneStart.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "sceneStart.h"
#include "manager.h"
#include "texture.h"
#include "sound.h"
#include "camera.h"
#include "startManager.h"

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CStartManager* CSceneStart::m_pStartManager = nullptr;	// スタートマネージャー

//************************************************************
//	子クラス [CSceneStart] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSceneStart::CSceneStart(const EMode mode) : CScene(mode)
{

}

//============================================================
//	デストラクタ
//============================================================
CSceneStart::~CSceneStart()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSceneStart::Init()
{
	// シーンの初期化
	if (FAILED(CScene::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// スタートマネージャーの生成
	m_pStartManager = CStartManager::Create();
	if (m_pStartManager == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 固定カメラにする
	CCamera* pCamera = GET_MANAGER->GetCamera();	// カメラ情報
	pCamera->SetState(CCamera::STATE_NONE);			// 固定状態を設定

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSceneStart::Uninit()
{
	// スタートマネージャーの破棄
	SAFE_REF_RELEASE(m_pStartManager);

	// シーンの終了
	CScene::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSceneStart::Update(const float fDeltaTime)
{
	// スタートマネージャーの更新
	assert(m_pStartManager != nullptr);
	m_pStartManager->Update(fDeltaTime);

	// シーンの更新
	CScene::Update(fDeltaTime);
}

//============================================================
//	スタートマネージャー取得処理
//============================================================
CStartManager* CSceneStart::GetStartManager()
{
	// インスタンス未使用
	assert(m_pStartManager != nullptr);

	// スタートマネージャーを返す
	return m_pStartManager;
}
