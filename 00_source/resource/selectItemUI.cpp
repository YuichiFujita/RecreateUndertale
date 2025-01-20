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
#include "menuManager.h"

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
//	静的メンバ変数宣言
//************************************************************
CItemUI::AFuncInitText CItemUI::m_aFuncInitText[] =	// テキスト初期化関数リスト
{
	&CItemUI::InitUseText,	// 使用テキスト初期化
	&CItemUI::InitInfoText,	// 情報テキスト初期化
	&CItemUI::InitDropText,	// 破棄テキスト初期化
};
CItemUI::AFuncBindText CItemUI::m_aFuncBindText[] =	// テキスト割当関数リスト
{
	&CItemUI::BindUseText,	// 使用テキスト割当
	&CItemUI::BindInfoText,	// 情報テキスト割当
	&CItemUI::BindDropText,	// 破棄テキスト割当
};
CItemUI::AFuncActItem CItemUI::m_aFuncActItem[] =	// アイテム行動関数リスト
{
	&CItemUI::ActUseItem,	// 選択アイテム使用行動
	&CItemUI::ActInfoItem,	// 選択アイテム情報行動
	&CItemUI::ActDropItem,	// 選択アイテム破棄行動
};

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
CItemUI::CItemUI(const CSelectItemUI::ESelect choiceAct, const int nChoiceItemIdx, const int nChoiceBagIdx) :
	m_choiceAct			(choiceAct),		// 選択中行動
	m_nChoiceItemIdx	(nChoiceItemIdx),	// 選択中アイテムインデックス
	m_nChoiceBagIdx		(nChoiceBagIdx)		// 選択中バッグインデックス
{
	// スタティックアサート
	static_assert(NUM_ARRAY(m_aFuncInitText) == CSelectItemUI::SELECT_MAX, "ERROR : Act Count Mismatch");
	static_assert(NUM_ARRAY(m_aFuncBindText) == CSelectItemUI::SELECT_MAX, "ERROR : Act Count Mismatch");
	static_assert(NUM_ARRAY(m_aFuncActItem)  == CSelectItemUI::SELECT_MAX, "ERROR : Act Count Mismatch");
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
	// 親クラスの初期化
	if (FAILED(CFrame2D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 自動破棄/更新をしないラベルにする
	SetLabel(LABEL_NONE);

	// プリセットを設定
	SetPreset(PRESET_DOWN);	// TODO：今は固定

	// テキスト表示機能を設定
	ChangeModule(new CFrame2DModuleText(false));

	// テキストの初期化
	assert(m_aFuncInitText != nullptr);
	(this->*(m_aFuncInitText[m_choiceAct]))();

	// テキストの割当
	assert(m_aFuncBindText != nullptr);
	(this->*(m_aFuncBindText[m_choiceAct]))();

	// 行動の適応
	assert(m_aFuncActItem != nullptr);
	(this->*(m_aFuncActItem[m_choiceAct]))();

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CItemUI::Uninit()
{
	// 親クラスの終了
	CFrame2D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CItemUI::Update(const float fDeltaTime)
{
	// 親クラスの更新
	CFrame2D::Update(fDeltaTime);

	if (!IsModuleText())
	{ // テキスト表示機能が終了した場合

		// フィールドメニューの終了
		CMenuManager::GetInstance()->SetEnableDrawMenu(false);
	}
}

//============================================================
//	描画処理
//============================================================
void CItemUI::Draw(CShader* pShader)
{
	// 親クラスの描画
	CFrame2D::Draw(pShader);
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
	CItemUI* pItemUI = new CItemUI(choiceAct, nChoiceItemIdx, nChoiceBagIdx);
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

//============================================================
//	テキスト表示機能かの確認処理
//============================================================
bool CItemUI::IsModuleText() const
{
	CFrame2DModule* pModule = GetModule();	// 現在機能

	// 機能が割り当てられていない場合抜ける
	if (pModule == nullptr) { return false; }	// テキスト表示ではない

	// 機能がテキスト表示かを返す
	return (typeid(*pModule) == typeid(CFrame2DModuleText));	// TODO：これprivateに
}

//============================================================
//	使用テキスト初期化処理
//============================================================
HRESULT CItemUI::InitUseText()
{
	// 機能が未設定の場合エラー
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// テキスト機能が未設定の場合エラー
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// アイテム情報を読み込んだパスを取得
	CItem* pItem = GET_MANAGER->GetItem();							// アイテム情報
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// アイテム情報

	// テキストの初期化バッファを取得
	CFrame2DModuleText::ABuffTextArray mapBuffText = rItemData.CreateUseBuffTextArray();

	// テキストバッファ連想配列の割当
	pModuleText->BindBuffTextArray(mapBuffText, "NONE", "NONE", "0");

	// テキストバッファの割当
	pModuleText->BindText("0");

	return S_OK;
}

//============================================================
//	情報テキスト初期化処理
//============================================================
HRESULT CItemUI::InitInfoText()
{
	// 機能が未設定の場合エラー
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// テキスト機能が未設定の場合エラー
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// アイテム情報を読み込んだパスを取得
	CItem* pItem = GET_MANAGER->GetItem();							// アイテム情報
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// アイテム情報

	// テキストの初期化バッファを取得
	CFrame2DModuleText::ABuffTextArray mapBuffText = rItemData.CreateInfoBuffTextArray();

	// テキストバッファ連想配列の割当
	pModuleText->BindBuffTextArray(mapBuffText, "NONE", "NONE", "0");

	// テキストバッファの割当
	pModuleText->BindText("0");

	return S_OK;
}

//============================================================
//	破棄テキスト初期化処理
//============================================================
HRESULT CItemUI::InitDropText()
{
	// 機能が未設定の場合エラー
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// テキスト機能が未設定の場合エラー
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// アイテム情報を読み込んだパスを取得
	CItem* pItem = GET_MANAGER->GetItem();							// アイテム情報
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// アイテム情報

	// テキストの初期化バッファを取得
	CFrame2DModuleText::ABuffTextArray mapBuffText = rItemData.CreateDropBuffTextArray();

	// テキストバッファ連想配列の割当
	pModuleText->BindBuffTextArray(mapBuffText, "NONE", "NONE", "0");

	// テキストバッファの割当
	pModuleText->BindText("0");

	return S_OK;
}

//============================================================
//	使用テキスト割当処理
//============================================================
HRESULT CItemUI::BindUseText()
{
	// 機能が未設定の場合エラー
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// テキスト機能が未設定の場合エラー
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// アイテム情報を読み込んだパスを取得
	CItem* pItem = GET_MANAGER->GetItem();							// アイテム情報
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// アイテム情報

	// アイテム使用時のテキストを割当
	if (SUCCEEDED(pModuleText->BindTextBox(rItemData.GetDataPath(), "USE")))
	{ // 割当に成功した場合

		// アイテム使用後の文字列を最後尾に追加
		const std::string sKey = std::to_string(pModuleText->GetNumText() - 1);
		if (FAILED(pModuleText->PushBackString(rItemData.UseEnd(), sKey)))
		{ // 追加に失敗した場合

			assert(false);
			return E_FAIL;
		}
	}

	return S_OK;
}

//============================================================
//	情報テキスト割当処理
//============================================================
HRESULT CItemUI::BindInfoText()
{
	// 機能が未設定の場合エラー
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// テキスト機能が未設定の場合エラー
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// アイテム情報を読み込んだパスを取得
	CItem* pItem = GET_MANAGER->GetItem();							// アイテム情報
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// アイテム情報

	// アイテム情報の確認時のテキストを割当
	if (SUCCEEDED(pModuleText->BindTextBox(rItemData.GetDataPath(), "INFO")))
	{ // 割当に成功した場合

		// アイテム詳細を先頭に追加
		if (FAILED(pModuleText->PushFrontString(rItemData.Detail(), "0")))
		{ // 追加に失敗した場合

			assert(false);
			return E_FAIL;
		}
	}

	return S_OK;
}

//============================================================
//	破棄テキスト割当処理
//============================================================
HRESULT CItemUI::BindDropText()
{
	// 機能が未設定の場合エラー
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// テキスト機能が未設定の場合エラー
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// アイテム情報を読み込んだパスを取得
	CItem* pItem = GET_MANAGER->GetItem();							// アイテム情報
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// アイテム情報

	// アイテム破棄時のテキストを割当
	pModuleText->BindTextBox(rItemData.GetDataPath(), "DROP");

	return S_OK;
}

//============================================================
//	選択アイテム使用行動処理
//============================================================
void CItemUI::ActUseItem()
{
	// 選択アイテムを使用済みにする
	CItem* pItem = GET_MANAGER->GetItem();	// アイテム情報
	pItem->GetInfo(m_nChoiceItemIdx).Use(m_nChoiceBagIdx);
}

//============================================================
//	選択アイテム情報行動処理
//============================================================
void CItemUI::ActInfoItem()
{
	// 選択アイテムの情報を確認済みにする
	CItem* pItem = GET_MANAGER->GetItem();	// アイテム情報
	pItem->GetInfo(m_nChoiceItemIdx).Info(m_nChoiceBagIdx);
}

//============================================================
//	選択アイテム破棄行動処理
//============================================================
void CItemUI::ActDropItem()
{
	// 選択アイテムを破棄済みにする
	CItem* pItem = GET_MANAGER->GetItem();	// アイテム情報
	pItem->GetInfo(m_nChoiceItemIdx).Drop(m_nChoiceBagIdx);
}
