//============================================================
//
//	特殊効果なしアイテムヘッダー [itemNone.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ITEM_NONE_H_
#define _ITEM_NONE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "item.h"

//************************************************************
//	クラス定義
//************************************************************
// 特殊効果なしアイテム情報クラス
class CItemNone : public CItemData
{
public:
	// コンストラクタ
	CItemNone();

	// デストラクタ
	~CItemNone() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Use() const override;	// アイテム使用
	void Info() const override;	// アイテム情報
	void Drop() const override;	// アイテム破棄
	std::string Detail() const override;	// アイテム詳細の文字列取得

private:
	// オーバーライド関数
	HRESULT LoadSetup(std::ifstream* pFile, std::string& rString) override;	// 種類ごとのセットアップ

	// メンバ変数

};

#endif	// _ITEM_NONE_H_
