//============================================================
//
//	アイテムメニューヘッダー [selectItemUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SELECT_ITEM_UI_H_
#define _SELECT_ITEM_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "menuSelectUI.h"

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス
class CItemUI;		// アイテムUIクラス

//************************************************************
//	クラス定義
//************************************************************
// アイテムメニュークラス
class CSelectItemUI : public CSelectUI
{
public:
	// 選択列挙
	enum ESelect
	{
		SELECT_USE = 0,	// 使用
		SELECT_INFO,	// 情報
		SELECT_DROP,	// 破棄
		SELECT_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CSelectItemUI(AFuncUninit funcUninit, CObject2D *pSoul);

	// デストラクタ
	~CSelectItemUI() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画
	void SetEnableDraw(const bool bDraw) override;	// 描画状況設定
	bool IsCreateOK() override;	// メニュー生成可能フラグ取得

private:
	// 状態列挙
	enum EState
	{
		STATE_ITEM = 0,	// アイテム選択状態
		STATE_ACT,		// 行動選択状態
		STATE_TEXT,		// テキスト表示状態
		STATE_MAX		// この列挙型の総数
	};

	// 表示テキスト列挙
	enum EText
	{
		TEXT_USE = 0,	// USE
		TEXT_INFO,		// INFO
		TEXT_DROP,		// DROP
		TEXT_MAX		// この列挙型の総数
	};

	// アイテム構造体
	struct SItem
	{
		// デフォルトコンストラクタ
		SItem() :
			pName	 (nullptr),	// アイテム名情報
			nItemIdx (0)		// アイテムインデックス
		{}

		// デストラクタ
		~SItem() {}

		// メンバ変数
		CString2D* pName;	// アイテム名情報
		int nItemIdx;		// アイテムインデックス
	};

	// メンバ関数
	void UpdateSelectItem();	// アイテム選択更新
	void UpdateDecideItem();	// アイテム決定更新
	void UpdateSelectAct();		// 行動選択更新
	void UpdateDecideAct();		// 行動決定更新

	// メンバ変数
	std::vector<SItem> m_vecItemName;	// アイテム情報
	CString2D* m_apSelect[SELECT_MAX];	// 選択情報
	CItemUI* m_pItemMenu;	// アイテムメニュー情報
	EState m_state;			// 状態
	int m_nCurSelectItem;	// 現在の選択アイテム
	int m_nCurSelectAct;	// 現在の選択行動
};

#endif	// _SELECT_ITEM_UI_H_
