//============================================================
//
//	名前決定状態ヘッダー [startStateDecideName.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _START_STATE_DECIDE_NAME_H_
#define _START_STATE_DECIDE_NAME_H_

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
// 名前決定状態クラス
class CStartStateDecideName : public CStartState
{
public:
	// コンストラクタ
	CStartStateDecideName();

	// デストラクタ
	~CStartStateDecideName() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// 選択列挙
	enum ESelect
	{
		SELECT_NO = 0,	// いいえ
		SELECT_YES,		// はい
		SELECT_MAX		// この列挙型の総数
	};

	// メンバ関数
	void UpdateSelect(void);	// 選択更新
	void UpdateDecide(void);	// 決定更新
	void ShakeName(const float fDeltaTime);	// 名前振動
	void MoveName(const float fDeltaTime);	// 名前移動

	// メンバ変数
	CString2D *m_apSelect[SELECT_MAX];	// 選択肢
	CText2D *m_pTitle;		// タイトル
	CString2D *m_pName;		// 名前
	int m_nCurSelect;		// 現在の選択肢
	int m_nOldSelect;		// 前回の選択肢
	float m_fCurTimeShake;	// 現在の振動の経過時間
	float m_fCurTimeMove;	// 現在の移動の経過時間
	float m_fNameDestPosX;	// 名前の目標位置X
	bool m_bMove;			// 名前の移動状況
};

#endif	// _START_STATE_DECIDE_NAME_H_
