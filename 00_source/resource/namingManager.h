//============================================================
//
//	命名マネージャーヘッダー [namingManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _NAMING_MANAGER_H_
#define _NAMING_MANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CStartStateCreateName;	// 命名状態クラス
class CString2D;				// 文字列2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// 命名マネージャークラス
class CNamingManager
{
public:
	// 文字種類列挙
	enum ETypeChar
	{
		TYPECHAR_HIRAGANA = 0,	// ひらがな
		TYPECHAR_KATAKANA,		// カタカナ
		TYPECHAR_ALPHABET,		// アルファベット
		TYPECHAR_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CNamingManager();

	// デストラクタ
	~CNamingManager();

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(const float fDeltaTime);			// 更新
	HRESULT ChangeChar(const ETypeChar typeChar);	// 文字変更

	// 静的メンバ関数
	static CNamingManager *Create(void);	// 生成
	static void Release(CNamingManager *&prNamingManager);	// 破棄

private:
	// メンバ関数
	int GetSelectWidth(void)	{ return (int)m_vecSelect[0].size(); }	// 横の文字数取得
	int GetSelectHeight(void)	{ return (int)m_vecSelect.size(); }		// 縦の文字数取得
	void UpdateSelect(void);	// 選択更新
	void UpdateDecide(void);	// 決定更新
	HRESULT LoadArray(const ETypeChar typeChar);	// 配置読込

	// メンバ変数
	std::vector<std::vector<CString2D*>> m_vecSelect;	// 選択文字
	POSGRID2 m_curSelect;	// 現在の選択文字
	POSGRID2 m_oldSelect;	// 前回の選択文字
};

#endif	// _NAMING_MANAGER_H_
