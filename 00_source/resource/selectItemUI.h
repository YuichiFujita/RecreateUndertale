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
class CFrameText2D;	// フレームテキスト2Dクラス
class CString2D;	// 文字列2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// アイテムメニュークラス
class CSelectItemUI : public CSelect
{
public:
	// コンストラクタ
	CSelectItemUI(AFuncUninit funcUninit, CObject2D *pSoul);

	// デストラクタ
	~CSelectItemUI() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

private:
	// 選択列挙
	enum ESelect
	{
		SELECT_USE = 0,	// 使用
		SELECT_INFO,	// 情報
		SELECT_DROP,	// 破棄
		SELECT_MAX		// この列挙型の総数
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
		CString2D *m_pName;	// アイテム名情報
		int nItemID;		// アイテムインデックス
	};

	// メンバ関数
	void UpdateSelectItem(void);	// アイテム選択更新
	void UpdateDecideItem(void);	// アイテム決定更新
	void UpdateSelect(void);		// 選択更新
	void UpdateDecide(void);		// 決定更新

	// メンバ変数
	std::vector<SItem> m_vecItemName;	// アイテム情報
	CString2D *m_apSelect[SELECT_MAX];	// 選択情報
	CFrameText2D *m_pTextBox;			// テキストボックス情報
	SItem *m_pSelectItem;	// 選択中アイテム情報		// TODO：アイテム選択中かはインデックスでの管理にしよう
	int m_nCurTextIdx;		// 現在のテキストインデックス
	int m_nCurSelectItem;	// 現在の選択アイテム
	int m_nCurSelect;		// 現在の選択肢
};

#endif	// _SELECT_ITEM_UI_H_
