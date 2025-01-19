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
	pModuleText->BindTextBox(sPath, "USE");

	// テキスト内容の進行
	//NextText();

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
}

//============================================================
//	描画処理
//============================================================
void CItemUseUI::Draw(CShader* pShader)
{
	// アイテムUIの描画
	CItemUI::Draw(pShader);
}

//============================================================
//	テキストボックス進行処理
//============================================================
void CItemUseUI::NextText()
{
	// TODO：NextTextの作成
#if 0
	int nTextIdx = GetCurTextIdx();			// テキスト進行度インデックス
	int nItemIdx = GetChoiceItemIdx();		// 選択アイテムインデックス
	CItem* pItem = GET_MANAGER->GetItem();	// アイテム情報
	const CItemData& rItemData = pItem->GetInfo(nItemIdx);	// アイテム内部データ

	// アイテム使用時のテキスト情報を取得
	ATextBox textData = rItemData.GetUse();

	int nNumText = (int)textData.size();	// テキスト総数
	if (nTextIdx >= nNumText)
	{ // テキストが終了した場合

		// 選択アイテムを使用済みにする
		int nBagIdx = GetChoiceBagIdx();	// 選択バッグインデックス
		pItem->GetInfo(nItemIdx).Use(nBagIdx);

		// フィールドメニューの終了
		CMenuManager::GetInstance()->SetEnableDrawMenu(false);
		return;
	}

	// 現在のテキスト進行度に合わせたテキスト内容に変更
	ChangeTextBox(textData[nTextIdx]);

	// テキスト進行度を進める
	CItemUI::NextText();

	if (nTextIdx + 1 >= nNumText)
	{ // 最終テキストの場合

		// アイテム使用後の文字列を最後尾に追加
		PushBackString(rItemData.UseEnd());
	}
#endif
}
