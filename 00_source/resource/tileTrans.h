//============================================================
//
//	遷移タイルヘッダー [tileTrans.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _TILE_TRANS_H_
#define _TILE_TRANS_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object3D.h"

//************************************************************
//	前方宣言
//************************************************************
class CObjectChara2D;	// オブジェクトキャラクター2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// 遷移タイルクラス
class CTileTrans : public CObject3D
{
public:
	// コンストラクタ
	explicit CTileTrans(const char* pNextPath);

	// デストラクタ
	~CTileTrans();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CTileTrans* Create(const char* pNextPath, const VECTOR3& rPos);	// 生成
	static CListManager<CTileTrans>* GetList(void);	// リスト取得

	static void CollisionTile	// 遷移タイルとの当たり判定
	( // 引数
		const VECTOR3& rPos,			// 位置
		const VECTOR3& rRot,			// 向き
		const CObjectChara2D* pChara2D	// キャラクター2D情報
	);
	static void CollisionTile	// 遷移タイルとの当たり判定
	( // 引数
		const VECTOR3& rPos,		// 位置
		const VECTOR3& rSizeUp,		// 大きさ (右/上/後)
		const VECTOR3& rSizeDown	// 大きさ (左/下/前)
	);

private:
	// 静的メンバ変数
	static CListManager<CTileTrans>* m_pList;	// オブジェクトリスト

	// メンバ変数
	CListManager<CTileTrans>::AIterator m_iterator;	// イテレーター
	const std::string m_sNextStagePath;	// 遷移先ステージパス
};

#endif	// _TILE_TRANS_H_
