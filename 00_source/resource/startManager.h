//============================================================
//
//	スタートマネージャーヘッダー [startManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _STARTMANAGER_H_
#define _STARTMANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CStartState;	// スタート状態クラス

//************************************************************
//	クラス定義
//************************************************************
// スタートマネージャークラス
class CStartManager
{
public:
	// 表示テキスト列挙
	enum EText
	{
		TEXT_BUTTON_TITLE = 0,	// ─ ボタンそうさ ─
		TEXT_BUTTON_KINDS,		// 各種操作ボタン
		TEXT_RULE,				// HPが0になるとゲームオーバー
		TEXT_START,				// ゲームをはじめる
		TEXT_OPTION,			// せってい
		TEXT_NAMING,			// なまえをつけてください
		TEXT_HIRAGANA,			// ひらがな
		TEXT_KATAKANA,			// カタカナ
		TEXT_ALPHABET,			// アルファベット
		TEXT_NAMING_QUIT,		// やめる
		TEXT_NAMING_DEL,		// さくじょ
		TEXT_NAMING_DEC,		// かくてい
		TEXT_MAX				// この列挙型の総数
	};

	// コンストラクタ
	CStartManager();

	// デストラクタ
	~CStartManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);		// 更新
	HRESULT ChangeState(CStartState* pState);	// 状態変更
	inline void SetName(const std::string& rName)	{ m_sName = rName; }	// 名前設定
	inline std::string GetName() const				{ return m_sName; }		// 名前取得

	// 静的メンバ関数
	static CStartManager* Create();	// 生成
	static void Release(CStartManager*& prStartManager);	// 破棄

private:
	// メンバ変数
	CStartState* m_pState;	// 状態
	std::string m_sName;	// 名前
};

#endif	// _STARTMANAGER_H_
