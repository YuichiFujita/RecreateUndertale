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
#include "manager.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 6;	// 戦闘時のコマンド表示の優先順位

	const float POS_X[CBattleCommandUI::NUM_COMMAND] =	// コマンド表示X座標
	{
		130.0f,	// FIGHT
		363.5f,	// ACT
		596.5f,	// ITEM
		830.0f	// MERCY
	};
	const float POS_Y = 680.0f;	// コマンド表示Y座標

	const VECTOR3 OFFSET = VECTOR3(-58.0f, 0.0f, 0.0f);	// ソウルカーソルオフセット
}

//************************************************************
//	子クラス [CBattleCommandUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBattleCommandUI::CBattleCommandUI() : CObject(CObject::LABEL_UI, CObject::DIM_2D, CObject::DEFAULT_PRIO),
	m_pSoul			(nullptr),	// ソウルカーソル情報
	m_nCurSelect	(0),		// 現在の選択肢
	m_bDecide		(false)		// 決定操作済みか
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
	m_pSoul      = nullptr;	// ソウルカーソル情報
	m_nCurSelect = 0;		// 現在の選択肢
	m_bDecide    = false;	// 決定操作済みか

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

	// 選択項目の初期化
	SetSelect(0);

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
	if (!m_bDecide)
	{ // 決定前の場合

		// 選択の更新
		UpdateSelect();

		// 決定の更新
		UpdateDecide();
	}

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
CBattleCommandUI* CBattleCommandUI::Create(CObject* pSoul)
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

		// ソウルカーソルを設定
		pBattleCommandUI->SetSoul(pSoul);

		// 確保したアドレスを返す
		return pBattleCommandUI;
	}
}

//============================================================
//	選択項目の設定処理
//============================================================
void CBattleCommandUI::SetSelect(const int nSelect)
{
	// 引数インデックスの選択肢を設定
	m_nCurSelect = nSelect;

	// 全コマンドを非選択状態にする
	for (int i = 0; i < NUM_COMMAND; i++)
	{
		m_apCommand[i]->SetState(CCommand::STATE_OFF);
	}

	// 引数インデックスのコマンドを選択状態にする
	m_apCommand[m_nCurSelect]->SetState(CCommand::STATE_ON);

	// ソウルカーソルの位置を移動
	if (m_pSoul != nullptr)
	{
		m_pSoul->SetVec3Position(m_apCommand[m_nCurSelect]->GetVec3Position() + OFFSET);
	}
}

//============================================================
//	ソウルカーソルの設定処理
//============================================================
void CBattleCommandUI::SetSoul(CObject* pSoul)
{
	// ソウルカーソルオブジェクトの設定
	m_pSoul = pSoul;

	// ソウルカーソルの位置を移動
	if (m_pSoul != nullptr)
	{
		m_pSoul->SetVec3Position(m_apCommand[m_nCurSelect]->GetVec3Position() + OFFSET);
	}
}

//============================================================
//	選択中タイプの取得処理
//============================================================
CCommand::EType CBattleCommandUI::GetTypeSelect() const
{
	// 現在選択中のコマンドタイプを返す
	return m_apCommand[m_nCurSelect]->GetType();
}

//============================================================
//	選択の更新処理
//============================================================
void CBattleCommandUI::UpdateSelect()
{
	const int nOldSelect = m_nCurSelect;	// 前回の選択肢
	bool      bInput     = false;			// 選択肢の操作が行われたか

	// 選択肢操作
	CInputKeyboard* pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// 右に選択をずらす
		m_nCurSelect = (m_nCurSelect + 1) % NUM_COMMAND;
		bInput = true;
	}
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// 左に選択をずらす
		m_nCurSelect = (m_nCurSelect + (NUM_COMMAND - 1)) % NUM_COMMAND;
		bInput = true;
	}

	// 操作があった場合
	if (bInput)
	{
		// 選択解除したコマンドを非選択状態にする
		m_apCommand[nOldSelect]->SetState(CCommand::STATE_OFF);

		// 選択開始したコマンドを選択状態にする
		m_apCommand[m_nCurSelect]->SetState(CCommand::STATE_ON);

		// ソウルカーソルの位置を移動
		if (m_pSoul != nullptr)
		{
			m_pSoul->SetVec3Position(m_apCommand[m_nCurSelect]->GetVec3Position() + OFFSET);
		}
	}
}

//============================================================
//	決定の更新処理
//============================================================
void CBattleCommandUI::UpdateDecide()
{
	if (input::Decide())
	{
		// 選択していたコマンドを非選択状態にする
		m_apCommand[m_nCurSelect]->SetState(CCommand::STATE_OFF);

		// 決定済みにする
		m_bDecide = true;
	}
}
