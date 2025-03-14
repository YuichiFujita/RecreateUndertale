//============================================================
//
//	テキスト保存バッファヘッダー [frame2DTextBufferText.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_BUFFER_TEXT_H_
#define _FRAME2D_TEXT_BUFFER_TEXT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBuffer.h"
#include "frame2D.h"

//************************************************************
//	クラス定義
//************************************************************
// テキスト保存バッファクラス
class CFrame2DTextBufferText : public CFrame2DTextBuffer
{
public:
	// コンストラクタ
	CFrame2DTextBufferText();

	// デストラクタ
	~CFrame2DTextBufferText() override;

	// オーバーライド関数
	CFrame2DTextState* CreateState() override;	// テキスト機能状態生成
	void LoadSetup(std::ifstream* pFile, const std::string& rString) override;	// バッファごとのセットアップ
	inline CFrame2DTextBufferText* GetBufferText() override { return this; }	// テキストバッファ取得

	// メンバ変数
	std::string m_sNextTextKey;	// 次テキストの検索キー
};

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferFaceText.h"
#include "frame2DTextBufferItem.h"

#endif	// _FRAME2D_TEXT_BUFFER_TEXT_H_
