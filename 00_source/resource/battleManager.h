//============================================================
//
//	バトルマネージャーヘッダー [battleManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _BATTLEMANAGER_H_
#define _BATTLEMANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CBattleState;		// バトル状態クラス
class CObject2D;		// オブジェクト2Dクラス			// TODO：将来的にはプレイヤーにする
class CFrame2D;			// フレーム2Dクラス
class CBattleCommandUI;	// 戦闘時のコマンド表示クラス
class CBattleNameUI;	// 戦闘時の名前表示クラス
class CBattleLifeUI;	// 戦闘時の体力表示クラス

//************************************************************
//	クラス定義
//************************************************************
// バトルマネージャークラス
class CBattleManager
{
public:
	// コンストラクタ
	CBattleManager();

	// デストラクタ
	~CBattleManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);		// 更新
	HRESULT ChangeState(CBattleState* pState);	// 状態変更

	CObject2D*			GetPlayer()		{ return m_pPlayer; }		// プレイヤー情報取得
	CFrame2D*			GetFrame()		{ return m_pFrame; }		// フレーム情報
	CBattleCommandUI*	GetCommandUI()	{ return m_pCommandUI; }	// コマンド表示取得
	CBattleNameUI*		GetNameUI()		{ return m_pNameUI; }		// 名前表示取得
	CBattleLifeUI*		GetLifeUI()		{ return m_pLifeUI; }		// 体力表示取得

	// 静的メンバ関数
	static CBattleManager* Create();	// 生成
	static void Release(CBattleManager*& prBattleManager);	// 破棄

private:
	// メンバ変数
	CBattleState*		m_pState;		// 状態
	CObject2D*			m_pPlayer;		// プレイヤー情報	// TODO：将来的にはプレイヤーにする
	CFrame2D*			m_pFrame;		// フレーム情報
	CBattleCommandUI*	m_pCommandUI;	// コマンド表示
	CBattleNameUI*		m_pNameUI;		// 名前表示
	CBattleLifeUI*		m_pLifeUI;		// 体力表示
};

#endif	// _BATTLEMANAGER_H_
