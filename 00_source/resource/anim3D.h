//============================================================
//
//	アニメーション3Dヘッダー [anim3D.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ANIM3D_H_
#define _ANIM3D_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object3D.h"

//************************************************************
//	クラス定義
//************************************************************
// アニメーション3Dクラス
class CAnim3D : public CObject3D
{
public:
	// 定数
	static constexpr float DEF_NEXT = 1.0f;	// パターン変更時間 (デフォルト)

	// コンストラクタ
	explicit CAnim3D(const CObject::ELabel label = LABEL_NONE, const EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// デストラクタ
	~CAnim3D() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;			// 更新
	void Draw(CShader *pShader = nullptr) override;			// 描画
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// 向き設定
	void SetVec3Sizing(const D3DXVECTOR3& rSize) override;	// 大きさ設定

	// 静的メンバ関数
	static CAnim3D *Create	// 生成
	( // 引数
		const POSGRID2& rPtrn,		// テクスチャ分割数
		const D3DXVECTOR3& rPos,	// 位置
		const float fNextTime = DEF_NEXT,		// パターン変更時間
		const D3DXVECTOR3& rSize = VEC3_ONE,	// 大きさ
		const D3DXVECTOR3& rRot = VEC3_ZERO,	// 向き
		const D3DXCOLOR& rCol = XCOL_WHITE		// 色
	);

	// メンバ関数
	void SetColor(const D3DXCOLOR& rCol);				// 色設定
	void SetCurPtrn(const int nPtrn);					// 現在パターン設定
	void SetTexPtrn(const POSGRID2& rPtrn);				// テクスチャ分割数設定
	void SetTexPtrnWidth(const int nTexPtrnW);			// テクスチャ横分割数設定
	void SetTexPtrnHeight(const int nTexPtrnH);			// テクスチャ縦分割数設定
	void SetEnablePlay(const bool bPlay);				// 再生フラグ設定
	void SetEnablePlayBack(const bool bPlayBack);		// 逆再生フラグ設定
	int GetPattern(void) const	{ return m_nCurPtrn; }	// パターン取得
	int GetLoopAnim(void) const	{ return m_nNumLoop; }	// パターン繰り返し数取得

	void SetNextTime(const int nPtrnID, const float fNextTime);	// パターン変更時間設定 (パターン指定)
	void SetNextTime(const float fNextTime);					// パターン変更時間設定 (全パターン)

private:
	// メンバ関数
	HRESULT SetMaxPtrn(const int nMaxPtrn);	// パターン総数設定
	void NextPtrn(void);	// パターン加算
	void BackPtrn(void);	// パターン減算

	// メンバ変数
	std::function<void(void)> m_funcNext;	// パターン変更関数ポインタ
	POSGRID2 m_ptrn;	// テクスチャ分割数
	float *m_pNextTime;	// パターン変更時間
	float m_fCurTime;	// 現在の待機時間
	int m_nCurPtrn;		// 現在のパターン
	int m_nMaxPtrn;		// パターン総数
	int m_nNumLoop;		// パターン繰り返し数
	bool m_bPlay;		// 再生状況
	bool m_bPlayBack;	// 逆再生状況
};

#endif	// _ANIM3D_H_
