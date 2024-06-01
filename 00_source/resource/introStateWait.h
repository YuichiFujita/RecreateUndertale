//============================================================
//
//	待機状態ヘッダー [introStateWait.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _INTRO_STATE_WAIT_H_
#define _INTRO_STATE_WAIT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "introState.h"

//************************************************************
//	クラス定義
//************************************************************
// 待機状態クラス
class CIntroStateWait : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateWait(const float fEndTime);

	// デストラクタ
	~CIntroStateWait() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ変数
	const float m_fEndTime;	// 待機の終了時間
	float m_fCurTime;		// 現在の待機時間
};

#endif	// _INTRO_STATE_WAIT_H_
