//============================================================
//
//	通常状態ヘッダー [playerStateNormal.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PLAYER_STATE_NORMAL_H_
#define _PLAYER_STATE_NORMAL_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "playerState.h"

//************************************************************
//	クラス定義
//************************************************************
// 通常状態クラス
class CPlayerStateNormal : public CPlayerState
{
public:
	// コンストラクタ
	CPlayerStateNormal();

	// デストラクタ
	~CPlayerStateNormal() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	int Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ関数
	int ControlMove();	// 移動操作
	void UpdatePosition(VECTOR3& rPos, const float fDeltaTime);	// 位置更新

	// メンバ変数
	VECTOR3 m_move;	// 移動量
};

#endif	// _PLAYER_STATE_NORMAL_H_
