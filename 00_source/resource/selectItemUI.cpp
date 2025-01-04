//============================================================
//
//	アイテムメニュー処理 [selectItemUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "selectItemUI.h"
#include "manager.h"
#include "string2D.h"
#include "text2D.h"
#include "loadtext.h"
#include "item.h"
#include "itemUseUI.h"
#include "itemInfoUI.h"
#include "itemDropUI.h"
#include "sceneGame.h"
#include "player.h"
#include "playerItem.h"

// TODO：デバッグ
#if 0
#define RAND_ITEM
#endif

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char	*FONT	 = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
	const char	*PATH	 = "data\\TEXT\\selectItem.txt";				// テキストパス
	const bool	ITALIC	 = false;	// イタリック
	const float	HEIGHT	 = 42.0f;	// 文字縦幅
	const int	PRIORITY = 6;		// アイテムメニューの優先順位
	const VECTOR3 CURSOR_OFFSET = VECTOR3(22.0f, 0.0f, 0.0f);	// カーソルオフセット

	namespace frame
	{
		const VECTOR3 POS	= VECTOR3(545.0f, 347.5f, 0.0f);	// フレーム位置
		const VECTOR3 ROT	= VEC3_ZERO;						// フレーム向き
		const VECTOR3 SIZE	= VECTOR3(500.0f, 520.0f, 0.0f);	// フレーム大きさ
	}

	namespace select
	{
		const VECTOR3	POS		= VECTOR3(380.0f, 555.0f, 0.0f);	// 位置
		const VECTOR3	SPACE	= VECTOR3(160.0f, 0.0f, 0.0f);		// 空白
		const VECTOR3	ROT		= VEC3_ZERO;		// 向き
		const COLOR		COL		= color::White();	// 通常色
		const EAlignX	ALIGN_X = XALIGN_CENTER;	// 横配置
	}

	namespace item
	{
		const VECTOR3	POS		= VECTOR3(360.0f, 145.0f, 0.0f);	// 位置
		const VECTOR3	SPACE	= VECTOR3(0.0f, 49.0f, 0.0f);		// 空白
		const VECTOR3	ROT		= VEC3_ZERO;		// 向き
		const COLOR		COL		= color::White();	// 通常色
		const EAlignX	ALIGN_X = XALIGN_LEFT;		// 横配置
	}
}

//************************************************************
//	子クラス [CSelectItemUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSelectItemUI::CSelectItemUI(AFuncUninit funcUninit, CObject2D* pSoul) : CSelectUI(funcUninit, pSoul),
	m_pItemMenu		 (nullptr),		// アイテムメニュー情報
	m_state			 (STATE_ITEM),	// 状態
	m_nCurSelectItem (0),			// 現在の選択アイテム
	m_nCurSelectAct	 (0)			// 現在の選択行動
{
	// メンバ変数をクリア
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択情報
	m_vecItemName.clear();	// アイテム情報
}

//============================================================
//	デストラクタ
//============================================================
CSelectItemUI::~CSelectItemUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSelectItemUI::Init()
{
	// メンバ変数を初期化
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択情報
	m_vecItemName.clear();			// アイテム情報
	m_pItemMenu		 = nullptr;		// アイテムメニュー情報
	m_state			 = STATE_ITEM;	// 状態
	m_nCurSelectItem = 0;			// 現在の選択アイテム
	m_nCurSelectAct	 = 0;			// 現在の選択行動

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

	//--------------------------------------------------------
	//	選択の初期化 / 設定
	//--------------------------------------------------------
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 文字位置オフセットを計算
		VECTOR3 offset = select::SPACE * (float)i;

		// 選択の生成
		m_apSelect[i] = CString2D::Create
		( // 引数
			FONT,					// フォントパス
			ITALIC,					// イタリック
			L"",					// 指定文字列
			select::POS + offset,	// 原点位置
			HEIGHT,					// 文字縦幅
			select::ALIGN_X,		// 横配置
			select::ROT,			// 原点向き
			select::COL				// 色
		);
		if (m_apSelect[i] == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_apSelect[i]->SetPriority(PRIORITY);

		// 文字列を割当
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(PATH, TEXT_USE + i));
	}

	//--------------------------------------------------------
	//	アイテムの初期化 / 設定
	//--------------------------------------------------------
	CPlayerItem itemArray = *CSceneGame::GetPlayer()->GetItem();	// プレイヤー所持アイテム情報
	CItem* pItem = GET_MANAGER->GetItem();	// アイテム情報
