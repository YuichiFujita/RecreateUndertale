//============================================================
//
//	テキスト機能状態ヘッダー [frame2DTextState.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_H_
#define _FRAME2D_TEXT_STATE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "sound.h"
#include "frame2DModuleText.h"

//************************************************************
//	前方宣言
//************************************************************
class CFrame2DModuleText;			// テキスト表示機能クラス
class CFrame2DTextBuffer;			// テキスト情報保存バッファクラス
class CFrame2DTextStateText;		// テキスト状態クラス
class CFrame2DTextStateSelect;		// 選択付きテキスト状態クラス
class CFrame2DTextStateFaceText;	// 表情付きテキスト状態クラス
class CFrame2DTextStateFaceSelect;	// 表情/選択付きテキスト状態クラス
class CFrame2DTextStateItem;		// アイテムテキスト状態クラス

//************************************************************
//	クラス定義
//************************************************************
// テキスト機能状態クラス
class CFrame2DTextState
{
public:
	// コンストラクタ
	CFrame2DTextState();

	// デストラクタ
	virtual ~CFrame2DTextState();

	// 純粋仮想関数
	virtual HRESULT Init()	= 0;	// 初期化
	virtual void Uninit()	= 0;	// 終了
	virtual void Update(const float fDeltaTime) = 0;	// 更新
	virtual void BindTextBuffer(CFrame2DTextBuffer* pBuffer) = 0;	// テキスト情報保存バッファ割当

	// 仮想関数
	inline virtual CFrame2DTextStateText* GetStateText()			 { return nullptr; }	// テキスト状態取得
	inline virtual CFrame2DTextStateSelect* GetStateSelect()		 { return nullptr; }	// 選択付きテキスト状態取得
	inline virtual CFrame2DTextStateFaceText* GetStateFaceText()	 { return nullptr; }	// 表情付きテキスト状態取得
	inline virtual CFrame2DTextStateFaceSelect* GetStateFaceSelect() { return nullptr; }	// 表情/選択付きテキスト状態取得
	inline virtual CFrame2DTextStateItem* GetStateItem()			 { return nullptr; }	// アイテムテキスト状態取得
	inline virtual void SetPriority(const int)			{ assert(false); }	// 優先順位設定
	inline virtual void SetVec3Position(const VECTOR3&)	{ assert(false); }	// 位置設定
	inline virtual void SetVec3Rotation(const VECTOR3&)	{ assert(false); }	// 向き設定
	inline virtual void SetVec3Size(const VECTOR3&)		{ assert(false); }	// 大きさ設定
	inline virtual void SetFontPath(const CFrame2DModuleText::EFont /*font*/)		{}	// フォントパス設定
	inline virtual void SetSoundLabel(const CFrame2DModuleText::ESound /*sound*/)	{}	// サウンドラベル設定

	// メンバ関数
	std::string GetFontPath(const CFrame2DModuleText::EFont font);					// フォントパス取得
	float GetFontHeight(const CFrame2DModuleText::EFont font);						// フォント縦幅取得
	CSound::ELabel GetSoundLabel(const CFrame2DModuleText::ESound sound);			// サウンドラベル取得
	inline void SetContext(CFrame2DModuleText* pContext) { m_pContext = pContext; }	// コンテキスト設定
	inline void SetCurTextKey(const std::string& rKey)	 { m_sCurTextKey = rKey; }	// テキスト検索キー設定
	inline std::string GetCurTextKey() const			 { return m_sCurTextKey; }	// テキスト検索キー取得

protected:
	// 純粋仮想関数
	virtual void SetPositionRelative() = 0;	// 相対位置設定

	// メンバ変数
	CFrame2DModuleText* m_pContext;	// コンテキスト

private:
	// メンバ変数
	std::string m_sCurTextKey;	// 割当済みテキストの検索キー
};

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateText.h"

#endif	// _FRAME2D_TEXT_STATE_H_
