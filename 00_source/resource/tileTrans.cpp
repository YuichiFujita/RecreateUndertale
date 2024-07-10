//============================================================
//
//	遷移タイル処理 [tileTrans.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "tileTrans.h"
#include "collision.h"
#include "sceneGame.h"
#include "stage.h"
#include "objectChara2D.h"

// TODO
#include "manager.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *TEXTURE_FILE = "data\\TEXTURE\\DEBUG\\trans000.png";
	const int PRIORITY = 3;	// 遷移タイルの優先順位
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CListManager<CTileTrans> *CTileTrans::m_pList = nullptr;	// オブジェクトリスト

//************************************************************
//	子クラス [CTileTrans] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTileTrans::CTileTrans(const char *pNextPass) : CObject3D(CObject::LABEL_TILE, CObject::DIM_3D, PRIORITY),
	m_sNextStagePass	(pNextPass)	// 遷移先ステージパス
{

}

//============================================================
//	デストラクタ
//============================================================
CTileTrans::~CTileTrans()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTileTrans::Init(void)
{
	// オブジェクト3Dの初期化
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを割当
	BindTexture(TEXTURE_FILE);

	// 大きさを設定
	SetVec3Sizing(D3DXVECTOR3(SIZE_TILE, SIZE_TILE, 0.0f));

	if (m_pList == nullptr)
	{ // リストマネージャーが存在しない場合

		// リストマネージャーの生成
		m_pList = CListManager<CTileTrans>::Create();
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
void CTileTrans::Uninit(void)
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
void CTileTrans::Update(const float fDeltaTime)
{
	// オブジェクト3Dの更新
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CTileTrans::Draw(CShader *pShader)
{
	// オブジェクト3Dの描画
	CObject3D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CTileTrans *CTileTrans::Create(const char *pNextPass, const D3DXVECTOR3& rPos)
{
	// 遷移タイルの生成
	CTileTrans *pTileTrans = new CTileTrans(pNextPass);
	if (pTileTrans == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 遷移タイルの初期化
		if (FAILED(pTileTrans->Init()))
		{ // 初期化に失敗した場合

			// 遷移タイルの破棄
			SAFE_DELETE(pTileTrans);
			return nullptr;
		}

		// 位置を設定
		pTileTrans->SetVec3Position(rPos);

		// 確保したアドレスを返す
		return pTileTrans;
	}
}

//============================================================
//	リスト取得処理
//============================================================
CListManager<CTileTrans> *CTileTrans::GetList(void)
{
	// オブジェクトリストを返す
	return m_pList;
}

//============================================================
//	遷移タイルとの当たり判定
//============================================================
bool CTileTrans::CollisionTile
(
	const D3DXVECTOR3& rPos,		// 位置
	const D3DXVECTOR3& rRot,		// 向き
	const CObjectChara2D *pChara2D	// キャラクター2D情報
)
{
	// キャラクター2Dが存在しない場合抜ける
	if (pChara2D == nullptr) { assert(false); return false; }

	// 遷移タイルとの当たり判定
	D3DXVECTOR3 posOffset = pChara2D->CalcCollOffsetPosition(rPos, rRot);	// 判定原点位置
	D3DXVECTOR3 sizeColl  = pChara2D->GetCollSizing() * 0.5f;				// 判定大きさ
	return CollisionTile(posOffset, sizeColl, sizeColl);
}

//============================================================
//	遷移タイルとの当たり判定
//============================================================
bool CTileTrans::CollisionTile
(
	const D3DXVECTOR3& rPos,		// 位置
	const D3DXVECTOR3& rSizeUp,		// 大きさ (右/上/後)
	const D3DXVECTOR3& rSizeDown	// 大きさ (左/下/前)
)
{
	// 遷移タイルがない場合抜ける
	if (m_pList == nullptr) { return false; }

	std::list<CTileTrans*> list = m_pList->GetList();	// 内部リスト
	for (const auto& rList : list)
	{ // 要素数分繰り返す

		D3DXVECTOR3 posTile  = rList->GetVec3Position();		// タイル位置
		D3DXVECTOR3 sizeTile = rList->GetVec3Sizing() * 0.5f;	// タイル大きさ

		// XY平面の矩形の当たり判定
		bool bHit = collision::BoxXY
		( // 引数
			rPos,		// 判定位置
			posTile,	// タイル位置
			rSizeUp,	// 判定大きさ (右/上/後)
			rSizeDown,	// 判定大きさ (左/下/前)
			sizeTile,	// タイル大きさ (右/上/後)
			sizeTile	// タイル大きさ (左/下/前)
		);
		if (bHit)
		{ // 当たっている場合

			// 踏んだタイルのルームパスに遷移する
			//CSceneGame::GetStage()->SetFadeRoom(rList->m_sNextStagePass.c_str());
			GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_CENTER, "[当たってるよ]");	// TODO
			return true;
		}
	}

	return false;
}
