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
//	構造体定義
//************************************************************
// プレイヤーステータス構造体
struct SPlayerStatus
{
public:
	// デフォルトコンストラクタ
	SPlayerStatus() :
		sName		(""),	// プレイヤー名
		nLove		(1),	// レベル	// TODO：外部ファイルからの読み込み作ったら0に戻す
		nHP			(0),	// 体力
		nMaxHP		(0),	// 最大体力
		nCurExp		(0),	// 現在経験値
		nWpnItemIdx	(0),	// 武器アイテムインデックス
		nAmrItemIdx	(0),	// 防具アイテムインデックス
		nGold		(0),	// 残金
		nKills		(0),	// 殺害数
		fSpeed		(0.0f),	// 移動速度
		fInvTime	(0.0f)	// 無敵時間
	{}

	// デストラクタ
	~SPlayerStatus() {}

	// メンバ関数
	int GetMaxHP() const;				// 最大HP取得 (最大レベル)
	int GetMaxHP(const int nLv) const;	// 最大HP取得 (レベル指定)
	int GetCurMaxHP() const;			// 現在の最大HP取得
	int GetAtk(const int nLv) const;	// 攻撃力取得
	int GetCurAtk() const;				// 現在の攻撃力取得
	int GetDef(const int nLv) const;	// 防御力取得
	int GetCurDef() const;				// 現在の防御力取得
	int GetNext(const int nLv) const;	// 次レベルまでのEXP取得
	int GetCurNext() const;				// 現在の次レベルまでのEXP取得

	// メンバ変数
	std::string sName;	// プレイヤー名
	int nLove;			// レベル
	int nHP;			// 体力		// TODO：戦闘時のHPバーの実装はこの値をポインタで持って扱おう
	int nMaxHP;			// 最大体力
	int nCurExp;		// 現在経験値
	int nWpnItemIdx;	// 武器アイテムインデックス
	int nAmrItemIdx;	// 防具アイテムインデックス
	int nGold;			// 残金
	int nKills;			// 殺害数
	float fSpeed;		// 移動速度
	float fInvTime;		// 無敵時間
};

#endif	// _PLAYER_STATUS_H_
