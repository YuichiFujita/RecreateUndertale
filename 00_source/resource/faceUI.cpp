//============================================================
//
//	表情UI処理 [faceUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "faceUI.h"
#include "manager.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 6;	// 表情UIの優先順位
}

//************************************************************
//	子クラス [CFaceUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFaceUI::CFaceUI() : CAnim2D(CObject::LABEL_UI, CObject::DIM_2D, PRIORITY),
	m_pos		(VEC3_ZERO),	// 原点位置
	m_info		({}),			// 表情情報
	m_nTypeEmo	(0)				// 表情種類
{

}

//============================================================
//	デストラクタ
//============================================================
CFaceUI::~CFaceUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFaceUI::Init()
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
void CFaceUI::Uninit()
{
	// アニメーション2Dの終了
	CAnim2D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CFaceUI::Update(const float fDeltaTime)
{
	// 表情がない場合抜ける
	if (m_info.vecEmotion.empty()) { assert(false); return; }

	// アニメーション2Dの更新
	CAnim2D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CFaceUI::Draw(CShader* pShader)
{
	// アニメーション2Dの描画
	CAnim2D::Draw(pShader);
}

//============================================================
//	位置の設定処理
//============================================================
void CFaceUI::SetVec3Position(const VECTOR3& rPos)
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
CFaceUI* CFaceUI::Create(const int nIdxFace, const int nTypeEmo, const VECTOR3& rPos, const VECTOR3& rRot)
{
	// 表情UIの生成
	CFaceUI* pFaceUI = new CFaceUI;
	if (pFaceUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 表情UIの初期化
		if (FAILED(pFaceUI->Init()))
		{ // 初期化に失敗した場合

			// 表情UIの破棄
			SAFE_DELETE(pFaceUI);
			return nullptr;
		}

		// 顔を割当
		pFaceUI->BindFaceData(nIdxFace);

		// 表情を設定
		pFaceUI->SetEmotion(nTypeEmo);

		// 位置を設定
		pFaceUI->SetVec3Position(rPos);

		// 向きを設定
		pFaceUI->SetVec3Rotation(rRot);

		// 確保したアドレスを返す
		return pFaceUI;
	}
}

//============================================================
//	顔の割当処理
//============================================================
void CFaceUI::BindFaceData(const int nIdxFace)
{
	// モーション情報の全設定
	SetAllInfo(GET_MANAGER->GetFaceAnim2D()->GetInfo(nIdxFace));

	// 表情の初期化
	SetEmotion(0);
}

//============================================================
//	表情の設定処理
//============================================================
void CFaceUI::SetEmotion(const int nTypeEmo)
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
void CFaceUI::AddInfo(const AEmotion& rEmotion)
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
void CFaceUI::SetAllInfo(const AFace& rFace)
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
void CFaceUI::SetPositionRelative()
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
