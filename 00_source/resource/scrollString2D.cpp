//============================================================
//
//	文字送り文字列2D処理 [scrollString2D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "scrollString2D.h"
#include "manager.h"
#include "string2D.h"
#include "char2D.h"

//************************************************************
//	子クラス [CScrollString2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CScrollString2D::CScrollString2D() :
	m_labelSE	(CSound::LABEL_NONE),	// 文字送り再生SEラベル
	m_nNextIdx	(0),	// 次表示する文字インデックス
	m_fNextTime	(0.0f),	// 次表示するまでの時間
	m_fCurTime	(0.0f),	// 現在の待機時間
	m_bScroll	(false)	// 文字送り状況
{

}

//============================================================
//	デストラクタ
//============================================================
CScrollString2D::~CScrollString2D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CScrollString2D::Init()
{
	// メンバ変数を初期化
	m_labelSE	= CSound::LABEL_NONE;	// 文字送り再生SEラベル
	m_nNextIdx	= 0;		// 次表示する文字インデックス
	m_fNextTime	= 0.0f;		// 次表示するまでの時間
	m_fCurTime	= 0.0f;		// 現在の待機時間
	m_bScroll	= false;	// 文字送り状況

	// 文字列2Dの初期化
	if (FAILED(CString2D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CScrollString2D::Uninit()
{
	// 文字列2Dの終了
	CString2D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CScrollString2D::Update(const float fDeltaTime)
{
	// 文字送りの更新
	UpdateScroll(fDeltaTime);

	// 文字列2Dの更新
	CString2D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CScrollString2D::Draw(CShader* pShader)
{
	// 文字列2Dの描画
	CString2D::Draw(pShader);
}

//============================================================
//	描画状況の設定処理
//============================================================
void CScrollString2D::SetEnableDraw(const bool bDraw)
{
	// 次表示する文字インデックスを描画設定に応じて反映
	m_nNextIdx = (bDraw) ? GetNumChar() - 1 : 0;	// ONなら最後尾、OFFなら先頭

	// 現在の待機時間を初期化
	m_fCurTime = 0.0f;

	// 描画状況の設定
	CString2D::SetEnableDraw(bDraw);
}

//============================================================
//	フォントの設定処理
//============================================================
void CScrollString2D::SetFont
(
	const std::string& rFilePath,	// フォントパス
	const bool bItalic				// イタリック
)
{
	// フォントの設定
	CString2D::SetFont(rFilePath, bItalic);

	// 文字列の自動描画をOFFにする
	SetEnableDraw(false);
}

//============================================================
//	文字列の設定処理 (マルチバイト文字列)
//============================================================
HRESULT CScrollString2D::SetString(const std::string& rStr)
{
	// 文字列をワイド変換
	std::wstring wsStr = useful::MultiByteToWide(rStr);

	// 文字列を設定
	if (FAILED(SetString(wsStr)))
	{ // 設定に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	文字列の設定処理 (ワイド文字列)
//============================================================
HRESULT CScrollString2D::SetString(const std::wstring& rStr)
{
	// 文字列の設定
	if (FAILED(CString2D::SetString(rStr)))
	{ // 追加に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 設定した文字列の自動描画をOFFにする
	SetEnableDraw(false);

	return S_OK;
}

//============================================================
//	生成処理 (マルチバイト文字列)
//============================================================
CScrollString2D* CScrollString2D::Create
(
	const std::string& rFilePath,	// フォントパス
	const bool bItalic,				// イタリック
	const std::string& rStr,		// 指定文字列
	const VECTOR3& rPos,			// 原点位置
	const float fNextTime,			// 文字表示の待機時間
	const float fHeight,			// 文字縦幅
	const EAlignX alignX,			// 横配置
	const VECTOR3& rRot,			// 原点向き
	const COLOR& rCol				// 色
)
{
	// 文字送り文字列2Dの生成
	CScrollString2D* pScrollString2D = new CScrollString2D;
	if (pScrollString2D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 文字送り文字列2Dの初期化
		if (FAILED(pScrollString2D->Init()))
		{ // 初期化に失敗した場合

			// 文字送り文字列2Dの破棄
			SAFE_DELETE(pScrollString2D);
			return nullptr;
		}

		// フォントを設定
		pScrollString2D->SetFont(rFilePath, bItalic);

		// 文字列を設定
		if (FAILED(pScrollString2D->SetString(rStr)))
		{ // 設定に失敗した場合

			// 文字送り文字列2Dの破棄
			SAFE_DELETE(pScrollString2D);
			return nullptr;
		}

		// 原点位置を設定
		pScrollString2D->SetVec3Position(rPos);

		// 原点向きを設定
		pScrollString2D->SetVec3Rotation(rRot);

		// 色を設定
		pScrollString2D->SetColor(rCol);

		// 文字表示の待機時間を設定
		pScrollString2D->SetNextTime(fNextTime);

		// 文字縦幅を設定
		pScrollString2D->SetCharHeight(fHeight);

		// 横配置を設定
		pScrollString2D->SetAlignX(alignX);

		// 確保したアドレスを返す
		return pScrollString2D;
	}
}

//============================================================
//	生成処理 (ワイド文字列)
//============================================================
CScrollString2D* CScrollString2D::Create
(
	const std::string& rFilePath,	// フォントパス
	const bool bItalic,				// イタリック
	const std::wstring& rStr,		// 指定文字列
	const VECTOR3& rPos,			// 原点位置
	const float fNextTime,			// 文字表示の待機時間
	const float fHeight,			// 文字縦幅
	const EAlignX alignX,			// 横配置
	const VECTOR3& rRot,			// 原点向き
	const COLOR& rCol				// 色
)
{
	// 文字送り文字列2Dの生成
	CScrollString2D* pScrollString2D = new CScrollString2D;
	if (pScrollString2D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 文字送り文字列2Dの初期化
		if (FAILED(pScrollString2D->Init()))
		{ // 初期化に失敗した場合

			// 文字送り文字列2Dの破棄
			SAFE_DELETE(pScrollString2D);
			return nullptr;
		}

		// フォントを設定
		pScrollString2D->SetFont(rFilePath, bItalic);

		// 文字列を設定
		if (FAILED(pScrollString2D->SetString(rStr)))
		{ // 設定に失敗した場合

			// 文字送り文字列2Dの破棄
			SAFE_DELETE(pScrollString2D);
			return nullptr;
		}

		// 原点位置を設定
		pScrollString2D->SetVec3Position(rPos);

		// 原点向きを設定
		pScrollString2D->SetVec3Rotation(rRot);

		// 色を設定
		pScrollString2D->SetColor(rCol);

		// 文字表示の待機時間を設定
		pScrollString2D->SetNextTime(fNextTime);

		// 文字縦幅を設定
		pScrollString2D->SetCharHeight(fHeight);

		// 横配置を設定
		pScrollString2D->SetAlignX(alignX);

		// 確保したアドレスを返す
		return pScrollString2D;
	}
}

//============================================================
//	文字送り終了状況の取得処理
//============================================================
bool CScrollString2D::IsEndScroll() const
{
	// 文字列がない場合抜ける
	if (GetNumChar() <= 0) { return true; }

	// 終端文字の自動描画フラグから文字送りの終了を判定する
	return GetChar2D(GetNumChar() - 1)->IsDraw();
}

//============================================================
//	文字送りの更新処理
//============================================================
void CScrollString2D::UpdateScroll(const float fDeltaTime)
{
	// 文字送りがOFFなら抜ける
	if (!m_bScroll) { return; }

	// 文字がない場合抜ける
	if (GetNumChar() <= 0) { m_bScroll = false; return; }

	// 現在の待機時間を加算
	m_fCurTime += fDeltaTime;
	while (m_fCurTime >= m_fNextTime)
	{ // 待機し終わった場合

		CChar2D* pChar = GetChar2D(m_nNextIdx);	// 表示させる文字情報

		// 文字の自動描画をONにする
		assert(pChar != nullptr);
		pChar->SetEnableDraw(true);

		// 現在の待機時間から待機時間を減算
		m_fCurTime -= m_fNextTime;

		// 文字送り中の効果音を再生
		PlayScrollSE(pChar);

		// 次の文字インデックスに移行
		m_nNextIdx++;

		if (useful::LimitMaxNum(m_nNextIdx, GetNumChar() - 1))
		{ // 最後の文字に到達した場合

			// 現在の待機時間を初期化
			m_fCurTime = 0.0f;

			// 文字送りをOFFにする
			m_bScroll = false;

			break;
		}
	}
}

//============================================================
//	文字送り効果音の再生処理
//============================================================
void CScrollString2D::PlayScrollSE(CChar2D* pChar2D)
{
	// ラベルが指定なしの場合抜ける
	if (m_labelSE == CSound::LABEL_NONE) { return; }

	// テクスチャが透明な場合抜ける
	if (pChar2D->IsTexEmpty()) { return; }

	// 指定ラベルのSEを再生
	PLAY_SOUND(m_labelSE);
}
