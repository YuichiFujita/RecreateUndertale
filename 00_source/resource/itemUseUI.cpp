#if 0
//============================================================
//
//	使用メニュー処理 [itemUseUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "itemUseUI.h"
#include "manager.h"
#include "item.h"
#include "menuManager.h"
#include "frame2DTextBuffer.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 6;	// 使用メニューの優先順位
}

//************************************************************
//	子クラス [CItemUseUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CItemUseUI::CItemUseUI(const int nChoiceItemIdx, const int nChoiceBagIdx) : CItemUI(nChoiceItemIdx, nChoiceBagIdx)
{

}

//============================================================
//	デストラクタ
//============================================================
CItemUseUI::~CItemUseUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CItemUseUI::Init()
{
	// アイテムUIの初期化
	if (FAILED(CItemUI::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 機能が未設定の場合エラー
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// テキスト機能が未設定の場合エラー
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// アイテム情報を読み込んだパスを取得
	CItem* pItem = GET_MANAGER->GetItem();							// アイテム情報
	const CItemData& rItem = pItem->GetInfo(GetChoiceItemIdx());	// アイテム情報
	const std::string sPath = rItem.GetDataPath();					// アイテム情報読込パス



	// テキストの初期化バッファを取得
	CFrame2DModuleText::ABuffTextArray mapBuffText = rItem.CreateUseBuffTextArray();

	// テキストバッファ連想配列の割当
	pModuleText->BindBuffTextArray(mapBuffText, "NONE", "NONE", "0");

	// テキストバッファの割当
	pModuleText->BindText("0");



	// アイテム使用時のテキストを割当
	if (SUCCEEDED(pModuleText->BindTextBox(sPath, "USE")))
	{ // 割当に成功した場合

		// アイテム使用後の文字列を最後尾に追加
		pModuleText->PushBackString(rItem.UseEnd(), std::to_string(pModuleText->GetNumText() - 1));
	}

	// 選択アイテムを使用済みにする
	int nItemIdx = GetChoiceItemIdx();	// 選択アイテムインデックス
	int nBagIdx = GetChoiceBagIdx();	// 選択バッグインデックス
	pItem->GetInfo(nItemIdx).Use(nBagIdx);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CItemUseUI::Uninit()
{
	// アイテムUIの終了
	CItemUI::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CItemUseUI::Update(const float fDeltaTime)
{
	// アイテムUIの更新
	CItemUI::Update(fDeltaTime);

	if (!IsModuleText())
	{ // テキスト表示機能が終了した場合

		// フィールドメニューの終了
		CMenuManager::GetInstance()->SetEnableDrawMenu(false);
	}
}

//============================================================
//	描画処理
//============================================================
void CItemUseUI::Draw(CShader* pShader)
{
	// アイテムUIの描画
	CItemUI::Draw(pShader);
}
#endif