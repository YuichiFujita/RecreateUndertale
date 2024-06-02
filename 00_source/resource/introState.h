//============================================================
//
//	イントロ状態ヘッダー [introState.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _INTRO_STATE_H_
#define _INTRO_STATE_H_

//************************************************************
//	前方宣言
//************************************************************
class CIntroManager;	// イントロマネージャークラス

//************************************************************
//	クラス定義
//************************************************************
// イントロ状態クラス
class CIntroState
{
public:
	// コンストラクタ
	CIntroState();

	// デストラクタ
	virtual ~CIntroState();

	// 純粋仮想関数
	virtual HRESULT Init(void)	= 0;	// 初期化
	virtual void Uninit(void)	= 0;	// 終了
	virtual void Update(const float fDeltaTime) = 0;	// 更新

	// メンバ関数
	void SetContext(CIntroManager *pContext) { m_pContext = pContext; }	// コンテキスト設定

protected:
	// メンバ変数
	CIntroManager *m_pContext;	// コンテキスト
};

//************************************************************
//	インクルードファイル
//************************************************************
#include "introStateLogo.h"
#include "introStateText.h"
#include "introStateWait.h"
#include "introStateScroll.h"
#include "introStateEnd.h"

#endif	// _INTRO_STATE_H_
