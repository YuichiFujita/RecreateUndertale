//============================================================
//
//	アイテムテキスト保存バッファ処理 [frame2DTextBufferItem.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferItem.h"
#include "frame2DTextStateItem.h"

//************************************************************
//	子クラス [CFrame2DTextBufferItem] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2DTextBufferItem::CFrame2DTextBufferItem()
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextBufferItem::~CFrame2DTextBufferItem()
{

}

//============================================================
//	テキスト機能状態の生成処理
//============================================================
CFrame2DTextState* CFrame2DTextBufferItem::CreateState(const CFrame2D::EPreset preset)
{
	if (preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX)
	{ // プリセットが範囲内の場合

		// アイテムテキスト状態を生成し返す
		return new CFrame2DTextStateItem(preset);	// 配置指定
	}
	else
	{ // プリセットが範囲外の場合

		// アイテムテキスト状態を生成し返す
		return new CFrame2DTextStateItem;	// デフォルト
	}
}

// TODO：いる？
#if 0
//============================================================
//	バッファごとのセットアップ処理
//============================================================
void CFrame2DTextBufferItem::LoadSetup(std::ifstream* pFile, const std::string& rString)
{
	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return; }

	std::string str;	// 読込文字列
	if (rString == "NEXT")
	{
		*pFile >> str;				// ＝を読込
		*pFile >> m_sNextTextKey;	// 次テキストの検索キーを読込
	}
}
#endif
