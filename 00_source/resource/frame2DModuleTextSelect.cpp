//============================================================
//
//	選択付きテキスト表示機能処理 [frame2DModuleTextSelect.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DModuleTextSelect.h"
#include "manager.h"
#include "object2D.h"

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
		const int	PRIORITY	= 6;				// テキストの優先順位
		const bool	ITALIC		= false;			// イタリック
		const float	CHAR_HEIGHT	= 42.0f;			// 文字縦幅
		const float	LINE_HEIGHT	= 54.0f;			// 行間縦幅
		const float	WAIT_TIME	= 0.045f;			// 文字表示の待機時間
		const EAlignX ALIGN_X	= XALIGN_CENTER;	// 横配置
		const EAlignY ALIGN_Y	= YALIGN_TOP;		// 縦配置
	}

	namespace soul
	{
		const char* PATH	= "data\\TEXTURE\\spr_heartsmall.png";	// ソウルカーソルテクスチャパス
		const VECTOR3 SIZE	= VECTOR3(26.5f, 26.5f, 0.0f);			// ソウルカーソル大きさ
	}
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(text::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	子クラス [CFrame2DModuleTextSelect] のメンバ関数
//************************************************************
//============================================================
//	移譲コンストラクタ (配置プリセット)
//============================================================
CFrame2DModuleTextSelect::CFrame2DModuleTextSelect(const CFrame2D::EPreset preset) : CFrame2DModuleTextSelect(text::OFFSET[preset])
{
	// プリセット範囲外エラー
	assert(preset > NONE_IDX && preset < CFrame2D::PRESET_MAX);
}

//============================================================
//	コンストラクタ (配置指定)
//============================================================
CFrame2DModuleTextSelect::CFrame2DModuleTextSelect(const VECTOR3& rOffset) : CFrame2DModuleText(rOffset),
	m_pSoul		 (nullptr),	// ソウルカーソル情報
	m_nCurSelect (0)		// 現在の選択肢
{
	// メンバ変数をクリア
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢情報
}

//============================================================
//	デストラクタ
//============================================================
CFrame2DModuleTextSelect::~CFrame2DModuleTextSelect()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFrame2DModuleTextSelect::Init()
{
	// メンバ変数を初期化
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択肢情報
	m_pSoul		 = nullptr;	// ソウルカーソル情報
	m_nCurSelect = 0;		// 現在の選択肢

	// 親クラスの初期化
	if (FAILED(CFrame2DModuleText::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	const int nPrioContext = m_pContext->GetPriority();	// コンテキストの優先順位
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択肢の生成
		m_apSelect[i] = CScrollText2D::Create
		( // 引数
			text::FONT,			// フォントパス
			text::ITALIC,		// イタリック
// TODO
#if 0
			VEC3_ZERO,			// 原点位置
#else
			VECTOR3(SCREEN_CENT.x - 150.0f + 300.0f * (float)i, 600.0f, 0.0f),	// 原点位置
#endif
			text::WAIT_TIME,	// 文字表示の待機時間
			text::CHAR_HEIGHT,	// 文字縦幅
			text::LINE_HEIGHT,	// 行間縦幅
			text::ALIGN_X,		// 横配置
			text::ALIGN_Y		// 縦配置
		);
		if (m_apSelect[i] == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_apSelect[i]->SetPriority(nPrioContext);

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
	m_pSoul->SetPriority(nPrioContext);

	// カーソルの自動描画をOFFにする
	m_pSoul->SetEnableDraw(false);

	// 相対位置の設定
	SetPositionRelative();

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrame2DModuleTextSelect::Uninit()
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// テキストの終了
		SAFE_UNINIT(m_apSelect[i]);
	}

	// ソウルカーソルの終了
	SAFE_UNINIT(m_pSoul);

	// 親クラスの終了
	CFrame2DModuleText::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CFrame2DModuleTextSelect::Update(const float fDeltaTime)
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
void CFrame2DModuleTextSelect::SetPriority(const int nPriority)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// テキストの優先順位を設定
		m_apSelect[i]->SetPriority(nPriority);
	}
}

//============================================================
//	位置の設定処理
//============================================================
void CFrame2DModuleTextSelect::SetVec3Position(const VECTOR3& /*rPos*/)
{
	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	向きの設定処理
//============================================================
void CFrame2DModuleTextSelect::SetVec3Rotation(const VECTOR3& rRot)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// テキストの向きを設定
		m_apSelect[i]->SetVec3Rotation(rRot);
	}

	// 相対位置の設定
	SetPositionRelative();
}

#if 0
//============================================================
//	テキスト変更処理
//============================================================
void CFrame2DModuleTextSelect::ChangeText(const ESelect select, const AText& rText)
{
#if 0
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
#else

#endif
}
#endif

//============================================================
//	保存機能の割当処理
//============================================================
void CFrame2DModuleTextSelect::BindTextSave(CFrame2DModule* pModule, CTextSave* pText)
{
	// 選択付きテキスト表示機能に変換できない場合抜ける
	CFrame2DModuleTextSelect* pModuleSelect = pModule->GetModuleTextSelect();
	if (pModuleSelect == nullptr) { assert(false); return; }

	// 選択付きテキスト保存ポインタに変換できない場合抜ける
	CTextSaveSelect* pSaveSelect = pText->GetSelect();
	if (pSaveSelect == nullptr) { assert(false); return; }

	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 次テキストの検索キーを割当
		pModuleSelect->m_aNextTextKey[i] = pSaveSelect->m_aNextTextKey[i];

		// 選択肢のテキスト情報を割当
		for (int j = 0; j < (int)pSaveSelect->m_aSelect[i].size(); j++)
		{ // 文字列数分繰り返す

			// 文字列を最後尾に追加
			pModuleSelect->m_apSelect[i]->PushBackString(pSaveSelect->m_aSelect[i][j]);
		}
	}

	// テキスト情報を割当
	for (int i = 0; i < (int)pSaveSelect->m_text.size(); i++)
	{ // 文字列数分繰り返す

		// 文字列を最後尾に追加
		pModuleSelect->PushBackString(pSaveSelect->m_text[i]);
	}
}

