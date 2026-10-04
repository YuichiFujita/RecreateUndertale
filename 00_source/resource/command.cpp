//============================================================
//
//	コマンド処理 [command.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "command.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// テクスチャファイル
	{
		"data\\TEXTURE\\BATTLE\\spr_fightbt.png",	// たたかうテクスチャ
		"data\\TEXTURE\\BATTLE\\spr_talkbt.png",	// こうどうテクスチャ
		"data\\TEXTURE\\BATTLE\\spr_itembt.png",	// アイテムテクスチャ
		"data\\TEXTURE\\BATTLE\\spr_sparebt.png",	// みのがすテクスチャ
	};

	namespace command
	{
		const int		PRIORITY	= 6;							// コマンドの優先順位
		const VECTOR3	SIZE		= VECTOR3(110.0f, 42.0f, 0.0f) * 1.5f;	// 大きさ
		const POSGRID2	PTRN		= POSGRID2(1, 2);				// テクスチャ分割数
	}
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CCommand::TYPE_MAX, "ERROR : Type Count Mismatch");

//************************************************************
//	子クラス [CCommand] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CCommand::CCommand() : CAnim2D(CObject::LABEL_UI, CObject::DIM_2D, command::PRIORITY),
	m_type	(TYPE_FIGHT),	// 種類
	m_state	(STATE_OFF)		// 状態
{

}

//============================================================
//	デストラクタ
//============================================================
CCommand::~CCommand()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CCommand::Init()
{
	// メンバ変数を初期化
	m_type	= TYPE_FIGHT;	// 種類
	m_state	= STATE_OFF;	// 状態

	// アニメーション2Dの初期化
	if (FAILED(CAnim2D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 大きさの設定
	SetVec3Size(command::SIZE);

	// テクスチャ分割数の設定
	SetTexPtrn(command::PTRN);

	// アニメーションを停止
	SetEnablePlay(false);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CCommand::Uninit()
{
	// アニメーション2Dの終了
	CAnim2D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CCommand::Update(const float fDeltaTime)
{
	// アニメーション2Dの更新
	CAnim2D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CCommand::Draw(CShader* pShader)
{
	// アニメーション2Dの描画
	CAnim2D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CCommand* CCommand::Create
(
	const EType type,	// コマンド種類
	const VECTOR3& rPos	// 位置
)
{
	// コマンドの生成
	CCommand* pCommand = new CCommand;
	if (pCommand == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// コマンドの初期化
		if (FAILED(pCommand->Init()))
		{ // 初期化に失敗した場合

			// コマンドの破棄
			SAFE_DELETE(pCommand);
			return nullptr;
		}

		// コマンド種類を設定
		pCommand->SetType(type);

		// 位置を設定
		pCommand->SetVec3Position(rPos);

		// 確保したアドレスを返す
		return pCommand;
	}
}

//============================================================
//	種類の設定処理
//============================================================
void CCommand::SetType(const EType type)
{
	// 引数の種類を代入
	m_type = type;

	// テクスチャを登録・割当
	BindTexture(GET_MANAGER->GetTexture()->Regist(TEXTURE_FILE[type]));
}

//============================================================
//	値の設定処理
//============================================================
void CCommand::SetState(const EState state)
{
	// 引数の状態を代入
	m_state = state;

	// パターンの設定
	CAnim2D::SetCurPtrn((int)m_state);
}
