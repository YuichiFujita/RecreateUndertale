//============================================================
//
//	吹き出し状態ヘッダー [gameStateEncount.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _GAME_STATE_ENCOUNT_H_
#define _GAME_STATE_ENCOUNT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "gameState.h"

//************************************************************
//	クラス定義
//************************************************************
// 吹き出し状態クラス
class CGameStateEncount : public CGameState
{
public:
	// コンストラクタ
	CGameStateEncount();

	// デストラクタ
	~CGameStateEncount() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ変数
	float m_fCurTime;	// 現在の待機時間
};

#endif	// _GAME_STATE_ENCOUNT_H_
