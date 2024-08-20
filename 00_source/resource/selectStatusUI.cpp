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
	const char	*PASS	 = "data\\TEXT\\start.txt";						// テキストパス	// TODO：パスどう分けるか
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
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
	}

	namespace lvhp_title
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 205.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
		const float	LINE_HEIGHT = 44.0f;		// 行間縦幅
	}

	namespace lvhp_value
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(415.0f, 205.5f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
		const float	LINE_HEIGHT = 44.0f;		// 行間縦幅
	}
}

//************************************************************
//	子クラス [CSelectStatusUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSelectStatusUI::CSelectStatusUI(AFuncUninit funcUninit, CObject2D *pSoul) : CSelect(funcUninit, pSoul),
	m_pName		 (nullptr),	// 名前情報
	m_pLvHpTitle (nullptr),	// レベル/HPタイトル情報
	m_pLvHpValue (nullptr)	// レベル/HP数値情報
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
	m_pName		 = nullptr;	// 名前情報
	m_pLvHpTitle = nullptr;	// レベル/HPタイトル情報
	m_pLvHpValue = nullptr;	// レベル/HP数値情報

	//--------------------------------------------------------
	//	親クラスの初期化 / 設定
	//--------------------------------------------------------
	// セレクトの初期化
	if (FAILED(CSelect::Init()))
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
	SetFrameSizing(frame::SIZE);

	// ソウルカーソルの描画をOFFにする
	SetSoulCursorDraw(false);

	//--------------------------------------------------------
	//	名前の初期化 / 設定
	//--------------------------------------------------------
	// 表示する名前文字列を作成
	std::wstring wsName;
	wsName.append(L"\"");		// ”を先頭に追加
	wsName.append(L"おぷおぷ");	// 名前を追加	// TODO：外部読込
	wsName.append(L"\"");		// ”を最後尾に追加

	// 名前の生成
	m_pName = CString2D::Create
	( // 引数
		FONT,			// フォントパス
		ITALIC,			// イタリック
		wsName,			// 指定文字列
		name::POS,		// 原点位置
		HEIGHT,			// 文字縦幅
		name::ALIGN_X,	// 横配置
		name::ROT,		// 原点向き
		name::COL		// 色
	);

	// 優先順位を設定
	m_pName->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	レベル / HPタイトルの初期化 / 設定
	//--------------------------------------------------------
	// レベル/HPタイトルの生成
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

	// TODO：外部ファイル化
#if 1
	m_pLvHpTitle->AddString(L"LV");
	m_pLvHpTitle->AddString(L"HP");
#endif

	//--------------------------------------------------------
	//	レベル / HP数値の初期化 / 設定
	//--------------------------------------------------------
	// レベル/HP数値の生成
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
	m_pLvHpValue->AddString(L"1");
	m_pLvHpValue->AddString(L"20/20");
#endif

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

	// レベル/HPタイトルの終了
	SAFE_UNINIT(m_pLvHpTitle);

	// レベル/HP数値の終了
	SAFE_UNINIT(m_pLvHpValue);

	// セレクトの終了
	CSelect::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSelectStatusUI::Update(const float fDeltaTime)
{
	// セレクトの更新
	CSelect::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CSelectStatusUI::Draw(CShader *pShader)
{
	// セレクトの描画
	CSelect::Draw(pShader);
}
