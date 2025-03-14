//============================================================
//
//	マップタイル処理 [tileMap.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "tileMap.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* TEXTURE_FILE[] =	// テクスチャファイル
	{
		nullptr,	// テクスチャなし
		"data\\TEXTURE\\RUINS\\spr_fallpoint.png",		// 初期落下地点
		"data\\TEXTURE\\RUINS\\spr_ruinsgate.png",		// ルインズ入口前
		"data\\TEXTURE\\RUINS\\spr_ruinsstairs.png",	// ルインズ大階段
	};
	const int PRIORITY = 3;	// マップタイルの優先順位
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CTileMap::TYPE_MAX, "ERROR : Type Count Mismatch");

//************************************************************
//	子クラス [CTileMap] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTileMap::CTileMap() : CObject3D(CObject::LABEL_TILE, CObject::DIM_3D, PRIORITY),
	m_type	((EType)0)	// 種類
{

}

//============================================================
//	デストラクタ
//============================================================
CTileMap::~CTileMap()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTileMap::Init()
{
	// メンバ変数を初期化
	m_type = TYPE_NONE;	// 種類

	// オブジェクト3Dの初期化
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 大きさを設定
	SetVec3Size(VECTOR3(SIZE_TILE, SIZE_TILE, 0.0f));

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CTileMap::Uninit()
{
	// オブジェクト3Dの終了
	CObject3D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CTileMap::Update(const float fDeltaTime)
{
	// オブジェクト3Dの更新
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CTileMap::Draw(CShader* pShader)
{
	// オブジェクト3Dの描画
	CObject3D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CTileMap* CTileMap::Create(const EType type, const VECTOR3& rPos)
{
	// マップタイルの生成
	CTileMap* pTileMap = new CTileMap;
	if (pTileMap == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// マップタイルの初期化
		if (FAILED(pTileMap->Init()))
		{ // 初期化に失敗した場合

			// マップタイルの破棄
			SAFE_DELETE(pTileMap);
			return nullptr;
		}

		// 種類を設定
		pTileMap->SetType(type);

		// 位置を設定
		pTileMap->SetVec3Position(rPos);

		// 確保したアドレスを返す
		return pTileMap;
	}
}

//============================================================
//	種類設定処理
//============================================================
void CTileMap::SetType(const EType type)
{
	// 種類を保存
	m_type = type;

	// テクスチャを割当
	BindTexture(TEXTURE_FILE[type]);

	if (m_type == TYPE_FALL_POINT)
	{
		// 大きさを設定
		SetVec3Size(VECTOR3(SIZE_TILE * 34.0f, SIZE_TILE * 13.0f, 0.0f));	// TODO：どうにかしよう
	}
	if (m_type == TYPE_RUINS_GATE)
	{
		// 大きさを設定
		SetVec3Size(VECTOR3(SIZE_TILE * 16.0f, SIZE_TILE * 17.0f, 0.0f));	// TODO：どうにかしよう
	}
	if (m_type == TYPE_RUINS_STAIRS)
	{
		// 大きさを設定
		SetVec3Size(VECTOR3(SIZE_TILE * 14.0f, SIZE_TILE * 6.4f, 0.0f));	// TODO：どうにかしよう
	}
}
