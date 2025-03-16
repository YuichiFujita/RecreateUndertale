//============================================================
//
//	表情/選択付きテキスト保存バッファヘッダー [frame2DTextBufferFaceSelect.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_BUFFER_FACE_SELECT_H_
#define _FRAME2D_TEXT_BUFFER_FACE_SELECT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferSelect.h"
#include "frame2D.h"

//************************************************************
//	クラス定義
//************************************************************
// 表情/選択付きテキスト保存バッファクラス
class CFrame2DTextBufferFaceSelect : public CFrame2DTextBufferSelect
{
public:
	// コンストラクタ
	CFrame2DTextBufferFaceSelect(const int nIdxFace);

	// デストラクタ
	~CFrame2DTextBufferFaceSelect() override;

	// オーバーライド関数
	CFrame2DTextState* CreateState() override;	// テキスト機能状態生成
	void LoadSetup(std::ifstream* pFile, const std::string& rString) override;				// バッファごとのセットアップ
	inline CFrame2DTextBufferFaceSelect* GetBufferFaceSelect() override { return this; }	// 表情/選択付きテキストバッファ取得

	// メンバ変数
	const int m_nIdxFace;	// 顔インデックス
	int m_nTypeTalkEmo;		// 会話中の表情種類
	int m_nTypeIdolEmo;		// 待機中の表情種類
};

#endif	// _FRAME2D_TEXT_BUFFER_FACE_SELECT_H_
