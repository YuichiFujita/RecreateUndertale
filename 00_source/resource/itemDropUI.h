//============================================================
//
//	破棄メニューヘッダー [itemDropUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ITEM_DROP_UI_H_
#define _ITEM_DROP_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "selectItemUI.h"

//************************************************************
//	クラス定義
//************************************************************
// 破棄メニュークラス
class CItemDropUI : public CItemUI
{
public:
	// コンストラクタ
	explicit CItemDropUI(const int nChoiceItemIdx, const int nChoiceBagIdx);

	// デストラクタ
	~CItemDropUI() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

private:
	// オーバーライド関数
	void NextText() override;	// テキストボックス進行
};

#endif	// _ITEM_DROP_UI_H_
