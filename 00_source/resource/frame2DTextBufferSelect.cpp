//============================================================
//
//	選択付きテキスト保存バッファ処理 [frame2DTextBufferSelect.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferSelect.h"

//************************************************************
//	子クラス [CFrame2DTextBufferSelect] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2DTextBufferSelect::CFrame2DTextBufferSelect()
{
	// メンバ変数をクリア
	for (int i = 0; i < CFrame2DTextStateSelect::SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		m_aNextTextKey[i] = {};	// 次テキストの検索キー
		m_aSelect[i] = {};		// 選択テキスト保存
	}
}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextBufferSelect::~CFrame2DTextBufferSelect()
{

}

//============================================================
//	テキスト機能状態の生成処理
//============================================================
CFrame2DTextState* CFrame2DTextBufferSelect::CreateState(const CFrame2D::EPreset preset)
{
	// 選択付きテキスト状態を生成し返す
	return new CFrame2DTextStateSelect(preset);
}

//============================================================
//	現在キーの文字列読込処理
//============================================================
void CFrame2DTextBufferSelect::LoadKeyString(std::ifstream* pFile, std::string& rString)
{
	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return; }

	if (rString == "SELECT_LEFT")
	{
		// 選択肢文字列の読込
		LoadSelect(pFile, CFrame2DTextStateSelect::SELECT_LEFT);
	}
	else if (rString == "SELECT_RIGHT")
	{
		// 選択肢文字列の読込
		LoadSelect(pFile, CFrame2DTextStateSelect::SELECT_RIGHT);
	}
}

//============================================================
//	選択肢文字列の読込処理
//============================================================
void CFrame2DTextBufferSelect::LoadSelect(std::ifstream* pFile, const CFrame2DTextStateSelect::ESelect select)
{
	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return; }

	// 選択付きテキスト保存ポインタに変換できない場合抜ける
	CFrame2DTextBufferSelect* pSelect = GetBufferSelect();
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
