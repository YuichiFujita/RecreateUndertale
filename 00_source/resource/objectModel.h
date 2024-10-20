//============================================================
//
//	オブジェクトモデルヘッダー [objectModel.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _OBJECTMODEL_H_
#define _OBJECTMODEL_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"
#include "model.h"
#include "renderState.h"

//************************************************************
//	クラス定義
//************************************************************
// オブジェクトモデルクラス
class CObjectModel : public CObject
{
public:
	// コンストラクタ
	explicit CObjectModel(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// デストラクタ
	~CObjectModel() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	void SetVec3Scale(const VECTOR3& rScale) override;	// 拡大率設定
	VECTOR3 GetVec3Position(void) const override	{ return m_pos; }		// 位置取得
	VECTOR3 GetVec3Rotation(void) const override	{ return m_rot; }		// 向き取得
	VECTOR3 GetVec3Scale(void) const override		{ return m_scale; }		// 拡大率取得
	MATRIX *GetPtrMtxWorld(void) override			{ return &m_mtxWorld; }	// マトリックスポインタ取得
	MATRIX GetMtxWorld(void) const override			{ return m_mtxWorld; }	// マトリックス取得

	// 静的メンバ関数
	static CObjectModel *Create	// 生成
	( // 引数
		const VECTOR3& rPos,	// 位置
		const VECTOR3& rRot,	// 向き
		const VECTOR3& rScale = VEC3_ONE	// 大きさ
	);

	// メンバ関数
	void SetMaterial(const D3DXMATERIAL& rMat, const int nMatID);	// マテリアル設定
	D3DXMATERIAL GetMaterial(const int nMatID) const;	// マテリアル取得
	void SetAlpha(const float fAlpha);	// 透明度設定
	float GetAlpha(void) const;			// 透明度取得
	float GetMaxAlpha(void) const;		// 最大透明度取得

	CRenderState *GetRenderState(void);					// レンダーステート情報取得
	void BindModel(const int nModelID);					// モデル割当 (インデックス)
	void BindModel(const char *pModelPath);				// モデル割当 (パス)
	void SetAllMaterial(const D3DXMATERIAL& rMat);		// マテリアル全設定
	void ResetMaterial(void);							// マテリアル再設定
	void SetModelData(const CModel::SModel& rModel);	// モデル情報設定
	void SetMtxWorld(const MATRIX& rMtxWorld);			// マトリックス設定
	int GetModelID(void) const				{ return m_nModelID; }	// モデルインデックス取得
	CModel::SModel GetModelData(void) const	{ return m_modelData; }	// モデル情報取得

protected:
	// メンバ関数
	D3DXMATERIAL *GetPtrMaterial(const int nID) const;	// マテリアルポインタ取得

private:
	// オーバーライド関数
	void Release(void) override { CObject::Release(); }	// 破棄

	// メンバ関数
	HRESULT SetOriginMaterial(const LPD3DXBUFFER pBuffMat, const int nNumMat);	// 元マテリアル設定
	void DrawNormal(void);				// 通常描画
	void DrawShader(CShader* pShader);	// シェーダー描画

	// メンバ変数
	CRenderState	*m_pRenderState;	// レンダーステートの情報
	D3DXMATERIAL	*m_pMat;			// マテリアルへのポインタ
	CModel::SModel	m_modelData;		// モデル情報
	MATRIX	m_mtxWorld;	// ワールドマトリックス
	VECTOR3	m_pos;		// 位置
	VECTOR3	m_rot;		// 向き
	VECTOR3	m_scale;	// 拡大率
	int		m_nModelID;	// モデルインデックス
};

#endif	// _OBJECTMODEL_H_
