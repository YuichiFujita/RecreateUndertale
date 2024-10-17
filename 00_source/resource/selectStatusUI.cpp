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
#include "loadtext.h"
#include "string2D.h"
#include "text2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char	*FONT	 = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
	const char	*PASS	 = "data\\TEXT\\selectStatus.txt";				// テキストパス
	const bool	ITALIC	 = false;	// イタリック
	const float	HEIGHT	 = 42.0f;	// 文字縦幅
	const int	PRIORITY = 6;		// フルステータスメニューの優先順位

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(555.0f, 386.5f, 0.0f);	// フレーム位置
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// フレーム向き
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(525.0f, 600.0f, 0.0f);	// フレーム大きさ
	}

	namespace name
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 140.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
	}

	namespace lvhp_title
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 200.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
		const float	LINE_HEIGHT = 53.0f;			// 行間縦幅
	}

	namespace lvhp_value
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(402.0f, 200.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
		const float	LINE_HEIGHT = 53.0f;			// 行間縦幅
	}

	namespace atkdef_title
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 330.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
		const float	LINE_HEIGHT = 53.0f;			// 行間縦幅
	}

	namespace atkdef_value
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(402.0f, 330.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
		const float	LINE_HEIGHT = 53.0f;			// 行間縦幅
	}

	namespace expnext_title
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(570.0f, 330.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
		const float	LINE_HEIGHT = 53.0f;			// 行間縦幅
	}

	namespace expnext_value
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(672.0f, 330.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
		const float	LINE_HEIGHT = 53.0f;			// 行間縦幅
	}

	namespace wpnamr_title
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 460.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
		const float	LINE_HEIGHT = 53.0f;			// 行間縦幅
	}

	namespace wpnamr_name
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(402.0f, 460.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
		const float	LINE_HEIGHT = 53.0f;			// 行間縦幅
	}

	namespace gold_title
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 615.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
	}

	namespace gold_value
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(423.0f, 615.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
	}

	namespace kills_title
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(500.0f, 615.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
	}

	namespace kills_value
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(627.0f, 615.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR			COL = color::White();	// 色
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
HRESULT CSelectStatusUI::Init(void)
{
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

		// 失敗を返す
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
	std::string sName = useful::SandString("\"", "おぷおぷ", "\"");	// TODO：名前の外部読込

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

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pLvHpTitle->SetPriority(PRIORITY);

	// テキストを割当
	loadtext::BindText(m_pLvHpTitle, loadtext::LoadText(PASS, TEXT_LV_HP));

	//--------------------------------------------------------
	//	LV / HP数値の初期化 / 設定
	//--------------------------------------------------------
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

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pLvHpValue->SetPriority(PRIORITY);

	// TODO：ステータス情報読込
#if 1
	m_pLvHpValue->PushBackString("1");
	m_pLvHpValue->PushBackString(useful::SandString("20", "/", "20"));
#endif

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

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pAtkDefTitle->SetPriority(PRIORITY);

	// テキストを割当
	loadtext::BindText(m_pAtkDefTitle, loadtext::LoadText(PASS, TEXT_ATK_DEF));

	//--------------------------------------------------------
	//	ATK / DEF数値の初期化 / 設定
	//--------------------------------------------------------
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

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pAtkDefValue->SetPriority(PRIORITY);

	// TODO：ステータス情報 / 装備情報の読込
#if 1
	// 攻撃力のステータス文字列を追加
	std::string sAtk = std::to_string(0);							// 自前のステータスを文字列に追加
	sAtk.append(useful::SandString(" (", std::to_string(3), ")"));	// 装備のプラスステータスを文字列に追加
	m_pAtkDefValue->PushBackString(sAtk);							// 作成した文字列を割当

	// 防御力のステータス文字列を追加
	std::string sDef = std::to_string(0);							// 自前のステータスを文字列に追加
	sDef.append(useful::SandString(" (", std::to_string(3), ")"));	// 装備のプラスステータスを文字列に追加
	m_pAtkDefValue->PushBackString(sDef);							// 作成した文字列を割当
#endif

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

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pExpNextTitle->SetPriority(PRIORITY);

	// テキストを割当
	loadtext::BindText(m_pExpNextTitle, loadtext::LoadText(PASS, TEXT_EXP_NEXT));

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

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pExpNextValue->SetPriority(PRIORITY);

	// TODO：ステータス情報読込
#if 1
	m_pExpNextValue->PushBackString("0");
	m_pExpNextValue->PushBackString("10");
#endif

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

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pWpnAmrTitle->SetPriority(PRIORITY);

	// テキストを割当
	loadtext::BindText(m_pWpnAmrTitle, loadtext::LoadText(PASS, TEXT_WPN_AMR));

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

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pWpnAmrName->SetPriority(PRIORITY);

	// TODO：装備情報から名称取得
#if 1
	m_pWpnAmrName->PushBackString("ぼうきれ");
	m_pWpnAmrName->PushBackString("ほうたい");
#endif

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
	loadtext::BindString(m_pGoldTitle, loadtext::LoadText(PASS, TEXT_GOLD));

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

	// TODO：所持金取得
#if 1
	m_pGoldValue->SetString("0");
#endif

	// TODO：キル数取得
#if 1
	int nNumKill = 0;	// キル数
#endif

	if (nNumKill > 0)
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
		loadtext::BindString(m_pKillsTitle, loadtext::LoadText(PASS, TEXT_KILLS));

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

		// 表示文字列を指定
		m_pKillsValue->SetString(std::to_string(nNumKill));
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSelectStatusUI::Uninit(void)
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
void CSelectStatusUI::Draw(CShader *pShader)
{
	// セレクトUIの描画
	CSelectUI::Draw(pShader);
}
