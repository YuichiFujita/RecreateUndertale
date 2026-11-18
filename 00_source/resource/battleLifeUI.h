//============================================================
//
//	戦闘時の体力表示ヘッダー [battleLifeUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _BATTLE_LIFE_UI_H_
#define _BATTLE_LIFE_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"

//************************************************************
//	インクルードファイル
//************************************************************
class CObject2D;	// オブジェクト2Dクラス
class CGauge2D;		// ゲージ2Dクラス
class CString2D;	// 文字列2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// 戦闘時の体力表示クラス
class CBattleLifeUI : public CObject
{
public:
	// コンストラクタ
	CBattleLifeUI();

	// デストラクタ
	~CBattleLifeUI() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetPriority(const int nPriority) override;		// 優先順位設定
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	inline VECTOR3 GetVec3Position() const override	{ return m_pos; }	// 位置取得
	inline VECTOR3 GetVec3Rotation() const override	{ return m_rot; }	// 向き取得

	// 静的メンバ関数
	static CBattleLifeUI* Create	// 生成
	( // 引数
		const int nMaxHp,	// 最大HP
		const int nNumHp	// HP
	);

	// メンバ関数
	void AddHp(const int nAddHp);		// HP加算
	void SetHp(const int nNumHp);		// HP設定
	void SetMaxHp(const int nMaxHp);	// 最大HP設定
	int GetHp() const;					// HP取得
	int GetMaxHp() const;				// 最大HP取得

private:
	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ関数
	void SetMaxHpString(const int nNumHp, const int nMaxHp);	// 最大HPの文字列設定
	void SetMaxHpGaugeSize(const int nMaxHp);	// 最大HPのゲージ大きさ設定
	void SetPositionRelative();					// 相対位置設定

	// メンバ変数
	CObject2D*	m_pHp;		// HP情報
	CGauge2D*	m_pGauge;	// HPゲージ情報
	CString2D*	m_pMaxHp;	// 最大HP情報
	VECTOR3		m_pos;		// 原点位置
	VECTOR3		m_rot;		// 原点向き
};

#endif	// _BATTLE_LIFE_UI_H_
