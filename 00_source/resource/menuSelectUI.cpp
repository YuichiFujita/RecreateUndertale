//============================================================
//
//	セレクトメニュー処理 [menuSelectUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "menuSelectUI.h"
#include "menuUI.h"
#include "frame2D.h"
#include "string2D.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 6;	// セレクトメニューの優先順位

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(155.0f, 362.5f, 0.0f);	// フレーム位置
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// フレーム向き
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(200.0f, 205.0f, 0.0f);	// フレーム大きさ
	}

	namespace select
	{
		const char	*FONT		= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const char	*PASS		= "data\\TEXT\\menu.txt";	// テキストパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 43.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 53.0f;	// 行間縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const D3DXVECTOR3 POS = D3DXVECTOR3(125.0f, 308.5f, 0.0f);	// 位置
		const D3DXVECTOR3 ROT = VEC3_ZERO;			// 向き
		const D3DXCOLOR COL_DEFAULT	= XCOL_WHITE;	// 通常色
		const D3DXCOLOR COL_CHOICE	= XCOL_YELLOW;	// 選択色
	}
}

//************************************************************
//	子クラス [CMenuSelectUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CMenuSelectUI::CMenuSelectUI() : CObject(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY),
	m_pFrame	(nullptr)	// フレーム情報
{
	// メンバ変数をクリア
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢情報
}

//============================================================
//	デストラクタ
//============================================================
CMenuSelectUI::~CMenuSelectUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CMenuSelectUI::Init(void)
{
	// メンバ変数を初期化
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢情報
	m_pFrame = nullptr;	// フレーム情報

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

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の項目数分繰り返す

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
		if (m_apSelect[i] == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_apSelect[i]->SetPriority(PRIORITY);

		// 文字列を割当
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(select::PASS, CMenuUI::TEXT_ITEM + i));
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CMenuSelectUI::Uninit(void)
{
	// フレームの終了
	SAFE_UNINIT(m_pFrame);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の項目数分繰り返す

		// 選択肢の終了
		SAFE_UNINIT(m_apSelect[i]);
	}

	// オブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CMenuSelectUI::Update(const float fDeltaTime)
{

}

//============================================================
//	描画処理
//============================================================
void CMenuSelectUI::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	生成処理
//============================================================
CMenuSelectUI *CMenuSelectUI::Create(void)
{
	// セレクトメニューの生成
	CMenuSelectUI *pMenuSelectUI = new CMenuSelectUI;
	if (pMenuSelectUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// セレクトメニューの初期化
		if (FAILED(pMenuSelectUI->Init()))
		{ // 初期化に失敗した場合

			// セレクトメニューの破棄
			SAFE_DELETE(pMenuSelectUI);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pMenuSelectUI;
	}
}
