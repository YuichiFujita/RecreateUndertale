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
	// TODO：エンカウント時のテキストを表示
	CFrame2D* pFrame = m_pContext->GetFrame();
	pFrame->ChangeModule(new CFrame2DModuleText(false));
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
		// TODO：他ステートへ遷移

		// TODO：現状だとコマンド押下時にテキストが全文表示されてしまう。
		// 　　　これを無視する設定を用意するか...？
#if 0
		// TODO：適当なテキストを表示
		CFrame2D* pFrame = m_pContext->GetFrame();
		pFrame->ChangeModule(new CFrame2DModuleText(false));
		pFrame->GetModule()->GetModuleText()->BindTextBox
		(
			"data\\TXT\\TEXTBOX\\battle_test00.txt",
			"MERCY"
		);
#endif
	}
}
