﻿//============================================================
//
//	武器アイテム処理 [itemWeapon.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "itemWeapon.h"
#include "sceneGame.h"
#include "player.h"
#include "playerStatus.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{

}

//************************************************************
//	子クラス [CItemWeapon] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CItemWeapon::CItemWeapon()
{

}

//============================================================
//	デストラクタ
//============================================================
CItemWeapon::~CItemWeapon()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CItemWeapon::Init()
{
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
void CItemWeapon::Uninit()
{
	// アイテム情報の終了
	CItemData::Uninit();
}

//============================================================
//	アイテム使用処理
//============================================================
void CItemWeapon::Use(const int nBagIdx) const
{
	CPlayerStatus* pStatus = CSceneGame::GetPlayer()->GetStatus();	// プレイヤーステータス情報

	// 使用した装備に入れ替え
	pStatus->SwapWeaponIdx(nBagIdx);
}

//============================================================
//	アイテム詳細の文字列取得処理
//============================================================
std::string CItemWeapon::Detail() const
{
	// アイテム詳細の取得
	std::string sDetail = CItemData::Detail();

	// 攻撃力上昇量を表示
	sDetail.append("ぶきAT");
	sDetail.append(std::to_string(GetAddAtk()));

	// アイテム詳細を返す
	return sDetail;
}

//============================================================
//	種類ごとのセットアップ処理
//============================================================
HRESULT CItemWeapon::LoadSetup(std::ifstream* pFile, std::string& /*rString*/)
{
	// ファイルストリームが未設定の場合抜ける
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	return S_OK;
}