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
class CObject2D;		// オブジェクト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// イントロ状態クラス
class CIntroState
{
public:
	// コンストラクタ
	CIntroState(CIntroManager *pIntro) :
		m_pIntro	(pIntro)	// イントロマネージャー
	{}

	// デストラクタ
	virtual ~CIntroState() {}

	// 純粋仮想関数
	virtual HRESULT Init(void)	= 0;	// 初期化
	virtual void Uninit(void)	= 0;	// 終了
	virtual void Update(const float fDeltaTime) = 0;	// 更新

protected:
	// メンバ変数
	CIntroManager *m_pIntro;	// イントロマネージャー
};

// ロゴ表示状態クラス
class CIntroStateLogo : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateLogo(CIntroManager *pIntro) :
		CIntroState(pIntro),	// イニシャライザ
		m_pLogo	(nullptr)		// タイトルロゴ
	{}

	// デストラクタ
	~CIntroStateLogo() override {}

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ変数
	CObject2D *m_pLogo;	// タイトルロゴ
};

// 文字送り状態クラス
class CIntroStateText : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateText(CIntroManager *pIntro) :
		CIntroState(pIntro)	// イニシャライザ
	{}

	// デストラクタ
	~CIntroStateText() override {}

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
};

// 待機状態クラス
class CIntroStateWait : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateWait(CIntroManager *pIntro) :
		CIntroState(pIntro)	// イニシャライザ
	{}

	// デストラクタ
	~CIntroStateWait() override {}

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
};

// 終了状態クラス
class CIntroStateEnd : public CIntroState
{
public:
	// コンストラクタ
	CIntroStateEnd(CIntroManager *pIntro) :
		CIntroState(pIntro)	// イニシャライザ
	{}

	// デストラクタ
	~CIntroStateEnd() override {}

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
};

#endif	// _INTRO_STATE_H_
