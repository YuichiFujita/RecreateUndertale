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
	void UpdateShakeName(const float fDeltaTime);	// 名前振動更新

	// メンバ変数
	CString2D *m_apSelect[SELECT_MAX];	// 選択肢
	CText2D *m_pTitle;		// タイトル
	CString2D *m_pName;		// 名前
	int m_nCurSelect;		// 現在の選択肢
	int m_nOldSelect;		// 前回の選択肢
	float m_fCurTimeShake;	// 現在の振動の経過時間
	float m_fCurTimeMove;	// 現在の移動の経過時間

	float f;

private:
	// 状態列挙
	enum EState
	{
		STATE_NONE = 0,	// 何もしない状態
		STATE_MOVE,		// 名前の移動状態
		STATE_MAX		// この列挙型の総数
	};

	// メンバ関数
	void StateUpdateNone(const float fDeltaTime);	// 何もしない状態更新
	void StateUpdateMove(const float fDeltaTime);	// 名前の移動状態更新

	// メンバ変数
	EState m_state;	// 状態

	// 状態更新の関数ポインタ型エイリアス定義
	typedef void (CStartStateDecideName::*AFuncState)(const float);

	// 状態ごとの更新関数ポインタ
	static constexpr AFuncState FUNC_STATE[] =
	{
		&CStartStateDecideName::StateUpdateNone,	// 何もしない状態更新
		&CStartStateDecideName::StateUpdateMove,	// 名前の移動状態更新
	};

	// スタティックアサート
	static_assert(NUM_ARRAY(FUNC_STATE) == STATE_MAX, "ERROR : Func Count Mismatch");
};

#endif	// _START_STATE_DECIDE_NAME_H_
