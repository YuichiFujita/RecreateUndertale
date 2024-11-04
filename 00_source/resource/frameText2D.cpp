//============================================================
//
//	フレームテキスト2D処理 [frameText2D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frameText2D.h"
#include "string2D.h"
#include "text2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	namespace text
	{
		const char*	FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const int	PRIORITY	= 6;		// テキストの優先順位
		const bool	ITALIC		= false;	// イタリック
		const float	CHAR_HEIGHT	= 45.0f;	// 文字縦幅
		const float	LINE_HEIGHT	= 62.0f;	// 行間縦幅
		const float	WAIT_TIME	= 0.105f;	// 文字表示の待機時間

		const VECTOR3 POS = VECTOR3(100.0f, 460.0f, 0.0f);	// テキスト位置
		const EAlignX ALIGN_X = XALIGN_LEFT;	// 横配置
		const EAlignY ALIGN_Y = YALIGN_TOP;		// 縦配置
	}
}

//************************************************************
//	子クラス [CFrameText2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrameText2D::CFrameText2D() :
	m_pText	(nullptr)	// テキスト情報
{

}

//============================================================
//	デストラクタ
//============================================================
CFrameText2D::~CFrameText2D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFrameText2D::Init()
{
	// メンバ変数を初期化
	m_pText = nullptr;	// テキスト情報

	// フレーム2Dの初期化
	if (FAILED(CFrame2D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// テキストの生成
	m_pText = CScrollText2D::Create
	( // 引数
		text::FONT,			// フォントパス
		text::ITALIC,		// イタリック
		text::POS,			// 原点位置
		text::WAIT_TIME,	// 文字表示の待機時間
		text::CHAR_HEIGHT,	// 文字縦幅
		text::LINE_HEIGHT,	// 行間縦幅
		text::ALIGN_X,		// 横配置
		text::ALIGN_Y		// 縦配置
	);
	if (m_pText == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位をフェードより上にする
	m_pText->SetPriority(GetPriority());

	// 文字送り時の再生SEを設定
	m_pText->SetScrollSE(CSound::LABEL_SE_TEXT01);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrameText2D::Uninit()
{
	// テキストの終了
	SAFE_UNINIT(m_pText);

	// フレーム2Dの終了
	CFrame2D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CFrameText2D::Update(const float fDeltaTime)
{
	// フレーム2Dの更新
	CFrame2D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CFrameText2D::Draw(CShader* pShader)
{
	// フレーム2Dの描画
	CFrame2D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CFrameText2D* CFrameText2D::Create
(
	const VECTOR3& rPos,	// 位置
	const VECTOR3& rRot,	// 向き
	const VECTOR3& rSize	// 大きさ
)
{
	// フレームテキスト2Dの生成
	CFrameText2D* pFrameText2D = new CFrameText2D;
	if (pFrameText2D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// フレームテキスト2Dの初期化
		if (FAILED(pFrameText2D->Init()))
		{ // 初期化に失敗した場合

			// フレームテキスト2Dの破棄
			SAFE_DELETE(pFrameText2D);
			return nullptr;
		}

		// 位置を設定
		pFrameText2D->SetVec3Position(rPos);

		// 向きを設定
		pFrameText2D->SetVec3Rotation(rRot);

		// 大きさを設定
		pFrameText2D->SetVec3Size(rSize);

		// 確保したアドレスを返す
		return pFrameText2D;
	}
}

//============================================================
//	テキスト変更処理
//============================================================
void CFrameText2D::ChangeText(const AText& rText)
{
	// 文字列を全て削除
	m_pText->DeleteStringAll();

	// テキストを割当
	int nLoop = (int)rText.size();	// 文字列数
	for (int i = 0; i < nLoop; i++)
	{ // 文字列の数分繰り返す

		// 文字列を最後尾に追加
		m_pText->PushBackString(rText[i]);
	}

	// 文字列を全て非表示にする
	m_pText->SetEnableScroll(true);
}
