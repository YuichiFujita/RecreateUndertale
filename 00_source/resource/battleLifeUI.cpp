//============================================================
//
//	戦闘時の体力表示処理 [battleLifeUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "battleLifeUI.h"
#include "object2D.h"
#include "gauge2D.h"
#include "string2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 6;	// 戦闘時の体力表示の優先順位

	namespace hp
	{
		const char*		PATH	= "data\\TEXTURE\\BATTLE\\spr_hpname_0.png";	// テクスチャパス
		const VECTOR3	SIZE	= VECTOR3(34.5f, 14.5f, 0.0f);					// 大きさ
	}

	namespace gauge
	{
		const int		CHANGE_FRAME	= 1;							// ゲージ変動フレーム
		const float		RATE_SIZE_X		= 0.912f;						// 最大HPから計算する横幅割合
		const float		SIZE_Y			= 16.0f;						// 縦幅
		const VECTOR3	OFFSET			= VECTOR3(12.5f, 1.0f, 0.0f);	// オフセット
		const COLOR		COL_FRONT		= color::Yellow();				// 表ゲージ色
		const COLOR		COL_BACK		= color::Red();					// 裏ゲージ色
	}

	namespace text
	{
		const char*		FONT	= "data\\FONT\\Mars Needs Cunnilingus.ttf";	// フォントパス
		const bool		ITALIC	= false;						// イタリック
		const float		HEIGHT	= 36.0f;						// 文字縦幅
		const VECTOR3	OFFSET	= VECTOR3(35.0f, 3.0f, 0.0f);	// オフセット
		const VECTOR3	ROT		= VEC3_ZERO;					// 向き
		const COLOR		COL		= color::White();				// 色
		const EAlignX	ALIGN_X	= XALIGN_LEFT;					// 横配置
	}
}

//************************************************************
//	子クラス [CBattleLifeUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBattleLifeUI::CBattleLifeUI() : CObject(CObject::LABEL_UI, CObject::DIM_2D, CObject::DEFAULT_PRIO),
	m_pHp		(nullptr),		// HP情報
	m_pGauge	(nullptr),		// HPゲージ情報
	m_pMaxHp	(nullptr),		// 最大HP情報
	m_pos		(VEC3_ZERO),	// 原点位置
	m_rot		(VEC3_ZERO)		// 原点向き
{

}

