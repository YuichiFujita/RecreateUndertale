//============================================================
//
//	テキスト情報保存バッファ処理 [frame2DTextBuffer.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBuffer.h"

//************************************************************
//	親クラス [CFrame2DTextBuffer] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2DTextBuffer::CFrame2DTextBuffer() :
	m_font	(CFrame2DModuleText::FONT_DEFAULT),		// フォント
	m_sound	(CFrame2DModuleText::SOUND_DEFAULT),	// サウンド
	m_sPath	(""),	// テキスト保存パス
	m_sKey	(""),	// テキスト検索キー
	m_text	({})	// テキスト保存
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextBuffer::~CFrame2DTextBuffer()
{

}

//============================================================
//	バッファごとのセットアップ処理
//============================================================
void CFrame2DTextBuffer::LoadSetup(std::ifstream* pFile, const std::string& rString)
{
	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return; }

	// ファイルを読込
	std::string str;	// 読込文字列
	if (rString == "FONT")
	{
		int nCastFont = 0;		// EFont型変換
		*pFile >> str;			// ＝を読込
		*pFile >> nCastFont;	// フォントを読込

		// 読み込んだ値をEFont型に変換
		assert(nCastFont > NONE_IDX && nCastFont < CFrame2DModuleText::FONT_MAX);
		m_font = (CFrame2DModuleText::EFont)nCastFont;
	}
	else if (rString == "SOUND")
	{
		int nCastSound = 0;		// ESound型変換
		*pFile >> str;			// ＝を読込
		*pFile >> nCastSound;	// サウンドを読込

		// 読み込んだ値をESound型に変換
		assert(nCastSound > NONE_IDX && nCastSound < CFrame2DModuleText::SOUND_MAX);
		m_sound = (CFrame2DModuleText::ESound)nCastSound;
	}
}
