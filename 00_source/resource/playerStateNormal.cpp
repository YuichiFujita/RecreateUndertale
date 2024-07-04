//============================================================
//
//	通常状態処理 [playerStateNormal.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "playerStateNormal.h"
#include "player.h"
#include "manager.h"

// TODO
#include "tileColl.h"
#include "tileTrans.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const float	MOVE = 260.0f;	// 移動量
}

//************************************************************
//	子クラス [CPlayerStateNormal] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPlayerStateNormal::CPlayerStateNormal() :
	m_move		(VEC3_ZERO),	// 移動量
	m_moveAngle	((EAngle)0)		// 移動方向

{

}

//============================================================
//	デストラクタ
//============================================================
CPlayerStateNormal::~CPlayerStateNormal()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CPlayerStateNormal::Init(void)
{
	// メンバ変数を初期化
	m_move		= VEC3_ZERO;	// 移動量
	m_moveAngle	= ANGLE_DOWN;	// 移動方向

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CPlayerStateNormal::Uninit(void)
{
	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
int CPlayerStateNormal::Update(const float fDeltaTime)
{
	// プレイヤー位置を取得
	D3DXVECTOR3 posPlayer = m_pContext->GetVec3Position();

	// 移動の操作
	int nCurMotion = ControlMove();	// 現在のモーション取得

	// 位置の更新
	UpdatePosition(posPlayer, fDeltaTime);

	// TODO
	// 判定タイルとの当たり判定
	CTileColl::CollisionTile(posPlayer, m_pContext->GetOldPosition(), (m_pContext->GetVec3Sizing() + D3DXVECTOR3(0.0f, 0.0f, 50.0f)) * 0.5f);

	// TODO
	// 遷移タイルとの当たり判定
	CTileTrans::CollisionTile(posPlayer, (m_pContext->GetVec3Sizing() + D3DXVECTOR3(0.0f, 0.0f, 50.0f)) * 0.5f);

	// プレイヤー位置を反映
	m_pContext->SetVec3Position(posPlayer);

	// 現在のモーションを返す
	return nCurMotion;
}

//============================================================
//	移動の操作処理
//============================================================
int CPlayerStateNormal::ControlMove(void)
{
	if (GET_INPUTKEY->IsPress(DIK_UP))
	{
		if (GET_INPUTKEY->IsPress(DIK_LEFT))
		{
			// 移動量を設定
			m_move.x += sinf(-D3DX_PI * 0.25f) * MOVE;
			m_move.y += cosf(-D3DX_PI * 0.25f) * MOVE;

			// 前回の移動方向に応じてモーションを返す
			if (m_moveAngle == ANGLE_LEFT)	{ return CPlayer::MOTION_MOVE_L; }	// 前回が左移動なら左移動モーション
			else							{ return CPlayer::MOTION_MOVE_U; }	// それ以外なら上移動モーション
		}
		else if (GET_INPUTKEY->IsPress(DIK_RIGHT))
		{
			// 移動量を設定
			m_move.x -= sinf(-D3DX_PI * 0.75f) * MOVE;
			m_move.y -= cosf(-D3DX_PI * 0.75f) * MOVE;

			// 前回の移動方向に応じてモーションを返す
			if (m_moveAngle == ANGLE_RIGHT)	{ return CPlayer::MOTION_MOVE_R; }	// 前回が右移動なら右移動モーション
			else							{ return CPlayer::MOTION_MOVE_U; }	// それ以外なら上移動モーション
		}
		else
		{
			// 移動量を設定
			m_move.x += sinf(0.0f) * MOVE;
			m_move.y += cosf(0.0f) * MOVE;

			// 上移動を保存
			m_moveAngle = ANGLE_UP;

			// 上移動モーションを返す
			return CPlayer::MOTION_MOVE_U;
		}
	}
	else if (GET_INPUTKEY->IsPress(DIK_DOWN))
	{
		if (GET_INPUTKEY->IsPress(DIK_LEFT))
		{
			// 移動量を設定
			m_move.x += sinf(-D3DX_PI * 0.75f) * MOVE;
			m_move.y += cosf(-D3DX_PI * 0.75f) * MOVE;

			// 前回の移動方向に応じてモーションを返す
			if (m_moveAngle == ANGLE_LEFT)	{ return CPlayer::MOTION_MOVE_L; }	// 前回が左移動なら左移動モーション
			else							{ return CPlayer::MOTION_MOVE_D; }	// それ以外なら下移動モーション
		}
		else if (GET_INPUTKEY->IsPress(DIK_RIGHT))
		{
			// 移動量を設定
			m_move.x -= sinf(-D3DX_PI * 0.25f) * MOVE;
			m_move.y -= cosf(-D3DX_PI * 0.25f) * MOVE;

			// 前回の移動方向に応じてモーションを返す
			if (m_moveAngle == ANGLE_RIGHT)	{ return CPlayer::MOTION_MOVE_R; }	// 前回が右移動なら右移動モーション
			else							{ return CPlayer::MOTION_MOVE_D; }	// それ以外なら下移動モーション
		}
		else
		{
			// 移動量を設定
			m_move.x -= sinf(0.0f) * MOVE;
			m_move.y -= cosf(0.0f) * MOVE;

			// 下移動を保存
			m_moveAngle = ANGLE_DOWN;

			// 下移動モーションを返す
			return CPlayer::MOTION_MOVE_D;
		}
	}
	else if (GET_INPUTKEY->IsPress(DIK_LEFT))
	{
		// 移動量を設定
		m_move.x += sinf(-D3DX_PI * 0.5f) * MOVE;
		m_move.y += cosf(-D3DX_PI * 0.5f) * MOVE;

		// 左移動を保存
		m_moveAngle = ANGLE_LEFT;

		// 左移動モーションを返す
		return CPlayer::MOTION_MOVE_L;
	}
	else if (GET_INPUTKEY->IsPress(DIK_RIGHT))
	{
		// 移動量を設定
		m_move.x -= sinf(-D3DX_PI * 0.5f) * MOVE;
		m_move.y -= cosf(-D3DX_PI * 0.5f) * MOVE;

		// 右移動を保存
		m_moveAngle = ANGLE_RIGHT;

		// 右移動モーションを返す
		return CPlayer::MOTION_MOVE_R;
	}

	// 前回移動した方向の待機モーションを返す
	return (CPlayer::EMotion)m_moveAngle;
}

//============================================================
//	位置の更新処理
//============================================================
void CPlayerStateNormal::UpdatePosition(D3DXVECTOR3& rPosPlayer, const float fDeltaTime)
{
	// プレイヤーを移動させる
	rPosPlayer += m_move * fDeltaTime;

	// 移動量を初期化
	m_move = VEC3_ZERO;
}
