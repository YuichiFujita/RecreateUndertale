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

// TODO
#include "sceneGame.h"
#include "menuManager.h"

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
CItemUseUI::CItemUseUI(const int nChoiceItemIdx) : CItemUI(nChoiceItemIdx)
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
HRESULT CItemUseUI::Init(void)
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

	// TODO：これはInfo用
#if 1
	CItem* pItem = GET_MANAGER->GetItem();								// アイテム情報
	const CItemData& rItemData = pItem->GetInfo(GetChoiceItemIdx());	// アイテム内部データ
	ATextBox textData = rItemData.GetUse();								// アイテム使用テキスト

	// アイテム詳細を先頭に追加
	std::string str = rItemData.Detail();
	PushFrontString(useful::MultiByteToWide(str));
#endif

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CItemUseUI::Uninit(void)
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
void CItemUseUI::Draw(CShader *pShader)
{
	// アイテムUIの描画
	CItemUI::Draw(pShader);
}

//============================================================
//	テキストボックス進行処理
//============================================================
void CItemUseUI::NextText(void)
{
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
		pItem->GetInfo(nItemIdx).Use();

		// フィールドメニューの終了
		CSceneGame::GetMenuManager()->SetEnableDrawMenu(false);
		return;
	}

	// 現在のテキスト進行度に合わせたテキスト内容に変更
	ChangeTextBox(textData[nTextIdx]);

	// テキスト進行度を進める
	CItemUI::NextText();

	// TODO：Useだけ
#if 1
	// 回復量を表示
	if (nTextIdx >= nNumText)
	{ // 最終テキストの場合

		PushBackString(L" ＊ そこそこ回復したで");
	}
#endif
}
