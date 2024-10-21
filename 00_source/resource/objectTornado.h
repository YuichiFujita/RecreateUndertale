//============================================================
//
//	オブジェクト竜巻ヘッダー [objectTornado.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _OBJECT_TORNADO_H_
#define _OBJECT_TORNADO_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	定数宣言
//************************************************************
namespace tornado
{
	const int	NUM_AROUND	= 3;		// 渦の周回数
	const int	NUM_PTRN	= 16;		// 渦の分割数
	const float	MOVE_ROT	= 0.3f;		// 向きの変更量
	const float	THICKNESS	= 25.0f;	// ポリゴンの太さ
	const float	OUTER_PLUSY	= 35.0f;	// ポリゴン外周のY座標加算量
	const float	SET_WIDTH	= 80.0f;	// 生成時の横ずれ量
	const float	SET_ALPHA	= 0.85f;	// 生成時の透明度
	const float	ADD_WIDTH	= 7.0f;		// 横ずれの加算量
	const float	ADD_HEIGHT	= 7.0f;		// 縦ずれの加算量
	const float	SUB_ALPHA	= 0.015f;	// 透明度の減算量
	const float	GROW_WIDTH	= 0.0f;		// 横ずれの成長量
	const float	GROW_HEIGHT	= 0.0f;		// 縦ずれの成長量
	const float	GROW_ALPHA	= 0.0f;		// 透明度の成長量
}

//************************************************************
//	クラス定義
//************************************************************
// オブジェクト竜巻クラス
class CObjectTornado : public CObject
{
public:
	// コンストラクタ
	CObjectTornado();

	// デストラクタ
	~CObjectTornado() override;

	// 竜巻構造体
	struct STornado
	{
		VECTOR3 pos;		// 位置
		VECTOR3 rot;		// 向き
		VECTOR3 growRot;	// 成長向き
		COLOR col;			// 色
		MATRIX mtxWorld;	// ワールドマトリックス
		MATRIX* pMtxParent;	// 親のマトリックス
		float fMoveRot;		// 向きの変更量
		float fThickness;	// ポリゴンの太さ
		float fOuterPlusY;	// ポリゴン外周のY座標加算量
		float fSetWidth;	// 生成時の横ずれ量
		float fSetAlpha;	// 生成時の透明度
		float fAddWidth;	// 横ずれの加算量
		float fAddHeight;	// 縦ずれの加算量
		float fSubAlpha;	// 透明度の減算量
		float fGrowWidth;	// 横ずれの成長量
		float fGrowHeight;	// 縦ずれの成長量
		float fGrowAlpha;	// 透明度の成長量
	};

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	VECTOR3 GetVec3Position() const override	{ return m_tornado.pos; }		// 位置取得
	MATRIX* GetPtrMtxWorld() override			{ return &m_tornado.mtxWorld; }	// マトリックスポインタ取得
	MATRIX GetMtxWorld() const override			{ return m_tornado.mtxWorld; }	// マトリックス取得

	// 静的メンバ関数
	static CObjectTornado* Create	// 生成
	( // 引数
		const VECTOR3& rPos,		// 位置
		const VECTOR3& rGrowRot,	// 成長向き
		const COLOR& rCol,			// 色
		MATRIX* pMtxParent		= nullptr,				// 親のマトリックス
		const int	nNumAround	= tornado::NUM_AROUND,	// 渦の周回数
		const int	nPattern	= tornado::NUM_PTRN,	// 渦の分割数
		const float	fMoveRot	= tornado::MOVE_ROT,	// 向きの変更量
		const float	fThickness	= tornado::THICKNESS,	// ポリゴンの太さ
		const float	fOuterPlusY	= tornado::OUTER_PLUSY,	// ポリゴン外周のY座標加算量
		const float	fSetWidth	= tornado::SET_WIDTH,	// 生成時の横ずれ量
		const float	fSetAlpha	= tornado::SET_ALPHA,	// 生成時の透明度
		const float	fAddWidth	= tornado::ADD_WIDTH,	// 横ずれの加算量
		const float	fAddHeight	= tornado::ADD_HEIGHT,	// 縦ずれの加算量
		const float	fSubAlpha	= tornado::SUB_ALPHA,	// 透明度の減算量
		const float	fGrowWidth	= tornado::GROW_WIDTH,	// 横ずれの成長量
		const float	fGrowHeight	= tornado::GROW_HEIGHT,	// 縦ずれの成長量
		const float	fGrowAlpha	= tornado::GROW_ALPHA	// 透明度の成長量
	);

