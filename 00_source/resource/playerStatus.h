//============================================================
//
//	プレイヤーステータスヘッダー [playerStatus.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PLAYER_STATUS_H_
#define _PLAYER_STATUS_H_

//************************************************************
//	クラス定義
//************************************************************
// プレイヤーステータスクラス
class CPlayerStatus
{
public:
	// コンストラクタ
	CPlayerStatus();

	// デストラクタ
	~CPlayerStatus();

	// メンバ関数
	void ChangeHP(const int nChange);		// 体力増減
	void SwapWeaponIdx(const int nBagIdx);	// 武器アイテムインデックス入替
	void SwapArmorIdx(const int nBagIdx);	// 防具アイテムインデックス入替
	int GetBaseMaxHP() const;				// レベル基準の最大HP取得 (最大レベル)
	int GetBaseMaxHP(const int nLv) const;	// レベル基準の最大HP取得 (レベル指定)
	int GetCurBaseMaxHP() const;			// レベル基準の最大HP取得 (現在レベル)
	int GetAtk(const int nLv) const;		// 攻撃力取得 (レベル指定)
	int GetCurAtk() const;					// 攻撃力取得 (現在レベル)
	int GetDef(const int nLv) const;		// 防御力取得 (レベル指定)
	int GetCurDef() const;					// 防御力取得 (現在レベル)
	int GetNext(const int nLv) const;		// 次レベルまでのEXP取得 (レベル指定)
	int GetCurNext() const;					// 次レベルまでのEXP取得 (現在レベル)
	inline void SetName(const std::string& rName)	{ m_sName = rName; }			// プレイヤー名取得
	inline void SetLove(const int nLove)			{ m_nLove = nLove; }			// レベル取得
	inline void SetHP(const int nHP)				{ m_nHP = nHP; }				// 体力取得
	inline void SetMaxHP(const int nMaxHP)			{ m_nMaxHP = nMaxHP; }			// 最大体力取得
	inline void SetExp(const int nExp)				{ m_nExp = nExp; }				// 経験値取得
	inline void SetWpnItemIdx(const int nItemIdx)	{ m_nWpnItemIdx = nItemIdx; }	// 武器アイテムインデックス取得
	inline void SetAmrItemIdx(const int nItemIdx)	{ m_nAmrItemIdx = nItemIdx; }	// 防具アイテムインデックス取得
	inline void SetNumGold(const int nNumGold)		{ m_nNumGold = nNumGold; }		// 所持金取得
	inline void SetNumKill(const int nNumKill)		{ m_nNumKill = nNumKill; }		// 殺害数取得
	inline void SetSpeed(const float fSpeed)		{ m_fSpeed = fSpeed; }			// 移動速度取得
	inline void SetInvTime(const float fInvTime)	{ m_fInvTime = fInvTime; }		// 無敵時間取得
	inline std::string GetName() const	{ return m_sName; }			// プレイヤー名取得
	inline int GetLove() const			{ return m_nLove; }			// レベル取得
	inline int GetHP() const			{ return m_nHP; }			// 体力取得
	inline int GetMaxHP() const			{ return m_nMaxHP; }		// 最大体力取得
	inline int GetExp() const			{ return m_nExp; }			// 経験値取得
	inline int GetWpnItemIdx() const	{ return m_nWpnItemIdx; }	// 武器アイテムインデックス取得
	inline int GetAmrItemIdx() const	{ return m_nAmrItemIdx; }	// 防具アイテムインデックス取得
	inline int GetNumGold() const		{ return m_nNumGold; }		// 所持金取得
	inline int GetNumKill() const		{ return m_nNumKill; }		// 殺害数取得
	inline float GetSpeed() const		{ return m_fSpeed; }		// 移動速度取得
	inline float GetInvTime() const		{ return m_fInvTime; }		// 無敵時間取得

private:
	// メンバ関数
	void AddHP(const int nAdd);	// 体力加算
	void SubHP(const int nSub);	// 体力減算

	// メンバ変数
	std::string m_sName;	// プレイヤー名
	int m_nLove;			// レベル
	int m_nHP;				// 体力		// TODO：戦闘時のHPバーの実装はこの値をポインタで持って扱おう
	int m_nMaxHP;			// 最大体力
	int m_nExp;				// 経験値
	int m_nWpnItemIdx;		// 武器アイテムインデックス
	int m_nAmrItemIdx;		// 防具アイテムインデックス
	int m_nNumGold;			// 所持金
	int m_nNumKill;			// 殺害数
	float m_fSpeed;			// 移動速度
	float m_fInvTime;		// 無敵時間
};

#endif	// _PLAYER_STATUS_H_
