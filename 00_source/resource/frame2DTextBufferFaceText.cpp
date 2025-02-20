//============================================================
//
//	表情付きテキスト保存バッファ処理 [frame2DTextBufferFaceText.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferFaceText.h"
#include "frame2DTextStateFaceText.h"

//************************************************************
//	子クラス [CFrame2DTextBufferFaceText] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2DTextBufferFaceText::CFrame2DTextBufferFaceText()
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextBufferFaceText::~CFrame2DTextBufferFaceText()
{

}

//============================================================
//	テキスト機能状態の生成処理
//============================================================
CFrame2DTextState* CFrame2DTextBufferFaceText::CreateState(const CFrame2D::EPreset preset)
{
	if (preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX)
	{ // プリセットが範囲内の場合

		// 表情付きテキスト状態を生成し返す
		return new CFrame2DTextStateFaceText(preset);	// 配置指定
	}
	else
	{ // プリセットが範囲外の場合

		// 表情付きテキスト状態を生成し返す
		return new CFrame2DTextStateFaceText;	// デフォルト
	}
}
