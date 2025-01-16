//============================================================
//
//	アイテムテキスト保存バッファヘッダー [frame2DTextBufferItem.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_BUFFER_ITEM_H_
#define _FRAME2D_TEXT_BUFFER_ITEM_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferText.h"
#include "frame2D.h"

//************************************************************
//	クラス定義
//************************************************************
// アイテムテキスト保存バッファクラス
class CFrame2DTextBufferItem : public CFrame2DTextBufferText
{
public:
	// コンストラクタ
	CFrame2DTextBufferItem();

	// デストラクタ
	~CFrame2DTextBufferItem() override;

	// オーバーライド関数
	CFrame2DTextState* CreateState(const CFrame2D::EPreset preset = CFrame2D::PRESET_NONE) override;	// テキスト機能状態生成
	inline CFrame2DTextBufferItem* GetBufferItem() override { return this; }	// アイテムテキストバッファ取得
};

#endif	// _FRAME2D_TEXT_BUFFER_ITEM_H_
