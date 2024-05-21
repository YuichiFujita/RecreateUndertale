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
class CIntroState;		// イントロ状態クラス

//************************************************************
//	クラス定義
//************************************************************
// イントロコンテキストクラス
class CIntroContext
{
public:
	// コンストラクタ
	CIntroContext(CIntroManager *pIntro) :
		m_pIntro(pIntro),	// イントロマネージャー
		m_pState(nullptr)	// 状態インスタンス
	{}

	// デストラクタ
	~CIntroContext() { SAFE_DELETE(m_pState); }

	// メンバ関数
	void Update(const float fDeltaTime);	// 更新
	void Change(CIntroState *pState);		// 状態変更

//private:	// TODO：本来絶対ダメ！
	// メンバ変数
	CIntroManager *m_pIntro;	// イントロマネージャー
	CIntroState *m_pState;		// 状態インスタンス
};

// イントロ状態クラス
class CIntroState
{
public:
	// コンストラクタ
	CIntroState(CIntroContext *pContext) :
		m_pContext(pContext)	// イントロコンテキスト
	{}

	// デストラクタ
	virtual ~CIntroState() {}

	// 純粋仮想関数
	virtual void Update(const float fDeltaTime) = 0;	// 更新

protected:
	// メンバ変数
	CIntroContext *m_pContext;	// イントロコンテキスト
};

// ロゴ表示状態クラス
class CIntroStateLogo : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateLogo(CIntroContext *pContext) :
		CIntroState(pContext)
	{}

	// デストラクタ
	~CIntroStateLogo() override {}

	// オーバーライド関数
	void Update(const float fDeltaTime) override;	// 更新
};

// 文字送り状態クラス
class CIntroStateText : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateText(CIntroContext *pContext) :
		CIntroState(pContext)
	{}

	// デストラクタ
	~CIntroStateText() override {}

	// オーバーライド関数
	void Update(const float fDeltaTime) override;	// 更新
};

// 待機状態クラス
class CIntroStateWait : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateWait(CIntroContext *pContext) :
		CIntroState(pContext)
	{}

	// デストラクタ
	~CIntroStateWait() override {}

	// オーバーライド関数
	void Update(const float fDeltaTime) override;	// 更新
};

// 終了状態クラス
class CIntroStateEnd : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateEnd(CIntroContext *pContext) :
		CIntroState(pContext)
	{}

	// デストラクタ
	~CIntroStateEnd() override {}

	// オーバーライド関数
	void Update(const float fDeltaTime) override;	// 更新
};

#endif	// _INTRO_STATE_H_
