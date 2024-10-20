//============================================================
//
//	判定タイル処理 [tileColl.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "tileColl.h"
#include "collision.h"
#include "objectChara2D.h"

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
static_assert(NUM_ARRAY(TEXTURE_FILE) == CTileColl::TYPE_MAX, "ERROR : Type Count Mismatch");

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CListManager<CTileColl> *CTileColl::m_pList = nullptr;	// オブジェクトリスト

//************************************************************
//	子クラス [CTileColl] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTileColl::CTileColl() : CObject3D(CObject::LABEL_TILE, CObject::DIM_3D, PRIORITY),
	m_type	((EType)0)	// 種類
{

}

//============================================================
//	デストラクタ
//============================================================
CTileColl::~CTileColl()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTileColl::Init(void)
{
	// メンバ変数を初期化
	m_type = TYPE_BOX;	// 種類

	// オブジェクト3Dの初期化
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 大きさを設定
	SetVec3Size(VECTOR3(SIZE_TILE, SIZE_TILE, 0.0f));

	if (m_pList == nullptr)
	{ // リストマネージャーが存在しない場合

		// リストマネージャーの生成
		m_pList = CListManager<CTileColl>::Create();
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
void CTileColl::Uninit(void)
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
void CTileColl::Update(const float fDeltaTime)
{
	// オブジェクト3Dの更新
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CTileColl::Draw(CShader* pShader)
{
	// オブジェクト3Dの描画
	CObject3D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CTileColl *CTileColl::Create(const EType type, const VECTOR3& rPos)
{
	// 判定タイルの生成
	CTileColl *pTileColl = new CTileColl;
	if (pTileColl == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 判定タイルの初期化
		if (FAILED(pTileColl->Init()))
		{ // 初期化に失敗した場合

			// 判定タイルの破棄
			SAFE_DELETE(pTileColl);
			return nullptr;
		}

		// 種類を設定
		pTileColl->SetType(type);

		// 位置を設定
		pTileColl->SetVec3Position(rPos);

		// 確保したアドレスを返す
		return pTileColl;
	}
}

//============================================================
//	リスト取得処理
//============================================================
CListManager<CTileColl> *CTileColl::GetList(void)
{
	// オブジェクトリストを返す
	return m_pList;
}

//============================================================
//	遷移タイルとの当たり判定
//============================================================
void CTileColl::CollisionTile
(
	VECTOR3& rPosCur,				// 現在位置
	const VECTOR3& rPosOld,			// 過去位置
	const VECTOR3& rRot,			// 向き
	const CObjectChara2D *pChara2D	// キャラクター2D情報
)
{
	// キャラクター2Dが存在しない場合抜ける
	if (pChara2D == nullptr) { assert(false); return; }

	VECTOR3 posCur = pChara2D->CalcCollOffsetPosition(rPosCur, rRot);	// 判定原点の現在位置
	VECTOR3 posOld = pChara2D->CalcCollOffsetPosition(rPosOld, rRot);	// 判定原点の過去位置
	VECTOR3 sizeColl = pChara2D->GetCollSize() * 0.5f;					// 判定大きさ

	// 判定原点の現在位置を保存
	VECTOR3 posSave = posCur;

	// 遷移タイルとの当たり判定
	CollisionTile(posCur, posOld, sizeColl, sizeColl);

	// 判定後の補正量を現在位置に適応
	rPosCur -= posSave - posCur;
}

//============================================================
//	遷移タイルとの当たり判定
//============================================================
void CTileColl::CollisionTile
(
	VECTOR3& rPosCur,			// 現在位置
	const VECTOR3& rPosOld,		// 過去位置
	const VECTOR3& rSizeUp,		// 大きさ (右/上/後)
	const VECTOR3& rSizeDown	// 大きさ (左/下/前)
)
{
	// 遷移タイルがない場合抜ける
	if (m_pList == nullptr) { return; }

	std::list<CTileColl*> list = m_pList->GetList();	// 内部リスト
	for (const auto& rList : list)
	{ // 要素数分繰り返す

		VECTOR3 posTile  = rList->GetVec3Position();	// タイル位置
		VECTOR3 sizeTile = rList->GetVec3Size() * 0.5f;	// タイル大きさ

		// XY平面の角柱の衝突判定
		collision::ResponseBoxPillarXY
		( // 引数
			rPosCur,	// 判定現在位置
			rPosOld,	// 判定過去位置
			posTile,	// タイル位置
			rSizeUp,	// 判定大きさ (右/上/後)
			rSizeDown,	// 判定大きさ (左/下/前)
			sizeTile,	// タイル大きさ (右/上/後)
			sizeTile	// タイル大きさ (左/下/前)
		);
	}
}

//============================================================
//	種類設定処理
//============================================================
void CTileColl::SetType(const EType type)
{
	// 種類を保存
	m_type = type;

	// テクスチャを割当
	BindTexture(TEXTURE_FILE[type]);
}
