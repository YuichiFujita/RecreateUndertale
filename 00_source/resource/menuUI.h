//============================================================
//
//	フィールドメニューヘッダー [menuUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _MENU_UI_H_
#define _MENU_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"
#include "menuSelectUI.h"

//************************************************************
//	前方宣言
//************************************************************
class CMenuStatusUI;	// ステータスメニュークラス

//************************************************************
//	クラス定義
//************************************************************
// フィールドメニュークラス
class CMenuUI : public CObject
{
public:
	// 表示テキスト列挙
	enum EText
	{
		TEXT_MINI_STATUS = 0,	// ミニステータス表示
		TEXT_ITEM,				// ITEM
		TEXT_STATUS,			// STAT
		TEXT_PHONE,				// PHONE
		TEXT_MAX				// この列挙型の総数
	};

	// コンストラクタ
	CMenuUI();

	// デストラクタ
	~CMenuUI() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CMenuUI* Create();	// 生成

	// メンバ関数
	inline bool IsChoiceSelect() const { return m_pSelectMenu->IsChoiceSelect(); }	// 選択中状況取得

private:
	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ変数
	CMenuStatusUI* m_pStatusMenu;	// ステータスメニュー情報
	CMenuSelectUI* m_pSelectMenu;	// セレクトメニュー情報
};

#endif	// _MENU_UI_H_
