//============================================================
//
//	プレイヤー処理 [player.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "player.h"
#include "manager.h"
#include "camera.h"
#include "playerState.h"
#include "userdataManager.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* SETUP_TXT	= "data\\TXT\\CHARACTER\\frisk.txt";	// プレイヤーセットアップテキスト
	const int	PRIORITY	= 4;	// プレイヤーの優先順位
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CListManager<CPlayer>* CPlayer::m_pList = nullptr;	// オブジェクトリスト

//************************************************************
//	子クラス [CPlayer] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPlayer::CPlayer() : CObjectCharaAnim3D(CObject::LABEL_PLAYER, CObject::DIM_3D, PRIORITY),
	m_status ({}),			// ステータス情報
	m_item	 ({}),			// アイテム情報
	m_pState (nullptr),		// 状態
	m_oldPos (VEC3_ZERO),	// 過去位置
	m_angle	 ((EAngle)0)	// 向き
{

}

//============================================================
//	デストラクタ
//============================================================
CPlayer::~CPlayer()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CPlayer::Init()
{
	CUserDataManager* pUserData = CUserDataManager::GetInstance();	// ユーザーデータ情報

	// メンバ変数を初期化
	m_status = {};			// ステータス情報
	m_item	 = {};			// アイテム情報
	m_pState = nullptr;		// 状態
	m_oldPos = VEC3_ZERO;	// 過去位置
	m_angle	 = ANGLE_DOWN;	// 向き

	// 通常状態にする
	ChangeState(new CPlayerStateNormal);

	// オブジェクトキャラクターアニメーション3Dの初期化
	if (FAILED(CObjectCharaAnim3D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// キャラクター情報の割当
	BindCharaData(SETUP_TXT);

	// ステータスの読込
	if (FAILED(pUserData->LoadPlayerStatus(&m_status)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 所持アイテムの読込
	if (FAILED(pUserData->LoadPlayerItem(&m_item)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	if (m_pList == nullptr)
	{ // リストマネージャーが存在しない場合

		// リストマネージャーの生成
		m_pList = CListManager<CPlayer>::Create();
		if (m_pList == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}
	}

	// リストに自身のオブジェクトを追加・イテレーターを取得
	m_iterator = m_pList->AddList(this);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CPlayer::Uninit()
{
	// 状態の終了
	SAFE_UNINIT(m_pState);

	// リストから自身のオブジェクトを削除
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // オブジェクトが一つもない場合

		// リストマネージャーの破棄
		m_pList->Release(m_pList);
	}

	// オブジェクトキャラクターアニメーション3Dの終了
	CObjectCharaAnim3D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CPlayer::Update(const float fDeltaTime)
{
	// 過去位置の更新
	UpdateOldPosition();

	// 状態ごとの更新
	assert(m_pState != nullptr);
	int nCurMotion = m_pState->Update(fDeltaTime);	// 現在のモーション取得

	// モーション・キャラクター2Dの更新
	UpdateMotion(nCurMotion, fDeltaTime);

	// 位置表示
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[プレイヤー位置]：%f %f %f", GetVec3Position().x, GetVec3Position().y, GetVec3Position().z);
}

//============================================================
//	描画処理
//============================================================
void CPlayer::Draw(CShader* pShader)
{
	// オブジェクトキャラクターアニメーション3Dの描画
	CObjectCharaAnim3D::Draw(pShader);
}

//============================================================
//	状態の変更処理
//============================================================
HRESULT CPlayer::ChangeState(CPlayerState* pState)
{
	// 状態の生成に失敗している場合抜ける
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// 状態インスタンスを終了
	SAFE_UNINIT(m_pState);

	// 状態インスタンスを変更
	assert(m_pState == nullptr);
	m_pState = pState;

	// 状態にコンテキストを設定
	m_pState->SetContext(this);

	// 状態インスタンスを初期化
	if (FAILED(m_pState->Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	生成処理
//============================================================
CPlayer* CPlayer::Create(const VECTOR3& rPos)
{
	// プレイヤーの生成
	CPlayer* pPlayer = new CPlayer;
	if (pPlayer == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// プレイヤーの初期化
		if (FAILED(pPlayer->Init()))
		{ // 初期化に失敗した場合

			// プレイヤーの破棄
			SAFE_DELETE(pPlayer);
			return nullptr;
		}

		// 位置を設定
		pPlayer->SetVec3Position(rPos);

		// 確保したアドレスを返す
		return pPlayer;
	}
}

//============================================================
//	リスト取得処理
//============================================================
CListManager<CPlayer>* CPlayer::GetList()
{
	// オブジェクトリストを返す
	return m_pList;
}

//============================================================
//	部屋の遷移処理
//============================================================
void CPlayer::TransRoom(const VECTOR3& rPos, const EAngle angle)
{
	// 引数位置を設定
	m_oldPos = rPos;
	SetVec3Position(rPos);

	// 引数方向の待機モーションを設定
	m_angle = angle;
	SetMotion(angle);

	// 追従カメラの初期化
	GET_MANAGER->GetCamera()->InitFollow();
}

//============================================================
//	過去位置の更新処理
//============================================================
void CPlayer::UpdateOldPosition()
{
	// 過去位置を更新
	m_oldPos = GetVec3Position();
}

//============================================================
//	モーション・キャラクター2Dの更新処理
//============================================================
void CPlayer::UpdateMotion(int nCurMotion, const float fDeltaTime)
{
	// 死んでいる場合抜ける
	if (IsDeath()) { return; }

	// モーションが設定されていない場合抜ける
	if (nCurMotion == NONE_IDX) { return; }

	int nAnimMotion = GetMotion();	// 現在再生中のモーション
	if (IsLoop())
	{ // ループするモーションだった場合

		if (nAnimMotion != nCurMotion)
		{ // 現在のモーションが再生中のモーションと一致しない場合

			// 現在のモーションの設定
			SetMotion(nCurMotion);
		}
	}

	// オブジェクトキャラクターアニメーション3Dの更新
	CObjectCharaAnim3D::Update(fDeltaTime);

	switch (GetMotion())
	{ // モーションの種類ごとの処理
	case MOTION_IDOL_U:	// 上待機モーション
	case MOTION_IDOL_D:	// 下待機モーション
	case MOTION_IDOL_L:	// 左待機モーション
	case MOTION_IDOL_R:	// 右待機モーション
	case MOTION_MOVE_U:	// 上移動モーション
	case MOTION_MOVE_D:	// 下移動モーション
	case MOTION_MOVE_L:	// 左移動モーション
	case MOTION_MOVE_R:	// 右移動モーション
		break;
	}
}
