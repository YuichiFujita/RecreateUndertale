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
	// 定数
	static constexpr int SELECT_Y_MAX = 2;	// 選択肢の縦の最大数
	static constexpr int SELECT_X_MAX = 3;	// 選択肢の横の最大数

	// コンストラクタ
	CStartStateCreateName();

	// デストラクタ
	~CStartStateCreateName() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ関数
	void UpdateSelect(void);	// 選択更新
	void UpdateDecide(void);	// 決定更新

	// メンバ変数
	CString2D *m_apSelect[SELECT_Y_MAX][SELECT_X_MAX];	// 選択肢
	CString2D *m_pTitle;	// タイトル
};

#endif	// _START_STATE_CREATE_NAME_H_
