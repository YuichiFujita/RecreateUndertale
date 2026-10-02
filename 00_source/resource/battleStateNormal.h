//============================================================
//
//	通常状態ヘッダー [battleStateNormal.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _BATTLE_STATE_NORMAL_H_
#define _BATTLE_STATE_NORMAL_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "battleState.h"

//************************************************************
//	クラス定義
//************************************************************
// 通常状態クラス
class CBattleStateNormal : public CBattleState
{
public:
	// コンストラクタ
	CBattleStateNormal();

	// デストラクタ
	~CBattleStateNormal() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
};

#endif	// _BATTLE_STATE_NORMAL_H_
