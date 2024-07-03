//============================================================
//
//	判定タイル処理 [collTile.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "collTile.h"

// TODO
#include "manager.h"
#include "collision.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// テクスチャファイル
	{
		"data\\TEXTURE\\DEBUG\\collision000.png",	// 矩形
		"data\\TEXTURE\\DEBUG\\collision001.png",	// 三角
	};
	const int PRIORITY = 3;	// 判定タイルの優先順位
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CCollTile::TYPE_MAX, "ERROR : Type Count Mismatch");

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CListManager<CCollTile> *CCollTile::m_pList = nullptr;	// オブジェクトリスト

//************************************************************
//	子クラス [CCollTile] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CCollTile::CCollTile() : CObject3D(CObject::LABEL_TILE, CObject::DIM_3D, PRIORITY),
	m_type	((EType)0)	// 種類
{

}

//============================================================
//	デストラクタ
//============================================================
CCollTile::~CCollTile()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CCollTile::Init(void)
{
	// メンバ変数を初期化
	m_type = TYPE_TRIANGLE;	// 種類	// TODO

	// オブジェクト3Dの初期化
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 大きさを設定
	SetVec3Sizing(D3DXVECTOR3(SIZE_TILE, SIZE_TILE, 0.0f));

	if (m_pList == nullptr)
	{ // リストマネージャーが存在しない場合

		// リストマネージャーの生成
		m_pList = CListManager<CCollTile>::Create();
		if (m_pList == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}
	}

	// リストに自身のオブジェクトを追加・イテレーターを取得
	m_iterator = m_pList->AddList(this);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CCollTile::Uninit(void)
{
	// リストから自身のオブジェクトを削除
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // オブジェクトが一つもない場合

		// リストマネージャーの破棄
		m_pList->Release(m_pList);
	}

	// オブジェクト3Dの終了
	CObject3D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CCollTile::Update(const float fDeltaTime)
{
	// オブジェクト3Dの更新
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CCollTile::Draw(CShader *pShader)
{
	// オブジェクト3Dの描画
	CObject3D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CCollTile *CCollTile::Create(const EType type, const D3DXVECTOR3& rPos)
{
	// 判定タイルの生成
	CCollTile *pCollTile = new CCollTile;
	if (pCollTile == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 判定タイルの初期化
		if (FAILED(pCollTile->Init()))
		{ // 初期化に失敗した場合

			// 判定タイルの破棄
			SAFE_DELETE(pCollTile);
			return nullptr;
		}

		// 種類を設定
		pCollTile->SetType(type);

		// 位置を設定
		pCollTile->SetVec3Position(rPos);

		// 確保したアドレスを返す
		return pCollTile;
	}
}

//============================================================
//	リスト取得処理
//============================================================
CListManager<CCollTile> *CCollTile::GetList(void)
{
	// オブジェクトリストを返す
	return m_pList;
}

//============================================================
//	判定タイルとの当たり判定処理
//============================================================
bool CCollTile::CollisionTile
(
	D3DXVECTOR3& rPos,			// 位置
	const D3DXVECTOR3& rPosOld,	// 過去位置
	const D3DXVECTOR3& rSize	// 大きさ
)
{
	// 判定タイルがない場合抜ける
	if (m_pList == nullptr) { return false; }

	std::list<CCollTile*> list = m_pList->GetList();	// 内部リスト
	for (const auto& rList : list)
	{ // 要素数分繰り返す

#if 1
		D3DXVECTOR3 posTile = rList->GetVec3Position();
		D3DXVECTOR3 sizeTile = (rList->GetVec3Sizing() + D3DXVECTOR3(0.0f, 0.0f, 50.0f)) * 0.5f;

		bool bHit = collision::ResponseBox3D
		( // 引数
			rPos,
			rPosOld,
			posTile,
			rSize,
			rSize,
			sizeTile,
			sizeTile
		);
		if (bHit)
		{ // 当たっている場合

			GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_CENTER, "[当たってるよ]");
		}
#else

#endif
	}

	return false;
}

//============================================================
//	種類設定処理
//============================================================
void CCollTile::SetType(const EType type)
{
	// 種類を保存
	m_type = type;

	// テクスチャを割当
	BindTexture(TEXTURE_FILE[type]);
}
