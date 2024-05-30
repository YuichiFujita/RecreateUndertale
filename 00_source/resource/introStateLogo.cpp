//============================================================
//
//	ロゴ表示状態処理 [introStateLogo.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "introStateLogo.h"
#include "introManager.h"
#include "object2D.h"
#include "scroll2D.h"
#include "scrollText2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *TEXTURE		= "data\\TEXTURE\\logoIntro000.png";	// ロゴテクスチャ
	const int	PRIORITY	= 6;	// 優先順位
	const float	DISP_TIME	= 4.0f;	// タイトルロゴ表示時間
}

//************************************************************
//	子クラス [CIntroStateLogo] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CIntroStateLogo::CIntroStateLogo() :
	m_pLogo		(nullptr),	// タイトルロゴ
	m_fCurTime	(0.0f)		// 現在の待機時間
{

}

//============================================================
//	デストラクタ
//============================================================
CIntroStateLogo::~CIntroStateLogo()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CIntroStateLogo::Init(void)
{
	// メンバ変数を初期化
	m_pLogo		= nullptr;	// タイトルロゴ
	m_fCurTime	= 0.0f;		// 現在の待機時間

	// タイトルロゴの生成
	m_pLogo = CObject2D::Create(SCREEN_CENT, SCREEN_SIZE);
	if (m_pLogo == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pLogo->BindTexture(TEXTURE);

	// 優先順位を設定
	m_pLogo->SetPriority(PRIORITY);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CIntroStateLogo::Uninit(void)
{
	// タイトルロゴの終了
	SAFE_UNINIT(m_pLogo);

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CIntroStateLogo::Update(const float fDeltaTime)
{
	// 待機時刻を進める
	m_fCurTime += fDeltaTime;
	if (m_fCurTime >= DISP_TIME)
	{ // 待機終了した場合

		// 待機時間を初期化
		m_fCurTime = 0.0f;

		// ストーリーの自動描画をONにする
		m_pContext->m_pStory->SetEnableDraw(true);

		// 文字送りを開始する
		m_pContext->m_pText->SetEnableScroll(true);

		// 文字送り状態にする
		m_pContext->ChangeState(new CIntroStateText);
	}
}
