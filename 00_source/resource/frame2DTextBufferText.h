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
//	前方宣言
//************************************************************
class CFrame2DModule;	// フレーム2D機能クラス

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
	CFrame2DModule* CreateModule(const CFrame2D::EPreset preset) override;		// テキスト機能生成
	void LoadKeyString(std::ifstream* pFile, std::string& rString) override;	// 現在キー文字列読込
	inline CFrame2DTextBufferText* GetText() override { return this; }			// テキスト取得

	// メンバ変数
	std::string m_sNextTextKey;	// 次テキストの検索キー
};

#endif	// _FRAME2D_TEXT_BUFFER_TEXT_H_
