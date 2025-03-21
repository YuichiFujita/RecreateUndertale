//============================================================
//
//	名前接近マネージャー処理 [nearNameManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "nearNameManager.h"
#include "manager.h"
#include "sound.h"
#include "shakeString2D.h"
#include "string2D.h"
#include "text2D.h"
#include "loadtext.h"
#include "userdataManager.h"
#include "playerStatus.h"
#include "playerItem.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char*	PATH		= "data\\TEXT\\start.txt";	// テキストパス
	const int	PRIORITY	= 6;	// 優先順位
	const float	MOVE_TIME	= 4.0f;	// 移動時間
	const float FADE_ADDOUT	= 0.2f;	// アウトのα値増加量
	const float FADE_SUBIN	= 3.0f;	// インのα値減少量

	namespace title
	{	
		const char*	FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const char*	PATH = "data\\TXT\\TEXT\\naming.txt";	// テキストパス
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 42.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 54.0f;	// 行間縦幅

		const VECTOR3	POS = VECTOR3(270.0f, 130.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;			// 向き
		const COLOR		COL = color::White();		// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;		// 横配置
		const EAlignY	ALIGN_Y = YALIGN_CENTER;	// 縦配置
	}

	namespace name
	{
		const char*	FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC	= false;		// イタリック
		const float	INIT_HEIGHT	= 42.0f;	// 初期文字縦幅
		const float	DEST_HEIGHT	= 148.0f;	// 目標文字縦幅
		const float	DEST_POSY	= 385.0f;	// 目標位置Y
		const float	NEXT_TIME	= 0.035f;	// 文字振動の待機時間
		const float WAIT_TIME	= 0.018f;	// 振動の待機時間
		const float	MOVE_POS	= 1.5f;		// 位置のランダム振動量
		const float MOVE_ROT	= 0.011f;	// 向きのランダム変動量

		const VECTOR3	INIT_POS = VECTOR3(360.0f, 155.0f, 0.0f);	// 初期位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}

	namespace select
	{
		const char*	FONT		= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const char* STRING[]	= { "いいえ", "はい" };		// 選択肢文字列
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 42.0f;	// 文字縦幅
		const float	LINE_WIDTH	= 500.0f;	// 列間縦幅

		const VECTOR3 POS = VECTOR3(180.0f, 615.0f, 0.0f);	// 位置
		const VECTOR3 ROT = VEC3_ZERO;				// 向き
		const COLOR COL_DEFAULT	= color::White();	// 通常色
		const COLOR COL_CHOICE	= color::Yellow();	// 選択色
		const EAlignX ALIGN_X	= XALIGN_LEFT;		// 横配置
	}
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(select::STRING) == CNearNameManager::SELECT_MAX, "ERROR : Array Count Mismatch");

//************************************************************
//	親クラス [CNearNameManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CNearNameManager::CNearNameManager() :
	m_pTitle		(nullptr),	// タイトル
	m_pName			(nullptr),	// 名前
	m_nCurSelect	(0),		// 現在の選択肢
	m_nOldSelect	(0),		// 前回の選択肢
	m_fCurTimeShake	(0.0f),		// 現在の振動の経過時間
	m_fCurTimeMove	(0.0f),		// 現在の移動の経過時間
	m_fNameDestPosX	(0.0f),		// 名前の目標位置X
	m_bMove			(false)		// 名前の移動状況
{
	// メンバ変数をクリア
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢
}

//============================================================
//	デストラクタ
//============================================================
CNearNameManager::~CNearNameManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CNearNameManager::Init()
{
	// メンバ変数を初期化
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢
	m_pTitle		= nullptr;	// タイトル
	m_pName			= nullptr;	// 名前
	m_nCurSelect	= 0;		// 現在の選択肢
	m_nOldSelect	= 0;		// 前回の選択肢
	m_fCurTimeShake	= 0.0f;		// 現在の振動の経過時間
	m_fCurTimeMove	= 0.0f;		// 現在の移動の経過時間
	m_fNameDestPosX	= 0.0f;		// 名前の目標位置X
	m_bMove			= true;		// 名前の移動状況

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

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pTitle->SetPriority(PRIORITY);

	// 名前の生成
	m_pName = CShakeString2D::Create
	( // 引数
		name::FONT,			// フォントパス
		name::ITALIC,		// イタリック
		L"",				// 指定文字列
		name::INIT_POS,		// 原点位置
		name::NEXT_TIME,	// 文字振動の待機時間
		name::MOVE_POS,		// 振動移動量
		name::INIT_HEIGHT,	// 文字縦幅
		name::ALIGN_X,		// 横配置
		name::ROT,			// 原点向き
		name::COL			// 色
	);
	if (m_pName == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pName->SetPriority(PRIORITY);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 文字位置オフセット
		VECTOR3 offset = VECTOR3(select::LINE_WIDTH * i, 0.0f, 0.0f);

		// 選択肢の生成
		m_apSelect[i] = CString2D::Create
		( // 引数
			select::FONT,			// フォントパス
			select::ITALIC,			// イタリック
			select::STRING[i],		// 指定文字列
			select::POS + offset,	// 原点位置
			select::CHAR_HEIGHT,	// 文字縦幅
			select::ALIGN_X,		// 横配置
			select::ROT,			// 原点向き
			select::COL_DEFAULT		// 色
		);

		// 優先順位を設定
		m_apSelect[i]->SetPriority(PRIORITY);
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CNearNameManager::Uninit()
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
}

//============================================================
//	更新処理
//============================================================
CNearNameManager::ESelect CNearNameManager::Update(const float fDeltaTime)
{
	// 名前の移動
	MoveName(fDeltaTime);

	// 名前の振動
	ShakeName(fDeltaTime);

	if (!GET_MANAGER->GetFade()->IsFade())
	{ // フェードしていない場合

		// 選択の更新
		UpdateSelect();

		// 決定の更新
		return UpdateDecide();
	}

	return SELECT_NONE;
}

//============================================================
//	ゲーム画面の遷移処理
//============================================================
void CNearNameManager::TransGame()
{
	CUserDataManager* pUserData = CUserDataManager::GetInstance();	// ユーザーデータマネージャー
	CPlayerStatus status;	// ステータス情報
	CPlayerItem item;		// 所持アイテム情報

	// ユーザーデータがない場合エラー
	assert(pUserData != nullptr);

	// タイトルの終了
	SAFE_UNINIT(m_pTitle);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択肢の終了
		SAFE_UNINIT(m_apSelect[i]);
	}

	// 内部データの初期化
	pUserData->InitAllData(&status, &item);

	// 作成した名前の設定
	status.SetName(m_pName->GetStr());

	// 内部データの書き出し
	pUserData->SaveAllData(&status, &item);

	// 逆シンバルを再生
	PLAY_SOUND(CSound::LABEL_SE_CYMBAL);

	// ゲーム画面に遷移する
	GET_MANAGER->SetFadeScene(CScene::MODE_GAME, 0.0f, FADE_ADDOUT, FADE_SUBIN, color::White(0.0f));
}

//============================================================
//	生成処理
//============================================================
CNearNameManager* CNearNameManager::Create
(
	const std::string& rName,					// 表示名
	const std::vector<std::wstring>& rVecStr	// タイトル割当テキスト
)
{
	// 名前接近マネージャーの生成
	CNearNameManager* pNearNameManager = new CNearNameManager;
	if (pNearNameManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 名前接近マネージャーの初期化
		if (FAILED(pNearNameManager->Init()))
		{ // 初期化に失敗した場合

			// 名前接近マネージャーの破棄
			SAFE_DELETE(pNearNameManager);
			return nullptr;
		}

		// 名前を設定
		pNearNameManager->SetName(rName);

		// タイトルテキストを割当
		loadtext::BindText(pNearNameManager->m_pTitle, rVecStr);

		// 確保したアドレスを返す
		return pNearNameManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CNearNameManager::Release(CNearNameManager*& prNearNameManager)
{
	// 名前接近マネージャーの終了
	assert(prNearNameManager != nullptr);
	prNearNameManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prNearNameManager);
}

//============================================================
//	選択の更新処理
//============================================================
void CNearNameManager::UpdateSelect()
{
	CInputKeyboard* pKey = GET_INPUTKEY;	// キーボード情報

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
CNearNameManager::ESelect CNearNameManager::UpdateDecide()
{
	if (input::Decide())
	{
		// 現在の選択肢を返す
		return (ESelect)m_nCurSelect;
	}

	// 選択無しを返す
	return SELECT_NONE;
}

//============================================================
//	名前の振動処理
//============================================================
void CNearNameManager::ShakeName(const float fDeltaTime)
{
	// 現在の待機時間を加算
	m_fCurTimeShake += fDeltaTime;
	if (m_fCurTimeShake >= name::WAIT_TIME)
	{ // 待機し終わった場合

		VECTOR3 rotName = VEC3_ZERO;				// 名前向き
		float fRefRand = (float)(rand() % 3 - 1);	// ランダム参照値

		// 現在の待機時間を初期化
		m_fCurTimeShake = 0.0f;

		// 向きをランダムに振動させる
		rotName.z = name::MOVE_ROT * fRefRand;	// ランダム向きを計算
		m_pName->SetVec3Rotation(rotName);		// 名前向きを反映
	}
}

//============================================================
//	名前の移動状態の更新処理
//============================================================
void CNearNameManager::MoveName(const float fDeltaTime)
{
	// 移動しない状況なら抜ける
	if (!m_bMove) { return; }

	// 経過時刻の割合を計算
	float fRate = easing::Liner(m_fCurTimeMove, 0.0f, MOVE_TIME);

	// 目標への差分を計算
	VECTOR3 posDest = VECTOR3(m_fNameDestPosX, name::DEST_POSY, 0.0f);	// 目標位置
	VECTOR3 posDiff = posDest - name::INIT_POS;					// 差分位置
	float fHeightDiff = name::DEST_HEIGHT - name::INIT_HEIGHT;	// 差分縦幅

	// 経過時刻を進める
	m_fCurTimeMove += fDeltaTime;
	if (useful::LimitMaxNum(m_fCurTimeMove, MOVE_TIME))
	{ // 移動しきった場合

		// 移動を停止
		m_bMove = false;
	}

	// 現在位置を反映
	m_pName->SetVec3Position(name::INIT_POS + posDiff * fRate);

	// 現在縦幅を反映
	m_pName->SetCharHeight(name::INIT_HEIGHT + fHeightDiff * fRate);
}

//============================================================
//	名前の設定処理
//============================================================
void CNearNameManager::SetName(const std::string& rName)
{
	// 命名中の名前を設定
	m_pName->SetString(rName);

	// 名前の目標X座標を計算
	float fDestStrWidth = m_pName->GetStrWidth() * (name::DEST_HEIGHT / name::INIT_HEIGHT);	// 文字列の目標横幅
	m_fNameDestPosX = SCREEN_CENT.x - fDestStrWidth * 0.5f;
}
