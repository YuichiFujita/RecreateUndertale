//============================================================
//
//	アニメーション3D処理 [anim3D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "anim3D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const POSGRID2 INIT_PTRN = GRID2_ONE;	// テクスチャ分割数の初期値
}

//************************************************************
//	子クラス [CAnim3D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CAnim3D::CAnim3D(const CObject::ELabel label, const EDim dimension, const int nPriority) : CObject3D(label, dimension, nPriority),
	m_funcNext	(nullptr),		// パターン変更関数ポインタ
	m_ptrn		(GRID2_ZERO),	// テクスチャ分割数
	m_fNextTime	(0.0f),			// パターン変更時間
	m_fCurTime	(0.0f),			// 現在の待機時間
	m_nCurPtrn	(0),			// 現在のパターン
	m_nMaxPtrn	(0),			// パターンの総数
	m_nNumLoop	(0),			// パターン繰り返し数
	m_bPlay		(false),		// 再生状況
	m_bPlayBack	(false)			// 逆再生状況
{

}

//============================================================
//	デストラクタ
//============================================================
CAnim3D::~CAnim3D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CAnim3D::Init(void)
{
	// メンバ変数を初期化
	m_funcNext	= nullptr;		// パターン変更関数ポインタ
	m_ptrn		= INIT_PTRN;	// テクスチャ分割数
	m_fNextTime	= 0.0f;			// パターン変更時間
	m_fCurTime	= 0.0f;			// 現在の待機時間
	m_nCurPtrn	= 0;			// 現在のパターン
	m_nMaxPtrn	= 0;			// パターン総数
	m_nNumLoop	= 0;			// パターン繰り返し数
	m_bPlay		= true;			// 再生状況
	m_bPlayBack	= false;		// 逆再生状況

	// 通常再生を設定
	SetEnablePlayBack(false);

	// オブジェクト3Dの初期化
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CAnim3D::Uninit(void)
{
	// オブジェクト3Dの終了
	CObject3D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CAnim3D::Update(const float fDeltaTime)
{
	// 停止中の場合抜ける
	if (!m_bPlay) { return; }

	// 現在の待機時間を加算
	m_fCurTime += fDeltaTime;
	while (m_fCurTime >= m_fNextTime)
	{ // 待機し終わった場合

		// 現在の待機時間から今回の待機時間を減算
		m_fCurTime -= m_fNextTime;

		// 現在のパターンを変更
		assert(m_funcNext != nullptr);
		m_funcNext();

		if (m_nCurPtrn == 0)
		{ // パターン数が一枚目の場合

			// 繰り返し数を加算
			m_nNumLoop++;
		}
	}

	// オブジェクト3Dの更新
	CObject3D::Update(fDeltaTime);

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	描画処理
//============================================================
void CAnim3D::Draw(CShader *pShader)
{
	// オブジェクト3Dの描画
	CObject3D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CAnim3D *CAnim3D::Create
(
	const POSGRID2& rPtrn,		// テクスチャ分割数
	const D3DXVECTOR3& rPos,	// 位置
	const float fNextTime,		// パターン変更時間
	const D3DXVECTOR3& rSize,	// 大きさ
	const D3DXVECTOR3& rRot,	// 向き
	const D3DXCOLOR& rCol		// 色
)
{
	// アニメーション3Dの生成
	CAnim3D *pAnim3D = new CAnim3D;
	if (pAnim3D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// アニメーション3Dの初期化
		if (FAILED(pAnim3D->Init()))
		{ // 初期化に失敗した場合

			// アニメーション3Dの破棄
			SAFE_DELETE(pAnim3D);
			return nullptr;
		}

		// テクスチャ分割数を設定
		pAnim3D->SetTexPtrn(rPtrn);

		// パターン変更時間を設定
		pAnim3D->SetNextTime(fNextTime);

		// 位置を設定
		pAnim3D->SetVec3Position(rPos);

		// 向きを設定
		pAnim3D->SetVec3Rotation(rRot);

		// 大きさを設定
		pAnim3D->SetVec3Sizing(rSize);

		// 色を設定
		pAnim3D->SetColor(rCol);

		// 確保したアドレスを返す
		return pAnim3D;
	}
}

//============================================================
//	位置の設定処理
//============================================================
void CAnim3D::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// 位置の設定
	CObject3D::SetVec3Position(rPos);

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	向きの設定処理
//============================================================
void CAnim3D::SetVec3Rotation(const D3DXVECTOR3& rRot)
{
	// 向きの設定
	CObject3D::SetVec3Rotation(rRot);

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	大きさの設定処理
//============================================================
void CAnim3D::SetVec3Sizing(const D3DXVECTOR3& rSize)
{
	// 大きさの設定
	CObject3D::SetVec3Sizing(rSize);

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	色の設定処理
//============================================================
void CAnim3D::SetColor(const D3DXCOLOR& rCol)
{
	// 色の設定
	CObject3D::SetColor(rCol);

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	現在パターンの設定処理
//============================================================
void CAnim3D::SetCurPtrn(const int nPtrn)
{
	// 引数のパターン数を代入
	m_nCurPtrn = nPtrn;

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	テクスチャ分割数の設定処理
//============================================================
void CAnim3D::SetTexPtrn(const POSGRID2& rPtrn)
{
	// 引数のテクスチャ分割数を設定
	m_ptrn = rPtrn;

	// パターン総数を設定
	SetMaxPtrn(m_ptrn.x * m_ptrn.y);
}

//============================================================
//	テクスチャ横分割数の設定処理
//============================================================
void CAnim3D::SetTexPtrnWidth(const int nTexPtrnW)
{
	// 引数のテクスチャ横分割数を設定
	m_ptrn.x = nTexPtrnW;

	// パターン総数を設定
	SetMaxPtrn(m_ptrn.x * m_ptrn.y);
}

//============================================================
//	テクスチャ縦分割数の設定処理
//============================================================
void CAnim3D::SetTexPtrnHeight(const int nTexPtrnH)
{
	// 引数のテクスチャ縦分割数を設定
	m_ptrn.y = nTexPtrnH;

	// パターン総数を設定
	SetMaxPtrn(m_ptrn.x * m_ptrn.y);
}

//============================================================
//	パターン変更時間の設定処理
//============================================================
void CAnim3D::SetNextTime(const float fNextTime)
{
	// 変更時間がプラスではない場合抜ける
	if (fNextTime <= 0.0f) { assert(false); return; }

	// 引数のパターン変更時間を設定
	m_fNextTime = fNextTime;
}

//============================================================
//	再生フラグの設定処理
//============================================================
void CAnim3D::SetEnablePlay(const bool bPlay)
{
	// 引数の再生状況を設定
	m_bPlay = bPlay;

	// 停止した場合にパターン繰り返し数を初期化
	if (!m_bPlay) { m_nNumLoop = 0; }
}

//============================================================
//	逆再生フラグの設定処理
//============================================================
void CAnim3D::SetEnablePlayBack(const bool bPlayBack)
{
	// 引数の逆再生状況を設定
	m_bPlayBack = bPlayBack;

	if (!m_bPlayBack)
	{ // 通常再生の場合

		// パターン加算関数を設定
		m_funcNext = std::bind(&CAnim3D::NextPtrn, this);
	}
	else
	{ // 逆再生の場合

		// パターン減算関数を設定
		m_funcNext = std::bind(&CAnim3D::BackPtrn, this);
	}
}

//============================================================
//	パターン総数の設定処理
//============================================================
void CAnim3D::SetMaxPtrn(const int nMaxPtrn)
{
	// 引数のパターンの総数を代入
	m_nMaxPtrn = nMaxPtrn;

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	パターン加算処理
//============================================================
void CAnim3D::NextPtrn(void)
{
	// パターンを加算
	m_nCurPtrn = (m_nCurPtrn + 1) % m_nMaxPtrn;
}

//============================================================
//	パターン減算処理
//============================================================
void CAnim3D::BackPtrn(void)
{
	// パターンを減算
	m_nCurPtrn = (m_nCurPtrn + (m_nMaxPtrn - 1)) % m_nMaxPtrn;
}
