//============================================================
//
//	ミニステータスメニュー処理 [menuStatusUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "menuStatusUI.h"
#include "menuUI.h"
#include "frame2D.h"
#include "string2D.h"
#include "text2D.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 5;	// ミニステータスメニューの優先順位

	namespace frame
	{
		const VECTOR3 POS	= VECTOR3(155.0f, 160.0f, 0.0f);	// フレーム位置
		const VECTOR3 ROT	= VEC3_ZERO;						// フレーム向き
		const VECTOR3 SIZE	= VECTOR3(200.0f, 145.0f, 0.0f);	// フレーム大きさ
	}

	namespace name
	{
		const char*	FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス	// TODO：多分フォント違うの使ってる
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 26.0f;	// 文字縦幅

		const VECTOR3	POS = VECTOR3(68.0f, 115.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}

	namespace status
	{
		const char*	FONT = "data\\FONT\\Crypt of Tomorrow.ttf";	// フォントパス7
		const char*	PATH = "data\\TEXT\\menu.txt";	// テキストパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 22.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 26.0f;	// 行間縦幅

		const VECTOR3	POS = VECTOR3(68.0f, 225.5f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;			// 向き
		const COLOR		COL = color::White();		// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;		// 横配置
		const EAlignY	ALIGN_Y = YALIGN_BOTTOM;	// 縦配置
	}

	namespace value
	{
		const char*	FONT		= status::FONT;			// フォントパス
		const bool	ITALIC		= status::ITALIC;		// イタリック
		const float	CHAR_HEIGHT	= status::CHAR_HEIGHT;	// 文字縦幅
		const float	LINE_HEIGHT = status::LINE_HEIGHT;	// 行間縦幅

		const VECTOR3	POS = VECTOR3(115.0f, status::POS.y, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;			// 向き
		const COLOR		COL = color::White();		// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;		// 横配置
		const EAlignY	ALIGN_Y = YALIGN_BOTTOM;	// 縦配置
	}
}

//************************************************************
//	子クラス [CMenuStatusUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CMenuStatusUI::CMenuStatusUI() : CObject(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY),
	m_pFrame	(nullptr),	// フレーム情報
	m_pName		(nullptr),	// 名前情報
	m_pStatus	(nullptr),	// ステータス情報
	m_pValue	(nullptr)	// ステータス数値情報
{

}

//============================================================
//	デストラクタ
//============================================================
CMenuStatusUI::~CMenuStatusUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CMenuStatusUI::Init()
{
	// メンバ変数を初期化
	m_pFrame	= nullptr;	// フレーム情報
	m_pName		= nullptr;	// 名前情報
	m_pStatus	= nullptr;	// ステータス情報
	m_pValue	= nullptr;	// ステータス数値情報

	// フレームの生成
	m_pFrame = CFrame2D::Create
	( // 引数
		frame::POS,	// 位置
		frame::ROT,	// 向き
		frame::SIZE	// 大きさ
	);
	if (m_pFrame == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pFrame->SetPriority(PRIORITY);

	// 名前の生成
	m_pName = CString2D::Create
	( // 引数
		name::FONT,		// フォントパス
		name::ITALIC,	// イタリック
		L"おぷおぷ",	// 指定文字列	// TODO：名前の保存システムを作成
		name::POS,		// 原点位置
		name::HEIGHT,	// 文字縦幅
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

	// ステータスの生成
	m_pStatus = CText2D::Create
	( // 引数
		status::FONT,			// フォントパス
		status::ITALIC,			// イタリック
		status::POS,			// 原点位置
		status::CHAR_HEIGHT,	// 文字縦幅
		status::LINE_HEIGHT,	// 行間縦幅
		status::ALIGN_X,		// 横配置
		status::ALIGN_Y,		// 縦配置
		status::ROT,			// 原点向き
		status::COL				// 色
	);
	if (m_pStatus == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pStatus->SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindText(m_pStatus, loadtext::LoadText(status::PATH, CMenuUI::TEXT_MINI_STATUS));

	// ステータス数値の生成
	m_pValue = CText2D::Create
	( // 引数
		value::FONT,		// フォントパス
		value::ITALIC,		// イタリック
		value::POS,			// 原点位置
		value::CHAR_HEIGHT,	// 文字縦幅
		value::LINE_HEIGHT,	// 行間縦幅
		value::ALIGN_X,		// 横配置
		value::ALIGN_Y,		// 縦配置
		value::ROT,			// 原点向き
		value::COL			// 色
	);
	if (m_pValue == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// TODO：ステータスの取得
#if 1
	m_pValue->PushBackString("1");
	m_pValue->PushBackString(useful::SandString("20", "/", "20"));
	m_pValue->PushBackString("0");
#endif

	// 優先順位を設定
	m_pValue->SetPriority(PRIORITY);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CMenuStatusUI::Uninit()
{
	// フレームの終了
	SAFE_UNINIT(m_pFrame);

	// 名前の終了
	SAFE_UNINIT(m_pName);

	// ステータスの終了
	SAFE_UNINIT(m_pStatus);

	// ステータス数値の終了
	SAFE_UNINIT(m_pValue);

	// オブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CMenuStatusUI::Update(const float fDeltaTime)
{

}

//============================================================
//	描画処理
//============================================================
void CMenuStatusUI::Draw(CShader* /*pShader*/)
{

}

//============================================================
//	生成処理
//============================================================
CMenuStatusUI* CMenuStatusUI::Create()
{
	// ミニステータスメニューの生成
	CMenuStatusUI* pMenuStatusUI = new CMenuStatusUI;
	if (pMenuStatusUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// ミニステータスメニューの初期化
		if (FAILED(pMenuStatusUI->Init()))
		{ // 初期化に失敗した場合

			// ミニステータスメニューの破棄
			SAFE_DELETE(pMenuStatusUI);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pMenuStatusUI;
	}
}
