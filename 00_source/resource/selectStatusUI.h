//============================================================
//
//	フルステータスメニューヘッダー [selectStatusUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SELECT_STATUS_UI_H_
#define _SELECT_STATUS_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "menuSelectUI.h"

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス
class CText2D;		// テキスト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// フルステータスメニュークラス
class CSelectStatusUI : public CSelectUI
{
public:
	// コンストラクタ
	CSelectStatusUI(AFuncUninit funcUninit, CObject2D* pSoul);

	// デストラクタ
	~CSelectStatusUI() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

private:
	// 表示テキスト列挙
	enum EText
	{
		TEXT_LV_HP = 0,	// LV/HP
		TEXT_ATK_DEF,	// ATK/DEF
		TEXT_EXP_NEXT,	// EXP/NEXT
		TEXT_WPN_AMR,	// WPN/AMR
		TEXT_GOLD,		// GOLD
		TEXT_KILLS,		// KILLS
		TEXT_MAX		// この列挙型の総数
	};

	// メンバ変数
	CString2D* m_pName;			// 名前情報
	CText2D* m_pLvHpTitle;		// LV/HPタイトル情報
	CText2D* m_pLvHpValue;		// LV/HP数値情報
	CText2D* m_pAtkDefTitle;	// ATK/DEFタイトル情報
	CText2D* m_pAtkDefValue;	// ATK/DEF数値情報
	CText2D* m_pExpNextTitle;	// EXP/NEXTタイトル情報
	CText2D* m_pExpNextValue;	// EXP/NEXT数値情報
	CText2D* m_pWpnAmrTitle;	// WPN/AMRタイトル情報
	CText2D* m_pWpnAmrName;		// WPN/AMR名称情報
	CString2D* m_pGoldTitle;	// GOLDタイトル情報
	CString2D* m_pGoldValue;	// GOLD数値情報
	CString2D* m_pKillsTitle;	// KILLSタイトル情報
	CString2D* m_pKillsValue;	// KILLS数値情報
};

#endif	// _SELECT_STATUS_UI_H_
