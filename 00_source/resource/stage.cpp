//============================================================
//
//	ステージ処理 [stage.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "stage.h"
#include "manager.h"
#include "texture.h"
#include "collision.h"

#include "tileSpawn.h"
#include "tileTrans.h"

#include "sceneGame.h"
#include "player.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *INIT_PASS = "data\\ROOM\\room004.txt";	// セットアップテキスト相対パス
}

//************************************************************
//	親クラス [CStage] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStage::CStage()
{
	// メンバ変数をクリア
	memset(&m_limit, 0, sizeof(m_limit));	// ステージ範囲
}

//============================================================
//	デストラクタ
//============================================================
CStage::~CStage()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CStage::Init(void)
{
	// メンバ変数を初期化
	memset(&m_limit, 0, sizeof(m_limit));	// ステージ範囲

	// ステージの割当
	if (FAILED(BindStage(INIT_PASS)))
	{ // 読込に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CStage::Uninit(void)
{

}

//============================================================
//	ステージ割当処理
//============================================================
HRESULT CStage::BindStage(const char *pStagePass)
{
	// ファイルを開く
	std::ifstream file(pStagePass);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "ステージセットアップの読み込みに失敗！", "警告！", MB_ICONWARNING);

		// 失敗を返す
		return E_FAIL;
	}

	// ファイルを読込
	std::string str;	// 読込文字列
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#')
		{ // コメントアウトされている場合

			// 一行全て読み込む
			std::getline(file, str);
		}

		// ステージ範囲情報の読込
		else if (FAILED(LoadLimit(&file, str)))
		{ // 読込に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// 出現タイル情報の読込
		else if (FAILED(LoadSpawn(&file, str)))
		{ // 読込に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// 遷移タイル情報の読込
		else if (FAILED(LoadTrans(&file, str)))
		{ // 読込に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}
	}

	// ファイルを閉じる
	file.close();

	// 成功を返す
	return S_OK;
}

//============================================================
//	位置の補正処理
//============================================================
void CStage::LimitPosition(D3DXVECTOR3& rPos, const float fRadius)
{
	// XY平面角柱の内側制限
	collision::InBoxPillarXY
	( // 引数
		rPos,				// 判定位置
		VEC3_ZERO,			// 判定原点位置
		VEC3_ALL(fRadius),	// 判定サイズ(右・上・後)
		VEC3_ALL(fRadius),	// 判定サイズ(左・下・前)
		D3DXVECTOR3(fabsf(m_limit.fRight), fabsf(m_limit.fUp), 0.0f),	// 判定原点サイズ(右・上・後)
		D3DXVECTOR3(fabsf(m_limit.fLeft), fabsf(m_limit.fDown), 0.0f)	// 判定原点サイズ(左・下・前)
	);
}

//============================================================
//	生成処理
//============================================================
CStage *CStage::Create(void)
{
	// ステージの生成
	CStage *pStage = new CStage;
	if (pStage == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// ステージの初期化
		if (FAILED(pStage->Init()))
		{ // 初期化に失敗した場合

			// ステージの破棄
			SAFE_DELETE(pStage);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pStage;
	}
}

//============================================================
//	破棄処理
//============================================================
void CStage::Release(CStage *&prStage)
{
	// ステージの終了
	assert(prStage != nullptr);
	prStage->Uninit();

	// メモリ開放
	SAFE_DELETE(prStage);
}

//============================================================
//	ステージ範囲情報の読込処理
//============================================================
HRESULT CStage::LoadLimit(std::ifstream *pFile, std::string& rString)
{
	// ファイルストリームが未設定の場合抜ける
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// ステージ範囲の設定
	if (rString == "LIMITSET")
	{
		SLimit limit;		// ステージ範囲の代入用
		std::string str;	// 読込文字列

		do { // END_LIMITSETを読み込むまでループ

			// 文字列を読み込む
			*pFile >> str;

			if (str.front() == '#')
			{ // コメントアウトされている場合

				// 一行全て読み込む
				std::getline(*pFile, str);
			}
			else if (str == "UP")
			{
				*pFile >> str;			// ＝を読込
				*pFile >> limit.fUp;	// 上位置を読込
			}
			else if (str == "DOWN")
			{
				*pFile >> str;			// ＝を読込
				*pFile >> limit.fDown;	// 下位置を読込
			}
			else if (str == "LEFT")
			{
				*pFile >> str;			// ＝を読込
				*pFile >> limit.fLeft;	// 左位置を読込
			}
			else if (str == "RIGHT")
			{
				*pFile >> str;			// ＝を読込
				*pFile >> limit.fRight;	// 右位置を読込
			}
		} while (str != "END_LIMITSET");	// END_LIMITSETを読み込むまでループ

		// ステージ範囲の設定
		SetLimit(limit);
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	出現タイル情報の読込処理
//============================================================
HRESULT CStage::LoadSpawn(std::ifstream *pFile, std::string& rString)
{
	// ファイルストリームが未設定の場合抜ける
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// 出現タイルの設定
	if (rString == "SPAWNSET")
	{
		std::string str;	// 読込文字列
		std::string pass;	// 遷移前ルームパス
		D3DXVECTOR3 pos;	// 位置

		do { // END_SPAWNSETを読み込むまでループ

			// 文字列を読み込む
			*pFile >> str;

			if (str.front() == '#')
			{ // コメントアウトされている場合

				// 一行全て読み込む
				std::getline(*pFile, str);
			}
			else if (str == "PREV_ROOMPASS")
			{
				*pFile >> str;		// ＝を読込
				*pFile >> pass;		// 遷移前のルームパスを読込

				// ルームパスを標準化
				useful::StandardizePathPart(&pass);
			}
			else if (str == "POS")
			{
				*pFile >> str;		// ＝を読込
				*pFile >> pos.x;	// 位置Xを読込
				*pFile >> pos.y;	// 位置Yを読込
				*pFile >> pos.z;	// 位置Zを読込
			}
		} while (str != "END_SPAWNSET");	// END_SPAWNSETを読み込むまでループ

		// 出現タイルの生成
		if (CTileSpawn::Create(pass.c_str(), pos) == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		if (INIT_PASS == pass)
		{
			// TODO
			CSceneGame::GetPlayer()->SetVec3Position(pos);
		}
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	遷移タイル情報の読込処理
//============================================================
HRESULT CStage::LoadTrans(std::ifstream *pFile, std::string& rString)
{
	// ファイルストリームが未設定の場合抜ける
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// 遷移タイルの設定
	if (rString == "TRANSSET")
	{
		std::string str;	// 読込文字列
		std::string pass;	// 遷移先ルームパス
		D3DXVECTOR3 pos;	// 位置

		do { // END_TRANSSETを読み込むまでループ

			// 文字列を読み込む
			*pFile >> str;

			if (str.front() == '#')
			{ // コメントアウトされている場合

				// 一行全て読み込む
				std::getline(*pFile, str);
			}
			else if (str == "NEXT_ROOMPASS")
			{
				*pFile >> str;		// ＝を読込
				*pFile >> pass;		// 遷移先のルームパスを読込

				// ルームパスを標準化
				useful::StandardizePathPart(&pass);
			}
			else if (str == "POS")
			{
				*pFile >> str;		// ＝を読込
				*pFile >> pos.x;	// 位置Xを読込
				*pFile >> pos.y;	// 位置Yを読込
				*pFile >> pos.z;	// 位置Zを読込
			}
		} while (str != "END_TRANSSET");	// END_TRANSSETを読み込むまでループ

		// 遷移タイルの生成
		if (CTileTrans::Create(pass.c_str(), pos) == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}