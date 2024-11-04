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
	virtual void Use() const	= 0;	// アイテム使用
	virtual void Info() const	= 0;	// アイテム情報
	virtual void Drop() const	= 0;	// アイテム破棄

	// 仮想関数
	virtual HRESULT Init();	// 初期化
	virtual void Uninit();	// 終了
	virtual std::string Detail() const;	// アイテム詳細取得

	// 静的メンバ関数
	static CItemData* Create(const EType type);	// 生成

	// メンバ関数
	inline void SetName(const char* pName)			{ m_sName = pName; }		// アイテム名設定
	inline const char* GetName() const				{ return m_sName.c_str(); }	// アイテム名取得
	inline void SetUse(const ATextBox& rVecUse)		{ m_vecUse = rVecUse; }		// 使用テキスト設定
	inline const ATextBox& GetUse() const			{ return m_vecUse; }		// 使用テキスト取得
	inline void SetInfo(const ATextBox& rVecInfo)	{ m_vecInfo = rVecInfo; }	// 情報テキスト設定
	inline const ATextBox& GetInfo() const			{ return m_vecInfo; }		// 情報テキスト取得

	// TODO：DropText取得の作成
	// TODO：UnityみたいにGetComponentで各子クラスにできるようにしよう。
	//		 typeid使えば本当に型が変換後かの確認もできるし、ダメな時は関数呼ばなければいいしね

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
	HRESULT Init();		// アイテム初期化
	void Uninit();		// アイテム終了
	HRESULT LoadAll();	// アイテム全読込
	const CItemData& GetInfo(const int nIdx);	// アイテム情報取得

	// 静的メンバ関数
	static CItem* Create();					// 生成
	static void Release(CItem*& prItem);	// 破棄

private:
	// メンバ関数
	HRESULT LoadSetup();	// セットアップ
	ATextBox LoadText(std::ifstream& rFile, const char* pEndStr, const CItemData& rItem);	// テキストセットアップ
	void ReplaceCommand(std::string* pStr, const CItemData& rItem);	// 文字列内のコマンドの置換

	// メンバ変数
	std::vector<CItemData*> m_vecItemData;	// アイテム動的配列
};

#endif	// _ITEM_H_
