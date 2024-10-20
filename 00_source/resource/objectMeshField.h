//============================================================
//
//	オブジェクトメッシュフィールドヘッダー [objectMeshField.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _OBJECT_MESHFIELD_H_
#define _OBJECT_MESHFIELD_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	クラス定義
//************************************************************
// オブジェクトメッシュフィールドクラス
class CObjectMeshField : public CObject
{
public:
	// コンストラクタ
	explicit CObjectMeshField(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// デストラクタ
	~CObjectMeshField() override;

	// メッシュフィールド構造体
	struct SMeshField
	{
		VECTOR3	pos;		// 位置
		VECTOR3	rot;		// 向き
		VECTOR2	size;		// 大きさ
		COLOR	col;		// 色
		MATRIX	mtxWorld;	// ワールドマトリックス
	};

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	void SetVec2Size(const VECTOR2& rSize) override;	// 大きさ設定
	VECTOR3 GetVec3Position(void) const override	{ return m_meshField.pos; }			// 位置取得
	VECTOR3 GetVec3Rotation(void) const override	{ return m_meshField.rot; }			// 向き取得
	VECTOR2 GetVec2Size(void) const override		{ return m_meshField.size; }		// 大きさ取得
	MATRIX *GetPtrMtxWorld(void) override			{ return &m_meshField.mtxWorld; }	// マトリックスポインタ取得
	MATRIX GetMtxWorld(void) const override			{ return m_meshField.mtxWorld; }	// マトリックス取得

	// 静的メンバ関数
	static CObjectMeshField *Create	// 生成
	( // 引数
		const VECTOR3& rPos,	// 位置
		const VECTOR3& rRot,	// 向き
		const VECTOR2& rSize,	// 大きさ
		const COLOR& rCol,		// 色
		const POSGRID2& rPart	// 分割数
	);

	// メンバ関数
	CRenderState *GetRenderState(void);			// レンダーステート情報取得
	void BindTexture(const int nTextureID);		// テクスチャ割当 (インデックス)
	void BindTexture(const char *pTexturePath);	// テクスチャ割当 (パス)
	void SetAlpha(const float fAlpha);			// 透明度設定
	void SetColor(const COLOR& rCol);			// 色設定
	HRESULT SetPattern(const POSGRID2& rPart);	// 分割数設定
	int GetTextureIndex(void) const	{ return m_nTextureID; }		// テクスチャインデックス取得
	float GetAlpha(void) const		{ return m_meshField.col.a; }	// 透明度取得
	COLOR GetColor(void) const		{ return m_meshField.col; }		// 色取得
	POSGRID2 GetPattern(void) const	{ return m_part; }				// 分割数取得
	int GetNumVertex(void) const	{ return m_nNumVtx; }			// 頂点数取得

	void SetGapPosition(const int nID, const VECTOR3& rPos);		// 座標のずれ設定
	VECTOR3 GetGapPosition(const int nID);							// 座標のずれ取得
	void NormalizeNormal(void);										// 法線の正規化
	bool LandPosition(VECTOR3& rPos, VECTOR3& rMove);				// メッシュ着地
	void SetMeshVertexPosition(const int nID, const VECTOR3& rPos);	// メッシュの頂点位置設定
	void SetTerrain(const POSGRID2& rPart, VECTOR3 *pPosGap);		// 地形設定

	VECTOR3 GetMeshVertexPosition(const int nID);		// メッシュの頂点位置取得
	bool IsPositionRange(const VECTOR3& rPos);			// メッシュの範囲内取得
	float GetPositionHeight(const VECTOR3& rPos);		// メッシュの着地位置取得 (回転非考慮)
	float GetPositionRotateHeight(const VECTOR3& rPos);	// メッシュの着地位置取得 (回転考慮)

protected:
	// メンバ関数
	void SetVtx(bool bNor);	// 頂点情報の設定
	void SetIdx(void);		// インデックス情報の設定
	void SetScrollTex		// スクロールのテクスチャ座標の設定
	( // 引数
		const float fTexU,	// テクスチャの横座標の開始位置
		const float fTexV	// テクスチャの縦座標の開始位置
	);

private:
	// オーバーライド関数
	void Release(void) override { CObject::Release(); }	// 破棄

	// メンバ関数
	void DrawNormal(void);	// 通常描画
	void DrawShader(CShader* pShader);	// シェーダー描画
	VECTOR3 GetNormalLeft(VERTEX_3D *pVtx);			// 法線の取得 (左)
	VECTOR3 GetNormalLeftTop(VERTEX_3D *pVtx);		// 法線の取得 (左上)
	VECTOR3 GetNormalLeftBottom(VERTEX_3D *pVtx);	// 法線の取得 (左下)
	VECTOR3 GetNormalRight(VERTEX_3D *pVtx);		// 法線の取得 (右)
	VECTOR3 GetNormalRightTop(VERTEX_3D *pVtx);		// 法線の取得 (右上)
	VECTOR3 GetNormalRightBottom(VERTEX_3D *pVtx);	// 法線の取得 (右下)

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファへのポインタ
	CRenderState *m_pRenderState;		// レンダーステートの情報
	VECTOR3 *m_pPosGapBuff;	// 座標のずれバッファへのポインタ
	VECTOR3 *m_pNorBuff;	// 法線バッファへのポインタ
	int *m_pNumNorBuff;		// 法線の使用数バッファへのポインタ
	SMeshField m_meshField;	// メッシュフィールドの情報
	POSGRID2 m_part;		// 分割数
	int m_nNumVtx;			// 必要頂点数
	int m_nNumIdx;			// 必要インデックス数
	int m_nTextureID;		// テクスチャインデックス
};

#endif	// _OBJECT_MESHFIELD_H_
