//============================================================
//
//	出現タイルヘッダー [tileSpawn.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _TILE_SPAWN_H_
#define _TILE_SPAWN_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object3D.h"

//************************************************************
//	クラス定義
//************************************************************
// 出現タイルクラス
class CTileSpawn : public CObject3D
{
public:
	// コンストラクタ
	CTileSpawn(const char *pPrevPass);

	// デストラクタ
	~CTileSpawn();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CTileSpawn *Create(const char *pPrevPass, const D3DXVECTOR3& rPos);	// 生成

private:
	// メンバ変数
	const std::string m_sPrevStagePass;	// 遷移元ステージパス
};

#endif	// _TILE_SPAWN_H_
