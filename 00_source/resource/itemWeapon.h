//============================================================
//
//	武器アイテムヘッダー [itemWeapon.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ITEM_WEAPON_H_
#define _ITEM_WEAPON_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "item.h"

//************************************************************
//	クラス定義
//************************************************************
// 武器アイテム情報クラス
class CItemWeapon : public CItemData
{
public:
	// コンストラクタ
	CItemWeapon();

	// デストラクタ
	~CItemWeapon() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Use(const int nBagIdx) const override;	// アイテム使用
	std::string Detail() const override;		// アイテム詳細の文字列取得

private:
	// オーバーライド関数
	HRESULT LoadSetup(std::ifstream* pFile, std::string& rString) override;	// 種類ごとのセットアップ
};

#endif	// _ITEM_WEAPON_H_
