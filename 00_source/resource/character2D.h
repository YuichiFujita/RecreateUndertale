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

	// アニメーション構造体
	struct SAnim
	{
		// コンストラクタ
		SAnim() :
			ptrnTexture	(GRID2_ZERO),	// テクスチャ分割数
			sizeChara	(VEC3_ZERO)		// キャラクター大きさ
		{
			sPassTexture.clear();	// テクスチャパスをクリア
		}

		// メンバ変数
		std::string sPassTexture;	// テクスチャパス
		POSGRID2 ptrnTexture;		// テクスチャ分割数
		D3DXVECTOR3 sizeChara;		// キャラクター大きさ
		float fNextTime;			// パターン変更時間
	};

	// アニメーション情報構造体
	struct SAnimInfo
	{
		// コンストラクタ
		SAnimInfo()
		{
			vecAnim.clear();	// アニメーション情報をクリア
		}

		// メンバ関数
		int GetNumAnim(void) { return vecAnim.size(); }	// アニメーション情報の総数取得

		// メンバ変数
		std::vector<SAnim> vecAnim;	// アニメーション情報
	};

	// キャラクター情報構造体
	struct SCharaData
	{
		// コンストラクタ
		SCharaData() {}

		// メンバ変数
		CMotion2D::SInfo infoMotion;	// モーション情報
		SAnimInfo infoAnim;				// アニメーション情報
	};

	// メンバ関数
	HRESULT Init(void);		// キャラクター初期化
	void Uninit(void);		// キャラクター終了
	HRESULT LoadAll(void);	// キャラクター全読込
	SCharaData Regist(const char *pCharaPass);	// キャラクター登録

	// 静的メンバ関数
	static CCharacter2D *Create(void);	// 生成
	static void Release(CCharacter2D *&prCharacter2D);	// 破棄

private:
	// メンバ関数
	HRESULT SearchFolderAll(std::string sFolderPath);	// フォルダ全検索

	// メンバ関数
	HRESULT LoadSetup(SCharaData *pInfoChara, const char *pCharaPass);			// キャラクター情報セットアップ
	HRESULT LoadMotionSetup(SCharaData *pInfoChara, const char *pMotionPass);	// モーション情報セットアップ

	// メンバ変数
	std::map<std::string, SCharaData> m_mapCharacter;	// キャラクター2D連想配列
};

#endif	// _CHARACTER2D_H_
