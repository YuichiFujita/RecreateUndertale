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
#include "command.h"
#include "frame2D.h"
#include "loadtext.h"
#include "frame2DModule.h"
#include "string2D.h"
#include "userdataManager.h"
#include "playerStatus.h"
#include "gauge2D.h"
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
		const char*		PATH		= "data\\TEXTURE\\spr_heart_0.png";	// ソウルのテクスチャパス
		const int		PRIO_NORMAL	= 6;								// ソウルの優先順位（通常時）
		const int		PRIO_FADE	= 8;								// ソウルの優先順位（フェード時）
		const VECTOR3	SIZE		= VECTOR3(25.5f, 25.5f, 0.0f);		// ソウルの大きさ
	}

	namespace hp
	{
		const char*		PATH		= "data\\TEXTURE\\BATTLE\\spr_hpname_0.png";	// HPのテクスチャパス
		const int		PRIORITY	= 6;											// HPの優先順位
		const VECTOR3	POS			= VECTOR3(383.5f, 615.0f, 0.0f);				// HPの位置
		const VECTOR3	SIZE		= VECTOR3(23.0f, 9.5f, 0.0f)*1.55f;				// HPの大きさ
	}

	namespace text
	{
		const int	PRIORITY	= 6;		// テキストの優先順位
		const bool	ITALIC		= false;	// イタリック

		const VECTOR3	ROT		= VEC3_ZERO;		// 向き
		const COLOR		COL		= color::White();	// 色
		const EAlignX	ALIGN_X	= XALIGN_LEFT;		// 横配置

		namespace name
		{
			const char*		FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
			const VECTOR3	POS		= VECTOR3(48.0f, 616.0f, 0.0f);				// 位置
			const float		HEIGHT	= 25.0f;									// 文字縦幅
		}

		namespace love
		{
			const char*		FONT	= "data\\FONT\\Mars Needs Cunnilingus.ttf";	// フォントパス
			const VECTOR3	POS		= VECTOR3(183.0f, 618.0f, 0.0f);			// 位置
			const float		HEIGHT	= 35.0f;									// 文字縦幅
		}
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
	// TODO：ソウルの移動
	const VECTOR3 DEST_POS = VECTOR3(72.0f, 680.0f, 0.0f);

	// ソウルの生成
	CObject2D* pSoul = CObject2D::Create
	( // 引数
		DEST_POS,	// 位置
		soul::SIZE	// 大きさ
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

	const float aX[CCommand::TYPE_MAX] = {130.0f, 363.5f, 596.5f, 830.0f};
	for (int i = 0; i < CCommand::TYPE_MAX; i++)
	{
		// コマンドの生成
		CCommand* pCommand = CCommand::Create
		( // 引数
			(CCommand::EType)i,
			VECTOR3(aX[i], 680.0f, 0.0f)
		);
		if (pCommand == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}

		if (i == 0)
		{
			pCommand->SetState(CCommand::STATE_ON);
		}
	}

	CFrame2D* pFrame = CFrame2D::Create(CFrame2D::PRESET_BATTLE_TEXT);
	pFrame->ChangeModule(new CFrame2DModuleText);
	pFrame->GetModule()->GetModuleText()->BindTextBox
	(
		"data\\TXT\\TEXTBOX\\del_test00.txt",
		"0"
	);

	// ステータスの読込
	CPlayerStatus     status;	// ステータス情報
	CUserDataManager* pUserData = CUserDataManager::GetInstance();	// ユーザーデータ情報
	if (FAILED(pUserData->LoadPlayerStatus(&status)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 名前の生成
	CString2D* pName = CString2D::Create
	( // 引数
		text::name::FONT,	// フォントパス
		text::ITALIC,		// イタリック
		status.GetName(),	// 指定文字列
		text::name::POS,	// 原点位置
		text::name::HEIGHT,	// 文字縦幅
		text::ALIGN_X,		// 横配置
		text::ROT,			// 原点向き
		text::COL			// 色
	);
	if (pName == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	pName->SetPriority(text::PRIORITY);

	// レベルの生成
	const std::string sLove = useful::SandString("", "LV ", std::to_string(status.GetLove()));	// レベル
	CString2D* pLv = CString2D::Create
	( // 引数
		text::love::FONT,	// フォントパス
		text::ITALIC,		// イタリック
		sLove,				// 指定文字列
		VECTOR3(text::name::POS.x + pName->GetStrWidth() + 40.0f, text::love::POS.y, 0.0f),	// 原点位置
		text::love::HEIGHT,	// 文字縦幅
		text::ALIGN_X,		// 横配置
		text::ROT,			// 原点向き
		text::COL			// 色
	);
	if (pLv == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	pLv->SetPriority(text::PRIORITY);

	// HPの生成
	CObject2D* pHP = CObject2D::Create
	( // 引数
		hp::POS,	// 位置
		hp::SIZE	// 大きさ
	);
	if (pHP == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ソウルテクスチャを割当
	pHP->BindTexture(hp::PATH);

	// ラベルを設定
	pHP->SetLabel(CObject::LABEL_UI);

	// 優先順位を設定
	pHP->SetPriority(hp::PRIORITY);

#if 0
#if 0
	// TODO：Lv1
	const VECTOR3 POS  = VECTOR3(414.0f, 616.0f, 0.0f);
	const VECTOR3 SIZE = VECTOR3(18.0f, 16.0f, 0.0f);
	CGauge2D* pGauge = CGauge2D::Create(20, 1, POS + VECTOR3(SIZE.x, 0.0f, 0.0f), SIZE, color::Yellow(), color::Red());
	pGauge->AddNum(-10);
#else
	// TODO：Lv20
	const VECTOR3 POS = VECTOR3(414.0f, 616.0f, 0.0f);
	const VECTOR3 SIZE = VECTOR3(90.0f, 16.0f, 0.0f);
	CGauge2D* pGauge = CGauge2D::Create(20, 1, POS + VECTOR3(SIZE.x, 0.0f, 0.0f), SIZE, color::Yellow(), color::Red());
	pGauge->AddNum(-10);
#endif
#else
	// TODO：Lv指定
	const int LV = 1 - 1;
	const VECTOR3 POS = VECTOR3(414.0f, 616.0f, 0.0f);
	const VECTOR3 SIZE = VECTOR3(18.0f + (LV * 3.7f), 16.0f, 0.0f);
	CGauge2D* pGauge = CGauge2D::Create(20, 1, POS + VECTOR3(SIZE.x, 0.0f, 0.0f), SIZE, color::Yellow(), color::Red());
	pGauge->AddNum(-10);
#endif

	// レベルの生成
	const std::string& rHP    = std::to_string(status.GetHP());			// 現在の体力文字列
	const std::string& rMaxHP = std::to_string(status.GetMaxHP());		// 最大の体力文字列
	const std::string  sHP    = useful::SandString(rHP, " / ", rMaxHP);	// 体力文字列
	CString2D* pNum = CString2D::Create
	( // 引数
		text::love::FONT,	// フォントパス
		text::ITALIC,		// イタリック
		sHP,				// 指定文字列
		VECTOR3(POS.x + SIZE.x, text::love::POS.y, 0.0f) + VECTOR3(22.0f + SIZE.x, 0.0f, 0.0f),	// 原点位置
		text::love::HEIGHT,	// 文字縦幅
		text::ALIGN_X,		// 横配置
		text::ROT,			// 原点向き
		text::COL			// 色
	);
	if (pNum == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	pNum->SetPriority(text::PRIORITY);
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
