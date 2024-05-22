//============================================================
//
//	イントロマネージャー処理 [introManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "introManager.h"
#include "manager.h"
#include "object2D.h"
#include "scroll2D.h"
#include "scrollText2D.h"
#include "introState.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 6;	// イントロの優先順位

	namespace logo
	{
		const char *TEXTURE		= "data\\TEXTURE\\logoIntro000.png";	// タイトルロゴテクスチャ
		const D3DXVECTOR3 POS	= SCREEN_CENT;	// タイトルロゴ位置
		const D3DXVECTOR3 SIZE	= SCREEN_SIZE;	// タイトルロゴ大きさ
	}

	namespace story
	{
		const char *TEXTURE[] =	// 物語のテクスチャ
		{
			"data\\TEXTURE\\story000.png",	// むかしむかし
			"data\\TEXTURE\\story001.png",	// ところがあるとき
			"data\\TEXTURE\\story002.png",	// ニンゲンしょうり
			"data\\TEXTURE\\story003.png",	// ちかにとじこめました
			"data\\TEXTURE\\story004.png",	// ながいときがながれ
			"data\\TEXTURE\\story005.png",	// イビト山
			"data\\TEXTURE\\story006.png",	// でんせつの山
			"data\\TEXTURE\\story007.png",	// 見下ろし
			"data\\TEXTURE\\story008.png",	// 引っ掛かり
			"data\\TEXTURE\\story009.png",	// 落下
			"data\\TEXTURE\\story010.png",	// 着地
		};

		const D3DXVECTOR3 POS	= D3DXVECTOR3(SCREEN_CENT.x, 225.0f, 0.0f);	// ストーリー位置
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(605.0f, 302.5f, 0.0f);		// ストーリー大きさ
	}

	namespace text
	{
#if 1
		const wchar_t *TEXT[][3] =	// 物語のテキスト
		{
			{
				L"むかしむかし　ちきゅうには",
				L"ニンゲンと　モンスターという",
				L"2つのしゅぞくが　いました。",
			},
			{
				L"ところが　あるとき",
				L"2つのしゅぞくの　あいだに",
				L"せんそうが　おきました。",
			},
			{
				L"そして　ながい",
				L"たたかいのすえ　ニンゲンが",
				L"しょうりしました。",
			},
			{
				L"ニンゲンは　まほうのちからで",
				L"モンスターたちを",
				L"ちかに　とじこめました。",
			},
			{
				L"それから　さらに",
				L"ながい　ときが　ながれ………",
				L"",
			},
			{
				L"　　　　イビト山",
				L"　　　　　 201X年",
				L"",
			},
			{
				L"それは「のぼったものは",
				L"にどと　もどらない」といわれる",
				L"でんせつの山でした。",
			},
			{ L"", L"", L"", },
			{ L"", L"", L"", },
			{ L"", L"", L"", },
			{ L"", L"", L"", },
		};
#endif

		const char *FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC		= false;	// イタリック
		const float	WAIT_TIME	= 0.115f;	// 文字表示の待機時間
		const float	CHAR_HEIGHT	= 45.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 62.0f;	// 行間縦幅

		const D3DXVECTOR3 POS = D3DXVECTOR3(SCREEN_CENT.x - story::SIZE.x * 0.5f, 460.0f, 0.0f);	// テキスト位置
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY ALIGN_Y = CText2D::YALIGN_TOP;		// 縦配置
	}
}

//************************************************************
//	親クラス [CIntroManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CIntroManager::CIntroManager() :
	m_pFade		(nullptr),		// フェード
	m_pStory	(nullptr),		// ストーリー
	m_pText		(nullptr),		// テキスト
	m_pState	(nullptr),		// 状態
	m_fade		(FADE_NONE),	// フェード状況
	m_nStory	(0),			// 物語インデックス
	m_fCurTime	(0.0f)			// 現在の待機時間
{

}

