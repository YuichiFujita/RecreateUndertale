//============================================================
//
//	タイマーUI処理 [timerUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "timerUI.h"
#include "timer.h"

//************************************************************
//	親クラス [CTimerUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTimerUI::CTimerUI() : m_pTimer(nullptr)
{

}

//============================================================
//	デストラクタ
//============================================================
CTimerUI::~CTimerUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTimerUI::Init()
{
	// メンバ変数を初期化
	m_pTimer = nullptr;	// タイマー管理情報

	// タイムUIの初期化
	if (FAILED(CTimeUI::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// タイマーの生成
	m_pTimer = CTimer::Create(0.0f, 0.0f);
	if (m_pTimer == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// タイマーの自動更新・自動終了をOFFにする
	m_pTimer->SetLabel(LABEL_NONE);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CTimerUI::Uninit()
{
	// タイマーの終了
	SAFE_UNINIT(m_pTimer);

	// タイムUIの終了
	CTimeUI::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CTimerUI::Update(const float fDeltaTime)
{
	// タイマーの更新
	m_pTimer->Update(fDeltaTime);

	// 表示時間の設定
	SetTime(m_pTimer->GetTime());

	// タイムUIの更新
	CTimeUI::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CTimerUI::Draw(CShader* pShader)
{
	// タイマーの描画
	m_pTimer->Draw(pShader);

	// タイムUIの描画
	CTimeUI::Draw(pShader);
}

//============================================================
//	表示時間の設定処理
//============================================================
void CTimerUI::SetTime(const float fTime)
{
	// タイマー時間の設定
	m_pTimer->SetTime(fTime);

	// 表示時間の設定
	CTimeUI::SetTime(fTime);
}

//============================================================
//	生成処理
//============================================================
CTimerUI* CTimerUI::Create
(
	const float fTime,			// 開始時間
	const float fLimit,			// 制限時間
	const VECTOR3& rPos,		// 位置
	const VECTOR3& rSizeValue,	// 数字の大きさ
	const VECTOR3& rSizePart,	// 区切りの大きさ
	const VECTOR3& rSpaceValue,	// 数字の空白
	const VECTOR3& rSpacePart,	// 区切りの空白
	const CValue::EType type,	// 数字種類
	const EAlignX alignX,		// 横配置
	const EAlignY alignY,		// 縦配置
	const VECTOR3& rRot,		// 向き
	const COLOR& rCol			// 色
)
{
	// タイマーUIの生成
	CTimerUI* pTimerUI = new CTimerUI;
	if (pTimerUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// タイマーUIの初期化
		if (FAILED(pTimerUI->Init()))
		{ // 初期化に失敗した場合

			// タイマーUIの破棄
			SAFE_DELETE(pTimerUI);
			return nullptr;
		}

		// 開始時間を設定
		pTimerUI->SetTime(fTime);

		// 制限時間を設定
		pTimerUI->SetLimit(fLimit);

		// 数字種類を設定
		pTimerUI->SetValueType(type);

		// 原点位置を設定
		pTimerUI->SetVec3Position(rPos);

		// 原点向きを設定
		pTimerUI->SetVec3Rotation(rRot);

		// 数字の大きさを設定
		pTimerUI->SetSizeValue(rSizeValue);

		// 区切りの大きさを設定
		pTimerUI->SetSizePart(rSizePart);

		// 数字の空白を設定
		pTimerUI->SetSpaceValue(rSpaceValue);

		// 区切りの空白を設定
		pTimerUI->SetSpacePart(rSpacePart);

		// 色を設定
		pTimerUI->SetColor(rCol);

		// 横配置を設定
		pTimerUI->SetAlignX(alignX);

		// 縦配置を設定
		pTimerUI->SetAlignY(alignY);

		// 確保したアドレスを返す
		return pTimerUI;
	}
}
