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
class CFrame2DTextState;			// テキスト機能状態クラス
class CFrame2DTextBufferText;		// テキスト保存バッファクラス
class CFrame2DTextBufferSelect;		// 選択付きテキスト保存バッファクラス
class CFrame2DTextBufferFaceText;	// 表情付きテキスト保存バッファクラス
class CFrame2DTextBufferFaceSelect;	// 表情/選択付きテキスト保存バッファクラス
class CFrame2DTextBufferItem;		// アイテムテキスト保存バッファクラス

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
	virtual inline CFrame2DTextBufferText* GetBufferText()				{ return nullptr; }		// テキストバッファ取得
	virtual inline CFrame2DTextBufferSelect* GetBufferSelect()			{ return nullptr; }		// 選択付きテキストバッファ取得
	virtual inline CFrame2DTextBufferFaceText* GetBufferFaceText()		{ return nullptr; }		// 表情付きテキストバッファ取得
	virtual inline CFrame2DTextBufferFaceSelect* GetBufferFaceSelect()	{ return nullptr; }		// 表情/選択付きテキストバッファ取得
	virtual inline CFrame2DTextBufferItem* GetBufferItem()				{ return nullptr; }		// アイテムテキストバッファ取得
	virtual inline void LoadSetup(std::ifstream* /*pFile*/, const std::string& /*rString*/)	{}	// バッファごとのセットアップ

	// メンバ変数
	std::string m_sPath;	// テキスト保存パス
	std::string m_sKey;		// テキスト検索キー
	AText m_text;			// テキスト保存
};

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferText.h"
#include "frame2DTextBufferSelect.h"

#endif	// _FRAME2D_TEXT_BUFFER_H_
