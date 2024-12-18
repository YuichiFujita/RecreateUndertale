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
	explicit CTileSpawn(const char* pPrevPath);

	// デストラクタ
	~CTileSpawn();

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CTileSpawn* Create(const char* pPrevPath, const VECTOR3& rPos);	// 生成

private:
	// メンバ変数
	const std::string m_sPrevStagePath;	// 遷移元ステージパス
};

#endif	// _TILE_SPAWN_H_
