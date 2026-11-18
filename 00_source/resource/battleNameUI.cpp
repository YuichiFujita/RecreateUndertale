//============================================================
//
//	戦闘時の名前表示処理 [battleNameUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "battleNameUI.h"
#include "string2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int     PRIORITY	= 6;							// 戦闘時の名前表示の優先順位
	const VECTOR3 POS		= VECTOR3(48.0f, 616.0f, 0.0f);	// 位置

	namespace text
	{
		const bool		ITALIC	= false;			// イタリック
		const VECTOR3	ROT		= VEC3_ZERO;		// 向き
		const COLOR		COL		= color::White();	// 色
		const EAlignX	ALIGN_X	= XALIGN_LEFT;		// 横配置

		namespace name
		{
			const char*	FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
			const float	HEIGHT	= 25.0f;									// 文字縦幅
		}

		namespace love
		{
			const char*		FONT		= "data\\FONT\\Mars Needs Cunnilingus.ttf";	// フォントパス
			const char*		LV_FORMAT	= "LV ";									// LV表示フォーマット
			const float		HEIGHT		= 36.0f;									// 文字縦幅
			const VECTOR3	OFFSET		= VECTOR3(40.0f, 2.0f, 0.0f);				// オフセット
		}
	}
}

//************************************************************
//	子クラス [CBattleNameUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBattleNameUI::CBattleNameUI() : CObject(CObject::LABEL_UI, CObject::DIM_2D, CObject::DEFAULT_PRIO),
	m_pName	(nullptr),		// 名前情報
	m_pLv	(nullptr),		// LV情報
	m_pos	(VEC3_ZERO),	// 原点位置
	m_rot	(VEC3_ZERO)		// 原点向き
{

}

