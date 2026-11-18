//============================================================
//
//	ゲージ2D処理 [gauge2D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "gauge2D.h"
#include "object2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 5;	// ゲージ2Dの優先順位
}

//************************************************************
//	子クラス [CGauge2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CGauge2D::CGauge2D(const float fChangeTime) : CObject(CObject::LABEL_UI, CObject::DIM_2D, PRIORITY),
	m_fChangeTime	(fChangeTime),	// ゲージの変動時間
	m_state			(STATE_NONE),	// 状態
	m_nNum			(0),			// 表示値
	m_nMaxNum		(0),			// 最大値
	m_fInitNum		(0.0f),			// 変動開始時の表示値
	m_fDestNum		(0.0f),			// 変動終了時の表示値
	m_fCurTime		(0.0f)			// 現在の経過時間
{
	// メンバ変数をクリア
	memset(&m_pGauge[0], 0, sizeof(m_pGauge));	// ゲージ情報
}

//============================================================
//	デストラクタ
//============================================================
CGauge2D::~CGauge2D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CGauge2D::Init()
{
	// メンバ変数を初期化
	memset(&m_pGauge[0], 0, sizeof(m_pGauge));	// ゲージ情報
	m_state		= STATE_NONE;	// 状態
	m_nNum		= 0;			// 表示値
	m_nMaxNum	= 0;			// 最大値
	m_fInitNum	= 0.0f;			// 変動開始時の表示値
	m_fDestNum	= 0.0f;			// 変動終了時の表示値
	m_fCurTime	= 0.0f;			// 現在の経過時間

	for (int nCntGauge = 0; nCntGauge < POLYGON_MAX; nCntGauge++)
	{ // 使用する四角形ポリゴン数分繰り返す

		// ゲージの生成
		m_pGauge[nCntGauge] = CObject2D::Create
		(
			VEC3_ZERO,				// 位置
			VEC3_ZERO,				// 大きさ
			VEC3_ZERO,				// 向き
			color::White(),			// 色
			EAlignX::XALIGN_LEFT,	// 横配置
			EAlignY::YALIGN_CENTER	// 縦配置
		);
		if (m_pGauge[nCntGauge] == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}

		// 自動更新・自動描画をOFFにする
		m_pGauge[nCntGauge]->SetEnableUpdate(false);
		m_pGauge[nCntGauge]->SetEnableDraw(false);
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CGauge2D::Uninit()
{
	for (int nCntGauge = 0; nCntGauge < POLYGON_MAX; nCntGauge++)
	{ // 使用する四角形ポリゴン数分繰り返す

		// ゲージの終了
		SAFE_UNINIT(m_pGauge[nCntGauge]);
	}

	// 自身のオブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CGauge2D::Update(const float fDeltaTime)
{
	// ゲージが変動中ではない場合抜ける
	if (m_state != STATE_CHANGE) { return; }

	// ゲージの横幅更新
	if (UpdateGaugeWidthFront(fDeltaTime))
	{ // 変動しきった場合

		// 通常状態にする
		m_state = STATE_NONE;

		// 表ゲージの横幅を補正
		SetGaugeWidthFront(m_fDestNum);

		// 変動時間の初期化
		m_fCurTime = 0.0f;
	}

	for (int nCntGauge = 0; nCntGauge < POLYGON_MAX; nCntGauge++)
	{ // 使用する四角形ポリゴン数分繰り返す

		// ゲージの更新
		m_pGauge[nCntGauge]->Update(fDeltaTime);
	}
}

//============================================================
//	描画処理
//============================================================
void CGauge2D::Draw(CShader* pShader)
{
	for (int nCntGauge = 0; nCntGauge < POLYGON_MAX; nCntGauge++)
	{ // 使用する四角形ポリゴン数分繰り返す

		// ゲージの描画
		m_pGauge[nCntGauge]->Draw(pShader);
	}
}

//============================================================
//	位置の設定処理
//============================================================
void CGauge2D::SetVec3Position(const VECTOR3& rPos)
{
	for (int nCntGauge = 0; nCntGauge < POLYGON_MAX; nCntGauge++)
	{ // 使用する四角形ポリゴン数分繰り返す

		// ゲージの位置を設定
		m_pGauge[nCntGauge]->SetVec3Position(rPos);
	}
}

//============================================================
//	向きの設定処理
//============================================================
void CGauge2D::SetVec3Rotation(const VECTOR3& rRot)
{
	for (int nCntGauge = 0; nCntGauge < POLYGON_MAX; nCntGauge++)
	{ // 使用する四角形ポリゴン数分繰り返す

		// ゲージの向きを設定
		m_pGauge[nCntGauge]->SetVec3Rotation(rRot);
	}
}

//============================================================
//	大きさの設定処理
//============================================================
void CGauge2D::SetVec3Size(const VECTOR3& rSize)
{
	for (int nCntGauge = 0; nCntGauge < POLYGON_MAX; nCntGauge++)
	{ // 使用する四角形ポリゴン数分繰り返す

		// ゲージの大きさを設定
		m_pGauge[nCntGauge]->SetVec3Size(rSize);
	}

	// ゲージの設定
	SetNum(m_nNum);
}

//============================================================
//	位置の取得処理
//============================================================
VECTOR3 CGauge2D::GetVec3Position() const
{
	// 裏ゲージの位置を返す
	return m_pGauge[EPolygon::POLYGON_BACK]->GetVec3Position();
}

//============================================================
//	向きの取得処理
//============================================================
VECTOR3 CGauge2D::GetVec3Rotation() const
{
	// 裏ゲージの向きを返す
	return m_pGauge[EPolygon::POLYGON_BACK]->GetVec3Rotation();
}

//============================================================
//	大きさの取得処理
//============================================================
VECTOR3 CGauge2D::GetVec3Size() const
{
	// 裏ゲージの大きさを返す
	return m_pGauge[EPolygon::POLYGON_BACK]->GetVec3Size();
}

//============================================================
//	生成処理
//============================================================
CGauge2D* CGauge2D::Create
(
	const int nMax,				// 最大値
	const float fChangeTime,	// ゲージの変動時間
	const VECTOR3& rPos,		// 位置
	const VECTOR3& rSize,		// 大きさ
	const COLOR& rColFront,		// 表ゲージ色
	const COLOR& rColBack		// 裏ゲージ色
)
{
	// ゲージ2Dの生成
	CGauge2D* pGauge2D = new CGauge2D(fChangeTime);
	if (pGauge2D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// ゲージ2Dの初期化
		if (FAILED(pGauge2D->Init()))
		{ // 初期化に失敗した場合

			// ゲージ2Dの破棄
			SAFE_DELETE(pGauge2D);
			return nullptr;
		}

		// ゲージ最大値を設定
		pGauge2D->SetMaxNum(nMax);

		// 位置を設定
		pGauge2D->SetVec3Position(rPos);

		// 大きさを設定
		pGauge2D->SetVec3Size(rSize);

		// 色を設定
		pGauge2D->SetColorFront(rColFront);	// 表ゲージ色
		pGauge2D->SetColorBack(rColBack);	// 裏ゲージ色

		// 確保したアドレスを返す
		return pGauge2D;
	}
}

//============================================================
//	テクスチャ割当処理 (インデックス)
//============================================================
void CGauge2D::BindTexture(const int nPolygonIdx, const int nTextureIdx)
{
	if (nPolygonIdx > NONE_IDX && nPolygonIdx < POLYGON_MAX)
	{ // 正規インデックスの場合

		// テクスチャインデックスを代入
		m_pGauge[nPolygonIdx]->BindTexture(nTextureIdx);
	}
}

//============================================================
//	テクスチャ割当処理 (パス)
//============================================================
void CGauge2D::BindTexture(const int nPolygonIdx, const char* pTexturePath)
{
	if (nPolygonIdx > NONE_IDX && nPolygonIdx < POLYGON_MAX)
	{ // 正規インデックスの場合

		// テクスチャパスを代入
		m_pGauge[nPolygonIdx]->BindTexture(pTexturePath);
	}
}

//============================================================
//	テクスチャインデックス取得処理
//============================================================
int CGauge2D::GetTextureIndex(const int nPolygonIdx) const
{
	// 非正規なポリゴンのインデックスの場合抜ける
	if (nPolygonIdx <= NONE_IDX || nPolygonIdx >= POLYGON_MAX) { assert(false); return NONE_IDX; }

	// テクスチャインデックスを返す
	return m_pGauge[nPolygonIdx]->GetTextureIndex();
}

//============================================================
//	表示値の加算処理
//============================================================
void CGauge2D::AddNum(const int nAdd, const bool bAnim)
{
	switch (m_state)
	{
	case STATE_NONE:
	{
		// 加算前の表示値を保存
		m_fInitNum = (float)m_nNum;

		// 表示値の加算/補正
		m_nNum += nAdd;
		useful::LimitNum(m_nNum, 0, m_nMaxNum);

		// 加算後の表示値を保存
		m_fDestNum = (float)m_nNum;

		// 変動時間の初期化
		m_fCurTime = 0.0f;
	}
	break;
	case STATE_CHANGE:
	{
		// 変動時間の割合を計算
		float fRate = easing::Liner(m_fCurTime, 0.0f, m_fChangeTime);

		// 目標値への差分を計算
		float fDiffNum = m_fDestNum - m_fInitNum;

		// 途中経過の表示値を保存
		const float fMoveNum = m_fInitNum + fDiffNum * fRate;
		m_fInitNum = fMoveNum;

		// 表示値の加算/補正
		m_nNum += nAdd;
		useful::LimitNum(m_nNum, 0, m_nMaxNum);

		// 加算後の表示値を保存
		m_fDestNum = (float)m_nNum;

		// 変動時間の初期化
		m_fCurTime = 0.0f;
	}
	break;
	}

	if (bAnim)
	{ // 時間をかけてゲージを動かす場合

		// ゲージ変動状態にする
		m_state = STATE_CHANGE;
	}
	else
	{ // 瞬時にゲージを動かす場合

		// 通常状態にする
		m_state = STATE_NONE;

		// 表ゲージの横幅設定
		SetGaugeWidthFront(m_fDestNum);
	}
}

//============================================================
//	表示値の設定処理
//============================================================
void CGauge2D::SetNum(const int nNum, const bool bAnim)
{
	switch (m_state)
	{
	case STATE_NONE:
	{
		// 加算前の表示値を保存
		m_fInitNum = (float)m_nNum;

		// 表示値の設定/補正
		m_nNum = nNum;
		useful::LimitNum(m_nNum, 0, m_nMaxNum);

		// 加算後の表示値を保存
		m_fDestNum = (float)m_nNum;

		// 変動時間の初期化
		m_fCurTime = 0.0f;
	}
	break;
	case STATE_CHANGE:
	{
		// 変動時間の割合を計算
		float fRate = easing::Liner(m_fCurTime, 0.0f, m_fChangeTime);

		// 目標値への差分を計算
		float fDiffNum = m_fDestNum - m_fInitNum;

		// 途中経過の表示値を保存
		const float fMoveNum = m_fInitNum + fDiffNum * fRate;
		m_fInitNum = fMoveNum;

		// 表示値の設定/補正
		m_nNum = nNum;
		useful::LimitNum(m_nNum, 0, m_nMaxNum);

		// 加算後の表示値を保存
		m_fDestNum = (float)m_nNum;

		// 変動時間の初期化
		m_fCurTime = 0.0f;
	}
	break;
	}

	if (bAnim)
	{ // 時間をかけてゲージを動かす場合

		// ゲージ変動状態にする
		m_state = STATE_CHANGE;
	}
	else
	{ // 瞬時にゲージを動かす場合

		// 通常状態にする
		m_state = STATE_NONE;

		// 表ゲージの横幅設定
		SetGaugeWidthFront(m_fDestNum);
	}
}

//============================================================
//	最大値の設定処理
//============================================================
void CGauge2D::SetMaxNum(const int nMax)
{
	// 引数の最大値を設定
	m_nMaxNum = nMax;

	// 表示値が最大値以上の場合は補正
	useful::LimitMaxNum(m_nNum, m_nMaxNum);

	// ゲージの再設定
	SetNum(m_nNum);
}

//============================================================
//	表ゲージ透明度の設定処理
//============================================================
void CGauge2D::SetAlphaFront(const float fAlpha)
{
	// 引数の表ゲージ透明度を設定
	m_pGauge[EPolygon::POLYGON_FRONT]->SetAlpha(fAlpha);
}

//============================================================
//	表ゲージ色の設定処理
//============================================================
void CGauge2D::SetColorFront(const COLOR& rCol)
{
	// 引数の表ゲージ色を設定
	m_pGauge[EPolygon::POLYGON_FRONT]->SetColor(rCol);
}

//============================================================
//	裏ゲージ透明度の設定処理
//============================================================
void CGauge2D::SetAlphaBack(const float fAlpha)
{
	// 引数の裏ゲージ透明度を設定
	m_pGauge[EPolygon::POLYGON_BACK]->SetAlpha(fAlpha);
}

//============================================================
//	裏ゲージ色の設定処理
//============================================================
void CGauge2D::SetColorBack(const COLOR& rCol)
{
	// 引数の裏ゲージ色を設定
	m_pGauge[EPolygon::POLYGON_BACK]->SetColor(rCol);
}

//============================================================
//	表ゲージ透明度の取得処理
//============================================================
float CGauge2D::GetAlphaFront() const
{
	// 表ゲージ透明度を返す
	return m_pGauge[EPolygon::POLYGON_FRONT]->GetAlpha();
}

//============================================================
//	表ゲージ色の取得処理
//============================================================
COLOR CGauge2D::GetColorFront() const
{
	// 表ゲージ色を返す
	return m_pGauge[EPolygon::POLYGON_FRONT]->GetColor();
}

//============================================================
//	裏ゲージ透明度の取得処理
//============================================================
float CGauge2D::GetAlphaBack() const
{
	// 裏ゲージ透明度を返す
	return m_pGauge[EPolygon::POLYGON_BACK]->GetAlpha();
}

//============================================================
//	裏ゲージ色の取得処理
//============================================================
COLOR CGauge2D::GetColorBack() const
{
	// 裏ゲージ色を返す
	return m_pGauge[EPolygon::POLYGON_BACK]->GetColor();
}

//============================================================
//	表ゲージの横幅更新処理
//============================================================
bool CGauge2D::UpdateGaugeWidthFront(const float fDeltaTime)
{
	// 変動時間を進める
	m_fCurTime += fDeltaTime;

	// 変動時間の補正
	bool bEnd = false;
	if (useful::LimitMaxNum(m_fCurTime, m_fChangeTime))
	{ // 変動しきった場合

		// 変動終了を判定
		bEnd = true;
	}

	// 変動時間の割合を計算
	float fRate = easing::Liner(m_fCurTime, 0.0f, m_fChangeTime);

	// 目標値への差分を計算
	float fDiffNum = m_fDestNum - m_fInitNum;

	// 表ゲージの横幅設定
	const float fMoveNum = m_fInitNum + fDiffNum * fRate;
	SetGaugeWidthFront(fMoveNum);

	// 変動が終了しているかを返す
	return bEnd;
}

//============================================================
//	表ゲージの横幅設定処理
//============================================================
void CGauge2D::SetGaugeWidthFront(const float fNum)
{
	const VECTOR3 size = GetVec3Size();	// ゲージの大きさ

	// ゲージの横幅加算量を計算
	const float fFrontWidth = fNum * (size.x / (float)m_nMaxNum);

	// 表ゲージの大きさ設定
	m_pGauge[EPolygon::POLYGON_FRONT]->SetVec3Size(VECTOR3(fFrontWidth, size.y, 0.0f));
}
