//============================================================
//
//	タイトルマネージャーヘッダー [titleManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _TITLEMANAGER_H_
#define _TITLEMANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス
class CVersion;		// バージョン表記クラス

//************************************************************
//	クラス定義
//************************************************************
// タイトルマネージャークラス
class CTitleManager
{
public:
	// 表示テキスト列挙
	enum EText
	{
		TEXT_CONTINUE = 0,	// コンティニュー
		TEXT_RESET,			// リセット
		TEXT_SETTING,		// 設定
		TEXT_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CTitleManager();

	// デストラクタ
	~CTitleManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);	// 更新

	// 静的メンバ関数
	static CTitleManager* Create();	// 生成
	static void Release(CTitleManager*& prTitleManager);	// 破棄

private:
	// メンバ関数
	void UpdateSelect();	// 選択更新
	void UpdateDecide();	// 決定更新

	// メンバ変数
	std::vector<std::vector<CString2D*>> m_vecSelect;	// 選択肢情報
	CString2D* m_pName;		// 名前情報
	CString2D* m_pLove;		// レベル情報
	CString2D* m_pTime;		// 総プレイ時間情報
	CVersion* m_pVersion;	// バージョン表記情報
	POSGRID2 m_curSelect;	// 現在の選択肢
	POSGRID2 m_oldSelect;	// 前回の選択肢
};

#endif	// _TITLEMANAGER_H_
