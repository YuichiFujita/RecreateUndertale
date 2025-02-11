//============================================================
//
//	選択付きテキスト状態処理 [frame2DTextStateSelect.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextStateSelect.h"
#include "frame2DModuleText.h"
#include "frame2DTextBuffer.h"
#include "manager.h"
#include "object2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	namespace select
	{
		namespace L
		{
			const float OFFSET_X[] =	// テキストオフセットプリセット
			{
				-160.0f,	// 下部配置
			};
		}
		namespace R
		{
			const float OFFSET_X[] =	// テキストオフセットプリセット
			{
				160.0f,		// 下部配置
			};
		}

		const char*	FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC		= false;		// イタリック
		const EAlignX ALIGN_X	= XALIGN_LEFT;	// 横配置
		const EAlignY ALIGN_Y	= YALIGN_TOP;	// 縦配置
	}

	namespace soul
	{
		const char* PATH	= "data\\TEXTURE\\spr_heartsmall.png";	// ソウルカーソルテクスチャパス
		const float OFFSET	= 10.0f;								// ソウルカーソルオフセット
		const VECTOR3 SIZE	= VECTOR3(26.5f, 26.5f, 0.0f);			// ソウルカーソル大きさ
	}
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CFrame2DTextStateSelect::AFuncOffset CFrame2DTextStateSelect::m_aFuncOffset[][SELECT_MAX] =	// オフセット取得関数リスト
{
	{ &CFrame2DTextStateSelect::GetOffsetDownLeft, &CFrame2DTextStateSelect::GetOffsetDownRight },	// 下部配置オフセット
};

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(select::L::OFFSET_X) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");
static_assert(NUM_ARRAY(select::R::OFFSET_X) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	子クラス [CFrame2DTextStateSelect] のメンバ関数
//************************************************************
//============================================================
//	移譲コンストラクタ (デフォルト)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect() : CFrame2DTextStateSelect(VEC3_ZERO, VEC3_ZERO, VEC3_ZERO)
{
	// スタティックアサート
	static_assert(NUM_ARRAY(m_aFuncOffset) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");
}

//============================================================
//	コンストラクタ (配置プリセット)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect(const CFrame2D::EPreset preset) : CFrame2DTextStateText(preset),
	m_sCutTextPath	(""),		// 現在テキストの保存パス
	m_pSoul			(nullptr),	// ソウルカーソル情報
	m_nCurSelect	(0)			// 現在の選択肢
{
	// メンバ変数をクリア
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		m_aNextPath[i]	 = "";		// 次テキストボックスの保存パス
		m_aNextBoxKey[i] = "";		// 次テキストボックスの検索キー
		m_aNextKey[i]	 = "";		// テキストボックスのテキスト開始キー
		m_apSelect[i]	 = nullptr;	// 選択肢情報
	}
	m_aOffset[SELECT_LEFT]	= GetPresetOffset(SELECT_LEFT, preset);		// 左選択肢オフセット
	m_aOffset[SELECT_RIGHT]	= GetPresetOffset(SELECT_RIGHT, preset);	// 右選択肢オフセット
}

//============================================================
//	コンストラクタ (配置指定)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect(const VECTOR3& rOffsetText, const VECTOR3& rOffsetSelectL, const VECTOR3& rOffsetSelectR) : CFrame2DTextStateText(rOffsetText),
	m_sCutTextPath	(""),		// 現在テキストの保存パス
	m_pSoul			(nullptr),	// ソウルカーソル情報
	m_nCurSelect	(0)			// 現在の選択肢
{
	// メンバ変数をクリア
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		m_aNextPath[i]	 = "";		// 次テキストボックスの保存パス
		m_aNextBoxKey[i] = "";		// 次テキストボックスの検索キー
		m_aNextKey[i]	 = "";		// テキストボックスのテキスト開始キー
		m_apSelect[i]	 = nullptr;	// 選択肢情報
	}
	m_aOffset[SELECT_LEFT]	= rOffsetSelectL;	// 左選択肢オフセット
	m_aOffset[SELECT_RIGHT]	= rOffsetSelectR;	// 右選択肢オフセット
}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextStateSelect::~CFrame2DTextStateSelect()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFrame2DTextStateSelect::Init()
{
	// メンバ変数を初期化
	m_sCutTextPath	= "NONE";	// 現在テキストの保存パス
	m_pSoul			= nullptr;	// ソウルカーソル情報
	m_nCurSelect	= 0;		// 現在の選択肢
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		m_aNextPath[i]	 = "NONE";	// 次テキストボックスの保存パス
		m_aNextBoxKey[i] = "NONE";	// 次テキストボックスの検索キー
		m_aNextKey[i]	 = "NONE";	// テキストボックスのテキスト開始キー
		m_apSelect[i]	 = nullptr;	// 選択肢情報
	}

	// TODO：ここで他のキー情報の初期値を設定
	// TODO：それと他のキー初期化では何の文字列入れてるかも確認

	// 親クラスの初期化
	if (FAILED(CFrame2DTextStateText::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	const int nPrioFrame = m_pContext->GetFramePriority();	// コンテキストの優先順位
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択肢の生成
		m_apSelect[i] = CScrollText2D::Create
		( // 引数
			select::FONT,						// フォントパス
			select::ITALIC,						// イタリック
			VEC3_ZERO,							// 原点位置
			CFrame2DTextStateText::WAIT_TIME,	// 文字表示の待機時間
			CFrame2DTextStateText::CHAR_HEIGHT,	// 文字縦幅
			CFrame2DTextStateText::LINE_HEIGHT,	// 行間縦幅
			select::ALIGN_X,					// 横配置
			select::ALIGN_Y						// 縦配置
		);
		if (m_apSelect[i] == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_apSelect[i]->SetPriority(nPrioFrame);

		// 文字送り時の再生SEを設定
		m_apSelect[i]->SetScrollSE(CSound::LABEL_SE_TEXT01);
	}

	// ソウルカーソルの生成
	m_pSoul = CObject2D::Create
	( // 引数
		VEC3_ZERO,	// 位置
		soul::SIZE	// 大きさ
	);
	if (m_pSoul == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ソウルテクスチャを割当
	m_pSoul->BindTexture(soul::PATH);

	// ラベルを設定
	m_pSoul->SetLabel(CObject::LABEL_UI);

	// 優先順位を設定
	m_pSoul->SetPriority(nPrioFrame);

	// カーソルの自動描画をOFFにする
	m_pSoul->SetEnableDraw(false);

	// 相対位置の設定
	CFrame2DTextStateSelect::SetPositionRelative();	// 自身の相対位置

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrame2DTextStateSelect::Uninit()
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// テキストの終了
		SAFE_UNINIT(m_apSelect[i]);
	}

	// ソウルカーソルの終了
	SAFE_UNINIT(m_pSoul);

	// 親クラスの終了
	CFrame2DTextStateText::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CFrame2DTextStateSelect::Update(const float fDeltaTime)
{
	if (!m_pSoul->IsDraw())
	{ // カーソルが表示されていない場合

		if (input::Decide())
		{
			// 文字を全表示させる
			SetTextEnableDraw(true);
			m_apSelect[SELECT_LEFT]->SetEnableDraw(true);
			m_apSelect[SELECT_RIGHT]->SetEnableDraw(true);

			// カーソルの自動描画をONにする
			m_pSoul->SetEnableDraw(true);
			return;
		}

		// 文字送りの更新
		UpdateScroll();
	}
	else
	{ // カーソルが表示されている場合

		// 選択の更新
		UpdateSelect();

		// 決定の更新
		UpdateDecide();
	}
}

//============================================================
//	優先順位の設定処理
//============================================================
void CFrame2DTextStateSelect::SetPriority(const int nPriority)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// テキストの優先順位を設定
		m_apSelect[i]->SetPriority(nPriority);
	}

	// ソウルカーソルの優先順位を設定
	m_pSoul->SetPriority(nPriority);

	// 親クラスの優先順位を設定
	CFrame2DTextStateText::SetPriority(nPriority);
}

