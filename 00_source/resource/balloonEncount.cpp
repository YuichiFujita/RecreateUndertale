//============================================================
//
//	エンカウント吹き出し処理 [balloonEncount.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "balloonEncount.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* TEXTURE_FILE[] =	// テクスチャファイル
	{
		"data\\TEXTURE\\spr_exc_0.png"	// 通常エンカウント
	};
	const int PRIORITY = 6;	// エンカウント吹き出しの優先順位

	namespace balloon
	{
		const VECTOR3 SIZE = VECTOR3(30.0f, 30.0f, 0.0f);	// 大きさ
	}
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CBalloonEncount::TYPE_MAX, "ERROR : Type Count Mismatch");

//************************************************************
//	子クラス [CBalloonEncount] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBalloonEncount::CBalloonEncount() : CObject3D(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY),
	m_type	((EType)0)	// 種類
{

}

//============================================================
//	デストラクタ
//============================================================
CBalloonEncount::~CBalloonEncount()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBalloonEncount::Init()
{
	// メンバ変数を初期化
	m_type = TYPE_ENCOUNT;	// 種類

	// オブジェクト3Dの初期化
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 大きさを設定
	SetVec3Size(balloon::SIZE);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBalloonEncount::Uninit()
{
	// オブジェクト3Dの終了
	CObject3D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CBalloonEncount::Update(const float fDeltaTime)
{
	// オブジェクト3Dの更新
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CBalloonEncount::Draw(CShader* pShader)
{
	// オブジェクト3Dの描画
	CObject3D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CBalloonEncount* CBalloonEncount::Create(const EType type, const VECTOR3& rPos, const VECTOR3& rRot, const VECTOR2& rOffset)
{
	// エンカウント吹き出しの生成
	CBalloonEncount* pBalloonEncount = new CBalloonEncount;
	if (pBalloonEncount == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// エンカウント吹き出しの初期化
		if (FAILED(pBalloonEncount->Init()))
		{ // 初期化に失敗した場合

			// エンカウント吹き出しの破棄
			SAFE_DELETE(pBalloonEncount);
			return nullptr;
		}

		// 種類を設定
		pBalloonEncount->SetType(type);

		// 相対位置の設定
		pBalloonEncount->SetPositionRelative(rPos, rRot, rOffset);

		// 確保したアドレスを返す
		return pBalloonEncount;
	}
}

//============================================================
//	相対位置の設定処理
//============================================================
void CBalloonEncount::SetPositionRelative(const VECTOR3& rPos, const VECTOR3& rRot, const VECTOR2& rOffset)
{
	VECTOR3 posThis = rPos;	// 自身の位置

	// X座標オフセット分ずらす
	posThis.x += sinf(rRot.z + HALF_PI) * rOffset.x;
	posThis.y += cosf(rRot.z + HALF_PI) * rOffset.x;

	// Y座標オフセット分ずらす
	posThis.x += sinf(rRot.z) * rOffset.y;
	posThis.y += cosf(rRot.z) * rOffset.y;

	// TODO：Z座標の決め方
	// Z座標を設定
	posThis.z = -10.0f;

	// 相対位置の反映
	CObject3D::SetVec3Position(posThis);
}

//============================================================
//	種類設定処理
//============================================================
void CBalloonEncount::SetType(const EType type)
{
	// 種類を保存
	m_type = type;

	// テクスチャを割当
	BindTexture(TEXTURE_FILE[type]);
}
