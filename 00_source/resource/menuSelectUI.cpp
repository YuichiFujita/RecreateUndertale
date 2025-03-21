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
	const int MENU_PRIO = 5;	// メニューの優先順位
	const int SOUL_PRIO = 6;	// カーソルの優先順位

	namespace frame
	{
		const VECTOR3 POS	= VECTOR3(155.0f, 362.5f, 0.0f);	// フレーム位置
		const VECTOR3 ROT	= VEC3_ZERO;						// フレーム向き
		const VECTOR3 SIZE	= VECTOR3(200.0f, 205.0f, 0.0f);	// フレーム大きさ
	}

	namespace select
	{
		const char*	FONT		= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const char*	PATH		= "data\\TXT\\TEXT\\menu.txt";	// テキストパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 43.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 53.0f;	// 行間縦幅

		const VECTOR3 POS = VECTOR3(125.0f, 308.5f, 0.0f);	// 位置
		const VECTOR3 ROT = VEC3_ZERO;			// 向き
		const EAlignX ALIGN_X = XALIGN_LEFT;	// 横配置

		const COLOR COL_UNCREATE = COLOR(0.5f, 0.5f, 0.5f, 1.0f);	// 生成不可色
		const COLOR COL_DEFAULT = color::White();	// 通常色
		const COLOR COL_CHOICE = color::Yellow();	// 選択色

		const COLOR COL[] =	// 選択肢色
		{
			COL_UNCREATE,	// 生成不可色
			COL_DEFAULT,	// 通常色
		};
	}

	namespace soul
	{
		const char* PATH	= "data\\TEXTURE\\spr_heartsmall.png";	// ソウルカーソルテクスチャパス
		const VECTOR3 POS	= VECTOR3(97.5f, 308.5f, 0.0f);			// ソウルカーソル位置
		const VECTOR3 SIZE	= VECTOR3(26.5f, 26.5f, 0.0f);			// ソウルカーソル大きさ
	}
}

//************************************************************
//	子クラス [CMenuSelectUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CMenuSelectUI::CMenuSelectUI() : CObject(CObject::LABEL_UI, CObject::DIM_3D, MENU_PRIO),
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
HRESULT CMenuSelectUI::Init()
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

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pFrame->SetPriority(MENU_PRIO);

	// ソウルカーソルの生成
	m_pSoul = CObject2D::Create
	( // 引数
		soul::POS,	// 位置
		soul::SIZE	// 大きさ
	);
	if (m_pSoul == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ソウルテクスチャを割当
	m_pSoul->BindTexture(soul::PATH);

	// ラベルを設定
	m_pSoul->SetLabel(CObject::LABEL_UI);

	// 優先順位を設定
	m_pSoul->SetPriority(SOUL_PRIO);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の項目数分繰り返す

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
			select::COL[(int)IsCreateOK((ESelect)i)]	// 色
		);
		if (m_apSelect[i] == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_apSelect[i]->SetPriority(MENU_PRIO);

		// 文字列を割当
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(select::PATH, CMenuUI::TEXT_ITEM + i));
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CMenuSelectUI::Uninit()
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

	// 選択メニューの終了
	SAFE_UNINIT(m_pSelectMenu);

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
void CMenuSelectUI::Draw(CShader* /*pShader*/)
{

}

