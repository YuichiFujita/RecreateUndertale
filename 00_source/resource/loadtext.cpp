//============================================================
//
//	テキスト読込関数処理 [loadtext.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "loadtext.h"
#include "text2D.h"
#include "string2D.h"

//============================================================
//	テキストの読込処理
//============================================================
std::vector<std::wstring> loadtext::LoadText(const char *pFilePass, const int nTextID)
{
	std::vector<std::wstring> vecStr;	// 文字列の動的配列
	std::string sLoadStart;				// 読込開始の文字列

	// 読込の開始文字列を作成
	sLoadStart = "TEXT_" + std::to_string(nTextID);	// 引数のインデックスと合わせる

	// ファイルを開く
	std::ifstream file(pFilePass);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "テキストファイルの読み込みに失敗！", "警告！", MB_ICONWARNING);

		// 初期値を返す
		return vecStr;
	}

	// ファイルを読込
	std::string sStr;	// 読込文字列
	while (file >> sStr)
	{ // ファイルの終端ではない場合ループ

		if (sStr.front() == '#')
		{ // コメントアウトされている場合

			// 一行全て読み込む
			std::getline(file, sStr);
		}
		else if (sStr == sLoadStart)
		{ // 読込開始の文字列と一致した場合

			do
			{ // END_TEXTを読み込むまでループ

				// 文字列を読み込む
				file >> sStr;

				if (sStr.front() == '#')
				{ // コメントアウトされている場合

					// 一行全て読み込む
					std::getline(file, sStr);
				}
				else if (sStr == "STR")
				{
					file >> sStr;					// ＝を読込
					file.seekg(1, std::ios::cur);	// 読込位置を空白分ずらす
					std::getline(file, sStr);		// 一行全て読み込む

					// 文字列を最後尾に追加
					vecStr.push_back(useful::MultiByteToWide(&sStr));	// ワイド文字列に変換
				}
			} while (sStr != "END_TEXT");	// END_TEXTを読み込むまでループ
		}
	}

	// ファイルを閉じる
	file.close();

	// 文字列の動的配列を返す
	return vecStr;
}

//============================================================
//	テキストの割当処理
//============================================================
void loadtext::BindText(CText2D *pText2D, const std::vector<std::wstring>& rVecStr)
{
	for (int i = 0; i < (int)rVecStr.size(); i++)
	{ // 文字列数分繰り返す

		// 文字列を追加
		pText2D->AddString(rVecStr[i]);
	}
}

//============================================================
//	文字列の割当処理
//============================================================
void loadtext::BindString(CString2D *pString2D, const std::vector<std::wstring> &rVecStr)
{
	// 文字列が一つではない場合エラー
	assert((int)rVecStr.size() == 1);

	// 文字列を設定
	pString2D->SetString(rVecStr[0]);
}
