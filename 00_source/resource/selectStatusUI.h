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
class CSelectStatusUI : public CSelect
{
public:
	// コンストラクタ
	CSelectStatusUI(AFuncUninit funcUninit, CObject2D *pSoul);

	// デストラクタ
	~CSelectStatusUI() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

private:
	// メンバ変数
	CString2D *m_pName;		// 名前情報
	CText2D *m_pLvHpTitle;	// レベル/HPタイトル情報
	CText2D *m_pLvHpValue;	// レベル/HP数値情報
};

#endif	// _SELECT_STATUS_UI_H_
