//============================================================
//
//	吹き出し状態処理 [playerStateEncount.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "playerStateEncount.h"
#include "player.h"
#include "balloonEncount.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	namespace balloon
	{
		VECTOR2 OFFSET = VECTOR2(0.0f, 50.0f);	// オフセット
	}
}

//************************************************************
//	子クラス [CPlayerStateEncount] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPlayerStateEncount::CPlayerStateEncount()
{

}

//============================================================
//	デストラクタ
//============================================================
CPlayerStateEncount::~CPlayerStateEncount()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CPlayerStateEncount::Init()
{
	// メンバ変数を初期化
	m_pEncount = nullptr;	// エンカウント吹き出し

	// エンカウント吹き出しの生成
	VECTOR3 pos = m_pContext->GetVec3Position();	// プレイヤー位置
	VECTOR3 rot = m_pContext->GetVec3Rotation();	// プレイヤー向き
	m_pEncount = CBalloonEncount::Create(CBalloonEncount::EType::TYPE_ENCOUNT, pos, rot, balloon::OFFSET);
	if (m_pEncount == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CPlayerStateEncount::Uninit()
{
	// エンカウント吹き出しの終了
	SAFE_UNINIT(m_pEncount);

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
int CPlayerStateEncount::Update(const float fDeltaTime)
{
	// 現在向きの待機モーションを返す
	return GetIdolMotionType();
}

//============================================================
//	現在向きの待機モーション取得処理
//============================================================
CPlayer::EMotion CPlayerStateEncount::GetIdolMotionType() const
{
	CPlayer::EAngle angle = m_pContext->GetAngle();	// 向き
	switch (angle)
	{
	case CPlayer::EAngle::ANGLE_UP:
		return CPlayer::EMotion::MOTION_IDOL_U;
	case CPlayer::EAngle::ANGLE_DOWN:
		return CPlayer::EMotion::MOTION_IDOL_D;
	case CPlayer::EAngle::ANGLE_LEFT:
		return CPlayer::EMotion::MOTION_IDOL_L;
	case CPlayer::EAngle::ANGLE_RIGHT:
		return CPlayer::EMotion::MOTION_IDOL_R;
	default:
		assert(false);
		return CPlayer::EMotion::MOTION_IDOL_U;
	}
}
