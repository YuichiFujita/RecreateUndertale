//============================================================
//
//	選択付きテキスト状態処理 [frame2DTextStateSelect.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateSelect.h"
#include "frame2DModuleText.h"
#include "frame2DTextBuffer.h"
#include "manager.h"
#include "object2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	namespace select
	{
		namespace L
		{
			const VECTOR3 OFFSET[] =	// テキストオフセットプリセット
			{
				VECTOR3(-410.0f, -80.0f, 0.0f)	// 下部配置
			};
		}

		namespace R
		{
			const VECTOR3 OFFSET[] =	// テキストオフセットプリセット
			{
				VECTOR3(-410.0f, -80.0f, 0.0f)	// 下部配置
			};
		}

		const char*	FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const int	PRIORITY	= 6;				// テキストの優先順位
		const bool	ITALIC		= false;			// イタリック
		const float	CHAR_HEIGHT	= 42.0f;			// 文字縦幅
		const float	LINE_HEIGHT	= 54.0f;			// 行間縦幅
		const float	WAIT_TIME	= 0.045f;			// 文字表示の待機時間
		const EAlignX ALIGN_X	= XALIGN_CENTER;	// 横配置
		const EAlignY ALIGN_Y	= YALIGN_TOP;		// 縦配置
	}

	namespace soul
	{
		const char* PATH	= "data\\TEXTURE\\spr_heartsmall.png";	// ソウルカーソルテクスチャパス
		const VECTOR3 SIZE	= VECTOR3(26.5f, 26.5f, 0.0f);			// ソウルカーソル大きさ
	}
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(select::L::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");
static_assert(NUM_ARRAY(select::R::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	子クラス [CFrame2DTextStateSelect] のメンバ関数
//************************************************************
//============================================================
//	移譲コンストラクタ (デフォルト)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect() : CFrame2DTextStateSelect(VEC3_ZERO, VEC3_ZERO, VEC3_ZERO)	// TODO：コンストラクタ群それぞれ想定した挙動になっているか検証
{

}

//============================================================
//	コンストラクタ (配置プリセット)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect(const CFrame2D::EPreset preset) : CFrame2DTextStateText(preset),
	m_pSoul		 (nullptr),	// ソウルカーソル情報
	m_nCurSelect (0)		// 現在の選択肢
{
	// プリセット範囲外エラー
	assert(preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX);

	// メンバ変数をクリア
	m_aOffset[SELECT_LEFT]	= select::L::OFFSET[preset];	// 左選択肢オフセット
	m_aOffset[SELECT_RIGHT]	= select::R::OFFSET[preset];	// 右選択肢オフセット
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		m_aNextTextKey[i]	= {};		// 次テキストの検索キー
		m_apSelect[i]		= nullptr;	// 選択肢情報
	}
}

//============================================================
//	コンストラクタ (配置指定)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect(const VECTOR3& rOffsetText, const VECTOR3& rOffsetSelectL, const VECTOR3& rOffsetSelectR) : CFrame2DTextStateText(rOffsetText),
	m_pSoul		 (nullptr),	// ソウルカーソル情報
	m_nCurSelect (0)		// 現在の選択肢
{
	// メンバ変数をクリア
	m_aOffset[SELECT_LEFT]	= rOffsetSelectL;	// 左選択肢オフセット
	m_aOffset[SELECT_RIGHT]	= rOffsetSelectR;	// 右選択肢オフセット
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		m_aNextTextKey[i]	= {};		// 次テキストの検索キー
		m_apSelect[i]		= nullptr;	// 選択肢情報
	}
}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextStateSelect::~CFrame2DTextStateSelect()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFrame2DTextStateSelect::Init()
{
	// メンバ変数を初期化
	m_pSoul		 = nullptr;	// ソウルカーソル情報
	m_nCurSelect = 0;		// 現在の選択肢
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		m_aNextTextKey[i]	= "NONE";	// 次テキストの検索キー
		m_apSelect[i]		= nullptr;	// 選択肢情報
	}

	// 親クラスの初期化
	if (FAILED(CFrame2DTextStateText::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	const int nPrioFrame = m_pContext->GetFramePriority();	// コンテキストの優先順位
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択肢の生成
		m_apSelect[i] = CScrollText2D::Create
		( // 引数
			select::FONT,			// フォントパス
			select::ITALIC,			// イタリック
// TODO
#if 0
			VEC3_ZERO,				// 原点位置
#else
			VECTOR3(SCREEN_CENT.x - 150.0f + 300.0f * (float)i, 600.0f, 0.0f),	// 原点位置
#endif
			select::WAIT_TIME,		// 文字表示の待機時間
			select::CHAR_HEIGHT,	// 文字縦幅
			select::LINE_HEIGHT,	// 行間縦幅
			select::ALIGN_X,		// 横配置
			select::ALIGN_Y			// 縦配置
		);
		if (m_apSelect[i] == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_apSelect[i]->SetPriority(nPrioFrame);

		// 文字送り時の再生SEを設定
		m_apSelect[i]->SetScrollSE(CSound::LABEL_SE_TEXT01);
	}

	// ソウルカーソルの生成
	m_pSoul = CObject2D::Create
	( // 引数
		VEC3_ZERO,	// 位置
		soul::SIZE	// 大きさ
	);
	if (m_pSoul == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ソウルテクスチャを割当
	m_pSoul->BindTexture(soul::PATH);

	// ラベルを設定
	m_pSoul->SetLabel(CObject::LABEL_UI);

	// 優先順位を設定
	m_pSoul->SetPriority(nPrioFrame);

	// カーソルの自動描画をOFFにする
	m_pSoul->SetEnableDraw(false);

	// 相対位置の設定
	SetPositionRelative();

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrame2DTextStateSelect::Uninit()
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// テキストの終了
		SAFE_UNINIT(m_apSelect[i]);
	}

	// ソウルカーソルの終了
	SAFE_UNINIT(m_pSoul);

	// 親クラスの終了
	CFrame2DTextStateText::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CFrame2DTextStateSelect::Update(const float fDeltaTime)
{
	if (!m_pSoul->IsDraw())
	{ // カーソルが表示されていない場合

		if (input::Decide())
		{
			// 文字を全表示させる
			SetTextEnableDraw(true);
			m_apSelect[SELECT_LEFT]->SetEnableDraw(true);
			m_apSelect[SELECT_RIGHT]->SetEnableDraw(true);

			// カーソルの自動描画をONにする
			m_pSoul->SetEnableDraw(true);
			return;
		}

		if (IsTextEndScroll())
		{ // 本文の文字送りが終了した場合

			// 左選択肢の文字送りを開始
			m_apSelect[SELECT_LEFT]->SetEnableScroll(true);
		}
		else { return; }

		if (m_apSelect[SELECT_LEFT]->IsEndScroll())
		{ // 左選択肢の文字送りが終了した場合

			// 右選択肢の文字送りを開始
			m_apSelect[SELECT_RIGHT]->SetEnableScroll(true);
		}
		else { return; }

		if (m_apSelect[SELECT_RIGHT]->IsEndScroll())
		{ // 右選択肢の文字送りが終了した場合

			// カーソルの自動描画をONにする
			m_pSoul->SetEnableDraw(true);
		}
	}
	else
	{ // カーソルが表示されている場合

		// 選択の更新
		UpdateSelect();

		// 決定の更新
		UpdateDecide();
	}
}

//============================================================
//	優先順位の設定処理
//============================================================
void CFrame2DTextStateSelect::SetPriority(const int nPriority)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// テキストの優先順位を設定
		m_apSelect[i]->SetPriority(nPriority);
	}
}

//============================================================
//	位置の設定処理
//============================================================
void CFrame2DTextStateSelect::SetVec3Position(const VECTOR3& /*rPos*/)
{
	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	向きの設定処理
//============================================================
void CFrame2DTextStateSelect::SetVec3Rotation(const VECTOR3& rRot)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// テキストの向きを設定
		m_apSelect[i]->SetVec3Rotation(rRot);
	}

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	テキスト情報保存バッファの割当処理
//============================================================
void CFrame2DTextStateSelect::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// 選択付きテキスト保存バッファに変換できない場合抜ける
	CFrame2DTextBufferSelect* pBuffSelect = pBuffer->GetBufferSelect();
	if (pBuffSelect == nullptr) { assert(false); return; }

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 次テキストの検索キーを割当
		m_aNextTextKey[i] = pBuffSelect->m_aNextTextKey[i];

		// 選択肢のテキスト情報を割当
		int nNumSelect = (int)pBuffSelect->m_aSelect[i].size();	// 文字列数
		for (int j = 0; j < nNumSelect; j++)
		{ // 文字列数分繰り返す

			// 文字列を最後尾に追加
			m_apSelect[i]->PushBackString(pBuffSelect->m_aSelect[i][j]);
		}
	}

	// テキスト情報を割当
	int nNumStr = (int)pBuffSelect->m_text.size();	// 文字列数
	for (int i = 0; i < nNumStr; i++)
	{ // 文字列数分繰り返す

		// 文字列を最後尾に追加
		PushBackString(pBuffSelect->m_text[i]);
	}

	// 文字送りを開始する
	SetTextEnableScroll(true);
}

