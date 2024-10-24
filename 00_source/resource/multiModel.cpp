//============================================================
//
//	マルチモデル処理 [multiModel.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "multiModel.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "renderState.h"

//************************************************************
//	子クラス [CMultiModel] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CMultiModel::CMultiModel(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObjectModel(label, dimension, nPriority), m_pParent(nullptr)
{

}

//============================================================
//	デストラクタ
//============================================================
CMultiModel::~CMultiModel()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CMultiModel::Init()
{
	// メンバ変数を初期化
	m_pParent = nullptr;	// 親モデルへのポインタ

	// オブジェクトモデルの初期化
	if (FAILED(CObjectModel::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 自動描画をOFFにする
	SetEnableDraw(false);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CMultiModel::Uninit()
{
	// オブジェクトモデルの終了
	CObjectModel::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CMultiModel::Update(const float fDeltaTime)
{
	// オブジェクトモデルの更新
	CObjectModel::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CMultiModel::Draw(CShader* pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;			// デバイスのポインタ
	CRenderState* pRenderState = GetRenderState();	// レンダーステートの情報
	CModel::SModel modelData = GetModelData();		// モデルの情報
	VECTOR3 pos = GetVec3Position();	// モデルの位置
	VECTOR3 rot = GetVec3Rotation();	// モデルの向き
	VECTOR3 scale = GetVec3Scale();		// モデルの拡大率
	MATRIX mtxScale, mtxRot, mtxTrans;	// 計算用マトリックス
	MATRIX mtxWorld;		// ワールドマトリックス
	MATRIX mtxParent;		// 親のマトリックス
	D3DMATERIAL9 matDef;	// 現在のマテリアル保存用

	// レンダーステートを設定
	pRenderState->Set();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 拡大率を反映
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// 親マトリックスを設定
	if (m_pParent == nullptr)
	{ // 親が存在しない場合

		// 現在のマトリックスを取得
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);	// 設定された最新のマトリックス (実体のマトリックス)
	}
	else
	{ // 親が存在する場合

		// 親のマトリックスを設定
		mtxParent = *m_pParent->GetPtrMtxWorld();
	}

	// ワールドマトリックスと親マトリックスを掛け合わせる
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

	// ワールドマトリックスの反映
	SetMtxWorld(mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	if (pShader == nullptr)
	{ // シェーダーが使用されていない場合

		// 通常描画
		DrawNormal();
	}
	else
	{ // シェーダーが使用されている場合

		// シェーダー描画
		DrawShader(pShader);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	// レンダーステートを再設定
	pRenderState->Reset();
}

//============================================================
//	生成処理
//============================================================
CMultiModel* CMultiModel::Create(const VECTOR3& rPos, const VECTOR3& rRot, const VECTOR3& rScale)
{
	// マルチモデルの生成
	CMultiModel* pMultiModel = new CMultiModel;
	if (pMultiModel == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// マルチモデルの初期化
		if (FAILED(pMultiModel->Init()))
		{ // 初期化に失敗した場合

			// マルチモデルの破棄
			SAFE_DELETE(pMultiModel);
			return nullptr;
		}

		// 位置を設定
		pMultiModel->SetVec3Position(rPos);

		// 向きを設定
		pMultiModel->SetVec3Rotation(rRot);

		// 拡大率を設定
		pMultiModel->SetVec3Scale(rScale);

		// 確保したアドレスを返す
		return pMultiModel;
	}
}

//============================================================
//	親オブジェクトの設定処理
//============================================================
void CMultiModel::SetParentObject(CObject* pObject)
{
	// 引数のオブジェクトポインタを親に設定
	m_pParent = pObject;
}

//============================================================
//	親オブジェクトの設定処理
//============================================================
void CMultiModel::SetParentModel(CMultiModel* pModel)
{
	// 引数のモデルポインタを親に設定
	m_pParent = (CObject*)pModel;
}

//============================================================
//	親オブジェクト削除処理
//============================================================
void CMultiModel::DeleteParentObject()
{
	// 親オブジェクトをnullptrにする
	m_pParent = nullptr;
}

//============================================================
//	通常描画処理
//============================================================
void CMultiModel::DrawNormal()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;		// デバイスのポインタ
	CModel::SModel modelData = GetModelData();	// モデルの情報
	VECTOR3 scale = GetVec3Scale();				// モデルの拡大率
	MATRIX mtxWorld = GetMtxWorld();			// ワールドマトリックス
	for (int nCntMat = 0; nCntMat < (int)modelData.dwNumMat; nCntMat++)
	{ // マテリアルの数分繰り返す

		// マテリアルの設定
		pDevice->SetMaterial(&GetPtrMaterial(nCntMat)->MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(modelData.pTextureIdx[nCntMat]));

		if (scale != VEC3_ONE)
		{ // 拡大率が変更されている場合

			// 頂点法線の自動正規化を有効にする
			pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
		}

		// モデルの描画
		modelData.pMesh->DrawSubset(nCntMat);

		// 頂点法線の自動正規化を無効にする
		pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	}
}

//============================================================
//	シェーダー描画処理
//============================================================
void CMultiModel::DrawShader(CShader* pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;		// デバイスのポインタ
	CModel::SModel modelData = GetModelData();	// モデルの情報
	VECTOR3 scale = GetVec3Scale();				// モデルの拡大率
	MATRIX mtxWorld = GetMtxWorld();			// ワールドマトリックス

	// 描画開始
	pShader->Begin();
	pShader->BeginPass(0);

	// マトリックス情報を設定
	pShader->SetMatrix(&mtxWorld);

	// ライト方向を設定
	pShader->SetLightDirect(&mtxWorld, 0);

	for (int nCntMat = 0; nCntMat < (int)modelData.dwNumMat; nCntMat++)
	{ // マテリアルの数分繰り返す

		// マテリアルの設定
		pDevice->SetMaterial(&GetPtrMaterial(nCntMat)->MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(modelData.pTextureIdx[nCntMat]));

		// マテリアルを設定
		pShader->SetMaterial(GetPtrMaterial(nCntMat)->MatD3D);

		// テクスチャを設定
		pShader->SetTexture(modelData.pTextureIdx[nCntMat]);

		// 状態変更の伝達
		pShader->CommitChanges();

		if (scale != VEC3_ONE)
		{ // 拡大率が変更されている場合

			// 頂点法線の自動正規化を有効にする
			pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
		}

		// モデルの描画
		modelData.pMesh->DrawSubset(nCntMat);

		// 頂点法線の自動正規化を無効にする
		pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	}

	// 描画終了
	pShader->EndPass();
	pShader->End();
}