//============================================================
//	位置の設定処理
//============================================================
void CFrame2DTextStateSelect::SetVec3Position(const VECTOR3& rPos)
{
	// 親クラスの位置を設定
	CFrame2DTextStateText::SetVec3Position(rPos);
}

//============================================================
//	向きの設定処理
//============================================================
void CFrame2DTextStateSelect::SetVec3Rotation(const VECTOR3& rRot)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// テキストの向きを設定
		m_apSelect[i]->SetVec3Rotation(rRot);
	}

	// ソウルカーソルの向きを設定
	m_pSoul->SetVec3Rotation(rRot);

	// 親クラスの向きを設定
	CFrame2DTextStateText::SetVec3Rotation(rRot);
}

//============================================================
//	テキスト情報保存バッファの割当処理
//============================================================
void CFrame2DTextStateSelect::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// 選択付きテキスト保存バッファに変換できない場合抜ける
	CFrame2DTextBufferSelect* pBuffSelect = pBuffer->GetBufferSelect();
	if (pBuffSelect == nullptr) { assert(false); return; }

	// 割り当てるテキストの検索キーを保存
	SetCurTextKey(pBuffer->m_sKey);

	// 割り当てるテキストの保存パスを保存
	m_sCutTextPath = pBuffer->m_sPath;

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// テキストの識別情報を割当
		m_aNextPath[i]	 = pBuffSelect->m_aNextPath[i];		// 次テキストボックスの保存パス
		m_aNextBoxKey[i] = pBuffSelect->m_aNextBoxKey[i];	// 次テキストボックスの検索キー
		m_aNextKey[i]	 = pBuffSelect->m_aNextKey[i];		// テキストボックスのテキスト開始キー

		// 選択肢のテキスト情報を割当
		int nNumSelect = (int)pBuffSelect->m_aSelect[i].size();	// 文字列数
		for (int j = 0; j < nNumSelect; j++)
		{ // 文字列数分繰り返す

			// 文字列を最後尾に追加
			m_apSelect[i]->PushBackString(pBuffSelect->m_aSelect[i][j]);
		}
	}

	// テキスト情報を割当
	int nNumStr = (int)pBuffSelect->m_text.size();	// 文字列数
	for (int i = 0; i < nNumStr; i++)
	{ // 文字列数分繰り返す

		// 文字列を最後尾に追加
		PushBackString(pBuffSelect->m_text[i]);
	}

	// 文字送りを開始する
	SetTextEnableScroll(true);

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	テキスト変更処理
//============================================================
void CFrame2DTextStateSelect::ChangeText(const ESelect select, const AText& rText)
{
	// 文字列を全て削除
	m_apSelect[select]->DeleteStringAll();

	// テキストを割当
	int nLoop = (int)rText.size();	// 文字列数
	for (int i = 0; i < nLoop; i++)
	{ // 文字列の数分繰り返す

		// 文字列を最後尾に追加
		m_apSelect[select]->PushBackString(rText[i]);
	}

	// 文字送りを開始する
	m_apSelect[select]->SetEnableScroll(true);

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	プリセットオフセットの取得処理
//============================================================
VECTOR3 CFrame2DTextStateSelect::GetPresetOffset(const ESelect select, const CFrame2D::EPreset preset)
{
	// プリセット範囲外エラー
	assert(preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX);

	// 引数プリセットのオフセットを返す
	return (this->*(m_aFuncOffset[preset][select]))();
}

//============================================================
//	相対位置の設定処理
//============================================================
void CFrame2DTextStateSelect::SetPositionRelative()
{
	// 親クラスの相対位置の設定
	CFrame2DTextStateText::SetPositionRelative();

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
}

//============================================================
//	文字送りの更新処理
//============================================================
void CFrame2DTextStateSelect::UpdateScroll()
{
	if (IsTextEndScroll())
	{ // 本文の文字送りが終了した場合

		// 左選択肢の文字送りを開始
		m_apSelect[SELECT_LEFT]->SetEnableScroll(true);
	}
	else { return; }

	if (m_apSelect[SELECT_LEFT]->IsEndScroll())
	{ // 左選択肢の文字送りが終了した場合

		// 右選択肢の文字送りを開始
		m_apSelect[SELECT_RIGHT]->SetEnableScroll(true);
	}
	else { return; }

	if (m_apSelect[SELECT_RIGHT]->IsEndScroll())
	{ // 右選択肢の文字送りが終了した場合

		// カーソルの自動描画をONにする
		m_pSoul->SetEnableDraw(true);
	}
}

//============================================================
//	選択の更新処理
//============================================================
void CFrame2DTextStateSelect::UpdateSelect()
{
	// 選択肢操作
	CInputKeyboard* pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// 左に選択をずらす
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;

		// 相対位置の設定
		SetPositionRelative();
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// 右に選択をずらす
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;

		// 相対位置の設定
		SetPositionRelative();
	}
}

