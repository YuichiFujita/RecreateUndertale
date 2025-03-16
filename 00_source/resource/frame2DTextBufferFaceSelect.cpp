//============================================================
//
//	表情/選択付きテキスト保存バッファ処理 [frame2DTextBufferFaceSelect.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DTextBufferFaceSelect.h"
#include "frame2DTextStateFaceSelect.h"

//************************************************************
//	子クラス [CFrame2DTextBufferFaceSelect] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2DTextBufferFaceSelect::CFrame2DTextBufferFaceSelect(const int nIdxFace) :
	m_nIdxFace		(nIdxFace),	// 顔インデックス
	m_nTypeTalkEmo	(0),		// 会話中の表情種類
	m_nTypeIdolEmo	(0)			// 待機中の表情種類
{

}

//============================================================
//	デストラクタ
//============================================================
CFrame2DTextBufferFaceSelect::~CFrame2DTextBufferFaceSelect()
{

}

//============================================================
//	テキスト機能状態の生成処理
//============================================================
CFrame2DTextState* CFrame2DTextBufferFaceSelect::CreateState()
{
	// 表情/選択付きテキスト状態を生成し返す
	return new CFrame2DTextStateFaceSelect;
}

//============================================================
//	バッファごとのセットアップ処理
//============================================================
void CFrame2DTextBufferFaceSelect::LoadSetup(std::ifstream* pFile, const std::string& rString)
{
	// 基底バッファのセットアップ
	CFrame2DTextBufferSelect::LoadSetup(pFile, rString);

	// ファイルポインタがない場合抜ける
	if (pFile == nullptr) { assert(false); return; }

	// 開けてないファイルの場合抜ける
	if (!pFile->is_open()) { assert(false); return; }

	// 表情/選択付きテキスト保存バッファに変換できない場合抜ける
	CFrame2DTextBufferFaceSelect* pBuffFaceSelect = GetBufferFaceSelect();
	if (pBuffFaceSelect == nullptr) { assert(false); return; }

	// ファイルを読込
	std::string str;	// 読込文字列
	if (rString == "TALK_EMO")
	{
		*pFile >> str;								// ＝を読込
		*pFile >> pBuffFaceSelect->m_nTypeTalkEmo;	// 会話中の表情種類を読込
	}
	else if (rString == "IDOL_EMO")
	{
		*pFile >> str;								// ＝を読込
		*pFile >> pBuffFaceSelect->m_nTypeIdolEmo;	// 待機中の表情種類を読込
	}
}
