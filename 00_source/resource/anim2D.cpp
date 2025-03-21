//============================================================
//
//	アニメーション2D処理 [anim2D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "anim2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const POSGRID2 INIT_PTRN = GRID2_ONE;	// テクスチャ分割数の初期値
}

//************************************************************
//	子クラス [CAnim2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CAnim2D::CAnim2D(const CObject::ELabel label, const EDim dimension, const int nPriority) : CObject2D(label, dimension, nPriority),
	m_funcPattern	(nullptr),		// パターン変更関数ポインタ
	m_state			(STATE_PLAY),	// 状態
	m_ptrn			(GRID2_ZERO),	// テクスチャ分割数
	m_pNextTime		(nullptr),		// パターン変更時間
	m_fCurTime		(0.0f),			// 現在の待機時間
	m_fCurWholeTime	(0.0f),			// 現在の全体時間
	m_fMaxWholeTime	(0.0f),			// 総全体時間
	m_fCurLoopTime	(0.0f),			// 現在のループ待機時間
	m_fLoopWaitTime	(0.0f),			// ループ待機時間
	m_nCurPtrn		(0),			// 現在のパターン
	m_nMaxPtrn		(0),			// パターンの総数
	m_nNumLoop		(0),			// パターン繰り返し数
	m_bPlay			(false),		// 再生フラグ
	m_bPlayBack		(false),		// 逆再生フラグ
	m_bLoop			(false),		// ループフラグ
	m_bFinish		(false)			// 終了フラグ
{

}

