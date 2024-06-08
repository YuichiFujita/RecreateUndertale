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
#include "text2D.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *PASS = "data\\TEXT\\start.txt";	// テキストパス
	const int PRIORITY = 6;	// 優先順位

	namespace title
	{	
		const char	*FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 45.0f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 70.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;								// 向き
		const D3DXCOLOR		COL = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);		// 色
	}

	namespace control
	{
		const char *FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 45.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 62.0f;	// 行間縦幅

		const D3DXVECTOR3	POS = D3DXVECTOR3(120.0f, 285.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;							// 向き
		const D3DXCOLOR		COL = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);	// 色
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_CENTER;	// 縦配置
	}

	namespace rule
	{
		const char	*FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC = false;	// イタリック
		const float	HEIGHT = 45.0f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(120.0f, 500.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;							// 向き
		const D3DXCOLOR		COL = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);	// 色
	}

	namespace virsion
	{
		const char	*FONT	= "data\\FONT\\Crypt of Tomorrow.ttf";	// フォントパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 22.5f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 706.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;								// 向き
		const D3DXCOLOR		COL = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);		// 色
	}
}

//************************************************************
//	子クラス [CStartStateTutorial] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartStateTutorial::CStartStateTutorial() :
	m_pCont		(nullptr),	// 操作説明
	m_pTitle	(nullptr),	// タイトル
	m_pRule		(nullptr),	// ゲーム概要
	m_pVersion	(nullptr)	// バージョン表記
{
	// メンバ変数をクリア
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢
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
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢
	m_pCont		= nullptr;	// 操作説明
	m_pTitle	= nullptr;	// タイトル
	m_pRule		= nullptr;	// ゲーム概要
	m_pVersion	= nullptr;	// バージョン表記

	// タイトルの生成
	m_pTitle = CString2D::Create
	( // 引数
		title::FONT,	// フォントパス
		title::ITALIC,	// イタリック
		L"",			// 指定文字列
		title::POS,		// 原点位置
		title::HEIGHT,	// 文字縦幅
		title::ALIGN_X,	// 横配置
		title::ROT,		// 原点向き
		title::COL		// 色
	);

	// 優先順位を設定
	m_pTitle->SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindString(m_pTitle, loadtext::LoadText(PASS, CStartManager::TEXT_BUTTON_TITLE));

	// 操作説明の生成
	m_pCont = CText2D::Create
	( // 引数
		control::FONT,			// フォントパス
		control::ITALIC,		// イタリック
		control::POS,			// 原点位置
		control::CHAR_HEIGHT,	// 文字縦幅
		control::LINE_HEIGHT,	// 行間縦幅
		control::ALIGN_X,		// 横配置
		control::ALIGN_Y,		// 縦配置
		control::ROT,			// 原点向き
		control::COL			// 色
	);
	if (m_pCont == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pCont->SetPriority(PRIORITY);

	// テキストを割当
	loadtext::BindText(m_pCont, loadtext::LoadText(PASS, CStartManager::TEXT_BUTTON_KINDS));

	// ゲーム概要の生成
	m_pRule = CString2D::Create
	( // 引数
		rule::FONT,		// フォントパス
		rule::ITALIC,	// イタリック
		L"",			// 指定文字列
		rule::POS,		// 原点位置
		rule::HEIGHT,	// 文字縦幅
		rule::ALIGN_X,	// 横配置
		rule::ROT,		// 原点向き
		rule::COL		// 色
	);

	// 優先順位を設定
	m_pRule->SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindString(m_pRule, loadtext::LoadText(PASS, CStartManager::TEXT_RULE));

	// バージョン表記の生成
	m_pVersion = CString2D::Create
	( // 引数
		virsion::FONT,		// フォントパス
		virsion::ITALIC,	// イタリック
		L"",				// 指定文字列
		virsion::POS,		// 原点位置
		virsion::HEIGHT,	// 文字縦幅
		virsion::ALIGN_X,	// 横配置
		virsion::ROT,		// 原点向き
		virsion::COL		// 色
	);

	// 優先順位を設定
	m_pVersion->SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindString(m_pVersion, loadtext::LoadText(PASS, CStartManager::TEXT_VIRSION));

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
