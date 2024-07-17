//============================================================
//
//	フェードヘッダー [fade.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FADE_H_
#define _FADE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "scene.h"
#include "object2D.h"

//************************************************************
//	クラス定義
//************************************************************
// フェードクラス
class CFade : public CObject2D
{
public:
	// 定数
	static constexpr int	PRIORITY	= 7;		// 優先順位
	static constexpr float	DEF_LEVEL	= 1.0f;		// α値加減量 (デフォルト)
	static constexpr float	SKIP_LEVEL	= 120.0f;	// α値加減量 (スキップ)

	// フェード状態列挙
	enum EFade
	{
		FADE_NONE = 0,	// 何もしていない状態
		FADE_WAIT,		// フェード余韻状態
		FADE_IN,		// フェードイン状態
		FADE_OUT,		// フェードアウト状態
		FADE_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CFade();

	// デストラクタ
	~CFade();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CFade *Create(void);	// 生成

	// メンバ関数
	void SetNextMode(const CScene::EMode next)	{ m_modeNext = next; }	// 遷移先モード設定
	CScene::EMode GetNextMode(void) const		{ return m_modeNext; }	// 遷移先モード取得
	EFade GetState(void) const	{ return m_fade; }						// フェード状態取得
	bool IsFade(void) const		{ return m_fade != FADE_NONE; }			// フェード状況取得

	void SetFade	// フェード開始設定
	( // 引数
		const float fAddOut		= DEF_LEVEL,	// アウトのα値増加量
		const float fSubIn		= DEF_LEVEL,	// インのα値減少量
		const int nPriority		= PRIORITY,		// 優先順位
		const D3DXCOLOR colFade	= XCOL_ABLACK	// フェード色
	);
	void SetModeFade	// 遷移先モード設定 (フェードのみ)
	( // 引数
		const CScene::EMode mode,				// 遷移先モード
		const float fWaitTime	= 0.0f,			// 余韻時間
		const float fAddOut		= DEF_LEVEL,	// アウトのα値増加量
		const float fSubIn		= DEF_LEVEL,	// インのα値減少量
		const D3DXCOLOR colFade	= XCOL_ABLACK	// フェード色
	);
	void SetLoadFade	// 遷移先モード設定 (ロード画面付き)
	( // 引数
		const CScene::EMode mode,				// 遷移先モード
		const float fWaitTime	= 0.0f,			// 余韻時間
		const float fAddOut		= DEF_LEVEL,	// アウトのα値増加量
		const float fSubIn		= DEF_LEVEL,	// インのα値減少量
		const D3DXCOLOR colFade	= XCOL_ABLACK	// フェード色
	);
	void SetRoomFade(void);	// 遷移先ルーム設定

private:
	// メンバ変数
	std::function<HRESULT(void)> m_funcSetMode;	// モード設定関数ポインタ
	CScene::EMode m_modeNext;	// 遷移先モード
	EFade m_fade;		// フェード状態
	float m_fWaitTime;	// 現在の余韻時間
	float m_fSubIn;		// インのα値減少量
	float m_fAddOut;	// アウトのα値増加量
};

#endif	// _FADE_H_
