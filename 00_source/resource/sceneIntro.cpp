//============================================================
//
//	イントロ画面処理 [sceneIntro.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "sceneIntro.h"
#include "manager.h"
#include "texture.h"
#include "sound.h"
#include "camera.h"
#include "introManager.h"

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CIntroManager *CSceneIntro::m_pIntroManager = nullptr;	// イントロマネージャー

//************************************************************
//	子クラス [CSceneIntro] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSceneIntro::CSceneIntro(const EMode mode) : CScene(mode)
{

}

//============================================================
//	デストラクタ
//============================================================
CSceneIntro::~CSceneIntro()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSceneIntro::Init(void)
{
	// シーンの初期化
	if (FAILED(CScene::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// イントロマネージャーの生成
	m_pIntroManager = CIntroManager::Create();
	if (m_pIntroManager == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 固定カメラにする
	CCamera *pCamera = GET_MANAGER->GetCamera();	// カメラ情報
	pCamera->SetState(CCamera::STATE_NONE);			// 固定状態を設定

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSceneIntro::Uninit(void)
{
	// イントロマネージャーの破棄
	SAFE_REF_RELEASE(m_pIntroManager);

	// シーンの終了
	CScene::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSceneIntro::Update(const float fDeltaTime)
{
	// イントロマネージャーの更新
	assert(m_pIntroManager != nullptr);
	m_pIntroManager->Update(fDeltaTime);

	// シーンの更新
	CScene::Update(fDeltaTime);
}

//============================================================
//	イントロマネージャー取得処理
//============================================================
CIntroManager *CSceneIntro::GetIntroManager(void)
{
	// インスタンス未使用
	assert(m_pIntroManager != nullptr);

	// イントロマネージャーを返す
	return m_pIntroManager;
}
