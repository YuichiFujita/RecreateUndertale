//============================================================
//
//	フルステータスメニュー処理 [selectStatusUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "selectStatusUI.h"
#include "manager.h"
#include "loadtext.h"
#include "string2D.h"
#include "text2D.h"
#include "sceneGame.h"
#include "player.h"
#include "playerStatus.h"
#include "item.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char*	FONT	 = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
	const char*	PATH	 = "data\\TXT\\TEXT\\selectStatus.txt";			// テキストパス
	const bool	ITALIC	 = false;	// イタリック
	const float	HEIGHT	 = 42.0f;	// 文字縦幅
	const int	PRIORITY = 6;		// フルステータスメニューの優先順位

	namespace frame
	{
		const VECTOR3 POS	= VECTOR3(555.0f, 386.5f, 0.0f);	// フレーム位置
		const VECTOR3 ROT	= VEC3_ZERO;						// フレーム向き
		const VECTOR3 SIZE	= VECTOR3(525.0f, 600.0f, 0.0f);	// フレーム大きさ
	}

	namespace name
	{
		const VECTOR3	POS = VECTOR3(320.0f, 140.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}

	namespace lvhp_title
	{

		const VECTOR3	POS = VECTOR3(320.0f, 200.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
		const EAlignY	ALIGN_Y = YALIGN_TOP;	// 縦配置
		const float		LINE_HEIGHT = 53.0f;	// 行間縦幅
	}

	namespace lvhp_value
	{
		const VECTOR3	POS = VECTOR3(402.0f, 200.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
		const EAlignY	ALIGN_Y = YALIGN_TOP;	// 縦配置
		const float		LINE_HEIGHT = 53.0f;	// 行間縦幅
	}

	namespace atkdef_title
	{
		const VECTOR3	POS = VECTOR3(320.0f, 330.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
		const EAlignY	ALIGN_Y = YALIGN_TOP;	// 縦配置
		const float		LINE_HEIGHT = 53.0f;	// 行間縦幅
	}

	namespace atkdef_value
	{
		const VECTOR3	POS = VECTOR3(402.0f, 330.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
		const EAlignY	ALIGN_Y = YALIGN_TOP;	// 縦配置
		const float		LINE_HEIGHT = 53.0f;	// 行間縦幅
	}

	namespace expnext_title
	{
		const VECTOR3	POS = VECTOR3(570.0f, 330.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
		const EAlignY	ALIGN_Y = YALIGN_TOP;	// 縦配置
		const float		LINE_HEIGHT = 53.0f;	// 行間縦幅
	}

	namespace expnext_value
	{
		const VECTOR3	POS = VECTOR3(672.0f, 330.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
		const EAlignY	ALIGN_Y = YALIGN_TOP;	// 縦配置
		const float		LINE_HEIGHT = 53.0f;	// 行間縦幅
	}

	namespace wpnamr_title
	{
		const VECTOR3	POS = VECTOR3(320.0f, 460.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
		const EAlignY	ALIGN_Y = YALIGN_TOP;	// 縦配置
		const float		LINE_HEIGHT = 53.0f;	// 行間縦幅
	}

	namespace wpnamr_name
	{
		const VECTOR3	POS = VECTOR3(402.0f, 460.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
		const EAlignY	ALIGN_Y = YALIGN_TOP;	// 縦配置
		const float		LINE_HEIGHT = 53.0f;	// 行間縦幅
	}

	namespace gold_title
	{
		const VECTOR3	POS = VECTOR3(320.0f, 615.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}

	namespace gold_value
	{
		const VECTOR3	POS = VECTOR3(423.0f, 615.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}

	namespace kills_title
	{
		const VECTOR3	POS = VECTOR3(500.0f, 615.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}

	namespace kills_value
	{
		const VECTOR3	POS = VECTOR3(627.0f, 615.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}
}

//************************************************************
//	子クラス [CSelectStatusUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSelectStatusUI::CSelectStatusUI(AFuncUninit funcUninit, CObject2D *pSoul) : CSelectUI(funcUninit, pSoul),
	m_pName			(nullptr),	// 名前情報
	m_pLvHpTitle	(nullptr),	// LV/HPタイトル情報
	m_pLvHpValue	(nullptr),	// LV/HP数値情報
	m_pAtkDefTitle	(nullptr),	// ATK/DEFタイトル情報
	m_pAtkDefValue	(nullptr),	// ATK/DEF数値情報
	m_pExpNextTitle	(nullptr),	// EXP/NEXTタイトル情報
	m_pExpNextValue	(nullptr),	// EXP/NEXT数値情報
	m_pWpnAmrTitle	(nullptr),	// WPN/AMRタイトル情報
	m_pWpnAmrName	(nullptr),	// WPN/AMR名称情報
	m_pGoldTitle	(nullptr),	// GOLDタイトル情報
	m_pGoldValue	(nullptr),	// GOLD数値情報
	m_pKillsTitle	(nullptr),	// KILLSタイトル情報
	m_pKillsValue	(nullptr)	// KILLS数値情報
{

}

//============================================================
//	デストラクタ
//============================================================
CSelectStatusUI::~CSelectStatusUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSelectStatusUI::Init()
{
	CPlayerStatus status = *CSceneGame::GetPlayer()->GetStatus();	// ステータス情報

	// メンバ変数を初期化
	m_pName			= nullptr;	// 名前情報
	m_pLvHpTitle	= nullptr;	// LV/HPタイトル情報
	m_pLvHpValue	= nullptr;	// LV/HP数値情報
	m_pAtkDefTitle	= nullptr;	// ATK/DEFタイトル情報
	m_pAtkDefValue	= nullptr;	// ATK/DEF数値情報
	m_pExpNextTitle	= nullptr;	// EXP/NEXTタイトル情報
	m_pExpNextValue	= nullptr;	// EXP/NEXT数値情報
	m_pWpnAmrTitle	= nullptr;	// WPN/AMRタイトル情報
	m_pWpnAmrName	= nullptr;	// WPN/AMR名称情報
	m_pGoldTitle	= nullptr;	// GOLDタイトル情報
	m_pGoldValue	= nullptr;	// GOLD数値情報
	m_pKillsTitle	= nullptr;	// KILLSタイトル情報
	m_pKillsValue	= nullptr;	// KILLS数値情報

	//--------------------------------------------------------
	//	親クラスの初期化 / 設定
	//--------------------------------------------------------
	// セレクトUIの初期化
	if (FAILED(CSelectUI::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// フレームの位置を設定
	SetFramePosition(frame::POS);

	// フレームの向きを設定
	SetFrameRotation(frame::ROT);

	// フレームの大きさを設定
	SetFrameSize(frame::SIZE);

	// ソウルカーソルの描画をOFFにする
	SetSoulCursorDraw(false);

	//--------------------------------------------------------
	//	名前の初期化 / 設定
	//--------------------------------------------------------
	// 表示する名前文字列を作成
	std::string sName = useful::SandString("\"", status.GetName(), "\"");

	// 名前の生成
	m_pName = CString2D::Create
	( // 引数
		FONT,			// フォントパス
		ITALIC,			// イタリック
		sName,			// 指定文字列
		name::POS,		// 原点位置
		HEIGHT,			// 文字縦幅
		name::ALIGN_X,	// 横配置
		name::ROT,		// 原点向き
		name::COL		// 色
	);
	if (m_pName == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pName->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	LV / HPタイトルの初期化 / 設定
	//--------------------------------------------------------
	// LV/HPタイトルの生成
	m_pLvHpTitle = CText2D::Create
	( // 引数
		FONT,						// フォントパス
		ITALIC,						// イタリック
		lvhp_title::POS,			// 原点位置
		HEIGHT,						// 文字縦幅
		lvhp_title::LINE_HEIGHT,	// 行間縦幅
		lvhp_title::ALIGN_X,		// 横配置
		lvhp_title::ALIGN_Y,		// 縦配置
		lvhp_title::ROT,			// 原点向き
		lvhp_title::COL				// 色
	);
	if (m_pLvHpTitle == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pLvHpTitle->SetPriority(PRIORITY);

	// テキストを割当
	loadtext::BindText(m_pLvHpTitle, loadtext::LoadText(PATH, TEXT_LV_HP));

	//--------------------------------------------------------
	//	LV / HP数値の初期化 / 設定
	//--------------------------------------------------------
	const std::string& rHP = std::to_string(status.GetHP());		// 現在の体力文字列
	const std::string& rMaxHP = std::to_string(status.GetMaxHP());	// 最大の体力文字列

	// LV/HP数値の生成
	m_pLvHpValue = CText2D::Create
	( // 引数
		FONT,						// フォントパス
		ITALIC,						// イタリック
		lvhp_value::POS,			// 原点位置
		HEIGHT,						// 文字縦幅
		lvhp_value::LINE_HEIGHT,	// 行間縦幅
		lvhp_value::ALIGN_X,		// 横配置
		lvhp_value::ALIGN_Y,		// 縦配置
		lvhp_value::ROT,			// 原点向き
		lvhp_value::COL				// 色
	);
	if (m_pLvHpValue == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pLvHpValue->SetPriority(PRIORITY);

	// LV/HP情報の追加
	m_pLvHpValue->PushBackString(std::to_string(status.GetLove()));
	m_pLvHpValue->PushBackString(useful::SandString(rHP, "/", rMaxHP));

	//--------------------------------------------------------
	//	ATK / DEFタイトルの初期化 / 設定
	//--------------------------------------------------------
	// ATK/DEFタイトルの生成
	m_pAtkDefTitle = CText2D::Create
	( // 引数
		FONT,						// フォントパス
		ITALIC,						// イタリック
		atkdef_title::POS,			// 原点位置
		HEIGHT,						// 文字縦幅
		atkdef_title::LINE_HEIGHT,	// 行間縦幅
		atkdef_title::ALIGN_X,		// 横配置
		atkdef_title::ALIGN_Y,		// 縦配置
		atkdef_title::ROT,			// 原点向き
		atkdef_title::COL			// 色
	);
	if (m_pAtkDefTitle == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pAtkDefTitle->SetPriority(PRIORITY);

	// テキストを割当
	loadtext::BindText(m_pAtkDefTitle, loadtext::LoadText(PATH, TEXT_ATK_DEF));

	//--------------------------------------------------------
	//	ATK / DEF数値の初期化 / 設定
	//--------------------------------------------------------
	const CItemData& rItemWpn = GET_MANAGER->GetItem()->GetInfo(status.GetWpnItemIdx());		// 武器アイテム情報
	const CItemData& rItemAmr = GET_MANAGER->GetItem()->GetInfo(status.GetAmrItemIdx());		// 防具アイテム情報
	const std::string& rAddAtk = std::to_string(rItemWpn.GetAddAtk() + rItemAmr.GetAddAtk());	// 攻撃力上昇量文字列
	const std::string& rAddDef = std::to_string(rItemWpn.GetAddDef() + rItemAmr.GetAddDef());	// 防御力上昇量文字列

	// ATK/DEF数値の生成
	m_pAtkDefValue = CText2D::Create
	( // 引数
		FONT,						// フォントパス
		ITALIC,						// イタリック
		atkdef_value::POS,			// 原点位置
		HEIGHT,						// 文字縦幅
		atkdef_value::LINE_HEIGHT,	// 行間縦幅
		atkdef_value::ALIGN_X,		// 横配置
		atkdef_value::ALIGN_Y,		// 縦配置
		atkdef_value::ROT,			// 原点向き
		atkdef_value::COL			// 色
	);
	if (m_pAtkDefValue == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pAtkDefValue->SetPriority(PRIORITY);

	// 攻撃力情報の追加
	std::string sAtk = std::to_string(status.GetCurAtk());	// 自前のステータスを文字列に追加
	sAtk.append(useful::SandString(" (", rAddAtk, ")"));	// 装備のプラスステータスを文字列に追加
	m_pAtkDefValue->PushBackString(sAtk);					// 作成した文字列を割当

	// 防御力情報の追加
	std::string sDef = std::to_string(status.GetCurDef());	// 自前のステータスを文字列に追加
	sDef.append(useful::SandString(" (", rAddDef, ")"));	// 装備のプラスステータスを文字列に追加
	m_pAtkDefValue->PushBackString(sDef);					// 作成した文字列を割当

	//--------------------------------------------------------
	//	EXP / NEXTタイトルの初期化 / 設定
	//--------------------------------------------------------
	// EXP/NEXTタイトルの生成
	m_pExpNextTitle = CText2D::Create
	( // 引数
		FONT,						// フォントパス
		ITALIC,						// イタリック
		expnext_title::POS,			// 原点位置
		HEIGHT,						// 文字縦幅
		expnext_title::LINE_HEIGHT,	// 行間縦幅
		expnext_title::ALIGN_X,		// 横配置
		expnext_title::ALIGN_Y,		// 縦配置
		expnext_title::ROT,			// 原点向き
		expnext_title::COL			// 色
	);
	if (m_pExpNextTitle == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pExpNextTitle->SetPriority(PRIORITY);

	// テキストを割当
	loadtext::BindText(m_pExpNextTitle, loadtext::LoadText(PATH, TEXT_EXP_NEXT));

	//--------------------------------------------------------
	//	EXP / NEXT数値の初期化 / 設定
	//--------------------------------------------------------
	// EXP/NEXT数値の生成
	m_pExpNextValue = CText2D::Create
	( // 引数
		FONT,						// フォントパス
		ITALIC,						// イタリック
		expnext_value::POS,			// 原点位置
		HEIGHT,						// 文字縦幅
		expnext_value::LINE_HEIGHT,	// 行間縦幅
		expnext_value::ALIGN_X,		// 横配置
		expnext_value::ALIGN_Y,		// 縦配置
		expnext_value::ROT,			// 原点向き
		expnext_value::COL			// 色
	);
	if (m_pExpNextValue == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pExpNextValue->SetPriority(PRIORITY);

	// 現在経験値/次経験値の追加
	const int nCurExp = status.GetExp();	// 現在の経験値
	m_pExpNextValue->PushBackString(std::to_string(nCurExp));
	m_pExpNextValue->PushBackString(std::to_string(status.GetCurNext() - nCurExp));

	//--------------------------------------------------------
	//	WPN / AMRタイトルの初期化 / 設定
	//--------------------------------------------------------
	// WPN/AMRタイトルの生成
	m_pWpnAmrTitle = CText2D::Create
	( // 引数
		FONT,						// フォントパス
		ITALIC,						// イタリック
		wpnamr_title::POS,			// 原点位置
		HEIGHT,						// 文字縦幅
		wpnamr_title::LINE_HEIGHT,	// 行間縦幅
		wpnamr_title::ALIGN_X,		// 横配置
		wpnamr_title::ALIGN_Y,		// 縦配置
		wpnamr_title::ROT,			// 原点向き
		wpnamr_title::COL			// 色
	);
	if (m_pWpnAmrTitle == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pWpnAmrTitle->SetPriority(PRIORITY);

	// テキストを割当
	loadtext::BindText(m_pWpnAmrTitle, loadtext::LoadText(PATH, TEXT_WPN_AMR));

	//--------------------------------------------------------
	//	WPN / AMR名称の初期化 / 設定
	//--------------------------------------------------------
	// WPN/AMR名称の生成
	m_pWpnAmrName = CText2D::Create
	( // 引数
		FONT,						// フォントパス
		ITALIC,						// イタリック
		wpnamr_name::POS,			// 原点位置
		HEIGHT,						// 文字縦幅
		wpnamr_name::LINE_HEIGHT,	// 行間縦幅
		wpnamr_name::ALIGN_X,		// 横配置
		wpnamr_name::ALIGN_Y,		// 縦配置
		wpnamr_name::ROT,			// 原点向き
		wpnamr_name::COL			// 色
	);
	if (m_pWpnAmrName == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pWpnAmrName->SetPriority(PRIORITY);

	// 武器/防具名の追加
	m_pWpnAmrName->PushBackString(rItemWpn.GetName());
	m_pWpnAmrName->PushBackString(rItemAmr.GetName());

	//--------------------------------------------------------
	//	GOLDタイトルの初期化 / 設定
	//--------------------------------------------------------
	// GOLDタイトルの生成
	m_pGoldTitle = CString2D::Create
	( // 引数
		FONT,					// フォントパス
		ITALIC,					// イタリック
		L"",					// 指定文字列
		gold_title::POS,		// 原点位置
		HEIGHT,					// 文字縦幅
		gold_title::ALIGN_X,	// 横配置
		gold_title::ROT,		// 原点向き
		gold_title::COL			// 色
	);

	// 優先順位を設定
	m_pGoldTitle->SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindString(m_pGoldTitle, loadtext::LoadText(PATH, TEXT_GOLD));

	//--------------------------------------------------------
	//	GOLD数値の初期化 / 設定
	//--------------------------------------------------------
	// GOLD数値の生成
	m_pGoldValue = CString2D::Create
	( // 引数
		FONT,					// フォントパス
		ITALIC,					// イタリック
		L"",					// 指定文字列
		gold_value::POS,		// 原点位置
		HEIGHT,					// 文字縦幅
		gold_value::ALIGN_X,	// 横配置
		gold_value::ROT,		// 原点向き
		gold_value::COL			// 色
	);

	// 優先順位を設定
	m_pGoldValue->SetPriority(PRIORITY);

	// 所持金の追加
	m_pGoldValue->SetString(std::to_string(status.GetNumGold()));

	//--------------------------------------------------------
	//	KILLS情報の生成
	//--------------------------------------------------------
	int nNumKill = status.GetNumKill();	// キル数
	if (nNumKill > 0)	// TODO：1Killだけじゃ表示されなかったわ
	{ // 一体でも殺したことがある場合

		//----------------------------------------------------
		//	KILLSタイトルの初期化 / 設定
		//----------------------------------------------------
		// KILLSタイトルの生成
		m_pKillsTitle = CString2D::Create
		( // 引数
			FONT,					// フォントパス
			ITALIC,					// イタリック
			L"",					// 指定文字列
			kills_title::POS,		// 原点位置
			HEIGHT,					// 文字縦幅
			kills_title::ALIGN_X,	// 横配置
			kills_title::ROT,		// 原点向き
			kills_title::COL		// 色
		);

		// 優先順位を設定
		m_pKillsTitle->SetPriority(PRIORITY);

		// 文字列を割当
		loadtext::BindString(m_pKillsTitle, loadtext::LoadText(PATH, TEXT_KILLS));

		//----------------------------------------------------
		//	KILLS数値の初期化 / 設定
		//----------------------------------------------------
		// KILLS数値の生成
		m_pKillsValue = CString2D::Create
		( // 引数
			FONT,					// フォントパス
			ITALIC,					// イタリック
			L"",					// 指定文字列
			kills_value::POS,		// 原点位置
			HEIGHT,					// 文字縦幅
			kills_value::ALIGN_X,	// 横配置
			kills_value::ROT,		// 原点向き
			kills_value::COL		// 色
		);

		// 優先順位を設定
		m_pKillsValue->SetPriority(PRIORITY);

		// キル数の追加
		m_pKillsValue->SetString(std::to_string(nNumKill));
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSelectStatusUI::Uninit()
{
	// ソウルカーソルの描画をONにする
	SetSoulCursorDraw(true);

	// 名前の終了
	SAFE_UNINIT(m_pName);

	// LV/HPタイトルの終了
	SAFE_UNINIT(m_pLvHpTitle);

	// LV/HP数値の終了
	SAFE_UNINIT(m_pLvHpValue);

	// ATK/DEFタイトルの終了
	SAFE_UNINIT(m_pAtkDefTitle);

	// ATK/DEF数値の終了
	SAFE_UNINIT(m_pAtkDefValue);

	// EXP/NEXTタイトルの終了
	SAFE_UNINIT(m_pExpNextTitle);

	// EXP/NEXT数値の終了
	SAFE_UNINIT(m_pExpNextValue);

	// WPN/AMRタイトルの終了
	SAFE_UNINIT(m_pWpnAmrTitle);

	// WPN/AMR名称の終了
	SAFE_UNINIT(m_pWpnAmrName);

	// GOLDタイトルの終了
	SAFE_UNINIT(m_pGoldTitle);

	// GOLD数値の終了
	SAFE_UNINIT(m_pGoldValue);

	// KILLSタイトルの終了
	SAFE_UNINIT(m_pKillsTitle);

	// KILLS数値の終了
	SAFE_UNINIT(m_pKillsValue);

	// セレクトUIの終了
	CSelectUI::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSelectStatusUI::Update(const float fDeltaTime)
{
	// セレクトUIの更新
	CSelectUI::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CSelectStatusUI::Draw(CShader* pShader)
{
	// セレクトUIの描画
	CSelectUI::Draw(pShader);
}

//============================================================
//	メニュー生成可能フラグの取得処理
//============================================================
bool CSelectStatusUI::IsCreateOK()
{
	// いつでも生成可能
	return true;
}
