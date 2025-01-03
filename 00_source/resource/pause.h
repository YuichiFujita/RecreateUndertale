//============================================================
//
//	ポーズヘッダー [pause.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PAUSE_H_
#define _PAUSE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"

//************************************************************
//	前方宣言
//************************************************************
class CObject2D;	// オブジェクト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// ポーズクラス
class CPause
{
public:
	// 選択列挙
	enum ESelect
	{
		SELECT_RESUME = 0,	// 再開
		SELECT_RETRY,		// リトライ
		SELECT_EXIT,		// 終了
		SELECT_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CPause();

	// デストラクタ
	~CPause();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);	// 更新
	void Draw();							// 描画
	bool IsPause();							// ポーズ状況取得
	void SetEnableDraw(const bool bDraw);	// 描画状況設定

	// 静的メンバ関数
	static CPause* Create();				// 生成
	static void Release(CPause*& prPause);	// 破棄

#ifdef _DEBUG

	// メンバ関数
	void SetEnableDebugDisp(const bool bDisp);	// デバッグ表示状況設定
	bool IsDebugDisp() const;	// デバッグ表示状況取得

#endif	// _DEBUG

private:
	// メンバ関数
	void Select();	// 選択操作

	// メンバ変数
	CObject2D* m_apSelect[SELECT_MAX];	// 選択情報
	CObject2D* m_pBG;	// 背景情報
	int  m_nSelect;		// 現在の選択
	int  m_nOldSelect;	// 前回の選択
	bool m_bPause;		// ポーズ状況
};

#endif	// _PAUSE_H_
