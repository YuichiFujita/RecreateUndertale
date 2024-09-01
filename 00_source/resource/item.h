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
//	前方宣言
//************************************************************
class CItemData;	// アイテム情報クラス

//************************************************************
//	クラス定義
//************************************************************
// アイテムクラス
class CItem
{
public:
	// 種類列挙
	enum EType
	{
		TYPE_CANDY_MONSTER = 0,	// モンスターあめ
		TYPE_MAX				// この列挙型の総数
	};

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

	// メンバ変数
	CItemData *m_apItemData[TYPE_MAX];	// アイテム配列
};

// アイテム情報クラス
class CItemData
{
public:
	// コンストラクタ
	CItemData();

	// デストラクタ
	virtual ~CItemData();

	// 純粋仮想関数
	virtual HRESULT Init(void)	= 0;	// 初期化
	virtual void Uninit(void)	= 0;	// 終了
	virtual void Use(void)		= 0;	// アイテム使用
	virtual void Info(void)		= 0;	// アイテム情報
	virtual void Drop(void)		= 0;	// アイテム破棄

	// 静的メンバ関数
	static CItemData *Create(void);				// 生成
	static void Release(CItemData *&pItemData);	// 破棄

	// メンバ関数
	void SetName(const char* pName) { m_sName = pName; }	// アイテム名設定

private:
	// メンバ変数
	std::string m_sName;	// アイテム名
	std::vector<std::vector<std::string>> m_vecUse;		// 使用テキスト
	std::vector<std::vector<std::string>> m_vecInfo;	// 情報テキスト
};

#endif	// _ITEM_H_
