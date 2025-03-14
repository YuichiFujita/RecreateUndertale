//============================================================
//
//	バージョン表記処理 [version.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "version.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char*	PATH	 = "data\\TXT\\TEXT\\version.txt";		// テキストパス
	const char*	FONT	 = "data\\FONT\\Crypt of Tomorrow.ttf";	// フォントパス
	const int	PRIORITY = 6;		// 優先順位
	const bool	ITALIC	 = false;	// イタリック
	const float	HEIGHT	 = 22.5f;	// 文字縦幅

	const VECTOR3	POS = VECTOR3(SCREEN_CENT.x, 706.0f, 0.0f);	// 位置
	const VECTOR3	ROT = VEC3_ZERO;							// 向き
	const COLOR		COL = COLOR(0.5f, 0.5f, 0.5f, 1.0f);		// 色
	const EAlignX	ALIGN_X = XALIGN_CENTER;					// 横配置
}

//************************************************************
//	子クラス [CVersion] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CVersion::CVersion()
{

}

//============================================================
//	デストラクタ
//============================================================
CVersion::~CVersion()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CVersion::Init()
{
	// 文字列2Dの初期化
	if (FAILED(CString2D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// フォントを設定
	SetFont(FONT, ITALIC);

	// 原点位置を設定
	SetVec3Position(POS);

	// 色を設定
	SetColor(COL);

	// 文字縦幅を設定
	SetCharHeight(HEIGHT);

	// 横配置を設定
	SetAlignX(ALIGN_X);

	// 優先順位を設定
	SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindString(this, loadtext::LoadText(PATH, 0));

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CVersion::Uninit()
{
	// 文字列2Dの終了
	CString2D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CVersion::Update(const float fDeltaTime)
{
	// 文字列2Dの更新
	CString2D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CVersion::Draw(CShader* pShader)
{
	// 文字列2Dの描画
	CString2D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CVersion* CVersion::Create()
{
	// バージョン表記の生成
	CVersion* pVersion = new CVersion;
	if (pVersion == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// バージョン表記の初期化
		if (FAILED(pVersion->Init()))
		{ // 初期化に失敗した場合

			// バージョン表記の破棄
			SAFE_DELETE(pVersion);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pVersion;
	}
}
