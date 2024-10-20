//============================================================
//
//	オブジェクト2Dヘッダー [object2D.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	クラス定義
//************************************************************
// オブジェクト2Dクラス
class CObject2D : public CObject
{
public:
	// コンストラクタ
	explicit CObject2D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_2D, const int nPriority = object::DEFAULT_PRIO);

	// デストラクタ
	~CObject2D() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	void SetVec3Size(const VECTOR3& rSize) override;	// 大きさ設定
	VECTOR3 GetVec3Position(void) const override	{ return m_pos; }	// 位置取得
	VECTOR3 GetVec3Rotation(void) const override	{ return m_rot; }	// 向き取得
	VECTOR3 GetVec3Size(void) const override		{ return m_size; }	// 大きさ取得

	// メンバ関数
	CRenderState* GetRenderState(void);			// レンダーステート情報取得
	void BindTexture(const int nTextureID);		// テクスチャ割当 (インデックス)
	void BindTexture(const char* pTexturePath);	// テクスチャ割当 (パス)
	void SetAlpha(const float fAlpha);			// 透明度設定
	void SetColor(const COLOR& rCol);			// 色設定
	int GetTextureIndex(void) const	{ return m_nTextureID; }	// テクスチャインデックス取得
	float GetAlpha(void) const		{ return m_col.a; }			// 透明度取得
	COLOR GetColor(void) const		{ return m_col; }			// 色取得

	// 静的メンバ関数
	static CObject2D* Create	// 生成
	( // 引数
		const VECTOR3& rPos,				// 位置
		const VECTOR3& rSize = VEC3_ONE,	// 大きさ
		const VECTOR3& rRot = VEC3_ZERO,	// 向き
		const COLOR& rCol = color::White()	// 色
	);

protected:
	// メンバ関数
	void SetVtx(void);	// 頂点情報の設定
	void SetAnimTex		// アニメーションのテクスチャ座標の設定
	( // 引数
		const int nPattern,		// アニメーションパターン
		const int nWidthPtrn,	// テクスチャの横の分割数
		const int nHeightPtrn	// テクスチャの縦の分割数
	);
	void SetScrollTex	// スクロールのテクスチャ座標の設定
	( // 引数
		const float fTexU,		// テクスチャの横座標の開始位置
		const float fTexV,		// テクスチャの縦座標の開始位置
		const float fOffsetU,	// テクスチャの横座標のオフセット位置
		const float fOffsetV	// テクスチャの縦座標のオフセット位置
	);

private:
	// オーバーライド関数
	void Release(void) override { CObject::Release(); }	// 破棄

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	CRenderState* m_pRenderState;		// レンダーステートの情報
	VECTOR3	m_pos;			// 位置
	VECTOR3	m_rot;			// 向き
	VECTOR3	m_size;			// 大きさ
	COLOR	m_col;			// 色
	float	m_fAngle;		// 対角線の角度
	float	m_fLength;		// 対角線の長さ
	int		m_nTextureID;	// テクスチャインデックス
};

#endif	// _OBJECT2D_H_