//============================================================
//	生成処理
//============================================================
CMenuSelectUI* CMenuSelectUI::Create()
{
	// セレクトメニューの生成
	CMenuSelectUI* pMenuSelectUI = new CMenuSelectUI;
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
void CMenuSelectUI::UpdateSelect()
{
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

	// 文字位置オフセットを計算
	VECTOR3 offset = VECTOR3(0.0f, select::LINE_HEIGHT * m_nCurSelect, 0.0f);

	// ソウルカーソルの位置を移動
	m_pSoul->SetVec3Position(soul::POS + offset);
}

//============================================================
//	決定の更新処理
//============================================================
void CMenuSelectUI::UpdateDecide()
{
	if (input::Decide())
	{
		// メニューが生成できない場合抜ける
		if (!IsCreateOK((ESelect)m_nCurSelect)) { return; }

		// 現在選択中のメニューに変更
		ChangeSelectMenu((ESelect)m_nCurSelect);
	}
}

//============================================================
//	選択メニューの終了処理
//============================================================
void CMenuSelectUI::UninitSelectMenu()
{
	// 選択メニューの終了
	SAFE_UNINIT(m_pSelectMenu);
}

//============================================================
//	メニュー生成可能フラグの取得処理
//============================================================
bool CMenuSelectUI::IsCreateOK(const CMenuSelectUI::ESelect select)
{
	// 選択肢に応じてメニューを生成
	CSelectUI* pTempSelectMenu = CSelectUI::Create(nullptr, m_pSoul, select);

	// 生成可能かを取得
	bool bCreateOK = pTempSelectMenu->IsCreateOK();

	// 選択メニューの終了
	SAFE_UNINIT(pTempSelectMenu);

	// 生成可能かを返す
	return bCreateOK;
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
	m_pSelectMenu = CSelectUI::Create
	( // 引数
		std::bind(&CMenuSelectUI::UninitSelectMenu, this),	// 選択メニュー終了関数
		m_pSoul,	// ソウルカーソル情報
		select		// 選択肢
	);
	if (m_pSelectMenu == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//************************************************************
//	子クラス [CSelectUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSelectUI::CSelectUI(AFuncUninit funcUninit, CObject2D* pSoul) : CObject(CObject::LABEL_UI, CObject::DIM_3D, MENU_PRIO),
	m_funcUninitMenu (funcUninit),	// 選択メニュー終了関数ポインタ
	m_pSoul			 (pSoul),		// ソウルカーソル情報
	m_pFrame		 (nullptr)		// フレーム情報
{

}

//============================================================
//	デストラクタ
//============================================================
CSelectUI::~CSelectUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSelectUI::Init()
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

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pFrame->SetPriority(MENU_PRIO);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSelectUI::Uninit()
{
	// フレームの終了
	SAFE_UNINIT(m_pFrame);

	// オブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CSelectUI::Update(const float fDeltaTime)
{
	if (input::Cancel())
	{
		// 選択メニューの終了
		m_funcUninitMenu();
	}
}

//============================================================
//	描画処理
//============================================================
void CSelectUI::Draw(CShader* /*pShader*/)
{

}

//============================================================
//	描画状況の設定処理
//============================================================
void CSelectUI::SetEnableDraw(const bool bDraw)
{
	// 自身の描画状況の設定
	CObject::SetEnableDraw(bDraw);

	// フレームの描画状況の設定
	m_pFrame->SetEnableDraw(bDraw);
}

//============================================================
//	生成処理
//============================================================
CSelectUI* CSelectUI::Create
(
	AFuncUninit funcUninit,	// 選択メニュー終了関数
	CObject2D* pSoul,		// ソウルカーソル情報
	const CMenuSelectUI::ESelect select	// 選択肢
)
{
	// セレクトUIの生成
	CSelectUI* pSelectUI = nullptr;	// セレクトUI情報
	switch (select)
	{ // 選択肢ごとの処理
	case CMenuSelectUI::SELECT_ITEM:
		pSelectUI = new CSelectItemUI(funcUninit, pSoul);
		break;

	case CMenuSelectUI::SELECT_STATUS:
		pSelectUI = new CSelectStatusUI(funcUninit, pSoul);
		break;

	case CMenuSelectUI::SELECT_PHONE:
		pSelectUI = new CSelectPhoneUI(funcUninit, pSoul);
		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	if (pSelectUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// セレクトの初期化
		if (FAILED(pSelectUI->Init()))
		{ // 初期化に失敗した場合

			// セレクトの破棄
			SAFE_DELETE(pSelectUI);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pSelectUI;
	}
}