//============================================================
//	選択の更新処理
//============================================================
void CFrame2DModuleTextSelect::UpdateSelect()
{
	// 選択肢操作
	CInputKeyboard* pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// 左に選択をずらす
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// 右に選択をずらす
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}

	// TODO
	VECTOR3 posSelect = m_apSelect[m_nCurSelect]->GetVec3Position();
	posSelect.x -= m_apSelect[m_nCurSelect]->GetTextWidth() * 0.5f + 30.0f;
	posSelect.y += m_apSelect[m_nCurSelect]->GetCharHeight() * 0.5f;

	// ソウルカーソルの位置を移動
	m_pSoul->SetVec3Position(posSelect);
}

//============================================================
//	決定の更新処理
//============================================================
void CFrame2DModuleTextSelect::UpdateDecide()
{
	if (input::Decide())
	{
		const std::string& rSelectTextKey = m_aNextTextKey[m_nCurSelect];	// 選択中の次テキスト検索キー
		std::string sNextPath = GetNextPath();		// 次テキストボックスの保存パス
		std::string sNextBoxKey = GetNextBoxKey();	// 次テキストボックスの検索キー
		if (rSelectTextKey == "-1"
		||  rSelectTextKey == "NONE")
		{ // テキスト遷移先がない場合

			if (IsNextTextBox(&sNextPath, &sNextBoxKey))
			{ // テキストボックス遷移先がある場合

				SetNextPath(sNextPath);
				SetNextBoxKey(sNextBoxKey);

				// 次のテキストを割当
				BindText(sNextPath, sNextBoxKey, "0");
			}
			else
			{ // テキストボックス遷移先がない場合

				// コンテキストの終了
				SAFE_UNINIT(m_pContext);
			}
		}
		else
		{ // テキスト遷移先がある場合

			// 次のテキストを割当
			BindText(sNextPath, sNextBoxKey, rSelectTextKey);
		}
	}
}

//============================================================
//	相対位置の設定処理
//============================================================
void CFrame2DModuleTextSelect::SetPositionRelative()
{
#if 0
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
#else
	// TODO：1Fだけ位置ずれしてる
	VECTOR3 posSelect = m_apSelect[m_nCurSelect]->GetVec3Position();
	posSelect.x -= m_apSelect[m_nCurSelect]->GetTextWidth() * 0.5f + 30.0f;
	posSelect.y += m_apSelect[m_nCurSelect]->GetCharHeight() * 0.5f;

	// ソウルカーソルの位置を移動
	m_pSoul->SetVec3Position(posSelect);
#endif
}

//************************************************************
//	子クラス [CTextSaveText] のメンバ関数
//************************************************************
//============================================================
//	テキスト機能の生成処理
//============================================================
CFrame2DModule* CTextSaveSelect::CreateModule(const CFrame2D::EPreset preset)
{
	// 選択付きテキスト表示機能を生成し返す
	return new CFrame2DModuleTextSelect(preset);
}

//============================================================
//	現在キーの文字列読込処理
//============================================================
void CTextSaveSelect::LoadKeyString(std::ifstream* pFile, std::string& rString)
{
	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return; }

	if (rString == "SELECT_LEFT")
	{
		// 選択肢文字列の読込
		LoadSelect(pFile, CFrame2DModuleTextSelect::SELECT_LEFT);
	}
	else if (rString == "SELECT_RIGHT")
	{
		// 選択肢文字列の読込
		LoadSelect(pFile, CFrame2DModuleTextSelect::SELECT_RIGHT);
	}
}

//============================================================
//	選択肢文字列の読込処理
//============================================================
void CTextSaveSelect::LoadSelect(std::ifstream* pFile, const CFrame2DModuleTextSelect::ESelect select)
{
	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return; }

	// 選択付きテキスト保存ポインタに変換できない場合抜ける
	CTextSaveSelect* pSelect = GetSelect();
	if (pSelect == nullptr) { assert(false); return; }

	// ファイルを読込
	std::string str;	// 読込文字列
	do { // END_SELECTを読み込むまでループ

		// 文字列を読み込む
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// コメントアウト
		else if (str == "NEXT")
		{
			*pFile >> str;						// ＝を読込
			*pFile >> m_aNextTextKey[select];	// 次テキストの検索キーを読込
		}
		else if (str == "STR")
		{
			*pFile >> str;					// ＝を読込
			pFile->seekg(1, std::ios::cur);	// 読込位置を空白分ずらす
			std::getline(*pFile, str);		// 一行全て読み込む

			// 文字列の先頭に空白を追加
			str.insert(0, " ");

			// 文字列を最後尾に追加
			pSelect->m_aSelect[select].push_back(str);
		}
	} while (str != "END_SELECT");	// END_SELECTを読み込むまでループ
}
