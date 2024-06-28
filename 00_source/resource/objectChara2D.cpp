//============================================================
//
//	オブジェクトキャラクター2D処理 [objectChara2D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "objectChara2D.h"
#include "manager.h"
#include "renderer.h"
#include "motion2D.h"

//************************************************************
//	子クラス [CObjectChara2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CObjectChara2D::CObjectChara2D(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CAnim3D(label, dimension, nPriority),
	m_pMotion	(nullptr)	// モーション2D情報
{

}

//============================================================
//	デストラクタ
//============================================================
CObjectChara2D::~CObjectChara2D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CObjectChara2D::Init(void)
{
	// メンバ変数を初期化
	m_pMotion = nullptr;	// モーション2D情報

	// アニメーション3Dの初期化
	if (FAILED(CAnim3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// モーション2Dの生成
	m_pMotion = CMotion2D::Create(this);
	if (m_pMotion == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CObjectChara2D::Uninit(void)
{
	// モーション2Dの破棄
	SAFE_REF_RELEASE(m_pMotion);

	// アニメーション3Dの終了
	CAnim3D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CObjectChara2D::Update(const float fDeltaTime)
{
	// モーション2Dの更新
	assert(m_pMotion != nullptr);
	m_pMotion->Update(fDeltaTime);

	// アニメーション3Dの更新
	CAnim3D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CObjectChara2D::Draw(CShader *pShader)
{
	// アニメーション3Dの描画
	CAnim3D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CObjectChara2D *CObjectChara2D::Create(const D3DXVECTOR3 &rPos, const D3DXVECTOR3 &rRot)
{
	// オブジェクトキャラクター2Dの生成
	CObjectChara2D *pObjectChara2D = new CObjectChara2D;
	if (pObjectChara2D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// オブジェクトキャラクター2Dの初期化
		if (FAILED(pObjectChara2D->Init()))
		{ // 初期化に失敗した場合

			// オブジェクトキャラクター2Dの破棄
			SAFE_DELETE(pObjectChara2D);
			return nullptr;
		}

		// 位置を設定
		pObjectChara2D->SetVec3Position(rPos);

		// 向きを設定
		pObjectChara2D->SetVec3Rotation(rRot);

		// 確保したアドレスを返す
		return pObjectChara2D;
	}
}

//============================================================
//	キャラクター情報割当
//============================================================
void CObjectChara2D::BindCharaData(const char *pCharaPass)
{
	// 割り当てるモーションパスが存在しない場合抜ける
	if (pCharaPass == nullptr) { assert(false); return; }

	// キャラクター2D情報を取得
	CMotion2D::SInfo data = GET_MANAGER->GetCharacter2D()->Regist(pCharaPass);

	// モーション情報の全設定
	m_pMotion->SetAllInfo(data);
}

//============================================================
//	モーションの設定処理
//============================================================
void CObjectChara2D::SetMotion(const int nType)
{
	// モーションの設定
	m_pMotion->Set(nType);
}
