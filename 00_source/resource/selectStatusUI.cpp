//============================================================
//
//	フルステータスメニュー処理 [selectStatusUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "selectStatusUI.h"
#include "loadtext.h"
#include "string2D.h"
#include "text2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *PASS = "data\\TEXT\\start.txt";	// テキストパス	// TODO：パスどう分けるか
	const int PRIORITY = 6;	// フルステータスメニューの優先順位

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(555.0f, 386.5f, 0.0f);	// フレーム位置
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// フレーム向き
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(525.0f, 600.0f, 0.0f);	// フレーム大きさ
	}

	namespace name
	{
		const char	*FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC = false;	// イタリック
		const float	HEIGHT = 42.0f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 140.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
	}
}

//************************************************************
//	子クラス [CSelectStatusUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSelectStatusUI::CSelectStatusUI(AFuncUninit funcUninit, CObject2D *pSoul) : CSelect(funcUninit, pSoul),
	m_pName		 (nullptr),	// 名前情報
	m_pLvHpTitle (nullptr),	// レベル/HPタイトル情報
	m_pLvHpValue (nullptr)	// レベル/HP数値情報
{

}

//============================================================
//	デストラクタ
//============================================================
CSelectStatusUI::~CSelectStatusUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSelectStatusUI::Init(void)
{
	// メンバ変数を初期化
	m_pName		 = nullptr;	// 名前情報
	m_pLvHpTitle = nullptr;	// レベル/HPタイトル情報
	m_pLvHpValue = nullptr;	// レベル/HP数値情報

	// セレクトの初期化
	if (FAILED(CSelect::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// フレームの位置を設定
	SetFramePosition(frame::POS);

	// フレームの向きを設定
	SetFrameRotation(frame::ROT);

	// フレームの大きさを設定
	SetFrameSizing(frame::SIZE);

	// ソウルカーソルの描画をOFFにする
	SetSoulCursorDraw(false);

	// 名前の生成
	m_pName = CString2D::Create
	( // 引数
		name::FONT,		// フォントパス
		name::ITALIC,	// イタリック
		L"",			// 指定文字列
		name::POS,		// 原点位置
		name::HEIGHT,	// 文字縦幅
		name::ALIGN_X,	// 横配置
		name::ROT,		// 原点向き
		name::COL		// 色
	);

	// 優先順位を設定
	m_pName->SetPriority(PRIORITY);

	// TODO：きもくない？
	std::wstring str;
	str.append(L"\"");
	str.append(L"おぷおぷ");
	str.append(L"\"");
	m_pName->SetString(str);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSelectStatusUI::Uninit(void)
{
	// ソウルカーソルの描画をONにする
	SetSoulCursorDraw(true);

	// セレクトの終了
	CSelect::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSelectStatusUI::Update(const float fDeltaTime)
{
	// セレクトの更新
	CSelect::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CSelectStatusUI::Draw(CShader *pShader)
{
	// セレクトの描画
	CSelect::Draw(pShader);
}
