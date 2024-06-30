//============================================================
//
//	キャラクター2Dヘッダー [character2D.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _CHARACTER2D_H_
#define _CHARACTER2D_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "motion2D.h"

//************************************************************
//	クラス定義
//************************************************************
// キャラクター2Dクラス
class CCharacter2D
{
public:
	// コンストラクタ
	CCharacter2D();

	// デストラクタ
	~CCharacter2D();

	// モーション情報型エイリアス定義
	using AMotion = CMotion2D::SInfo;

	// メンバ関数
	HRESULT Init(void);		// キャラクター初期化
	void Uninit(void);		// キャラクター終了
	HRESULT LoadAll(void);	// キャラクター全読込
	AMotion Regist(const char *pCharaPass);	// キャラクター登録

	// 静的メンバ関数
	static CCharacter2D *Create(void);	// 生成
	static void Release(CCharacter2D *&prCharacter2D);	// 破棄

private:
	// メンバ関数
	HRESULT SearchFolderAll(std::string sFolderPath);	// フォルダ全検索

	// メンバ関数
	HRESULT LoadSetup(AMotion *pInfoChara, const char *pCharaPass);		// キャラクター情報セットアップ
	HRESULT LoadMotionSetup(AMotion *pInfoChara, const char *pMotionPass);	// モーション情報セットアップ

	// メンバ変数
	std::map<std::string, AMotion> m_mapCharacter;	// キャラクター2D連想配列
};

#endif	// _CHARACTER2D_H_
