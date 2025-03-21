//============================================================
//
//	初期設定状態ヘッダー [startStateOption.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _START_STATE_OPTION_H_
#define _START_STATE_OPTION_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "startState.h"

//************************************************************
//	前方宣言
//************************************************************
class COptionManager;	// 設定マネージャークラス

//************************************************************
//	クラス定義
//************************************************************
// 初期設定状態クラス
class CStartStateOption : public CStartState
{
public:
	// コンストラクタ
	CStartStateOption();

	// デストラクタ
	~CStartStateOption() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ変数
	COptionManager* m_pOptionManager;	// 設定マネージャー
};

#endif	// _START_STATE_OPTION_H_
