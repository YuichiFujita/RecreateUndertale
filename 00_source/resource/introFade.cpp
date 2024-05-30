//============================================================
//
//	イントロフェード処理 [introFade.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "introFade.h"
#include "introManager.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int	PRIORITY	= 5;	// フェードの優先順位
	const float	FADE_LEVEL	= 2.8f;	// フェードのα変化量
}

//************************************************************
//	子クラス [CIntroFade] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CIntroFade::CIntroFade(CIntroManager *pIntro) :
	m_pIntro	(pIntro),	// イントロマネージャー
	m_fade		(FADE_IN)	// フェード状況
{

}

//============================================================
//	デストラクタ
//============================================================
CIntroFade::~CIntroFade()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CIntroFade::Init(void)
{
	// メンバ変数を初期化
	m_fade = FADE_IN;	// フェード状況

	// オブジェクト2Dの初期化
	if (FAILED(CObject2D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// ラベルをUIにする
	SetLabel(LABEL_UI);

	// 優先順位を物語表示ポリゴンより上にする
	SetPriority(PRIORITY);

	// 位置をスクリーン中央にする
	SetVec3Position(SCREEN_CENT);

	// 大きさをスクリーンサイズにする
	SetVec3Sizing(SCREEN_SIZE);

	// ポリゴンを黒にする
	SetColor(XCOL_ABLACK);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CIntroFade::Uninit(void)
{
	// オブジェクト2Dの終了
	CObject2D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CIntroFade::Update(const float fDeltaTime)
{
	D3DXCOLOR colFade = GetColor();	// フェード色

	switch (m_fade)
	{ // フェード状態ごとの処理
	case FADE_IN:	// フェードイン

		// 透明度を上げる
		colFade.a += FADE_LEVEL * fDeltaTime;
		if (colFade.a >= 1.0f)
		{ // フェード仕切った場合

			// イントロの表示物語を変更する
			m_pIntro->ChangeStory(m_pIntro->GetStoryID());

			// フェードアウト状態にする
			m_fade = FADE_OUT;
		}

		break;

	case FADE_OUT:	// フェードアウト

		// 透明度を下げる
		colFade.a -= FADE_LEVEL * fDeltaTime;
		if (colFade.a <= 0.0f)
		{ // フェード仕切った場合

			// フェードの終了
			Uninit();
			return;
		}

		break;

	default:
		assert(false);
		break;
	}

	// 色を反映
	SetColor(colFade);

	// オブジェクト2Dの更新
	CObject2D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CIntroFade::Draw(CShader *pShader)
{
	// オブジェクト2Dの描画
	CObject2D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CIntroFade *CIntroFade::Create(CIntroManager *pIntro)
{
	// イントロフェードの生成
	CIntroFade *pIntroFade = new CIntroFade(pIntro);
	if (pIntroFade == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// イントロフェードの初期化
		if (FAILED(pIntroFade->Init()))
		{ // 初期化に失敗した場合

			// イントロフェードの破棄
			SAFE_DELETE(pIntroFade);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pIntroFade;
	}
}
