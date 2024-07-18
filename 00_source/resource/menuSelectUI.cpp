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
#include "manager.h"
#include "string2D.h"
#include "loadtext.h"
#include "selectItemUI.h"
#include "selectStatusUI.h"
#include "selectPhoneUI.h"

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

	namespace soul
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(97.5f, 308.5f, 0.0f);	// ソウルカーソル位置
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(26.5f, 26.5f, 0.0f);	// ソウルカーソル大きさ
	}
}

//************************************************************
//	子クラス [CMenuSelectUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CMenuSelectUI::CMenuSelectUI() : CObject(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY),
	m_pFrame		(nullptr),	// フレーム情報
	m_pSoul			(nullptr),	// ソウルカーソル情報
	m_pSelectMenu	(nullptr),	// 選択メニュー情報
	m_nCurSelect	(0)			// 現在の選択肢
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
	m_pFrame		= nullptr;	// フレーム情報
	m_pSoul			= nullptr;	// ソウルカーソル情報
	m_pSelectMenu	= nullptr;	// 選択メニュー情報
	m_nCurSelect	= 0;		// 現在の選択肢

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

	// ソウルカーソルの生成
	m_pSoul = CObject2D::Create
	( // 引数
		soul::POS,	// 位置
		soul::SIZE	// 大きさ
	);
	if (m_pSoul == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// ソウルテクスチャを割当
	m_pSoul->BindTexture("data\\TEXTURE\\spr_heartsmall.png");	// TODO：パス

	// ラベルを設定
	m_pSoul->SetLabel(CObject::LABEL_UI);

	// 優先順位を設定
	m_pSoul->SetPriority(PRIORITY);

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

	// ソウルカーソルの終了
	SAFE_UNINIT(m_pSoul);

	// オブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CMenuSelectUI::Update(const float fDeltaTime)
{
	if (m_pSelectMenu == nullptr)
	{ // メニューを選択していない場合

		// 選択の更新
		UpdateSelect();

		// 決定の更新
		UpdateDecide();
	}
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

//============================================================
//	選択の更新処理
//============================================================
void CMenuSelectUI::UpdateSelect(void)
{
	// 選択肢操作
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
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

	// 文字位置オフセットを計算
	D3DXVECTOR3 offset = D3DXVECTOR3(0.0f, select::LINE_HEIGHT * m_nCurSelect, 0.0f);

	// ソウルカーソルの位置を移動
	m_pSoul->SetVec3Position(soul::POS + offset);
}

//============================================================
//	決定の更新処理
//============================================================
void CMenuSelectUI::UpdateDecide(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_Z) || pKey->IsTrigger(DIK_RETURN))
	{
		// 現在選択中のメニューに変更
		ChangeSelectMenu((ESelect)m_nCurSelect);
	}
}

//============================================================
//	選択メニューの終了処理
//============================================================
void CMenuSelectUI::UninitSelectMenu(void)
{
	// 選択メニューの終了
	SAFE_UNINIT(m_pSelectMenu);
}

//============================================================
//	選択メニューの変更処理
//============================================================
HRESULT CMenuSelectUI::ChangeSelectMenu(const CMenuSelectUI::ESelect select)
{
	// 選択メニューの終了
	SAFE_UNINIT(m_pSelectMenu);

	// 選択肢に応じてメニューを生成
	assert(m_pSelectMenu == nullptr);
	m_pSelectMenu = CSelect::Create
	( // 引数
		std::bind(&CMenuSelectUI::UninitSelectMenu, this),	// 選択メニュー終了関数
		m_pSoul,	// ソウルカーソル情報
		select		// 選択肢
	);
	if (m_pSelectMenu == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//************************************************************
//	子クラス [CSelect] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSelect::CSelect(AFuncUninit funcUninit, CObject2D *pSoul) : CObject(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY),
	m_funcUninitMenu (funcUninit),	// 選択メニュー終了関数ポインタ
	m_pSoul			 (pSoul),		// ソウルカーソル情報
	m_pFrame		 (nullptr)		// フレーム情報
{

}

//============================================================
//	デストラクタ
//============================================================
CSelect::~CSelect()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSelect::Init(void)
{
	// メンバ変数を初期化
	m_pFrame = nullptr;	// フレーム情報

	// フレームの生成
	m_pFrame = CFrame2D::Create
	( // 引数
		VEC3_ZERO,	// 位置
		VEC3_ZERO,	// 向き
		VEC3_ZERO	// 大きさ
	);
	if (m_pFrame == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pFrame->SetPriority(PRIORITY);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSelect::Uninit(void)
{
	// フレームの終了
	SAFE_UNINIT(m_pFrame);

	// オブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CSelect::Update(const float fDeltaTime)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_X) || pKey->IsTrigger(DIK_LSHIFT) || pKey->IsTrigger(DIK_RSHIFT))
	{
		// 選択メニューの終了
		m_funcUninitMenu();
	}
}

//============================================================
//	描画処理
//============================================================
void CSelect::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	生成処理
//============================================================
CSelect *CSelect::Create
(
	AFuncUninit funcUninit,	// 選択メニュー終了関数
	CObject2D *pSoul,		// ソウルカーソル情報
	const CMenuSelectUI::ESelect select	// 選択肢
)
{
	// セレクトの生成
	CSelect *pSelect = nullptr;	// セレクト情報
	switch (select)
	{ // 選択肢ごとの処理
	case CMenuSelectUI::SELECT_ITEM:
		pSelect = new CSelectItemUI(funcUninit, pSoul);
		break;

	case CMenuSelectUI::SELECT_STATUS:
		pSelect = new CSelectStatusUI(funcUninit, pSoul);
		break;

	case CMenuSelectUI::SELECT_PHONE:
		pSelect = new CSelectPhoneUI(funcUninit, pSoul);
		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	if (pSelect == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// セレクトの初期化
		if (FAILED(pSelect->Init()))
		{ // 初期化に失敗した場合

			// セレクトの破棄
			SAFE_DELETE(pSelect);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pSelect;
	}
}
