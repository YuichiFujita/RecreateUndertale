//============================================================
//
//	ひらがな状態ヘッダー [charStateHiragana.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _CHAR_STATE_HIRAGANA_H_
#define _CHAR_STATE_HIRAGANA_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "charState.h"

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// ひらがな状態クラス
class CCharStateHiragana : public CCharState
{
public:
	// コンストラクタ
	CCharStateHiragana();

	// デストラクタ
	~CCharStateHiragana() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ関数
	int GetSelectWidth(void)	{ return (int)m_vecSelect[0].size(); }	// 横の文字数取得
	int GetSelectHeight(void)	{ return (int)m_vecSelect.size(); }		// 縦の文字数取得
	void UpdateSelect(void);	// 選択更新
	void UpdateDecide(void);	// 決定更新
	HRESULT LoadArray(void);	// 配置読込

	// メンバ変数
	std::vector<std::vector<CString2D*>> m_vecSelect;	// 選択文字
	POSGRID2 m_selectMax;	// 選択文字の最大量
	POSGRID2 m_curSelect;	// 現在の選択文字
	POSGRID2 m_oldSelect;	// 前回の選択文字
};

#endif	// _CHAR_STATE_HIRAGANA_H_
