//============================================================
//
//	ステータスメニュー処理 [menuStatusUI.cpp]
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
	const int PRIORITY = 6;	// ステータスメニューの優先順位

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(155.0f, 160.0f, 0.0f);	// フレーム位置
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// フレーム向き
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(200.0f, 140.0f, 0.0f);	// フレーム大きさ
	}

	namespace name
	{
		const char	*FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス	// TODO：多分フォント違うの使ってる
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 26.0f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(68.0f, 115.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
	}

	namespace status
	{
		const char	*FONT = "data\\FONT\\Crypt of Tomorrow.ttf";	// フォントパス7
		const char	*PASS = "data\\TEXT\\menu.txt";	// テキストパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 22.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 26.0f;	// 行間縦幅

		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_BOTTOM;	// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(68.0f, 223.0f, 0.0f);		// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
	}

	namespace value
	{
		const char	*FONT = "data\\FONT\\Crypt of Tomorrow.ttf";	// フォントパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 22.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 26.0f;	// 行間縦幅

		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_BOTTOM;	// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(115.0f, 223.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
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
HRESULT CMenuStatusUI::Init(void)
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

		// 失敗を返す
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

		// 失敗を返す
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

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pStatus->SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindText(m_pStatus, loadtext::LoadText(status::PASS, CMenuUI::TEXT_MINI_STATUS));

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

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// TODO：ステータスの取得
#if 1
	m_pValue->AddString(L"1");
	m_pValue->AddString(L"20/20");
	m_pValue->AddString(L"0");
#endif

	// 優先順位を設定
	m_pValue->SetPriority(PRIORITY);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CMenuStatusUI::Uninit(void)
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
void CMenuStatusUI::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	生成処理
//============================================================
CMenuStatusUI *CMenuStatusUI::Create(void)
{
	// ステータスメニューの生成
	CMenuStatusUI *pMenuStatusUI = new CMenuStatusUI;
	if (pMenuStatusUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// ステータスメニューの初期化
		if (FAILED(pMenuStatusUI->Init()))
		{ // 初期化に失敗した場合

			// ステータスメニューの破棄
			SAFE_DELETE(pMenuStatusUI);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pMenuStatusUI;
	}
}
