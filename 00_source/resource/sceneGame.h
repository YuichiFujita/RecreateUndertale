//============================================================
//
//	ゲーム画面ヘッダー [sceneGame.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "scene.h"

//************************************************************
//	前方宣言
//************************************************************
class CGameManager;	// ゲームマネージャークラス
class CPause;		// ポーズクラス
class CStage;		// ステージクラス
class CPlayer;		// プレイヤークラス

//************************************************************
//	クラス定義
//************************************************************
// ゲーム画面クラス
class CSceneGame : public CScene
{
public:
	// コンストラクタ
	explicit CSceneGame(const EMode mode);

	// デストラクタ
	~CSceneGame() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

	// 静的メンバ関数
	static CGameManager* GetGameManager();	// ゲームマネージャー取得
	static CPause* GetPause();		// ポーズ取得
	static CStage* GetStage();		// ステージ取得
	static CPlayer* GetPlayer();	// プレイヤー取得

private:
	// 静的メンバ変数
	static CGameManager* m_pGameManager;	// ゲームマネージャー
	static CPause* m_pPause;	// ポーズ情報
	static CStage* m_pStage;	// ステージ情報
};

#endif	// _SCENE_GAME_H_
