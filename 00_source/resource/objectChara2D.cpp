//============================================================
//
//	オブジェクトキャラクター2D処理 [objectChara2D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "objectChara2D.h"
#include "manager.h"
#include "renderer.h"
#include "character2D.h"

//************************************************************
//	子クラス [CObjectChara2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CObjectChara2D::CObjectChara2D(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CAnim3D(label, dimension, nPriority)
{

}

//============================================================
//	デストラクタ
//============================================================
CObjectChara2D::~CObjectChara2D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CObjectChara2D::Init(void)
{
	// アニメーション3Dの初期化
	if (FAILED(CAnim3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CObjectChara2D::Uninit(void)
{
	// アニメーション3Dの終了
	CAnim3D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CObjectChara2D::Update(const float fDeltaTime)
{
	// モーションがない場合抜ける
	if (m_info.vecMotion.empty()) { assert(false); return; }

	// アニメーション3Dの更新
	CAnim3D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CObjectChara2D::Draw(CShader *pShader)
{
	// アニメーション3Dの描画
	CAnim3D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CObjectChara2D *CObjectChara2D::Create(const D3DXVECTOR3 &rPos, const D3DXVECTOR3 &rRot)
{
	// オブジェクトキャラクター2Dの生成
	CObjectChara2D *pObjectChara2D = new CObjectChara2D;
	if (pObjectChara2D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// オブジェクトキャラクター2Dの初期化
		if (FAILED(pObjectChara2D->Init()))
		{ // 初期化に失敗した場合

			// オブジェクトキャラクター2Dの破棄
			SAFE_DELETE(pObjectChara2D);
			return nullptr;
		}

		// 位置を設定
		pObjectChara2D->SetVec3Position(rPos);

		// 向きを設定
		pObjectChara2D->SetVec3Rotation(rRot);

		// 確保したアドレスを返す
		return pObjectChara2D;
	}
}

//============================================================
//	キャラクター情報割当
//============================================================
void CObjectChara2D::BindCharaData(const char *pCharaPass)
{
	// 割り当てるモーションパスが存在しない場合抜ける
	if (pCharaPass == nullptr) { assert(false); return; }

	// モーション情報の全設定
	SetAllInfo(GET_MANAGER->GetCharacter2D()->Regist(pCharaPass));
}

//============================================================
//	モーションの設定処理
//============================================================
void CObjectChara2D::SetMotion(const int nType)
{
	// 指定されたモーションが存在しない場合抜ける
	if (nType <= NONE_IDX || nType >= m_info.GetNumMotion()) { assert(false); return; }

	// 引数のモーションの種類を設定
	m_info.nType = nType;

	// 変数をポインタ化し簡略化
	SChara *pInfoChara = &m_info.vecMotion[nType].infoChara;	// キャラクター情報

	// 指定テクスチャの割当
	BindTexture(pInfoChara->sPassTexture.c_str());

	// キャラクター情報を設定
	SetTexPtrn(pInfoChara->ptrnTexture);	// テクスチャ分割数
	SetEnableLoop(pInfoChara->bLoop);		// ループON/OFF
	SetVec3Size(pInfoChara->size);			// 大きさ

	assert((int)pInfoChara->vecNextTime.size() == pInfoChara->nMaxPtrn);
	for (int i = 0; i < pInfoChara->nMaxPtrn; i++)
	{
		// パターン変更時間を設定
		SetNextTime(pInfoChara->vecNextTime[i]);
	}

	// キャラクター情報を初期化
	ResetCurPtrn();	// 開始パターン
	ResetNumLoop();	// 繰り返し数
}

//============================================================
//	モーション情報の追加処理
//============================================================
void CObjectChara2D::AddInfo(const SMotion& rMotion)
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
void CObjectChara2D::SetAllInfo(const SInfo& rInfo)
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
bool CObjectChara2D::IsCancel(void) const
{
	float fCancelTime = m_info.vecMotion[m_info.nType].fCancelTime;	// キャンセル可能時間
	if (fCancelTime >= 0.0f)
	{ // キャンセル可能時間が設定されている場合

		// モーションのキャンセル状況を返す
		return (GetCurWholeTime() >= fCancelTime);
	}

	// キャンセル不可を返す
	return false;
}

//============================================================
//	コンボ取得処理
//============================================================
bool CObjectChara2D::IsCombo(void) const
{
	float fComboTime = m_info.vecMotion[m_info.nType].fComboTime;	// コンボ可能時間
	if (fComboTime >= 0.0f)
	{ // コンボ可能時間が設定されている場合

		// モーションのコンボ状況を返す
		return (GetCurWholeTime() >= fComboTime);
	}

	// コンボ不可を返す
	return false;
}

//============================================================
//	原点オフセット反映位置の計算処理
//============================================================
D3DXVECTOR3 CObjectChara2D::CalcOriginOffsetPosition(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot) const
{
	const D3DXVECTOR3& rOffset = m_info.vecMotion[m_info.nType].infoChara.offset;	// オフセット

	// オフセット反映位置の計算結果を返す
	return CalcOffsetPosition(rPos, rRot, rOffset);
}

//============================================================
//	判定原点オフセット反映位置の計算処理
//============================================================
D3DXVECTOR3 CObjectChara2D::CalcCollOffsetPosition(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot) const
{
	const D3DXVECTOR3& rOffset = m_info.vecMotion[m_info.nType].infoColl.offset;	// オフセット

	// オフセット反映位置の計算結果を返す
	return CalcOffsetPosition(rPos, rRot, rOffset);
}

//============================================================
//	原点オフセット反映位置の取得処理
//============================================================
D3DXVECTOR3 CObjectChara2D::GetOriginOffsetPosition(void) const
{
	const D3DXVECTOR3& rPos = GetVec3Position();	// 位置
	const D3DXVECTOR3& rRot = GetVec3Rotation();	// 向き

	// 原点オフセット反映位置の計算結果を返す
	return CalcOriginOffsetPosition(rPos, rRot);
}

//============================================================
//	判定原点オフセット反映位置の取得処理
//============================================================
D3DXVECTOR3 CObjectChara2D::GetCollOffsetPosition(void) const
{
	const D3DXVECTOR3& rPos = GetVec3Position();	// 位置
	const D3DXVECTOR3& rRot = GetVec3Rotation();	// 向き

	// 判定原点オフセット反映位置の計算結果を返す
	return CalcCollOffsetPosition(rPos, rRot);
}

//============================================================
//	描画マトリックスの計算処理
//============================================================
void CObjectChara2D::CalcDrawMatrix(void)
{
	D3DXVECTOR3 offset = m_info.vecMotion[m_info.nType].infoChara.offset;	// オフセット
	MATRIX *pMtxWorld = GetPtrMtxWorld();	// ワールドマトリックス
	MATRIX mtxRot, mtxTrans, mtxOffset;		// 計算用マトリックス
	D3DXVECTOR3 pos = GetVec3Position();	// 位置
	D3DXVECTOR3 rot = GetVec3Rotation();	// 向き

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(pMtxWorld);

	// オフセットを反映
	D3DXMatrixTranslation(&mtxOffset, offset.x, offset.y, offset.z);
	D3DXMatrixMultiply(pMtxWorld, pMtxWorld, &mtxOffset);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pMtxWorld, pMtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pMtxWorld, pMtxWorld, &mtxTrans);
}

//============================================================
//	オフセット反映位置の計算処理
//============================================================
D3DXVECTOR3 CObjectChara2D::CalcOffsetPosition
(
	const D3DXVECTOR3& rPos,	// 位置
	const D3DXVECTOR3& rRot,	// 向き
	const D3DXVECTOR3& rOffset	// オフセット
) const
{
	MATRIX mtxWorld, mtxRot, mtxTrans, mtxOffset;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// オフセットを反映
	D3DXMatrixTranslation(&mtxOffset, rOffset.x, rOffset.y, rOffset.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxOffset);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rRot.y, rRot.x, rRot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, rPos.x, rPos.y, rPos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// 算出したマトリックスの位置を返す
	return mtxWorld.GetPosition();
}
