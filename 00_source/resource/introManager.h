//============================================================
//
//	イントロマネージャーヘッダー [introManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _INTROMANAGER_H_
#define _INTROMANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CObject2D;		// オブジェクト2Dクラス
class CScroll2D;		// スクロール2Dクラス
class CScrollText2D;	// 文字送りテキスト2Dクラス
class CIntroState;		// イントロ状態クラス

//************************************************************
//	クラス定義
//************************************************************
// イントロマネージャークラス
class CIntroManager
{
public:
	// フェード列挙
	enum EFade
	{
		FADE_NONE = 0,	// フェード無し
		FADE_IN,		// フェードイン
		FADE_OUT,		// フェードアウト
		FADE_MAX		// この列挙型の総数
	};

	// 物語列挙
	enum EStory
	{
		STORY_00 = 0,	// むかしむかし
		STORY_01,		// ところがあるとき
		STORY_02,		// ニンゲンしょうり
		STORY_03,		// ちかにとじこめました
		STORY_04,		// ながいときがながれ
		STORY_05,		// イビト山
		STORY_06,		// でんせつの山
		STORY_07,		// 見下ろし
		STORY_08,		// 引っ掛かり
		STORY_09,		// 落下
		STORY_10,		// 着地
		STORY_MAX,		// この列挙型の総数
	};

	// コンストラクタ
	CIntroManager();

	// デストラクタ
	~CIntroManager();

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(const float fDeltaTime);		// 更新
	HRESULT ChangeState(CIntroState *pState);	// 状態変更

	// 静的メンバ関数
	static CIntroManager *Create(void);	// 生成
	static void Release(CIntroManager *&prIntroManager);	// 破棄

//private:	// TODO：本来絶対ダメ！
	// メンバ関数
	bool WaitTime(const float fDeltaTime, const float fDestTime);	// 待機時間の管理
	void NextStory(void);	// 物語の遷移
	void UpdateFade(void);	// フェード更新

	// メンバ変数
	CObject2D *m_pFade;		// フェード
	CScroll2D *m_pStory;	// ストーリー
	CScrollText2D *m_pText;	// テキスト
	CIntroState *m_pState;	// 状態
	EFade m_fade;			// フェード状況
	int m_nStory;			// 物語インデックス
	float m_fCurTime;		// 現在の待機時間
};

#endif	// _INTROMANAGER_H_
