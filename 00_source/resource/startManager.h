//============================================================
//
//	スタートマネージャーヘッダー [startManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

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
		TEXT_PRESS_Z = 0,	// [PRESS Z OR ENTER]
		TEXT_BUTTON_TITLE,	// ─ ボタンそうさ ─
		TEXT_BUTTON_KINDS,	// 各種操作ボタン
		TEXT_RULE,			// HPが0になるとゲームオーバー
		TEXT_START,			// ゲームをはじめる
		TEXT_OPTION,		// せってい
		TEXT_VIRSION,		// バージョン情報
		TEXT_OPTION_TITLE,	// せってい
		TEXT_OPTION_CLOSE,	// とじる
		TEXT_NAMING,		// なまえをつけてください
		TEXT_HIRAGANA,		// ひらがな
		TEXT_KATAKANA,		// カタカナ
		TEXT_ALPHABET,		// アルファベット
		TEXT_NAMING_QUIT,	// やめる
		TEXT_NAMING_DEL,	// さくじょ
		TEXT_NAMING_DEC,	// かくてい
		TEXT_DESIDE_NO,		// いいえ
		TEXT_DESIDE_YES,	// はい
		TEXT_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CStartManager();

	// デストラクタ
	~CStartManager();

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(const float fDeltaTime);		// 更新
	HRESULT ChangeState(CStartState* pState);	// 状態変更
	void SetName(const std::string& rName)	{ m_sName = rName; }	// 名前設定
	std::string GetName(void) const			{ return m_sName; }		// 名前取得

	// 静的メンバ関数
	static CStartManager* Create(void);	// 生成
	static void Release(CStartManager*& prStartManager);	// 破棄

private:
	// メンバ変数
	CStartState* m_pState;	// 状態
	std::string m_sName;	// 名前
};

#endif	// _STATEMANAGER_H_
