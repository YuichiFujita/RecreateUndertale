//============================================================
//
//	テキスト保存バッファ処理 [frame2DTextBufferText.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferText.h"
#include "frame2DTextStateText.h"

//************************************************************
//	子クラス [CFrame2DTextBufferText] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2DTextBufferText::CFrame2DTextBufferText() :
	m_sNextTextKey	("NONE")	// 次テキストの検索キー
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextBufferText::~CFrame2DTextBufferText()
{

}

//============================================================
//	テキスト機能状態の生成処理
//============================================================
CFrame2DTextState* CFrame2DTextBufferText::CreateState(const CFrame2D::EPreset preset)
{
	if (preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX)
	{ // プリセットが範囲内の場合

		// テキスト状態を生成し返す
		return new CFrame2DTextStateText(preset);	// 配置指定
	}
	else
	{ // プリセットが範囲外の場合

		// テキスト状態を生成し返す
		return new CFrame2DTextStateText;	// デフォルト
	}
}

//============================================================
//	バッファごとのセットアップ処理
//============================================================
void CFrame2DTextBufferText::LoadSetup(std::ifstream* pFile, const std::string& rString)
{
	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return; }

	// ファイルを読込
	std::string str;	// 読込文字列
	if (rString == "NEXT")
	{
		*pFile >> str;				// ＝を読込
		*pFile >> m_sNextTextKey;	// 次テキストの検索キーを読込
	}
}