//============================================================
//	決定の更新処理
//============================================================
void CFrame2DTextStateSelect::UpdateDecide()
{
	// 決定操作がされていない場合抜ける
	if (!input::Decide()) { return; }

	if (m_aNextPath[m_nCurSelect] == "-1"
	||  m_aNextPath[m_nCurSelect] == "NONE"
	||  m_aNextPath[m_nCurSelect].empty())
	{ // テキスト遷移先が同一パスにある場合

		if (m_aNextBoxKey[m_nCurSelect] == "-1"
		||  m_aNextBoxKey[m_nCurSelect] == "NONE"
		||  m_aNextBoxKey[m_nCurSelect].empty())
		{ // テキストボックス検索キーの指定がない場合

			// テキストの遷移
			m_pContext->TransText(m_aNextKey[m_nCurSelect]);	// 遷移前と同一のテキストバッファ連想配列を使用
		}
		else
		{ // テキストボックス検索キーの指定がある場合

			// テキストボックスの読込
			m_pContext->LoadTextBox
			( // 引数
				m_sCutTextPath,				// 次テキストボックスの保存パス
				m_aNextBoxKey[m_nCurSelect]	// 次テキストボックスの検索キー
			);

			// テキストの割当
			m_pContext->BindText(m_aNextKey[m_nCurSelect]);
		}
	}
	else
	{ // テキスト遷移先が別パスにある場合

		// テキストボックスの読込
		m_pContext->LoadTextBox
		( // 引数
			m_aNextPath[m_nCurSelect],	// 次テキストボックスの保存パス
			m_aNextBoxKey[m_nCurSelect]	// 次テキストボックスの検索キー
		);

		// テキストの割当
		m_pContext->BindText(m_aNextKey[m_nCurSelect]);
	}
}