//============================================================
//	デストラクタ
//============================================================
CBattleLifeUI::~CBattleLifeUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBattleLifeUI::Init()
{
	// メンバ変数を初期化
	m_pHp		= nullptr;		// HP情報
	m_pGauge	= nullptr;		// HPゲージ情報
	m_pMaxHp	= nullptr;		// 最大HP情報
	m_pos		= VEC3_ZERO;	// 原点位置
	m_rot		= VEC3_ZERO;	// 原点向き

	// HPの生成
	m_pHp = CObject2D::Create
	( // 引数
		VEC3_ZERO,	// 位置
		hp::SIZE	// 大きさ
	);
	if (m_pHp == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ソウルテクスチャを割当
	m_pHp->BindTexture(hp::PATH);

	// ラベルを設定
	m_pHp->SetLabel(CObject::LABEL_UI);

	// HPゲージの生成
	m_pGauge = CGauge2D::Create
	( // 引数
		1,						// 最大表示値
		gauge::CHANGE_FRAME,	// 表示値変動フレーム
		VEC3_ZERO,				// 位置
		VEC3_ZERO,				// ゲージ大きさ
		gauge::COL_FRONT,		// 表ゲージ色
		gauge::COL_BACK			// 裏ゲージ色
	);
	if (m_pGauge == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 最大HPの生成
	m_pMaxHp = CString2D::Create
	( // 引数
		text::FONT,		// フォントパス
		text::ITALIC,	// イタリック
		"",				// 指定文字列
		VEC3_ZERO,		// 原点位置
		text::HEIGHT,	// 文字縦幅
		text::ALIGN_X	// 横配置
	);
	if (m_pMaxHp == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	SetPriority(PRIORITY);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBattleLifeUI::Uninit()
{
	// HPの終了
	SAFE_UNINIT(m_pHp);

	// HPゲージの終了
	SAFE_UNINIT(m_pGauge);

	// 最大HPの終了
	SAFE_UNINIT(m_pMaxHp);

	// 自身のオブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CBattleLifeUI::Update(const float fDeltaTime)
{

}

//============================================================
//	描画処理
//============================================================
void CBattleLifeUI::Draw(CShader* /*pShader*/)
{

}

//============================================================
//	優先順位の設定処理
//============================================================
void CBattleLifeUI::SetPriority(const int nPriority)
{
	// 引数の優先順位を設定
	CObject::SetPriority(nPriority);	// 自身
	m_pHp->SetPriority(nPriority);		// HP
	m_pGauge->SetPriority(nPriority);	// HPゲージ
	m_pMaxHp->SetPriority(nPriority);	// 最大HP
}

//============================================================
//	位置の設定処理
//============================================================
void CBattleLifeUI::SetVec3Position(const VECTOR3& rPos)
{
	// 引数の位置を設定
	m_pos = rPos;

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	向きの設定処理
//============================================================
void CBattleLifeUI::SetVec3Rotation(const VECTOR3& rRot)
{
	// 設定する向きを保存
	m_rot = rRot;

	// オブジェクト向きの設定
	m_pHp->SetVec3Rotation(rRot);		// HP
	//m_pGauge->SetVec3Rotation(rRot);	// HPゲージ	// TODO：ゲージに向きがない
	m_pMaxHp->SetVec3Rotation(rRot);	// 最大HP

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	生成処理
//============================================================
CBattleLifeUI* CBattleLifeUI::Create
(
	const int nMaxHp,		// 最大HP
	const int nNumHp,		// HP
	const VECTOR3& rPos,	// 位置
	const VECTOR3& rRot		// 向き
)
{
	// 戦闘時の体力表示の生成
	CBattleLifeUI* pBattleLifeUI = new CBattleLifeUI;
	if (pBattleLifeUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 戦闘時の体力表示の初期化
		if (FAILED(pBattleLifeUI->Init()))
		{ // 初期化に失敗した場合

			// 戦闘時の体力表示の破棄
			SAFE_DELETE(pBattleLifeUI);
			return nullptr;
		}

		// 最大HPを設定
		pBattleLifeUI->SetMaxHp(nMaxHp);

		// HPを設定
		pBattleLifeUI->SetHp(nNumHp);

		// 位置を設定
		pBattleLifeUI->SetVec3Position(rPos);

		// 向きを設定
		pBattleLifeUI->SetVec3Rotation(rRot);

		// 確保したアドレスを返す
		return pBattleLifeUI;
	}
}

//============================================================
//	HPの加算処理
//============================================================
void CBattleLifeUI::AddHp(const int nAddHp)
{
	// HPの加算
	m_pGauge->AddNum(nAddHp);

	// 最大HPの文字列設定
	SetMaxHpString(GetHp(), GetMaxHp());
}

//============================================================
//	HPの設定処理
//============================================================
void CBattleLifeUI::SetHp(const int nNumHp)
{
	// HPの設定
	m_pGauge->SetNum(nNumHp);

	// 最大HPの文字列設定
	SetMaxHpString(nNumHp, GetMaxHp());
}

//============================================================
//	最大HPの設定処理
//============================================================
void CBattleLifeUI::SetMaxHp(const int nMaxHp)
{
	// 最大HPの設定
	m_pGauge->SetMaxNum(nMaxHp);

	// 最大HPの文字列設定
	SetMaxHpString(GetHp(), nMaxHp);

	// 最大HPのゲージ大きさ設定
	SetMaxHpGaugeSize(nMaxHp);
}

//============================================================
//	HPの取得処理
//============================================================
int CBattleLifeUI::GetHp() const
{
	// HPを返す
	return m_pGauge->GetNum();
}

//============================================================
//	最大HPの取得処理
//============================================================
int CBattleLifeUI::GetMaxHp() const
{
	// 最大HPを返す
	return m_pGauge->GetMaxNum();
}

//============================================================
//	最大HPの文字列設定処理
//============================================================
void CBattleLifeUI::SetMaxHpString(const int nNumHp, const int nMaxHp)
{
	const std::string& rHp		= std::to_string(nNumHp);					// 現在の体力文字列
	const std::string& rMaxHp	= std::to_string(nMaxHp);					// 最大の体力文字列
	const std::string  sHp		= useful::SandString(rHp, " / ", rMaxHp);	// 体力文字列

	// 文字列の設定
	m_pMaxHp->SetString(sHp);
}

//============================================================
//	最大HPのゲージ大きさ設定処理
//============================================================
void CBattleLifeUI::SetMaxHpGaugeSize(const int nMaxHp)
{
	const VECTOR3 size = VECTOR3(nMaxHp * gauge::RATE_SIZE_X, gauge::SIZE_Y, 0.0f);

	// ゲージの大きさ設定
	m_pGauge->SetVec3Size(size);

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	相対位置の設定処理
//============================================================
void CBattleLifeUI::SetPositionRelative()
{
	// HPの位置を反映
	{
		VECTOR3 pos    = m_pos;		// 位置
		VECTOR3 offset = VEC3_ZERO;	// 原点からのオフセット

		// -- オフセットを計算
		// ※ 原点が中央のため、大きさの半分をずらす。
		offset.x = m_pHp->GetVec3Size().x * 0.5f;

		// X座標オフセット分ずらす
		pos.x += sinf(m_rot.z + HALF_PI) * offset.x;
		pos.y += cosf(m_rot.z + HALF_PI) * offset.x;

		// Y座標オフセット分ずらす
		pos.x += sinf(m_rot.z) * offset.y;
		pos.y += cosf(m_rot.z) * offset.y;

		// 位置を反映
		m_pHp->SetVec3Position(pos);
	}

	// HPゲージの位置を反映
	{
		VECTOR3 pos    = m_pos;			// 位置
		VECTOR3 offset = gauge::OFFSET;	// 原点からのオフセット

		// -- オフセットを計算
		// ※ HPの大きさ分ずらす。ゲージの原点が中央のため、大きさの半分をずらす。
		offset.x += m_pHp->GetVec3Size().x + m_pGauge->GetVec3Size().x;

		// X座標オフセット分ずらす
		pos.x += sinf(m_rot.z + HALF_PI) * offset.x;
		pos.y += cosf(m_rot.z + HALF_PI) * offset.x;

		// Y座標オフセット分ずらす
		pos.x += sinf(m_rot.z) * offset.y;
		pos.y += cosf(m_rot.z) * offset.y;

		// 位置を反映
		m_pGauge->SetVec3Position(pos);
	}

	// 最大HPの位置を反映
	{
		VECTOR3 pos    = m_pos;			// 位置
		VECTOR3 offset = text::OFFSET;	// 原点からのオフセット

		// -- オフセットを計算
		// ※ HPとHPゲージの大きさ分ずらす。
		offset.x += m_pHp->GetVec3Size().x + m_pGauge->GetVec3Size().x * 2.0f;

		// X座標オフセット分ずらす
		pos.x += sinf(m_rot.z + HALF_PI) * offset.x;
		pos.y += cosf(m_rot.z + HALF_PI) * offset.x;

		// Y座標オフセット分ずらす
		pos.x += sinf(m_rot.z) * offset.y;
		pos.y += cosf(m_rot.z) * offset.y;

		// 位置を反映
		m_pMaxHp->SetVec3Position(pos);
	}
}
