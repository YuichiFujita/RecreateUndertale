//============================================================
//
//	テキスト表示機能処理 [frame2DModuleText.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DModuleText.h"
#include "frame2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	namespace text
	{
		const VECTOR3 OFFSET[] =	// テキストオフセットプリセット
		{
			VECTOR3(-410.0f, -80.0f, 0.0f)	// 下部配置
		};
		const char*	FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const int	PRIORITY	= 6;			// テキストの優先順位
		const bool	ITALIC		= false;		// イタリック
		const float	CHAR_HEIGHT	= 42.0f;		// 文字縦幅
		const float	LINE_HEIGHT	= 54.0f;		// 行間縦幅
		const float	WAIT_TIME	= 0.045f;		// 文字表示の待機時間
		const EAlignX ALIGN_X	= XALIGN_LEFT;	// 横配置
		const EAlignY ALIGN_Y	= YALIGN_TOP;	// 縦配置
	}
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(text::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	子クラス [CFrame2DModuleText] のメンバ関数
//************************************************************
//============================================================
//	移譲コンストラクタ (配置プリセット)
//============================================================
CFrame2DModuleText::CFrame2DModuleText(const CFrame2D::EPreset preset) : CFrame2DModuleText(text::OFFSET[preset])
{
	// プリセット範囲外エラー
	assert(preset > NONE_IDX && preset < CFrame2D::PRESET_MAX);
}

//============================================================
//	コンストラクタ (配置指定)
//============================================================
CFrame2DModuleText::CFrame2DModuleText(const VECTOR3& rOffset) :
	m_pText	 (nullptr),	// テキスト情報
	m_offset (rOffset)	// テキストオフセット
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DModuleText::~CFrame2DModuleText()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFrame2DModuleText::Init()
{
	// メンバ変数を初期化
	m_pText = nullptr;	// テキスト情報

	// テキストの生成
	m_pText = CScrollText2D::Create
	( // 引数
		text::FONT,			// フォントパス
		text::ITALIC,		// イタリック
		VEC3_ZERO,			// 原点位置
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

	// 優先順位を設定
	m_pText->SetPriority(m_pContext->GetPriority());

	// 文字送り時の再生SEを設定
	m_pText->SetScrollSE(CSound::LABEL_SE_TEXT01);

	// 相対位置の設定
	SetPositionRelative();

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrame2DModuleText::Uninit()
{
	// テキストの終了
	SAFE_UNINIT(m_pText);

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CFrame2DModuleText::Update(const float fDeltaTime)
{

}

//============================================================
//	優先順位の設定処理
//============================================================
void CFrame2DModuleText::SetPriority(const int nPriority)
{
	// テキストの優先順位を設定
	m_pText->SetPriority(nPriority);
}

//============================================================
//	位置の設定処理
//============================================================
void CFrame2DModuleText::SetVec3Position(const VECTOR3& /*rPos*/)
{
	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	向きの設定処理
//============================================================
void CFrame2DModuleText::SetVec3Rotation(const VECTOR3& rRot)
{
	// テキストの向きを設定
	m_pText->SetVec3Rotation(rRot);

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	テキスト変更処理
//============================================================
void CFrame2DModuleText::ChangeText(const AText& rText)
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

//============================================================
//	テキストオフセットの設定処理
//============================================================
void CFrame2DModuleText::SetOffset(const VECTOR3& rOffset)
{
	// テキストオフセットの設定
	m_offset = rOffset;

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	相対位置の設定処理
//============================================================
void CFrame2DModuleText::SetPositionRelative()
{
	VECTOR3 posFrame = m_pContext->GetVec3Position();	// フレーム位置
	VECTOR3 rotFrame = m_pContext->GetVec3Rotation();	// フレーム向き

	// X座標オフセット分ずらす
	posFrame.x += sinf(rotFrame.z + HALF_PI) * m_offset.x;
	posFrame.y += cosf(rotFrame.z + HALF_PI) * m_offset.x;

	// Y座標オフセット分ずらす
	posFrame.x += sinf(rotFrame.z) * m_offset.y;
	posFrame.y += cosf(rotFrame.z) * m_offset.y;

	// テキスト位置の反映
	m_pText->SetVec3Position(posFrame);
}
