//============================================================
//
//	ロゴ表示状態処理 [startStateLogo.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "startStateLogo.h"
#include "startManager.h"
#include "introManager.h"
#include "manager.h"
#include "sound.h"
#include "object2D.h"
#include "string2D.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char	*TEXTURE	= "data\\TEXTURE\\logo000.png";	// ロゴテクスチャ
	const int	PRIORITY	= 6;		// 優先順位
	const float	DISP_TIME	= 3.0f;		// ロゴ表示時間
	const float	TRANS_TIME	= 17.0f;	// イントロ遷移の余韻時間
	const char	*CMD_BALL	= "ball";	// BALL効果音を鳴らすコマンド入力

	namespace str
	{
		const char	*FONT	= "data\\FONT\\Crypt of Tomorrow.ttf";	// フォントパス
		const char	*PASS	= "data\\TEXT\\start.txt";				// テキストパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 22.5f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// 横配置
		const D3DXCOLOR   COL = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);			// 色
		const D3DXVECTOR3 POS = D3DXVECTOR3(SCREEN_CENT.x, 545.0f, 0.0f);	// 位置
		const D3DXVECTOR3 ROT = VEC3_ZERO;	// 向き
	}
}

//************************************************************
//	子クラス [CStartStateLogo] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartStateLogo::CStartStateLogo() :
	m_pLogo		(nullptr),	// タイトルロゴ
	m_pCont		(nullptr),	// 操作説明
	m_fCurTime	(0.0f),		// 現在の待機時間
	m_bSndBall	(false)		// BALLコマンド再生フラグ
{

}

//============================================================
//	デストラクタ
//============================================================
CStartStateLogo::~CStartStateLogo()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CStartStateLogo::Init(void)
{
	// メンバ変数を初期化
	m_pLogo		= nullptr;	// タイトルロゴ
	m_pCont		= nullptr;	// 操作説明
	m_fCurTime	= 0.0f;		// 現在の待機時間
	m_bSndBall	= false;	// BALLコマンド再生フラグ

	// タイトルロゴの生成
	m_pLogo = CObject2D::Create(SCREEN_CENT, SCREEN_SIZE);
	if (m_pLogo == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pLogo->BindTexture(TEXTURE);

	// 優先順位を設定
	m_pLogo->SetPriority(PRIORITY);

	// イントロノイズを再生
	PLAY_SOUND(CSound::LABEL_SE_INTRONOISE);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CStartStateLogo::Uninit(void)
{
	// タイトルロゴの終了
	SAFE_UNINIT(m_pLogo);

	// 操作説明の終了
	SAFE_UNINIT(m_pCont);

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CStartStateLogo::Update(const float fDeltaTime)
{
	// 操作表示・遷移の更新
	UpdateDispTrans(fDeltaTime);

	// コマンド入力の更新
	UpdateCommand();

	// 進行操作
	if (GET_INPUTKEY->IsTrigger(DIK_RETURN) || GET_INPUTKEY->IsTrigger(DIK_Z))
	{
		// チュートリアル状態にする
		m_pContext->ChangeState(new CStartStateTutorial);
	}
}

//============================================================
//	操作表示・遷移の更新処理
//============================================================
void CStartStateLogo::UpdateDispTrans(const float fDeltaTime)
{
	if (m_pCont == nullptr)
	{ // 操作説明が非表示の場合

		// 待機時刻を進める
		m_fCurTime += fDeltaTime;
		if (m_fCurTime >= DISP_TIME)
		{ // 待機終了した場合

			// 待機時間を初期化
			m_fCurTime = 0.0f;

			// 操作説明の生成
			m_pCont = CString2D::Create
			( // 引数
				str::FONT,		// フォントパス
				str::ITALIC,	// イタリック
				L"",			// 指定文字列
				str::POS,		// 原点位置
				str::HEIGHT,	// 文字縦幅
				str::ALIGN_X,	// 横配置
				str::ROT,		// 原点向き
				str::COL		// 色
			);

			// 優先順位を設定
			m_pCont->SetPriority(PRIORITY);

			// 文字列を割当
			loadtext::BindString(m_pCont, loadtext::LoadText(str::PASS, CStartManager::TEXT_PRESS_Z));
		}
	}
	else
	{ // 操作説明が表示済みの場合

		// 待機時刻を進める
		m_fCurTime += fDeltaTime;
		if (m_fCurTime >= TRANS_TIME)
		{ // 待機終了した場合

			// 待機時間を初期化
			m_fCurTime = 0.0f;

			// ロゴ表示をスキップする
			CIntroManager::SetEnableLogoSkip(true);

			// イントロ画面に遷移する
			GET_MANAGER->SetScene(CScene::MODE_INTRO);
		}
	}
}

//============================================================
//	コマンド入力の更新処理
//============================================================
void CStartStateLogo::UpdateCommand(void)
{
	// BALL効果音が再生済みの場合抜ける
	if (m_bSndBall) { return; }

	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報

	// 最後尾に入力キーのフラグを追加
	if (pKey->IsTrigger(DIK_B))
	{
		m_sFragInput.push_back('b');
	}
	if (pKey->IsTrigger(DIK_A))
	{
		m_sFragInput.push_back('a');
	}
	if (pKey->IsTrigger(DIK_L))
	{
		m_sFragInput.push_back('l');
	}

	// 入力フラグ群にコマンドが成立している瞬間があるかを確認
	if (m_sFragInput.find(CMD_BALL) != std::string::npos)
	{ // コマンド文字列が存在した場合

		// BALL入力効果音を再生
		PLAY_SOUND(CSound::LABEL_SE_BALLCHIME);

		// BALL効果音を再生済みにする
		m_bSndBall = true;
	}
}
