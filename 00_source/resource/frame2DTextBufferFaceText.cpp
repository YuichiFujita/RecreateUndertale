//============================================================
//
//	表情付きテキスト保存バッファ処理 [frame2DTextBufferFaceText.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferFaceText.h"
#include "frame2DTextStateFaceText.h"

//************************************************************
//	子クラス [CFrame2DTextBufferFaceText] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2DTextBufferFaceText::CFrame2DTextBufferFaceText(const int nIdxFace) :
	m_nIdxFace		(nIdxFace),	// 顔インデックス
	m_nTypeTalkEmo	(0),		// 会話中の表情種類
	m_nTypeIdolEmo	(0)			// 待機中の表情種類
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextBufferFaceText::~CFrame2DTextBufferFaceText()
{

}

//============================================================
//	テキスト機能状態の生成処理
//============================================================
CFrame2DTextState* CFrame2DTextBufferFaceText::CreateState()
{
	// 表情付きテキスト状態を生成し返す
	return new CFrame2DTextStateFaceText;
}

//============================================================
//	バッファごとのセットアップ処理
//============================================================
void CFrame2DTextBufferFaceText::LoadSetup(std::ifstream* pFile, const std::string& rString)
{
	// 基底バッファのセットアップ
	CFrame2DTextBufferText::LoadSetup(pFile, rString);

	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return; }

	// 表情付きテキスト保存バッファに変換できない場合抜ける
	CFrame2DTextBufferFaceText* pBuffFaceText = GetBufferFaceText();
	if (pBuffFaceText == nullptr) { assert(false); return; }

	// ファイルを読込
	std::string str;	// 読込文字列
	if (rString == "TALK_EMO")
	{
		*pFile >> str;								// ＝を読込
		*pFile >> pBuffFaceText->m_nTypeTalkEmo;	// 会話中の表情種類を読込
	}
	else if (rString == "IDOL_EMO")
	{
		*pFile >> str;								// ＝を読込
		*pFile >> pBuffFaceText->m_nTypeIdolEmo;	// 待機中の表情種類を読込
	}
}
