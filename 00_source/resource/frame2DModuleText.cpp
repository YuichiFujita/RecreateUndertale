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
#include "frame2DTextBuffer.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const std::string KEY_TEXT = "TEXT_";				// テキスト読込開始キー
	const int KET_TEXT_LEN = (int)KEY_TEXT.length();	// 読込開始テキストキーの文字数
}

//************************************************************
//	子クラス [CFrame2DModuleText] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2DModuleText::CFrame2DModuleText(const bool bAutoUninit) :
	m_pState			(nullptr),		// 状態
	m_pMapBuffText		(nullptr),		// テキストバッファ連想配列
	m_sNextPath			(""),			// 次テキストボックスの保存パス
	m_sNextBoxKey		(""),			// 次テキストボックスの検索キー
	m_sStartKey			(""),			// テキストボックスのテキスト開始キー
	m_bAutoUninitFrame	(bAutoUninit)	// フレーム自動破棄フラグ
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
	m_pState		= nullptr;	// 状態
	m_pMapBuffText	= nullptr;	// テキストバッファ連想配列
	m_sNextPath		= "NONE";	// 次テキストボックスの保存パス
	m_sNextBoxKey	= "NONE";	// 次テキストボックスの検索キー
	m_sStartKey		= "NONE";	// テキストボックスのテキスト開始キー

	CFrame2D::EPreset preset = GetFramePreset();	// 配置プリセット
	if (preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX)
	{ // プリセットが範囲内の場合

		// テキスト状態を生成
		ChangeState(new CFrame2DTextStateText(preset));	// 配置指定
	}
	else
	{ // プリセットが範囲外の場合

		// テキスト状態を生成
		ChangeState(new CFrame2DTextStateText);	// デフォルト
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrame2DModuleText::Uninit()
{
	// テキストバッファの破棄
	ReleaseBuffText();

	// 状態の終了
	SAFE_UNINIT(m_pState);

	// 機能の初期化
	m_pContext->InitModule();

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CFrame2DModuleText::Update(const float fDeltaTime)
{
	// 状態ごとの更新
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	優先順位の設定処理
//============================================================
void CFrame2DModuleText::SetPriority(const int nPriority)
{
	// テキスト状態の優先順位を設定
	m_pState->SetPriority(nPriority);
}

//============================================================
//	位置の設定処理
//============================================================
void CFrame2DModuleText::SetVec3Position(const VECTOR3& rPos)
{
	// テキスト状態の位置を設定
	m_pState->SetVec3Position(rPos);
}

//============================================================
//	向きの設定処理
//============================================================
void CFrame2DModuleText::SetVec3Rotation(const VECTOR3& rRot)
{
	// テキスト状態の向きを設定
	m_pState->SetVec3Rotation(rRot);
}

//============================================================
//	テキストバッファ連想配列の割当処理
//============================================================
void CFrame2DModuleText::BindMapBuffText
(
	AMapBuffText* pMapBuffText,		// テキストバッファ連想配列ポインタ
	const std::string& rFilePath,	// 次テキストボックスの保存パス
	const std::string& rBoxKey,		// 次テキストボックスの検索キー
	const std::string& rStartKey	// テキストボックスのテキスト開始キー
)
{
	// テキストバッファの破棄
	ReleaseBuffText();

	// テキストバッファ連想配列の割当
	m_pMapBuffText = pMapBuffText;

	// 次テキストボックス情報の割当
	m_sNextPath		= rFilePath;	// 次テキストボックスの保存パス
	m_sNextBoxKey	= rBoxKey;		// 次テキストボックスの検索キー
	m_sStartKey		= rStartKey;	// テキストボックスのテキスト開始キー
}

//============================================================
//	テキストボックスの割当処理 (失敗無視)
//============================================================
CFrame2DModuleText::ETextResult CFrame2DModuleText::BindTextBoxIgnoreFail
(
	const std::string& rFilePath,	// 次テキストボックスの保存パス
	const std::string& rBoxKey		// 次テキストボックスの検索キー
)
{
	// テキストボックスの読込
	ETextResult tr = LoadTextBoxIgnoreFail(rFilePath, rBoxKey);
	if (TR_SAFE_FAIL(tr))
	{ // 読込に失敗した場合

		return tr;
	}

	// テキストの割当
	if (FAILED(BindText(m_sStartKey)))
	{ // 割当に失敗した場合

		assert(false);
		return RES_FAIL;
	}

	return RES_OK;
}

//============================================================
//	テキストボックスの割当処理 (失敗停止)
//============================================================
HRESULT CFrame2DModuleText::BindTextBox
(
	const std::string& rFilePath,	// 次テキストボックスの保存パス
	const std::string& rBoxKey		// 次テキストボックスの検索キー
)
{
	// テキストボックスの割当
	ETextResult tr = BindTextBoxIgnoreFail(rFilePath, rBoxKey);
	if (TR_SAFE_FAIL(tr))
	{ // 割当に失敗した場合

		// エラーメッセージボックス
		switch (tr)
		{ // テキストリザルトごとの処理
		case RES_TEXTBOX_FAIL:
			MessageBox(nullptr, "テキストボックスの割り当てに失敗！", "警告！", MB_ICONWARNING);
			break;

		case RES_TEXT_FAIL:
			MessageBox(nullptr, "テキストの割り当てに失敗！", "警告！", MB_ICONWARNING);
			break;

		default:
			MessageBox(nullptr, "テキストボックスの割り当て時に例外が発生！", "警告！", MB_ICONWARNING);
			break;
		}

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	テキスト割当処理
//============================================================
HRESULT CFrame2DModuleText::BindText(const std::string& rTextKey)
{
	// 引数キーのテキストを検索
	auto itr = m_pMapBuffText->find(rTextKey);
	if (itr == m_pMapBuffText->end()) { assert(false); return E_FAIL; }

	// テキストバッファを簡略化
	CFrame2DTextBuffer* pNextBuffText = itr->second;

	// テキスト機能状態の変更
	CFrame2D::EPreset preset = GetFramePreset();					// フレームプリセット
	CFrame2DTextState* pState = pNextBuffText->CreateState(preset);	// テキスト機能状態
	if (FAILED(ChangeState(pState)))
	{ // 変更に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// テキストバッファの割当
	m_pState->BindTextBuffer(pNextBuffText);

	return S_OK;
}

//============================================================
//	テキストの遷移処理
//============================================================
HRESULT CFrame2DModuleText::TransText(const std::string& rNextTextKey)
{
	if (rNextTextKey == "-1"
	||  rNextTextKey == "NONE"
	||  rNextTextKey.empty())
	{ // テキスト遷移先がない場合

		if (m_sNextPath == "-1"
		||  m_sNextPath == "NONE"
		||  m_sNextPath.empty()
		||  m_sNextBoxKey == "-1"
		||  m_sNextBoxKey == "NONE"
		||  m_sNextBoxKey.empty())
		{ // テキストボックス遷移先がない場合

			if (m_bAutoUninitFrame)
			{ // フレーム自動破棄がONの場合

				// コンテキストの終了
				SAFE_UNINIT(m_pContext);
			}
			else
			{ // フレーム自動破棄がOFFの場合

				// テキスト表示機能の終了
				Uninit();
			}
		}
		else
		{ // テキストボックス遷移先がある場合

			// 次のテキストボックスを割当
			if (FAILED(BindTextBox(m_sNextPath, m_sNextBoxKey)))
			{ // 割当に失敗した場合

				assert(false);
				return E_FAIL;
			}
		}
	}
	else
	{ // テキスト遷移先がある場合

		// 次のテキストを割当
		if (FAILED(BindText(rNextTextKey)))
		{ // 割当に失敗した場合

			assert(false);
			return E_FAIL;
		}
	}

	return S_OK;
}

//============================================================
//	状態の変更処理
//============================================================
HRESULT CFrame2DModuleText::ChangeState(CFrame2DTextState* pState)
{
	// 状態の生成に失敗している場合抜ける
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// 状態インスタンスを終了
	SAFE_UNINIT(m_pState);

	// 状態インスタンスを変更
	assert(m_pState == nullptr);
	m_pState = pState;

	// 状態にコンテキストを設定
	m_pState->SetContext(this);

	// 状態インスタンスを初期化
	if (FAILED(m_pState->Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	文字列の先頭追加処理 (マルチバイト文字列)
//============================================================
HRESULT CFrame2DModuleText::PushFrontString(const std::string& rStr, const std::string& rTextKey)
{
	// 引数キーのテキストを検索
	auto itr = m_pMapBuffText->find(rTextKey);
	if (itr == m_pMapBuffText->end()) { assert(false); return E_FAIL; }

	// テキストを簡略化
	AText* pText = &itr->second->m_text;

	// 先頭に文字列を追加
	pText->insert(pText->begin(), rStr);

	// 状態が未設定の場合抜ける
	if (m_pState == nullptr) { return S_OK; }

	if (rTextKey == m_pState->GetCurTextKey())
	{ // 現在の割当テキスト保存キーと同一の場合

		// 追加したテキストを反映
		if (FAILED(BindText(rTextKey)))
		{ // 割当に失敗した場合

			return E_FAIL;
		}
	}

	return S_OK;
}

//============================================================
//	文字列の先頭追加処理 (ワイド文字列)
//============================================================
HRESULT CFrame2DModuleText::PushFrontString(const std::wstring& rStr, const std::string& rTextKey)
{
	// 文字列をマルチバイト変換
	std::string sStr = useful::WideToMultiByte(rStr);

	// 文字列を先頭に追加
	if (FAILED(PushFrontString(sStr, rTextKey)))
	{ // 追加に失敗した場合

		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	文字列の最後尾追加処理 (マルチバイト文字列)
//============================================================
HRESULT CFrame2DModuleText::PushBackString(const std::string& rStr, const std::string& rTextKey)
{
	// 引数キーのテキストを検索
	auto itr = m_pMapBuffText->find(rTextKey);
	if (itr == m_pMapBuffText->end()) { assert(false); return E_FAIL; }

	// テキストを簡略化
	AText* pText = &itr->second->m_text;

	// 最後尾に文字列を追加
	pText->push_back(rStr);

	// 状態が未設定の場合抜ける
	if (m_pState == nullptr) { return S_OK; }

	if (rTextKey == m_pState->GetCurTextKey())
	{ // 現在の割当テキスト保存キーと同一の場合

		// 追加したテキストを反映
		if (FAILED(BindText(rTextKey)))
		{ // 割当に失敗した場合

			return E_FAIL;
		}
	}

	return S_OK;
}

//============================================================
//	文字列の最後尾追加処理 (ワイド文字列)
//============================================================
HRESULT CFrame2DModuleText::PushBackString(const std::wstring& rStr, const std::string& rTextKey)
{
	// 文字列をマルチバイト変換
	std::string sStr = useful::WideToMultiByte(rStr);

	// 文字列を最後尾に追加
	if (FAILED(PushBackString(sStr, rTextKey)))
	{ // 追加に失敗した場合

		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	行数の取得処理
//============================================================
int CFrame2DModuleText::GetNumString(const std::string& rTextKey) const
{
	// 引数キーのテキストを検索
	auto itr = m_pMapBuffText->find(rTextKey);
	if (itr == m_pMapBuffText->end()) { assert(false); return NONE_IDX; }

	// テキストを簡略化
	AText* pText = &itr->second->m_text;

	// テキストの行数を返す
	return (int)pText->size();
}

//============================================================
//	テキスト数の取得処理
//============================================================
int CFrame2DModuleText::GetNumText() const
{
	// テキストバッファ配列がない場合エラー
	if (m_pMapBuffText == nullptr) { assert(false); return 0; }

	// 現在のテキスト数を返す
	return (int)m_pMapBuffText->size();
}

//============================================================
//	テキストバッファ連想配列の破棄処理
//============================================================
void CFrame2DModuleText::ReleaseBuffText()
{
	// テキストが存在しない場合抜ける
	if (m_pMapBuffText == nullptr) { return; }

	for (auto& rMap : *m_pMapBuffText)
	{ // 要素数分繰り返す

		// テキストバッファの破棄
		SAFE_DELETE(rMap.second);
	}

	// テキストバッファ連想配列をクリア
	m_pMapBuffText->clear();

	// テキストバッファ連想配列の破棄
	SAFE_DELETE(m_pMapBuffText);
}

//============================================================
//	テキストバッファの生成処理
//============================================================
CFrame2DTextBuffer* CFrame2DModuleText::CreateBuffText(const std::string& rCreateKey, const int nFaceIdx)
{
	// TODO：追加したら修正
	// 生成キーに応じた保存バッファの生成
	if		(rCreateKey == "TEXT")
	{
		// 顔インデックスに応じて生成変更
		if (nFaceIdx == -1)	{ return new CFrame2DTextBufferText; }			// テキスト保存バッファ
		else				{ return new CFrame2DTextBufferText; }			// 表情付きテキスト保存バッファ
	}
	else if	(rCreateKey == "SELECT")
	{
		// 顔インデックスに応じて生成変更
		if (nFaceIdx == -1)	{ return new CFrame2DTextBufferSelect; }		// 選択付きテキスト保存バッファ
		else				{ return new CFrame2DTextBufferSelect; }		// 表情/選択付きテキスト保存バッファ
	}
	else if	(rCreateKey == "ITEM") { return new CFrame2DTextBufferItem; }	// アイテムテキスト保存バッファ

	// 存在しない生成キーの場合エラー
	assert(false);
	return nullptr;
}

//============================================================
//	テキストボックスの読込処理 (例外無視)
//============================================================
CFrame2DModuleText::ETextResult CFrame2DModuleText::LoadTextBoxIgnoreFail(const std::string& rFilePath, const std::string& rBoxKey)
{
	// 読込の開始文字列を作成
	std::string sLoadStart = "TEXTBOX_";	// 認識用の先頭文字を設定
	sLoadStart.append(rBoxKey);				// 引数の認識用文字列と連結

	// ファイルを開く
	std::ifstream file(rFilePath);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "テキストファイルの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return RES_FAIL;
	}

	// ファイルを読込
	std::string str;					// 読込文字列
	ETextResult tr = RES_TEXTBOX_FAIL;	// 読込フラグ
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
		else if (str == sLoadStart)
		{ // 読込開始の文字列と一致した場合

			// テキストの読込
			tr = LoadText(&file, rFilePath);
			break;
		}
	}

	// ファイルを閉じる
	file.close();

	// テキストが存在したかを返す
	return tr;
}

//============================================================
//	テキストボックスの読込処理 (失敗停止)
//============================================================
HRESULT CFrame2DModuleText::LoadTextBox(const std::string& rFilePath, const std::string& rBoxKey)
{
	// テキストボックスの読込
	ETextResult tr = LoadTextBoxIgnoreFail(rFilePath, rBoxKey);
	if (TR_SAFE_FAIL(tr))
	{ // 読込に失敗した場合

		// エラーメッセージボックス
		switch (tr)
		{ // テキストリザルトごとの処理
		case RES_TEXTBOX_FAIL:
			MessageBox(nullptr, "テキストボックスの読み込みに失敗！", "警告！", MB_ICONWARNING);
			break;

		case RES_TEXT_FAIL:
			MessageBox(nullptr, "テキストの読み込みに失敗！", "警告！", MB_ICONWARNING);
			break;

		default:
			MessageBox(nullptr, "テキストボックスの読み込み時に例外が発生！", "警告！", MB_ICONWARNING);
			break;
		}

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	テキストの読込処理
//============================================================
CFrame2DModuleText::ETextResult CFrame2DModuleText::LoadText(std::ifstream* pFile, const std::string& rFilePath)
{
	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return RES_FAIL; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return RES_FAIL; }

	// ファイルを読込
	std::string str;			// 読込文字列
	std::string sModuleKey;		// モジュール生成キー
	int nFaceIdx = NONE_IDX;	// 顔インデックス
	std::string sNextPath		= rFilePath;	// 次テキストボックスの保存パス
	std::string sNextBoxKey		= "NONE";		// 次テキストボックスの検索キー
	std::string sStartKey		= "0";			// テキストボックスのテキスト開始キー
	AMapBuffText* pMapBuffText	= nullptr;		// テキストバッファ連想配列
	do { // END_TEXTBOXを読み込むまでループ

		// 文字列を読み込む
		*pFile >> str;

		// テキスト開始キーを検索
		size_t idxFind = str.find(KEY_TEXT);

		if (str.front() == '#') { std::getline(*pFile, str); }	// コメントアウト
		else if (idxFind != std::string::npos)
		{ // テキスト開始キーがあった場合

			// 文字列の読込
			CFrame2DTextBuffer* pBuffText = LoadString(pFile, sModuleKey, nFaceIdx);	// 読み込んだテキストバッファ取得
			if (pBuffText == nullptr)
			{ // 生成に失敗した場合

				assert(false);
				return RES_FAIL;
			}

			// テキストの検索キー以外の部分を削除
			str.erase(0, idxFind + KET_TEXT_LEN);

			// 読み込んだファイルパスを保存
			pBuffText->m_sPath = rFilePath;

			// テキストの検索キーを保存
			pBuffText->m_sKey = str;

			if (pMapBuffText == nullptr)
			{ // テキストバッファ連想配列が未生成の場合

				// テキストバッファ連想配列の生成
				pMapBuffText = new AMapBuffText;
				if (pMapBuffText == nullptr)
				{ // 生成に失敗した場合

					assert(false);
					return RES_FAIL;
				}
			}

			// テキストバッファを保存
			pMapBuffText->insert(std::make_pair(str, pBuffText));
		}
		else if (str == "NEXT_PATH")
		{
			*pFile >> str;			// ＝を読込
			*pFile >> sNextPath;	// 次テキストボックスの保存パスを読込
		}
		else if (str == "NEXT_BOX")
		{
			*pFile >> str;			// ＝を読込
			*pFile >> sNextBoxKey;	// 次テキストボックスの検索キーを読込
		}
		else if (str == "START_KEY")
		{
			*pFile >> str;			// ＝を読込
			*pFile >> sStartKey;	// テキストボックスのテキスト開始キーを読込
		}
		else if (str == "ALL_MODULE")
		{
			*pFile >> str;			// ＝を読込
			*pFile >> sModuleKey;	// 生成するモジュールを読込
		}
		else if (str == "FACE")
		{
			*pFile >> str;			// ＝を読込
			*pFile >> nFaceIdx;		// 顔インデックスを読込
		}
	} while (str != "END_TEXTBOX");	// END_TEXTBOXを読み込むまでループ

	if (pMapBuffText != nullptr)
	{ // テキストが存在する場合

		// テキストバッファ連想配列の割当
		BindMapBuffText(pMapBuffText, sNextPath, sNextBoxKey, sStartKey);
		return RES_OK;
	}

	return RES_TEXT_FAIL;
}

//============================================================
//	文字列の読込処理
//============================================================
CFrame2DTextBuffer* CFrame2DModuleText::LoadString(std::ifstream* pFile, const std::string& rModuleKey, const int nFaceIdx)
{
	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return nullptr; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return nullptr; }

	CFrame2DTextBuffer* pBuffText = nullptr;	// テキスト情報保存バッファ
	if (!rModuleKey.empty())
	{ // 生成キーが設定されている場合

		// テキストバッファの生成
		assert(pBuffText == nullptr);
		pBuffText = CreateBuffText(rModuleKey, nFaceIdx);
	}

	// ファイルを読込
	std::string str;	// 読込文字列
	do { // END_TEXTを読み込むまでループ

		// 文字列を読み込む
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// コメントアウト
		else if (str == "MODULE")
		{
			*pFile >> str;	// ＝を読込
			*pFile >> str;	// 生成するモジュールを読込

			if (pBuffText != nullptr)
			{ // テキストバッファが生成済みの場合

				// エラーメッセージボックス
				MessageBox(nullptr, "テキストバッファは生成済みです！", "警告！", MB_ICONWARNING);
			}
			else
			{ // テキストバッファが未生成の場合

				// テキストバッファの生成
				pBuffText = CreateBuffText(str, nFaceIdx);
			}
		}
		else if (str == "STR")
		{
			*pFile >> str;					// ＝を読込
			pFile->seekg(1, std::ios::cur);	// 読込位置を空白分ずらす
			std::getline(*pFile, str);		// 一行全て読み込む

			// 文字列の先頭に空白を追加
			str.insert(0, " ");

			// 文字列を最後尾に追加
			assert(pBuffText != nullptr);
			pBuffText->m_text.push_back(str);
		}
		else if (pBuffText != nullptr)
		{
			// バッファごとのセットアップ読込
			assert(pBuffText != nullptr);
			pBuffText->LoadSetup(pFile, str);
		}
	} while (str != "END_TEXT");	// END_TEXTを読み込むまでループ

	// テキスト情報保存バッファを返す
	return pBuffText;
}
