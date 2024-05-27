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
	const int PRIORITY = 6;	// イントロの優先順位

	namespace logo
	{
		const char *TEXTURE		= "data\\TEXTURE\\logoIntro000.png";	// タイトルロゴテクスチャ
		const D3DXVECTOR3 POS	= SCREEN_CENT;	// タイトルロゴ位置
		const D3DXVECTOR3 SIZE	= SCREEN_SIZE;	// タイトルロゴ大きさ
	}
}

//************************************************************
//	子クラス [CIntroStateLogo] のメンバ関数
//************************************************************
//============================================================
//	初期化処理
//============================================================
HRESULT CIntroStateLogo::Init(void)
{
	// メンバ変数を初期化
	m_pLogo = nullptr;	// タイトルロゴ

	// タイトルロゴの生成
	m_pLogo = CObject2D::Create(logo::POS, logo::SIZE);
	if (m_pLogo == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pLogo->BindTexture(logo::TEXTURE);

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
	if (m_pIntro->WaitTime(fDeltaTime, 4.0f))
	{ // 待機終了した場合

		// ストーリーの自動描画をONにする
		m_pIntro->m_pStory->SetEnableDraw(true);

		// 文字送りを開始する
		m_pIntro->m_pText->SetEnableScroll(true);

		// 文字送り状態にする
		m_pIntro->ChangeState(new CIntroStateText(m_pIntro));
	}
}
