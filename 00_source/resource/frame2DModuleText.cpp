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
	if (input::Decide())
	{
		if (!m_pText->IsEndScroll())
		{ // 文字送り中の場合

			// 文字を全表示させる
			m_pText->SetEnableDraw(true);
			return;
		}

		if (m_sNextTextKey == "-1"
		||  m_sNextTextKey == "NONE")
		{ // テキスト遷移先がない場合

			if (IsNextTextBox(&m_sNextPath, &m_sNextBoxKey))
			{ // テキストボックス遷移先がある場合

				// 次のテキストを割当
				BindText(m_sNextPath, m_sNextBoxKey, "0");
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
			BindText(m_sNextPath, m_sNextBoxKey, m_sNextTextKey);
		}
	}
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

	// 文字送りを開始する
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
//	テキスト割当処理
//============================================================
HRESULT CFrame2DModuleText::BindText(const std::string& rPath, const std::string& rBoxKey, const std::string& rTextKey)
{
#if 0
	// コンテキストの保存
	CFrame2D* pFrame2D = m_pContext;

	// 引数情報の保存
	std::string sNextPath		= rPath;	// 次テキストボックスの保存パス
	std::string sNextBoxKey		= rBoxKey;	// 次テキストボックスの検索キー
	std::string sNextTextKey	= rTextKey;	// 次テキストの検索キー

	// テキスト表示機能を設定
	if (FAILED(pFrame2D->ChangeModule(new CFrame2DModuleText(CFrame2D::PRESET_DOWN))))	// TODO：Select対応
	{ // 設定に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// テキスト表示機能を取得
	CFrame2DModuleText* pModule = pFrame2D->GetModule()->GetModuleText();
	if (pModule == nullptr)
	{ // 取得に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 引数情報の保存
	pModule->m_sNextPath	= sNextPath;	// 次テキストボックスの保存パス
	pModule->m_sNextBoxKey	= sNextBoxKey;	// 次テキストボックスの検索キー
	pModule->m_sNextTextKey	= sNextTextKey;	// 次テキストの検索キー

	// テキストボックス情報を読込
	AText text = pModule->LoadTextBox(sNextPath, sNextBoxKey, sNextTextKey);

	// テキスト情報を割当
	for (int i = 0; i < (int)text.size(); i++)
	{ // 文字列数分繰り返す

		// 文字列を最後尾に追加
		pModule->PushBackString(text[i]);
	}

	// 文字送りを開始する
	pModule->SetTextEnableScroll(true);
#else
	// コンテキストの保存
	CFrame2D* pFrame2D = m_pContext;

	// 引数情報の保存
	const std::string sNextPath		= rPath;	// 次テキストボックスの保存パス
	const std::string sNextBoxKey	= rBoxKey;	// 次テキストボックスの検索キー
	const std::string sNextTextKey	= rTextKey;	// 次テキストの検索キー

	// テキスト表示機能を設定
	if (FAILED(pFrame2D->ChangeModule(new CFrame2DModuleText(CFrame2D::PRESET_DOWN))))	// TODO：Select対応	// TODO：CFrame2DのPresetGetter作成、んでBindTextのプリセットを指定
	{ // 設定に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// テキスト表示機能を取得
	CFrame2DModuleText* pModule = pFrame2D->GetModule()->GetModuleText();
	if (pModule == nullptr)
	{ // 取得に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 引数情報の保存
	pModule->m_sNextPath	= sNextPath;	// 次テキストボックスの保存パス
	pModule->m_sNextBoxKey	= sNextBoxKey;	// 次テキストボックスの検索キー
	pModule->m_sNextTextKey	= sNextTextKey;	// 次テキストの検索キー

	// テキストボックス情報を読込
	AText text = pModule->LoadTextBox(sNextPath, sNextBoxKey, sNextTextKey);	// AText＋必要なModule列挙指定/情報保存したものを返そう (staticなら可能)

	// TODO：各Moduleごとの割当関数作成
#if 1
	// テキスト情報を割当
	for (int i = 0; i < (int)text.size(); i++)
	{ // 文字列数分繰り返す

		// 文字列を最後尾に追加
		pModule->PushBackString(text[i]);
	}
#endif

	// 文字送りを開始する
	pModule->SetTextEnableScroll(true);
#endif

	return S_OK;
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

//============================================================
//	テキストボックスの読込処理
//============================================================
AText CFrame2DModuleText::LoadTextBox(const std::string& rPath, const std::string& rBoxKey, const std::string& rTextKey)
{
	// 読込の開始文字列を作成
	std::string sLoadStart = "TEXTBOX_";	// 認識用の先頭文字を設定
	sLoadStart.append(rBoxKey);				// 引数の認識用文字列と連結

	// ファイルを開く
	std::ifstream file(rPath);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "テキストファイルの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return {};
	}

	// ファイルを読込
	AText text;			// テキスト情報
	std::string str;	// 読込文字列
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
		else if (str == sLoadStart)
		{ // 読込開始の文字列と一致した場合

			// テキストの読込
			LoadText(&file, &text, rTextKey);
		}
	}

	// ファイルを閉じる
	file.close();

	// テキスト情報を返す
	return text;
}

//============================================================
//	テキストの読込処理
//============================================================
void CFrame2DModuleText::LoadText(std::ifstream* pFile, AText* pText, const std::string& rTextKey)
{
	// テキスト保存ポインタがない場合抜ける
	if (pText == nullptr) { assert(false); return; }

	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return; }

	// 読込の開始文字列を作成
	std::string sLoadStart = "TEXT_";	// 認識用の先頭文字を設定
	sLoadStart.append(rTextKey);		// 引数の認識用文字列と連結

	// ファイルを読込
	std::string str;	// 読込文字列
	do { // END_TEXTBOXを読み込むまでループ

		// 文字列を読み込む
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// コメントアウト
		else if (str == sLoadStart)
		{ // 読込開始の文字列と一致した場合

			// 文字列の読込
			LoadString(pFile, pText);
		}
	} while (str != "END_TEXTBOX");	// END_TEXTBOXを読み込むまでループ
}

//============================================================
//	文字列の読込処理
//============================================================
void CFrame2DModuleText::LoadString(std::ifstream* pFile, AText* pText)
{
	// テキスト保存ポインタがない場合抜ける
	if (pText == nullptr) { assert(false); return; }

	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return; }

	// ファイルを読込
	std::string str;	// 読込文字列
	do { // END_TEXTを読み込むまでループ

		// 文字列を読み込む
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// コメントアウト
		else if (str == "NEXT")
		{
			*pFile >> str;				// ＝を読込
			*pFile >> m_sNextTextKey;	// 次テキストの検索キーを読込
		}
		else if (str == "STR")
		{
			*pFile >> str;					// ＝を読込
			pFile->seekg(1, std::ios::cur);	// 読込位置を空白分ずらす
			std::getline(*pFile, str);		// 一行全て読み込む

			// 文字列の先頭に空白を追加
			str.insert(0, " ");

			// 文字列を最後尾に追加
			pText->push_back(str);
		}

	} while (str != "END_TEXT");	// END_TEXTを読み込むまでループ
}

//============================================================
//	次テキストボックスがあるかの確認処理
//============================================================
bool CFrame2DModuleText::IsNextTextBox(std::string* pPath, std::string* pBoxKey)
{
	// 読込の開始文字列を作成
	std::string sLoadStart = "TEXTBOX_";	// 認識用の先頭文字を設定
	sLoadStart.append(*pBoxKey);			// 引数の認識用文字列と連結

	// ファイルを開く
	std::ifstream file(*pPath);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "テキストファイルの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return false;
	}

	// ファイルを読込
	AText text;			// テキスト情報
	std::string str;	// 読込文字列
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
		else if (str == sLoadStart)
		{ // 読込開始の文字列と一致した場合

			do { // END_TEXTBOXを読み込むまでループ

				// 文字列を読み込む
				file >> str;

				if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
				else if (str == "NEXT_PATH")
				{
					file >> str;		// ＝を読込
					file >> *pPath;		// 次テキストボックスの保存パスを読込
				}
				else if (str == "NEXT_KEY")
				{
					file >> str;		// ＝を読込
					file >> *pBoxKey;	// 次テキストボックスの検索キーを読込
				}
			} while (str != "END_TEXTBOX");	// END_TEXTBOXを読み込むまでループ
		}
	}

	// ファイルを閉じる
	file.close();

	// 次のテキストボックスがあるかを返す
	return !(*pBoxKey == "-1" || *pBoxKey == "NONE");
}
