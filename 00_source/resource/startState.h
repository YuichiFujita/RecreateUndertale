//============================================================
//
//	スタート状態ヘッダー [startState.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _START_STATE_H_
#define _START_STATE_H_

//************************************************************
//	前方宣言
//************************************************************
class CStartManager;	// スタートマネージャークラス

//************************************************************
//	クラス定義
//************************************************************
// スタート状態クラス
class CStartState
{
public:
	// コンストラクタ
	CStartState();

	// デストラクタ
	virtual ~CStartState();

	// 純粋仮想関数
	virtual HRESULT Init(void)	= 0;	// 初期化
	virtual void Uninit(void)	= 0;	// 終了
	virtual void Update(const float fDeltaTime) = 0;	// 更新

	// メンバ関数
	void SetContext(CStartManager *pContext) { m_pContext = pContext; }	// コンテキスト設定

protected:
	// メンバ変数
	CStartManager *m_pContext;	// コンテキスト
};

//************************************************************
//	インクルードファイル
//************************************************************
#include "startStateLogo.h"
#include "startStateTutorial.h"
#include "startStateOption.h"
#include "startStateCreateName.h"
#include "startStateDecideName.h"

#endif	// _START_STATE_H_
