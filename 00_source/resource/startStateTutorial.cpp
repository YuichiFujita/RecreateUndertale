//============================================================
//
//	チュートリアル状態処理 [startStateTutorial.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "startStateTutorial.h"
#include "startManager.h"
#include "string2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 6;	// 優先順位

	namespace virsion
	{
		const char		*FONT = "data\\FONT\\Crypt of Tomorrow.ttf";	// フォントパス
		const wchar_t	*STRING = L"UNDERTALE_REPRISE V1.00 (C) OPUGST 2024-20XX";	// 表示文字列
		const bool		ITALIC = false;	// イタリック
		const float		HEIGHT = 22.5f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// 横配置
		const D3DXCOLOR   COL = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);			// 色
		const D3DXVECTOR3 POS = D3DXVECTOR3(SCREEN_CENT.x, 706.0f, 0.0f);	// 位置
		const D3DXVECTOR3 ROT = VEC3_ZERO;	// 向き
	}
}

//************************************************************
//	子クラス [CStartStateTutorial] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartStateTutorial::CStartStateTutorial() :
	m_pVersion	(nullptr)	// バージョン表記
{

}

//============================================================
//	デストラクタ
//============================================================
CStartStateTutorial::~CStartStateTutorial()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CStartStateTutorial::Init(void)
{
	// メンバ変数を初期化
	m_pVersion = nullptr;	// バージョン表記

	// バージョン表記の生成
	m_pVersion = CString2D::Create
	( // 引数
		virsion::FONT,		// フォントパス
		virsion::ITALIC,	// イタリック
		virsion::STRING,	// 指定文字列
		virsion::POS,		// 原点位置
		virsion::HEIGHT,	// 文字縦幅
		virsion::ALIGN_X,	// 横配置
		virsion::ROT,		// 原点向き
		virsion::COL		// 色
	);

	// 優先順位を設定
	m_pVersion->SetPriority(PRIORITY);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CStartStateTutorial::Uninit(void)
{
	// バージョン表記の終了
	SAFE_UNINIT(m_pVersion);

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CStartStateTutorial::Update(const float fDeltaTime)
{

}
