//============================================================
//
//	オブジェクトメッシュチューブヘッダー [objectMeshTube.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _OBJECT_MESHTUBE_H_
#define _OBJECT_MESHTUBE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"
#include "objectMeshCylinder.h"

//************************************************************
//	前方宣言
//************************************************************
class CObjectMeshCircle;	// オブジェクトメッシュサークルクラス
class CRenderState;			// レンダーステートクラス

//************************************************************
//	クラス定義
//************************************************************
// オブジェクトメッシュチューブクラス
class CObjectMeshTube : public CObject
{
public:
	// 蓋列挙
	enum ECover
	{
		COVER_BOTTOM = 0,	// 下蓋
		COVER_TOP,			// 上蓋
		COVER_MAX			// この列挙型の総数
	};

	// コンストラクタ
	explicit CObjectMeshTube(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// デストラクタ
	~CObjectMeshTube() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetPriority(const int nPriority) override;		// 優先順位設定
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	inline VECTOR3 GetVec3Position() const override	{ return m_pCylinder->GetVec3Position(); }	// 位置取得
	inline VECTOR3 GetVec3Rotation() const override	{ return m_pCylinder->GetVec3Rotation(); }	// 向き取得
	inline MATRIX* GetPtrMtxWorld() override		{ return m_pCylinder->GetPtrMtxWorld(); }	// マトリックスポインタ取得
	inline MATRIX GetMtxWorld() const override		{ return m_pCylinder->GetMtxWorld(); }		// マトリックス取得

	// 静的メンバ関数
	static CObjectMeshTube* Create	// 生成
	( // 引数
		const VECTOR3& rPos,		// 位置
		const VECTOR3& rRot,		// 向き
		const COLOR& rCol,			// 色
		const POSGRID2& rPart,		// 分割数
		const POSGRID2& rTexPart,	// テクスチャ分割数
		const float fRadius,		// 半径
		const float fHeight			// 縦幅
	);

	// メンバ関数
	void SetRenderState(CRenderState renderState);	// レンダーステート情報設定
	void BindTexture(const int nTextureIdx);		// テクスチャ割当 (インデックス)
	void BindTexture(const char* pTexturePath);		// テクスチャ割当 (パス)
	void SetAlpha(const float fAlpha);				// 透明度設定
	void SetColor(const COLOR& rCol);				// 色設定
	void SetRadius(const float fRadius);			// 半径設定
	void SetHeight(const float fHeight);			// 縦幅設定
	HRESULT SetPattern(const POSGRID2& rPart);		// 分割数設定
	void SetTexPattern(const POSGRID2& rTexPart);	// テクスチャ分割数設定
	inline int GetTextureIndex() const		{ return m_pCylinder->GetTextureIndex(); }	// テクスチャインデックス取得
	inline float GetAlpha() const			{ return m_pCylinder->GetAlpha(); }			// 透明度取得
	inline COLOR GetColor() const			{ return m_pCylinder->GetColor(); }			// 色取得
	inline float GetRadius() const			{ return m_pCylinder->GetRadius(); }		// 半径取得
	inline float GetHeight() const			{ return m_pCylinder->GetHeight(); }		// 縦幅取得
	inline POSGRID2 GetPattern() const		{ return m_pCylinder->GetPattern(); }		// 分割数取得
	inline POSGRID2 GetTexPattern() const	{ return m_pCylinder->GetTexPattern(); }	// テクスチャ分割数取得

private:
	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ関数
	void SetPositionRelative();				// 相対位置設定
	MATRIX CalcCylinderMtxWorld() const;	// シリンダーマトリックス計算結果取得

	// メンバ変数
	CObjectMeshCircle* m_apCover[COVER_MAX];	// 蓋の情報
	CObjectMeshCylinder* m_pCylinder;			// 筒の情報
	POSGRID2 m_part;	// 分割数
	POSGRID2 m_texPart;	// テクスチャ分割数
};

#endif	// _OBJECT_MESHTUBE_H_
