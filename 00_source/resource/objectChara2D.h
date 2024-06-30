//============================================================
//
//	オブジェクトキャラクター2Dヘッダー [objectChara2D.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _OBJECTCHARA2D_H_
#define _OBJECTCHARA2D_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "anim3D.h"
#include "motion2D.h"

//************************************************************
//	クラス定義
//************************************************************
// オブジェクトキャラクター2Dクラス
class CObjectChara2D : public CAnim3D
{
public:
	// コンストラクタ
	explicit CObjectChara2D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// デストラクタ
	~CObjectChara2D() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CObjectChara2D *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot = VEC3_ZERO);	// 生成

	// メンバ関数
	void BindCharaData(const char *pCharaPass);				// キャラクター情報割当
	void SetMotion(const int nType);						// モーション設定
	CMotion2D *GetMotion(void) const { return m_pMotion; }	// モーション取得

	void AddMotionInfo(const CMotion2D::SMotion& rInfo)	{ m_pMotion->AddInfo(rInfo); }					// モーション情報追加
	float GetMotionCancelTime(void) const	{ return m_pMotion->GetCancelTime(m_pMotion->GetType()); }	// モーションキャンセル時間取得
	float GetMotionComboTime(void) const	{ return m_pMotion->GetComboTime(m_pMotion->GetType()); }	// モーションコンボ時間取得
	int GetMotionType(void) const			{ return m_pMotion->GetType(); }	// モーション種類取得
	int GetMotionNumType(void) const		{ return m_pMotion->GetNumType(); }	// モーション種類総数取得
	bool IsMotionCancel(void) const			{ return m_pMotion->IsCancel(); }	// モーションキャンセル取得
	bool IsMotionCombo(void) const			{ return m_pMotion->IsCombo(); }	// モーションコンボ取得

private:
	// メンバ変数
	CMotion2D *m_pMotion;	// モーション2D情報
};

#endif	// _OBJECTCHARA2D_H_
