//============================================================
//
//	コマンド選択ヘッダー [battleStateCommand.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _BATTLE_STATE_COMMAND_H_
#define _BATTLE_STATE_COMMAND_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "battleState.h"

//************************************************************
//	クラス定義
//************************************************************
// コマンド選択クラス
class CBattleStateCommand : public CBattleState
{
public:
	// コンストラクタ
	CBattleStateCommand();

	// デストラクタ
	~CBattleStateCommand() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
};

#endif	// _BATTLE_STATE_COMMAND_H_
