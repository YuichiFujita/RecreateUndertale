//============================================================
//
//	出現タイル処理 [tileSpawn.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "tileSpawn.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* TEXTURE_FILE = "data\\TEXTURE\\DEBUG\\spawn000.png";
	const int PRIORITY = 3;	// 出現タイルの優先順位
}

//************************************************************
//	子クラス [CTileSpawn] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTileSpawn::CTileSpawn(const char* pPrevPath) : CObject3D(CObject::LABEL_TILE, CObject::DIM_3D, PRIORITY),
	m_sPrevStagePath	(pPrevPath)	// 遷移元ステージパス
{

}

//============================================================
//	デストラクタ
//============================================================
CTileSpawn::~CTileSpawn()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTileSpawn::Init()
{
	// オブジェクト3Dの初期化
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// テクスチャを割当
	BindTexture(TEXTURE_FILE);

	// 大きさを設定
	SetVec3Size(VECTOR3(SIZE_TILE, SIZE_TILE, 0.0f));

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CTileSpawn::Uninit()
{
	// オブジェクト3Dの終了
	CObject3D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CTileSpawn::Update(const float fDeltaTime)
{
	// オブジェクト3Dの更新
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CTileSpawn::Draw(CShader* pShader)
{
	// オブジェクト3Dの描画
	CObject3D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CTileSpawn* CTileSpawn::Create(const char* pPrevPath, const VECTOR3& rPos)
{
	// 出現タイルの生成
	CTileSpawn* pTileSpawn = new CTileSpawn(pPrevPath);
	if (pTileSpawn == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 出現タイルの初期化
		if (FAILED(pTileSpawn->Init()))
		{ // 初期化に失敗した場合

			// 出現タイルの破棄
			SAFE_DELETE(pTileSpawn);
			return nullptr;
		}

		// 位置を設定
		pTileSpawn->SetVec3Position(rPos);

		// 確保したアドレスを返す
		return pTileSpawn;
	}
}
