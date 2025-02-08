//============================================================
//
//	アイテムUI処理 [itemUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "itemUI.h"
#include "manager.h"
#include "item.h"
#include "menuManager.h"

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
	CFrame2DModuleText::AMapBuffText* pMapBuffText = rItemData.CreateUseBuffText();

	// テキストバッファ連想配列の割当
	pModuleText->BindBuffTextArray(pMapBuffText, "NONE", "NONE");

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
	CFrame2DModuleText::AMapBuffText* pMapBuffText = rItemData.CreateInfoBuffText();

	// テキストバッファ連想配列の割当
	pModuleText->BindBuffTextArray(pMapBuffText, "NONE", "NONE");

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
	CFrame2DModuleText::AMapBuffText* pMapBuffText = rItemData.CreateDropBuffText();

	// テキストバッファ連想配列の割当
	pModuleText->BindBuffTextArray(pMapBuffText, "NONE", "NONE");

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

//============================================================
//	テキスト表示機能かの確認処理
//============================================================
bool CItemUI::IsModuleText() const
{
	// 機能が割り当てられていない場合抜ける
	CFrame2DModule* pModule = GetModule();		// 現在機能
	if (pModule == nullptr) { return false; }	// テキスト表示ではない

	// 機能がテキスト表示かを返す
	return (typeid(*pModule) == typeid(CFrame2DModuleText));
}
