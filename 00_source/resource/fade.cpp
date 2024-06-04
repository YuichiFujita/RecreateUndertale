//============================================================
//
//	フェード処理 [fade.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "loading.h"
#include "object2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int	PRIORITY	= 7;		// フェードの優先順位
	const float	FADE_LEVEL	= 0.05f;	// フェードのα値の加減量

#ifdef _DEBUG

	const CScene::EMode INIT_SCENE = CScene::MODE_INTRO;	// 初期シーン

#else	// NDEBUG

	const CScene::EMode INIT_SCENE = CScene::MODE_INTRO;	// 初期シーン

#endif	// _DEBUG
}

//************************************************************
//	親クラス [CFade] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFade::CFade() :
	m_pFade		(nullptr),		// フェード情報
	m_modeNext	(INIT_SCENE),	// 次シーン
	m_fade		(FADE_NONE),	// フェード状態
	m_fWaitTime	(0.0f)			// 余韻管理カウンター
{

}

//============================================================
//	デストラクタ
//============================================================
CFade::~CFade()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFade::Init(void)
{
	// メンバ変数を初期化
	m_pFade		= nullptr;		// フェード情報
	m_modeNext	= INIT_SCENE;	// 次シーン
	m_fade		= FADE_IN;		// フェード状態
	m_fWaitTime	= 0.0f;			// 余韻管理カウンター

	// フェードの生成
	m_pFade = CObject2D::Create
	( // 引数
		SCREEN_CENT,	// 位置
		SCREEN_SIZE,	// 大きさ
		VEC3_ZERO,		// 向き
		XCOL_BLACK		// 色
	);
	if (m_pFade == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位の設定
	m_pFade->SetPriority(PRIORITY);

	// ラベル指定なしに設定
	m_pFade->SetLabel(CObject::LABEL_NONE);	// 自動破棄・更新を停止する

	// シーンの初期化
	if (FAILED(GET_MANAGER->InitScene(m_modeNext)))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFade::Uninit(void)
{
	// フェードの終了
	SAFE_UNINIT(m_pFade);
}

//============================================================
//	更新処理
//============================================================
void CFade::Update(const float fDeltaTime)
{
	// フェードしていない場合抜ける
	if (m_fade == FADE_NONE) { return; }

	D3DXCOLOR colFade = m_pFade->GetColor();	// フェード色
	switch (m_fade)
	{ // フェード状態ごとの処理
	case FADE_WAIT:	// フェード余韻状態

		// 余韻時刻を減らす
		m_fWaitTime -= fDeltaTime;
		if (m_fWaitTime <= 0.0f)
		{ // 余韻終了した場合

			// フェードアウト状態にする
			m_fade = FADE_OUT;
		}

		break;

	case FADE_IN:	// フェードイン状態

		// ロードが完了していない場合抜ける
		if (GET_MANAGER->GetLoading()->GetState() != CLoading::LOAD_NONE) { break; }

		// 透明にしていく
		colFade.a -= FADE_LEVEL;
		if (colFade.a <= 0.0f)
		{ // 透明になった場合

			// α値を補正
			colFade.a = 0.0f;

			// 何もしない状態にする
			m_fade = FADE_NONE;
		}

		break;

	case FADE_OUT:	// フェードアウト状態

		// 不透明にしていく
		colFade.a += FADE_LEVEL;
		if (colFade.a >= 1.0f)
		{ // 不透明になった場合

			// α値を補正
			colFade.a = 1.0f;

			// フェードイン状態にする
			m_fade = FADE_IN;

			// モードの設定
			GET_MANAGER->SetMode(m_modeNext);
		}

		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	// 色を反映
	m_pFade->SetColor(colFade);

	// フェードの更新
	m_pFade->Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CFade::Draw(void)
{

}

//============================================================
//	フェード状態取得処理
//============================================================
CFade::EFade CFade::GetState(void) const
{
	// 現在のフェード状態を返す
	return m_fade;
}

//============================================================
//	フェードの開始処理
//============================================================
void CFade::SetFade(const float fWaitTime)
{
	// フェード中の場合抜ける
	if (m_fade != FADE_NONE) { return; }

	// 余韻フレームオーバー
	assert(fWaitTime >= 0.0f);

	// 余韻時間を設定
	m_fWaitTime = fWaitTime;

	// TODO：フェードしかしない状態作ろう
	if (m_fWaitTime <= 0.0f)
	{ // カウンターが未設定の場合

		// フェードアウト状態にする
		m_fade = FADE_OUT;
	}
	else
	{ // カウンターが設定された場合

		// フェード余韻状態にする
		m_fade = FADE_WAIT;
	}
}

//============================================================
//	次シーンの設定処理 (フェードのみ)
//============================================================
void CFade::SetFade(const CScene::EMode mode, const float fWaitTime)
{
	// フェード中の場合抜ける
	if (m_fade != FADE_NONE) { return; }

	// 余韻フレームオーバー
	assert(fWaitTime >= 0.0f);

	// 引数のモードを設定
	m_modeNext = mode;

	// 余韻時間を設定
	m_fWaitTime = fWaitTime;

	// TODO：ロード画面に行かないフェード状態作ろう
	if (m_fWaitTime <= 0.0f)
	{ // カウンターが未設定の場合

		// フェードアウト状態にする
		m_fade = FADE_OUT;
	}
	else
	{ // カウンターが設定された場合

		// フェード余韻状態にする
		m_fade = FADE_WAIT;
	}
}

//============================================================
//	次シーンの設定処理 (ロード画面付き)
//============================================================
void CFade::SetLoadFade(const CScene::EMode mode, const float fWaitTime)
{
	// フェード中の場合抜ける
	if (m_fade != FADE_NONE) { return; }

	// 余韻フレームオーバー
	assert(fWaitTime >= 0.0f);

	// 引数のモードを設定
	m_modeNext = mode;

	// 余韻時間を設定
	m_fWaitTime = fWaitTime;

	// TODO：ロード画面に行くフェード状態作ろう
	if (m_fWaitTime <= 0.0f)
	{ // カウンターが未設定の場合

		// フェードアウト状態にする
		m_fade = FADE_OUT;
	}
	else
	{ // カウンターが設定された場合

		// フェード余韻状態にする
		m_fade = FADE_WAIT;
	}
}

//============================================================
//	生成処理
//============================================================
CFade *CFade::Create(void)
{
	// フェードの生成
	CFade *pFade = new CFade;
	if (pFade == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// フェードの初期化
		if (FAILED(pFade->Init()))
		{ // 初期化に失敗した場合

			// フェードの破棄
			SAFE_DELETE(pFade);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pFade;
	}
}

//============================================================
//	破棄処理
//============================================================
void CFade::Release(CFade *&prFade)
{
	// フェードの終了
	assert(prFade != nullptr);
	prFade->Uninit();

	// メモリ開放
	SAFE_DELETE(prFade);
}
