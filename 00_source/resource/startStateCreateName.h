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
class CCharState;	// 文字状態クラス

//************************************************************
//	クラス定義
//************************************************************
// 命名状態クラス
class CStartStateCreateName : public CStartState
{
public:
	// 横選択列挙
	enum ESelectX
	{
		XSELECT_LEFT = 0,	// 左
		XSELECT_CENTER,		// 中央
		XSELECT_RIGHT,		// 右
		XSELECT_MAX			// この列挙型の総数
	};

	// 縦選択列挙
	enum ESelectY
	{
		YSELECT_TOP = 0,	// 上
		YSELECT_CENTER,		// 中央
		YSELECT_BOTTOM,		// 下
		YSELECT_MAX			// この列挙型の総数
	};

	// 定数
	static constexpr int YSELECT_POLY_MAX = YSELECT_MAX - 1;

	// コンストラクタ
	CStartStateCreateName();

	// デストラクタ
	~CStartStateCreateName() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

	// メンバ関数
	HRESULT ChangeState(CCharState *pState);	// 状態変更

private:
	// メンバ関数
	void UpdateSelect(const float fDeltaTime);	// 選択更新
	void UpdateDecide(void);	// 決定更新

	// メンバ変数
	CString2D *m_apSelect[YSELECT_POLY_MAX][XSELECT_MAX];	// 選択肢
	CString2D *m_pTitle;	// タイトル
	CCharState *m_pState;	// 文字状態
	POSGRID2 m_curSelect;	// 現在の選択肢
	POSGRID2 m_oldSelect;	// 前回の選択肢
};

#endif	// _START_STATE_CREATE_NAME_H_
