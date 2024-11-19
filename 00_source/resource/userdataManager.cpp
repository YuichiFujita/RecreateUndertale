//============================================================
//
//	ユーザーデータマネージャー処理 [userdataManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "userdataManager.h"
#include "playerStatus.h"
#include "playerItem.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* FILE0_TXT		= "data\\TXT\\file0.txt";		// 内部データテキスト相対パス
	const char* INIT_STATUS_TXT	= "data\\TXT\\init_status.txt";	// 初期ステータステキスト相対パス
	const char* INIT_ITEM_TXT	= "data\\TXT\\init_item.txt";	// 初期所持アイテムテキスト相対パス
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CUserDataManager* CUserDataManager::m_pInstance = nullptr;	// 自身のインスタンス

//************************************************************
//	親クラス [CUserDataManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CUserDataManager::CUserDataManager() :
	m_nRoom		(0),	// 部屋番号
	m_nFun		(0),	// FUN値
	m_fPlayTime	(0.0f)	// 総プレイ時間
{

}

//============================================================
//	デストラクタ
//============================================================
CUserDataManager::~CUserDataManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CUserDataManager::Init()
{
	// メンバ変数を初期化
	m_nRoom		= 0;	// 部屋番号
	m_nFun		= 0;	// FUN値
	m_fPlayTime	= 0.0f;	// 総プレイ時間

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CUserDataManager::Uninit()
{

}

//============================================================
//	更新処理
//============================================================
void CUserDataManager::Update(const float fDeltaTime)
{
	// 総プレイ時間を加算
	m_fPlayTime += fDeltaTime;
}

//============================================================
//	プレイヤーステータスの初期化処理
//============================================================
HRESULT CUserDataManager::InitPlayerStatus(CPlayerStatus* pStatus)
{
	// プレイヤーステータスの読込
	if (FAILED(LoadPlayerStatus(pStatus, INIT_STATUS_TXT)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	プレイヤーステータスの読込処理
//============================================================
HRESULT CUserDataManager::LoadPlayerStatus(CPlayerStatus* pStatus)
{
	// プレイヤーステータスの読込
	if (FAILED(LoadPlayerStatus(pStatus, FILE0_TXT)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	プレイヤー所持アイテムの初期化処理
//============================================================
HRESULT CUserDataManager::InitPlayerItem(CPlayerItem* pItem)
{
	// プレイヤー所持アイテムの読込
	if (FAILED(LoadPlayerItem(pItem, INIT_ITEM_TXT)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	プレイヤー所持アイテムの読込処理
//============================================================
HRESULT CUserDataManager::LoadPlayerItem(CPlayerItem* pItem)
{
	// プレイヤー所持アイテムの読込
	if (FAILED(LoadPlayerItem(pItem, FILE0_TXT)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	ユーザーデータの読込処理
//============================================================
HRESULT CUserDataManager::LoadUserData()
{
	// ファイルを開く
	std::ifstream file(FILE0_TXT);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "ユーザーデータの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ファイルを読込
	std::string str;	// 読込文字列
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
		else if (str == "USERSET")
		{
			do { // END_USERSETを読み込むまでループ

				// 文字列を読み込む
				file >> str;

				if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
				else if (str == "ROOM")
				{
					file >> str;		// ＝を読込
					file >> m_nRoom;	// 部屋番号を読込
				}
				else if (str == "FUN")
				{
					file >> str;	// ＝を読込
					file >> m_nFun;	// FUN値を読込
				}
				else if (str == "PLAYTIME")
				{
					file >> str;			// ＝を読込
					file >> m_fPlayTime;	// 総プレイ時間を読込
				}
			} while (str != "END_USERSET");	// END_USERSETを読み込むまでループ
		}
	}

	// ファイルを閉じる
	file.close();

	return S_OK;
}

//============================================================
//	インスタンス生成処理
//============================================================
CUserDataManager* CUserDataManager::Create()
{
	// インスタンス生成済み
	assert(m_pInstance == nullptr);

	// ユーザーデータマネージャーの生成
	m_pInstance = new CUserDataManager;
	if (m_pInstance == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// ユーザーデータマネージャーの初期化
		if (FAILED(m_pInstance->Init()))
		{ // 初期化に失敗した場合

			// ユーザーデータマネージャーの破棄
			SAFE_DELETE(m_pInstance);
			return nullptr;
		}

		// 確保したアドレスを返す
		return m_pInstance;
	}
}

//============================================================
//	インスタンス取得処理
//============================================================
CUserDataManager* CUserDataManager::GetInstance()
{
	// インスタンス未生成
	assert(m_pInstance != nullptr);

	// 自身のインスタンスを返す
	return m_pInstance;
}

//============================================================
//	インスタンス破棄処理
//============================================================
void CUserDataManager::Release()
{
	// ユーザーデータマネージャーの終了
	assert(m_pInstance != nullptr);
	m_pInstance->Uninit();

	// メモリ開放
	SAFE_DELETE(m_pInstance);
}

//============================================================
//	プレイヤーステータスの読込処理 (パス指定)
//============================================================
HRESULT CUserDataManager::LoadPlayerStatus(CPlayerStatus* pStatus, const char* pFilePath)
{
	// ファイルを開く
	std::ifstream file(pFilePath);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "プレイヤーステータスの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ファイルを読込
	std::string str;	// 読込文字列
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
		else if (str == "STATUSSET")
		{
			do { // END_STATUSSETを読み込むまでループ

				// 文字列を読み込む
				file >> str;

				if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
				else if (str == "NAME")
				{
					file >> str;	// ＝を読込
					file >> str;	// プレイヤー名を読込
					pStatus->SetName(str);
				}
				else if (str == "LOVE")
				{
					int nLove;
					file >> str;	// ＝を読込
					file >> nLove;	// レベルを読込
					pStatus->SetLove(nLove);
				}
				else if (str == "HP")
				{
					int nHP;
					file >> str;	// ＝を読込
					file >> nHP;	// 体力を読込
					pStatus->SetHP(nHP);
				}
				else if (str == "MAX_HP")
				{
					int nMaxHP;
					file >> str;	// ＝を読込
					file >> nMaxHP;	// 最大体力を読込
					pStatus->SetMaxHP(nMaxHP);
				}
				else if (str == "EXP")
				{
					int nExp;
					file >> str;	// ＝を読込
					file >> nExp;	// 経験値を読込
					pStatus->SetExp(nExp);
				}
				else if (str == "WPN_ITEMIDX")
				{
					int nItemIdx;
					file >> str;		// ＝を読込
					file >> nItemIdx;	// 武器アイテムインデックスを読込
					pStatus->SetWpnItemIdx(nItemIdx);
				}
				else if (str == "AMR_ITEMIDX")
				{
					int nItemIdx;
					file >> str;		// ＝を読込
					file >> nItemIdx;	// 防具アイテムインデックスを読込
					pStatus->SetAmrItemIdx(nItemIdx);
				}
				else if (str == "NUM_GOLD")
				{
					int nNumGold;
					file >> str;		// ＝を読込
					file >> nNumGold;	// 所持金を読込
					pStatus->SetNumGold(nNumGold);
				}
				else if (str == "NUM_KILL")
				{
					int nNumKill;
					file >> str;		// ＝を読込
					file >> nNumKill;	// 殺害数を読込
					pStatus->SetNumKill(nNumKill);
				}
			} while (str != "END_STATUSSET");	// END_STATUSSETを読み込むまでループ
		}
	}

	// ファイルを閉じる
	file.close();

	return S_OK;
}

//============================================================
//	プレイヤー所持アイテムの読込処理 (パス指定)
//============================================================
HRESULT CUserDataManager::LoadPlayerItem(CPlayerItem* pItem, const char* pFilePath)
{
	// ファイルを開く
	std::ifstream file(pFilePath);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "プレイヤー所持アイテムの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ファイルを読込
	std::string str;	// 読込文字列
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
		else if (str == "ITEMSET")
		{
			do { // END_ITEMSETを読み込むまでループ

				// 文字列を読み込む
				file >> str;

				if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
				else if (str == "ITEMIDX")
				{
					int nItemIdx;
					file >> str;		// ＝を読込
					file >> nItemIdx;	// アイテムインデックスを読込

					// アイテムインデックスを最後尾に追加
					pItem->PushBackItem(nItemIdx);
				}
			} while (str != "END_ITEMSET");	// END_ITEMSETを読み込むまでループ
		}
	}

	// ファイルを閉じる
	file.close();

	return S_OK;
}
