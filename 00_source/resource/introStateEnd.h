//============================================================
//
//	終了状態ヘッダー [introStateEnd.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _INTRO_STATE_END_H_
#define _INTRO_STATE_END_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "introState.h"

//************************************************************
//	クラス定義
//************************************************************
// 終了状態クラス
class CIntroStateEnd : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateEnd();

	// デストラクタ
	~CIntroStateEnd() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ変数
	float m_fCurTime;	// 現在の待機時間
};

#endif	// _INTRO_STATE_END_H_
