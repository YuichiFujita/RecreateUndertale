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
//	子クラス [CFrame2DModuleText] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2DModuleText::CFrame2DModuleText(const bool bAutoUninit) :
	m_mapBuffText		({}),			// テキストバッファ連想配列
	m_pState			(nullptr),		// 状態
	m_sNextPath			({}),			// 次テキストボックスの保存パス
	m_sNextBoxKey		({}),			// 次テキストボックスの検索キー
	m_sNextStartKey		({}),			// 次テキストボックスのテキスト開始キー
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
	m_mapBuffText	= {};		// テキストバッファ連想配列
	m_pState		= nullptr;	// 状態
	m_sNextPath		= "NONE";	// 次テキストボックスの保存パス
	m_sNextBoxKey	= "NONE";	// 次テキストボックスの検索キー
	m_sNextStartKey	= "NONE";	// 次テキストボックスのテキスト開始キー

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
	// テキストバッファの削除
	DeleteBuffText();

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
//	テキストボックスの割当処理
//============================================================
HRESULT CFrame2DModuleText::BindTextBox(const std::string& rFilePath, const std::string& rBoxKey, const std::string& rNextStartKey)
{
	// 次テキストボックスのテキスト開始キーを保存
	const std::string sNextStartKey = rNextStartKey;

	// テキストバッファの削除
	DeleteBuffText();

	// テキストボックスの読込
	if (FAILED(LoadTextBox(rFilePath, rBoxKey)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// テキストの割当
	if (FAILED(BindText(sNextStartKey)))
	{ // 割当に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	テキストの遷移処理
//============================================================
void CFrame2DModuleText::TransText(const std::string& rNextTextKey)
{
	if (rNextTextKey == "-1"
	||  rNextTextKey == "NONE"
	||  rNextTextKey.empty())
	{ // テキスト遷移先がない場合

		if (m_sNextBoxKey == "-1"
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
			BindTextBox(m_sNextPath, m_sNextBoxKey, m_sNextStartKey);	// TODO：選択肢ごとに違うテキストボックスにも飛べるようにする
		}
	}
	else
	{ // テキスト遷移先がある場合

		// 次のテキストを割当
		BindText(rNextTextKey);
	}
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
//	テキスト割当処理
//============================================================
HRESULT CFrame2DModuleText::BindText(const std::string& rTextKey)
{
	// 引数キーのテキストを検索
	auto itr = m_mapBuffText.find(rTextKey);
	if (itr == m_mapBuffText.end()) { assert(false); return E_FAIL; }

	// テキストバッファを簡略化
	CFrame2DTextBuffer* pNextBuffText = itr->second;

	// テキスト機能状態の変更
	ChangeState(pNextBuffText->CreateState(GetFramePreset()));	// 次テキストに使用する機能を取得	// TODO：同じ状態なら変更なしにすれば壊れない

	// テキストバッファの割当
	m_pState->BindTextBuffer(pNextBuffText);

	// TODO：アイテムテキストがテキスト進行ごとにアイテムインデックスを忘れる問題の解決案
	//  １ ：同じテキスト機能状態なら変更しないでテキストの初期化のみ行う
	//  ２ ：frame2DModuleTextItemを作成し、メンバ変数でアイテムインデックスを管理する
	//  ３ ：frame2DTextStateItemが読込毎にアイテムの名前を読み込み、アイテム管理をmapにしてアイテム名からインデックスを検索
	//  ４ ：全く同じものを独自関数として再作成

	return S_OK;
}

//============================================================
//	テキストバッファ連想配列の削除処理
//============================================================
void CFrame2DModuleText::DeleteBuffText()
{
	for (auto& rMap : m_mapBuffText)
	{ // 要素数分繰り返す

		// テキストバッファの破棄
		SAFE_DELETE(rMap.second);
	}

	// テキストバッファ連想配列をクリア
	m_mapBuffText.clear();
}

//============================================================
//	テキストバッファの生成処理
//============================================================
CFrame2DTextBuffer* CFrame2DModuleText::CreateBuffText(const std::string& rCreateKey)
{
	// 生成キーに応じた保存バッファの生成
	if		(rCreateKey == "TEXT")			{ return new CFrame2DTextBufferText; }		// テキスト保存バッファ
	else if	(rCreateKey == "SELECT")		{ return new CFrame2DTextBufferSelect; }	// 選択付きテキスト保存バッファ
	// TODO：追加したら修正
	else if	(rCreateKey == "TEXT_FACE")		{ return new CFrame2DTextBufferText; }		// 表情付きテキスト保存バッファ
	else if	(rCreateKey == "SELECT_FACE")	{ return new CFrame2DTextBufferSelect; }	// 表情/選択付きテキスト保存バッファ
	else if	(rCreateKey == "ITEM")			{ return new CFrame2DTextBufferItem; }		// アイテムテキスト保存バッファ

	// 存在しない生成キーの場合エラー
	assert(false);
	return nullptr;
}

//============================================================
//	テキストボックスの読込処理
//============================================================
HRESULT CFrame2DModuleText::LoadTextBox(const std::string& rFilePath, const std::string& rBoxKey)
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
		return E_FAIL;
	}

	// ファイルを読込
	std::string str;	// 読込文字列
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#') { std::getline(file, str); }	// コメントアウト
		else if (str == sLoadStart)
		{ // 読込開始の文字列と一致した場合

			// テキストの読込
			LoadText(rFilePath, &file);
		}
	}

	// ファイルを閉じる
	file.close();

	return S_OK;
}

//============================================================
//	テキストの読込処理
//============================================================
HRESULT CFrame2DModuleText::LoadText(const std::string& rFilePath, std::ifstream* pFile)
{
	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return E_FAIL; }

	// ファイルを読込
	std::string str;	// 読込文字列
	do { // END_TEXTBOXを読み込むまでループ

		// 文字列を読み込む
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// コメントアウト
		else if (str == "NEXT_PATH")
		{
			*pFile >> str;				// ＝を読込
			*pFile >> m_sNextPath;		// 次テキストボックスの保存パスを読込
		}
		else if (str == "NEXT_BOX")
		{
			*pFile >> str;				// ＝を読込
			*pFile >> m_sNextBoxKey;	// 次テキストボックスの検索キーを読込
		}
		else if (str == "NEXT_START")
		{
			*pFile >> str;				// ＝を読込
			*pFile >> m_sNextStartKey;	// 次テキストボックスのテキスト開始キーを読込
		}

		// TODO：ここでFACEとNAMEのキーを判定
		//		 FACE = -1でないならこれ以降のテキスト生成は顔つき

		else if (size_t findIdx = str.find("TEXT_") != std::string::npos)	// TODO：ここどう書くかは要検討
		{ // 読込開始の文字列が含まれていた場合

			// テキストの検索キーを読込
			str.erase(0, findIdx + 4);	// TODO：定数

			// 文字列の読込
			CFrame2DTextBuffer* pBuffText = LoadString(pFile);	// 読み込んだテキストバッファ取得
			if (pBuffText == nullptr)
			{ // 生成に失敗した場合

				assert(false);
				return E_FAIL;
			}

			// 読み込んだファイルパスを保存
			pBuffText->m_sPath = rFilePath;

			// テキストバッファを保存
			m_mapBuffText.insert(std::make_pair(str, pBuffText));
		}
	} while (str != "END_TEXTBOX");	// END_TEXTBOXを読み込むまでループ

	return S_OK;
}

//============================================================
//	文字列の読込処理
//============================================================
CFrame2DTextBuffer* CFrame2DModuleText::LoadString(std::ifstream* pFile)
{
	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return nullptr; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return nullptr; }

	// ファイルを読込
	CFrame2DTextBuffer* pBuffText = nullptr;	// テキスト情報保存バッファ
	std::string str;	// 読込文字列
	do { // END_TEXTを読み込むまでループ

		// 文字列を読み込む
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// コメントアウト
		else if (str == "MODULE")
		{
			*pFile >> str;	// ＝を読込
			*pFile >> str;	// 生成するモジュールを読込

			// テキストバッファの生成
			assert(pBuffText == nullptr);
			pBuffText = CreateBuffText(str);
		}
		else if (str == "STR")
		{
			*pFile >> str;					// ＝を読込
			pFile->seekg(1, std::ios::cur);	// 読込位置を空白分ずらす
			std::getline(*pFile, str);		// 一行全て読み込む

			// 文字列の先頭に空白を追加
			str.insert(0, " ");

			// 文字列を最後尾に追加
			pBuffText->m_text.push_back(str);
		}
		else if (pBuffText != nullptr)
		{
			// バッファごとのセットアップ読込
			pBuffText->LoadSetup(pFile, str);
		}
	} while (str != "END_TEXT");	// END_TEXTを読み込むまでループ

	// テキスト情報保存バッファを返す
	return pBuffText;
}
