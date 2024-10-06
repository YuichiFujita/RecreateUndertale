//============================================================
//
//	アイテムヘッダー [item.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ITEM_H_
#define _ITEM_H_

//************************************************************
//	クラス定義
//************************************************************
// アイテム情報クラス
class CItemData
{
public:
	// 種類列挙
	enum EType
	{
		TYPE_NONE = 0,	// 特殊効果なし
		TYPE_HEAL,		// HP関与
		TYPE_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CItemData();

	// デストラクタ
	virtual ~CItemData();

	// 純粋仮想関数
	virtual void Use(void) const	= 0;	// アイテム使用
	virtual void Info(void) const	= 0;	// アイテム情報
	virtual void Drop(void) const	= 0;	// アイテム破棄

	// 仮想関数
	virtual HRESULT Init(void);	// 初期化
	virtual void Uninit(void);	// 終了

	// 静的メンバ関数
	static CItemData *Create(const EType type);	// 生成

	// メンバ関数
	void SetName(const char* pName)			{ m_sName = pName; }		// アイテム名設定
	const char* GetName(void) const			{ return m_sName.c_str(); }	// アイテム名取得
	void SetUse(const ATextBox& rVecUse)	{ m_vecUse = rVecUse; }		// 使用テキスト設定
	const ATextBox& GetUse(void) const		{ return m_vecUse; }		// 使用テキスト取得
	void SetInfo(const ATextBox& rVecInfo)	{ m_vecInfo = rVecInfo; }	// 情報テキスト設定
	const ATextBox& GetInfo(void) const		{ return m_vecInfo; }		// 情報テキスト取得

private:
	// メンバ変数
	std::string m_sName;	// アイテム名
	ATextBox m_vecUse;		// 使用テキスト
	ATextBox m_vecInfo;		// 情報テキスト
};

// アイテムクラス
class CItem
{
public:
	// コンストラクタ
	CItem();

	// デストラクタ
	~CItem();

	// メンバ関数
	HRESULT Init(void);		// アイテム初期化
	void Uninit(void);		// アイテム終了
	HRESULT LoadAll(void);	// アイテム全読込
	const CItemData& GetInfo(const int nID);	// アイテム情報取得

	// 静的メンバ関数
	static CItem *Create(void);			// 生成
	static void Release(CItem *&pItem);	// 破棄

private:
	// メンバ関数
	HRESULT LoadSetup(void);	// セットアップ
	ATextBox LoadText(std::ifstream& rFile, const char *pEndStr);	// テキストセットアップ

	// メンバ変数
	std::vector<CItemData*> m_vecItemData;	// アイテム動的配列
};

#endif	// _ITEM_H_
