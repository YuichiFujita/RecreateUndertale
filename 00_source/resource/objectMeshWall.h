//============================================================
//
//	オブジェクトメッシュウォールヘッダー [objectMeshWall.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _OBJECT_MESHWALL_H_
#define _OBJECT_MESHWALL_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	クラス定義
//************************************************************
// オブジェクトメッシュウォールクラス
class CObjectMeshWall : public CObject
{
public:
	// コンストラクタ
	explicit CObjectMeshWall(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// デストラクタ
	~CObjectMeshWall() override;

	// メッシュウォール構造体
	struct SMeshWall
	{
		VECTOR3	pos;		// 位置
		VECTOR3	rot;		// 向き
		VECTOR2	size;		// 大きさ
		COLOR	col;		// 色
		MATRIX	mtxWorld;	// ワールドマトリックス
	};

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	void SetVec2Size(const VECTOR2& rSize) override;	// 大きさ設定
	VECTOR3 GetVec3Position() const override	{ return m_meshWall.pos; }			// 位置取得
	VECTOR3 GetVec3Rotation() const override	{ return m_meshWall.rot; }			// 向き取得
	VECTOR2 GetVec2Size() const override		{ return m_meshWall.size; }			// 大きさ取得
	MATRIX* GetPtrMtxWorld() override			{ return &m_meshWall.mtxWorld; }	// マトリックスポインタ取得
	MATRIX GetMtxWorld() const override			{ return m_meshWall.mtxWorld; }		// マトリックス取得

	// 静的メンバ関数
	static CObjectMeshWall* Create	// 生成
	( // 引数
		const VECTOR3& rPos,	// 位置
		const VECTOR3& rRot,	// 向き
		const VECTOR2& rSize,	// 大きさ
		const COLOR& rCol,		// 色
		const POSGRID2& rPart	// 分割数
	);

	// メンバ関数
	CRenderState* GetRenderState();			// レンダーステート情報取得
	void BindTexture(const int nTextureID);		// テクスチャ割当 (インデックス)
	void BindTexture(const char* pTexturePath);	// テクスチャ割当 (パス)
	void SetAlpha(const float fAlpha);			// 透明度設定
	void SetColor(const COLOR& rCol);			// 色設定
	HRESULT SetPattern(const POSGRID2& rPart);	// 分割数設定
	int GetTextureIndex() const	{ return m_nTextureID; }		// テクスチャインデックス取得
	float GetAlpha() const		{ return m_meshWall.col.a; }	// 透明度取得
	COLOR GetColor() const		{ return m_meshWall.col; }		// 色取得
	POSGRID2 GetPattern() const	{ return m_part; }				// 分割数取得

protected:
	// メンバ関数
	void SetVtx();	// 頂点情報の設定
	void SetIdx();	// インデックス情報の設定
	void SetScrollTex	// スクロールのテクスチャ座標の設定
	( // 引数
		const float fTexU,	// テクスチャの横座標の開始位置
		const float fTexV	// テクスチャの縦座標の開始位置
	);

private:
	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ関数
	void DrawNormal();	// 通常描画
	void DrawShader(CShader* pShader);	// シェーダー描画

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファへのポインタ
	CRenderState* m_pRenderState;		// レンダーステートの情報
	SMeshWall m_meshWall;	// メッシュウォールの情報
	POSGRID2 m_part;		// 分割数
	int m_nNumVtx;			// 必要頂点数
	int m_nNumIdx;			// 必要インデックス数
	int m_nTextureID;		// テクスチャインデックス
};

#endif	// _OBJECT_MESHWALL_H_
