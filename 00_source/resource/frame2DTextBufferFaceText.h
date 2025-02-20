//============================================================
//
//	表情付きテキスト保存バッファヘッダー [frame2DTextBufferFaceText.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_BUFFER_FACE_TEXT_H_
#define _FRAME2D_TEXT_BUFFER_FACE_TEXT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferText.h"
#include "frame2D.h"

//************************************************************
//	クラス定義
//************************************************************
// 表情付きテキスト保存バッファクラス
class CFrame2DTextBufferFaceText : public CFrame2DTextBufferText
{
public:
	// コンストラクタ
	CFrame2DTextBufferFaceText();

	// デストラクタ
	~CFrame2DTextBufferFaceText() override;

	// オーバーライド関数
	CFrame2DTextState* CreateState(const CFrame2D::EPreset preset = CFrame2D::PRESET_NONE) override;	// テキスト機能状態生成
	inline CFrame2DTextBufferFaceText* GetBufferFaceText() override { return this; }	// 表情付きテキストバッファ取得
};

#endif	// _FRAME2D_TEXT_BUFFER_FACE_TEXT_H_
