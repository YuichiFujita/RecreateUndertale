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
#include "itemWeapon.h"
#include "itemArmor.h"
#include "manager.h"
#include "renderer.h"
#include "sceneGame.h"
#include "player.h"
#include "playerItem.h"
#include "frame2DTextBuffer.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	// TODO：今後消える
	const char* LOAD_TXT_OLD = "data\\TXT\\item.txt";	// アイテムテキスト相対パス
	const std::string CMD_NAME = "/name";	// 文字列を名前に置き換えるコマンド

	const char* LOAD_TXT = "data\\ITEM\\info.txt";	// アイテムテキスト相対パス
}

//************************************************************
//	親クラス [CItemData] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CItemData::CItemData() :
	m_sDataPath	(""),	// アイテム情報パス
	m_sName		(""),	// アイテム名
	m_nAddAtk	(0),	// 攻撃力上昇量
	m_nAddDef	(0)		// 防御力上昇量
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
	// メンバ変数を初期化
	m_sDataPath	= "";	// アイテム情報パス
	m_sName		= "";	// アイテム名
	m_nAddAtk	= 0;	// 攻撃力上昇量
	m_nAddDef	= 0;	// 防御力上昇量

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
//	アイテム情報処理
//============================================================
void CItemData::Info(const int /*nBagIdx*/) const
{

}

