//============================================================
//
//	テキスト機能状態ヘッダー [frame2DTextState.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_H_
#define _FRAME2D_TEXT_STATE_H_

//************************************************************
//	前方宣言
//************************************************************
class CFrame2DModuleText;		// テキスト表示機能クラス
class CFrame2DTextStateText;	// テキスト状態クラス
class CFrame2DTextStateSelect;	// 選択付きテキスト状態クラス

//************************************************************
//	クラス定義
//************************************************************
// テキスト機能状態クラス
class CFrame2DTextState
{
public:
	// コンストラクタ
	CFrame2DTextState();

	// デストラクタ
	virtual ~CFrame2DTextState();

	// 純粋仮想関数
	virtual HRESULT Init()	= 0;	// 初期化
	virtual void Uninit()	= 0;	// 終了
	virtual void Update(const float fDeltaTime) = 0;	// 更新

	// 仮想関数
	inline virtual CFrame2DTextStateText* GetStateText()	 { return nullptr; }	// テキスト状態取得
	inline virtual CFrame2DTextStateSelect* GetStateSelect() { return nullptr; }	// 選択付きテキスト状態取得

	// メンバ関数
	inline void SetContext(CFrame2DModuleText* pContext) { m_pContext = pContext; }	// コンテキスト設定

protected:
	// メンバ変数
	CFrame2DModuleText* m_pContext;	// コンテキスト
};

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateText.h"

#endif	// _FRAME2D_TEXT_STATE_H_
