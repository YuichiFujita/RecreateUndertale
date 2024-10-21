//============================================================
//
//	フレーム2D処理 [frame2D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2D.h"
#include "object2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const COLOR COL_FRAME[] = { color::White(), color::Black() };	// フレーム色
	const VECTOR3 BORD_THICK = VECTOR3(18.0f, 18.0f, 0.0f);	// 縁取り太さ
	const int PRIORITY = 6;	// フレーム2Dの優先順位
}

//************************************************************
//	子クラス [CFrame2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2D::CFrame2D() : CObject(LABEL_UI, DIM_2D, PRIORITY),
	m_pos	(VEC3_ZERO),	// 位置
	m_rot	(VEC3_ZERO),	// 向き
	m_size	(VEC3_ZERO)		// 大きさ
{
	// メンバ変数をクリア
	memset(&m_apFrame[0], 0, sizeof(m_apFrame));	// フレーム情報
}

//============================================================
//	デストラクタ
//============================================================
CFrame2D::~CFrame2D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFrame2D::Init()
{
	// メンバ変数を初期化
	memset(&m_apFrame[0], 0, sizeof(m_apFrame));	// フレーム情報
	m_pos	= VEC3_ZERO;	// 位置
	m_rot	= VEC3_ZERO;	// 向き
	m_size	= VEC3_ZERO;	// 大きさ

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの生成
		m_apFrame[i] = CObject2D::Create(VEC3_ZERO);
		if (m_apFrame[i] == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// 色を設定
		m_apFrame[i]->SetColor(COL_FRAME[i]);

		// 自動更新・自動描画をOFFにする
		m_apFrame[i]->SetEnableUpdate(false);
		m_apFrame[i]->SetEnableDraw(false);
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrame2D::Uninit()
{
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの終了
		SAFE_UNINIT(m_apFrame[i]);
	}

	// オブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CFrame2D::Update(const float fDeltaTime)
{
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの更新
		m_apFrame[i]->Update(fDeltaTime);
	}
}

//============================================================
//	描画処理
//============================================================
void CFrame2D::Draw(CShader* pShader)
{
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの描画
		m_apFrame[i]->Draw(pShader);
	}
}

//============================================================
//	優先順位の設定処理
//============================================================
void CFrame2D::SetPriority(const int nPriority)
{
	// 引数の優先順位を設定
	CObject::SetPriority(nPriority);	// 自身
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		m_apFrame[i]->SetPriority(nPriority);	// フレーム
	}
}

//============================================================
//	位置の設定処理
//============================================================
void CFrame2D::SetVec3Position(const VECTOR3& rPos)
{
	// 引数の位置を設定
	m_pos = rPos;
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		m_apFrame[i]->SetVec3Position(rPos);	// フレーム
	}
}

//============================================================
//	向きの設定処理
//============================================================
void CFrame2D::SetVec3Rotation(const VECTOR3& rRot)
{
	// 引数の向きを設定
	m_rot = rRot;

	// 向きの正規化
	useful::NormalizeRot(m_rot);

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		m_apFrame[i]->SetVec3Rotation(rRot);	// フレーム
	}
}

//============================================================
//	大きさの設定処理
//============================================================
void CFrame2D::SetVec3Size(const VECTOR3& rSize)
{
	// 引数の大きさを設定
	m_size = rSize;
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		float fCalcScale = (-1.0f * (i - 1));	// 大きさ調整値
		m_apFrame[i]->SetVec3Size(rSize + fCalcScale * BORD_THICK);	// フレーム
	}
}

//============================================================
//	生成処理
//============================================================
CFrame2D* CFrame2D::Create
(
	const VECTOR3& rPos,	// 位置
	const VECTOR3& rRot,	// 向き
	const VECTOR3& rSize	// 大きさ
)
{
	// フレーム2Dの生成
	CFrame2D* pFrame2D = new CFrame2D;
	if (pFrame2D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// フレーム2Dの初期化
		if (FAILED(pFrame2D->Init()))
		{ // 初期化に失敗した場合

			// フレーム2Dの破棄
			SAFE_DELETE(pFrame2D);
			return nullptr;
		}

		// 位置を設定
		pFrame2D->SetVec3Position(rPos);

		// 向きを設定
		pFrame2D->SetVec3Rotation(rRot);

		// 大きさを設定
		pFrame2D->SetVec3Size(rSize);

		// 確保したアドレスを返す
		return pFrame2D;
	}
}