#ifdef RAND_ITEM
	for (int i = 0; i < SPlayerItem::MAX_ITEM; i++)
	{ // アイテム数分繰り返す
#else
	int nNumItem = itemArray.GetNumItem();	// 所持アイテム数
	for (int i = 0; i < nNumItem; i++)
	{ // 所持アイテム数分繰り返す
#endif

		// 空の要素を最後尾に追加
		m_vecItemName.emplace_back();

#ifdef RAND_ITEM
		// アイテムインデックスを保存
		m_vecItemName[i].nItemIdx = rand() % 6;
#else
		// アイテムインデックスを保存
		m_vecItemName[i].nItemIdx = itemArray.GetItemIdx(i);
#endif

		// 文字位置オフセットを計算
		VECTOR3 offset = item::SPACE * (float)i;

		// アイテム名の生成
		m_vecItemName[i].pName = CString2D::Create
		( // 引数
			FONT,				// フォントパス
			ITALIC,				// イタリック
			L"",				// 指定文字列
			item::POS + offset,	// 原点位置
			HEIGHT,				// 文字縦幅
			item::ALIGN_X,		// 横配置
			item::ROT,			// 原点向き
			item::COL			// 色
		);
		if (m_vecItemName[i].pName == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_vecItemName[i].pName->SetPriority(PRIORITY);

		// アイテム名設定
		m_vecItemName[i].pName->SetString(pItem->GetInfo(m_vecItemName[i].nItemIdx).GetName());
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSelectItemUI::Uninit()
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択の終了
		SAFE_UNINIT(m_apSelect[i]);
	}

	for (auto& rVec : m_vecItemName)
	{ // 要素数分繰り返す

		// アイテム名の終了
		SAFE_UNINIT(rVec.pName);
	}

	// アイテム情報のクリア
	m_vecItemName.clear();

	// アイテムメニューの終了
	SAFE_UNINIT(m_pItemMenu);

	// セレクトUIの終了
	CSelectUI::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSelectItemUI::Update(const float fDeltaTime)
{
	switch (m_state)
	{ // 状態ごとの処理
	case STATE_ITEM:

		// アイテム選択の更新
		UpdateSelectItem();

		// アイテム決定の更新
		UpdateDecideItem();

		// セレクトUIの更新
		CSelectUI::Update(fDeltaTime);
		break;

	case STATE_ACT:

		// 行動選択の更新
		UpdateSelectAct();

		// 行動決定の更新
		UpdateDecideAct();
		break;

	case STATE_TEXT:

		// アイテムメニューの更新
		assert(m_pItemMenu != nullptr);
		m_pItemMenu->Update(fDeltaTime);
		break;

	default:
		assert(false);
		break;
	}
}

//============================================================
//	描画処理
//============================================================
void CSelectItemUI::Draw(CShader* pShader)
{
	// セレクトUIの描画
	CSelectUI::Draw(pShader);
}

//============================================================
//	描画状況の設定処理
//============================================================
void CSelectItemUI::SetEnableDraw(const bool bDraw)
{
	// 自身の描画状況の設定
	CSelectUI::SetEnableDraw(bDraw);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択の描画状況の設定
		m_apSelect[i]->SetEnableDraw(bDraw);
	}

	for (auto& rVec : m_vecItemName)
	{ // 要素数分繰り返す

		// アイテム名の描画状況の設定
		rVec.pName->SetEnableDraw(bDraw);
	}
}

//============================================================
//	メニュー生成可能フラグの取得処理
//============================================================
bool CSelectItemUI::IsCreateOK()
{
	CPlayerItem itemArray = *CSceneGame::GetPlayer()->GetItem();	// プレイヤー所持アイテム情報

	// アイテムを持っているなら生成可能
	return (itemArray.GetNumItem() > 0);
}

//============================================================
//	アイテム選択の更新処理
//============================================================
void CSelectItemUI::UpdateSelectItem()
{
	// 選択肢操作
	CInputKeyboard* pKey = GET_INPUTKEY;		// キーボード情報
	int nMaxItem = (int)m_vecItemName.size();	// アイテムの総数
	if (pKey->IsTrigger(DIK_DOWN))
	{
		// 上に選択をずらす
		m_nCurSelectItem = (m_nCurSelectItem + 1) % nMaxItem;
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		// 下に選択をずらす
		m_nCurSelectItem = (m_nCurSelectItem + (nMaxItem - 1)) % nMaxItem;
	}

	// ソウルカーソルの位置を移動
	SetSoulPosition(m_vecItemName[m_nCurSelectItem].pName->GetVec3Position() - CURSOR_OFFSET);
}

//============================================================
//	アイテム決定の更新処理
//============================================================
void CSelectItemUI::UpdateDecideItem()
{
	if (input::Decide())
	{
		// 行動選択状態にする
		m_state = STATE_ACT;
	}
}

//============================================================
//	行動選択の更新処理
//============================================================
void CSelectItemUI::UpdateSelectAct()
{
	// 選択肢操作
	CInputKeyboard* pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// 右に選択をずらす
		m_nCurSelectAct = (m_nCurSelectAct + 1) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// 左に選択をずらす
		m_nCurSelectAct = (m_nCurSelectAct + (SELECT_MAX - 1)) % SELECT_MAX;
	}

	// ソウルカーソルの位置を移動
	const VECTOR3 offset = VECTOR3(m_apSelect[m_nCurSelectAct]->GetStrWidth() * 0.5f, 0.0f, 0.0f) + CURSOR_OFFSET;	// カーソルオフセット
	SetSoulPosition(m_apSelect[m_nCurSelectAct]->GetVec3Position() - offset);
}

