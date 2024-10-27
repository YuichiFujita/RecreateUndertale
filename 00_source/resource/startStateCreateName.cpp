//============================================================
//
//	命名状態処理 [startStateCreateName.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "startStateCreateName.h"
#include "startManager.h"
#include "manager.h"
#include "string2D.h"
#include "shakeString2D.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* PASS_CHAR[] =	// 文字配置情報の相対パス
	{
		"data\\CSV\\char_hiragana.csv",	// ひらがな配置情報
		"data\\CSV\\char_katakana.csv",	// カタカナ配置情報
		"data\\CSV\\char_alphabet.csv",	// アルファベット配置情報
	};

	const char* PASS		= "data\\TEXT\\start.txt";	// テキストパス
	const int PRIORITY		= 6;	// 優先順位
	const int MAX_STR_NAME	= 6;	// 名前の最大文字数

	namespace title
	{	
		const char*	FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 42.0f;	// 文字縦幅

		const VECTOR3	POS = VECTOR3(SCREEN_CENT.x, 80.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;			// 向き
		const COLOR		COL = color::White();		// 色
		const EAlignX	ALIGN_X = XALIGN_CENTER;	// 横配置
	}
	
	namespace name
	{
		const char*	FONT = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC = false;	// イタリック
		const float	HEIGHT = 42.0f;	// 文字縦幅

		const VECTOR3	POS = VECTOR3(360.0f, 155.0f, 0.0f);	// 位置
		const VECTOR3	ROT = VEC3_ZERO;		// 向き
		const COLOR		COL = color::White();	// 色
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// 横配置
	}

	namespace select
	{	
		const VECTOR3 POS[CStartStateCreateName::YSELECT_MAX][CStartStateCreateName::XSELECT_MAX] =	// 位置配列
		{
			{ VECTOR3(180.0f, 530.0f, 0.0f), VECTOR3(440.0f, 530.0f, 0.0f), VECTOR3(750.0f, 530.0f, 0.0f) },
			{ VECTOR3(220.0f, 630.0f, 0.0f), VECTOR3(460.0f, 630.0f, 0.0f), VECTOR3(700.0f, 630.0f, 0.0f) },
		};

		const CStartStateCreateName::ETypeChar INIT_TYPE = CStartStateCreateName::TYPECHAR_HIRAGANA;	// 初期文字セット
		const POSGRID2 INIT_SELECT = POSGRID2(0, 2);	// 初期選択位置

		const char*	FONT		= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC		= false;	// イタリック
		const float	HEIGHT		= 42.0f;	// 文字縦幅
		const float	NEXT_TIME	= 0.035f;	// 文字振動の待機時間
		const float	MOVE		= 1.0f;		// 振動移動量
		const VECTOR3 ROT		= VEC3_ZERO;		// 向き
		const COLOR COL_DEFAULT	= color::White();	// 通常色
		const COLOR COL_CHOICE	= color::Yellow();	// 選択色
		const EAlignX ALIGN_X	= XALIGN_CENTER;	// 横配置
	}
}

//************************************************************
//	子クラス [CStartStateCreateName] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CStartStateCreateName::CStartStateCreateName() :
	m_pTitle	(nullptr),		// タイトル
	m_pName		(nullptr),		// 名前
	m_typeChar	((ETypeChar)0),	// 文字種類
	m_curSelect	(GRID2_ZERO),	// 現在の選択肢
	m_oldSelect	(GRID2_ZERO)	// 前回の選択肢
{
	// 選択文字配列をクリア
	m_vecSelect.clear();
}

