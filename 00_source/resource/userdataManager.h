//============================================================
//
//	ユーザーデータマネージャーヘッダー [userdataManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _USERDATA_MANAGER_H_
#define _USERDATA_MANAGER_H_

//************************************************************
//	クラス定義
//************************************************************
// ユーザーデータマネージャークラス
class CUserDataManager
{
public:
	// コンストラクタ
	CUserDataManager();

	// デストラクタ
	~CUserDataManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);	// 更新

	// 静的メンバ関数
	static CUserDataManager* Create();		// 生成
	static CUserDataManager* GetInstance();	// 取得
	static void Release();					// 破棄

private:
	// 静的メンバ変数
	static CUserDataManager* m_pInstance;	// 自身のインスタンス

	// メンバ変数
	float m_fPlayTime;	// プレイ総時間
};

#endif	// _USERDATA_MANAGER_H_
