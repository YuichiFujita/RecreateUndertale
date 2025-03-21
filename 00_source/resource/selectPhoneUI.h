//============================================================
//
//	電話メニューヘッダー [selectPhoneUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SELECT_PHONE_UI_H_
#define _SELECT_PHONE_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "menuSelectUI.h"

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// 電話メニュークラス
class CSelectPhoneUI : public CSelectUI
{
public:
	// コンストラクタ
	CSelectPhoneUI(AFuncUninit funcUninit, CObject2D* pSoul);

	// デストラクタ
	~CSelectPhoneUI() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画
	bool IsCreateOK() override;	// メニュー生成可能フラグ取得

private:
	// メンバ変数

};

#endif	// _SELECT_PHONE_UI_H_