#if 0
//============================================================
//	テキスト変更処理
//============================================================
void CFrame2DTextStateSelect::ChangeText(const ESelect select, const AText& rText)
{
#if 0
	// 文字列を全て削除
	m_pText->DeleteStringAll();

	// テキストを割当
	int nLoop = (int)rText.size();	// 文字列数
	for (int i = 0; i < nLoop; i++)
	{ // 文字列の数分繰り返す

		// 文字列を最後尾に追加
		m_pText->PushBackString(rText[i]);
	}

	// 文字送りを開始する
	m_pText->SetEnableScroll(true);
#else

#endif
}
#endif

//============================================================
//	選択の更新処理
//============================================================
void CFrame2DTextStateSelect::UpdateSelect()
{
	// 選択肢操作
	CInputKeyboard* pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// 左に選択をずらす
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// 右に選択をずらす
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}

	// TODO
	VECTOR3 posSelect = m_apSelect[m_nCurSelect]->GetVec3Position();
	posSelect.x -= m_apSelect[m_nCurSelect]->GetTextWidth() * 0.5f + 30.0f;
	posSelect.y += m_apSelect[m_nCurSelect]->GetCharHeight() * 0.5f;

	// ソウルカーソルの位置を移動
	m_pSoul->SetVec3Position(posSelect);
}

