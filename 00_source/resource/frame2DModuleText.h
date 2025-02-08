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

//************************************************************
//	前方宣言
//************************************************************
class CFrame2DTextState;	// テキスト機能状態クラス
class CFrame2DTextBuffer;	// テキスト情報保存バッファクラス

//************************************************************
//	クラス定義
//************************************************************
// テキスト表示機能クラス
class CFrame2DModuleText : public CFrame2DModule
{
public:
	// エイリアス定義
	using AMapBuffText = std::map<std::string, CFrame2DTextBuffer*>;	// テキストバッファ連想配列型

	// コンストラクタ
	CFrame2DModuleText(const bool bAutoUninit = true);

	// デストラクタ
	~CFrame2DModuleText() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void SetPriority(const int nPriority) override;		// 優先順位設定
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	inline CFrame2DModuleText* GetModuleText() override	{ return this; }	// テキスト表示機能取得

	// メンバ関数
	void BindBuffTextArray(AMapBuffText* pMapBuffText, const std::string& rFilePath, const std::string& rBoxKey, const std::string& rStartKey = "0");	// テキストバッファ連想配列割当
	HRESULT BindTextBox(const std::string& rFilePath, const std::string& rBoxKey);	// テキストボックス割当
	HRESULT BindText(const std::string& rTextKey);		// テキスト割当
	HRESULT TransText(const std::string& rNextTextKey);	// テキスト遷移
	HRESULT ChangeState(CFrame2DTextState* pState);		// 状態変更
	inline CFrame2DTextState* GetState() const { return m_pState; }	// 状態取得

	HRESULT PushFrontString(const std::string& rStr, const std::string& rTextKey);	// 文字列の先頭追加 (マルチバイト文字列)
	HRESULT PushFrontString(const std::wstring& rStr, const std::string& rTextKey);	// 文字列の先頭追加 (ワイド文字列)
	HRESULT PushBackString(const std::string& rStr, const std::string& rTextKey);	// 文字列の最後尾追加 (マルチバイト文字列)
	HRESULT PushBackString(const std::wstring& rStr, const std::string& rTextKey);	// 文字列の最後尾追加 (ワイド文字列)
	int GetNumString(const std::string& rTextKey) const;	// 行数取得
	int GetNumText() const;	// テキスト数取得

private:
	// メンバ関数
	void ReleaseBuffText();	// テキストバッファ連想配列破棄
	CFrame2DTextBuffer* CreateBuffText(const std::string& rCreateKey, const int nFaceIdx);	// テキストバッファ生成
	bool LoadTextBox(const std::string& rFilePath, const std::string& rBoxKey);	// テキストボックス読込
	bool LoadText(std::ifstream* pFile, const std::string& rFilePath);			// テキスト読込
	CFrame2DTextBuffer* LoadString(std::ifstream* pFile, const int nFaceIdx);	// 文字列読込

	// メンバ変数
	CFrame2DTextState* m_pState;	// 状態
	AMapBuffText* m_pMapBuffText;	// テキストバッファ連想配列
	std::string m_sNextPath;		// 次テキストボックスの保存パス
	std::string m_sNextBoxKey;		// 次テキストボックスの検索キー
	std::string m_sStartKey;		// テキストボックスのテキスト開始キー
	bool m_bAutoUninitFrame;		// フレーム自動破棄フラグ
};

#endif	// _FRAME2D_MODULE_TEXT_H_
