//============================================================
//
//	イントロフェードヘッダー [introFade.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _INTRO_FADE_H_
#define _INTRO_FADE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object2D.h"

//************************************************************
//	クラス定義
//************************************************************
// イントロフェードクラス
class CIntroFade : public CObject2D
{
public:
	// フェード列挙
	enum EFade
	{
		FADE_IN = 0,	// フェードイン
		FADE_OUT,		// フェードアウト
		FADE_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CIntroFade();

	// デストラクタ
	~CIntroFade();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CIntroFade *Create(void);	// 生成

private:
	// メンバ変数
	EFade m_fade;	// フェード状況
};

#endif	// _INTRO_FADE_H_
