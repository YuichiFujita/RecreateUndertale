//============================================================
//
//	ソウル点滅状態処理 [gameStateEncountBlink.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "gameStateEncountBlink.h"
#include "gameManager.h"
#include "sceneGame.h"
#include "object2D.h"
#include "object3D.h"
#include "player.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const float MOVE_TIME  = 0.6f;	// ソウルの移動時間
	const float BLINK_TIME = 0.08f;	// 点滅を切り替える時間
	const float BLINK_NUM  = 4;		// 点滅の回数

	namespace soul
	{
		const char*		PATH		= "data\\TEXTURE\\spr_heartsmall.png";	// ソウルのテクスチャパス
		const int		PRIORITY	= 6;									// ソウルの優先順位
		const VECTOR3	OFFSET		= VECTOR3(0.0f, -35.0f, 0.0f);			// ソウルのオフセット
		const VECTOR3	SIZE		= VECTOR3(26.5f, 26.5f, 0.0f);			// ソウルの大きさ
	}

	namespace bg
	{
		const int		PRIORITY	= 3;									// 背景の優先順位
		const VECTOR3	SIZE		= VECTOR3(1280.0f, 1280.0f, -50.0f);	// 背景の大きさ
	}
}

//************************************************************
//	子クラス [CGameStateEncountBlink] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CGameStateEncountBlink::CGameStateEncountBlink() :
	m_pSoul		(nullptr),		// ソウル情報
	m_posInit	(VEC3_ZERO),	// 初期位置
	m_fCurTime	(0.0f),			// 現在の待機時間
	m_nNumBlink	(0)				// 点滅カウント
{

}

//============================================================
//	デストラクタ
//============================================================
CGameStateEncountBlink::~CGameStateEncountBlink()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CGameStateEncountBlink::Init()
{
	// メンバ変数を初期化
	m_pSoul		= nullptr;		// ソウル情報
	m_posInit	= VEC3_ZERO;	// 初期位置
	m_fCurTime	= 0.0f;			// 現在の待機時間
	m_nNumBlink	= 0;			// 点滅カウント

	CPlayer* pPlayer = CSceneGame::GetPlayer();	// プレイヤー情報
	VECTOR3  posInit3D, posPlayer, rotPlayer;	// 2D座標変換情報
	if (pPlayer != nullptr)
	{
		// プレイヤー位置/向きを取得
		posPlayer = pPlayer->GetVec3Position();
		rotPlayer = pPlayer->GetVec3Rotation();

		// X座標オフセット分ずらす
		posInit3D.x = posPlayer.x + sinf(rotPlayer.z + HALF_PI) * soul::OFFSET.x;
		posInit3D.y = posPlayer.y + cosf(rotPlayer.z + HALF_PI) * soul::OFFSET.x;

		// Y座標オフセット分ずらす
		posInit3D.x = posPlayer.x + sinf(rotPlayer.z) * soul::OFFSET.y;
		posInit3D.y = posPlayer.y + cosf(rotPlayer.z) * soul::OFFSET.y;

		// 3D座標を2D座標に変換
		m_posInit = useful::Position3DToPosition2D(posInit3D, rotPlayer);
	}

	// ソウルの生成
	m_pSoul = CObject2D::Create
	( // 引数
		m_posInit,	// 位置
		soul::SIZE	// 大きさ
	);
	if (m_pSoul == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ソウルテクスチャを割当
	m_pSoul->BindTexture(soul::PATH);

	// ラベルを設定
	m_pSoul->SetLabel(CObject::LABEL_UI);

	// 優先順位を設定
	m_pSoul->SetPriority(soul::PRIORITY);

	// TODO：Z座標どうするか決める
	// 黒背景の生成
	VECTOR3    posBG    = VECTOR3(posPlayer.x, posPlayer.y, -50.0f);	// 背景位置
	CObject3D* pBlackBG = CObject3D::Create
	( // 引数
		posBG,			// 位置
		bg::SIZE,		// 大きさ
		VEC3_ZERO,		// 向き
		color::Black()	// 色
	);
	if (pBlackBG == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ラベルを設定
	pBlackBG->SetLabel(CObject::LABEL_UI);

	// 優先順位を設定
	pBlackBG->SetPriority(bg::PRIORITY);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CGameStateEncountBlink::Uninit()
{
	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CGameStateEncountBlink::Update(const float fDeltaTime)
{
	// 待機時刻を進める
	m_fCurTime += fDeltaTime;

	if (m_nNumBlink < BLINK_NUM)
	{ // 点滅中の場合

		if (m_fCurTime >= BLINK_TIME)
		{ // 待機終了した場合

			// 待機時間を初期化
			m_fCurTime = 0.0f;

			// 点滅回数の加算
			m_nNumBlink++;

			// ソウルの表示を切り替え
			m_pSoul->SetEnableDraw(!m_pSoul->IsDraw());

			if (m_nNumBlink >= BLINK_NUM)
			{ // 点滅中の場合

				CPlayer* pPlayer = CSceneGame::GetPlayer();	// プレイヤー情報
				if (pPlayer != nullptr)
				{
					// プレイヤーの自動描画をOFFにする
					pPlayer->SetEnableDraw(false);
				}
			}
		}
	}
	else
	{ // 点滅終了した場合

		// TODO：ソウルの移動
		const VECTOR3 DEST_POS = VECTOR3(60.0f, 640.0f, 0.0f);

		// 経過時刻の割合を計算
		float fRate = easing::Liner(m_fCurTime, 0.0f, MOVE_TIME);

		// 目標位置への差分を計算
		VECTOR3 posDiff = DEST_POS - m_posInit;

		if (useful::LimitMaxNum(m_fCurTime, MOVE_TIME))
		{ // 移動しきった場合

			// TODO：ここで遷移
		}

		// ソウル位置を反映
		m_pSoul->SetVec3Position(m_posInit + posDiff * fRate);
	}
}
