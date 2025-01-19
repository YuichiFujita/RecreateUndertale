//============================================================
//
//	使用メニューヘッダー [itemUseUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ITEM_USE_UI_H_
#define _ITEM_USE_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "selectItemUI.h"

//************************************************************
//	クラス定義
//************************************************************
// 使用メニュークラス
class CItemUseUI : public CItemUI
{
public:
	// コンストラクタ
	CItemUseUI(const int nChoiceItemIdx, const int nChoiceBagIdx);

	// デストラクタ
	~CItemUseUI() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画
};

#endif	// _ITEM_USE_UI_H_
