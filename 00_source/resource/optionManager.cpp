//============================================================
//
//	設定マネージャー処理 [optionManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "optionManager.h"
#include "manager.h"
#include "string2D.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char*	PATH = "data\\TXT\\TEXT\\option.txt";				// テキストパス
	const char*	FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
	const bool	ITALIC = false;	// イタリック
	const int	PRIORITY = 6;	// 優先順位

	namespace title
	{	
		const VECTOR3	POS = VECTOR3(SCREEN_CENT.x, 70.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;			// 向き
		const COLOR		COL = color::White();		// 色
		const EAlignX	ALIGN_X = XALIGN_CENTER;	// 横配置
		const float		HEIGHT = 90.0f;				// 文字縦幅
	}

	namespace select
	{
		const VECTOR3	POS = VECTOR3(55.0f, 140.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;					// 向き
		const COLOR		COL_DEFAULT	= color::White();		// 通常色
		const COLOR		COL_CHOICE	= color::Yellow();		// 選択色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
		const float		CHAR_HEIGHT = 42.0f;	// 文字縦幅
		const float		LINE_HEIGHT = 54.0f;	// 行間縦幅
	}
}

//************************************************************
//	親クラス [COptionManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
COptionManager::COptionManager() :
	m_pTitle	 (nullptr),	// タイトル
	m_nCurSelect (0),		// 現在の選択肢
	m_nOldSelect (0)		// 前回の選択肢
{
	// メンバ変数をクリア
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢
}

//============================================================
//	デストラクタ
//============================================================
COptionManager::~COptionManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT COptionManager::Init()
{
	// メンバ変数を初期化
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢
	m_pTitle	 = nullptr;	// タイトル
	m_nCurSelect = 0;		// 現在の選択肢
	m_nOldSelect = 0;		// 前回の選択肢

	// タイトルの生成
	m_pTitle = CString2D::Create
	( // 引数
		FONT,			// フォントパス
		ITALIC,			// イタリック
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
	loadtext::BindString(m_pTitle, loadtext::LoadText(PATH, TEXT_TITLE));

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 文字位置オフセット
		VECTOR3 offset = VECTOR3(0.0f, select::LINE_HEIGHT * i, 0.0f);

		// 選択肢の生成
		m_apSelect[i] = CString2D::Create
		( // 引数
			FONT,					// フォントパス
			ITALIC,					// イタリック
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
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(PATH, TEXT_CLOSE + i));
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void COptionManager::Uninit()
{
	// タイトルの終了
	SAFE_UNINIT(m_pTitle);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択肢の終了
		SAFE_UNINIT(m_apSelect[i]);
	}
}

//============================================================
//	更新処理
//============================================================
bool COptionManager::Update(const float fDeltaTime)
{
	// 選択の更新
	UpdateSelect();

	// 決定の更新
	return UpdateDecide();	// 状態遷移の操作があった場合trueを返す
}

//============================================================
//	生成処理
//============================================================
COptionManager* COptionManager::Create()
{
	// 設定マネージャーの生成
	COptionManager* pOptionManager = new COptionManager;
	if (pOptionManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 設定マネージャーの初期化
		if (FAILED(pOptionManager->Init()))
		{ // 初期化に失敗した場合

			// 設定マネージャーの破棄
			SAFE_DELETE(pOptionManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pOptionManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void COptionManager::Release(COptionManager*& prOptionManager)
{
	// 設定マネージャーの終了
	assert(prOptionManager != nullptr);
	prOptionManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prOptionManager);
}

//============================================================
//	選択の更新処理
//============================================================
void COptionManager::UpdateSelect()
{
	// 前回の選択肢を保存
	m_nOldSelect = m_nCurSelect;

	// 選択肢操作
	CInputKeyboard* pKey = GET_INPUTKEY;	// キーボード情報
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
bool COptionManager::UpdateDecide()
{
	if (input::Decide())
	{
		// 選択肢に応じて遷移先を変更
		switch (m_nCurSelect)
		{ // 現在の選択肢ごとの処理
		case SELECT_CLOSE:
			return true;

		default:
			assert(false);
			break;
		}
	}

	return false;
}