//============================================================
//	デストラクタ
//============================================================
CStartStateCreateName::~CStartStateCreateName()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CStartStateCreateName::Init()
{
	// メンバ変数を初期化
	m_pTitle	= nullptr;				// タイトル
	m_pName		= nullptr;				// 名前
	m_typeChar	= (ETypeChar)0;			// 文字種類
	m_curSelect	= select::INIT_SELECT;	// 現在の選択肢
	m_oldSelect	= select::INIT_SELECT;	// 前回の選択肢

	// 選択文字配列を初期化
	m_vecSelect.clear();

	// タイトルの生成
	m_pTitle = CString2D::Create
	( // 引数
		title::FONT,	// フォントパス
		title::ITALIC,	// イタリック
		L"",			// 指定文字列
		title::POS,		// 原点位置
		title::HEIGHT,	// 文字縦幅
		title::ALIGN_X,	// 横配置
		title::ROT,		// 原点向き
		title::COL		// 色
	);
	if (m_pTitle == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pTitle->SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindString(m_pTitle, loadtext::LoadText(PASS, CStartManager::TEXT_NAMING));

	// 名前の生成
	m_pName = CString2D::Create
	( // 引数
		name::FONT,		// フォントパス
		name::ITALIC,	// イタリック
		L"",			// 指定文字列
		name::POS,		// 原点位置
		name::HEIGHT,	// 文字縦幅
		name::ALIGN_X,	// 横配置
		name::ROT,		// 原点向き
		name::COL		// 色
	);
	if (m_pName == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pName->SetPriority(PRIORITY);

	// 保存中の名前を設定
	m_pName->SetString(useful::MultiByteToWide(m_pContext->GetName()));

	for (int i = 0; i < YSELECT_MAX; i++)
	{ // 行の固定選択肢の総数分繰り返す

		// 横一行分の配列を拡張
		m_vecSelect.emplace_back();

		for (int j = 0; j < XSELECT_MAX; j++)
		{ // 列の固定選択肢の総数分繰り返す

			// 選択肢の生成
			CString2D* pSelect = CString2D::Create
			( // 引数
				select::FONT,		// フォントパス
				select::ITALIC,		// イタリック
				L"",				// 指定文字列
				select::POS[i][j],	// 原点位置
				select::HEIGHT,		// 文字縦幅
				select::ALIGN_X,	// 横配置
				select::ROT,		// 原点向き
				select::COL_DEFAULT	// 色
			);
			if (pSelect == nullptr)
			{ // 生成に失敗した場合

				assert(false);
				return E_FAIL;
			}

			// 優先順位を設定
			pSelect->SetPriority(PRIORITY);

			// 文字列を割当
			int nTextIdx = CStartManager::TEXT_HIRAGANA + j + (i * XSELECT_MAX);	// テキストインデックス
			loadtext::BindString(pSelect, loadtext::LoadText(PASS, nTextIdx));

			// 現在の行列の最後尾に生成した文字を追加
			m_vecSelect.back().push_back(pSelect);
		}
	}

	// 配置の読込
	if (FAILED(ChangeChar(select::INIT_TYPE)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CStartStateCreateName::Uninit()
{
	// タイトルの終了
	SAFE_UNINIT(m_pTitle);

	// 名前の終了
	SAFE_UNINIT(m_pName);

	for (int i = 0; i < (int)m_vecSelect.size(); i++)
	{ // 行の総数分繰り返す

		for (int j = 0; j < (int)m_vecSelect[i].size(); j++)
		{ // 列の総数分繰り返す

			// 選択文字の終了
			SAFE_UNINIT(m_vecSelect[i][j]);
		}
	}

	// 選択文字配列をクリア
	m_vecSelect.clear();

	// 自身の破棄
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CStartStateCreateName::Update(const float fDeltaTime)
{
	// 選択の更新
	UpdateSelect();

	// 決定の更新
	UpdateDecide();
}

//============================================================
//	選択の操作処理
//============================================================
void CStartStateCreateName::ControlSelect()
{
	CInputKeyboard* pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_LEFT))
	{
		do { // 選択先がない場合さらに動かす

			// 左に選択をずらす
			int nMaxWidth = (int)m_vecSelect[m_curSelect.y].size();	// 列の最大数
			m_curSelect.x = (m_curSelect.x + (nMaxWidth - 1)) % nMaxWidth;

		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		do { // 選択先がない場合さらに動かす

			// 右に選択をずらす
			int nMaxWidth = (int)m_vecSelect[m_curSelect.y].size();	// 列の最大数
			m_curSelect.x = (m_curSelect.x + 1) % nMaxWidth;

		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		do { // 選択先がない場合さらに動かす

			// 上に選択をずらす
			int nMaxHeight = (int)m_vecSelect.size();	// 行の最大数
			m_curSelect.y = (m_curSelect.y + (nMaxHeight - 1)) % nMaxHeight;

			// 列が増減した場合に列インデックスを補正
			int nPrevSelectY = (m_curSelect.y + 1) % nMaxHeight;
			if (m_vecSelect[m_curSelect.y].size() < m_vecSelect[nPrevSelectY].size())
			{ // 列が減少した場合

				// 列インデックスを小さい方の最大値で補正
				m_curSelect.x /= m_vecSelect[m_oldSelect.y].size() / XSELECT_MAX;
			}
			else if (m_vecSelect[m_curSelect.y].size() > m_vecSelect[nPrevSelectY].size())
			{ // 列が増加した場合

				// 列インデックスを大きい方の最大値で補正
				m_curSelect.x *= m_vecSelect[m_curSelect.y].size() / XSELECT_MAX;
			}

		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}
	if (pKey->IsTrigger(DIK_DOWN))
	{
		do { // 選択先がない場合さらに動かす

			// 下に選択をずらす
			int nMaxHeight = (int)m_vecSelect.size();	// 行の最大数
			m_curSelect.y = (m_curSelect.y + 1) % nMaxHeight;

			// 列が増減した場合に列インデックスを補正
			int nPrevSelectY = (m_curSelect.y + (nMaxHeight - 1)) % nMaxHeight;	// 一つ上の行選択インデックス
			if (m_vecSelect[m_curSelect.y].size() < m_vecSelect[nPrevSelectY].size())
			{ // 列が減少した場合

				// 列インデックスを小さい方の最大値で補正
				m_curSelect.x /= m_vecSelect[m_oldSelect.y].size() / XSELECT_MAX;
			}
			else if (m_vecSelect[m_curSelect.y].size() > m_vecSelect[nPrevSelectY].size())
			{ // 列が増加した場合

				// 列インデックスを大きい方の最大値で補正
				m_curSelect.x *= m_vecSelect[m_curSelect.y].size() / XSELECT_MAX;
			}

		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}
}

//============================================================
//	選択の更新処理
//============================================================
void CStartStateCreateName::UpdateSelect()
{
	// 前回の選択肢を保存
	m_oldSelect = m_curSelect;

	// 選択の操作
	ControlSelect();

	// 前回の選択要素の色を白色に設定
	assert(m_vecSelect[m_oldSelect.y][m_oldSelect.x] != nullptr);
	m_vecSelect[m_oldSelect.y][m_oldSelect.x]->SetColor(select::COL_DEFAULT);

	// 現在の選択要素の色を黄色に設定
	assert(m_vecSelect[m_curSelect.y][m_curSelect.x] != nullptr);
	m_vecSelect[m_curSelect.y][m_curSelect.x]->SetColor(select::COL_CHOICE);
}

//============================================================
//	決定の更新処理
//============================================================
void CStartStateCreateName::UpdateDecide()
{
	if (input::Decide())
	{
		// 選択肢に応じて操作を変更
		std::wstring wsName = m_pName->GetWideStr();	// 名前の文字列
		switch (m_curSelect.y)
		{ // 現在の行選択肢ごとの処理
		default:	// 文字選択

			if (m_pName->GetNumChar() < MAX_STR_NAME)
			{ // 文字数が最大ではない場合

				// 追加する文字列を取得
				std::wstring wsAddChar = m_vecSelect[m_curSelect.y][m_curSelect.x]->GetWideStr();

				// 最後尾に文字を追加
				wsName.push_back(wsAddChar.front());	// 文字列として管理してるので先頭文字を取得

				// 文字列を再設定
				m_pName->SetString(wsName);

				// 設定中の名前を保存
				m_pContext->SetName(useful::WideToMultiByte(wsName));
			}
			break;

		case YSELECT_CHAR_CHANGE:	// 文字変更

			if ((ETypeChar)m_curSelect.x != m_typeChar)
			{ // 変更先が別の文字形式な場合

				// 選択中の文字に変更
				ChangeChar((ETypeChar)m_curSelect.x);
			}
			break;

		case YSELECT_CHAR_DECIDE:	// 文字決定

			switch (m_curSelect.x)
			{ // 現在の列選択肢ごとの処理
			case XSELECT_LEFT:		// 止める

				// チュートリアル状態にする
				m_pContext->ChangeState(new CStartStateTutorial);
				break;

			case XSELECT_CENTER:	// 削除

				if (!wsName.empty())
				{ // 文字がまだある場合

					// 最後尾を一文字削除
					wsName.erase(wsName.end() - 1);

					// 文字列を再設定
					m_pName->SetString(wsName);

					// 設定中の名前を保存
					m_pContext->SetName(useful::WideToMultiByte(wsName));
				}
				break;

			case XSELECT_RIGHT:		// 確定

				if (!wsName.empty())
				{ // 文字が設定されている場合

					// 名前決定状態にする
					m_pContext->ChangeState(new CStartStateDecideName);
				}
				break;

			default:
				assert(false);
				break;
			}
			break;
		}
	}
}

//============================================================
//	文字の変更処理
//============================================================
HRESULT CStartStateCreateName::ChangeChar(const ETypeChar typeChar)
{
	// 文字種類が不明な値の場合抜ける
	if (typeChar <= NONE_IDX || typeChar >= TYPECHAR_MAX) { assert(false); return E_FAIL; }

	// 選択文字ポリゴンの終了
	for (int i = YSELECT_MAX; i < (int)m_vecSelect.size(); i++)
	{ // 固定選択肢を除く行の総数分繰り返す

		for (int j = 0; j < (int)m_vecSelect[i].size(); j++)
		{ // 列の総数分繰り返す

			// 選択文字の終了
			SAFE_UNINIT(m_vecSelect[i][j]);
		}
	}

	// 固定選択肢を除いた選択文字配列をクリア
	m_vecSelect.erase(m_vecSelect.begin() + YSELECT_MAX, m_vecSelect.end());

	// 配置の読込
	if (FAILED(LoadArray(typeChar)))
	{ // 読込に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 設定した文字種類を保存
	m_typeChar = typeChar;

	return S_OK;
}

//============================================================
//	配置の読込処理
//============================================================
HRESULT CStartStateCreateName::LoadArray(const ETypeChar typeChar)
{
	VECTOR3 posOffset	= VEC3_ZERO;	// 文字生成位置
	VECTOR3 posStart	= VEC3_ZERO;	// 文字開始位置
	VECTOR2 charOffset	= VEC2_ZERO;	// 文字のオフセット
	float fSpaceOffset	= 0.0f;			// 空白のオフセット

	// ファイルを開く
	std::ifstream file(PASS_CHAR[typeChar]);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "文字セットアップの読み込みに失敗！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ファイルを読込
	std::string str;	// 読込文字列
	while (std::getline(file, str))
	{ // ファイルの終端ではない場合ループ

		// カンマ区切りごとにデータを読込
		std::istringstream iss(str);	// 文字列ストリーム
		while (std::getline(iss, str, ','))
		{
			if (str == "START_POS")
			{
				// 開始位置を読込
				iss >> posStart.x >> posStart.y >> posStart.z;

				// 開始位置を生成位置に設定
				posOffset = posStart;
			}
			else if (str == "CHAR_OFFSET")
			{
				// 文字のオフセットを読込
				iss >> charOffset.x >> charOffset.y;
			}
			else if (str == "SAPCE_OFFSET")
			{
				// 空白のオフセットを読込
				iss >> fSpaceOffset;
			}
			else if (str == "SETCHAR")
			{
				while (std::getline(file, str))
				{ // ファイルの終端ではない場合ループ

					// 終端の場合文字生成を抜ける
					if (str == "END_SETCHAR") { break; }

					// 横一行分の配列を拡張
					m_vecSelect.emplace_back();

					// カンマ区切りごとにデータを読込
					std::istringstream issChar(str);	// 文字列ストリーム
					while (std::getline(issChar, str, ','))
					{
						if (str == "") { continue; }	// 空白は無視する
						else if (str == "/s")
						{ // 空白を読み込んだ場合

							// 横位置に空白分のオフセットを与える
							posOffset.x += fSpaceOffset;
							continue;	// 配列インデックスは進めない
						}
						else if (str == "/e")
						{ // 空文字を読み込んだ場合

							// 現在の行列の最後尾にnullptrを追加
							m_vecSelect.back().push_back(nullptr);

							// 横位置に文字分のオフセットを与える
							posOffset.x += charOffset.x;
						}
						else
						{ // 特殊操作ではない場合

							// 読み込んだ文字の生成
							CString2D* pChar = CShakeString2D::Create
							( // 引数
								select::FONT,					// フォントパス
								select::ITALIC,					// イタリック
								useful::MultiByteToWide(str),	// 指定文字列
								posOffset,						// 原点位置
								select::NEXT_TIME,				// 文字振動の待機時間
								select::MOVE,					// 振動移動量
								select::HEIGHT,					// 文字縦幅
								select::ALIGN_X,				// 横配置
								select::ROT,					// 原点向き
								select::COL_DEFAULT				// 色
							);

							// 優先順位を設定
							pChar->SetPriority(PRIORITY);

							// 現在の行列の最後尾に生成した文字を追加
							m_vecSelect.back().push_back(pChar);

							// 横位置に文字分のオフセットを与える
							posOffset.x += charOffset.x;
						}
					}

					// 横位置を先頭に戻す
					posOffset.x = posStart.x;

					// 縦位置に文字分のオフセットを与える
					posOffset.y += charOffset.y;
				}
			}
		}
	}

	// ファイルを閉じる
	file.close();

	return S_OK;
}
