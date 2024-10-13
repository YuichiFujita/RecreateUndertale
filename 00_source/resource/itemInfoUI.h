//============================================================
//
//	情報メニューヘッダー [itemInfoUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ITEM_INFO_UI_H_
#define _ITEM_INFO_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "selectItemUI.h"

//************************************************************
//	クラス定義
//************************************************************
// 情報メニュークラス
class CItemInfoUI : public CItemUI
{
public:
	// コンストラクタ
	explicit CItemInfoUI(const int nChoiceItemIdx);

	// デストラクタ
	~CItemInfoUI() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

private:
	// オーバーライド関数
	void NextText(void) override;	// テキストボックス進行
};

#endif	// _ITEM_INFO_UI_H_
