//============================================================
//
//	モーション2D処理 [motion2D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "motion2D.h"
#include "objectChara2D.h"

//************************************************************
//	親クラス [CMotion2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CMotion2D::CMotion2D() :
	m_pChara	(nullptr)	// オブジェクトキャラクター情報
{

}

//============================================================
//	デストラクタ
//============================================================
CMotion2D::~CMotion2D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CMotion2D::Init(void)
{
	// メンバ変数をクリア
	m_pChara = nullptr;	// オブジェクトキャラクター情報

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CMotion2D::Uninit(void)
{
	// モーション情報をクリア
	m_info.vecMotion.clear();
}

//============================================================
//	更新処理
//============================================================
void CMotion2D::Update(const float fDeltaTime)
{
	// モーションがない場合抜ける
	if (m_info.vecMotion.empty()) { return; }
}

//============================================================
//	設定処理
//============================================================
void CMotion2D::Set(const int nType)
{
	// 指定されたモーションが存在しない場合抜ける
	if (nType <= NONE_IDX || nType >= m_info.GetNumMotion()) { assert(false); return; }

	// 引数のモーションの種類を設定
	m_info.nType = nType;

	// 変数をポインタ化し簡略化
	SChara *pInfoChara = &m_info.vecMotion[nType].infoChara;	// キャラクター情報

	// 指定テクスチャの割当
	m_pChara->BindTexture(pInfoChara->sPassTexture.c_str());

	// キャラクター情報を設定
	m_pChara->SetTexPtrn(pInfoChara->ptrnTexture);	// テクスチャ分割数
	m_pChara->SetNextTime(pInfoChara->fNextTime);	// パターン変更時間
	m_pChara->SetEnableLoop(pInfoChara->bLoop);		// ループON/OFF
	m_pChara->SetVec3Sizing(pInfoChara->sizeChara);	// 大きさ

	// キャラクター情報を初期化
	m_pChara->ResetCurPtrn();	// 開始パターン
	m_pChara->ResetNumLoop();	// 繰り返し数
}

//============================================================
//	モーション情報の追加処理
//============================================================
void CMotion2D::AddInfo(const SMotion& rMotion)
{
	int nSetMotionID = m_info.GetNumMotion();	// モーションを設定する配列番号

	// 空の要素を最後尾に追加
	m_info.vecMotion.emplace_back();

	// 引数のモーション情報を設定
	m_info.vecMotion[nSetMotionID] = rMotion;
}

//============================================================
//	モーション情報全設定処理
//============================================================
void CMotion2D::SetAllInfo(const SInfo& rInfo)
{
	// モーション情報をクリア
	m_info.vecMotion.clear();

	for (auto& rVec : rInfo.vecMotion)
	{ // 読み込んだモーション数分繰り返す

		// モーション情報の追加
		AddInfo(rVec);
	}
}

//============================================================
//	キャンセル取得処理
//============================================================
bool CMotion2D::IsCancel(void) const
{
	float fCancelTime = m_info.vecMotion[m_info.nType].fCancelTime;	// キャンセル可能時間
	if (fCancelTime >= 0.0f)
	{ // キャンセル可能時間が設定されている場合

		// モーションのキャンセル状況を返す
		return (m_pChara->GetCurWholeTime() >= fCancelTime);
	}

	// キャンセル不可を返す
	return false;
}

//============================================================
//	コンボ取得処理
//============================================================
bool CMotion2D::IsCombo(void) const
{
	float fComboTime = m_info.vecMotion[m_info.nType].fComboTime;	// コンボ可能時間
	if (fComboTime >= 0.0f)
	{ // コンボ可能時間が設定されている場合

		// モーションのコンボ状況を返す
		return (m_pChara->GetCurWholeTime() >= fComboTime);
	}

	// コンボ不可を返す
	return false;
}

//============================================================
//	生成処理
//============================================================
CMotion2D *CMotion2D::Create(CObjectChara2D *pChara2D)
{
	// モーション2Dの生成
	CMotion2D *pMotion = new CMotion2D;
	if (pMotion == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// モーション2Dの初期化
		if (FAILED(pMotion->Init()))
		{ // 初期化に失敗した場合

			// モーション2Dの破棄
			SAFE_DELETE(pMotion);
			return nullptr;
		}

		// オブジェクトキャラクターを設定
		pMotion->m_pChara = pChara2D;

		// 確保したアドレスを返す
		return pMotion;
	}
}

//============================================================
//	破棄処理
//============================================================
void CMotion2D::Release(CMotion2D *&prMotion2D)
{
	// モーション2Dの終了
	assert(prMotion2D != nullptr);
	prMotion2D->Uninit();

	// メモリ開放
	SAFE_DELETE(prMotion2D);
}
