//============================================================
//
//	プレイヤーヘッダー [player.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "objectChara2D.h"

//************************************************************
//	前方宣言
//************************************************************
class CPlayerState;	// プレイヤー状態クラス

//************************************************************
//	クラス定義
//************************************************************
// プレイヤークラス
class CPlayer : public CObjectChara2D
{
public:
	// モーション列挙
	enum EMotion
	{
		MOTION_IDOL_U = 0,	// 上待機モーション
		MOTION_IDOL_D,		// 下待機モーション
		MOTION_IDOL_L,		// 左待機モーション
		MOTION_IDOL_R,		// 右待機モーション
		MOTION_MOVE_U,		// 上移動モーション
		MOTION_MOVE_D,		// 下移動モーション
		MOTION_MOVE_L,		// 左移動モーション
		MOTION_MOVE_R,		// 右移動モーション
		MOTION_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CPlayer();

	// デストラクタ
	~CPlayer();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画
	HRESULT ChangeState(CPlayerState *pState);		// 状態変更

	// 静的メンバ関数
	static CPlayer *Create(const D3DXVECTOR3& rPos);	// 生成
	static CListManager<CPlayer> *GetList(void);		// リスト取得

private:
	// メンバ関数
	void UpdateOldPosition(void);	// 過去位置の更新
	void UpdateMotion(int nCurMotion, const float fDeltaTime);	// モーション・キャラクター2Dの更新

	// 静的メンバ変数
	static CListManager<CPlayer> *m_pList;	// オブジェクトリスト

	// メンバ変数
	CListManager<CPlayer>::AIterator m_iterator;	// イテレーター
	CPlayerState *m_pState;	// 状態
	D3DXVECTOR3	m_oldPos;	// 過去位置
};

#endif	// _PLAYER_H_
