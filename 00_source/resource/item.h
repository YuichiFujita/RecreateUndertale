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
//	インクルードファイル
//************************************************************
#include "frame2DModuleText.h"

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
		TYPE_WEAPON,	// 武器
		TYPE_ARMOR,		// 防具
		TYPE_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CItemData();

	// デストラクタ
	virtual ~CItemData();

	// 純粋仮想関数
	virtual void Use(const int nBagIdx) const = 0;	// アイテム使用
	virtual HRESULT LoadSetup(std::ifstream* pFile, std::string& rString) = 0;	// 種類ごとのセットアップ

	// 仮想関数
	virtual HRESULT Init();	// 初期化
	virtual void Uninit();	// 終了
	virtual void Info(const int nBagIdx) const;	// アイテム情報
	virtual void Drop(const int nBagIdx) const;	// アイテム破棄
	virtual std::string Detail() const;			// アイテム詳細の文字列取得
	virtual std::string UseEnd() const;			// アイテム使用後の文字列取得
	virtual CFrame2DModuleText::ABuffTextArray CreateUseBuffTextArray() const;	// 初期使用テキストバッファ連想配列生成
	virtual CFrame2DModuleText::ABuffTextArray CreateInfoBuffTextArray() const;	// 初期情報テキストバッファ連想配列生成
	virtual CFrame2DModuleText::ABuffTextArray CreateDropBuffTextArray() const;	// 初期破棄テキストバッファ連想配列生成

	// 静的メンバ関数
	static CItemData* Create(const EType type);	// 生成

	// メンバ関数
	inline void SetDataPath(const std::string& rDataPath)	{ m_sDataPath = rDataPath; }	// アイテム情報パス設定
	inline std::string GetDataPath() const			{ return m_sDataPath; }		// アイテム情報パス取得
	inline void SetName(const std::string& rName)	{ m_sName = rName; }		// アイテム名設定
	inline std::string GetName() const				{ return m_sName; }			// アイテム名取得
	inline void SetAddAtk(const int nAddAtk)		{ m_nAddAtk = nAddAtk; }	// 攻撃力上昇量設定
	inline int GetAddAtk() const					{ return m_nAddAtk; }		// 攻撃力上昇量取得
	inline void SetAddDef(const int nAddDef)		{ m_nAddDef = nAddDef; }	// 防御力上昇量設定
	inline int GetAddDef() const					{ return m_nAddDef; }		// 防御力上昇量取得

private:
	// メンバ変数
	std::string m_sDataPath;	// アイテム情報パス
	std::string m_sName;		// アイテム名
	int m_nAddAtk;				// 攻撃力上昇量
	int m_nAddDef;				// 防御力上昇量
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
	const CItemData& GetInfo(const int nIdx);			// アイテム情報取得 (インデックス)
	const CItemData& GetInfo(const std::string& rPath);	// アイテム情報取得 (パス)

	// 静的メンバ関数
	static CItem* Create();					// 生成
	static void Release(CItem*& prItem);	// 破棄

private:
	// メンバ関数
	HRESULT LoadSetup();	// セットアップ
	CItemData* LoadDataSetup(const char* pDataPath);	// アイテム情報セットアップ

	// メンバ変数
	std::vector<CItemData*> m_vecItemData;	// アイテム動的配列
};

#endif	// _ITEM_H_
