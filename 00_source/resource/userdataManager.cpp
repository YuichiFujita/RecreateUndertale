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
#include "manager.h"
#include "playerStatus.h"
#include "playerItem.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* FILE0_TXT		= "data\\TXT\\file0.txt";			// 内部データテキスト相対パス
	const char* INIT_STATUS_TXT	= "data\\TXT\\init_status.txt";		// ステータス初期化テキスト相対パス
	const char* INIT_ITEM_TXT	= "data\\TXT\\init_item.txt";		// 所持アイテム初期化テキスト相対パス
	const char* INIT_USER_TXT	= "data\\TXT\\init_userdata.txt";	// ユーザーデータ初期化テキスト相対パス
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
	if (GET_MANAGER->GetMode() == CScene::MODE_GAME)
	{ // ゲーム画面の場合

		// 総プレイ時間を加算
		m_fPlayTime += fDeltaTime;
	}
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
//	ユーザーデータの初期化処理
//============================================================
HRESULT CUserDataManager::InitUserData()
{
	// ユーザーデータの読込
	if (FAILED(LoadUserData(INIT_USER_TXT)))
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
	// ユーザーデータの読込
	if (FAILED(LoadUserData(FILE0_TXT)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	内部データの初期化処理
//============================================================
HRESULT CUserDataManager::InitAllData
(
	CPlayerStatus* pStatus,	// プレイヤーステータス情報
	CPlayerItem* pItem		// プレイヤー所持アイテム情報
)
{
	// ステータスの初期化
	if (FAILED(InitPlayerStatus(pStatus)))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 所持アイテムの初期化
	if (FAILED(InitPlayerItem(pItem)))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ユーザーデータの初期化
	if (FAILED(InitUserData()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

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

//============================================================
//	ユーザーデータの読込処理
//============================================================
HRESULT CUserDataManager::LoadUserData(const char* pFilePath)
{
	// ファイルを開く
	std::ifstream file(pFilePath);	// ファイルストリーム
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
//	内部データの保存処理
//============================================================
HRESULT CUserDataManager::SaveAllData
(
	CPlayerStatus* pStatus,	// プレイヤーステータス情報
	CPlayerItem* pItem		// プレイヤー所持アイテム情報
)
{
	// ファイルを開く
	std::ofstream file(FILE0_TXT);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "内部データの書き出しに失敗！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 小数点の書き出し桁数を指定
	file << std::fixed << std::setprecision(4);

	// 見出しの書き出し
	file << "#==============================================================================" << std::endl;
	file << "#" << std::endl;
	file << "#	内部データテキスト [file0.txt]" << std::endl;
	file << "#	Author : 藤田 勇一" << std::endl;
	file << "#" << std::endl;
	file << "#==============================================================================" << std::endl;

	// ステータスの書き出し
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "#	ステータス情報" << std::endl;
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "STATUSSET" << std::endl;
	file << "	NAME 		= " << pStatus->GetName()		<< std::endl;
	file << "	LOVE 		= " << pStatus->GetLove()		<< std::endl;
	file << "	HP 			= " << pStatus->GetHP()			<< std::endl;
	file << "	MAX_HP 		= " << pStatus->GetMaxHP()		<< std::endl;
	file << "	EXP			= " << pStatus->GetExp()		<< std::endl;
	file << "	WPN_ITEMIDX	= " << pStatus->GetWpnItemIdx()	<< std::endl;
	file << "	AMR_ITEMIDX	= " << pStatus->GetAmrItemIdx()	<< std::endl;
	file << "	NUM_GOLD	= " << pStatus->GetNumGold()	<< std::endl;
	file << "	NUM_KILL	= " << pStatus->GetNumKill()	<< std::endl;
	file << "END_STATUSSET" << std::endl;
	file << std::endl;

	// 所持アイテムの書き出し
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "#	所持アイテム情報" << std::endl;
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "ITEMSET" << std::endl;
	for (int i = 0; i < pItem->GetNumItem(); i++)
	{ // 所持アイテム数分繰り返す

		file << "	ITEMIDX = " << pItem->GetItemIdx(i) << std::endl;
	}
	file << "END_ITEMSET" << std::endl;
	file << std::endl;

	// アイテムボックスの書き出し
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "#	アイテムボックス情報" << std::endl;
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "ITEMBOXSET" << std::endl;
	// TODO：ここにアイテムボックス内インデックスの書き出し
	file << "END_ITEMBOXSET" << std::endl;
	file << std::endl;

	// ここにユーザーデータの書き出し
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "#	ユーザーデータ情報" << std::endl;
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "USERSET" << std::endl;
	file << "	ROOM	 = " << m_nRoom		<< std::endl;
	file << "	FUN		 = " << m_nFun		<< std::endl;
	file << "	PLAYTIME = " << m_fPlayTime	<< std::endl;
	file << "END_USERSET" << std::endl;

	// ファイルを閉じる
	file.close();

	return S_OK;
}

//============================================================
//	内部データ保存ファイルがあるかの確認処理
//============================================================
bool CUserDataManager::IsCheckSaveData()
{
	// 指定したパスがあるかを返す
	return std::filesystem::exists(FILE0_TXT);
}

//============================================================
//	総プレイ時間文字列の取得処理
//============================================================
std::string CUserDataManager::GetStrPlayTime()
{
	// プレイ時間を分/秒に変換
	const long lLongTime = (DWORD)(m_fPlayTime * 1000.0f);		// 総プレイ整数時間
	const int nSecTime = (int)(lLongTime / 1000) % 60;			// 総プレイ整数秒
	const int nMinTime = (int)(lLongTime / 60000);				// 総プレイ整数分

	// 秒数が一桁の場合はゼロ埋め用文字列を作成
	const std::string sZero = (nSecTime < 10) ? "0" : "";

	// 分/秒を文字列に変換
	const std::string sSec = sZero + std::to_string(nSecTime);	// 総プレイ秒文字列
	const std::string sMin = std::to_string(nMinTime);			// 総プレイ分文字列

	// 総プレイ時間文字列を作成し返す
	return (sMin + ":" + sSec);
}
