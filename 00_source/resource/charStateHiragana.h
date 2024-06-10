//============================================================
//
//	ひらがな状態ヘッダー [charStateHiragana.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _CHAR_STATE_HIRAGANA_H_
#define _CHAR_STATE_HIRAGANA_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "charState.h"

//************************************************************
//	クラス定義
//************************************************************
// ひらがな状態クラス
class CCharStateHiragana : public CCharState
{
public:
	// コンストラクタ
	CCharStateHiragana();

	// デストラクタ
	~CCharStateHiragana() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
};

#endif	// _CHAR_STATE_HIRAGANA_H_
