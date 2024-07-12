//============================================================
//
//	セレクトメニューヘッダー [menuSelectUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _MENU_SELECT_UI_H_
#define _MENU_SELECT_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"

//************************************************************
//	前方宣言
//************************************************************
class CFrame2D;		// フレーム2Dクラス
class CString2D;	// 文字列2Dクラス
class CObject2D;	// オブジェクト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// セレクトメニュークラス
class CMenuSelectUI : public CObject
{
public:
	// コンストラクタ
	CMenuSelectUI();

	// デストラクタ
	~CMenuSelectUI() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CMenuSelectUI *Create(void);	// 生成

private:
	// 選択列挙
	enum ESelect
	{
		SELECT_ITEM = 0,	// アイテム
		SELECT_STATUS,		// ステータス
		SELECT_PHONE,		// 電話
		SELECT_MAX			// この列挙型の総数
	};

	// オーバーライド関数
	void Release(void) override { CObject::Release(); }	// 破棄

	// メンバ関数
	void UpdateSelect(void);	// 選択更新
	void UpdateDecide(void);	// 決定更新

	// メンバ変数
	CString2D *m_apSelect[SELECT_MAX];	// 選択肢情報
	CFrame2D *m_pFrame;	// フレーム情報
	CObject2D *m_pSoul;	// ソウルカーソル情報
	int m_nCurSelect;	// 現在の選択肢
};

#endif	// _MENU_SELECT_UI_H_
