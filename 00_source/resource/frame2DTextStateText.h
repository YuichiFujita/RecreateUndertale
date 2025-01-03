//============================================================
//
//	テキスト状態ヘッダー [frame2DTextStateText.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_TEXT_H_
#define _FRAME2D_TEXT_STATE_TEXT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextState.h"

//************************************************************
//	クラス定義
//************************************************************
// テキスト状態クラス
class CFrame2DTextStateText : public CFrame2DTextState
{
public:
	// コンストラクタ
	CFrame2DTextStateText();

	// デストラクタ
	~CFrame2DTextStateText() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	inline CFrame2DTextStateText* GetStateText() override { return this; }	// テキスト状態取得

private:
	// メンバ変数

};

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateSelect.h"

#endif	// _FRAME2D_TEXT_STATE_TEXT_H_
