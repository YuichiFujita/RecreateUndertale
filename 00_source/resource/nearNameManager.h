//============================================================
//
//	名前接近マネージャーヘッダー [nearNameManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _NEAR_NAME_MANAGER_H_
#define _NEAR_NAME_MANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス
class CText2D;		// テキスト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// 名前接近マネージャークラス
class CNearNameManager
{
public:
	// 選択列挙
	enum ESelect
	{
		SELECT_NONE = -1,	// 指定なし
		SELECT_NO,			// いいえ
		SELECT_YES,			// はい
		SELECT_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CNearNameManager();

	// デストラクタ
	~CNearNameManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	ESelect Update(const float fDeltaTime);	// 更新
	void TransGame();						// ゲーム画面遷移

	// 静的メンバ関数
	static CNearNameManager* Create	// 生成
	( // 引数
		const std::string& rName,					// 表示名
		const std::vector<std::wstring>& rVecStr	// タイトル割当テキスト
	);
	static void Release(CNearNameManager*& prNearNameManager);	// 破棄

private:
	// メンバ関数
	void UpdateSelect();	// 選択更新
	ESelect UpdateDecide();	// 決定更新
	void ShakeName(const float fDeltaTime);	// 名前振動
	void MoveName(const float fDeltaTime);	// 名前移動
	void SetName(const std::string& rName);	// 名前設定

	// メンバ変数
	CString2D* m_apSelect[SELECT_MAX];	// 選択肢
	CText2D* m_pTitle;		// タイトル
	CString2D* m_pName;		// 名前
	int m_nCurSelect;		// 現在の選択肢
	int m_nOldSelect;		// 前回の選択肢
	float m_fCurTimeShake;	// 現在の振動の経過時間
	float m_fCurTimeMove;	// 現在の移動の経過時間
	float m_fNameDestPosX;	// 名前の目標位置X
	bool m_bMove;			// 名前の移動状況
};

#endif	// _NEAR_NAME_MANAGER_H_
