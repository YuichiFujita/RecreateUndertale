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
	// 角度列挙
	enum EAngle
	{
		ANGLE_UP = 0,	// 上
		ANGLE_DOWN,		// 下
		ANGLE_LEFT,		// 左
		ANGLE_RIGHT,	// 右
		ANGLE_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CPlayerStateNormal();

	// デストラクタ
	~CPlayerStateNormal() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	int Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ関数
	int ControlMove(void);	// 移動操作
	void UpdatePosition(const float fDeltaTime);	// 位置更新

	// メンバ変数
	D3DXVECTOR3	m_move;	// 移動量
	EAngle m_moveAngle;	// 移動方向
};

#endif	// _PLAYER_STATE_NORMAL_H_
