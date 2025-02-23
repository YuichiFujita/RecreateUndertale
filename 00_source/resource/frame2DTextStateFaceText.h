//============================================================
//
//	表情付きテキスト状態ヘッダー [frame2DTextStateFaceText.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_FACE_TEXT_H_
#define _FRAME2D_TEXT_STATE_FACE_TEXT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateText.h"
#include "frame2D.h"

//************************************************************
//	前方宣言
//************************************************************
class CFrame2DTextBuffer;	// テキスト情報保存バッファクラス
class CFaceUI;				// 表情UIクラス

//************************************************************
//	クラス定義
//************************************************************
// 表情付きテキスト状態クラス
class CFrame2DTextStateFaceText : public CFrame2DTextStateText
{
public:
	// コンストラクタ
	CFrame2DTextStateFaceText();
	CFrame2DTextStateFaceText(const CFrame2D::EPreset preset);
	CFrame2DTextStateFaceText(const VECTOR3& rOffsetText, const VECTOR3& rOffsetFace);

	// デストラクタ
	~CFrame2DTextStateFaceText() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void SetPriority(const int nPriority) override;		// 優先順位設定
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	void BindTextBuffer(CFrame2DTextBuffer* pBuffer) override;	// テキスト情報保存バッファ割当
	inline CFrame2DTextStateFaceText* GetStateFaceText() override { return this; }	// 表情付きテキスト状態取得

protected:
	// オーバーライド関数
	VECTOR3 GetPresetOffset(const CFrame2D::EPreset preset) override;	// プリセットオフセット取得
	void SetPositionRelative() override;	// 相対位置設定

private:
	// メンバ変数
	CFaceUI* m_pFace;	// 表情情報
	VECTOR3 m_offset;	// 表情オフセット
};

#endif	// _FRAME2D_TEXT_STATE_FACE_TEXT_H_
