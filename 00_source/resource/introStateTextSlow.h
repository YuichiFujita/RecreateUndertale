//============================================================
//
//	文字送り速度低下状態ヘッダー [introStateTextSlow.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _INTRO_STATE_TEXT_SLOW_H_
#define _INTRO_STATE_TEXT_SLOW_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "introStateText.h"

//************************************************************
//	クラス定義
//************************************************************
// 文字送り速度低下状態クラス
class CIntroStateTextSlow : public CIntroStateText
{
public:
	// コンストラクタ
	CIntroStateTextSlow();

	// デストラクタ
	~CIntroStateTextSlow() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
};

#endif	// _INTRO_STATE_TEXT_SLOW_H_
