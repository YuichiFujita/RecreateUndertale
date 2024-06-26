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
#include "multiModel.h"
#include "motion.h"

//************************************************************
//	子クラス [CObjectChara2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CObjectChara2D::CObjectChara2D(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CAnim3D(label, dimension, nPriority),
	m_pMotion	(nullptr)	// モーション情報
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
	// メンバ変数を初期化
	m_pMotion = nullptr;	// モーション情報

	// モーションの生成
	//m_pMotion = CMotion::Create(this);	// TODO
	if (m_pMotion == nullptr)
	{ // 生成に失敗した場合

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
	// モーションの破棄
	SAFE_REF_RELEASE(m_pMotion);
}

//============================================================
//	更新処理
//============================================================
void CObjectChara2D::Update(const float fDeltaTime)
{
	// モーションの更新
	assert(m_pMotion != nullptr);
	m_pMotion->Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CObjectChara2D::Draw(CShader *pShader)
{

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
//	パーツ情報の設定処理
//============================================================
void CObjectChara2D::SetPartsInfo
(
	const int nID,				// パーツインデックス
	const int nParentID,		// 親インデックス
	const D3DXVECTOR3& rPos,	// 位置
	const D3DXVECTOR3& rRot,	// 向き
	const char *pFileName		// ファイル名
)
{
#if 0
	// インデックスが非正規の場合抜ける
	int nNumParts = GetNumParts();	// パーツの総数
	if (nID <= NONE_IDX || nID >= nNumParts) { assert(false); return; }
	if (nParentID <= NONE_IDX - 1 || nParentID >= nNumParts) { assert(false); return; }

	// ファイル指定がない場合抜ける
	if (pFileName == nullptr) { assert(false); return; }

	// モデルの原点位置・向きを設定
	m_pMotion->SetOriginPosition(rPos, nID);
	m_pMotion->SetOriginRotation(rRot, nID);

	// モデルの生成
	m_vecParts[nID] = CMultiModel::Create(rPos, rRot);

	// モデルを割当
	m_vecParts[nID]->BindModel(pFileName);

	// 親モデルの設定
	if (nParentID == NONE_IDX)
	{ // 親がない場合

		// nullptrを設定
		m_vecParts[nID]->SetParentModel(nullptr);
	}
	else
	{ // 親がいる場合

		// 親のアドレスを設定
		m_vecParts[nID]->SetParentModel(m_vecParts[nParentID]);
	}
#endif
}

//============================================================
//	キャラクター情報割当
//============================================================
void CObjectChara2D::BindCharaData(const char *pCharaPass)
{
	// 割り当てるモーションパスが存在しない場合抜ける
	if (pCharaPass == nullptr) { assert(false); return; }

#if 0
	CCharacter::SCharaData data = GET_MANAGER->GetCharacter()->Regist(pCharaPass);	// キャラクター情報

	// モーション情報の動的配列のクリア
	m_pMotion->ClearVector();

	// 自身とモーションのパーツ数を設定
	SetNumParts(data.infoParts.GetNumParts());

	// 自身のパーツ情報を設定
	SetPartsInfo(data.infoParts);

	// モーションにパーツ情報を割当
	m_pMotion->BindPartsData(&m_vecParts[0]);

	// モーションにモーション情報の全設定
	m_pMotion->SetAllInfo(data.infoMotion);
#endif
}

//============================================================
//	パーツ情報の設定処理
//============================================================
void CObjectChara2D::SetPartsInfo(CCharacter::SPartsInfo& rInfo)
{
	for (int nCntParts = 0; nCntParts < rInfo.GetNumParts(); nCntParts++)
	{ // パーツ数分繰り返す

		// パーツ情報の設定
		CCharacter::SParts *pParts = &rInfo.vecParts[nCntParts];	// パーツ情報
		CObjectChara2D::SetPartsInfo
		( // 引数
			nCntParts,				// パーツインデックス
			pParts->nParentID,		// 親インデックス
			pParts->pos,			// 位置
			pParts->rot,			// 向き
			pParts->strPass.c_str()	// ファイル名
		);
	}
}

//============================================================
//	モーションの設定処理
//============================================================
void CObjectChara2D::SetMotion(const int nType)
{
	// モーションの設定
	m_pMotion->Set(nType);
}