	// メンバ関数
	void SetGrow	// 成長設定
	( // 引数
		const float fMoveRot,		// 向きの変更量
		const float fGrowWidth,		// 横ずれの成長量
		const float fGrowHeight,	// 縦ずれの成長量
		const float fGrowAlpha		// 透明度の成長量
	);
	HRESULT SetVortex	// 渦設定
	( // 引数
		const int nNumAround,	// 渦の周回数
		const int nPattern		// 渦の分割数
	);

	CRenderState* GetRenderState();				// レンダーステート情報取得
	void BindTexture(const int nTextureID);			// テクスチャ割当 (インデックス)
	void BindTexture(const char* pTexturePath);		// テクスチャ割当 (パス)
	void DeleteMatrixParent();					// 親マトリックス削除
	void SetMatrixParent(MATRIX* pMtxParent);		// 親マトリックス設定
	void SetAlpha(const float fAlpha);				// 透明度設定
	void SetColor(const COLOR& rCol);				// 色設定
	void SetRotationGrow(const VECTOR3& rRot);		// 成長向き設定
	void SetThickness(const float fThickness);		// ポリゴンの太さ設定
	void SetOuterPlusY(const float fOuterPlusY);	// ポリゴン外周のY座標加算量設定
	void SetCreateWidth(const float fSetWidth);		// 生成時の横ずれ量設定
	void SetCreateAlpha(const float fSetAlpha);		// 生成時の透明度設定
	void SetAddWidth(const float fAddWidth);		// 横ずれの加算量設定
	void SetAddHeight(const float fAddHeight);		// 縦ずれの加算量設定
	void SetSubAlpha(const float fSubAlpha);		// 透明度の減算量設定
	int GetTextureIndex() const		{ return m_nTextureID; }			// テクスチャインデックス取得
	float GetAlpha() const			{ return m_tornado.col.a; }			// 透明度取得
	COLOR GetColor() const			{ return m_tornado.col; }			// 色取得
	VECTOR3 GetRotationGrow() const	{ return m_tornado.growRot; }		// 成長向き取得
	float GetThickness() const		{ return m_tornado.fThickness; }	// ポリゴンの太さ取得
	float GetOuterPlusY() const		{ return m_tornado.fOuterPlusY; }	// ポリゴン外周のY座標加算量取得
	float GetCreateWidth() const	{ return m_tornado.fSetWidth; }		// 生成時の横ずれ量取得
	float GetCreateAlpha() const	{ return m_tornado.fSetAlpha; }		// 生成時の透明度取得
	float GetAddWidth() const		{ return m_tornado.fAddWidth; }		// 横ずれの加算量取得
	float GetAddHeight() const		{ return m_tornado.fAddHeight; }	// 縦ずれの加算量取得
	float GetSubAlpha() const		{ return m_tornado.fSubAlpha; }		// 透明度の減算量取得

protected:
	// メンバ関数
	void SetVtx();	// 頂点情報の設定

private:
	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ関数
	void DrawNormal();	// 通常描画
	void DrawShader(CShader* pShader);	// シェーダー描画

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	CRenderState* m_pRenderState;		// レンダーステートの情報
	STornado m_tornado;	// 竜巻の情報
	int m_nNumVtx;		// 必要頂点数
	int m_nNumAround;	// 渦の周回数
	int m_nPattern;		// 渦の分割数
	int m_nTextureID;	// テクスチャインデックス
};

#endif	// _OBJECT_TORNADO_H_
