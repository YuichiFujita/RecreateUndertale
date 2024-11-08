//============================================================
//
//	アイテム処理 [item.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "item.h"
#include "itemNone.h"
#include "itemHeal.h"
#include "manager.h"
#include "renderer.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* LOAD_TXT = "data\\TXT\\item.txt";	// アイテムテキスト相対パス
	const std::string CMD_NAME = "/name";	// 文字列を名前に置き換えるコマンド
}

//************************************************************
//	親クラス [CItemData] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CItemData::CItemData() :
	m_sName		(""),	// アイテム名
	m_vecUse	({}),	// 使用テキスト
	m_vecInfo	({}),	// 情報テキスト
	m_vecDrop	({})	// 破棄テキスト
{

}

//============================================================
//	デストラクタ
//============================================================
CItemData::~CItemData()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CItemData::Init()
{
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CItemData::Uninit()
{
	// 自身の破棄
	delete this;
}

//============================================================
//	アイテム詳細の文字列取得処理
//============================================================
std::string CItemData::Detail() const
{
	std::string sDetail;		// アイテム詳細
	sDetail.append(" ＊ ");		// 開始アスタリスクを追加
	sDetail.append(m_sName);	// アイテム名を追加
	sDetail.append(" - ");		// ハイフンを追加

	// アイテム詳細を返す
	return sDetail;
}

//============================================================
//	アイテム使用後の文字列取得処理
//============================================================
std::string CItemData::UseEnd() const
{
	// 空の文字列を返す
	return "";
}

//============================================================
//	生成処理
//============================================================
CItemData* CItemData::Create(const EType type)
{
	// アイテム情報の生成
	CItemData* pItemData = nullptr;	// アイテム情報
	switch (type)
	{ // 種類ごとの処理
	case TYPE_NONE:
		pItemData = new CItemNone;
		break;

	case TYPE_HEAL:
		pItemData = new CItemHeal;
		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	if (pItemData == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// アイテム情報の初期化
		if (FAILED(pItemData->Init()))
		{ // 初期化に失敗した場合

			// アイテム情報の破棄
			SAFE_DELETE(pItemData);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pItemData;
	}
}

//============================================================
//	テキストの初期化処理
//============================================================
void CItemData::InitText()
{
	// 使用テキストの初期化
	m_vecUse.clear();
	m_vecUse.emplace_back();
	m_vecUse[0].push_back(" ＊ エラーメッセージ");

	// 情報テキストの初期化
	m_vecInfo.clear();
	m_vecInfo.emplace_back();
	m_vecInfo[0].push_back(" ＊ エラーメッセージ");

	// 破棄テキストの初期化
	m_vecDrop.clear();
	m_vecDrop.emplace_back();
	m_vecDrop[0].push_back(" ＊ ");
	m_vecDrop[0][0].append(m_sName);
	m_vecDrop[0][0].append("を　すてた");
}

//************************************************************
//	親クラス [CItem] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CItem::CItem()
{
	// アイテム動的配列をクリア
	m_vecItemData.clear();
}

//============================================================
//	デストラクタ
//============================================================
CItem::~CItem()
{

}

//============================================================
//	アイテム初期化処理
//============================================================
HRESULT CItem::Init()
{
	// アイテム動的配列を初期化
	m_vecItemData.clear();

	return S_OK;
}

//============================================================
//	アイテム終了処理
//============================================================
void CItem::Uninit()
{
	for (auto& rVec : m_vecItemData)
	{ // 要素数分繰り返す

		// アイテム情報の終了
		SAFE_UNINIT(rVec);
	}

	// アイテム動的配列をクリア
	m_vecItemData.clear();
}

//============================================================
//	アイテム全読込処理
//============================================================
HRESULT CItem::LoadAll()
{
	// アイテム情報のセットアップ
	if (FAILED(LoadSetup()))
	{ // セットアップに失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	アイテム情報の取得処理
//============================================================
const CItemData& CItem::GetInfo(const int nIdx)
{
	int nArray = (int)m_vecItemData.size();	// 配列要素数
	if (nIdx > NONE_IDX && nIdx < nArray)
	{ // アイテムがある場合

		// 引数のアイテム情報を返す
		return *m_vecItemData[nIdx];
	}

	// 空のアイテム情報を返す
	assert(false);
	return *m_vecItemData[0];
}

//============================================================
//	生成処理
//============================================================
CItem* CItem::Create()
{
	// アイテムの生成
	CItem* pItem = new CItem;
	if (pItem == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// アイテムの初期化
		if (FAILED(pItem->Init()))
		{ // アイテム初期化に失敗した場合

			// アイテムの破棄
			SAFE_DELETE(pItem);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pItem;
	}
}

//============================================================
//	破棄処理
//============================================================
void CItem::Release(CItem*& prItem)
{
	// アイテムの終了
	assert(prItem != nullptr);
	prItem->Uninit();

	// メモリ開放
	SAFE_DELETE(prItem);
}

//============================================================
//	アイテム情報のセットアップ処理
//============================================================
HRESULT CItem::LoadSetup()
{
	int nIdx = 0;			// アイテムインデックス
	int nType = NONE_IDX;	// アイテム種類

	// ファイルを開く
	std::ifstream file(LOAD_TXT);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "アイテムセットアップの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ファイルを読込
	std::string str;	// 読込文字列
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
		else if (str == "ITEMSET")
		{
			// 空の要素を最後尾に追加
			m_vecItemData.emplace_back();

			do { // END_ITEMSETを読み込むまでループ

				// 文字列を読み込む
				file >> str;

				if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
				else if (str == "TYPE")
				{
					file >> str;	// ＝を読込
					file >> nType;	// アイテム種類を読込

					// 空のアイテムデータを生成
					m_vecItemData[nIdx] = CItemData::Create((CItemData::EType)nType);
					if (m_vecItemData[nIdx] == nullptr)
					{ // 生成に失敗した場合

						assert(false);
						return E_FAIL;
					}
				}
				else if (str == "NAME")
				{
					file >> str;	// ＝を読込
					file >> str;	// アイテム名を読込

					// アイテム名を保存
					m_vecItemData[nIdx]->SetName(str.c_str());

					// テキストの初期化
					m_vecItemData[nIdx]->InitText();
				}
				else if (str == "USE")
				{
					// 使用テキスト情報のセットアップ
					m_vecItemData[nIdx]->SetUse(LoadText(file, "END_USE", *m_vecItemData[nIdx]));
				}
				else if (str == "INFO")
				{
					// 情報テキスト情報のセットアップ
					m_vecItemData[nIdx]->SetInfo(LoadText(file, "END_INFO", *m_vecItemData[nIdx]));
				}
				else if (str == "DROP")
				{
					// 破棄テキスト情報のセットアップ
					m_vecItemData[nIdx]->SetDrop(LoadText(file, "END_DROP", *m_vecItemData[nIdx]));
				}
				else if (m_vecItemData[nIdx] != nullptr)
				{
					// 種類ごとの情報読込
					if (FAILED(m_vecItemData[nIdx]->LoadSetup(&file, str)))
					{ // 読込に失敗した場合

						assert(false);
						return E_FAIL;
					}
				}
			} while (str != "END_ITEMSET");	// END_ITEMSETを読み込むまでループ

			// アイテムインデックスを進める
			nIdx++;
		}
	}

	// ファイルを閉じる
	file.close();

	return S_OK;
}

//============================================================
//	テキスト情報のセットアップ処理
//============================================================
ATextBox CItem::LoadText(std::ifstream& rFile, const char* pEndStr, const CItemData& rItem)
{
	ATextBox text = {};	// 読込テキスト情報
	int nBoxIdx = 0;	// テキストボックスインデックス

	// ファイルを読込
	std::string str;	// 読込文字列
	do { // 終了文字列を読み込むまでループ

		// 文字列を読み込む
		rFile >> str;

		if (str.front() == '#') { std::getline(rFile, str); }	// コメントアウト
		else if (str == "TEXT")
		{
			// 空の要素を最後尾に追加
			text.emplace_back();

			do { // END_TEXTを読み込むまでループ

				// 文字列を読み込む
				rFile >> str;

				if (str.front() == '#') { std::getline(rFile, str); }	// コメントアウト
				else if (str == "STR")
				{
					rFile >> str;					// ＝を読込
					rFile.seekg(1, std::ios::cur);	// 読込位置を空白分ずらす
					std::getline(rFile, str);		// 一行全て読み込む

					// 文字列内のコマンドを置換
					ReplaceCommand(&str, rItem);

					// 文字列を最後尾に追加
					text[nBoxIdx].push_back(str);
				}
			} while (str != "END_TEXT");	// END_TEXTを読み込むまでループ

			// テキストボックスインデックスを進める
			nBoxIdx++;
		}
	} while (str != pEndStr);	// 終了文字列を読み込むまでループ

	// 読み込んだテキストを返す
	return text;
}

//============================================================
//	文字列内のコマンドの置換処理
//============================================================
void CItem::ReplaceCommand(std::string* pStr, const CItemData& rItem)
{
	// 名前変換コマンドの検索
	size_t idxName = pStr->find(CMD_NAME);
	if (idxName != std::string::npos)
	{ // コマンドが存在した場合

		// アイテム名に変換する
		pStr->replace(idxName, CMD_NAME.length(), rItem.GetName());
	}
}
