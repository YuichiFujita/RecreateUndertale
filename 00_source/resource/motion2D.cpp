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
	m_pChara	(nullptr),	// オブジェクトキャラクター情報
	m_bUpdate	(true)		// 更新状況
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
	m_pChara	= nullptr;	// オブジェクトキャラクター情報
	m_bUpdate	= true;		// 更新状況

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
	// 更新停止中の場合抜ける
	if (!m_bUpdate) { return; }

	// モーションがない場合抜ける
	if (m_info.vecMotion.empty()) { return; }

	// モーションの更新
	UpdateMotion();
}

//============================================================
//	更新状況の設定処理
//============================================================
void CMotion2D::SetEnableUpdate(const bool bUpdate)
{
	// 引数の更新状況を設定
	m_bUpdate = bUpdate;
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

	// モーション情報を初期化
	m_info.fCurTime	= 0.0f;		// 現在のモーション全体時間
	m_info.bFinish	= false;	// モーション終了状況

	// キャラクター情報を設定	// TODO：これで大丈夫？
	SChara *pInfoChara = &m_info.vecMotion[nType].infoChara;	// キャラクター情報
	m_pChara->BindTexture(pInfoChara->sPassTexture.c_str());	// テクスチャを割当
	m_pChara->SetTexPtrn(pInfoChara->ptrnTexture);				// テクスチャ分割数を設定
	m_pChara->SetNextTime(pInfoChara->fNextTime);				// パターン変更時間を設定
	m_pChara->SetVec3Sizing(pInfoChara->sizeChara);				// 大きさを設定
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

	// モーション全体時間を設定	// TODO：ここできてる？
	int nLoop = m_info.vecMotion[nSetMotionID].infoChara.nMaxPtrn;	// 繰り返し数
	for (int nCntPtrn = 0; nCntPtrn < nLoop; nCntPtrn++)
	{ // パターンの総数分繰り返す

		// パターンの変更時間を加算
		m_info.vecMotion[nSetMotionID].fWholeTime += m_info.vecMotion[nSetMotionID].infoChara.fNextTime;
	}
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
bool CMotion2D::IsCancel(const int nType) const
{
	if (m_info.vecMotion[nType].fCancelTime >= 0.0f)
	{ // キャンセルフレームが設定されている場合

		// 引数モーションのキャンセル状況を返す
		return (m_info.fCurTime >= m_info.vecMotion[nType].fCancelTime);
	}

	// キャンセル不可を返す
	return false;
}

//============================================================
//	コンボ取得処理
//============================================================
bool CMotion2D::IsCombo(const int nType) const
{
	if (m_info.vecMotion[nType].fComboTime >= 0.0f)
	{ // コンボフレームが設定されている場合

		// 引数モーションのコンボ状況を返す
		return (m_info.fCurTime >= m_info.vecMotion[nType].fComboTime);
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

//============================================================
//	モーションの更新処理
//============================================================
void CMotion2D::UpdateMotion(void)
{
#if 0
	int nType = m_info.nType;	// モーション種類
	int nKey  = m_info.nKey;	// モーションキー番号

	// 次のモーションキー番号を求める
	int nNextKey = (nKey + 1) % m_info.vecMotion[nType].GetNumKey();

	// パーツの位置の更新
	for (int nCntParts = 0; nCntParts < m_funcGetNumParts(); nCntParts++)
	{ // パーツ数分繰り返す

		// 位置・向きの差分を求める
		D3DXVECTOR3 diffPos = m_info.vecMotion[nType].vecKey[nNextKey].vecParts[nCntParts].pos - m_info.vecMotion[nType].vecKey[nKey].vecParts[nCntParts].pos;
		D3DXVECTOR3 diffRot = m_info.vecMotion[nType].vecKey[nNextKey].vecParts[nCntParts].rot - m_info.vecMotion[nType].vecKey[nKey].vecParts[nCntParts].rot;
		useful::NormalizeRot(diffRot);	// 差分向きの正規化

		// 現在のパーツの位置・向きを更新
		float fRate = (float)m_info.nKeyCounter / (float)m_info.vecMotion[nType].vecKey[nKey].nFrame;	// キーフレーム割合
		m_ppModel[nCntParts]->SetVec3Position(m_info.vecMotion[nType].vecKey[nKey].vecParts[nCntParts].pos + diffPos * fRate);
		m_ppModel[nCntParts]->SetVec3Rotation(m_info.vecMotion[nType].vecKey[nKey].vecParts[nCntParts].rot + diffRot * fRate);
	}

	// モーションの遷移の更新
	if (m_info.nKeyCounter < m_info.vecMotion[nType].vecKey[nKey].nFrame)
	{ // 現在のキーの再生が終了していない場合

		// カウンターを加算
		m_info.nKeyCounter++;
		m_info.nWholeCounter++;
	}
	else
	{ // 現在のキーの再生が終了した場合

		// 次のキーに移行
		if (m_info.vecMotion[nType].bLoop)
		{ // モーションがループする場合

			// キーカウンターを初期化
			m_info.nKeyCounter = 0;

			// キーカウントを加算
			m_info.nKey = (m_info.nKey + 1) % m_info.vecMotion[nType].GetNumKey();	// 最大値で0に戻す

			if (m_info.nKey == 0)
			{ // キーが最初に戻った場合

				// 全体カウンターを初期化
				m_info.nWholeCounter = 0;
			}
		}
		else
		{ // モーションがループしない場合

			if (m_info.nKey < m_info.vecMotion[nType].GetNumKey() - 2)
			{ // 現在のキーが最終のキーではない場合

				// キーカウンターを初期化
				m_info.nKeyCounter = 0;

				// キーカウントを加算
				m_info.nKey++;
			}
			else
			{ // 現在のキーが最終のキーの場合

				// モーションを終了状態にする
				m_info.bFinish = true;
			}
		}
	}
#endif
}
