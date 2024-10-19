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
#include "manager.h"
#include "sound.h"
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
		const float	HEIGHT	= 42.0f;	// 文字縦幅

		const EAlignX		ALIGN_X = XALIGN_CENTER;	// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 65.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;								// 向き
		const COLOR			COL = COLOR(0.75f, 0.75f, 0.75f, 1.0f);			// 色
	}

	namespace control
	{
		const char *FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 42.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 54.0f;	// 行間縦幅

		const D3DXVECTOR3	POS = D3DXVECTOR3(150.0f, 262.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;							// 向き
		const COLOR			COL = COLOR(0.75f, 0.75f, 0.75f, 1.0f);		// 色
		const EAlignX		ALIGN_X = XALIGN_LEFT;		// 横配置
		const EAlignY		ALIGN_Y = YALIGN_CENTER;	// 縦配置
	}

	namespace rule
	{
		const char	*FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 42.0f;	// 文字縦幅

		const EAlignX		ALIGN_X = XALIGN_LEFT;	// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(150.0f, 450.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;							// 向き
		const COLOR			COL = COLOR(0.75f, 0.75f, 0.75f, 1.0f);		// 色
	}

	namespace select
	{
		const char	*FONT		= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 42.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 54.0f;	// 行間縦幅

		const EAlignX ALIGN_X = XALIGN_LEFT;	// 横配置
		const D3DXVECTOR3 POS = D3DXVECTOR3(255.0f, 535.0f, 0.0f);	// 位置
		const D3DXVECTOR3 ROT = VEC3_ZERO;			// 向き
		const COLOR COL_DEFAULT	= color::White();	// 通常色
		const COLOR COL_CHOICE	= color::Yellow();	// 選択色
	}

	namespace virsion
	{
		const char	*FONT	= "data\\FONT\\Crypt of Tomorrow.ttf";	// フォントパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 22.5f;	// 文字縦幅

		const EAlignX		ALIGN_X = XALIGN_CENTER;	// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 706.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;								// 向き
		const COLOR			COL = COLOR(0.5f, 0.5f, 0.5f, 1.0f);			// 色
	}
}

//************************************************************
//	子クラス [CStartStateTutorial] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartStateTutorial::CStartStateTutorial() :
	m_pCont			(nullptr),	// 操作説明
	m_pTitle		(nullptr),	// タイトル
	m_pRule			(nullptr),	// ゲーム概要
	m_pVersion		(nullptr),	// バージョン表記
	m_nCurSelect	(0),		// 現在の選択肢
	m_nOldSelect	(0)			// 前回の選択肢
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
	m_pCont			= nullptr;	// 操作説明
	m_pTitle		= nullptr;	// タイトル
	m_pRule			= nullptr;	// ゲーム概要
	m_pVersion		= nullptr;	// バージョン表記
	m_nCurSelect	= 0;		// 現在の選択肢
	m_nOldSelect	= 0;		// 前回の選択肢

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

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 文字位置オフセット
		D3DXVECTOR3 offset = D3DXVECTOR3(0.0f, select::LINE_HEIGHT * i, 0.0f);

		// 選択肢の生成
		m_apSelect[i] = CString2D::Create
		( // 引数
			select::FONT,			// フォントパス
			select::ITALIC,			// イタリック
			L"",					// 指定文字列
			select::POS + offset,	// 原点位置
			select::CHAR_HEIGHT,	// 文字縦幅
			select::ALIGN_X,		// 横配置
			select::ROT,			// 原点向き
			select::COL_DEFAULT		// 色
		);

		// 優先順位を設定
		m_apSelect[i]->SetPriority(PRIORITY);

		// 文字列を割当
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(PASS, CStartManager::TEXT_START + i));
	}

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

	// イントロノイズを停止
	GET_MANAGER->GetSound()->Stop(CSound::LABEL_SE_INTRONOISE);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CStartStateTutorial::Uninit(void)
{
	// タイトルの終了
	SAFE_UNINIT(m_pTitle);

	// 操作説明の終了
	SAFE_UNINIT(m_pCont);

	// ゲーム概要の終了
	SAFE_UNINIT(m_pRule);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択肢の終了
		SAFE_UNINIT(m_apSelect[i]);
	}

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
	// 選択の更新
	UpdateSelect();

	// 決定の更新
	UpdateDecide();
}

//============================================================
//	選択の更新処理
//============================================================
void CStartStateTutorial::UpdateSelect(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報

	// 前回の選択肢を保存
	m_nOldSelect = m_nCurSelect;

	// 選択肢操作
	if (pKey->IsTrigger(DIK_DOWN))
	{
		// 上に選択をずらす
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		// 下に選択をずらす
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}

	// 前回の選択要素の色を白色に設定
	m_apSelect[m_nOldSelect]->SetColor(select::COL_DEFAULT);

	// 現在の選択要素の色を黄色に設定
	m_apSelect[m_nCurSelect]->SetColor(select::COL_CHOICE);
}

//============================================================
//	決定の更新処理
//============================================================
void CStartStateTutorial::UpdateDecide(void)
{
	if (input::Decide())
	{
		// 選択肢に応じて遷移先を変更
		switch (m_nCurSelect)
		{ // 現在の選択肢ごとの処理
		case SELECT_START:
			m_pContext->ChangeState(new CStartStateCreateName);	// 命名状態
			break;

		case SELECT_OPTION:
			m_pContext->ChangeState(new CStartStateOption);	// 初期設定状態
			break;

		default:
			assert(false);
			break;
		}
	}
}
