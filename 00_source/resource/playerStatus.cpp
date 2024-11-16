//============================================================
//
//	プレイヤーステータス処理 [playerStatus.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "playerStatus.h"
#include "playerItem.h"
#include "sceneGame.h"
#include "player.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	namespace love
	{
		const int MIN = 1;	// 最小レベル
		const int MAX = 20;	// 最大レベル
	}

	namespace hp
	{
		const int MAX_MIN_LOVE = 20;	// レベル1の最大体力
		const int MAX_MAX_LOVE = 99;	// 最大レベル時の最大体力
		const int PLUS = 4;				// レベル上昇時の体力加算量
	}

	namespace atk
	{
		const int NUM_MIN_LOVE = 0;	// レベル1の攻撃力
		const int PLUS = 2;			// レベル上昇時の攻撃力加算量
	}

	namespace def
	{
		const int NUM_MIN_LOVE = 0;	// レベル1の防御力
		const int INTERVAL = 4;		// 防御力が上昇するレベル間隔量
		const int PLUS = 1;			// レベル上昇時の防御力加算量
	}

	namespace exp
	{
		const int LV_NEXT[] =	// 次レベルまでに必要な経験値
		{
			10,		20,		40,		50,		80,
			100,	200,	300,	400,	500,
			800,	1000,	1500,	2000,	3000,
			5000,	10000,	25000,	49999,	0,
		};
	}
}

//************************************************************
//	親クラス [CPlayerStatus] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPlayerStatus::CPlayerStatus() :
	m_sName			(""),	// プレイヤー名
	m_nLove			(1),	// レベル	// TODO：外部ファイルからの読み込み作ったら0に戻す
	m_nHP			(0),	// 体力
	m_nMaxHP		(0),	// 最大体力
	m_nExp			(0),	// 経験値
	m_nWpnItemIdx	(0),	// 武器アイテムインデックス
	m_nAmrItemIdx	(0),	// 防具アイテムインデックス
	m_nNumGold		(0),	// 所持金
	m_nNumKill		(0),	// 殺害数
	m_fSpeed		(0.0f),	// 移動速度
	m_fInvTime		(0.0f)	// 無敵時間
{

}

//============================================================
//	デストラクタ
//============================================================
CPlayerStatus::~CPlayerStatus()
{

}

//============================================================
//	体力の増減処理
//============================================================
void CPlayerStatus::ChangeHP(const int nChange)
{
	if (nChange > 0)
	{ // 体力を増加させる場合

		// 体力の加算
		AddHP(nChange);
	}
	else if (nChange < 0)
	{ // 体力を減少させる場合

		// 体力の減算
		SubHP(-nChange);
	}
}

//============================================================
//	武器アイテムインデックスの入替処理
//============================================================
void CPlayerStatus::SwapWeaponIdx(const int nBagIdx)
{
	CPlayerItem* pItem = CSceneGame::GetPlayer()->GetItem();	// プレイヤー所持アイテム情報

	// 所持アイテム数の範囲外インデックスなら抜ける
	if (nBagIdx > pItem->GetNumItem()) { return; }

	// アイテムインデックスの入れ替え
	int nTempWpn = m_nWpnItemIdx;				// 現在の武器インデックスを保存
	m_nWpnItemIdx = pItem->GetItemIdx(nBagIdx);	// バッグ内の武器インデックスに変更
	pItem->SetItemIdx(nBagIdx, nTempWpn);		// バック内に元の武器インデックスを入替
}

//============================================================
//	防具アイテムインデックスの入替処理
//============================================================
void CPlayerStatus::SwapArmorIdx(const int nBagIdx)
{
	CPlayerItem* pItem = CSceneGame::GetPlayer()->GetItem();	// プレイヤー所持アイテム情報

	// 所持アイテム数の範囲外インデックスなら抜ける
	if (nBagIdx > pItem->GetNumItem()) { return; }

	// アイテムインデックスの入れ替え
	int nTempAmr = m_nAmrItemIdx;				// 現在の防具インデックスを保存
	m_nAmrItemIdx = pItem->GetItemIdx(nBagIdx);	// バッグ内の防具インデックスに変更
	pItem->SetItemIdx(nBagIdx, nTempAmr);		// バック内に元の防具インデックスを入替
}

