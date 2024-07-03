//============================================================
//
//	判定タイルヘッダー [tileColl.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _TILE_COLL_H_
#define _TILE_COLL_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object3D.h"

//************************************************************
//	クラス定義
//************************************************************
// 判定タイルクラス
class CTileColl : public CObject3D
{
public:
	// 種類列挙
	enum EType
	{
		TYPE_BOX = 0,	// 矩形
		TYPE_TRIANGLE,	// 三角
		TYPE_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CTileColl();

	// デストラクタ
	~CTileColl();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CTileColl *Create(const EType type, const D3DXVECTOR3& rPos);	// 生成
	static CListManager<CTileColl> *GetList(void);	// リスト取得
	static bool CollisionTile	// 判定タイルとの当たり判定
	( // 引数
		D3DXVECTOR3& rPos,			// 位置
		const D3DXVECTOR3& rPosOld,	// 過去位置
		const D3DXVECTOR3& rSize	// 大きさ
	);

	// メンバ関数
	void SetType(const EType type);					// 種類設定
	EType GetType(void) const { return m_type; }	// 種類取得

private:
	// 静的メンバ変数
	static CListManager<CTileColl> *m_pList;	// オブジェクトリスト

	// メンバ変数
	CListManager<CTileColl>::AIterator m_iterator;	// イテレーター
	EType m_type;	// 種類
};

#endif	// _TILE_COLL_H_
