//============================================================
//
//	ソウル点滅状態ヘッダー [gameStateEncountBlink.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _GAME_STATE_ENCOUNT_BLINK_H_
#define _GAME_STATE_ENCOUNT_BLINK_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "gameState.h"

//************************************************************
//	前方宣言
//************************************************************
class CObject2D;	// オブジェクト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// ソウル点滅状態クラス
class CGameStateEncountBlink : public CGameState
{
public:
	// コンストラクタ
	CGameStateEncountBlink();

	// デストラクタ
	~CGameStateEncountBlink() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ関数
	void UpdateBlink(const float fDeltaTime);	// 点滅の更新
	bool UpdateMove(const float fDeltaTime);	// 移動の更新

	// メンバ変数
	CObject2D*	m_pSoul;		// ソウル情報
	VECTOR3		m_posInit;		// 初期位置
	float		m_fCurTime;		// 現在の待機時間
	int			m_nNumBlink;	// 点滅カウント
};

#endif	// _GAME_STATE_ENCOUNT_BLINK_H_
