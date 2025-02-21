//============================================================
//
//	表情付きテキスト状態処理 [frame2DTextStateFaceText.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateFaceText.h"
#include "frame2DModuleText.h"
#include "frame2DTextBuffer.h"
#include "faceUI.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	namespace face
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
static_assert(NUM_ARRAY(face::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	子クラス [CFrame2DTextStateFaceText] のメンバ関数
//************************************************************
//============================================================
//	移譲コンストラクタ (デフォルト)
//============================================================
CFrame2DTextStateFaceText::CFrame2DTextStateFaceText() : CFrame2DTextStateFaceText(VEC3_ZERO, VEC3_ZERO)
{

}

//============================================================
//	コンストラクタ (配置プリセット)
//============================================================
CFrame2DTextStateFaceText::CFrame2DTextStateFaceText(const CFrame2D::EPreset preset) : CFrame2DTextStateText(preset),
	m_pFace	 (nullptr),				// 表情情報
	m_offset (face::OFFSET[preset])	// 表情オフセット
{

}

//============================================================
//	コンストラクタ (配置指定)
//============================================================
CFrame2DTextStateFaceText::CFrame2DTextStateFaceText(const VECTOR3& rOffsetText, const VECTOR3& rOffsetFace) : CFrame2DTextStateText(rOffsetText),
	m_pFace	 (nullptr),		// 表情情報
	m_offset (rOffsetFace)	// 表情オフセット
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextStateFaceText::~CFrame2DTextStateFaceText()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFrame2DTextStateFaceText::Init()
{
	// メンバ変数を初期化
	m_pFace = nullptr;	// 表情情報

	// 親クラスの初期化
	if (FAILED(CFrame2DTextStateText::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 表情の生成
	//m_pFace = CFaceUI::Create(0, 0, VEC3_ZERO);	// TODO
	m_pFace = CFaceUI::Create(0, 0, SCREEN_CENT);
	if (m_pFace == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pFace->SetPriority(m_pContext->GetFramePriority());

	// 相対位置の設定
	CFrame2DTextStateFaceText::SetPositionRelative();	// 自身の相対位置

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrame2DTextStateFaceText::Uninit()
{
	// 表情の終了
	SAFE_UNINIT(m_pFace);

	// 親クラスの終了
	CFrame2DTextStateText::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CFrame2DTextStateFaceText::Update(const float fDeltaTime)
{
	// 親クラスの更新
	CFrame2DTextStateText::Update(fDeltaTime);
}

//============================================================
//	優先順位の設定処理
//============================================================
void CFrame2DTextStateFaceText::SetPriority(const int nPriority)
{
	// 表情の優先順位を設定
	m_pFace->SetPriority(nPriority);

	// 親クラスの優先順位を設定
	CFrame2DTextStateText::SetPriority(nPriority);
}

//============================================================
//	位置の設定処理
//============================================================
void CFrame2DTextStateFaceText::SetVec3Position(const VECTOR3& rPos)
{
	// 親クラスの位置を設定
	CFrame2DTextStateText::SetVec3Position(rPos);
}

//============================================================
//	向きの設定処理
//============================================================
void CFrame2DTextStateFaceText::SetVec3Rotation(const VECTOR3& rRot)
{
	// 表情の向きを設定
	m_pFace->SetVec3Rotation(rRot);

	// 親クラスの向きを設定
	CFrame2DTextStateText::SetVec3Rotation(rRot);
}

//============================================================
//	テキスト情報保存バッファの割当処理
//============================================================
void CFrame2DTextStateFaceText::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// 表情付きテキスト保存バッファに変換できない場合抜ける
	CFrame2DTextBufferFaceText* pBuffFaceText = pBuffer->GetBufferFaceText();
	if (pBuffFaceText == nullptr) { assert(false); return; }

	// 顔情報の割当
	m_pFace->BindFaceData(pBuffFaceText->m_nIdxFace);

	// 表情の設定
	m_pFace->SetEmotion(pBuffFaceText->m_nTypeEmo);

	// 親クラスのテキスト情報保存バッファの割当
	CFrame2DTextStateText::BindTextBuffer(pBuffer);
}

//============================================================
//	相対位置の設定処理
//============================================================
void CFrame2DTextStateFaceText::SetPositionRelative()
{
	// 親クラスの相対位置の設定
	CFrame2DTextStateText::SetPositionRelative();

	// TODO
#if 0
	CFrame2D::EPreset preset = m_pContext->GetFramePreset();	// フレームプリセット
	if (preset != CFrame2D::PRESET_NONE)
	{ // プリセットが指定されている場合

		for (int i = 0; i < SELECT_MAX; i++)
		{ // 選択肢の総数分繰り返す

			// オフセットを更新
			m_aOffset[i] = GetPresetOffset((ESelect)i, preset);
		}
	}

	VECTOR3 posFrame = m_pContext->GetFramePosition();	// フレーム位置
	VECTOR3 rotFrame = m_pContext->GetFrameRotation();	// フレーム向き
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		VECTOR3 posSelect = posFrame;	// 選択肢位置

		// X座標オフセット分ずらす
		posSelect.x += sinf(rotFrame.z + HALF_PI) * m_aOffset[i].x;
		posSelect.y += cosf(rotFrame.z + HALF_PI) * m_aOffset[i].x;

		// Y座標オフセット分ずらす
		posSelect.x += sinf(rotFrame.z) * m_aOffset[i].y;
		posSelect.y += cosf(rotFrame.z) * m_aOffset[i].y;

		// 選択肢位置の反映
		m_apSelect[i]->SetVec3Position(posSelect);
	}

	// X座標オフセット分ずらす
	VECTOR3 posCursor = m_apSelect[m_nCurSelect]->GetVec3Position();
	posCursor.x -= sinf(rotFrame.z + HALF_PI) * soul::OFFSET;
	posCursor.y -= cosf(rotFrame.z + HALF_PI) * soul::OFFSET;

	// Y座標オフセット分ずらす
	float fOffsetY = m_apSelect[m_nCurSelect]->GetCharHeight() * 0.5f;
	posCursor.x += sinf(rotFrame.z) * fOffsetY;
	posCursor.y += cosf(rotFrame.z) * fOffsetY;

	// ソウルカーソル位置の反映
	m_pSoul->SetVec3Position(posCursor);
#endif
}
