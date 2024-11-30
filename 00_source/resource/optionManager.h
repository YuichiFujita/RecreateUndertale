//============================================================
//
//	設定マネージャーヘッダー [optionManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _OPTION_MANAGER_H_
#define _OPTION_MANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// 設定マネージャークラス
class COptionManager
{
public:
	// 表示テキスト列挙
	enum EText
	{
		TEXT_TITLE = 0,	// せってい
		TEXT_CLOSE,		// とじる
		TEXT_MAX		// この列挙型の総数
	};

	// コンストラクタ
	COptionManager();

	// デストラクタ
	~COptionManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	bool Update(const float fDeltaTime);	// 更新

	// 静的メンバ関数
	static COptionManager* Create();	// 生成
	static void Release(COptionManager*& prOptionManager);	// 破棄

private:
	// 選択列挙
	enum ESelect
	{
		SELECT_CLOSE = 0,	// 閉じる
		SELECT_MAX			// この列挙型の総数
	};

	// メンバ関数
	void UpdateSelect();	// 選択更新
	bool UpdateDecide();	// 決定更新

	// メンバ変数
	CString2D* m_apSelect[SELECT_MAX];	// 選択肢
	CString2D* m_pTitle;	// タイトル
	int m_nCurSelect;		// 現在の選択肢
	int m_nOldSelect;		// 前回の選択肢
};

#endif	// _OPTION_MANAGER_H_