//============================================================
//	アイテム破棄処理
//============================================================
void CItemData::Drop(const int nBagIdx) const
{
	// 破棄したアイテムの削除
	CPlayerItem* pItemArray = CSceneGame::GetPlayer()->GetItem();	// プレイヤー所持アイテム情報
	pItemArray->DeleteItem(nBagIdx);
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
//	初期の使用テキストバッファ連想配列の生成処理
//============================================================
CFrame2DModuleText::ABuffTextArray CItemData::CreateUseBuffTextArray() const
{
	CFrame2DModuleText::ABuffTextArray mapBuffText;
	CFrame2DTextBufferItem* pBuffItem = new CFrame2DTextBufferItem;

	// アイテム情報パスを保存
	pBuffItem->m_sPath = m_sDataPath;

	// 使用テキストを最後尾に追加
	pBuffItem->m_text.push_back(" ＊ エラーメッセージ");

	// テキストバッファを保存
	mapBuffText.insert(std::make_pair("0", pBuffItem));

	return mapBuffText;
}

//============================================================
//	初期の情報テキストバッファ連想配列の生成処理
//============================================================
CFrame2DModuleText::ABuffTextArray CItemData::CreateInfoBuffTextArray() const
{
	CFrame2DModuleText::ABuffTextArray mapBuffText;
	CFrame2DTextBufferItem* pBuffItem = new CFrame2DTextBufferItem;

	// アイテム情報パスを保存
	pBuffItem->m_sPath = m_sDataPath;

	// 情報テキストを最後尾に追加
	pBuffItem->m_text.push_back(" ＊ エラーメッセージ");

	// テキストバッファを保存
	mapBuffText.insert(std::make_pair("0", pBuffItem));

	return mapBuffText;
}

//============================================================
//	初期の破棄テキストバッファ連想配列の生成処理
//============================================================
CFrame2DModuleText::ABuffTextArray CItemData::CreateDropBuffTextArray() const
{
	CFrame2DModuleText::ABuffTextArray mapBuffText;
	CFrame2DTextBufferItem* pBuffItem = new CFrame2DTextBufferItem;

	// アイテム情報パスを保存
	pBuffItem->m_sPath = m_sDataPath;

	// 破棄テキストの作成
	std::string sText = " ＊ ";
	sText.append(m_sName);
	sText.append("を　すてた");

	// 破棄テキストを最後尾に追加
	pBuffItem->m_text.push_back(sText);

	// テキストバッファを保存
	mapBuffText.insert(std::make_pair("0", pBuffItem));

	return mapBuffText;
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

	case TYPE_WEAPON:
		pItemData = new CItemWeapon;
		break;

	case TYPE_ARMOR:
		pItemData = new CItemArmor;
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

	// TODO：今後消える
	// 旧アイテム情報のセットアップ
#if 0
	if (FAILED(LoadSetupOld()))
	{ // セットアップに失敗した場合

		assert(false);
		return E_FAIL;
	}
#endif

	return S_OK;
}

//============================================================
//	アイテム情報の取得処理 (インデックス)
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
//	アイテム情報の取得処理 (パス)
//============================================================
const CItemData& CItem::GetInfo(const std::string& rPath)
{
	// 同一アイテムを判定するラムダ関数を作成
	auto funcSamePath = [rPath](CItemData* pItemData)
	{
		// 引数のパスと同一かを判定する
		return pItemData->GetDataPath() == rPath;
	};

	// 同一アイテムの検索
	auto itr = std::find_if(m_vecItemData.begin(), m_vecItemData.end(), funcSamePath);
	if (itr != m_vecItemData.end())
	{ // 同一アイテムが見つかった場合

		// 検索したアイテム情報を返す
		return *(*itr);
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
//	セットアップ処理
//============================================================
HRESULT CItem::LoadSetup()
{
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
		else if (str == "ITEMPATH")
		{
			file >> str;	// ＝を読込
			file >> str;	// アイテム種類を読込

			// アイテム情報の読込
			CItemData* pItemData = LoadDataSetup(str.c_str());
			if (pItemData == nullptr)
			{ // 読込に失敗した場合

				assert(false);
				return E_FAIL;
			}

			// アイテム情報を最後尾に追加
			m_vecItemData.push_back(pItemData);
		}
	}

	// ファイルを閉じる
	file.close();

	return S_OK;
}

//============================================================
//	アイテム情報のセットアップ処理
//============================================================
CItemData* CItem::LoadDataSetup(const char* pDataPath)
{
	CItemData* pItemData = nullptr;	// アイテム情報
	int nAddAtk = 0;		// 攻撃力上昇量
	int nAddDef = 0;		// 防御力上昇量
	int nType = NONE_IDX;	// アイテム種類

	// ファイルを開く
	std::ifstream file(pDataPath);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "アイテム情報セットアップの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return nullptr;
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
				else if (str == "TYPE")
				{
					file >> str;	// ＝を読込
					file >> nType;	// アイテム種類を読込

					// 空のアイテムデータを生成
					assert(pItemData == nullptr);
					pItemData = CItemData::Create((CItemData::EType)nType);
					if (pItemData == nullptr)
					{ // 生成に失敗した場合

						assert(false);
						return nullptr;
					}

					// アイテム情報パスを保存
					pItemData->SetDataPath(pDataPath);
				}
				else if (str == "NAME")
				{
					file >> str;	// ＝を読込
					file >> str;	// アイテム名を読込

					// アイテム名を保存
					pItemData->SetName(str);
				}
				else if (str == "ADD_ATK")
				{
					file >> str;		// ＝を読込
					file >> nAddAtk;	// 攻撃力上昇量を読込

					// 攻撃力上昇量を保存
					pItemData->SetAddAtk(nAddAtk);
				}
				else if (str == "ADD_DEF")
				{
					file >> str;		// ＝を読込
					file >> nAddDef;	// 防御力上昇量を読込

					// 防御力上昇量を保存
					pItemData->SetAddDef(nAddDef);
				}
				else if (pItemData != nullptr)
				{
					// 種類ごとの情報読込
					if (FAILED(pItemData->LoadSetup(&file, str)))
					{ // 読込に失敗した場合

						assert(false);
						return nullptr;
					}
				}
			} while (str != "END_ITEMSET");	// END_ITEMSETを読み込むまでループ
		}
	}

	// ファイルを閉じる
	file.close();

	// 生成したアイテム情報を返す
	return pItemData;
}
