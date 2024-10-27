//============================================================
//
//	タイトルマネージャー処理 [titleManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "titleManager.h"
#include "manager.h"

// TODO：デバッグ
#include "objectMeshField.h"
#include "objectMeshWall.h"
#include "object3D.h"
#include "objectBillboard.h"
#include "objectMeshCircle.h"
#include "objectMeshCube.h"
#include "objectMeshCylinder.h"
#include "objectMeshDome.h"
#include "objectMeshRing.h"
#include "objectMeshTube.h"
#include "objectModel.h"
#include "objectTornado.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{

}

//************************************************************
//	親クラス [CTitleManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTitleManager::CTitleManager()
{

}

//============================================================
//	デストラクタ
//============================================================
CTitleManager::~CTitleManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTitleManager::Init()
{
	// 地面
	CObjectMeshField* pField = CObjectMeshField::Create(VEC3_ZERO, VEC3_ZERO, VECTOR2(5000.0f, 500.0f), color::Yellow(), POSGRID2(10, 10));
	pField->SetLabel(CObject::LABEL_DEBUG);

	// 壁
	CObjectMeshWall* pWall = CObjectMeshWall::Create(VECTOR3(0.0f, 0.0f, 250.0f), VEC3_ZERO, VECTOR2(5000.0f, 500.0f), color::Cyan(), POSGRID2(10, 10));
	pWall->SetLabel(CObject::LABEL_DEBUG);

	// 3D
	CObject3D* p3D = CObject3D::Create(VECTOR3(0.0f, 50.0f, 0.0f), VECTOR3(50.0f, 50.0f, 0.0f));
	p3D->SetLabel(CObject::LABEL_DEBUG);

	// ビルボード
	CObjectBillboard* pBill = CObjectBillboard::Create(VECTOR3(150.0f, 50.0f, 0.0f), VECTOR3(50.0f, 50.0f, 0.0f));
	pBill->SetLabel(CObject::LABEL_DEBUG);
	//pBill->SetRotate(CObjectBillboard::ROTATE_LATERAL);

	// サークル
	CObjectMeshCircle* pCircle = CObjectMeshCircle::Create(VECTOR3(-150.0f, 50.0f, 0.0f), VEC3_ZERO, color::White(), POSGRID2(10, 10), 50.0f);
	pCircle->SetLabel(CObject::LABEL_DEBUG);

	// キューブ
	CObjectMeshCube* pCube = CObjectMeshCube::Create(VECTOR3(300.0f, 50.0f, 0.0f), VEC3_ZERO, VECTOR3(50.0f), color::White());
	pCube->SetLabel(CObject::LABEL_DEBUG);

	// シリンダー
	CObjectMeshCylinder* pCylinder = CObjectMeshCylinder::Create(VECTOR3(-300.0f, 50.0f, 0.0f), VEC3_ZERO, color::White(), POSGRID2(10), POSGRID2(10), 50.0f, 50.0f);
	pCylinder->SetLabel(CObject::LABEL_DEBUG);

	// ドーム
	CObjectMeshDome* pDome = CObjectMeshDome::Create(VECTOR3(450.0f, 50.0f, 0.0f), VEC3_ZERO, color::White(), POSGRID2(10), POSGRID2(10), 50.0f);
	pDome->SetLabel(CObject::LABEL_DEBUG);

	// リング
	CObjectMeshRing* pRing = CObjectMeshRing::Create(VECTOR3(-450.0f, 50.0f, 0.0f), VEC3_ZERO, color::White(), POSGRID2(10), POSGRID2(10), 50.0f, 50.0f, 50.0f);
	pRing->SetLabel(CObject::LABEL_DEBUG);

	// チューブ
	CObjectMeshTube* pTube = CObjectMeshTube::Create(VECTOR3(600.0f, 50.0f, 0.0f), VEC3_ZERO, color::White(), POSGRID2(10), POSGRID2(10),50.0f, 50.0f);
	pTube->SetLabel(CObject::LABEL_DEBUG);

	// モデル
	CObjectModel* pModel = CObjectModel::Create(VECTOR3(-600.0f, 50.0f, 0.0f), VEC3_ZERO);
	pModel->SetLabel(CObject::LABEL_DEBUG);
	pModel->BindModel("data\\MODEL\\02_head.x");

	// トルネード
	CObjectTornado* pTornado = CObjectTornado::Create(VECTOR3(750.0f, 50.0f, 0.0f), VEC3_ZERO, color::White());
	pTornado->SetLabel(CObject::LABEL_DEBUG);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CTitleManager::Uninit()
{

}

//============================================================
//	更新処理
//============================================================
void CTitleManager::Update(const float fDeltaTime)
{
	CInputKeyboard*	pKeyboard	= GET_INPUTKEY;	// キーボード
	CInputPad*		pPad		= GET_INPUTPAD;	// パッド
	if (pKeyboard->IsTrigger(DIK_RETURN)
	||  pKeyboard->IsTrigger(DIK_SPACE)
	||  pPad->IsTrigger(CInputPad::KEY_A)
	||  pPad->IsTrigger(CInputPad::KEY_B)
	||  pPad->IsTrigger(CInputPad::KEY_X)
	||  pPad->IsTrigger(CInputPad::KEY_Y)
	||  pPad->IsTrigger(CInputPad::KEY_START))
	{
		// イントロ画面に遷移する
		GET_MANAGER->SetFadeScene(CScene::MODE_INTRO);
	}
}

//============================================================
//	生成処理
//============================================================
CTitleManager* CTitleManager::Create()
{
	// タイトルマネージャーの生成
	CTitleManager* pTitleManager = new CTitleManager;
	if (pTitleManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// タイトルマネージャーの初期化
		if (FAILED(pTitleManager->Init()))
		{ // 初期化に失敗した場合

			// タイトルマネージャーの破棄
			SAFE_DELETE(pTitleManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pTitleManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CTitleManager::Release(CTitleManager*& prTitleManager)
{
	// タイトルマネージャーの終了
	assert(prTitleManager != nullptr);
	prTitleManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prTitleManager);
}
