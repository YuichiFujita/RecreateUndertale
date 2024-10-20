//============================================================
//
//	初期設定状態処理 [startStateOption.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "startStateOption.h"
#include "startManager.h"
#include "manager.h"
#include "string2D.h"
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
		const char*	FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 90.0f;	// 文字縦幅

		const VECTOR3	POS = VECTOR3(SCREEN_CENT.x, 70.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;			// 向き
		const COLOR		COL = color::White();		// 色
		const EAlignX	ALIGN_X = XALIGN_CENTER;	// 横配置
	}

	namespace select
	{
		const char*	FONT		= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 42.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 54.0f;	// 行間縦幅

		const VECTOR3	POS = VECTOR3(55.0f, 140.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;					// 向き
		const COLOR		COL_DEFAULT	= color::White();		// 通常色
		const COLOR		COL_CHOICE	= color::Yellow();		// 選択色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}
}

//************************************************************
//	子クラス [CStartStateOption] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartStateOption::CStartStateOption() :
	m_pTitle		(nullptr),	// タイトル
	m_nCurSelect	(0),		// 現在の選択肢
	m_nOldSelect	(0)			// 前回の選択肢
{
	// メンバ変数をクリア
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢
}

//============================================================
//	デストラクタ
//============================================================
CStartStateOption::~CStartStateOption()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CStartStateOption::Init(void)
{
	// メンバ変数を初期化
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢
	m_pTitle		= nullptr;	// タイトル
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
	loadtext::BindString(m_pTitle, loadtext::LoadText(PASS, CStartManager::TEXT_OPTION_TITLE));

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 文字位置オフセット
		VECTOR3 offset = VECTOR3(0.0f, select::LINE_HEIGHT * i, 0.0f);

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
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(PASS, CStartManager::TEXT_OPTION_CLOSE + i));
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CStartStateOption::Uninit(void)
{
	// タイトルの終了
	SAFE_UNINIT(m_pTitle);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択肢の終了
		SAFE_UNINIT(m_apSelect[i]);
	}

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CStartStateOption::Update(const float fDeltaTime)
{
	// 選択の更新
	UpdateSelect();

	// 決定の更新
	UpdateDecide();
}

//============================================================
//	選択の更新処理
//============================================================
void CStartStateOption::UpdateSelect(void)
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
void CStartStateOption::UpdateDecide(void)
{
	if (input::Decide())
	{
		// 選択肢に応じて遷移先を変更
		switch (m_nCurSelect)
		{ // 現在の選択肢ごとの処理
		case SELECT_CLOSE:
			m_pContext->ChangeState(new CStartStateTutorial);	// チュートリアル状態
			break;

		default:
			assert(false);
			break;
		}
	}
}
