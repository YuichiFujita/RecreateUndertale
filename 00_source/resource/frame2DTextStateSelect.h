//============================================================
//
//	選択付きテキスト状態ヘッダー [frame2DTextStateSelect.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_SELECT_H_
#define _FRAME2D_TEXT_STATE_SELECT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateText.h"
#include "frame2D.h"
#include "frame2DModuleText.h"
#include "scrollText2D.h"

//************************************************************
//	前方宣言
//************************************************************
class CFrame2DTextBuffer;	// テキスト情報保存バッファクラス
class CObject2D;			// オブジェクト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// 選択付きテキスト状態クラス
class CFrame2DTextStateSelect : public CFrame2DTextStateText
{
public:
	// 選択列挙
	enum ESelect
	{
		SELECT_LEFT = 0,	// 左選択
		SELECT_RIGHT,		// 右選択
		SELECT_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CFrame2DTextStateSelect();
	CFrame2DTextStateSelect(const VECTOR3& rOffsetText, const VECTOR3& rOffsetSelectL, const VECTOR3& rOffsetSelectR);

	// デストラクタ
	~CFrame2DTextStateSelect() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void SetPriority(const int nPriority) override;		// 優先順位設定
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	void SetFontPath(const CFrame2DModuleText::EFont font) override;			// フォントパス設定
	void SetSoundLabel(const CFrame2DModuleText::ESound sound) override;		// サウンドラベル設定
	void BindTextBuffer(CFrame2DTextBuffer* pBuffer) override;					// テキスト情報保存バッファ割当
	inline CFrame2DTextStateSelect* GetStateSelect() override { return this; }	// 選択付きテキスト状態取得

	// メンバ関数
	void ChangeText(const ESelect select, const AText& rText);	// テキスト変更
	inline HRESULT PushFrontString(const ESelect select, const std::string& rStr)	{ return m_apSelect[select]->PushFrontString(rStr); }	// 文字列の先頭追加 (マルチバイト文字列)
	inline HRESULT PushFrontString(const ESelect select, const std::wstring& rStr)	{ return m_apSelect[select]->PushFrontString(rStr); }	// 文字列の先頭追加 (ワイド文字列)
	inline HRESULT PushBackString(const ESelect select, const std::string& rStr)	{ return m_apSelect[select]->PushBackString(rStr); }	// 文字列の最後尾追加 (マルチバイト文字列)
	inline HRESULT PushBackString(const ESelect select, const std::wstring& rStr)	{ return m_apSelect[select]->PushBackString(rStr); }	// 文字列の最後尾追加 (ワイド文字列)
	inline void DeleteString(const ESelect select, const int nStrIdx)				{ m_apSelect[select]->DeleteString(nStrIdx); }			// 文字列削除
	inline void DeleteStringAll(const ESelect select)								{ m_apSelect[select]->DeleteStringAll(); }				// 文字列全削除
	inline void SetTextEnableDraw(const ESelect select, const bool bDraw)			{ m_apSelect[select]->SetEnableDraw(bDraw); };			// テキスト描画状況設定
	inline void SetTextEnableScroll(const ESelect select, const bool bScroll)		{ m_apSelect[select]->SetEnableScroll(bScroll); };		// テキスト文字送り状況設定
	inline bool IsTextScroll(const ESelect select) const							{ return m_apSelect[select]->IsScroll(); }				// テキスト文字送り状況取得
	inline bool IsTextEndScroll(const ESelect select) const							{ return m_apSelect[select]->IsEndScroll(); }			// テキスト文字送り終了状況取得

	// オーバーロード関数再公開
	using CFrame2DTextStateText::ChangeText;			// テキスト変更
	using CFrame2DTextStateText::PushFrontString;		// 文字列の先頭追加
	using CFrame2DTextStateText::PushBackString;		// 文字列の最後尾追加
	using CFrame2DTextStateText::DeleteString;			// 文字列削除
	using CFrame2DTextStateText::DeleteStringAll;		// 文字列全削除
	using CFrame2DTextStateText::SetTextEnableDraw;		// テキスト描画状況設定
	using CFrame2DTextStateText::SetTextEnableScroll;	// テキスト文字送り状況設定
	using CFrame2DTextStateText::IsTextScroll;			// テキスト文字送り状況取得
	using CFrame2DTextStateText::IsTextEndScroll;		// テキスト文字送り終了状況取得

protected:
	// 仮想関数
	virtual float GetPresetOffsetX(const ESelect select, const CFrame2D::EPreset preset);	// プリセットXオフセット取得

	// メンバ関数
	VECTOR3 GetPresetOffset(const ESelect select, const CFrame2D::EPreset preset);	// プリセットオフセット取得

	// オーバーロード関数再公開
	using CFrame2DTextStateText::GetPresetOffset;	// プリセットオフセット取得

	// オーバーライド関数
	void SetPositionRelative() override;	// 相対位置設定

private:
	// エイリアス定義
	typedef VECTOR3(CFrame2DTextStateSelect::*AFuncOffset)();	// オフセット取得関数ポインタ

	// 関数配列
	static AFuncOffset m_aFuncOffset[][SELECT_MAX];	// オフセット取得関数リスト

	// メンバ関数
	void UpdateScroll();	// 文字送り更新
	void UpdateSelect();	// 選択更新
	void UpdateDecide();	// 決定更新
	int GetMaxSelectLine();	// 選択肢の最大行数取得
	VECTOR3 GetOffsetDownLeft();	// 左下部配置オフセット取得
	VECTOR3 GetOffsetDownRight();	// 右下部配置オフセット取得

	// メンバ変数
	std::string m_aNextPath[SELECT_MAX];	// 次テキストボックスの保存パス
	std::string m_aNextBoxKey[SELECT_MAX];	// 次テキストボックスの検索キー
	std::string m_aNextKey[SELECT_MAX];		// テキストボックスのテキスト開始キー
	CScrollText2D* m_apSelect[SELECT_MAX];	// 選択肢情報
	VECTOR3 m_aOffset[SELECT_MAX];			// 選択肢オフセット
	std::string m_sCutTextPath;	// 現在テキストの保存パス
	CObject2D* m_pSoul;			// ソウルカーソル情報
	int m_nCurSelect;			// 現在の選択肢
};

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateFaceSelect.h"

#endif	// _FRAME2D_TEXT_STATE_SELECT_H_
