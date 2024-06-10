//============================================================
//
//	命名状態処理 [startStateCreateName.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "startStateCreateName.h"
#include "startManager.h"
#include "manager.h"
#include "string2D.h"
#include "charState.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *PASS = "data\\TEXT\\start.txt";	// テキストパス
	const int PRIORITY = 6;	// 優先順位

	namespace title
	{	
		const char	*FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 42.0f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 80.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
	}
	
	namespace select
	{	
		const D3DXVECTOR3 POS[CStartStateCreateName::SELECT_Y_MAX][CStartStateCreateName::SELECT_X_MAX] =	// 位置配列
		{
			{ D3DXVECTOR3(180.0f, 530.0f, 0.0f), D3DXVECTOR3(440.0f, 530.0f, 0.0f), D3DXVECTOR3(750.0f, 530.0f, 0.0f) },
			{ D3DXVECTOR3(220.0f, 630.0f, 0.0f), D3DXVECTOR3(460.0f, 630.0f, 0.0f), D3DXVECTOR3(700.0f, 630.0f, 0.0f) },
		};

		const char	*FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 42.0f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;	// 横配置
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
	}
}

//************************************************************
//	子クラス [CStartStateCreateName] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartStateCreateName::CStartStateCreateName() :
	m_pTitle	(nullptr),	// タイトル
	m_pState	(nullptr)	// 文字状態
{
	// メンバ変数をクリア
	memset(&m_apSelect[0][0], 0, sizeof(m_apSelect));	// 選択肢
}

//============================================================
//	デストラクタ
//============================================================
CStartStateCreateName::~CStartStateCreateName()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CStartStateCreateName::Init(void)
{
	// メンバ変数を初期化
	memset(&m_apSelect[0][0], 0, sizeof(m_apSelect));	// 選択肢
	m_pTitle = nullptr;	// タイトル
	m_pState = nullptr;	// 文字状態

	// 文字状態をひらがなにする
	ChangeState(new CCharStateHiragana);

	// タイトルの生成
	m_pTitle = CString2D::Create
	( // 引数
		title::FONT,	// フォントパス
		title::ITALIC,	// イタリック
		L"",			// 指定文字列
		title::POS,		// 原点位置
		title::HEIGHT,	// 文字縦幅
		title::ALIGN_X,	// 横配置
		title::ROT,		// 原点向き
		title::COL		// 色
	);

	// 優先順位を設定
	m_pTitle->SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindString(m_pTitle, loadtext::LoadText(PASS, CStartManager::TEXT_NAMING));

	for (int i = 0; i < SELECT_Y_MAX; i++)
	{
		for (int j = 0; j < SELECT_X_MAX; j++)
		{
			// 選択肢の生成
			m_apSelect[i][j] = CString2D::Create
			( // 引数
				select::FONT,		// フォントパス
				select::ITALIC,		// イタリック
				L"",				// 指定文字列
				select::POS[i][j],	// 原点位置
				select::HEIGHT,		// 文字縦幅
				select::ALIGN_X,	// 横配置
				select::ROT,		// 原点向き
				select::COL			// 色
			);

			// 優先順位を設定
			m_apSelect[i][j]->SetPriority(PRIORITY);

			// 文字列を割当
			loadtext::BindString(m_apSelect[i][j], loadtext::LoadText(PASS, CStartManager::TEXT_HIRAGANA + (i * SELECT_X_MAX) + j));
		}
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CStartStateCreateName::Uninit(void)
{
	// タイトルの終了
	SAFE_UNINIT(m_pTitle);

	for (int i = 0; i < SELECT_Y_MAX; i++)
	{
		for (int j = 0; j < SELECT_X_MAX; j++)
		{
			// 選択肢の終了
			SAFE_UNINIT(m_apSelect[i][j]);
		}
	}

	// 状態の終了
	SAFE_UNINIT(m_pState);

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CStartStateCreateName::Update(const float fDeltaTime)
{
	// 選択の更新
	UpdateSelect();

	// 決定の更新
	UpdateDecide();

	// 状態ごとの更新
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	状態の変更処理
//============================================================
HRESULT CStartStateCreateName::ChangeState(CCharState *pState)
{
	// 状態の生成に失敗している場合抜ける
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// 状態インスタンスを終了
	SAFE_UNINIT(m_pState);

	// 状態インスタンスを変更
	assert(m_pState == nullptr);
	m_pState = pState;

	// 状態インスタンスを初期化
	if (FAILED(m_pState->Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 状態にコンテキストを設定
	m_pState->SetContext(this);

	// 成功を返す
	return S_OK;
}

//============================================================
//	選択の更新処理
//============================================================
void CStartStateCreateName::UpdateSelect(void)
{
#if 0
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報

	// 前回の選択肢を保存
	m_nOldSelect = m_nCurSelect;

	// 選択肢操作
	if (pKey->IsTrigger(DIK_DOWN))
	{
		// 上に選択をずらす
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		// 下に選択をずらす
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}

	// 前回の選択要素の色を白色に設定
	m_apSelect[m_nOldSelect]->SetColor(select::COL_DEFAULT);

	// 現在の選択要素の色を黄色に設定
	m_apSelect[m_nCurSelect]->SetColor(select::COL_CHOICE);
#endif
}

//============================================================
//	決定の更新処理
//============================================================
void CStartStateCreateName::UpdateDecide(void)
{
#if 0
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_Z) || pKey->IsTrigger(DIK_RETURN))
	{
		// 選択肢に応じて遷移先を変更
		switch (m_nCurSelect)
		{ // 現在の選択肢ごとの処理
		case SELECT_CLOSE:
			m_pContext->ChangeState(new CStartStateTutorial);	// チュートリアル状態
			break;

		default:
			assert(false);
			break;
		}
	}
#endif
}
