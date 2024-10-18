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
#include "fade.h"
#include "camera.h"
#include "collision.h"

#include "tileMap.h"
#include "tileColl.h"
#include "tileSpawn.h"
#include "tileTrans.h"

#include "sceneGame.h"
#include "player.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *INIT_PASS = "data\\ROOM\\room004.txt";	// セットアップテキスト相対パス	// TODO：この定数を外部読み込みできるようにしないと
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

	// 割り当てたステージを保存
	m_sNextRoomPath = INIT_PASS;

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
//	遷移先ルームの設定処理
//============================================================
void CStage::SetFadeRoom(const char *pRoomPath)
{
	CFade *pFade = GET_MANAGER->GetFade();	// フェード情報

	// ルームパスの保存
	m_sPrevRoomPath = m_sNextRoomPath;	// 遷移元
	m_sNextRoomPath = pRoomPath;		// 遷移先

	// 遷移先ルームの設定
	pFade->SetRoomFade();
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
//	ステージ割当処理
//============================================================
HRESULT CStage::BindStage(const char *pStagePath)
{
	// ラベルタイルのオブジェクト全破棄
	CObject::ReleaseAll(CObject::LABEL_TILE);

	// TODO：後で消す
	CTileColl::Create(CTileColl::TYPE_TRIANGLE,	D3DXVECTOR3(SIZE_TILE * -2.0f, SIZE_TILE * 2.0f, -1.0f));
	CTileColl::Create(CTileColl::TYPE_BOX,		D3DXVECTOR3(SIZE_TILE *  0.0f, SIZE_TILE * 2.0f, -1.0f));
	CTileColl::Create(CTileColl::TYPE_TRIANGLE,	D3DXVECTOR3(SIZE_TILE *  2.0f, SIZE_TILE * 2.0f, -1.0f));

	// ファイルを開く
	std::ifstream file(pStagePath);	// ファイルストリーム
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

		// マップタイル情報の読込
		else if (FAILED(LoadMap(&file, str)))
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
//	ステージ範囲情報の読込処理
//============================================================
HRESULT CStage::LoadLimit(std::ifstream *pFile, std::string& rString)
{
	// ファイルストリームが未設定の場合抜ける
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// 読込開始位置ではない場合抜ける
	if (rString != "LIMITSET") { return S_OK; }

	// ステージ範囲の設定
	std::string str;	// 読込文字列
	SLimit limit;		// ステージ範囲の代入用
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

	// 成功を返す
	return S_OK;
}

//============================================================
//	マップタイル情報の読込処理
//============================================================
HRESULT CStage::LoadMap(std::ifstream *pFile, std::string& rString)
{
	// ファイルストリームが未設定の場合抜ける
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// 読込開始位置ではない場合抜ける
	if (rString != "MAPSET") { return S_OK; }

	// マップタイルの設定
	std::string str;	// 読込文字列
	do { // END_MAPSETを読み込むまでループ

		// 文字列を読み込む
		*pFile >> str;

		if (str == "MAP")
		{
			D3DXVECTOR3 pos = VEC3_ZERO;	// 位置
			int nType = 0;					// 種類
			do { // END_MAPを読み込むまでループ

				// 文字列を読み込む
				*pFile >> str;

				if (str.front() == '#')
				{ // コメントアウトされている場合

					// 一行全て読み込む
					std::getline(*pFile, str);
				}
				else if (str == "TYPE")
				{
					*pFile >> str;		// ＝を読込
					*pFile >> nType;	// 種類を読込
				}
				else if (str == "POS")
				{
					*pFile >> str;		// ＝を読込
					*pFile >> pos.x;	// 位置Xを読込
					*pFile >> pos.y;	// 位置Yを読込
					*pFile >> pos.z;	// 位置Zを読込
				}
			} while (str != "END_MAP");	// END_MAPを読み込むまでループ

			// マップタイルの生成
			if (CTileMap::Create((CTileMap::EType)nType, pos) == nullptr)
			{ // 生成に失敗した場合

				// 失敗を返す
				assert(false);
				return E_FAIL;
			}
		}
	} while (str != "END_MAPSET");	// END_MAPSETを読み込むまでループ

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

	// 読込開始位置ではない場合抜ける
	if (rString != "SPAWNSET") { return S_OK; }

	// 出現タイルの設定
	std::string str;	// 読込文字列
	do { // END_SPAWNSETを読み込むまでループ

		// 文字列を読み込む
		*pFile >> str;

		if (str == "SPAWN")
		{
			std::string passPrev;			// 遷移元ルームパス
			D3DXVECTOR3 pos = VEC3_ZERO;	// 位置
			CPlayer::EAngle angle = (CPlayer::EAngle)0;	// 角度
			do { // END_SPAWNを読み込むまでループ

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
					*pFile >> passPrev;	// 遷移元のルームパスを読込

					// ルームパスを標準化
					useful::StandardizePathPart(&passPrev);
				}
				else if (str == "POS")
				{
					*pFile >> str;		// ＝を読込
					*pFile >> pos.x;	// 位置Xを読込
					*pFile >> pos.y;	// 位置Yを読込
					*pFile >> pos.z;	// 位置Zを読込
				}
				else if (str == "ANGLE")
				{
					*pFile >> str;	// ＝を読込
					*pFile >> str;	// 角度を読込

					// 読み込んだ角度を保存
					if		(str == "UP")	 { angle = CPlayer::ANGLE_UP; }		// 上
					else if	(str == "DOWN")	 { angle = CPlayer::ANGLE_DOWN; }	// 下
					else if	(str == "LEFT")	 { angle = CPlayer::ANGLE_LEFT; }	// 左
					else if	(str == "RIGHT") { angle = CPlayer::ANGLE_RIGHT; }	// 右
				}
			} while (str != "END_SPAWN");	// END_SPAWNを読み込むまでループ

			// 出現タイルの生成
			if (CTileSpawn::Create(passPrev.c_str(), pos) == nullptr)
			{ // 生成に失敗した場合

				// 失敗を返す
				assert(false);
				return E_FAIL;
			}

			// プレイヤー出現先の設定
			if (passPrev == m_sPrevRoomPath)
			{ // タイルの読込パスとルームの遷移元パスが同じ場合

				// プレイヤーの部屋遷移
				CSceneGame::GetPlayer()->TransRoom(pos, angle);
			}
		}
	} while (str != "END_SPAWNSET");	// END_SPAWNSETを読み込むまでループ

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

	// 読込開始位置ではない場合抜ける
	if (rString != "TRANSSET") { return S_OK; }

	// 遷移タイルの設定
	std::string str;	// 読込文字列
	do { // END_TRANSSETを読み込むまでループ

		// 文字列を読み込む
		*pFile >> str;

		if (str == "TRANS")
		{
			std::string passNext;			// 遷移先ルームパス
			D3DXVECTOR3 pos = VEC3_ZERO;	// 位置
			do { // END_TRANSを読み込むまでループ

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
					*pFile >> passNext;	// 遷移先のルームパスを読込

					// ルームパスを標準化
					useful::StandardizePathPart(&passNext);
				}
				else if (str == "POS")
				{
					*pFile >> str;		// ＝を読込
					*pFile >> pos.x;	// 位置Xを読込
					*pFile >> pos.y;	// 位置Yを読込
					*pFile >> pos.z;	// 位置Zを読込
				}
			} while (str != "END_TRANS");	// END_TRANSを読み込むまでループ

			// 遷移タイルの生成
			if (CTileTrans::Create(passNext.c_str(), pos) == nullptr)
			{ // 生成に失敗した場合

				// 失敗を返す
				assert(false);
				return E_FAIL;
			}
		}
	} while (str != "END_TRANSSET");	// END_TRANSSETを読み込むまでループ

	// 成功を返す
	return S_OK;
}