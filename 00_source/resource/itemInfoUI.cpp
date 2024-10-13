//============================================================
//
//	情報メニュー処理 [itemInfoUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "itemInfoUI.h"
#include "manager.h"
#include "item.h"

// TODO
#include "sceneGame.h"
#include "menuManager.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 6;	// 情報メニューの優先順位
}

//************************************************************
//	子クラス [CItemInfoUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CItemInfoUI::CItemInfoUI(const int nChoiceItemIdx) : CItemUI(nChoiceItemIdx)
{

}

//============================================================
//	デストラクタ
//============================================================
CItemInfoUI::~CItemInfoUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CItemInfoUI::Init(void)
{
	// アイテムUIの初期化
	if (FAILED(CItemUI::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テキスト内容の進行
	NextText();

	// TODO：きったね
	// アイテム詳細を先頭に追加
	CItem* pItem = GET_MANAGER->GetItem();								// アイテム情報
	const CItemData& rItemData = pItem->GetInfo(GetChoiceItemIdx());	// アイテム内部データ
	std::string str = rItemData.Detail();
	PushFrontString(useful::MultiByteToWide(str));

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CItemInfoUI::Uninit(void)
{
	// アイテムUIの終了
	CItemUI::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CItemInfoUI::Update(const float fDeltaTime)
{
	// アイテムUIの更新
	CItemUI::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CItemInfoUI::Draw(CShader *pShader)
{
	// アイテムUIの描画
	CItemUI::Draw(pShader);
}

//============================================================
//	テキストボックス進行処理
//============================================================
void CItemInfoUI::NextText(void)
{
	int nTextIdx = GetCurTextIdx();			// テキスト進行度インデックス
	int nItemIdx = GetChoiceItemIdx();		// 選択アイテムインデックス
	CItem* pItem = GET_MANAGER->GetItem();	// アイテム情報
	const CItemData& rItemData = pItem->GetInfo(nItemIdx);	// アイテム内部データ

	// アイテム情報の確認時のテキスト情報を取得
	ATextBox textData = rItemData.GetInfo();

	int nNumText = (int)textData.size();	// テキスト総数
	if (nTextIdx >= nNumText)
	{ // テキストが終了した場合

		// 選択アイテムの情報を確認済みにする
		pItem->GetInfo(nItemIdx).Info();

		// フィールドメニューの終了
		CSceneGame::GetMenuManager()->SetEnableDrawMenu(false);
		return;
	}

	// 現在のテキスト進行度に合わせたテキスト内容に変更
	ChangeTextBox(textData[nTextIdx]);

	// テキスト進行度を進める
	CItemUI::NextText();
}