//============================================================
//	デストラクタ
//============================================================
CAnim2D::~CAnim2D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CAnim2D::Init()
{
	// メンバ変数を初期化
	m_funcPattern	= nullptr;		// パターン変更関数ポインタ
	m_state			= STATE_PLAY;	// 状態
	m_ptrn			= GRID2_ZERO;	// テクスチャ分割数
	m_pNextTime		= nullptr;		// パターン変更時間
	m_fCurTime		= 0.0f;			// 現在の待機時間
	m_fCurWholeTime	= 0.0f;			// 現在の全体時間
	m_fMaxWholeTime	= 0.0f;			// 総全体時間
	m_fCurLoopTime	= 0.0f;			// 現在のループ待機時間
	m_fLoopWaitTime = 0.0f;			// ループ待機時間
	m_nCurPtrn		= 0;			// 現在のパターン
	m_nMaxPtrn		= 0;			// パターン総数
	m_nNumLoop		= 0;			// パターン繰り返し数
	m_bPlay			= true;			// 再生フラグ
	m_bPlayBack		= false;		// 逆再生フラグ
	m_bLoop			= true;			// ループフラグ
	m_bFinish		= false;		// 終了フラグ

	// テクスチャ分割数を初期化
	SetTexPtrn(INIT_PTRN);

	// 通常再生を初期化
	SetEnablePlayBack(false);

	// オブジェクト2Dの初期化
	if (FAILED(CObject2D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// アニメーションのテクスチャ座標の設定
	CObject2D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CAnim2D::Uninit()
{
	// パターン変更時間の破棄
	SAFE_DEL_ARRAY(m_pNextTime);

	// オブジェクト2Dの終了
	CObject2D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CAnim2D::Update(const float fDeltaTime)
{
	// 停止中の場合抜ける
	if (!m_bPlay) { return; }

	switch (m_state)
	{ // 状態ごとの処理
	case STATE_PLAY:

		// パターンの更新
		assert(m_funcPattern != nullptr);
		m_funcPattern(fDeltaTime);
		break;

	case STATE_WAIT:

		// 待機時間の更新
		UpdateWait(fDeltaTime);
		break;

	default:
		assert(false);
		break;
	}

	// オブジェクト2Dの更新
	CObject2D::Update(fDeltaTime);

	// アニメーションのテクスチャ座標の設定
	CObject2D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	描画処理
//============================================================
void CAnim2D::Draw(CShader* pShader)
{
	// オブジェクト2Dの描画
	CObject2D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CAnim2D* CAnim2D::Create
(
	const POSGRID2& rPtrn,	// テクスチャ分割数
	const VECTOR3& rPos,	// 位置
	const float fNextTime,	// パターン変更時間
	const VECTOR3& rSize,	// 大きさ
	const VECTOR3& rRot,	// 向き
	const COLOR& rCol		// 色
)
{
	// アニメーション2Dの生成
	CAnim2D* pAnim2D = new CAnim2D;
	if (pAnim2D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// アニメーション2Dの初期化
		if (FAILED(pAnim2D->Init()))
		{ // 初期化に失敗した場合

			// アニメーション2Dの破棄
			SAFE_DELETE(pAnim2D);
			return nullptr;
		}

		// テクスチャ分割数を設定
		pAnim2D->SetTexPtrn(rPtrn);

		// パターン変更時間を設定
		pAnim2D->SetNextTime(fNextTime);

		// 位置を設定
		pAnim2D->SetVec3Position(rPos);

		// 向きを設定
		pAnim2D->SetVec3Rotation(rRot);

		// 大きさを設定
		pAnim2D->SetVec3Size(rSize);

		// 色を設定
		pAnim2D->SetColor(rCol);

		// 確保したアドレスを返す
		return pAnim2D;
	}
}

//============================================================
//	位置の設定処理
//============================================================
void CAnim2D::SetVec3Position(const VECTOR3& rPos)
{
	// 位置の設定
	CObject2D::SetVec3Position(rPos);

	// アニメーションのテクスチャ座標の設定
	CObject2D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	向きの設定処理
//============================================================
void CAnim2D::SetVec3Rotation(const VECTOR3& rRot)
{
	// 向きの設定
	CObject2D::SetVec3Rotation(rRot);

	// アニメーションのテクスチャ座標の設定
	CObject2D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	大きさの設定処理
//============================================================
void CAnim2D::SetVec3Size(const VECTOR3& rSize)
{
	// 大きさの設定
	CObject2D::SetVec3Size(rSize);

	// アニメーションのテクスチャ座標の設定
	CObject2D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	透明度の設定処理
//============================================================
void CAnim2D::SetAlpha(const float fAlpha)
{
	// 透明度の設定
	CObject2D::SetAlpha(fAlpha);

	// アニメーションのテクスチャ座標の設定
	CObject2D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	色の設定処理
//============================================================
void CAnim2D::SetColor(const COLOR& rCol)
{
	// 色の設定
	CObject2D::SetColor(rCol);

	// アニメーションのテクスチャ座標の設定
	CObject2D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	現在パターンの設定処理
//============================================================
void CAnim2D::SetCurPtrn(const int nPtrn)
{
	// 引数のパターン数を設定
	m_nCurPtrn = nPtrn;

	// 終了フラグをOFFにする
	m_bFinish = false;

	// 全体時間の初期化
	m_fCurWholeTime = 0.0f;

	// 全体時間をパターンの開始時間に設定
	int nAddTime = (!m_bPlayBack) ? 0 : 1;	// 逆再生の場合は現在パターンの待機時間も含む
	int nLoop = m_nCurPtrn + nAddTime;		// 繰り返し数を求める
	for (int i = 0; i < nLoop; i++)
	{ // 開始パターンまで繰り返す

		// 待機時間を加算
		m_fCurWholeTime += m_pNextTime[i];
	}

	// アニメーションのテクスチャ座標の設定
	CObject2D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	テクスチャ分割数の設定処理
//============================================================
void CAnim2D::SetTexPtrn(const POSGRID2& rPtrn)
{
	// 引数のテクスチャ分割数を設定
	m_ptrn = rPtrn;

	// パターン総数を設定
	SetMaxPtrn(m_ptrn.x * m_ptrn.y);
}

//============================================================
//	テクスチャ横分割数の設定処理
//============================================================
void CAnim2D::SetTexPtrnWidth(const int nTexPtrnW)
{
	// 引数のテクスチャ横分割数を設定
	m_ptrn.x = nTexPtrnW;

	// パターン総数を設定
	SetMaxPtrn(m_ptrn.x * m_ptrn.y);
}

//============================================================
//	テクスチャ縦分割数の設定処理
//============================================================
void CAnim2D::SetTexPtrnHeight(const int nTexPtrnH)
{
	// 引数のテクスチャ縦分割数を設定
	m_ptrn.y = nTexPtrnH;

	// パターン総数を設定
	SetMaxPtrn(m_ptrn.x * m_ptrn.y);
}

//============================================================
//	再生フラグの設定処理
//============================================================
void CAnim2D::SetEnablePlay(const bool bPlay)
{
	// 停止した場合に繰り返し数を初期化
	if (!bPlay) { m_nNumLoop = 0; }

	// 引数の再生状況を設定
	m_bPlay = bPlay;
}

//============================================================
//	逆再生フラグの設定処理
//============================================================
void CAnim2D::SetEnablePlayBack(const bool bPlayBack)
{
	// 再生/逆再生が反転した場合に繰り返し数と終了フラグを初期化
	if (m_bPlayBack != bPlayBack) { m_nNumLoop = 0; m_bFinish = false; }

	// 引数の逆再生状況を設定
	m_bPlayBack = bPlayBack;

	if (!m_bPlayBack)
	{ // 通常再生の場合

		// パターン加算関数を設定
		m_funcPattern = std::bind(&CAnim2D::NextPtrn, this, std::placeholders::_1);
	}
	else
	{ // 逆再生の場合

		// パターン減算関数を設定
		m_funcPattern = std::bind(&CAnim2D::BackPtrn, this, std::placeholders::_1);
	}
}

//============================================================
//	ループフラグの設定処理
//============================================================
void CAnim2D::SetEnableLoop(const bool bLoop)
{
	// ループする場合終了フラグを初期化
	if (bLoop) { m_bFinish = false; }

	// 引数のループ状況を設定
	m_bLoop = bLoop;
}

//============================================================
//	ループ待機時間の設定処理
//============================================================
void CAnim2D::SetLoopWaitTime(const float fWaitTime)
{
	// 引数の待機時間を設定
	m_fLoopWaitTime = fWaitTime;
}

//============================================================
//	現在パターンの初期化処理
//============================================================
void CAnim2D::ResetCurPtrn(const bool bLoopWait)
{
	// ループ待機フラグをもとに状態を設定
	m_state = (bLoopWait) ? STATE_WAIT : STATE_PLAY;

	// 終了フラグをOFFにする
	m_bFinish = false;

	if (!m_bPlayBack)
	{ // 通常再生の場合

		// 開始パターンの初期化
		m_nCurPtrn = 0;

		// 待機時間の初期化
		m_fCurTime = 0.0f;
		m_fCurWholeTime = 0.0f;
	}
	else
	{ // 逆再生の場合

		// 開始パターンの初期化
		m_nCurPtrn = m_nMaxPtrn - 1;

		// 待機時間の初期化
		m_fCurTime = m_pNextTime[m_nCurPtrn];
		m_fCurWholeTime = m_fMaxWholeTime;
	}
}

//============================================================
//	パターン変更時間の設定処理 (パターン指定)
//============================================================
void CAnim2D::SetNextTime(const int nPtrnIdx, const float fNextTime)
{
	// パターンインデックスが範囲外の場合抜ける
	if (nPtrnIdx <= NONE_IDX || nPtrnIdx >= m_nMaxPtrn) { assert(false); return; }

	// 変更時間がプラスではない場合抜ける
	if (fNextTime <= 0.0f) { assert(false); return; }

	// 変更前のパターン変更時間を保存
	float fOldNextTime = m_pNextTime[nPtrnIdx];

	// 引数のパターン変更時間を設定
	m_pNextTime[nPtrnIdx] = fNextTime;

	// 総全体時間を変更
	m_fMaxWholeTime -= fOldNextTime;
	m_fMaxWholeTime += fNextTime;
}

//============================================================
//	パターン変更時間の設定処理 (全パターン)
//============================================================
void CAnim2D::SetNextTime(const float fNextTime)
{
	// 変更時間がプラスではない場合抜ける
	if (fNextTime <= 0.0f) { assert(false); return; }

	for (int i = 0; i < m_nMaxPtrn; i++)
	{ // パターンの総数分繰り返す

		// 引数のパターン変更時間を設定
		m_pNextTime[i] = fNextTime;
	}

	// 総全体時間を変更
	m_fMaxWholeTime = fNextTime * (float)m_nMaxPtrn;
}

//============================================================
//	パターン総数の設定処理
//============================================================
HRESULT CAnim2D::SetMaxPtrn(const int nMaxPtrn)
{
	// 引数のパターンの総数を設定
	m_nMaxPtrn = nMaxPtrn;

	// パターン変更時間の破棄
	SAFE_DEL_ARRAY(m_pNextTime);

	// パターン変更時間の再生成
	m_pNextTime = new float[m_nMaxPtrn];
	if (m_pNextTime == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// パターン変更時間を初期化
	SetNextTime(DEF_NEXT);

	// アニメーションのテクスチャ座標の設定
	CObject2D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);

	return S_OK;
}

//============================================================
//	パターン加算処理
//============================================================
void CAnim2D::NextPtrn(const float fDeltaTime)
{
	// アニメーションが終了している場合抜ける
	if (m_bFinish) { return; }

	// 現在の待機時間を加算
	m_fCurTime += fDeltaTime;
	m_fCurWholeTime += fDeltaTime;

	while (m_fCurTime >= m_pNextTime[m_nCurPtrn])
	{ // 待機し終わった場合

		// 現在の待機時間から今回の待機時間を減算
		m_fCurTime -= m_pNextTime[m_nCurPtrn];

		// パターンを加算
		m_nCurPtrn = (m_nCurPtrn + 1) % m_nMaxPtrn;

		// 先頭パターンではない場合次へ
		if (m_nCurPtrn != 0) { continue; }

		if (m_bLoop)
		{ // ループする場合

			// 繰り返し数を加算
			m_nNumLoop++;

			// 全体時間を初期化
			m_fCurWholeTime = m_fCurTime;	// 余剰分の経過時間を保存

			// ループ後に待機しない場合次へ
			if (m_fLoopWaitTime <= 0.0f) { continue; }

			// 余剰分の経過時間を保存
			m_fCurLoopTime = m_fCurTime;
			if (m_fCurLoopTime < m_fLoopWaitTime)
			{ // 余剰時間が待機時間を超えていない場合

				// 時間を初期化
				m_fCurTime = 0.0f;		// 待機時間
				m_fCurWholeTime = 0.0f;	// 全体時間

				// 待機状態にする
				m_state = STATE_WAIT;
				return;	// 次フレームで待機更新へ
			}
			else
			{ // 余剰時間が待機時間を超えている場合

				// 再生時間にループ待機時間を減算
				m_fCurTime -= m_fLoopWaitTime;		// 待機時間
				m_fCurWholeTime -= m_fLoopWaitTime;	// 全体時間

				// 現在のループ待機時間を初期化
				m_fCurLoopTime = 0.0f;
			}
		}
		else
		{ // ループしない場合

			// パターンを補正
			m_nCurPtrn = m_nMaxPtrn - 1;

			// 時間を初期化
			m_fCurTime = m_pNextTime[m_nCurPtrn];	// 待機時間
			m_fCurWholeTime = m_fMaxWholeTime;		// 全体時間

			// アニメーション終了を保存
			m_bFinish = true;
			return;
		}
	}
}

//============================================================
//	パターン減算処理
//============================================================
void CAnim2D::BackPtrn(const float fDeltaTime)
{
	// アニメーションが終了している場合抜ける
	if (m_bFinish) { return; }

	// 現在の待機時間を減算
	m_fCurTime -= fDeltaTime;
	m_fCurWholeTime -= fDeltaTime;

	while (m_fCurTime <= 0.0f)
	{ // 待機し終わった場合

		int nOldPtrn = m_nCurPtrn;		// 前回パターン
		float fOldTime = m_fCurTime;	// 前回時間

		// 現在の待機時間から今回の待機時間を加算
		m_fCurTime += m_pNextTime[m_nCurPtrn];

		// パターンを減算
		m_nCurPtrn = (m_nCurPtrn + (m_nMaxPtrn - 1)) % m_nMaxPtrn;

		// 最終パターンではない場合次へ
		if (m_nCurPtrn != m_nMaxPtrn - 1) { continue; }

		if (m_bLoop)
		{ // ループする場合

			// 繰り返し数を加算
			m_nNumLoop++;

			// 全体時間を初期化
			m_fCurWholeTime = m_fMaxWholeTime + fOldTime;	// 余剰分の経過時間を保存

			// ループ後に待機しない場合次へ
			if (m_fLoopWaitTime <= 0.0f) { continue; }

			// 余剰分の経過時間を保存
			m_fCurLoopTime = (m_fCurTime - m_pNextTime[nOldPtrn]) * -1.0f;
			if (m_fCurLoopTime < m_fLoopWaitTime)
			{ // 余剰時間が待機時間を超えていない場合

				// 時間を初期化
				m_fCurTime = m_pNextTime[m_nCurPtrn];	// 待機時間
				m_fCurWholeTime = m_fMaxWholeTime;		// 全体時間

				// 待機状態にする
				m_state = STATE_WAIT;
				return;	// 次フレームで待機更新へ
			}
			else
			{ // 余剰時間が待機時間を超えている場合

				// 再生時間にループ待機時間を加算
				m_fCurTime += m_fLoopWaitTime;		// 待機時間
				m_fCurWholeTime += m_fLoopWaitTime;	// 全体時間

				// 現在のループ待機時間を初期化
				m_fCurLoopTime = 0.0f;
			}
		}
		else
		{ // ループしない場合

			// パターンを補正
			m_nCurPtrn = 0;

			// 時間を初期化
			m_fCurTime = 0.0f;		// 待機時間
			m_fCurWholeTime = 0.0f;	// 全体時間

			// アニメーション終了を保存
			m_bFinish = true;
			return;
		}
	}
}

//============================================================
//	待機時間の更新処理
//============================================================
void CAnim2D::UpdateWait(const float fDeltaTime)
{
	// アニメーションが終了している場合抜ける
	if (m_bFinish) { return; }

	// 現在の待機時間を加算
	m_fCurLoopTime += fDeltaTime;
	if (m_fCurLoopTime >= m_fLoopWaitTime)
	{ // 待機終了した場合

		// 再生状態にする
		m_state = STATE_PLAY;

		if (!m_bPlayBack)
		{ // 通常再生の場合

			// 余剰分の経過時間を保存
			m_fCurTime = m_fCurWholeTime = m_fCurLoopTime - m_fLoopWaitTime;
		}
		else
		{ // 逆再生の場合

			// 余剰分の経過時間を保存
			m_fCurTime = m_fCurWholeTime = m_pNextTime[m_nCurPtrn] - (m_fCurLoopTime - m_fLoopWaitTime);
		}

		// 現在のループ待機時間を初期化
		m_fCurLoopTime = 0.0f;
	}
}
