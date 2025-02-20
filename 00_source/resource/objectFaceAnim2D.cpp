//============================================================
//
//	オブジェクト表情アニメーション2D処理 [objectFaceAnim2D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "objectFaceAnim2D.h"
#include "manager.h"
#include "renderer.h"
#include "faceAnim2D.h"

//************************************************************
//	子クラス [CObjectFaceAnim2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CObjectFaceAnim2D::CObjectFaceAnim2D(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CAnim2D(label, dimension, nPriority),
	m_pos		(VEC3_ZERO),	// 原点位置
	m_info		({}),			// 表情情報
	m_nTypeEmo	(0)				// 表情種類
{

}

//============================================================
//	デストラクタ
//============================================================
CObjectFaceAnim2D::~CObjectFaceAnim2D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CObjectFaceAnim2D::Init()
{
	// メンバ変数を初期化
	m_pos		= VEC3_ZERO;	// 原点位置
	m_info		= {};			// 表情情報
	m_nTypeEmo	= 0;			// 表情種類

	// アニメーション2Dの初期化
	if (FAILED(CAnim2D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CObjectFaceAnim2D::Uninit()
{
	// アニメーション2Dの終了
	CAnim2D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CObjectFaceAnim2D::Update(const float fDeltaTime)
{
	// 表情がない場合抜ける
	if (m_info.vecEmotion.empty()) { assert(false); return; }

	// アニメーション2Dの更新
	CAnim2D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CObjectFaceAnim2D::Draw(CShader* pShader)
{
	// アニメーション2Dの描画
	CAnim2D::Draw(pShader);
}

//============================================================
//	位置の設定処理
//============================================================
void CObjectFaceAnim2D::SetVec3Position(const VECTOR3& rPos)
{
	// 原点位置の保存
	m_pos = rPos;

	// 位置の設定
	CAnim2D::SetVec3Position(rPos);

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	生成処理
//============================================================
CObjectFaceAnim2D* CObjectFaceAnim2D::Create(const int nIdxFace, const int nTypeEmo, const VECTOR3& rPos, const VECTOR3& rRot)
{
	// オブジェクト表情アニメーション2Dの生成
	CObjectFaceAnim2D* pObjectFaceAnim2D = new CObjectFaceAnim2D;
	if (pObjectFaceAnim2D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// オブジェクト表情アニメーション2Dの初期化
		if (FAILED(pObjectFaceAnim2D->Init()))
		{ // 初期化に失敗した場合

			// オブジェクト表情アニメーション2Dの破棄
			SAFE_DELETE(pObjectFaceAnim2D);
			return nullptr;
		}

		// 顔を割当
		pObjectFaceAnim2D->BindFaceData(nIdxFace);

		// 表情を設定
		pObjectFaceAnim2D->SetEmotion(nTypeEmo);

		// 位置を設定
		pObjectFaceAnim2D->SetVec3Position(rPos);

		// 向きを設定
		pObjectFaceAnim2D->SetVec3Rotation(rRot);

		// 確保したアドレスを返す
		return pObjectFaceAnim2D;
	}
}

//============================================================
//	顔の割当処理
//============================================================
void CObjectFaceAnim2D::BindFaceData(const int nIdxFace)
{
	// モーション情報の全設定
	SetAllInfo(GET_MANAGER->GetFaceAnim2D()->GetInfo(nIdxFace));

	// 表情の初期化
	SetEmotion(0);
}

//============================================================
//	表情の設定処理
//============================================================
void CObjectFaceAnim2D::SetEmotion(const int nTypeEmo)
{
	// 指定された表情が存在しない場合抜ける
	if (nTypeEmo <= NONE_IDX || nTypeEmo >= m_info.GetNumEmotion()) { assert(false); return; }

	// 引数の表情の種類を設定
	m_nTypeEmo = nTypeEmo;

	// 変数をポインタ化し簡略化
	AEmotion* pInfoEmo = &m_info.vecEmotion[nTypeEmo];	// 表情情報

	// 指定テクスチャの割当
	BindTexture(pInfoEmo->sPathTexture.c_str());

	// 表情情報を設定
	SetTexPtrn(pInfoEmo->ptrnTexture);			// テクスチャ分割数
	SetEnableLoop(pInfoEmo->bLoop);				// ループON/OFF
	SetLoopWaitTime(pInfoEmo->fLoopWaitTime);	// ループ待機時間
	SetVec3Size(pInfoEmo->size);				// 大きさ

	// TODO
	SetEnablePlayBack(true);

	assert((int)pInfoEmo->vecNextTime.size() == pInfoEmo->nMaxPtrn);
	for (int i = 0; i < pInfoEmo->nMaxPtrn; i++)
	{
		// パターン変更時間を設定
		SetNextTime(pInfoEmo->vecNextTime[i]);
	}

	// 顔情報を初期化
	ResetCurPtrn();	// 開始パターン
	ResetNumLoop();	// 繰り返し数
}

//============================================================
//	表情の追加処理
//============================================================
void CObjectFaceAnim2D::AddInfo(const AEmotion& rEmotion)
{
	int nSetEmotionIdx = m_info.GetNumEmotion();	// 表情を設定する配列番号

	// 空の要素を最後尾に追加
	m_info.vecEmotion.emplace_back();

	// 引数の表情情報を設定
	m_info.vecEmotion[nSetEmotionIdx] = rEmotion;
}

//============================================================
//	表情の全設定処理
//============================================================
void CObjectFaceAnim2D::SetAllInfo(const AFace& rFace)
{
	// 表情情報をクリア
	m_info.vecEmotion.clear();

	for (auto& rVec : rFace.vecEmotion)
	{ // 読み込んだ表情数分繰り返す

		// 表情情報の追加
		AddInfo(rVec);
	}
}

//============================================================
//	相対位置の設定処理
//============================================================
void CObjectFaceAnim2D::SetPositionRelative()
{
	VECTOR3 posThis = m_pos;				// 自身の位置
	VECTOR3 rotThis = GetVec3Rotation();	// 自身の向き

	// 変数をポインタ化し簡略化
	AEmotion* pInfoEmo = &m_info.vecEmotion[m_nTypeEmo];	// 表情情報

	// X座標オフセット分ずらす
	posThis.x += sinf(rotThis.z + HALF_PI) * pInfoEmo->offset.x;
	posThis.y += cosf(rotThis.z + HALF_PI) * pInfoEmo->offset.x;

	// Y座標オフセット分ずらす
	posThis.x += sinf(rotThis.z) * pInfoEmo->offset.y;
	posThis.y += cosf(rotThis.z) * pInfoEmo->offset.y;

	// 相対位置の反映
	CAnim2D::SetVec3Position(posThis);
}
