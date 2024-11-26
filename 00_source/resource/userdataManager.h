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
//	前方宣言
//************************************************************
class CPlayerStatus;	// プレイヤーステータスクラス
class CPlayerItem;		// プレイヤー所持アイテムクラス

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
	void Update(const float fDeltaTime);				// 更新
	HRESULT InitPlayerStatus(CPlayerStatus* pStatus);	// プレイヤーステータス初期化
	HRESULT LoadPlayerStatus(CPlayerStatus* pStatus);	// プレイヤーステータス読込
	HRESULT InitPlayerItem(CPlayerItem* pItem);			// プレイヤー所持アイテム初期化
	HRESULT LoadPlayerItem(CPlayerItem* pItem);			// プレイヤー所持アイテム読込
	HRESULT InitUserData();	// ユーザーデータ初期化
	HRESULT LoadUserData();	// ユーザーデータ読込
	HRESULT InitAllData		// 内部データ初期化
	( // 引数
		CPlayerStatus* pStatus,	// プレイヤーステータス情報
		CPlayerItem* pItem		// プレイヤー所持アイテム情報
	);
	HRESULT SaveAllData		// 内部データ保存
	( // 引数
		CPlayerStatus* pStatus,	// プレイヤーステータス情報
		CPlayerItem* pItem		// プレイヤー所持アイテム情報
	);
	bool IsCheckSaveData();	// 内部データ保存ファイルがあるかの確認
	inline int GetRoom() const			{ return m_nRoom; }		// 部屋番号取得
	inline int GetFun() const			{ return m_nFun; }		// FUN値取得
	inline float GetPlayTime() const	{ return m_fPlayTime; }	// 総プレイ時間取得

	// 静的メンバ関数
	static CUserDataManager* Create();		// 生成
	static CUserDataManager* GetInstance();	// 取得
	static void Release();					// 破棄

private:
	// メンバ関数
	HRESULT LoadPlayerStatus(CPlayerStatus* pStatus, const char* pFilePath);	// プレイヤーステータス読込 (パス指定)
	HRESULT LoadPlayerItem(CPlayerItem* pItem, const char* pFilePath);			// プレイヤー所持アイテム読込 (パス指定)
	HRESULT LoadUserData(const char* pFilePath);								// ユーザーデータ読込 (パス指定)

	// 静的メンバ変数
	static CUserDataManager* m_pInstance;	// 自身のインスタンス

	// メンバ変数
	int m_nRoom;		// 部屋番号
	int m_nFun;			// FUN値
	float m_fPlayTime;	// 総プレイ時間
};

#endif	// _USERDATA_MANAGER_H_
