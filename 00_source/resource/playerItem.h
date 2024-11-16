//============================================================
//
//	プレイヤー所持アイテムヘッダー [playerItem.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PLAYER_ITEM_H_
#define _PLAYER_ITEM_H_

//************************************************************
//	クラス定義
//************************************************************
// プレイヤー所持アイテムクラス
struct CPlayerItem
{
public:
	// 定数
	static constexpr int MAX_ITEM = 8;	// 最大アイテム数

	// コンストラクタ
	CPlayerItem();

	// デストラクタ
	~CPlayerItem();

	// メンバ関数
	void PushBackItem(const int nItemIdx);	// アイテム追加
	void DeleteItem(const int nBagIdx);		// アイテム削除
	int GetItemIdx(const int nBagIdx);		// アイテムインデックス取得
	void SetItemIdx(const int nBagIdx, const int nItemIdx);				// アイテムインデックス設定
	inline int GetNumItem() const { return (int)m_vecItemIdx.size(); }	// アイテム数取得

private:
	// メンバ変数
	std::vector<int> m_vecItemIdx;	// アイテムインデックス
};

#endif	// _PLAYER_ITEM_H_
