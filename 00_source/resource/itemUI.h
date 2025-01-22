//============================================================
//
//	アイテムUIヘッダー [itemUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ITEM_UI_H_
#define _ITEM_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2D.h"
#include "selectItemUI.h"

//************************************************************
//	クラス定義
//************************************************************
// アイテムUIクラス
class CItemUI : public CFrame2D
{
public:
	// コンストラクタ
	CItemUI(const CSelectItemUI::ESelect choiceAct, const int nChoiceItemIdx, const int nChoiceBagIdx);

	// デストラクタ
	~CItemUI() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CItemUI* Create	// 生成
	( // 引数
		const CSelectItemUI::ESelect choiceAct,	// 選択中行動
		const int nChoiceItemIdx,				// 選択中アイテムインデックス
		const int nChoiceBagIdx					// 選択中バッグインデックス
	);

private:
	// エイリアス定義
	typedef HRESULT(CItemUI::*AFuncInitText)();	// テキスト初期化関数ポインタ
	typedef HRESULT(CItemUI::*AFuncBindText)();	// テキスト割当関数ポインタ
	typedef void(CItemUI::*AFuncActItem)();		// アイテム行動関数ポインタ

	// 静的メンバ変数
	static AFuncInitText m_aFuncInitText[];	// テキスト初期化関数リスト
	static AFuncBindText m_aFuncBindText[];	// テキスト割当関数リスト
	static AFuncActItem	 m_aFuncActItem[];	// アイテム行動関数リスト

	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ関数
	HRESULT InitUseText();		// 使用テキスト初期化
	HRESULT InitInfoText();		// 情報テキスト初期化
	HRESULT InitDropText();		// 破棄テキスト初期化
	HRESULT BindUseText();		// 使用テキスト割当
	HRESULT BindInfoText();		// 情報テキスト割当
	HRESULT BindDropText();		// 破棄テキスト割当
	void ActUseItem();			// 選択アイテム使用行動
	void ActInfoItem();			// 選択アイテム情報行動
	void ActDropItem();			// 選択アイテム破棄行動
	bool IsModuleText() const;	// テキスト表示機能かの確認

	// メンバ変数
	const CSelectItemUI::ESelect m_choiceAct;	// 選択中行動
	const int m_nChoiceItemIdx;	// 選択中アイテムインデックス
	const int m_nChoiceBagIdx;	// 選択中バッグインデックス
};

#endif	// _ITEM_UI_H_
