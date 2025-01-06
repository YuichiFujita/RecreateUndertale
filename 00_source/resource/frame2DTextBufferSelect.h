//============================================================
//
//	選択付きテキスト保存バッファヘッダー [frame2DTextBufferSelect.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_BUFFER_SELECT_H_
#define _FRAME2D_TEXT_BUFFER_SELECT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBuffer.h"
#include "frame2D.h"
#include "frame2DTextStateSelect.h"

//************************************************************
//	前方宣言
//************************************************************
class CFrame2DModule;	// フレーム2D機能クラス

//************************************************************
//	クラス定義
//************************************************************
// 選択付きテキスト保存バッファクラス
class CFrame2DTextBufferSelect : public CFrame2DTextBuffer
{
public:
	// コンストラクタ
	CFrame2DTextBufferSelect();

	// デストラクタ
	~CFrame2DTextBufferSelect() override;

	// オーバーライド関数
	CFrame2DTextState* CreateState(const CFrame2D::EPreset preset = CFrame2D::PRESET_NONE) override;	// テキスト機能状態生成
	void LoadSetup(std::ifstream* pFile, const std::string& rString) override;		// バッファごとのセットアップ
	inline CFrame2DTextBufferSelect* GetBufferSelect() override { return this; }	// 選択付きテキストバッファ取得

	// メンバ関数
	void LoadSelect(std::ifstream* pFile, const CFrame2DTextStateSelect::ESelect select);	// 選択肢文字列読込

	// メンバ変数
	std::string m_aNextTextKey[CFrame2DTextStateSelect::SELECT_MAX];	// 次テキストの検索キー
	AText m_aSelect[CFrame2DTextStateSelect::SELECT_MAX];	// 選択テキスト保存
};

#endif	// _FRAME2D_TEXT_BUFFER_SELECT_H_
