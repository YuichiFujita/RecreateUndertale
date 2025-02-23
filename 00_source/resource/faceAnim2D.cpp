//============================================================
//
//	表情アニメーション2D処理 [faceAnim2D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "faceAnim2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* LOAD_TXT = "data\\TXT\\FACE\\info.txt";	// 顔テキスト相対パス
}

//************************************************************
//	親クラス [CFaceAnim2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFaceAnim2D::CFaceAnim2D()
{
	// 顔情報の連想配列をクリア
	m_vecFace.clear();
}

//============================================================
//	デストラクタ
//============================================================
CFaceAnim2D::~CFaceAnim2D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFaceAnim2D::Init()
{
	// 顔情報の連想配列を初期化
	m_vecFace.clear();

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFaceAnim2D::Uninit()
{
	for (auto& rVec : m_vecFace)
	{ // 顔情報数分繰り返す

		// 表情情報をクリア
		rVec.vecEmotion.clear();
	}

	// 顔情報の連想配列をクリア
	m_vecFace.clear();
}

//============================================================
//	全読込処理
//============================================================
HRESULT CFaceAnim2D::LoadAll()
{
	// 顔情報のセットアップ
	if (FAILED(LoadSetup()))
	{ // セットアップに失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	顔情報の取得処理
//============================================================
CFaceAnim2D::SFace CFaceAnim2D::GetInfo(const int nIdx)
{
	int nArray = (int)m_vecFace.size();	// 配列要素数
	if (nIdx > NONE_IDX && nIdx < nArray)
	{ // 顔がある場合

		// 引数の顔情報を返す
		return m_vecFace[nIdx];
	}

	// 空の顔情報を返す
	assert(false);
	return m_vecFace[0];
}

//============================================================
//	生成処理
//============================================================
CFaceAnim2D* CFaceAnim2D::Create()
{
	// 表情アニメーション2Dの生成
	CFaceAnim2D* pCharacter = new CFaceAnim2D;
	if (pCharacter == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 表情アニメーション2Dの初期化
		if (FAILED(pCharacter->Init()))
		{ // 初期化に失敗した場合

			// 表情アニメーション2Dの破棄
			SAFE_DELETE(pCharacter);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pCharacter;
	}
}

//============================================================
//	破棄処理
//============================================================
void CFaceAnim2D::Release(CFaceAnim2D*& prCharacter)
{
	// 表情アニメーション2Dの終了
	assert(prCharacter != nullptr);
	prCharacter->Uninit();

	// メモリ開放
	SAFE_DELETE(prCharacter);
}

//============================================================
//	セットアップ処理
//============================================================
HRESULT CFaceAnim2D::LoadSetup()
{
	// ファイルを開く
	std::ifstream file(LOAD_TXT);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "顔セットアップの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ファイルを読込
	std::string str;	// 読込文字列
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#')
		{ // コメントアウトされている場合

			// 一行全て読み込む
			std::getline(file, str);
		}
		else if (str == "FACEPATH")
		{
			file >> str;	// ＝を読込
			file >> str;	// 顔パスを読込

			// 顔パスを読込
			SFace infoFace;	// 顔情報
			if (FAILED(LoadFaceSetup(&infoFace, str.c_str())))
			{ // 読込に失敗した場合

				assert(false);
				return E_FAIL;
			}

			// 顔情報を最後尾に追加
			m_vecFace.push_back(infoFace);
		}
	}

	// ファイルを閉じる
	file.close();

	return S_OK;
}

//============================================================
//	顔情報セットアップ処理
//============================================================
HRESULT CFaceAnim2D::LoadFaceSetup(SFace* pInfoFace, const char* pFacePath)
{
	// ファイルを開く
	std::ifstream file(pFacePath);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "顔情報セットアップの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ファイルを読込
	std::string str;	// 読込文字列
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#')
		{ // コメントアウトされている場合

			// 一行全て読み込む
			std::getline(file, str);
		}
		else if (str == "EMOTIONPATH")
		{
			file >> str;	// ＝を読込
			file >> str;	// 表情パスを読込

			// 表情パスを読込
			if (FAILED(LoadEmotionSetup(pInfoFace, str.c_str())))
			{ // 読込に失敗した場合

				assert(false);
				return E_FAIL;
			}
		}
	}

	// ファイルを閉じる
	file.close();

	return S_OK;
}

//============================================================
//	表情情報セットアップ処理
//============================================================
HRESULT CFaceAnim2D::LoadEmotionSetup(SFace* pInfoFace, const char* pEmoPath)
{
	// ファイルを開く
	std::ifstream file(pEmoPath);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "表情情報セットアップの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 最後尾に表情情報を追加
	int nCurEmotionIdx = pInfoFace->GetNumEmotion();	// 現在の最後尾インデックス
	pInfoFace->vecEmotion.emplace_back();				// 空の要素を最後尾に追加

	// 変数をポインタ化し簡略化
	SEmotion* pInfoEmo = &pInfoFace->vecEmotion[nCurEmotionIdx];	// 表情情報

	// ファイルを読込
	std::string str;	// 読込文字列
	while (file >> str)
	{ // ファイルの終端ではない場合ループ

		if (str.front() == '#')
		{ // コメントアウトされている場合

			// 一行全て読み込む
			std::getline(file, str);
		}
		else if (str == "TEXTURE_PATH")
		{
			file >> str;					// ＝を読込
			file >> pInfoEmo->sPathTexture;	// テクスチャパスを読込
		}
		else if (str == "TEX_PATTERN")
		{
			POSGRID2 ptrnTexture;	// テクスチャ分割数
			file >> str;			// ＝を読込
			file >> ptrnTexture.x;	// テクスチャ横分割を読込
			file >> ptrnTexture.y;	// テクスチャ縦分割を読込

			// テクスチャ分割数・パターン総数を設定
			if (FAILED(pInfoEmo->SetTexPtrn(ptrnTexture)))
			{ // 設定に失敗した場合

				assert(false);
				return E_FAIL;
			}
		}
		else if (str == "OFFSET_ORIGIN")
		{
			file >> str;				// ＝を読込
			file >> pInfoEmo->offset.x;	// 原点オフセットXを読込
			file >> pInfoEmo->offset.y;	// 原点オフセットYを読込
			file >> pInfoEmo->offset.z;	// 原点オフセットZを読込
		}
		else if (str == "CHARA_SIZE")
		{
			file >> str;				// ＝を読込
			file >> pInfoEmo->size.x;	// 顔大きさXを読込
			file >> pInfoEmo->size.y;	// 顔大きさYを読込
			file >> pInfoEmo->size.z;	// 顔大きさZを読込
		}
		else if (str == "NEXT_TIME")
		{
			float fNextTime = 0.0f;	// パターン変更時間
			file >> str;			// ＝を読込
			file >> fNextTime;		// パターン変更時間を読込

			// パターン変更時間を設定
			if (FAILED(pInfoEmo->SetNextTime(fNextTime)))
			{ // 設定に失敗した場合

				assert(false);
				return E_FAIL;
			}
		}
		else if (str == "LOOP")
		{
			int nCastBool = 0;	// bool型変換
			file >> str;		// ＝を読込
			file >> nCastBool;	// ループのON/OFFを読込

			// 読み込んだ値をbool型に変換
			pInfoEmo->bLoop = (nCastBool != 0);
		}
		else if (str == "LOOP_WAIT")
		{
			file >> str;						// ＝を読込
			file >> pInfoEmo->fLoopWaitTime;	// ループ待機時間を読込
		}
	}

	// ファイルを閉じる
	file.close();

	return S_OK;
}
