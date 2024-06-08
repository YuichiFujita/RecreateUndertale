//============================================================
//
//	ロゴ表示状態処理 [startStateLogo.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "startStateLogo.h"
#include "startManager.h"
#include "manager.h"
#include "object2D.h"
#include "string2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *TEXTURE		= "data\\TEXTURE\\logo000.png";	// ロゴテクスチャ
	const int	PRIORITY	= 6;	// 優先順位
	const float	DISP_TIME	= 3.0f;	// ロゴ表示時間

	namespace str
	{
		const char		*FONT	= "data\\FONT\\Crypt of Tomorrow.ttf";	// フォントパス
		const wchar_t	*STRING	= L"[PRESS Z OR ENTER]";	// 表示文字列
		const bool		ITALIC	= false;	// イタリック
		const float		HEIGHT	= 22.5f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// 横配置
		const D3DXCOLOR   COL = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);			// 色
		const D3DXVECTOR3 POS = D3DXVECTOR3(SCREEN_CENT.x, 545.0f, 0.0f);	// 位置
		const D3DXVECTOR3 ROT = VEC3_ZERO;	// 向き
	}
}

//************************************************************
//	子クラス [CStartStateLogo] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartStateLogo::CStartStateLogo() :
	m_pLogo		(nullptr),	// タイトルロゴ
	m_pCont		(nullptr),	// 操作説明
	m_fCurTime	(0.0f)		// 現在の待機時間
{

}

//============================================================
//	デストラクタ
//============================================================
CStartStateLogo::~CStartStateLogo()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CStartStateLogo::Init(void)
{
	// メンバ変数を初期化
	m_pLogo		= nullptr;	// タイトルロゴ
	m_pCont		= nullptr;	// 操作説明
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
void CStartStateLogo::Uninit(void)
{
	// タイトルロゴの終了
	SAFE_UNINIT(m_pLogo);

	// 操作説明の終了
	SAFE_UNINIT(m_pCont);

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CStartStateLogo::Update(const float fDeltaTime)
{
	if (m_pCont == nullptr)
	{ // 操作説明が生成されていない場合

		// 待機時刻を進める
		m_fCurTime += fDeltaTime;
		if (m_fCurTime >= DISP_TIME)
		{ // 待機終了した場合

			// 待機時間を初期化
			m_fCurTime = 0.0f;

			// 操作説明の生成
			m_pCont = CString2D::Create
			( // 引数
				str::FONT,		// フォントパス
				str::ITALIC,	// イタリック
				str::STRING,	// 指定文字列
				str::POS,		// 原点位置
				str::HEIGHT,	// 文字縦幅
				str::ALIGN_X,	// 横配置
				str::ROT,		// 原点向き
				str::COL		// 色
			);

			// 優先順位を設定
			m_pCont->SetPriority(PRIORITY);
		}
	}

	// 進行操作
	if (GET_INPUTKEY->IsTrigger(DIK_RETURN) || GET_INPUTKEY->IsTrigger(DIK_Z))
	{
		// チュートリアル状態にする
		m_pContext->ChangeState(new CStartStateTutorial);
	}
}
