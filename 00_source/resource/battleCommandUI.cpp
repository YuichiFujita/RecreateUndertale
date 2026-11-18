//============================================================
//
//	戦闘時のコマンド表示処理 [battleCommandUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "battleCommandUI.h"
#include "command.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 6;	// 戦闘時のコマンド表示の優先順位

	const float POS_X[CBattleCommandUI::NUM_COMMAND] =	// コマンド表示X座標
	{
		130.0f,
		363.5f,
		596.5f,
		830.0f
	};
	const float POS_Y = 680.0f;	// コマンド表示Y座標
}

//************************************************************
//	子クラス [CBattleCommandUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBattleCommandUI::CBattleCommandUI() : CObject(CObject::LABEL_UI, CObject::DIM_2D, CObject::DEFAULT_PRIO)
{
	// メンバ変数をクリア
	memset(&m_apCommand[0], 0, sizeof(m_apCommand));	// コマンド情報
}

//============================================================
//	デストラクタ
//============================================================
CBattleCommandUI::~CBattleCommandUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBattleCommandUI::Init()
{
	// メンバ変数を初期化
	memset(&m_apCommand[0], 0, sizeof(m_apCommand));	// コマンド情報

	for (int i = 0; i < NUM_COMMAND; i++)
	{
		// コマンドの生成
		m_apCommand[i] = CCommand::Create
		( // 引数
			(CCommand::EType)i,
			VECTOR3(POS_X[i], POS_Y, 0.0f)
		);
		if (m_apCommand[i] == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}

		// ラベルを設定
		m_apCommand[i]->SetLabel(CObject::LABEL_NONE);

		// 自動更新・自動描画をOFFにする
		m_apCommand[i]->SetEnableUpdate(false);
		m_apCommand[i]->SetEnableDraw(false);
	}

	// 優先順位を設定
	SetPriority(PRIORITY);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBattleCommandUI::Uninit()
{
	for (int i = 0; i < NUM_COMMAND; i++)
	{
		// コマンドの終了
		SAFE_UNINIT(m_apCommand[i]);
	}

	// 自身のオブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CBattleCommandUI::Update(const float fDeltaTime)
{
	for (int i = 0; i < NUM_COMMAND; i++)
	{
		// コマンドの更新
		m_apCommand[i]->Update(fDeltaTime);
	}
}

//============================================================
//	描画処理
//============================================================
void CBattleCommandUI::Draw(CShader* pShader)
{
	for (int i = 0; i < NUM_COMMAND; i++)
	{
		// コマンドの描画
		m_apCommand[i]->Draw(pShader);
	}
}

//============================================================
//	優先順位の設定処理
//============================================================
void CBattleCommandUI::SetPriority(const int nPriority)
{
	// 引数の優先順位を設定
	CObject::SetPriority(nPriority);	// 自身
	for (int i = 0; i < NUM_COMMAND; i++)
	{
		m_apCommand[i]->SetPriority(nPriority);	// コマンド
	}
}

//============================================================
//	生成処理
//============================================================
CBattleCommandUI* CBattleCommandUI::Create()
{
	// 戦闘時のコマンド表示の生成
	CBattleCommandUI* pBattleCommandUI = new CBattleCommandUI;
	if (pBattleCommandUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 戦闘時のコマンド表示の初期化
		if (FAILED(pBattleCommandUI->Init()))
		{ // 初期化に失敗した場合

			// 戦闘時のコマンド表示の破棄
			SAFE_DELETE(pBattleCommandUI);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pBattleCommandUI;
	}
}
