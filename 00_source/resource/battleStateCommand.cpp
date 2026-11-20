//============================================================
//
//	コマンド選択処理 [battleStateCommand.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "battleStateCommand.h"
#include "battleManager.h"
#include "sceneBattle.h"

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
//	子クラス [CBattleStateCommand] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBattleStateCommand::CBattleStateCommand()
{

}

//============================================================
//	デストラクタ
//============================================================
CBattleStateCommand::~CBattleStateCommand()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBattleStateCommand::Init()
{
	// TODO：現状だとコマンド押下時にテキストが全文表示されてしまう。
	// 　　　これを無視する設定を用意するか...？
	// TODO：エンカウント時のテキストを表示

	// テキスト表示機能を設定
	CFrame2D* pFrame = m_pContext->GetFrame();
	pFrame->ChangeModule(new CFrame2DModuleText(false));

	// エンカウント時のテキストを割当
	pFrame->GetModule()->GetModuleText()->BindTextBox
	(
		"data\\TXT\\TEXTBOX\\battle_test00.txt",
		"ENCOUNT"
	);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBattleStateCommand::Uninit()
{
	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CBattleStateCommand::Update(const float fDeltaTime)
{
	CBattleCommandUI* pCommandUI = m_pContext->GetCommandUI();
	if (pCommandUI->IsDecide())
	{
		// TODO：ステートができたらコメントアウト解除

		// 選択コマンドごとに遷移先を変更
		switch (pCommandUI->GetTypeSelect())
		{
		case CCommand::EType::TYPE_FIGHT:
		{
			// たたかう状態にする
			//m_pContext->ChangeState(new CBattleStateFight);
		}
		break;
		case CCommand::EType::TYPE_ACT:
		{
			// こうどう状態にする
			//m_pContext->ChangeState(new CBattleStateAct);
		}
		break;
		case CCommand::EType::TYPE_ITEM:
		{
			// アイテム状態にする
			m_pContext->ChangeState(new CBattleStateItem);
		}
		break;
		case CCommand::EType::TYPE_MERCY:
		{
			// みのがす状態にする
			m_pContext->ChangeState(new CBattleStateMercy);
		}
		break;
		}
	}
}
