//============================================================
//
//	テキスト表示機能ヘッダー [frame2DModuleText.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_MODULE_TEXT_H_
#define _FRAME2D_MODULE_TEXT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DModule.h"
#include "frame2D.h"
#include "scrollText2D.h"

//************************************************************
//	前方宣言
//************************************************************
class CTextSave;		// 機能保存クラス
class CTextSaveText;	// テキスト機能保存クラス
class CTextSaveSelect;	// 選択付きテキスト機能保存クラス

//************************************************************
//	クラス定義
//************************************************************
// テキスト表示機能クラス
class CFrame2DModuleText : public CFrame2DModule
{
public:
	// コンストラクタ
	CFrame2DModuleText(const CFrame2D::EPreset preset);
	CFrame2DModuleText(const VECTOR3& rOffset);

	// デストラクタ
	~CFrame2DModuleText() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void SetPriority(const int nPriority) override;		// 優先順位設定
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	inline CFrame2DModuleText* GetModuleText() override { return this; }	// テキスト表示機能取得

	// メンバ関数
	void ChangeText(const AText& rText);	// テキスト変更
	void SetOffset(const VECTOR3& rOffset);	// テキストオフセット設定
	HRESULT BindText(const std::string& rPath, const std::string& rBoxKey, const std::string& rTextKey);	// テキスト割当
	inline HRESULT PushFrontString(const std::string& rStr)		{ return m_pText->PushFrontString(rStr); }	// 文字列の先頭追加 (マルチバイト文字列)
	inline HRESULT PushFrontString(const std::wstring& rStr)	{ return m_pText->PushFrontString(rStr); }	// 文字列の先頭追加 (ワイド文字列)
	inline HRESULT PushBackString(const std::string& rStr)		{ return m_pText->PushBackString(rStr); }	// 文字列の最後尾追加 (マルチバイト文字列)
	inline HRESULT PushBackString(const std::wstring& rStr)		{ return m_pText->PushBackString(rStr); }	// 文字列の最後尾追加 (ワイド文字列)
	inline void DeleteString(const int nStrIdx)			{ m_pText->DeleteString(nStrIdx); }		// 文字列削除
	inline void DeleteStringAll()						{ m_pText->DeleteStringAll(); }			// 文字列全削除
	inline void SetTextEnableDraw(const bool bDraw)		{ m_pText->SetEnableDraw(bDraw); };		// テキスト描画状況設定
	inline void SetTextEnableScroll(const bool bScroll)	{ m_pText->SetEnableScroll(bScroll); };	// テキスト文字送り状況設定
	inline bool IsTextScroll() const					{ return m_pText->IsScroll(); }			// テキスト文字送り状況取得
	inline bool IsTextEndScroll() const					{ return m_pText->IsEndScroll(); }		// テキスト文字送り終了状況取得
	inline VECTOR3 GetOffset() const					{ return m_offset; }					// テキストオフセット取得

protected:
	// メンバ関数
	bool IsNextTextBox(std::string* pPath, std::string* pBoxKey);		// 次テキストボックスがあるかの確認
	inline std::string GetNextPath() const	 { return m_sNextPath; }	// 次テキストボックスの保存パス取得
	inline std::string GetNextBoxKey() const { return m_sNextBoxKey; }	// 次テキストボックスの検索キー取得
	inline void SetNextPath(const std::string& rNextPath)		{ m_sNextPath = rNextPath; }		// 次テキストボックスの保存パス設定
	inline void SetNextBoxKey(const std::string& rNextBoxKey)	{ m_sNextBoxKey = rNextBoxKey; }	// 次テキストボックスの検索キー設定

private:
	// 仮想関数
	virtual void BindTextSave(CFrame2DModule* pModule, CTextSave* pText);	// 保存機能の割当

	// メンバ関数
	void SetPositionRelative();	// 相対位置設定
	CTextSave* LoadTextBox(const std::string& rPath, const std::string& rBoxKey, const std::string& rTextKey);	// テキストボックス読込
	CTextSave* LoadText(std::ifstream* pFile, const std::string& rTextKey);	// テキスト読込
	CTextSave* LoadString(std::ifstream* pFile);	// 文字列読込

	// メンバ変数
	CScrollText2D* m_pText;		// テキスト情報
	VECTOR3 m_offset;			// テキストオフセット
	std::string m_sNextPath;	// 次テキストボックスの保存パス
	std::string m_sNextBoxKey;	// 次テキストボックスの検索キー
	std::string m_sNextTextKey;	// 次テキストの検索キー
};

// 機能保存クラス
class CTextSave
{
public:
	// コンストラクタ
	CTextSave() {}

	// デストラクタ
	virtual ~CTextSave() {}

	// 純粋仮想関数
	virtual CFrame2DModule* CreateModule(const CFrame2D::EPreset preset) = 0;	// テキスト機能生成

	// 仮想関数
	virtual inline CTextSaveText* GetText()		{ return nullptr; }	// テキスト取得
	virtual inline CTextSaveSelect* GetSelect()	{ return nullptr; }	// 選択付きテキスト取得

	// TODO：各キーで読込情報がある場合はこれを派生クラスでoverride
	virtual inline void LoadKeyText(std::ifstream* /*pFile*/, std::string& /*rString*/)		{}	// 現在キーのテキスト読込
	virtual inline void LoadKeyString(std::ifstream* /*pFile*/, std::string& /*rString*/)	{}	// 現在キーの文字列読込

	// メンバ変数
	AText m_text;	// テキスト保存
};

// テキスト機能保存クラス
class CTextSaveText : public CTextSave
{
public:
	// コンストラクタ
	CTextSaveText() {}

	// デストラクタ
	~CTextSaveText() override {}

	// オーバーライド関数
	CFrame2DModule* CreateModule(const CFrame2D::EPreset preset) override;		// テキスト機能生成
	void LoadKeyString(std::ifstream* pFile, std::string& rString) override;	// 現在キーの文字列読込
	inline CTextSaveText* GetText() override { return this; }					// テキスト取得

	// メンバ変数
	std::string m_sNextTextKey;	// 次テキストの検索キー
};

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DModuleTextSelect.h"

#endif	// _FRAME2D_MODULE_TEXT_H_
