//============================================================
//
//	フィールドメニューマネージャーヘッダー [menuManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _MENUMANAGER_H_
#define _MENUMANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CMenuUI;	// フィールドメニュークラス

//************************************************************
//	クラス定義
//************************************************************
// フィールドメニューマネージャークラス
class CMenuManager
{
public:
	// コンストラクタ
	CMenuManager();

	// デストラクタ
	~CMenuManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);		// 更新
	void SetEnableDrawMenu(const bool bDraw);	// フィールドメニュー描画状況設定
	bool IsChoiceSelect() const;				// 選択中状況取得
	inline bool IsDrawMenu() const { return (m_pMenu != nullptr); }	// フィールドメニュー描画状況取得

	// 静的メンバ関数
	static CMenuManager* Create();		// 生成
	static CMenuManager* GetInstance();	// 取得
	static void Release();				// 破棄

private:
	// 静的メンバ変数
	static CMenuManager* m_pInstance;	// 自身のインスタンス

	// メンバ変数
	CMenuUI* m_pMenu;	// フィールドメニュー情報
};

#endif	// _MENUMANAGER_H_