//============================================================
//	決定の更新処理
//============================================================
void CFrame2DTextStateSelect::UpdateDecide()
{
	if (input::Decide())
	{
		// テキストの遷移
		m_pContext->TransText(m_aNextTextKey[m_nCurSelect]);
	}
}

//============================================================
//	相対位置の設定処理
//============================================================
void CFrame2DTextStateSelect::SetPositionRelative()
{
#if 0
	VECTOR3 posFrame = m_pContext->GetVec3Position();	// フレーム位置
	VECTOR3 rotFrame = m_pContext->GetVec3Rotation();	// フレーム向き

	// X座標オフセット分ずらす
	posFrame.x += sinf(rotFrame.z + HALF_PI) * m_offset.x;
	posFrame.y += cosf(rotFrame.z + HALF_PI) * m_offset.x;

	// Y座標オフセット分ずらす
	posFrame.x += sinf(rotFrame.z) * m_offset.y;
	posFrame.y += cosf(rotFrame.z) * m_offset.y;

	// テキスト位置の反映
	m_pText->SetVec3Position(posFrame);
#else
	// TODO：1Fだけ位置ずれしてる
	VECTOR3 posSelect = m_apSelect[m_nCurSelect]->GetVec3Position();
	posSelect.x -= m_apSelect[m_nCurSelect]->GetTextWidth() * 0.5f + 30.0f;
	posSelect.y += m_apSelect[m_nCurSelect]->GetCharHeight() * 0.5f;

	// ソウルカーソルの位置を移動
	m_pSoul->SetVec3Position(posSelect);
#endif
}
