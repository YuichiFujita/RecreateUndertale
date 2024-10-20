//============================================================
//
//	チュートリアル状態ヘッダー [startStateTutorial.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _START_STATE_TUTORIAL_H_
#define _START_STATE_TUTORIAL_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "startState.h"

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス
class CText2D;		// テキスト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// チュートリアル状態クラス
class CStartStateTutorial : public CStartState
{
public:
	// コンストラクタ
	CStartStateTutorial();

	// デストラクタ
	~CStartStateTutorial() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// 選択列挙
	enum ESelect
	{
		SELECT_START = 0,	// ゲーム開始
		SELECT_OPTION,		// 初期設定z
		SELECT_MAX			// この列挙型の総数
	};

	// メンバ関数
	void UpdateSelect(void);	// 選択更新
	void UpdateDecide(void);	// 決定更新

	// メンバ変数
	CString2D* m_apSelect[SELECT_MAX];	// 選択肢
	CText2D*   m_pCont;		// 操作説明
	CString2D* m_pTitle;	// タイトル
	CString2D* m_pRule;		// ゲーム概要
	CString2D* m_pVersion;	// バージョン表記
	int m_nCurSelect;		// 現在の選択肢
	int m_nOldSelect;		// 前回の選択肢
};

#endif	// _START_STATE_TUTORIAL_H_
