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
#include "frameText2D.h"

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
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画
	void SetEnableDraw(const bool bDraw) override;	// 描画状況設定

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
		CString2D *m_pName;	// アイテム名情報
		int nItemID;		// アイテムインデックス
	};

	// メンバ関数
	void UpdateSelectItem(void);	// アイテム選択更新
	void UpdateDecideItem(void);	// アイテム決定更新
	void UpdateSelectAct(void);		// 行動選択更新
	void UpdateDecideAct(void);		// 行動決定更新

	// メンバ変数
	std::vector<SItem> m_vecItemName;	// アイテム情報
	CString2D *m_apSelect[SELECT_MAX];	// 選択情報
	CItemUI *m_pItemMenu;	// アイテムメニュー情報
	EState m_state;			// 状態
	int m_nCurSelectItem;	// 現在の選択アイテム
	int m_nCurSelectAct;	// 現在の選択行動
};

// アイテムUIクラス
class CItemUI : public CObject
{
public:
	// コンストラクタ
	explicit CItemUI(const int nChoiceItemIdx);

	// デストラクタ
	~CItemUI() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CItemUI *Create	// 生成
	( // 引数
		const CSelectItemUI::ESelect choiceAct,	// 選択中行動
		const int nChoiceItemIdx				// 選択中アイテムインデックス
	);

	// メンバ関数
	HRESULT PushFrontString(const std::string& rStr)	{ return m_pTextBox->PushFrontString(rStr); }	// 文字列の先頭追加 (マルチバイト文字列)
	HRESULT PushFrontString(const std::wstring& rStr)	{ return m_pTextBox->PushFrontString(rStr); }	// 文字列の先頭追加 (ワイド文字列)
	HRESULT PushBackString(const std::string& rStr)		{ return m_pTextBox->PushBackString(rStr); }	// 文字列の最後尾追加 (マルチバイト文字列)
	HRESULT PushBackString(const std::wstring& rStr)	{ return m_pTextBox->PushBackString(rStr); }	// 文字列の最後尾追加 (ワイド文字列)
	void DeleteString(const int nStrID)			{ m_pTextBox->DeleteString(nStrID); }		// 文字列削除
	void DeleteStringAll(void)					{ m_pTextBox->DeleteStringAll(); }			// 文字列全削除
	void ChangeTextBox(const AText& rText)		{ m_pTextBox->ChangeText(rText); }			// テキスト変更
	void SetTextBoxEnableDraw(const bool bDraw)	{ m_pTextBox->SetTextEnableDraw(bDraw); };	// 描画状況設定
	bool IsTextBoxScroll(void) const	{ return m_pTextBox->IsTextScroll(); }	// 文字送り状況取得
	int GetChoiceItemIdx(void) const	{ return m_nChoiceItemIdx; }			// 選択中アイテムインデックス取得
	int GetCurTextIdx(void) const		{ return m_nCurTextIdx; }				// 現在のテキストインデックス取得

protected:
	// 純粋仮想関数
	virtual void NextText(void) = 0 { m_nCurTextIdx++; }	// テキストボックス進行

private:
	// オーバーライド関数
	void Release(void) override { CObject::Release(); }	// 破棄

	// メンバ変数
	const int m_nChoiceItemIdx;	// 選択中アイテムインデックス
	CFrameText2D *m_pTextBox;	// テキストボックス情報
	int m_nCurTextIdx;			// 現在のテキストインデックス
};

#endif	// _SELECT_ITEM_UI_H_
