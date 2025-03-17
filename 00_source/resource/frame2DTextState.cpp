//============================================================
//
//	テキスト機能状態処理 [frame2DTextState.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextState.h"
#include "frame2DTextBuffer.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* FONT_PATH[] =	// フォントパス
	{
		"data\\FONT\\JFドット東雲ゴシック14.ttf",	// デフォルト
	};

	const CSound::ELabel SOUND_LABEL[] =	// サウンドラベル
	{
		CSound::LABEL_SE_TEXT00,	// デフォルト
	};
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(FONT_PATH)   == CFrame2DTextState::FONT_MAX,  "ERROR : Font Count Mismatch");
static_assert(NUM_ARRAY(SOUND_LABEL) == CFrame2DTextState::SOUND_MAX, "ERROR : Sound Count Mismatch");

//************************************************************
//	親クラス [CFrame2DTextState] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2DTextState::CFrame2DTextState() :
	m_pContext		(nullptr),		// コンテキスト
	m_sCurTextKey	(""),			// 割当済みテキストの検索キー
	m_font			(FONT_DEFAULT),	// フォント
	m_sound			(SOUND_DEFAULT)	// サウンド
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextState::~CFrame2DTextState()
{

}

//============================================================
//	テキスト情報保存バッファの割当処理
//============================================================
void CFrame2DTextState::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// 割り当てるテキストの検索キーを保存
	m_sCurTextKey = pBuffer->m_sKey;

	// フォントを保存/割当
	m_font = pBuffer->m_font;
	SetFontPath(m_font);

	// サウンドを保存/割当
	m_sound = pBuffer->m_sound;
	SetSoundLabel(m_sound);

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	フォントパスの取得処理
//============================================================
std::string CFrame2DTextState::GetFontPath(const EFont font)
{
	// フォントパスを返す
	return FONT_PATH[font];
}

//============================================================
//	サウンドラベルの取得処理
//============================================================
CSound::ELabel CFrame2DTextState::GetSoundLabel(const ESound sound)
{
	// サウンドラベルを返す
	return SOUND_LABEL[sound];
}
