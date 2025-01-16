//============================================================
//
//	アイテムテキスト状態ヘッダー [frame2DTextStateItem.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_ITEM_H_
#define _FRAME2D_TEXT_STATE_ITEM_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateText.h"
#include "frame2D.h"

//************************************************************
//	前方宣言
//************************************************************
class CFrame2DTextBuffer;	// テキスト情報保存バッファクラス
class CItemData;			// アイテム情報クラス

//************************************************************
//	クラス定義
//************************************************************
// アイテムテキスト状態クラス
class CFrame2DTextStateItem : public CFrame2DTextStateText
{
public:
	// コンストラクタ
	CFrame2DTextStateItem();
	CFrame2DTextStateItem(const CFrame2D::EPreset preset);
	CFrame2DTextStateItem(const VECTOR3& rOffset);

	// デストラクタ
	~CFrame2DTextStateItem() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void BindTextBuffer(CFrame2DTextBuffer* pBuffer) override;	// テキスト情報保存バッファ割当
	inline CFrame2DTextStateItem* GetStateItem() override { return this; }	// アイテムテキスト状態取得

private:
	// メンバ関数
	void ReplaceCommand(std::string* pStr, const CItemData& rItem);	// 文字列内のコマンドの置換
};

#endif	// _FRAME2D_TEXT_STATE_ITEM_H_