//============================================================
//	デストラクタ
//============================================================
CIntroManager::~CIntroManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CIntroManager::Init(void)
{
	// メンバ変数を初期化
	m_pFade		= nullptr;		// フェード
	m_pStory	= nullptr;		// ストーリー
	m_pText		= nullptr;		// テキスト
	m_pState	= nullptr;		// 状態
	m_fade		= FADE_NONE;	// フェード状況
	m_nStory	= 0;			// 物語インデックス
	m_fCurTime	= 0.0f;			// 現在の待機時間

	// ロゴ表示状態にする
	ChangeState(new CIntroStateLogo(this));

	// ストーリーの生成
#if 1
	m_pStory = CScroll2D::Create(0.0f, 0.0f, story::POS, story::SIZE);
	if (m_pStory == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pStory->BindTexture(story::TEXTURE[0]);

	// 優先順位を設定
	m_pStory->SetPriority(PRIORITY);

	// 自動描画をOFFにする
	m_pStory->SetEnableDraw(false);
#endif

	// フェードの生成
#if 1
	m_pFade = CObject2D::Create(story::POS, story::SIZE, VEC3_ZERO, XCOL_ABLACK);
	if (m_pFade == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pFade->SetPriority(PRIORITY);
#endif

	// テキストの生成
#if 1
	m_pText = CScrollText2D::Create
	( // 引数
		text::FONT,			// フォントパス
		text::ITALIC,		// イタリック
		text::POS,			// 原点位置
		text::WAIT_TIME,	// 文字表示の待機時間
		text::CHAR_HEIGHT,	// 文字縦幅
		text::LINE_HEIGHT,	// 行間縦幅
		text::ALIGN_X,		// 横配置
		text::ALIGN_Y		// 縦配置
	);
	if (m_pText == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	for (int i = 0; i < 3; i++)
	{
		// 文字列を設定
		m_pText->AddString(text::TEXT[0][i]);
	}
#endif

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CIntroManager::Uninit(void)
{
	// 状態の破棄
	SAFE_DELETE(m_pState);

	// フェードの終了
	SAFE_UNINIT(m_pFade);

	// ストーリーの終了
	SAFE_UNINIT(m_pStory);
}

//============================================================
//	更新処理
//============================================================
void CIntroManager::Update(const float fDeltaTime)
{
	// フェードの更新
	UpdateFade();

	// 状態ごとの更新
	m_pState->Update(fDeltaTime);
}

//============================================================
//	状態の変更処理
//============================================================
HRESULT CIntroManager::ChangeState(CIntroState *pState)
{
	// 状態の生成に失敗している場合抜ける
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// 自身のインスタンスを終了
	SAFE_UNINIT(m_pState);

	// 自身のインスタンスを変更
	assert(m_pState == nullptr);
	m_pState = pState;

	// 自身のインスタンスを初期化
	if (FAILED(m_pState->Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	生成処理
//============================================================
CIntroManager *CIntroManager::Create(void)
{
	// イントロマネージャーの生成
	CIntroManager *pIntroManager = new CIntroManager;
	if (pIntroManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// イントロマネージャーの初期化
		if (FAILED(pIntroManager->Init()))
		{ // 初期化に失敗した場合

			// イントロマネージャーの破棄
			SAFE_DELETE(pIntroManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pIntroManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CIntroManager::Release(CIntroManager *&prIntroManager)
{
	// イントロマネージャーの終了
	assert(prIntroManager != nullptr);
	prIntroManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prIntroManager);
}

//============================================================
//	物語の遷移処理
//============================================================
void CIntroManager::NextStory(void)
{
	// 物語を次に進める
	m_nStory++;
	if (useful::LimitMaxNum(m_nStory, (int)STORY_MAX - 1))
	{ // 最後まで表示した場合

		// 終了状態にする
		ChangeState(new CIntroStateEnd(this));
	}
	else
	{ // まだ表示できる場合

		// 文字列をすべて破棄
		m_pText->DeleteStringAll();

		// 次の文字列に置換
		for (int i = 0; i < 3; i++)
		{
			// 文字列を設定
			m_pText->AddString(text::TEXT[m_nStory][i]);
		}

		// 文字送りを開始する
		m_pText->SetEnableScroll(true);

		// フェードを開始する
		m_fade = FADE_IN;

		// 文字送り状態にする
		ChangeState(new CIntroStateText(this));
	}
}

//============================================================
//	フェード更新処理
//============================================================
void CIntroManager::UpdateFade(void)
{
	switch (m_fade)
	{ // フェード状態ごとの処理
	case FADE_NONE:	// フェード無し
	{
		break;
	}
	case FADE_IN:	// フェードイン
	{
		D3DXCOLOR colFade = m_pFade->GetColor();	// フェード色
		colFade.a += 0.04f;
		m_pFade->SetColor(colFade);

		if (colFade.a >= 1.0f)
		{ // フェード仕切った場合

			// 物語の画像を差し替え
			m_pStory->BindTexture(story::TEXTURE[m_nStory]);

			// フェードアウト状態にする
			m_fade = FADE_OUT;
		}

		break;
	}
	case FADE_OUT:	// フェードアウト
	{
		D3DXCOLOR colFade = m_pFade->GetColor();	// フェード色
		colFade.a -= 0.04f;
		m_pFade->SetColor(colFade);

		if (colFade.a <= 0.0f)
		{ // フェード仕切った場合

			// フェード無し状態にする
			m_fade = FADE_NONE;
		}

		break;
	}
	default:
		assert(false);
		break;
	}
}

//============================================================
//	待機時間の管理処理
//============================================================
bool CIntroManager::WaitTime(const float fDeltaTime, const float fDestTime)
{
	// 待機時刻を進める
	m_fCurTime += fDeltaTime;
	if (m_fCurTime >= fDestTime)
	{ // 待機終了した場合

		// 待機時間を初期化
		m_fCurTime = 0.0f;

		return true;
	}

	return false;
}
