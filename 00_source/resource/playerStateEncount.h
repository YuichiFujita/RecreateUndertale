//============================================================
//
//	吹き出し状態ヘッダー [playerStateEncount.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PLAYER_STATE_ENCOUNT_H_
#define _PLAYER_STATE_ENCOUNT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "playerState.h"
#include "player.h"

//************************************************************
//	前方宣言
//************************************************************
class CBalloonEncount;	// エンカウント吹き出しクラス

//************************************************************
//	クラス定義
//************************************************************
// 吹き出し状態クラス
class CPlayerStateEncount : public CPlayerState
{
public:
	// コンストラクタ
	CPlayerStateEncount();

	// デストラクタ
	~CPlayerStateEncount() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	int Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ関数
	CPlayer::EMotion GetIdolMotionType() const;	// 現在向きの待機モーション取得

	// メンバ変数
	CBalloonEncount* m_pEncount;	// エンカウント吹き出し
};

#endif	// _PLAYER_STATE_ENCOUNT_H_
