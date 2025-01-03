//============================================================
//
//	選択付きテキスト状態ヘッダー [frame2DTextStateSelect.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_SELECT_H_
#define _FRAME2D_TEXT_STATE_SELECT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateText.h"

//************************************************************
//	クラス定義
//************************************************************
// 選択付きテキスト状態クラス
class CFrame2DTextStateSelect : public CFrame2DTextStateText
{
public:
	// コンストラクタ
	CFrame2DTextStateSelect();

	// デストラクタ
	~CFrame2DTextStateSelect() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	inline CFrame2DTextStateSelect* GetStateSelect() override { return this; }	// 選択付きテキスト状態取得

private:
	// メンバ変数

};

#endif	// _FRAME2D_TEXT_STATE_SELECT_H_