//============================================================
//	選択肢の最大行数の取得処理
//============================================================
int CFrame2DTextStateSelect::GetMaxSelectLine()
{
	int nMaxNumLine = 0;	// 最大の行数
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択肢が未生成の場合次へ
		if (m_apSelect[i] == nullptr) { continue; }

		int nNumLine = m_apSelect[i]->GetNumString();	// 現在の行数
		if (nMaxNumLine < nNumLine)
		{ // より多い行数の場合

			// 行数を保存
			nMaxNumLine = nNumLine;
		}
	}

	// 最大の行数を返す
	return nMaxNumLine;
}

//============================================================
//	左下部配置オフセットの取得処理
//============================================================
VECTOR3 CFrame2DTextStateSelect::GetOffsetDownLeft()
{
	// オフセットの計算
	VECTOR3 offset;
	offset.x = select::L::OFFSET_X[CFrame2D::PRESET_DOWN];
	offset.y = GetPresetOffset(CFrame2D::PRESET_DOWN).y + CFrame2DTextStateText::LINE_HEIGHT * (float)(3 - GetMaxSelectLine());

	// オフセットを返す
	return offset;
}

//============================================================
//	右下部配置オフセットの取得処理
//============================================================
VECTOR3 CFrame2DTextStateSelect::GetOffsetDownRight()
{
	// オフセットの計算
	VECTOR3 offset;
	offset.x = select::R::OFFSET_X[CFrame2D::PRESET_DOWN];
	offset.y = GetPresetOffset(CFrame2D::PRESET_DOWN).y + CFrame2DTextStateText::LINE_HEIGHT * (float)(3 - GetMaxSelectLine());

	// オフセットを返す
	return offset;
}
