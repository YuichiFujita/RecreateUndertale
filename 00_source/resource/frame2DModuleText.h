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
	HRESULT BindTextBox(const std::string& rFilePath, const std::string& rBoxKey, const std::string& rNextStartKey = "0");	// テキストボックス割当
	void TransText(const std::string& rNextTextKey);				// テキスト遷移
	HRESULT ChangeState(CFrame2DTextState* pState);					// 状態変更
	inline CFrame2DTextState* GetState() const { return m_pState; }	// 状態取得

private:
	// メンバ関数
	HRESULT BindText(const std::string& rTextKey);	// テキスト割当
	void DeleteBuffText();							// テキストバッファ連想配列削除
	CFrame2DTextBuffer* CreateBuffText(const std::string& rCreateKey);				// テキストバッファ生成
	HRESULT LoadTextBox(const std::string& rFilePath, const std::string& rBoxKey);	// テキストボックス読込
	void LoadText(std::ifstream* pFile);					// テキスト読込
	CFrame2DTextBuffer* LoadString(std::ifstream* pFile);	// 文字列読込

	// メンバ変数
	std::map<std::string, CFrame2DTextBuffer*> m_mapBuffText;	// テキストバッファ連想配列
	CFrame2DTextState* m_pState;	// 状態
	std::string m_sNextPath;		// 次テキストボックスの保存パス
	std::string m_sNextBoxKey;		// 次テキストボックスの検索キー
	std::string m_sNextStartKey;	// 次テキストボックスのテキスト開始キー
	bool m_bAutoUninitFrame;		// フレーム自動破棄フラグ
};

#endif	// _FRAME2D_MODULE_TEXT_H_
