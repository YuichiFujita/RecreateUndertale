//============================================================
//
//	イントロ状態ヘッダー [introState.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _INTRO_STATE_H_
#define _INTRO_STATE_H_

//************************************************************
//	前方宣言
//************************************************************
class CIntroManager;	// イントロマネージャークラス

//************************************************************
//	クラス定義
//************************************************************
// イントロ状態クラス
class CIntroState
{
public:
	// コンストラクタ
	CIntroState(CIntroManager *pIntro) :
		m_pIntro(pIntro)	// イントロマネージャー
	{}

	// デストラクタ
	virtual ~CIntroState() { SAFE_DELETE(m_pState); }

	// 純粋仮想関数
	virtual void Update(void) = 0;	// 更新

	// メンバ関数
	void Change(CIntroState *pState);	// 状態変更

private:
	// メンバ変数
	CIntroManager *m_pIntro;	// イントロマネージャー
	CIntroState *m_pState;		// 自身のインスタンス
};

// ロゴ表示状態クラス
class CIntroStateLogo : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateLogo(CIntroManager *pIntro) :
		CIntroState(pIntro)
	{}

	// デストラクタ
	~CIntroStateLogo() override {}

	// オーバーライド関数
	void Update(void) override;	// 更新
};

// 文字送り状態クラス
class CIntroStateText : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateText(CIntroManager *pIntro) :
		CIntroState(pIntro)
	{}

	// デストラクタ
	~CIntroStateText() override {}

	// オーバーライド関数
	void Update(void) override;	// 更新
};

// 待機状態クラス
class CIntroStateWait : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateWait(CIntroManager *pIntro) :
		CIntroState(pIntro)
	{}

	// デストラクタ
	~CIntroStateWait() override {}

	// オーバーライド関数
	void Update(void) override;	// 更新
};

// 終了状態クラス
class CIntroStateEnd : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateEnd(CIntroManager *pIntro) :
		CIntroState(pIntro)
	{}

	// デストラクタ
	~CIntroStateEnd() override {}

	// オーバーライド関数
	void Update(void) override;	// 更新
};

#endif	// _INTRO_STATE_H_