//============================================================
//	レベル基準の最大HP取得処理 (最大レベル)
//============================================================
int CPlayerStatus::GetBaseMaxHP() const
{
	// 最大レベル時のHPを返す
	return hp::MAX_MAX_LOVE;
}

//============================================================
//	レベル基準の最大HP取得処理 (レベル指定)
//============================================================
int CPlayerStatus::GetBaseMaxHP(const int nLv) const
{
	// レベルが範囲外の場合抜ける
	if (nLv <= 0 || nLv > love::MAX) { assert(false); return 0; }

	if (nLv < love::MAX)
	{ // 最大レベル未満の場合

		// 指定レベル時の最大HPを返す
		return hp::MAX_MIN_LOVE + (hp::PLUS * (nLv - 1));
	}

	// 最大レベル時の最大HPを返す
	return hp::MAX_MAX_LOVE;
}

//============================================================
//	レベル基準の最大HP取得処理 (現在レベル)
//============================================================
int CPlayerStatus::GetCurBaseMaxHP() const
{
	// 現在の最大HPを返す
	return GetBaseMaxHP(m_nLove);
}

//============================================================
//	攻撃力の取得処理 (レベル指定)
//============================================================
int CPlayerStatus::GetAtk(const int nLv) const
{
	// レベルが範囲外の場合抜ける
	if (nLv <= 0 || nLv > love::MAX) { assert(false); return 0; }

	// 指定レベル時の攻撃力を返す
	return atk::NUM_MIN_LOVE + (atk::PLUS * (nLv - 1));
}

//============================================================
//	攻撃力の取得処理 (現在レベル)
//============================================================
int CPlayerStatus::GetCurAtk() const
{
	// 現在の攻撃力を返す
	return GetAtk(m_nLove);
}

//============================================================
//	防御力の取得処理 (レベル指定)
//============================================================
int CPlayerStatus::GetDef(const int nLv) const
{
	// レベルが範囲外の場合抜ける
	if (nLv <= 0 || nLv > love::MAX) { assert(false); return 0; }

	// 指定レベル時の防御力を返す
	return def::NUM_MIN_LOVE + (def::PLUS * ((nLv - 1) / def::INTERVAL));
}

//============================================================
//	防御力の取得処理 (現在レベル)
//============================================================
int CPlayerStatus::GetCurDef() const
{
	// 現在の防御力を返す
	return GetDef(m_nLove);
}

//============================================================
//	次レベルまでのEXP取得処理 (レベル指定)
//============================================================
int CPlayerStatus::GetNext(const int nLv) const
{
	// レベルが範囲外の場合抜ける
	if (nLv <= 0 || nLv > love::MAX) { assert(false); return 0; }

	// 指定レベル時のEXPを返す
	return exp::LV_NEXT[nLv];
}

//============================================================
//	次レベルまでのEXP取得処理 (現在レベル)
//============================================================
int CPlayerStatus::GetCurNext() const
{
	// 現在のEXPを返す
	return GetNext(m_nLove);
}

//============================================================
//	体力の加算処理
//============================================================
void CPlayerStatus::AddHP(const int nAdd)
{
	// 体力を回復させる
	m_nHP += nAdd;

	// 体力の値を補正
	useful::LimitNum(m_nHP, 0, GetCurBaseMaxHP());
}

//============================================================
//	体力の減算処理
//============================================================
void CPlayerStatus::SubHP(const int nSub)
{
	int nDamage = nSub;					// ダメージ量
	int nBaseMaxHP = GetCurBaseMaxHP();	// レベル基準の最大HP
	if (m_nMaxHP > nBaseMaxHP)
	{ // 現在の最大HPがレベル基準の最大HPより多い場合

		int nDiffHP = m_nMaxHP - nBaseMaxHP;	// 最大HPの差分
		if (nDamage > nDiffHP)
		{ // ダメージ量が最大HPの差分より多い場合

			// 最大体力をレベル基準に修正
			m_nMaxHP = nBaseMaxHP;

			// 与えるダメージ量を軽減
			nDamage -= nDiffHP;
		}
		else
		{ // ダメージ量が最大HPの差分より少ない場合

			// 最大体力にダメージを与える
			m_nMaxHP -= nDamage;
			return;
		}
	}

	// 体力にダメージを与える
	m_nHP -= nDamage;

	// 体力の値を補正
	useful::LimitNum(m_nHP, 0, nBaseMaxHP);
}
