//============================================================
//
//	リセット状態ヘッダー [titleStateReset.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _TITLE_STATE_RESET_H_
#define _TITLE_STATE_RESET_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "titleState.h"
#include "nearNameManager.h"

//************************************************************
//	クラス定義
//************************************************************
// リセット状態クラス
class CTitleStateReset : public CTitleState
{
public:
	// コンストラクタ
	CTitleStateReset();

	// デストラクタ
	~CTitleStateReset() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ関数
	void UpdateDecide(const CNearNameManager::ESelect select);	// 決定更新

	// メンバ変数
	CNearNameManager* m_pNearNameManager;	// 名前接近マネージャー
};

#endif	// _TITLE_STATE_RESET_H_
