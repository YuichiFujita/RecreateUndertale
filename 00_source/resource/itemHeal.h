//============================================================
//
//	回復アイテムヘッダー [itemHeal.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ITEM_HEAL_H_
#define _ITEM_HEAL_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "item.h"

//************************************************************
//	クラス定義
//************************************************************
// 回復アイテム情報クラス
class CItemHeal : public CItemData
{
public:
	// コンストラクタ
	CItemHeal();

	// デストラクタ
	~CItemHeal() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Use() const override;	// アイテム使用
	void Info() const override;	// アイテム情報
	void Drop() const override;	// アイテム破棄
	std::string Detail() const override;	// アイテム詳細の文字列取得
	std::string UseEnd() const override;	// アイテム使用後の文字列取得

private:
	// オーバーライド関数
	HRESULT LoadSetup(std::ifstream* pFile, std::string& rString) override;	// 種類ごとのセットアップ

	// メンバ変数
	int m_nHeal;	// 回復量
	bool m_bUseEnd;	// 使用後の文字表示フラグ
};

#endif	// _ITEM_HEAL_H_
