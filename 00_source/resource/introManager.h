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
//	インクルードファイル
//************************************************************
#include "scrollText2D.h"

//************************************************************
//	前方宣言
//************************************************************
class CObject2D;	// オブジェクト2Dクラス
class CScroll2D;	// スクロール2Dクラス
class CIntroState;	// イントロ状態クラス

//************************************************************
//	クラス定義
//************************************************************
// イントロマネージャークラス
class CIntroManager
{
public:
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
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);		// 更新
	HRESULT ChangeState(CIntroState* pState);	// 状態変更
	void NextStory();							// 物語の遷移
	void ChangeStory(const int nStoryIdx);		// ストーリー変更
	void ChangeText(const int nStoryIdx);		// テキスト変更
	void StartScrollStory();					// ストーリースクロール開始
	bool NormalizeScrollStory();				// ストーリースクロール正規化
	void SetEnableSlowText(const bool bSlow);	// 文字送りの速度設定
	inline int GetStoryIdx()	{ return m_nStoryIdx; }					// 物語インデックス取得
	inline int GetNextCharIdx()	{ return m_pText->GetNextCharIdx(); }	// 次の表示文字インデックス取得
	inline bool IsTextScroll()	{ return m_pText->IsScroll(); }			// テキスト文字送り状況取得

	// 静的メンバ関数
	static CIntroManager* Create();	// 生成
	static void Release(CIntroManager*& prIntroManager);	// 破棄
	static inline void SetEnableLogoSkip(const bool bSkip)	{ m_bLogoSkip = bSkip; }	// ロゴスキップ状況設定
	static inline bool IsLogoSkip()							{ return m_bLogoSkip; }		// ロゴスキップ状況取得

private:
	// 静的メンバ変数
	static bool m_bLogoSkip;	// ロゴスキップ状況

	// メンバ変数
	CScroll2D* m_pStory;	// ストーリー
	CScrollText2D* m_pText;	// テキスト
	CIntroState* m_pState;	// 状態
	int m_nStoryIdx;		// 物語インデックス
};

#endif	// _INTROMANAGER_H_
