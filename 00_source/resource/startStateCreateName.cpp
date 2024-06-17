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
#include "namingManager.h"
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
		const D3DXVECTOR3 POS[CStartStateCreateName::YSELECT_POLY_MAX][CStartStateCreateName::XSELECT_MAX] =	// 位置配列
		{
			{ D3DXVECTOR3(180.0f, 530.0f, 0.0f), D3DXVECTOR3(440.0f, 530.0f, 0.0f), D3DXVECTOR3(750.0f, 530.0f, 0.0f) },
			{ D3DXVECTOR3(220.0f, 630.0f, 0.0f), D3DXVECTOR3(460.0f, 630.0f, 0.0f), D3DXVECTOR3(700.0f, 630.0f, 0.0f) },
		};

		const char	*FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 42.0f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;	// 横配置
		const D3DXVECTOR3	ROT			= VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL_DEFAULT	= XCOL_WHITE;	// 通常色
		const D3DXCOLOR		COL_CHOICE	= XCOL_YELLOW;	// 選択色
	}
}

//************************************************************
//	子クラス [CStartStateCreateName] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartStateCreateName::CStartStateCreateName() :
	m_pTitle	(nullptr),		// タイトル
	m_pNaming	(nullptr),		// 命名マネージャー
	m_curSelect	(GRID2_ZERO),	// 現在の選択肢
	m_oldSelect	(GRID2_ZERO)	// 前回の選択肢
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
	m_pTitle	= nullptr;		// タイトル
	m_pNaming	= nullptr;		// 命名マネージャー
	m_curSelect	= GRID2_ZERO;	// 現在の選択肢
	m_oldSelect	= GRID2_ZERO;	// 前回の選択肢

	// 命名マネージャーの生成
	m_pNaming = CNamingManager::Create(this);
	if (m_pNaming == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

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
	if (m_pTitle == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pTitle->SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindString(m_pTitle, loadtext::LoadText(PASS, CStartManager::TEXT_NAMING));


	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CStartStateCreateName::Uninit(void)
{
	// 命名マネージャーの破棄
	SAFE_REF_RELEASE(m_pNaming);

	// タイトルの終了
	SAFE_UNINIT(m_pTitle);

	for (int i = 0; i < YSELECT_POLY_MAX; i++)
	{
		for (int j = 0; j < XSELECT_MAX; j++)
		{
			// 選択肢の終了
			SAFE_UNINIT(m_apSelect[i][j]);
		}
	}

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CStartStateCreateName::Update(const float fDeltaTime)
{
	// 選択の更新
	UpdateSelect(fDeltaTime);

	// 決定の更新
	UpdateDecide();

	// TODO：検証用
	if (GET_INPUTKEY->IsTrigger(DIK_0))
	{
		m_pNaming->ChangeChar(CNamingManager::TYPECHAR_HIRAGANA);
	}
	if (GET_INPUTKEY->IsTrigger(DIK_9))
	{
		m_pNaming->ChangeChar(CNamingManager::TYPECHAR_KATAKANA);
	}
	if (GET_INPUTKEY->IsTrigger(DIK_8))
	{
		m_pNaming->ChangeChar(CNamingManager::TYPECHAR_ALPHABET);
	}
}

//============================================================
//	選択の更新処理
//============================================================
void CStartStateCreateName::UpdateSelect(const float fDeltaTime)
{
#if 0
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報

	// 前回の選択肢を保存
	m_oldSelect = m_curSelect;

	// TODO：いまのままだと選択肢は動かせないよ
	if (m_curSelect.y == YSELECT_TOP)
	{ // 選択が文字に入っている場合

		// 命名マネージャーの更新
		assert(m_pNaming != nullptr);
		m_pNaming->Update(fDeltaTime);
	}
	else
	{ // 選択が選択肢に入っている場合

		// 選択肢操作
		if (pKey->IsTrigger(DIK_LEFT))
		{
			// 左に選択をずらす
			m_curSelect.x = (m_curSelect.x + (XSELECT_MAX - 1)) % XSELECT_MAX;
		}
		if (pKey->IsTrigger(DIK_RIGHT))
		{
			// 右に選択をずらす
			m_curSelect.x = (m_curSelect.x + 1) % XSELECT_MAX;
		}
		if (pKey->IsTrigger(DIK_UP))
		{
			// 上に選択をずらす
			m_curSelect.y = (m_curSelect.y + (YSELECT_MAX - 1)) % YSELECT_MAX;
		}
		if (pKey->IsTrigger(DIK_DOWN))
		{
			// 下に選択をずらす
			m_curSelect.y = (m_curSelect.y + 1) % YSELECT_MAX;
		}

		if (m_curSelect.y == YSELECT_TOP)
		{
			// 前回の選択要素の色を白色に設定
			m_apSelect[m_oldSelect.y - 1][m_oldSelect.x]->SetColor(select::COL_DEFAULT);
		}
		else
		{
			// 前回の選択要素の色を白色に設定
			m_apSelect[m_oldSelect.y - 1][m_oldSelect.x]->SetColor(select::COL_DEFAULT);

			// 現在の選択要素の色を黄色に設定
			m_apSelect[m_curSelect.y - 1][m_curSelect.x]->SetColor(select::COL_CHOICE);
		}
	}
#else
	// 命名マネージャーの更新
	assert(m_pNaming != nullptr);
	m_pNaming->Update(fDeltaTime);
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
		// 選択肢に応じて操作を変更
		switch (m_curSelect.y)
		{ // 現在の行選択肢ごとの処理
		case YSELECT_CENTER:	// 文字変更行

			// 選択中の文字に変更
			m_pNaming->ChangeChar((CNamingManager::ETypeChar)m_curSelect.x);
			break;

		case YSELECT_BOTTOM:	// 設定済み文字操作行

			switch (m_curSelect.x)
			{ // 現在の列選択肢ごとの処理
			case XSELECT_LEFT:		// 止める

				// チュートリアル状態にする
				m_pContext->ChangeState(new CStartStateTutorial);
				break;

			case XSELECT_CENTER:	// 削除

				// 最後尾を一文字削除
				//m_pNaming->DeleteBackName();	// TODO
				break;

			case XSELECT_RIGHT:		// 確定

				// 名前決定状態にする
				//m_pContext->ChangeState(new CStartStateDecideName(m_pNaming->GetName()));	// TODO
				break;

			default:
				assert(false);
				break;
			}
			break;

		default:
			assert(false);
			break;
		}
	}
#endif
}
