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
class CBattleState;	// バトル状態クラス

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

	// 静的メンバ関数
	static CBattleManager* Create();	// 生成
	static void Release(CBattleManager*& prBattleManager);	// 破棄

private:
	// メンバ変数
	CBattleState* m_pState;	// 状態
};

#endif	// _BATTLEMANAGER_H_
