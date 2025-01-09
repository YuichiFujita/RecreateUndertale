//============================================================
//
//	テキスト情報保存バッファヘッダー [frame2DTextBuffer.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_BUFFER_H_
#define _FRAME2D_TEXT_BUFFER_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2D.h"

//************************************************************
//	前方宣言
//************************************************************
class CFrame2DTextState;		// テキスト機能状態クラス
class CFrame2DTextBufferText;	// テキスト機能保存クラス
class CFrame2DTextBufferSelect;	// 選択付きテキスト機能保存クラス
class CFrame2DTextBufferItem;	// アイテムテキスト機能保存クラス

//************************************************************
//	クラス定義
//************************************************************
// テキスト情報保存バッファクラス
class CFrame2DTextBuffer
{
public:
	// コンストラクタ
	CFrame2DTextBuffer();

	// デストラクタ
	virtual ~CFrame2DTextBuffer();

	// 純粋仮想関数
	virtual CFrame2DTextState* CreateState(const CFrame2D::EPreset preset) = 0;	// テキスト機能状態生成

	// 仮想関数
	virtual inline CFrame2DTextBufferText* GetBufferText()		{ return nullptr; }	// テキストバッファ取得
	virtual inline CFrame2DTextBufferSelect* GetBufferSelect()	{ return nullptr; }	// 選択付きテキストバッファ取得
	virtual inline CFrame2DTextBufferItem* GetBufferItem()		{ return nullptr; }	// アイテムテキストバッファ取得
	virtual inline void LoadSetup(std::ifstream* /*pFile*/, const std::string& /*rString*/)	{}	// バッファごとのセットアップ

	// メンバ変数
	AText m_text;	// テキスト保存
};

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferText.h"
#include "frame2DTextBufferSelect.h"

#endif	// _FRAME2D_TEXT_BUFFER_H_
