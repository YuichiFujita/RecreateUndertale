//============================================================
//
//	テキスト状態ヘッダー [frame2DTextStateText.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_TEXT_H_
#define _FRAME2D_TEXT_STATE_TEXT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextState.h"
#include "frame2D.h"
#include "scrollText2D.h"

//************************************************************
//	前方宣言
//************************************************************
class CFrame2DTextBuffer;	// テキスト情報保存バッファクラス

//************************************************************
//	クラス定義
//************************************************************
// テキスト状態クラス
class CFrame2DTextStateText : public CFrame2DTextState
{
public:
	// 定数
	static constexpr float CHAR_HEIGHT	= 42.0f;	// 文字縦幅
	static constexpr float LINE_HEIGHT	= 54.0f;	// 行間縦幅
	static constexpr float WAIT_TIME	= 0.045f;	// 文字表示の待機時間
	
	// コンストラクタ
	CFrame2DTextStateText();
	CFrame2DTextStateText(const CFrame2D::EPreset preset);
	CFrame2DTextStateText(const VECTOR3& rOffset);

	// デストラクタ
	~CFrame2DTextStateText() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void SetPriority(const int nPriority) override;		// 優先順位設定
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	void BindTextBuffer(CFrame2DTextBuffer* pBuffer) override;	// テキスト情報保存バッファ割当
	inline CFrame2DTextStateText* GetStateText() override { return this; }	// テキスト状態取得

	// メンバ関数
	void ChangeText(const AText& rText);	// テキスト変更
	void SetOffset(const VECTOR3& rOffset);	// テキストオフセット設定
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
	// 仮想関数
	virtual VECTOR3 GetPresetOffset(const CFrame2D::EPreset preset);	// プリセットオフセット取得
	virtual void SetPositionRelative();	// 相対位置設定

	// メンバ関数
	inline void SetNextTextKey(const std::string& rKey) { m_sNextTextKey = rKey; }	// 次テキストの検索キー設定

private:
	// メンバ変数
	std::string m_sNextTextKey;	// 次テキストの検索キー
	CScrollText2D* m_pText;		// テキスト情報
	VECTOR3 m_offset;			// テキストオフセット
	// TODO：ここにpreset保存を置くしかないかぁ。コンストラクタ時の保存にしか使わないように、const指定子で置いとくか
};

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateSelect.h"
#include "frame2DTextStateFaceText.h"
#include "frame2DTextStateItem.h"

#endif	// _FRAME2D_TEXT_STATE_TEXT_H_
