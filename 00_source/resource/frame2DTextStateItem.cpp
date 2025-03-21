//============================================================
//
//	アイテムテキスト状態処理 [frame2DTextStateItem.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateItem.h"
#include "frame2DModuleText.h"
#include "frame2DTextBuffer.h"
#include "manager.h"
#include "item.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	namespace cmd
	{
		namespace name
		{
			const std::string KEY = "/name";	// 文字列を名前に置き換えるコマンド
			const size_t LENGTH = KEY.length();	// コマンド文字列の長さ
		}
	}
}

//************************************************************
//	子クラス [CFrame2DTextStateItem] のメンバ関数
//************************************************************
//============================================================
//	移譲コンストラクタ (デフォルト)
//============================================================
CFrame2DTextStateItem::CFrame2DTextStateItem() : CFrame2DTextStateItem(VEC3_ZERO)
{

}

//============================================================
//	コンストラクタ (配置指定)
//============================================================
CFrame2DTextStateItem::CFrame2DTextStateItem(const VECTOR3& rOffset) : CFrame2DTextStateText(rOffset)
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextStateItem::~CFrame2DTextStateItem()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFrame2DTextStateItem::Init()
{
	// 親クラスの初期化
	if (FAILED(CFrame2DTextStateText::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 相対位置の設定
	CFrame2DTextStateItem::SetPositionRelative();	// 自身の相対位置

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrame2DTextStateItem::Uninit()
{
	// 親クラスの終了
	CFrame2DTextStateText::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CFrame2DTextStateItem::Update(const float fDeltaTime)
{
	// 親クラスの更新
	CFrame2DTextStateText::Update(fDeltaTime);
}

//============================================================
//	テキスト情報保存バッファの割当処理
//============================================================
void CFrame2DTextStateItem::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// アイテムテキスト保存バッファに変換できない場合抜ける
	CFrame2DTextBufferItem* pBuffItem = pBuffer->GetBufferItem();
	if (pBuffItem == nullptr) { assert(false); return; }

	// テキストパスからアイテム情報を検索
	CItem* pItem = GET_MANAGER->GetItem();
	const CItemData& rItemData = pItem->GetInfo(pBuffItem->m_sPath);

	// 次テキストの検索キーを割当
	SetNextTextKey(pBuffItem->m_sNextTextKey);

	// テキスト情報を割当
	int nNumStr = (int)pBuffItem->m_text.size();	// 文字列数
	for (int i = 0; i < nNumStr; i++)
	{ // 文字列数分繰り返す

		// 文字列内のコマンドを置換
		ReplaceCommand(&pBuffItem->m_text[i], rItemData);

		// 文字列を最後尾に追加
		PushBackString(pBuffItem->m_text[i]);
	}

	// 文字送りを開始する
	SetTextEnableScroll(true);

	// 親クラスのテキスト情報保存バッファの割当
	CFrame2DTextState::BindTextBuffer(pBuffer);
}

//============================================================
//	文字列内のコマンドの置換処理
//============================================================
void CFrame2DTextStateItem::ReplaceCommand(std::string* pStr, const CItemData& rItem)
{
	// 名前変換コマンドの全変換
	size_t idxName = 0;	// 検索結果インデックス
	while (true)
	{
		// コマンドの検索
		idxName = pStr->find(cmd::name::KEY, idxName);

		// コマンドが存在しない場合抜ける
		if (idxName == std::string::npos) { break; }

		// コマンドをアイテム名に変換
		pStr->replace(idxName, cmd::name::LENGTH, rItem.GetName());
	}
}
