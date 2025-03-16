//============================================================
//
//	表情/選択付きテキスト状態処理 [frame2DTextStateFaceSelect.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateFaceSelect.h"
#include "frame2DModuleText.h"
#include "frame2DTextBuffer.h"
#include "faceUI.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	namespace text
	{
		const VECTOR3 OFFSET[] =	// テキストオフセットプリセット
		{
			VECTOR3(-210.0f, -80.0f, 0.0f)	// 下部配置
		};
	}

	namespace face
	{
		const VECTOR3 OFFSET[] =	// 表情オフセットプリセット
		{
			VECTOR3(315.0f, 0.0f, 0.0f)	// 下部配置
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
static_assert(NUM_ARRAY(face::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	子クラス [CFrame2DTextStateFaceSelect] のメンバ関数
//************************************************************
//============================================================
//	移譲コンストラクタ (デフォルト)
//============================================================
CFrame2DTextStateFaceSelect::CFrame2DTextStateFaceSelect() : CFrame2DTextStateFaceSelect(VEC3_ZERO, VEC3_ZERO, VEC3_ZERO, VEC3_ZERO)
{

}

//============================================================
//	コンストラクタ (配置指定)
//============================================================
CFrame2DTextStateFaceSelect::CFrame2DTextStateFaceSelect(const VECTOR3& rOffsetText, const VECTOR3& rOffsetSelectL, const VECTOR3& rOffsetSelectR, const VECTOR3& rOffsetFace) : CFrame2DTextStateSelect(rOffsetText, rOffsetSelectL, rOffsetSelectR),
	m_pFace			(nullptr),		// 表情情報
	m_offset		(rOffsetFace),	// 表情オフセット
	m_nTypeTalkEmo	(0),			// 会話中の表情種類
	m_nTypeIdolEmo	(0)				// 待機中の表情種類
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextStateFaceSelect::~CFrame2DTextStateFaceSelect()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFrame2DTextStateFaceSelect::Init()
{
	// メンバ変数を初期化
	m_pFace			= nullptr;	// 表情情報
	m_nTypeTalkEmo	= 0;		// 会話中の表情種類
	m_nTypeIdolEmo	= 0;		// 待機中の表情種類

	// 親クラスの初期化
	if (FAILED(CFrame2DTextStateSelect::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	CFrame2D::EPreset preset = m_pContext->GetFramePreset();	// フレーム配置プリセット
	if (preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX)
	{ // プリセットが範囲内の場合

		// テキストオフセットの設定
		SetOffset(GetPresetOffset(preset));

		// 顔オフセットの設定
		m_offset = face::OFFSET[preset];
	}

	// 表情の生成
	m_pFace = CFaceUI::Create(0, 0, VEC3_ZERO);
	if (m_pFace == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pFace->SetPriority(m_pContext->GetFramePriority());

	// 相対位置の設定
	CFrame2DTextStateFaceSelect::SetPositionRelative();	// 自身の相対位置

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrame2DTextStateFaceSelect::Uninit()
{
	// 表情の終了
	SAFE_UNINIT(m_pFace);

	// 親クラスの終了
	CFrame2DTextStateSelect::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CFrame2DTextStateFaceSelect::Update(const float fDeltaTime)
{
	// 前回のループ数を保存
	int nOldNumLoop = m_pFace->GetLoopAnim();

	// 表情の更新
	m_pFace->Update(fDeltaTime);

	if (m_pFace->GetEmotion() != m_nTypeIdolEmo)
	{ // 表情変更前の場合

		if (IsTextEndScroll() && m_pFace->GetLoopAnim() > nOldNumLoop)
		{ // 文字送りが終了している且つ、ループが更新された場合

			// 待機表情の設定
			m_pFace->SetEmotion(m_nTypeIdolEmo);
		}
	}

	// 親クラスの更新
	CFrame2DTextStateSelect::Update(fDeltaTime);
}

//============================================================
//	優先順位の設定処理
//============================================================
void CFrame2DTextStateFaceSelect::SetPriority(const int nPriority)
{
	// 表情の優先順位を設定
	m_pFace->SetPriority(nPriority);

	// 親クラスの優先順位を設定
	CFrame2DTextStateSelect::SetPriority(nPriority);
}

//============================================================
//	位置の設定処理
//============================================================
void CFrame2DTextStateFaceSelect::SetVec3Position(const VECTOR3& rPos)
{
	// 親クラスの位置を設定
	CFrame2DTextStateSelect::SetVec3Position(rPos);
}

//============================================================
//	向きの設定処理
//============================================================
void CFrame2DTextStateFaceSelect::SetVec3Rotation(const VECTOR3& rRot)
{
	// 表情の向きを設定
	m_pFace->SetVec3Rotation(rRot);

	// 親クラスの向きを設定
	CFrame2DTextStateSelect::SetVec3Rotation(rRot);
}

//============================================================
//	テキスト情報保存バッファの割当処理
//============================================================
void CFrame2DTextStateFaceSelect::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// 表情/選択付きテキスト保存バッファに変換できない場合抜ける
	CFrame2DTextBufferFaceSelect* pBuffFaceSelect = pBuffer->GetBufferFaceSelect();
	if (pBuffFaceSelect == nullptr) { assert(false); return; }

	// 顔情報の割当
	m_pFace->BindFaceData(pBuffFaceSelect->m_nIdxFace);

	// 表情種類の保存
	m_nTypeTalkEmo = pBuffFaceSelect->m_nTypeTalkEmo;	// 会話中
	m_nTypeIdolEmo = pBuffFaceSelect->m_nTypeIdolEmo;	// 待機中

	// 初期表情の設定
	m_pFace->SetEmotion(m_nTypeTalkEmo);	// 会話表情から始める

	// 親クラスのテキスト情報保存バッファの割当
	CFrame2DTextStateSelect::BindTextBuffer(pBuffer);
}

//============================================================
//	プリセットオフセットの取得処理
//============================================================
VECTOR3 CFrame2DTextStateFaceSelect::GetPresetOffset(const CFrame2D::EPreset preset)
{
	// プリセット範囲外エラー
	assert(preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX);

	// 引数プリセットのオフセットを返す
	return text::OFFSET[preset];
}

//============================================================
//	相対位置の設定処理
//============================================================
void CFrame2DTextStateFaceSelect::SetPositionRelative()
{
	// 親クラスの相対位置の設定
	CFrame2DTextStateSelect::SetPositionRelative();

	if (m_pFace != nullptr)
	{ // 表情が生成済みの場合

		VECTOR3 posFrame = m_pContext->GetFramePosition();	// フレーム位置
		VECTOR3 rotFrame = m_pContext->GetFrameRotation();	// フレーム向き

		// X座標オフセット分ずらす
		posFrame.x -= sinf(rotFrame.z + HALF_PI) * m_offset.x;
		posFrame.y -= cosf(rotFrame.z + HALF_PI) * m_offset.x;

		// Y座標オフセット分ずらす
		posFrame.x += sinf(rotFrame.z) * m_offset.y;
		posFrame.y += cosf(rotFrame.z) * m_offset.y;

		// 表情位置の反映
		m_pFace->SetVec3Position(posFrame);
		m_pFace->SetVec3Rotation(rotFrame);
	}
}
