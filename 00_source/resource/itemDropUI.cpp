//============================================================
//
//	破棄メニュー処理 [itemDropUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "itemDropUI.h"
#include "manager.h"
#include "item.h"
#include "menuManager.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 6;	// 破棄メニューの優先順位
}

//************************************************************
//	子クラス [CItemDropUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CItemDropUI::CItemDropUI(const int nChoiceItemIdx, const int nChoiceBagIdx) : CItemUI(nChoiceItemIdx, nChoiceBagIdx)
{

}

//============================================================
//	デストラクタ
//============================================================
CItemDropUI::~CItemDropUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CItemDropUI::Init()
{
	// アイテムUIの初期化
	if (FAILED(CItemUI::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// テキスト内容の進行
	NextText();

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CItemDropUI::Uninit()
{
	// アイテムUIの終了
	CItemUI::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CItemDropUI::Update(const float fDeltaTime)
{
	// アイテムUIの更新
	CItemUI::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CItemDropUI::Draw(CShader* pShader)
{
	// アイテムUIの描画
	CItemUI::Draw(pShader);
}

//============================================================
//	テキストボックス進行処理
//============================================================
void CItemDropUI::NextText()
{
	int nTextIdx = GetCurTextIdx();			// テキスト進行度インデックス
	int nItemIdx = GetChoiceItemIdx();		// 選択アイテムインデックス
	CItem* pItem = GET_MANAGER->GetItem();	// アイテム情報
	const CItemData& rItemData = pItem->GetInfo(nItemIdx);	// アイテム内部データ

	// アイテム破棄時のテキスト情報を取得
	ATextBox textData = rItemData.GetDrop();

	int nNumText = (int)textData.size();	// テキスト総数
	if (nTextIdx >= nNumText)
	{ // テキストが終了した場合

		// 選択アイテムを破棄済みにする
		int nBagIdx = GetChoiceBagIdx();	// 選択バッグインデックス
		pItem->GetInfo(nItemIdx).Drop(nBagIdx);

		// フィールドメニューの終了
		CMenuManager::GetInstance()->SetEnableDrawMenu(false);
		return;
	}

	// 現在のテキスト進行度に合わせたテキスト内容に変更
	ChangeTextBox(textData[nTextIdx]);

	// テキスト進行度を進める
	CItemUI::NextText();
}
