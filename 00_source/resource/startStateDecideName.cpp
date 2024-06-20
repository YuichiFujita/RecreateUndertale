//============================================================
//
//	名前決定状態処理 [startStateDecideName.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "startStateDecideName.h"
#include "startManager.h"
#include "manager.h"
#include "shakeString2D.h"
#include "string2D.h"
#include "text2D.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *PASS		= "data\\TEXT\\start.txt";	// テキストパス
	const int	PRIORITY	= 6;	// 優先順位
	const float	MOVE_TIME	= 4.0f;	// 移動時間

	namespace title
	{	
		const char	*FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const char	*PASS = "data\\TEXT\\naming.txt";	// テキストパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 42.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 54.0f;	// 行間縦幅

		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_CENTER;	// 縦配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(270.0f, 130.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
	}

	namespace name
	{
		const char	*FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC	= false;		// イタリック
		const float	INIT_HEIGHT	= 42.0f;	// 初期文字縦幅
		const float	DEST_HEIGHT	= 148.0f;	// 目標文字縦幅
		const float	NEXT_TIME	= 0.035f;	// 文字振動の待機時間
		const float	MOVE		= 1.5f;		// 振動移動量

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;			// 横配置
		const D3DXVECTOR3	INIT_POS = D3DXVECTOR3(360.0f, 155.0f, 0.0f);	// 初期位置
		const D3DXVECTOR3	DEST_POS = D3DXVECTOR3(60.0f, 385.0f, 0.0f);	// 目標位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
	}

	namespace select
	{
		const char	*FONT		= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 42.0f;	// 文字縦幅
		const float	LINE_WIDTH	= 500.0f;	// 列間縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;	// 横配置
		const D3DXVECTOR3 POS = D3DXVECTOR3(180.0f, 615.0f, 0.0f);	// 位置
		const D3DXVECTOR3 ROT = VEC3_ZERO;			// 向き
		const D3DXCOLOR COL_DEFAULT	= XCOL_WHITE;	// 通常色
		const D3DXCOLOR COL_CHOICE	= XCOL_YELLOW;	// 選択色
	}
}

//************************************************************
//	子クラス [CStartStateDecideName] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartStateDecideName::CStartStateDecideName() :
	m_pTitle		(nullptr),		// タイトル
	m_pName			(nullptr),		// 名前
	m_state			((EState)0),	// 状態
	m_nCurSelect	(0),			// 現在の選択肢
	m_nOldSelect	(0),			// 前回の選択肢
	m_fCurTimeShake	(0.0f),			// 現在の振動の経過時間
	m_fCurTimeMove	(0.0f)			// 現在の移動の経過時間
{
	// メンバ変数をクリア
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢
}

