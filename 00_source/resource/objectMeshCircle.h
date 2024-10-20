//============================================================
//
//	オブジェクトメッシュサークルヘッダー [objectMeshCircle.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _OBJECT_MESHCIRCLE_H_
#define _OBJECT_MESHCIRCLE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	クラス定義
//************************************************************
// オブジェクトメッシュサークルクラス
class CObjectMeshCircle : public CObject
{
public:
	// コンストラクタ
	explicit CObjectMeshCircle(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// デストラクタ
	~CObjectMeshCircle() override;

	// メッシュサークル構造体
	struct SMeshCircle
	{
		VECTOR3	pos;		// 位置
		VECTOR3	rot;		// 向き
		COLOR	col;		// 色
		MATRIX	mtxWorld;	// ワールドマトリックス
		float	fRadius;	// 半径
	};

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader *pShader = nullptr) override;		// 描画
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	VECTOR3 GetVec3Position(void) const override	{ return m_meshCircle.pos; }		// 位置取得
	VECTOR3 GetVec3Rotation(void) const override	{ return m_meshCircle.rot; }		// 向き取得
	MATRIX *GetPtrMtxWorld(void) override			{ return &m_meshCircle.mtxWorld; }	// マトリックスポインタ取得
	MATRIX GetMtxWorld(void) const override			{ return m_meshCircle.mtxWorld; }	// マトリックス取得

	// 静的メンバ関数
	static CObjectMeshCircle *Create	// 生成
	( // 引数
		const VECTOR3& rPos,	// 位置
		const VECTOR3& rRot,	// 向き
		const COLOR& rCol,		// 色
		const POSGRID2& rPart,	// 分割数
		const float fRadius		// 半径
	);

	// メンバ関数
	CRenderState *GetRenderState(void);			// レンダーステート情報取得
	void BindTexture(const int nTextureID);		// テクスチャ割当 (インデックス)
	void BindTexture(const char *pTexturePath);	// テクスチャ割当 (パス)
	void SetAlpha(const float fAlpha);			// 透明度設定
	void SetColor(const COLOR& rCol);			// 色設定
	void SetRadius(const float fRadius);		// 半径設定
	HRESULT SetPattern(const POSGRID2& rPart);	// 分割数設定
	int GetTextureIndex(void) const	{ return m_nTextureID; }			// テクスチャインデックス取得
	float GetAlpha(void) const		{ return m_meshCircle.col.a; }		// 透明度取得
	COLOR GetColor(void) const		{ return m_meshCircle.col; }		// 色取得
	float GetRadius(void) const		{ return m_meshCircle.fRadius; }	// 半径取得
	POSGRID2 GetPattern(void) const	{ return m_part; }					// 分割数取得

protected:
	// メンバ関数
	void SetVtx(void);	// 頂点情報の設定
	void SetIdx(void);	// インデックス情報の設定

private:
	// オーバーライド関数
	void Release(void) override { CObject::Release(); }	// 破棄

	// メンバ関数
	void DrawNormal(void);	// 通常描画
	void DrawShader(CShader *pShader);	// シェーダー描画

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファへのポインタ
	CRenderState *m_pRenderState;		// レンダーステートの情報
	SMeshCircle m_meshCircle;			// メッシュサークルの情報
	POSGRID2 m_part;	// 分割数
	int m_nNumVtx;		// 必要頂点数
	int m_nNumIdx;		// 必要インデックス数
	int m_nTextureID;	// テクスチャインデックス
};

#endif	// _OBJECT_MESHCIRCLE_H_
