//============================================================
//
//	表情/選択付きテキスト状態ヘッダー [frame2DTextStateFaceSelect.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_FACE_SELECT_H_
#define _FRAME2D_TEXT_STATE_FACE_SELECT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateSelect.h"
#include "frame2D.h"

//************************************************************
//	前方宣言
//************************************************************
class CFrame2DTextBuffer;	// テキスト情報保存バッファクラス
class CFaceUI;				// 表情UIクラス

//************************************************************
//	クラス定義
//************************************************************
// 表情/選択付きテキスト状態クラス
class CFrame2DTextStateFaceSelect : public CFrame2DTextStateSelect
{
public:
	// コンストラクタ
	CFrame2DTextStateFaceSelect();
	CFrame2DTextStateFaceSelect(const VECTOR3& rOffsetText, const VECTOR3& rOffsetSelectL, const VECTOR3& rOffsetSelectR, const VECTOR3& rOffsetFace);

	// デストラクタ
	~CFrame2DTextStateFaceSelect() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void SetPriority(const int nPriority) override;		// 優先順位設定
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	void BindTextBuffer(CFrame2DTextBuffer* pBuffer) override;	// テキスト情報保存バッファ割当
	inline CFrame2DTextStateFaceSelect* GetStateFaceSelect() override { return this; }	// 表情/選択付きテキスト状態取得

protected:
	// オーバーライド関数
	VECTOR3 GetPresetOffset(const CFrame2D::EPreset preset) override;	// プリセットオフセット取得
	void SetPositionRelative() override;	// 相対位置設定

private:
	// メンバ変数
	CFaceUI* m_pFace;	// 表情情報
	VECTOR3 m_offset;	// 表情オフセット
	int m_nTypeTalkEmo;	// 会話中の表情種類
	int m_nTypeIdolEmo;	// 待機中の表情種類
};

#endif	// _FRAME2D_TEXT_STATE_FACE_SELECT_H_