//============================================================
//	行動決定の更新処理
//============================================================
void CSelectItemUI::UpdateDecideAct()
{
	if (input::Decide())
	{
		// アイテムメニューの生成
		m_pItemMenu = CItemUI::Create
		( // 引数
			(ESelect)m_nCurSelectAct,					// 選択中行動
			m_vecItemName[m_nCurSelectItem].nItemIdx,	// 選択中アイテムインデックス
			m_nCurSelectItem							// 選択中バッグインデックス
		);

		// アイテムメニューの描画をOFFにする
		SetEnableDraw(false);

		// ソウルカーソルの描画をOFFにする
		SetSoulCursorDraw(false);

		// テキスト表示状態にする
		m_state = STATE_TEXT;
	}

	if (input::Cancel())
	{
		// 選択肢を初期化
		m_nCurSelectAct = 0;

		// アイテム選択状態にする
		m_state = STATE_ITEM;
	}
}

//************************************************************
//	子クラス [CItemUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CItemUI::CItemUI(const int nChoiceItemIdx, const int nChoiceBagIdx) : CObject(CObject::LABEL_NONE, CObject::DIM_3D, PRIORITY),
	m_nChoiceItemIdx	(nChoiceItemIdx),	// 選択中アイテムインデックス
	m_nChoiceBagIdx		(nChoiceBagIdx),	// 選択中バッグインデックス
	m_pTextBox			(nullptr),			// テキストボックス情報
	m_nCurTextIdx		(0)					// 現在のテキストインデックス
{

}

//============================================================
//	デストラクタ
//============================================================
CItemUI::~CItemUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CItemUI::Init()
{
	// メンバ変数を初期化
	m_pTextBox = nullptr;	// テキストボックス情報
	m_nCurTextIdx = 0;		// 現在のテキストインデックス

	// テキストボックスの生成
	m_pTextBox = CFrame2D::Create(CFrame2D::PRESET_DOWN);	// TODO：ちょっと怖い、時間作ってブレークポイント
	if (m_pTextBox == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// テキスト表示機能を設定
	m_pTextBox->ChangeModule(new CFrame2DModuleText);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CItemUI::Uninit()
{
	// テキストボックスの終了
	SAFE_UNINIT(m_pTextBox);

	// オブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CItemUI::Update(const float fDeltaTime)
{
	if (input::Decide())
	{
		if (IsTextBoxScroll())
		{ // 文字送り中の場合

			// 文字を全表示させる
			SetTextBoxEnableDraw(true);
			return;
		}

		// テキスト内容の進行
		NextText();
	}
}

//============================================================
//	描画処理
//============================================================
void CItemUI::Draw(CShader* /*pShader*/)
{

}

//============================================================
//	生成処理
//============================================================
CItemUI* CItemUI::Create
(
	const CSelectItemUI::ESelect choiceAct,	// 選択中行動
	const int nChoiceItemIdx,				// 選択中アイテムインデックス
	const int nChoiceBagIdx					// 選択中バッグインデックス
)
{
	// アイテムUIの生成
	CItemUI* pItemUI = nullptr;	// アイテムUI情報
	switch (choiceAct)
	{ // 選択肢ごとの処理
	case CSelectItemUI::SELECT_USE:
		pItemUI = new CItemUseUI(nChoiceItemIdx, nChoiceBagIdx);
		break;

	case CSelectItemUI::SELECT_INFO:
		pItemUI = new CItemInfoUI(nChoiceItemIdx, nChoiceBagIdx);
		break;

	case CSelectItemUI::SELECT_DROP:
		pItemUI = new CItemDropUI(nChoiceItemIdx, nChoiceBagIdx);
		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	if (pItemUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// アイテムの初期化
		if (FAILED(pItemUI->Init()))
		{ // 初期化に失敗した場合

			// アイテムの破棄
			SAFE_DELETE(pItemUI);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pItemUI;
	}
}
