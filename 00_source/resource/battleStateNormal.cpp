//============================================================
//
//	通常状態処理 [battleStateNormal.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "battleStateNormal.h"
#include "battleManager.h"
#include "sceneBattle.h"

// TODO：ちらつきがないかの検証
#if 1
#include "object2D.h"
#include "frame2D.h"
#include "frame2DModule.h"

#include "userdataManager.h"
#include "playerStatus.h"
#include "battleCommandUI.h"
#include "battleNameUI.h"
#include "battleLifeUI.h"
#endif

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	// TODO：ちらつきがないかの検証
#if 1
	namespace soul
	{
		// TODO：ソウルの移動
		const VECTOR3 DEST_POS = VECTOR3(72.0f, 680.0f, 0.0f);

		const char*		PATH		= "data\\TEXTURE\\spr_heart_0.png";	// ソウルのテクスチャパス
		const int		PRIO_NORMAL	= 6;								// ソウルの優先順位（通常時）
		const int		PRIO_FADE	= 8;								// ソウルの優先順位（フェード時）
		const VECTOR3	SIZE		= VECTOR3(25.5f, 25.5f, 0.0f);		// ソウルの大きさ
	}
#endif
}

//************************************************************
//	子クラス [CBattleStateNormal] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBattleStateNormal::CBattleStateNormal()
{

}

//============================================================
//	デストラクタ
//============================================================
CBattleStateNormal::~CBattleStateNormal()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBattleStateNormal::Init()
{
	// TODO：画面配置参考用
#if 0
	// 画面配置参考用オブジェクトの生成
	CObject2D* pBG = CObject2D::Create
	( // 引数
		SCREEN_CENT,		// 位置
		SCREEN_SIZE,		// 大きさ
		VEC3_ZERO,			// 向き
		color::White(0.5f)	// 色
	);
	if (pBG == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// テクスチャを割当
	pBG->BindTexture("data\\TEXTURE\\DEBUG\\test.png");

	// ラベルを設定
	pBG->SetLabel(CObject::LABEL_UI);

	// 優先順位を設定
	pBG->SetPriority(6);
#endif

	// TODO：ちらつきがないかの検証
#if 1
	// ソウルの生成
	CObject2D* pSoul = CObject2D::Create
	( // 引数
		soul::DEST_POS,	// 位置
		soul::SIZE		// 大きさ
	);
	if (pSoul == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ソウルテクスチャを割当
	pSoul->BindTexture(soul::PATH);

	// ラベルを設定
	pSoul->SetLabel(CObject::LABEL_UI);

	// 優先順位を設定
	pSoul->SetPriority(soul::PRIO_FADE);

	// テキストボックスの生成
	CFrame2D* pFrame = CFrame2D::Create(CFrame2D::PRESET_BATTLE_TEXT);
	pFrame->ChangeModule(new CFrame2DModuleText);
	pFrame->GetModule()->GetModuleText()->BindTextBox
	(
		"data\\TXT\\TEXTBOX\\del_test00.txt",
		"0"
	);

	// ステータスの読込
	CUserDataManager* pUserData = CUserDataManager::GetInstance();	// ユーザーデータ情報
	CPlayerStatus     status;	// ステータス情報
	if (FAILED(pUserData->LoadPlayerStatus(&status)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// コマンド表示の生成
	CBattleCommandUI* pCommandUI = CBattleCommandUI::Create();
	if (pCommandUI == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 名前表示の生成
	CBattleNameUI* pNameUI = CBattleNameUI::Create(status.GetName(), status.GetLove());
	if (pNameUI == nullptr)
	{ // 生成に失敗した場合
	
		assert(false);
		return E_FAIL;
	}

	// 体力表示の生成
	CBattleLifeUI* pLifeUI = CBattleLifeUI::Create(status.GetMaxHP(), status.GetHP());
	if (pLifeUI == nullptr)
	{ // 生成に失敗した場合
	
		assert(false);
		return E_FAIL;
	}
#endif

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBattleStateNormal::Uninit()
{
	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CBattleStateNormal::Update(const float fDeltaTime)
{

}