//============================================================
//	デストラクタ
//============================================================
CBattleNameUI::~CBattleNameUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBattleNameUI::Init()
{
	// メンバ変数を初期化
	m_pName	= nullptr;		// 名前情報
	m_pLv	= nullptr;		// LV情報
	m_pos	= VEC3_ZERO;	// 原点位置
	m_rot	= VEC3_ZERO;	// 原点向き

	// 名前の生成
	m_pName = CString2D::Create
	( // 引数
		text::name::FONT,	// フォントパス
		text::ITALIC,		// イタリック
		"",					// 指定文字列
		VEC3_ZERO,			// 原点位置
		text::name::HEIGHT,	// 文字縦幅
		text::ALIGN_X		// 横配置
	);
	if (m_pName == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ラベルを設定
	m_pName->SetLabel(CObject::LABEL_NONE);

	// 自動更新・自動描画をOFFにする
	m_pName->SetEnableUpdate(false);
	m_pName->SetEnableDraw(false);

	// LVの生成
	m_pLv = CString2D::Create
	( // 引数
		text::love::FONT,	// フォントパス
		text::ITALIC,		// イタリック
		"",					// 指定文字列
		VEC3_ZERO,			// 原点位置
		text::love::HEIGHT,	// 文字縦幅
		text::ALIGN_X		// 横配置
	);
	if (m_pLv == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ラベルを設定
	m_pLv->SetLabel(CObject::LABEL_NONE);

	// 自動更新・自動描画をOFFにする
	m_pLv->SetEnableUpdate(false);
	m_pLv->SetEnableDraw(false);

	// 優先順位を設定
	SetPriority(PRIORITY);

	// 位置を設定
	SetVec3Position(POS);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBattleNameUI::Uninit()
{
	// 名前の終了
	SAFE_UNINIT(m_pName);

	// LVの終了
	SAFE_UNINIT(m_pLv);

	// 自身のオブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CBattleNameUI::Update(const float fDeltaTime)
{
	// 名前の更新
	m_pName->Update(fDeltaTime);

	// LVの更新
	m_pLv->Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CBattleNameUI::Draw(CShader* pShader)
{
	// 名前の描画
	m_pName->Draw(pShader);

	// LVの描画
	m_pLv->Draw(pShader);
}

//============================================================
//	優先順位の設定処理
//============================================================
void CBattleNameUI::SetPriority(const int nPriority)
{
	// 引数の優先順位を設定
	CObject::SetPriority(nPriority);	// 自身
	m_pName->SetPriority(nPriority);	// 名前
	m_pLv->SetPriority(nPriority);		// LV
}

//============================================================
//	位置の設定処理
//============================================================
void CBattleNameUI::SetVec3Position(const VECTOR3& rPos)
{
	// 引数の位置を設定
	m_pos = rPos;

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	向きの設定処理
//============================================================
void CBattleNameUI::SetVec3Rotation(const VECTOR3& rRot)
{
	// 設定する向きを保存
	m_rot = rRot;

	// オブジェクト向きの設定
	m_pName->SetVec3Rotation(rRot);	// 名前
	m_pLv->SetVec3Rotation(rRot);	// LV

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	生成処理 (マルチバイト文字列)
//============================================================
CBattleNameUI* CBattleNameUI::Create
(
	const std::string& rName,	// 名前
	const int nLv				// LV
)
{
	// 戦闘時の名前表示の生成
	CBattleNameUI* pBattleNameUI = new CBattleNameUI;
	if (pBattleNameUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 戦闘時の名前表示の初期化
		if (FAILED(pBattleNameUI->Init()))
		{ // 初期化に失敗した場合

			// 戦闘時の名前表示の破棄
			SAFE_DELETE(pBattleNameUI);
			return nullptr;
		}

		// 名前を設定
		pBattleNameUI->SetName(rName);

		// LVを設定
		pBattleNameUI->SetLv(nLv);

		// 確保したアドレスを返す
		return pBattleNameUI;
	}
}

//============================================================
//	生成処理 (ワイド文字列)
//============================================================
CBattleNameUI* CBattleNameUI::Create
(
	const std::wstring& rName,	// 名前
	const int nLv				// LV
)
{
	// 戦闘時の名前表示の生成
	CBattleNameUI* pBattleNameUI = new CBattleNameUI;
	if (pBattleNameUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 戦闘時の名前表示の初期化
		if (FAILED(pBattleNameUI->Init()))
		{ // 初期化に失敗した場合

			// 戦闘時の名前表示の破棄
			SAFE_DELETE(pBattleNameUI);
			return nullptr;
		}

		// 名前を設定
		pBattleNameUI->SetName(rName);

		// LVを設定
		pBattleNameUI->SetLv(nLv);

		// 確保したアドレスを返す
		return pBattleNameUI;
	}
}

//============================================================
//	名前の設定処理 (マルチバイト文字列)
//============================================================
HRESULT CBattleNameUI::SetName(const std::string& rName)
{
	// 文字列をワイド変換
	std::wstring wsStr = useful::MultiByteToWide(rName);

	// 名前を設定
	if (FAILED(SetName(wsStr)))
	{ // 設定に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	名前の設定処理 (ワイド文字列)
//============================================================
HRESULT CBattleNameUI::SetName(const std::wstring& rName)
{
	// 名前の設定
	if (FAILED(m_pName->SetString(rName)))
	{
		assert(false);
		return E_FAIL;
	}

	// 相対位置の設定
	SetPositionRelative();

	return S_OK;
}

//============================================================
//	LVの設定処理
//============================================================
void CBattleNameUI::SetLv(const int nLv)
{
	// LV文字列の作成
	std::string sLv;
	sLv.append(text::love::LV_FORMAT);
	sLv.append(std::to_string(nLv));

	// LVの設定
	m_pLv->SetString(sLv);

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	相対位置の設定処理
//============================================================
void CBattleNameUI::SetPositionRelative()
{
	VECTOR3 posLv  = m_pos;		// LVの位置
	VECTOR3 offset = VEC3_ZERO;	// 原点からのオフセット

	// 名前文字列の横幅からオフセットを計算
	offset.x = m_pName->GetStrWidth() + text::love::OFFSET.x;
	offset.y = text::love::OFFSET.y;

	// X座標オフセット分ずらす
	posLv.x += sinf(m_rot.z + HALF_PI) * offset.x;
	posLv.y += cosf(m_rot.z + HALF_PI) * offset.x;

	// Y座標オフセット分ずらす
	posLv.x += sinf(m_rot.z) * offset.y;
	posLv.y += cosf(m_rot.z) * offset.y;

	// 名前の位置を反映
	m_pName->SetVec3Position(m_pos);

	// LVの位置を反映
	m_pLv->SetVec3Position(posLv);
}