//============================================================
//	デストラクタ
//============================================================
CStartStateDecideName::~CStartStateDecideName()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CStartStateDecideName::Init(void)
{
	// メンバ変数を初期化
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢
	m_pTitle		= nullptr;		// タイトル
	m_pName			= nullptr;		// 名前
	m_state			= STATE_MOVE;	// 状態
	m_nCurSelect	= 0;			// 現在の選択肢
	m_nOldSelect	= 0;			// 前回の選択肢
	m_fCurTimeShake	= 0.0f;			// 現在の振動の経過時間
	m_fCurTimeMove	= 0.0f;			// 現在の移動の経過時間

	// タイトルの生成
	m_pTitle = CText2D::Create
	( // 引数
		title::FONT,		// フォントパス
		title::ITALIC,		// イタリック
		title::POS,			// 原点位置
		title::CHAR_HEIGHT,	// 文字縦幅
		title::LINE_HEIGHT,	// 行間縦幅
		title::ALIGN_X,		// 横配置
		title::ALIGN_Y,		// 縦配置
		title::ROT,			// 原点向き
		title::COL			// 色
	);
	if (m_pTitle == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pTitle->SetPriority(PRIORITY);

	// テキストを割当
	loadtext::BindText(m_pTitle, loadtext::LoadText(title::PASS, m_pContext->GetName().c_str()));

	// 名前の生成
	m_pName = CShakeString2D::Create
	( // 引数
		name::FONT,			// フォントパス
		name::ITALIC,		// イタリック
		L"",				// 指定文字列
		name::INIT_POS,		// 原点位置
		name::NEXT_TIME,	// 文字振動の待機時間
		name::MOVE,			// 振動移動量
		name::INIT_HEIGHT,	// 文字縦幅
		name::ALIGN_X,		// 横配置
		name::ROT,			// 原点向き
		name::COL			// 色
	);
	if (m_pName == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pName->SetPriority(PRIORITY);

	// 保存中の名前を設定
	m_pName->SetString(useful::MultiByteToWide(m_pContext->GetName()));

	f = m_pName->GetStrWidth() * (name::DEST_HEIGHT / name::INIT_HEIGHT);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 文字位置オフセット
		D3DXVECTOR3 offset = D3DXVECTOR3(select::LINE_WIDTH * i, 0.0f, 0.0f);

		// 選択肢の生成
		m_apSelect[i] = CString2D::Create
		( // 引数
			select::FONT,			// フォントパス
			select::ITALIC,			// イタリック
			L"",					// 指定文字列
			select::POS + offset,	// 原点位置
			select::CHAR_HEIGHT,	// 文字縦幅
			select::ALIGN_X,		// 横配置
			select::ROT,			// 原点向き
			select::COL_DEFAULT		// 色
		);

		// 優先順位を設定
		m_apSelect[i]->SetPriority(PRIORITY);

		// 文字列を割当
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(PASS, CStartManager::TEXT_DESIDE_NO + i));
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CStartStateDecideName::Uninit(void)
{
	// タイトルの終了
	SAFE_UNINIT(m_pTitle);

	// 名前の終了
	SAFE_UNINIT(m_pName);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択肢の終了
		SAFE_UNINIT(m_apSelect[i]);
	}

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CStartStateDecideName::Update(const float fDeltaTime)
{
	// 状態ごとの更新
	assert(m_state > NONE_IDX && m_state < STATE_MAX);
	(this->*(FUNC_STATE[m_state]))(fDeltaTime);

	// 名前振動の更新
	UpdateShakeName(fDeltaTime);

	// 選択の更新
	UpdateSelect();

	// 決定の更新
	UpdateDecide();
}

//============================================================
//	選択の更新処理
//============================================================
void CStartStateDecideName::UpdateSelect(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報

	// 前回の選択肢を保存
	m_nOldSelect = m_nCurSelect;

	// 選択肢操作
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// 左に選択をずらす
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// 右に選択をずらす
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}

	// 前回の選択要素の色を白色に設定
	m_apSelect[m_nOldSelect]->SetColor(select::COL_DEFAULT);

	// 現在の選択要素の色を黄色に設定
	m_apSelect[m_nCurSelect]->SetColor(select::COL_CHOICE);
}

//============================================================
//	決定の更新処理
//============================================================
void CStartStateDecideName::UpdateDecide(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_Z) || pKey->IsTrigger(DIK_RETURN))
	{
		// 選択肢に応じて遷移先を変更
		switch (m_nCurSelect)
		{ // 現在の選択肢ごとの処理
		case SELECT_NO:
			m_pContext->ChangeState(new CStartStateCreateName);	// 命名状態
			break;

		case SELECT_YES:
			// TODO：名前確定時の演出！
			break;

		default:
			assert(false);
			break;
		}
	}
}

//============================================================
//	名前振動の更新処理
//============================================================
void CStartStateDecideName::UpdateShakeName(const float fDeltaTime)
{
	// 現在の待機時間を加算
	m_fCurTimeShake += fDeltaTime;
	if (m_fCurTimeShake >= 0.018f)
	{ // 待機し終わった場合

		// 現在の待機時間を初期化
		m_fCurTimeShake = 0.0f;

		// 向きをぶんぶん動かす
		D3DXVECTOR3 rot = m_pName->GetVec3Rotation();
		rot.z = 0.011f * (float)(rand() % 3 - 1);
		m_pName->SetVec3Rotation(rot);
	}
}

//============================================================
//	何もしない状態の更新処理
//============================================================
void CStartStateDecideName::StateUpdateNone(const float fDeltaTime)
{

}

//============================================================
//	名前の移動状態の更新処理
//============================================================
void CStartStateDecideName::StateUpdateMove(const float fDeltaTime)
{
	// 経過時刻を進める
	m_fCurTimeMove += fDeltaTime;
	if (useful::LimitMaxNum(m_fCurTimeMove, MOVE_TIME))
	{ // 経過しきった場合

		// 何もしない状態にする
		m_state = STATE_NONE;
	}

	// 経過時刻の割合を計算
	float fRate = easeing::Liner(m_fCurTimeMove, 0.0f, MOVE_TIME);

	D3DXVECTOR3 posDest = name::DEST_POS;
	posDest.x = SCREEN_CENT.x - f * 0.75f;

	D3DXVECTOR3 pos = posDest - name::INIT_POS;
	m_pName->SetVec3Position(name::INIT_POS + pos * fRate);

	float fHeight = name::DEST_HEIGHT - name::INIT_HEIGHT;
	m_pName->SetCharHeight(name::INIT_HEIGHT + fHeight * fRate);
}
