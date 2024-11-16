//============================================================
//
//	プレイヤーアイテムヘッダー [playerItem.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PLAYER_ITEM_H_
#define _PLAYER_ITEM_H_

//************************************************************
//	構造体定義
//************************************************************
// プレイヤーアイテム構造体
struct SPlayerItem
{
public:
	// 定数
	static constexpr int MAX_ITEM = 8;	// 最大アイテム数

	// デフォルトコンストラクタ
	SPlayerItem() :
		m_vecItemIdx({})	// アイテムインデックス
#if 1	// TODO
	{
		m_vecItemIdx.push_back(0);
		m_vecItemIdx.push_back(1);
		m_vecItemIdx.push_back(2);
		m_vecItemIdx.push_back(3);
		m_vecItemIdx.push_back(4);
		m_vecItemIdx.push_back(5);
	}
#else
	{}
#endif

	// デストラクタ
	~SPlayerItem() {}

	// メンバ関数
	bool PushBackItem(const int nItemIdx);	// アイテム追加
	bool DeleteItem(const int nBagIdx);		// アイテム削除
	int GetItemIdx(const int nBagIdx);		// アイテムインデックス取得
	bool SwapItemIdx(int* pItemIdx, const int nBagIdx);					// アイテムインデックス入替
	inline int GetNumItem() const { return (int)m_vecItemIdx.size(); }	// アイテム数取得

private:
	// メンバ変数
	std::vector<int> m_vecItemIdx;	// アイテムインデックス
};

#endif	// _PLAYER_ITEM_H_
