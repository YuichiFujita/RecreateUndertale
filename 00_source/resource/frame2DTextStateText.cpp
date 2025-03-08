//============================================================
//
//	テキスト状態処理 [frame2DTextStateText.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateText.h"
#include "frame2DModuleText.h"
#include "frame2DTextBuffer.h"

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
		const bool	ITALIC		= false;		// イタリック
		const EAlignX ALIGN_X	= XALIGN_LEFT;	// 横配置
		const EAlignY ALIGN_Y	= YALIGN_TOP;	// 縦配置
	}
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(text::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	子クラス [CFrame2DTextStateText] のメンバ関数
//************************************************************
//============================================================
//	移譲コンストラクタ (デフォルト)
//============================================================
CFrame2DTextStateText::CFrame2DTextStateText() : CFrame2DTextStateText(VEC3_ZERO)
{

}

//============================================================
//	コンストラクタ (配置指定)
//============================================================
CFrame2DTextStateText::CFrame2DTextStateText(const VECTOR3& rOffset) :
	m_sNextTextKey	(""),		// 次テキストの検索キー
	m_pText			(nullptr),	// テキスト情報
	m_offset		(rOffset)	// テキストオフセット
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextStateText::~CFrame2DTextStateText()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFrame2DTextStateText::Init()
{
	// メンバ変数を初期化
	m_sNextTextKey	= "NONE";	// 次テキストの検索キー
	m_pText			= nullptr;	// テキスト情報

	CFrame2D::EPreset preset = m_pContext->GetFramePreset();	// フレーム配置プリセット
	if (preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX)
	{ // プリセットが範囲内の場合

		// テキストオフセットの設定
		m_offset = GetPresetOffset(preset);
	}

	// テキストの生成
	m_pText = CScrollText2D::Create
	( // 引数
		text::FONT,							// フォントパス
		text::ITALIC,						// イタリック
		VEC3_ZERO,							// 原点位置
		CFrame2DTextStateText::WAIT_TIME,	// 文字表示の待機時間
		CFrame2DTextStateText::CHAR_HEIGHT,	// 文字縦幅
		CFrame2DTextStateText::LINE_HEIGHT,	// 行間縦幅
		text::ALIGN_X,						// 横配置
		text::ALIGN_Y						// 縦配置
	);
	if (m_pText == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pText->SetPriority(m_pContext->GetFramePriority());

	// 文字送り時の再生SEを設定
	m_pText->SetScrollSE(CSound::LABEL_SE_TEXT01);

	// 相対位置の設定
	CFrame2DTextStateText::SetPositionRelative();	// 自身の相対位置

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrame2DTextStateText::Uninit()
{
	// テキストの終了
	SAFE_UNINIT(m_pText);

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CFrame2DTextStateText::Update(const float fDeltaTime)
{
	if (input::Decide())
	{
		if (!m_pText->IsEndScroll())
		{ // 文字送り中の場合

			// 文字を全表示させる
			m_pText->SetEnableDraw(true);
			return;
		}

		// テキストの遷移
		m_pContext->TransText(m_sNextTextKey);	// TODO：次テキスト検索キーを選択状態のとき使ってないな
	}
}

//============================================================
//	優先順位の設定処理
//============================================================
void CFrame2DTextStateText::SetPriority(const int nPriority)
{
	// テキストの優先順位を設定
	m_pText->SetPriority(nPriority);
}

//============================================================
//	位置の設定処理
//============================================================
void CFrame2DTextStateText::SetVec3Position(const VECTOR3& /*rPos*/)
{
	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	向きの設定処理
//============================================================
void CFrame2DTextStateText::SetVec3Rotation(const VECTOR3& rRot)
{
	// テキストの向きを設定
	m_pText->SetVec3Rotation(rRot);

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	テキスト情報保存バッファの割当処理
//============================================================
void CFrame2DTextStateText::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// テキスト保存バッファに変換できない場合抜ける
	CFrame2DTextBufferText* pBuffText = pBuffer->GetBufferText();
	if (pBuffText == nullptr) { assert(false); return; }

	// 割り当てるテキストの検索キーを保存
	SetCurTextKey(pBuffer->m_sKey);

	// 次テキストの検索キーを割当
	m_sNextTextKey = pBuffText->m_sNextTextKey;

	// テキスト情報を割当
	int nNumStr = (int)pBuffText->m_text.size();	// 文字列数
	for (int i = 0; i < nNumStr; i++)
	{ // 文字列数分繰り返す

		// 文字列を最後尾に追加
		m_pText->PushBackString(pBuffText->m_text[i]);
	}

	// 文字送りを開始する
	m_pText->SetEnableScroll(true);

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	テキスト変更処理
//============================================================
void CFrame2DTextStateText::ChangeText(const AText& rText)
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

	// 文字送りを開始する
	m_pText->SetEnableScroll(true);

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	テキストオフセットの設定処理
//============================================================
void CFrame2DTextStateText::SetOffset(const VECTOR3& rOffset)
{
	// テキストオフセットの設定
	m_offset = rOffset;

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	プリセットオフセットの取得処理
//============================================================
VECTOR3 CFrame2DTextStateText::GetPresetOffset(const CFrame2D::EPreset preset)
{
	// プリセット範囲外エラー
	assert(preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX);

	// 引数プリセットのオフセットを返す
	return text::OFFSET[preset];
}

//============================================================
//	相対位置の設定処理
//============================================================
void CFrame2DTextStateText::SetPositionRelative()
{
	if (m_pText != nullptr)
	{ // テキストが生成済みの場合

		VECTOR3 posFrame = m_pContext->GetFramePosition();	// フレーム位置
		VECTOR3 rotFrame = m_pContext->GetFrameRotation();	// フレーム向き

		// X座標オフセット分ずらす
		posFrame.x += sinf(rotFrame.z + HALF_PI) * m_offset.x;
		posFrame.y += cosf(rotFrame.z + HALF_PI) * m_offset.x;

		// Y座標オフセット分ずらす
		posFrame.x += sinf(rotFrame.z) * m_offset.y;
		posFrame.y += cosf(rotFrame.z) * m_offset.y;

		// テキスト位置の反映
		m_pText->SetVec3Position(posFrame);
		m_pText->SetVec3Rotation(rotFrame);
	}
}
