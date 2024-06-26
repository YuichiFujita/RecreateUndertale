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
//	子クラス [CAnim3D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CAnim3D::CAnim3D(const CObject::ELabel label, const EDim dimension, const int nPriority) : CObject3D(label, dimension, nPriority),
	m_nCounter		(0),	// アニメーションカウンター
	m_nCntChange	(0),	// パターン変更カウント
	m_nPattern		(0),	// アニメーションパターン
	m_nMaxPtrn		(0),	// パターンの総数
	m_nWidthPtrn	(0),	// テクスチャの横の分割数
	m_nHeightPtrn	(0),	// テクスチャの縦の分割数
	m_nNumLoop		(0),	// パターン繰り返し数
	m_bStop		(false),	// 停止状況
	m_bPlayBack	(false)		// 逆再生状況
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
	m_nCounter		= 0;	// アニメーションカウンター
	m_nCntChange	= 0;	// パターン変更カウント
	m_nPattern		= 0;	// アニメーションパターン
	m_nMaxPtrn		= 0;	// パターンの総数
	m_nWidthPtrn	= 1;	// テクスチャの横の分割数
	m_nHeightPtrn	= 1;	// テクスチャの縦の分割数
	m_nNumLoop		= 0;	// パターン繰り返し数
	m_bStop		= false;	// 停止状況
	m_bPlayBack	= false;	// 逆再生状況

	// オブジェクト3Dの初期化
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);

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
	if (m_bStop) { return; }

	if (m_nCntChange > 0)
	{ // 変更カウントが 0より大きい場合

		// カウンターを加算
		m_nCounter++;

		if (m_nCounter % m_nCntChange == 0)
		{ // カウンターが変更カウントになった場合

			// カウンターを初期化
			m_nCounter = 0;

			if (!m_bPlayBack)
			{ // 通常再生の場合

				// パターンを加算
				m_nPattern = (m_nPattern + 1) % m_nMaxPtrn;
			}
			else
			{ // 逆再生の場合

				// パターンを減算
				m_nPattern = (m_nPattern + (m_nMaxPtrn - 1)) % m_nMaxPtrn;
			}

			if (m_nPattern == 0)
			{ // パターン数が一枚目の場合

				// 繰り返し数を加算
				m_nNumLoop++;
			}
		}
	}

	// オブジェクト3Dの更新
	CObject3D::Update(fDeltaTime);

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
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
CAnim3D *CAnim3D::Create(const int nWidthPtrn, const int nHeightPtrn, const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize, const D3DXVECTOR3& rRot, const D3DXCOLOR& rCol)
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

		// テクスチャ横分割数を設定
		pAnim3D->SetWidthPattern(nWidthPtrn);

		// テクスチャ縦分割数を設定
		pAnim3D->SetHeightPattern(nHeightPtrn);

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
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	向きの設定処理
//============================================================
void CAnim3D::SetVec3Rotation(const D3DXVECTOR3& rRot)
{
	// 向きの設定
	CObject3D::SetVec3Rotation(rRot);

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	大きさの設定処理
//============================================================
void CAnim3D::SetVec3Sizing(const D3DXVECTOR3& rSize)
{
	// 大きさの設定
	CObject3D::SetVec3Sizing(rSize);

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	色の設定処理
//============================================================
void CAnim3D::SetColor(const D3DXCOLOR& rCol)
{
	// 色の設定
	CObject3D::SetColor(rCol);

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	パターンの設定処理
//============================================================
void CAnim3D::SetPattern(const int nPattern)
{
	// 引数のパターン数を代入
	m_nPattern = nPattern;

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	パターンの総数の設定処理
//============================================================
void CAnim3D::SetMaxPattern(const int nMaxPtrn)
{
	// 引数のパターンの総数を代入
	m_nMaxPtrn = nMaxPtrn;

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	テクスチャの横分割数の設定処理
//============================================================
void CAnim3D::SetWidthPattern(const int nWidthPtrn)
{
	// 引数のテクスチャ横分割数を設定
	m_nWidthPtrn = nWidthPtrn;

	// パターンの総数を設定
	m_nMaxPtrn = m_nWidthPtrn * m_nHeightPtrn;

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	テクスチャの縦分割数の設定処理
//============================================================
void CAnim3D::SetHeightPattern(const int nHeightPtrn)
{
	// 引数のテクスチャ縦分割数を設定
	m_nHeightPtrn = nHeightPtrn;

	// パターンの総数を設定
	m_nMaxPtrn = m_nWidthPtrn * m_nHeightPtrn;

	// アニメーションのテクスチャ座標の設定
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	カウンターの設定処理
//============================================================
void CAnim3D::SetCounter(const int nCntChange)
{
	// 引数のパターン変更カウントを代入
	m_nCntChange = nCntChange;
}

//============================================================
//	停止状況の設定処理
//============================================================
void CAnim3D::SetEnableStop(const bool bStop)
{
	// 引数の停止状況を代入
	m_bStop = bStop;

	if (m_bStop)
	{ // 停止された場合

		// 繰り返し数を初期化
		m_nNumLoop = 0;
	}
}

//============================================================
//	逆再生状況の設定処理
//============================================================
void CAnim3D::SetEnablePlayBack(const bool bPlayBack)
{
	// 引数の逆再生状況を代入
	m_bPlayBack = bPlayBack;
}
