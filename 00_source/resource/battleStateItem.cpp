//============================================================
//
//	アイテム状態処理 [battleStateItem.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "battleStateItem.h"
#include "battleManager.h"
#include "sceneBattle.h"

#include "userdataManager.h"
#include "playerItem.h"
#include "frame2D.h"
#include "frame2DModule.h"
#include "battleCommandUI.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{

}

//************************************************************
//	子クラス [CBattleStateItem] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBattleStateItem::CBattleStateItem()
{

}

//============================================================
//	デストラクタ
//============================================================
CBattleStateItem::~CBattleStateItem()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBattleStateItem::Init()
{
	// TODO：アイテム時のテキストを表示

	// テキスト表示機能を設定
	CFrame2D* pFrame = m_pContext->GetFrame();
	pFrame->ChangeModule(new CFrame2DModuleText(false));

	// TODO：ここは普通に今のアイテム入れないとだめか
	// アイテム時のテキストを割当
#if 0
	CFrame2DModuleText* pModule = pFrame->GetModule()->GetModuleText();
	pModule->BindTextBox
	(
		"data\\TXT\\TEXTBOX\\battle_test00.txt",
		"ITEM"
	);
#else
	// アイテムの読込
	CUserDataManager* pUserData = CUserDataManager::GetInstance();	// ユーザーデータ情報
	CPlayerItem       item;	// アイテム情報
	if (FAILED(pUserData->LoadPlayerItem(&item)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}
#endif

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBattleStateItem::Uninit()
{
	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CBattleStateItem::Update(const float fDeltaTime)
{
	if (input::Decide())
	{
		// TODO：決定時はここじゃない
	}

	if (input::Cancel())
	{
		// TODO：キャンセル時はここかも

		// コマンドを再度選択可能にする
		m_pContext->GetCommandUI()->ResetDecide(-1);

		// コマンド選択状態にする
		m_pContext->ChangeState(new CBattleStateCommand);
	}
}
