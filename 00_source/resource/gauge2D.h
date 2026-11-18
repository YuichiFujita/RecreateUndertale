//============================================================
//
//	ゲージ2Dヘッダー [gauge2D.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _GAUGE2D_H_
#define _GAUGE2D_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"

//************************************************************
//	前方宣言
//************************************************************
class CObject2D;	// オブジェクト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// ゲージ2Dクラス
class CGauge2D : public CObject
{
public:
	// 状態列挙
	enum EState
	{
		STATE_NONE = 0,	// 通常状態
		STATE_CHANGE,	// ゲージ変動状態
		STATE_MAX		// この列挙型の総数
	};

	// ポリゴン列挙
	enum EPolygon
	{
		POLYGON_BACK = 0,	// 背景
		POLYGON_FRONT,		// ゲージ
		POLYGON_MAX			// この列挙型の総数
	};

	// コンストラクタ
	explicit CGauge2D(const float fChangeTime);

	// デストラクタ
	~CGauge2D() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	void SetVec3Size(const VECTOR3& rSize) override;	// 大きさ設定
	VECTOR3 GetVec3Position() const override;			// 位置取得
	VECTOR3 GetVec3Rotation() const override;			// 向き取得
	VECTOR3 GetVec3Size() const override;				// 大きさ取得

	// 静的メンバ関数
	static CGauge2D* Create	// 生成
	( // 引数
		const int nMax,								// 最大値
		const float fChangeTime,					// ゲージの変動時間
		const VECTOR3& rPos,						// 位置
		const VECTOR3& rSize = VEC3_ONE,			// 大きさ
		const COLOR& rColFront = color::White(),	// 表ゲージ色
		const COLOR& rColBack = color::Black()		// 裏ゲージ色
	);

	// メンバ関数
	void BindTexture(const int nPolygonIdx, const int nTextureIdx);		// テクスチャ割当 (インデックス)
	void BindTexture(const int nPolygonIdx, const char* pTexturePath);	// テクスチャ割当 (パス)
	int GetTextureIndex(const int nPolygonIdx) const;					// テクスチャインデックス取得

	void AddNum(const int nAdd, const bool bAnim = true);	// 表示値加算
	void SetNum(const int nNum, const bool bAnim = true);	// 表示値設定
	void SetMaxNum(const int nMax);							// 最大値設定
	inline int GetNum() const { return m_nNum; }			// 表示値取得
	inline int GetMaxNum() const { return m_nMaxNum; }		// 最大値取得

	void SetAlphaFront(const float fAlpha);	// 表ゲージ透明度設定
	void SetColorFront(const COLOR& rCol);	// 表ゲージ色設定
	void SetAlphaBack(const float fAlpha);	// 裏ゲージ透明度設定
	void SetColorBack(const COLOR& rCol);	// 裏ゲージ色設定
	float GetAlphaFront() const;			// 表ゲージ透明度取得
	COLOR GetColorFront() const;			// 表ゲージ色取得
	float GetAlphaBack() const;				// 裏ゲージ透明度取得
	COLOR GetColorBack() const;				// 裏ゲージ色取得

private:
	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ関数
	bool UpdateGaugeWidthFront(const float fDeltaTime);	// 表ゲージの横幅更新
	void SetGaugeWidthFront(const float fNum);			// 表ゲージの横幅設定

	// メンバ変数
	CObject2D*	m_pGauge[POLYGON_MAX];	// ゲージ情報
	EState		m_state;				// 状態
	int			m_nNum;					// 表示値
	int			m_nMaxNum;				// 最大値
	float		m_fInitNum;				// 変動開始時の表示値
	float		m_fDestNum;				// 変動終了時の表示値
	float		m_fCurTime;				// 現在の経過時間
	const float	m_fChangeTime;			// ゲージの変動時間
};

#endif	// _GAUGE2D_H_
