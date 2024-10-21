//============================================================
//
//	マップタイルヘッダー [tileMap.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _TILE_MAP_H_
#define _TILE_MAP_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object3D.h"

//************************************************************
//	クラス定義
//************************************************************
// マップタイルクラス
class CTileMap : public CObject3D
{
public:
	// 種類列挙
	enum EType
	{
		TYPE_NONE = 0,		// テクスチャ無し
		TYPE_FALL_POINT,	// 初期落下地点
		TYPE_RUINS_GATE,	// ルインズ入口前
		TYPE_RUINS_STAIRS,	// ルインズ大階段
		TYPE_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CTileMap();

	// デストラクタ
	~CTileMap();

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CTileMap* Create(const EType type, const VECTOR3& rPos);	// 生成

	// メンバ関数
	void SetType(const EType type);					// 種類設定
	inline EType GetType() const { return m_type; }	// 種類取得

private:
	// メンバ変数
	EType m_type;	// 種類
};

#endif	// _TILE_MAP_H_
