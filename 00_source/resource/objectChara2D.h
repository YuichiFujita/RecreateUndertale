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
#include "character.h"

//************************************************************
//	クラス定義
//************************************************************
// オブジェクトキャラクター2Dクラス
class CObjectChara2D : public CAnim3D
{
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
	static CObjectChara2D *Create(const D3DXVECTOR3 &rPos, const D3DXVECTOR3 &rRot = VEC3_ZERO);	// 生成

	// メンバ関数
	void SetPartsInfo	// パーツ情報設定
	( // 引数
		const int nID,				// パーツインデックス
		const int nParentID,		// 親インデックス
		const D3DXVECTOR3& rPos,	// 位置
		const D3DXVECTOR3& rRot,	// 向き
		const char *pFileName		// ファイル名
	);

	void BindCharaData(const char *pCharaPass);				// キャラクター情報割当
	void SetPartsInfo(CCharacter::SPartsInfo& rInfo);		// パーツ情報設定
	void SetMotion(const int nType);						// モーション設定
	CMotion2D *GetMotion(void) const { return m_pMotion; }	// モーション取得

	void AddMotionInfo(const CMotion2D::SMotion& rInfo)	{ m_pMotion->AddInfo(rInfo); }					// モーション情報追加
	void SetEnableMotionUpdate(const bool bUpdate)		{ m_pMotion->SetEnableUpdate(bUpdate); }		// 更新状況設定
	int GetMotionType(void) const			{ return m_pMotion->GetType(); }							// モーション種類取得
	int GetMotionNumType(void) const		{ return m_pMotion->GetNumType(); }							// モーション種類総数取得
	int GetMotionKey(void) const			{ return m_pMotion->GetKey();}								// モーションキー番号取得
	int GetMotionNumKey(void) const			{ return m_pMotion->GetNumKey(m_pMotion->GetType()); }		// モーションキー総数取得
	int GetMotionKeyCounter(void) const		{ return m_pMotion->GetKeyCounter(); }						// モーションキーカウンター取得
	int GetMotionWholeCounter(void) const	{ return m_pMotion->GetWholeCounter(); }					// モーション全体カウンター取得
	int GetMotionWholeFrame(void) const		{ return m_pMotion->GetWholeFrame(m_pMotion->GetType()); }	// モーション全体フレーム数取得
	int GetMotionCancelFrame(void) const	{ return m_pMotion->GetCancelFrame(m_pMotion->GetType()); }	// モーションキャンセルフレーム取得
	int GetMotionComboFrame(void) const		{ return m_pMotion->GetComboFrame(m_pMotion->GetType()); }	// モーションコンボフレーム取得
	bool IsMotionFinish(void) const			{ return m_pMotion->IsFinish(); }							// モーション終了取得
	bool IsMotionLoop(void) const			{ return m_pMotion->IsLoop(m_pMotion->GetType()); }			// モーションループ取得
	bool IsMotionCancel(void) const			{ return m_pMotion->IsCancel(m_pMotion->GetType()); }		// モーションキャンセル取得
	bool IsMotionCombo(void) const			{ return m_pMotion->IsCombo(m_pMotion->GetType()); }		// モーションコンボ取得

private:
	// メンバ変数
	CMotion2D *m_pMotion;	// モーション2D情報
};

#endif	// _OBJECTCHARA2D_H_
