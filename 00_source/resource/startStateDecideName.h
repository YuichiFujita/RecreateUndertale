//============================================================
//
//	名前決定状態ヘッダー [startStateDecideName.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _START_STATE_DECIDE_NAME_H_
#define _START_STATE_DECIDE_NAME_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "startState.h"

//************************************************************
//	クラス定義
//************************************************************
// 名前決定状態クラス
class CStartStateDecideName : public CStartState
{
public:
	// コンストラクタ
	CStartStateDecideName();

	// デストラクタ
	~CStartStateDecideName() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
};

#endif	// _START_STATE_DECIDE_NAME_H_
