//============================================================
//
//	マップタイルヘッダー [mapTile.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _MAPTILE_H_
#define _MAPTILE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object3D.h"

//************************************************************
//	クラス定義
//************************************************************
// マップタイルクラス
class CMapTile : public CObject3D
{
public:
	// 種類列挙
	enum EType
	{
		TYPE_NONE = 0,	// テクスチャ無し
		TYPE_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CMapTile();

	// デストラクタ
	~CMapTile();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CMapTile *Create(const EType type, const D3DXVECTOR3& rPos);	// 生成

	// メンバ関数
	void SetType(const EType type);					// 種類設定
	EType GetType(void) const { return m_type; }	// 種類取得

private:
	// メンバ変数
	EType m_type;	// 種類
};

#endif	// _MAPTILE_H_
