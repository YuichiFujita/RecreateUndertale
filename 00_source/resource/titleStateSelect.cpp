//============================================================
//
//	遷移選択状態処理 [titleStateSelect.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "titleStateSelect.h"
#include "titleManager.h"
#include "manager.h"
#include "playerStatus.h"
#include "userdataManager.h"
#include "string2D.h"
#include "version.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* PATH	 = "data\\TEXT\\title.txt";	// テキストパス
	const char*	FONT	 = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
	const bool	ITALIC	 = false;	// イタリック
	const float	HEIGHT	 = 42.0f;	// 文字縦幅
	const int	PRIORITY = 6;		// タイトルの優先順位

	namespace name
	{
		const VECTOR3	POS = VECTOR3(198.0f, 207.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}

	namespace love
	{
		const VECTOR3	POS = VECTOR3(480.0f, 207.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}

	namespace time
	{
		const VECTOR3	POS = VECTOR3(687.0f, 207.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}

	namespace save
	{
		const VECTOR3	POS = VECTOR3(SCREEN_CENT.x, 260.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;			// 向き
		const COLOR		COL = color::White();		// 色
		const EAlignX	ALIGN_X = XALIGN_CENTER;	// 横配置
	}

	namespace select
	{
		const VECTOR3 POS_CONTINUE	= VECTOR3(217.0f, 336.0f, 0.0f);	// コンテニュー選択位置
		const VECTOR3 POS_RESET		= VECTOR3(597.0f, 336.0f, 0.0f);	// リセット選択位置
		const VECTOR3 POS_SETTING	= VECTOR3(399.0f, 396.0f, 0.0f);	// 設定選択位置

		const VECTOR3 POS_SAVEDATA[] =	// セーブデータ操作の選択位置
		{
			POS_CONTINUE,	// コンテニュー選択位置
			POS_RESET,		// リセット選択位置
		};
		const int NUM_SAVEDATA = NUM_ARRAY(POS_SAVEDATA);	// セーブデータ操作の選択数

		const COLOR COL_DEFAULT = color::White();	// 通常色
		const COLOR COL_CHOICE	= color::Yellow();	// 選択色
		const VECTOR3 ROT		= VEC3_ZERO;		// 向き
		const EAlignX ALIGN_X	= XALIGN_LEFT;		// 横配置
	}
}

//************************************************************
//	子クラス [CTitleStateSelect] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTitleStateSelect::CTitleStateSelect() :
	m_pName		(nullptr),		// 名前情報
	m_pLove		(nullptr),		// レベル情報
	m_pTime		(nullptr),		// 総プレイ時間情報
	m_pSave		(nullptr),		// セーブ地点情報
	m_pVersion	(nullptr),		// バージョン表記情報
	m_curSelect	(GRID2_ZERO),	// 現在の選択肢
	m_oldSelect	(GRID2_ZERO)	// 前回の選択肢
{
	// 選択文字配列をクリア
	m_vecSelect.clear();
}

//============================================================
//	デストラクタ
//============================================================
CTitleStateSelect::~CTitleStateSelect()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTitleStateSelect::Init()
{
	CUserDataManager* pUserDataManager = CUserDataManager::GetInstance();	// ユーザーデータマネージャー
	CPlayerStatus status;	// プレイヤーステータス情報

	// メンバ変数を初期化
	m_pName		= nullptr;		// 名前情報
	m_pLove		= nullptr;		// レベル情報
	m_pTime		= nullptr;		// 総プレイ時間情報
	m_pSave		= nullptr;		// セーブ地点情報
	m_pVersion	= nullptr;		// バージョン表記情報
	m_curSelect	= GRID2_ZERO;	// 現在の選択肢
	m_oldSelect	= GRID2_ZERO;	// 前回の選択肢

	// 選択文字配列を初期化
	m_vecSelect.clear();

	// プレイヤーステータスの読込
	pUserDataManager->LoadPlayerStatus(&status);

	//--------------------------------------------------------
	//	名前の初期化/設定
	//--------------------------------------------------------
	// 名前の生成
	m_pName = CString2D::Create
	( // 引数
		FONT,				// フォントパス
		ITALIC,				// イタリック
		status.GetName(),	// 指定文字列
		name::POS,			// 原点位置
		HEIGHT,				// 文字縦幅
		name::ALIGN_X,		// 横配置
		name::ROT,			// 原点向き
		name::COL			// 色
	);
	if (m_pName == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pName->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	レベルの初期化/設定
	//--------------------------------------------------------
	const std::string sLove = "LV " + std::to_string(status.GetLove());	// レベル文字列

	// レベルの生成
	m_pLove = CString2D::Create
	( // 引数
		FONT,			// フォントパス
		ITALIC,			// イタリック
		sLove,			// 指定文字列
		love::POS,		// 原点位置
		HEIGHT,			// 文字縦幅
		love::ALIGN_X,	// 横配置
		love::ROT,		// 原点向き
		love::COL		// 色
	);
	if (m_pLove == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pLove->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	総プレイ時間の初期化/設定
	//--------------------------------------------------------
	const std::string sTime = pUserDataManager->GetStrPlayTime();	// 総プレイ時間文字列

	// 総プレイ時間の生成
	m_pTime = CString2D::Create
	( // 引数
		FONT,			// フォントパス
		ITALIC,			// イタリック
		sTime,			// 指定文字列
		time::POS,		// 原点位置
		HEIGHT,			// 文字縦幅
		time::ALIGN_X,	// 横配置
		time::ROT,		// 原点向き
		time::COL		// 色
	);
	if (m_pTime == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pTime->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	セーブ地点の初期化/設定
	//--------------------------------------------------------
	// セーブ地点の生成
	m_pSave = CString2D::Create
	( // 引数
		FONT,				// フォントパス
		ITALIC,				// イタリック
		L"ここにセーブ名",	// 指定文字列	// TODO：ここにセーブ地点の名前
		save::POS,			// 原点位置
		HEIGHT,				// 文字縦幅
		save::ALIGN_X,		// 横配置
		save::ROT,			// 原点向き
		save::COL			// 色
	);
	if (m_pSave == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pSave->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	セーブデータ操作選択肢の初期化/設定
	//--------------------------------------------------------
	// 横一行分の配列を拡張
	m_vecSelect.emplace_back();

	for (int i = 0; i < select::NUM_SAVEDATA; i++)
	{ // 列の選択肢の総数分繰り返す

		// セーブデータ操作の選択肢生成
		CString2D* pSelect = CString2D::Create
		( // 引数
			FONT,						// フォントパス
			ITALIC,						// イタリック
			L"",						// 指定文字列
			select::POS_SAVEDATA[i],	// 原点位置
			HEIGHT,						// 文字縦幅
			select::ALIGN_X,			// 横配置
			select::ROT,				// 原点向き
			select::COL_DEFAULT			// 色
		);
		if (pSelect == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		pSelect->SetPriority(PRIORITY);

		// 文字列を割当
		loadtext::BindString(pSelect, loadtext::LoadText(PATH, CTitleManager::TEXT_CONTINUE + i));

		// 現在の行列の最後尾に生成した文字を追加
		m_vecSelect.back().push_back(pSelect);
	}

	//--------------------------------------------------------
	//	設定選択肢の初期化/設定
	//--------------------------------------------------------
	// 横一行分の配列を拡張
	m_vecSelect.emplace_back();

	// 設定の選択肢生成
	CString2D* pSetting = CString2D::Create
	( // 引数
		FONT,					// フォントパス
		ITALIC,					// イタリック
		L"",					// 指定文字列
		select::POS_SETTING,	// 原点位置
		HEIGHT,					// 文字縦幅
		select::ALIGN_X,		// 横配置
		select::ROT,			// 原点向き
		select::COL_DEFAULT		// 色
	);
	if (pSetting == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	pSetting->SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindString(pSetting, loadtext::LoadText(PATH, CTitleManager::TEXT_SETTING));

	// 現在の行列の最後尾に生成した文字を追加
	m_vecSelect.back().push_back(pSetting);

	//--------------------------------------------------------
	//	バージョン表記の初期化/設定
	//--------------------------------------------------------
	// バージョン表記の生成
	m_pVersion = CVersion::Create();
	if (m_pVersion == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CTitleStateSelect::Uninit()
{
	// 名前の終了
	SAFE_UNINIT(m_pName);

	// レベルの終了
	SAFE_UNINIT(m_pLove);

	// 総プレイ時間の終了
	SAFE_UNINIT(m_pTime);

	// セーブ地点の終了
	SAFE_UNINIT(m_pSave);

	// バージョン表記の終了
	SAFE_UNINIT(m_pVersion);

	for (int i = 0; i < (int)m_vecSelect.size(); i++)
	{ // 行の総数分繰り返す

		for (int j = 0; j < (int)m_vecSelect[i].size(); j++)
		{ // 列の総数分繰り返す

			// 選択文字の終了
			SAFE_UNINIT(m_vecSelect[i][j]);
		}
	}

	// 選択文字配列をクリア
	m_vecSelect.clear();

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CTitleStateSelect::Update(const float fDeltaTime)
{
	// 選択の更新
	UpdateSelect();

	// 決定の更新
	UpdateDecide();
}

//============================================================
//	選択の更新処理
//============================================================
void CTitleStateSelect::UpdateSelect()
{
	CInputKeyboard* pKey = GET_INPUTKEY;	// キーボード情報

	// 前回の選択肢を保存
	m_oldSelect = m_curSelect;

	// 選択肢操作
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// 左に選択をずらす
		int nMaxWidth = (int)m_vecSelect[m_curSelect.y].size();	// 列の最大数
		m_curSelect.x = (m_curSelect.x + (nMaxWidth - 1)) % nMaxWidth;
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// 右に選択をずらす
		int nMaxWidth = (int)m_vecSelect[m_curSelect.y].size();	// 列の最大数
		m_curSelect.x = (m_curSelect.x + 1) % nMaxWidth;
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		// 上に選択をずらす
		int nMaxHeight = (int)m_vecSelect.size();	// 行の最大数
		m_curSelect.y = (m_curSelect.y + (nMaxHeight - 1)) % nMaxHeight;

		// 列の選択を初期化
		m_curSelect.x = 0;
	}
	if (pKey->IsTrigger(DIK_DOWN))
	{
		// 下に選択をずらす
		int nMaxHeight = (int)m_vecSelect.size();	// 行の最大数
		m_curSelect.y = (m_curSelect.y + 1) % nMaxHeight;

		// 列の選択を初期化
		m_curSelect.x = 0;
	}

	// 前回の選択要素の色を白色に設定
	assert(m_vecSelect[m_oldSelect.y][m_oldSelect.x] != nullptr);
	m_vecSelect[m_oldSelect.y][m_oldSelect.x]->SetColor(select::COL_DEFAULT);

	// 現在の選択要素の色を黄色に設定
	assert(m_vecSelect[m_curSelect.y][m_curSelect.x] != nullptr);
	m_vecSelect[m_curSelect.y][m_curSelect.x]->SetColor(select::COL_CHOICE);
}

//============================================================
//	決定の更新処理
//============================================================
void CTitleStateSelect::UpdateDecide()
{
	if (input::Decide())
	{
		// 選択肢に応じて遷移先を変更
		switch (m_curSelect.x + m_curSelect.y * select::NUM_SAVEDATA)
		{ // 現在の選択肢ごとの処理
		case SELECT_CONTINUE:
			GET_MANAGER->SetScene(CScene::MODE_GAME);		// ゲーム画面に遷移する
			break;

		case SELECT_RESET:
			m_pContext->ChangeState(new CTitleStateReset);	// リセット状態
			break;

		case SELECT_SETTING:
			m_pContext->ChangeState(new CTitleStateOption);	// 設定状態
			break;

		default:
			assert(false);
			break;
		}
	}
}
