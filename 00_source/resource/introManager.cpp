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
#include "introState.h"
#include "introFade.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
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

		const int	PRIORITY		= 4;		// 物語表示ポリゴンの優先順位
		const float	SCROLL_MOVE		= -0.002f;	// スクロールの移動量
		const float	SCROLL_OFFSET	= 0.324f;	// スクロールポリゴンのテクスチャオフセット

		const float	WAIT_TIME_DISP		= 5.5f;	// 物語遷移の待機時間 (表示のみ)
		const float	WAIT_TIME_SCROLL	= 5.5f;	// 物語遷移の待機時間 (スクロール)

		const D3DXVECTOR3 POS	= D3DXVECTOR3(SCREEN_CENT.x, 225.0f, 0.0f);	// ストーリー位置
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(605.0f, 302.5f, 0.0f);		// ストーリー大きさ
	}

	namespace text
	{
		const char *FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const char *PASS = "data\\TEXT\\intro.txt";	// テキストパス

		const int	PRIORITY	= 6;		// テキストの優先順位
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 45.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 62.0f;	// 行間縦幅

		const float	WAIT_TIME_NOR	= 0.115f;	// 文字表示の待機時間 (通常速度)
		const float	WAIT_TIME_SLOW	= 0.7f;		// 文字表示の待機時間 (速度低下)

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
	m_pStory	(nullptr),	// ストーリー
	m_pText		(nullptr),	// テキスト
	m_pState	(nullptr),	// 状態
	m_nStoryID	(0)			// 物語インデックス
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
	m_pStory	= nullptr;	// ストーリー
	m_pText		= nullptr;	// テキスト
	m_pState	= nullptr;	// 状態
	m_nStoryID	= 0;		// 物語インデックス

	// ロゴ表示状態にする
	ChangeState(new CIntroStateLogo);

	//--------------------------------------------------------
	//	ストーリーの生成・設定
	//--------------------------------------------------------
	// ストーリーの生成
	m_pStory = CScroll2D::Create(0.0f, 0.0f, story::POS, story::SIZE);
	if (m_pStory == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// ラベルをUIに設定
	m_pStory->SetLabel(CObject::LABEL_UI);

	// 優先順位を設定
	m_pStory->SetPriority(story::PRIORITY);

	//--------------------------------------------------------
	//	テキストの生成・設定
	//--------------------------------------------------------
	// テキストの生成
	m_pText = CScrollText2D::Create
	( // 引数
		text::FONT,				// フォントパス
		text::ITALIC,			// イタリック
		text::POS,				// 原点位置
		text::WAIT_TIME_NOR,	// 文字表示の待機時間
		text::CHAR_HEIGHT,		// 文字縦幅
		text::LINE_HEIGHT,		// 行間縦幅
		text::ALIGN_X,			// 横配置
		text::ALIGN_Y			// 縦配置
	);
	if (m_pText == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位をフェードより上にする
	m_pText->SetPriority(text::PRIORITY);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CIntroManager::Uninit(void)
{
	// 状態の終了
	SAFE_UNINIT(m_pState);
}

//============================================================
//	更新処理
//============================================================
void CIntroManager::Update(const float fDeltaTime)
{
	// 状態ごとの更新
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	状態の変更処理
//============================================================
HRESULT CIntroManager::ChangeState(CIntroState *pState)
{
	// 状態の生成に失敗している場合抜ける
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// 状態インスタンスを終了
	SAFE_UNINIT(m_pState);

	// 状態インスタンスを変更
	assert(m_pState == nullptr);
	m_pState = pState;

	// 状態インスタンスを初期化
	if (FAILED(m_pState->Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 状態にコンテキストを設定
	m_pState->SetContext(this);

	// 成功を返す
	return S_OK;
}

//============================================================
//	物語の遷移処理
//============================================================
void CIntroManager::NextStory(void)
{
	// 物語を次に進める
	m_nStoryID++;

	// フェードを生成する
	CIntroFade::Create(this);

	switch (m_nStoryID)
	{ // 物語ごとの処理
	case STORY_00:	// むかしむかし
	case STORY_01:	// ところがあるとき
	case STORY_02:	// ニンゲンしょうり
	case STORY_03:	// ちかにとじこめました
	case STORY_05:	// イビト山
	case STORY_06:	// でんせつの山

		// 表示テキストを変更する
		ChangeText(m_nStoryID);

		// 文字送り状態にする
		ChangeState(new CIntroStateText);

		break;

	case STORY_04:	// ながいときがながれ

		// 表示テキストを変更する
		ChangeText(m_nStoryID);

		// 文字送り速度低下状態にする
		ChangeState(new CIntroStateTextSlow);

		break;

	case STORY_07:	// 見下ろし
	case STORY_08:	// 引っ掛かり
	case STORY_09:	// 落下

		// 文字列を全て削除
		m_pText->DeleteStringAll();

		// 待機状態にする
		ChangeState(new CIntroStateWait(story::WAIT_TIME_DISP));

		break;

	case STORY_10:	// 着地

		// 文字列を全て削除
		m_pText->DeleteStringAll();

		// 待機状態にする
		ChangeState(new CIntroStateWait(story::WAIT_TIME_SCROLL));

		break;
	}
}

//============================================================
//	ストーリー変更処理
//============================================================
void CIntroManager::ChangeStory(const int nStoryID)
{
	// 物語の画像を差し替え
	m_pStory->BindTexture(story::TEXTURE[nStoryID]);

	if (nStoryID == STORY_MAX - 1)
	{ // 最後の物語の場合

		// テクスチャの開始地点にする
		m_pStory->SetOffsetV(story::SCROLL_OFFSET);		// オフセットを設定
		m_pStory->SetTexV(1.0f - story::SCROLL_OFFSET);	// テクスチャ座標を設定
	}
}

//============================================================
//	テキスト変更処理
//============================================================
void CIntroManager::ChangeText(const int nStoryID)
{
	// 文字列を全て削除
	m_pText->DeleteStringAll();

	// 次のテキストを割当
	loadtext::BindText(m_pText, loadtext::LoadText(text::PASS, nStoryID));

	// 文字送りを開始する
	m_pText->SetEnableScroll(true);
}

//============================================================
//	ストーリースクロールの開始
//============================================================
void CIntroManager::StartScrollStory(void)
{
	// 物語のスクロールを開始する
	m_pStory->SetMoveV(story::SCROLL_MOVE);
}

//============================================================
//	ストーリースクロールの正規化
//============================================================
bool CIntroManager::NormalizeScrollStory(void)
{
	if (m_pStory->GetNumLoopV() >= 1)
	{ // テクスチャがワンループした場合

		// テクスチャの終了地点で停止
		m_pStory->SetMoveV(0.0f);	// 移動量を初期化
		m_pStory->SetTexV(1.0f);	// テクスチャ座標を補正

		return true;
	}

	return false;
}

//============================================================
//	文字送りの速度設定処理
//============================================================
void CIntroManager::SetEnableSlowText(const bool bSlow)
{
	// 速度フラグに応じて設定
	if (bSlow)	{ m_pText->SetNextTime(text::WAIT_TIME_SLOW); }	// 遅くする
	else		{ m_pText->SetNextTime(text::WAIT_TIME_NOR); }	// 早くする
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
