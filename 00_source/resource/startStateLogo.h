//============================================================
//
//	ロゴ表示状態ヘッダー [startStateLogo.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _START_STATE_LOGO_H_
#define _START_STATE_LOGO_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "startState.h"

//************************************************************
//	前方宣言
//************************************************************
class CObject2D;	// オブジェクト2Dクラス
class CString2D;	// 文字列2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// ロゴ表示状態クラス
class CStartStateLogo : public CStartState
{
public:
	// コンストラクタ
	CStartStateLogo();

	// デストラクタ
	~CStartStateLogo() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ関数
	void UpdateDispTrans(const float fDeltaTime);	// 操作表示・遷移更新
	void UpdateCommand(void);	// コマンド入力更新

	// メンバ変数
	std::string m_sFragInput;	// キー入力フラグ
	CObject2D* m_pLogo;	// タイトルロゴ
	CString2D* m_pCont;	// 操作説明
	float m_fCurTime;	// 現在の待機時間
	bool m_bSndBall;	// BALLコマンド再生フラグ
};

#endif	// _START_STATE_LOGO_H_
