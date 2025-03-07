﻿//============================================================
//
//	回復アイテム処理 [itemHeal.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "itemHeal.h"
#include "sceneGame.h"
#include "player.h"
#include "playerItem.h"
#include "playerStatus.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{

}

//************************************************************
//	子クラス [CItemHeal] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CItemHeal::CItemHeal() :
	m_nHeal		(0),	// 回復量
	m_bUseEnd	(false)	// 使用後の文字表示フラグ
{

}

//============================================================
//	デストラクタ
//============================================================
CItemHeal::~CItemHeal()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CItemHeal::Init()
{
	// メンバ変数を初期化
	m_nHeal = 0;		// 回復量
	m_bUseEnd = true;	// 使用後の文字表示フラグ

	// アイテム情報の初期化
	if (FAILED(CItemData::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CItemHeal::Uninit()
{
	// アイテム情報の終了
	CItemData::Uninit();
}

//============================================================
//	アイテム使用処理
//============================================================
void CItemHeal::Use(const int nBagIdx) const
{
	// 体力の回復
	CPlayerStatus* pStatus = CSceneGame::GetPlayer()->GetStatus();	// プレイヤーステータス情報
	pStatus->ChangeHP(m_nHeal);

	// 使用したアイテムの削除
	CPlayerItem* pItem = CSceneGame::GetPlayer()->GetItem();	// プレイヤー所持アイテム情報
	pItem->DeleteItem(nBagIdx);
}

//============================================================
//	アイテム詳細の文字列取得処理
//============================================================
std::string CItemHeal::Detail() const
{
	CPlayerStatus status = *CSceneGame::GetPlayer()->GetStatus();	// ステータス情報

	// アイテム詳細の取得
	std::string sDetail = CItemData::Detail();

	if (m_nHeal >= status.GetMaxHP())
	{ // HP上限以上の場合

		// 全回復を表示
		sDetail.append("HPぜんかいふく");
	}
	else if (m_nHeal < 0)
	{ // マイナスの場合

		// マイナス回復を表示
		sDetail.append("HP");
		sDetail.append(std::to_string(-m_nHeal));
		sDetail.append("マイナス");
	}
	else
	{ // 上記以外の場合

		// 回復数値を表示
		sDetail.append(std::to_string(m_nHeal));
		sDetail.append("HPかいふく");
	}

	// アイテム詳細を返す
	return sDetail;
}

//============================================================
//	アイテム使用後の文字列取得処理
//============================================================
std::string CItemHeal::UseEnd() const
{
	CPlayerStatus status = *CSceneGame::GetPlayer()->GetStatus();	// ステータス情報
	if (!m_bUseEnd)
	{ // 表示しない場合

		return "";
	}
	if (m_nHeal >= status.GetMaxHP())
	{ // HP上限以上の場合

		return " ＊ HPが　まんタンになった。";
	}
	else if (status.GetHP() + m_nHeal >= status.GetCurBaseMaxHP())
	{ // HPが満タンの場合

		return " ＊ HPが　まんたんに　なった。";
	}
	else if (m_nHeal < 0)
	{ // マイナスの場合

		return " ＊ HPが　" + std::to_string(-m_nHeal) + "へった。";
	}

	return " ＊ HPが　" + std::to_string(m_nHeal) + "かいふくした！";
}

//============================================================
//	種類ごとのセットアップ処理
//============================================================
HRESULT CItemHeal::LoadSetup(std::ifstream* pFile, std::string& rString)
{
	// ファイルストリームが未設定の場合抜ける
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	std::string str;	// 読込文字列
	if (rString == "HEAL")
	{
		*pFile >> str;		// ＝を読込
		*pFile >> m_nHeal;	// 回復量を読込
	}
	else if (rString == "USE_END")
	{
		*pFile >> str;	// ＝を読込
		*pFile >> str;	// 使用後の文字表示フラグを読込

		// 使用後の文字表示フラグに変換
		if		(str == "FALSE") { m_bUseEnd = false; }	// false
		else if	(str == "TRUE")	 { m_bUseEnd = true; }	// true
		else					 { return E_FAIL; }		// エラー
	}

	return S_OK;
}