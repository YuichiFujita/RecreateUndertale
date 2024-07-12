//============================================================
//
//	ステータスメニューヘッダー [menuStatusUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _MENU_STATUS_UI_H_
#define _MENU_STATUS_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"

//************************************************************
//	前方宣言
//************************************************************
class CFrame2D;		// フレーム2Dクラス
class CString2D;	// 文字列2Dクラス
class CText2D;		// テキスト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// ステータスメニュークラス
class CMenuStatusUI : public CObject
{
public:
	// コンストラクタ
	CMenuStatusUI();

	// デストラクタ
	~CMenuStatusUI() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CMenuStatusUI *Create(void);	// 生成

private:
	// オーバーライド関数
	void Release(void) override { CObject::Release(); }	// 破棄

	// メンバ変数
	CFrame2D *m_pFrame;	// フレーム情報
	CString2D *m_pName;	// 名前情報
	CText2D *m_pStatus;	// ステータス情報
	CText2D *m_pValue;	// ステータス数値情報
};

#endif	// _MENU_STATUS_UI_H_
