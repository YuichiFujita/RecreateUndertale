//============================================================
//
//	みのがす状態処理 [battleStateMercy.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "battleStateMercy.h"
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
//	子クラス [CBattleStateMercy] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBattleStateMercy::CBattleStateMercy()
{

}

//============================================================
//	デストラクタ
//============================================================
CBattleStateMercy::~CBattleStateMercy()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBattleStateMercy::Init()
{
	// TODO：みのがす時のテキストを表示

	// テキスト表示機能を設定
	CFrame2D* pFrame = m_pContext->GetFrame();
	pFrame->ChangeModule(new CFrame2DModuleText(false));

	// みのがす時のテキストを割当
	CFrame2DModuleText* pModule = pFrame->GetModule()->GetModuleText();
	pModule->BindTextBox
	(
		"data\\TXT\\TEXTBOX\\battle_test00.txt",
		"MERCY"
	);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBattleStateMercy::Uninit()
{
	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CBattleStateMercy::Update(const float fDeltaTime)
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
