//============================================================
//
//	命名状態ヘッダー [startStateCreateName.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _START_STATE_CREATE_NAME_H_
#define _START_STATE_CREATE_NAME_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "startState.h"

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// 命名状態クラス
class CStartStateCreateName : public CStartState
{
public:
	// コンストラクタ
	CStartStateCreateName();

	// デストラクタ
	~CStartStateCreateName() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// 選択列挙
	enum ESelect
	{
		SELECT_CLOSE = 0,	// 閉じる
		SELECT_MAX			// この列挙型の総数
	};

	// メンバ関数
	void UpdateSelect(void);	// 選択更新
	void UpdateDecide(void);	// 決定更新

	// メンバ変数
	CString2D *m_pTitle;	// タイトル
	int m_nCurSelect;		// 現在の選択肢
	int m_nOldSelect;		// 前回の選択肢
};

#endif	// _START_STATE_CREATE_NAME_H_
