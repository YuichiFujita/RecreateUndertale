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
	// 文字種類列挙
	enum ETypeChar
	{
		TYPECHAR_HIRAGANA = 0,	// ひらがな
		TYPECHAR_KATAKANA,		// カタカナ
		TYPECHAR_ALPHABET,		// アルファベット
		TYPECHAR_MAX			// この列挙型の総数
	};

	// 列選択列挙
	enum ESelectX
	{
		XSELECT_LEFT = 0,	// 左
		XSELECT_CENTER,		// 中央
		XSELECT_RIGHT,		// 右
		XSELECT_MAX			// この列挙型の総数
	};

	// 行選択列挙
	enum ESelectY
	{
		YSELECT_CHAR_CHANGE,	// 文字変更
		YSELECT_CHAR_DECIDE,	// 文字決定
		YSELECT_MAX				// この列挙型の総数
	};

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
	void ControlSelect(void);	// 選択操作
	void UpdateSelect(void);	// 選択更新
	void UpdateDecide(void);	// 決定更新
	HRESULT ChangeChar(const ETypeChar typeChar);	// 文字変更
	HRESULT LoadArray(const ETypeChar typeChar);	// 配置読込

	// メンバ変数
	std::vector<std::vector<CString2D*>> m_vecSelect;	// 選択文字
	CString2D *m_pTitle;	// タイトル
	CString2D *m_pName;		// 名前
	POSGRID2 m_curSelect;	// 現在の選択肢
	POSGRID2 m_oldSelect;	// 前回の選択肢
};

#endif	// _START_STATE_CREATE_NAME_H_
