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
		"data\\FONT\\玉ねぎ楷書激無料版v7改.ttf",	// テスト00
		"data\\FONT\\零ゴシック.otf",				// テスト01
	};
	const float FONT_HEIGHT[] =	// フォント縦幅
	{
		42.0f,	// デフォルト
		46.0f,	// テスト00
		60.0f,	// テスト01
	};
	const CSound::ELabel SOUND_LABEL[] =	// サウンドラベル
	{
		CSound::LABEL_SE_TEXT00,		// デフォルト
		CSound::LABEL_SE_TEXT01,		// イントロ
		CSound::LABEL_SE_TEXT_TORIEL00,	// トリエル00
	};
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(FONT_PATH)   == CFrame2DModuleText::FONT_MAX,  "ERROR : Font Count Mismatch");
static_assert(NUM_ARRAY(FONT_HEIGHT) == CFrame2DModuleText::FONT_MAX,  "ERROR : Font Count Mismatch");
static_assert(NUM_ARRAY(SOUND_LABEL) == CFrame2DModuleText::SOUND_MAX, "ERROR : Sound Count Mismatch");

//************************************************************
//	親クラス [CFrame2DTextState] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2DTextState::CFrame2DTextState() :
	m_pContext		(nullptr),	// コンテキスト
	m_sCurTextKey	("")		// 割当済みテキストの検索キー
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

	// フォントを割当
	SetFontPath(pBuffer->m_font);

	// サウンドを割当
	SetSoundLabel(pBuffer->m_sound);

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	フォントパスの取得処理
//============================================================
std::string CFrame2DTextState::GetFontPath(const CFrame2DModuleText::EFont font)
{
	// フォントパスを返す
	return FONT_PATH[font];
}

//============================================================
//	フォント縦幅の取得処理
//============================================================
float CFrame2DTextState::GetFontHeight(const CFrame2DModuleText::EFont font)
{
	// フォント縦幅を返す
	return FONT_HEIGHT[font];
}

//============================================================
//	サウンドラベルの取得処理
//============================================================
CSound::ELabel CFrame2DTextState::GetSoundLabel(const CFrame2DModuleText::ESound sound)
{
	// サウンドラベルを返す
	return SOUND_LABEL[sound];
}
