//============================================================
//
//	ロゴマネージャーヘッダー [logoManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _LOGO_MANAGER_H_
#define _LOGO_MANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CObject2D;	// オブジェクト2Dクラス
class CString2D;	// 文字列2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// ロゴマネージャークラス
class CLogoManager
{
public:
	// コンストラクタ
	CLogoManager();

	// デストラクタ
	~CLogoManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);	// 更新

	// 静的メンバ関数
	static CLogoManager* Create();	// 生成
	static void Release(CLogoManager*& prLogoManager);	// 破棄

private:
	// メンバ関数
	void UpdateDispTrans(const float fDeltaTime);	// 操作表示・遷移更新
	void UpdateCommand();	// コマンド入力更新

	// メンバ変数
	std::string m_sFragInput;	// キー入力フラグ
	CObject2D* m_pLogo;	// タイトルロゴ
	CString2D* m_pCont;	// 操作説明
	float m_fCurTime;	// 現在の待機時間
	bool m_bSndBall;	// BALLコマンド再生フラグ
};

#endif	// _LOGO_MANAGER_H_
