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
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *PASS_CHAR[] =	// 文字配置情報の相対パス
	{
		"data\\CSV\\char_hiragana.csv",	// ひらがな配置情報
		"data\\CSV\\char_katakana.csv",	// カタカナ配置情報
		"data\\CSV\\char_alphabet.csv",	// アルファベット配置情報
	};

	const char *PASS = "data\\TEXT\\start.txt";	// テキストパス
	const int PRIORITY = 6;	// 優先順位

	namespace title
	{	
		const char	*FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 42.0f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// 横配置
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 80.0f, 0.0f);	// 位置
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL = XCOL_WHITE;	// 色
	}
	
	namespace select
	{	
		const D3DXVECTOR3 POS[CStartStateCreateName::YSELECT_MAX][CStartStateCreateName::XSELECT_MAX] =	// 位置配列
		{
			{ D3DXVECTOR3(180.0f, 530.0f, 0.0f), D3DXVECTOR3(440.0f, 530.0f, 0.0f), D3DXVECTOR3(750.0f, 530.0f, 0.0f) },
			{ D3DXVECTOR3(220.0f, 630.0f, 0.0f), D3DXVECTOR3(460.0f, 630.0f, 0.0f), D3DXVECTOR3(700.0f, 630.0f, 0.0f) },
		};

		const CStartStateCreateName::ETypeChar INIT_TYPE = CStartStateCreateName::TYPECHAR_HIRAGANA;	// 初期文字セット
		const POSGRID2 INIT_SELECT = POSGRID2(0, 2);	// 初期選択位置

		const char	*FONT	= "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
		const bool	ITALIC	= false;	// イタリック
		const float	HEIGHT	= 42.0f;	// 文字縦幅

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;	// 横配置
		const D3DXVECTOR3	ROT			= VEC3_ZERO;	// 向き
		const D3DXCOLOR		COL_DEFAULT	= XCOL_WHITE;	// 通常色
		const D3DXCOLOR		COL_CHOICE	= XCOL_YELLOW;	// 選択色
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
HRESULT CStartStateCreateName::Init(void)
{
	// メンバ変数を初期化
	m_pTitle	= nullptr;				// タイトル
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

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pTitle->SetPriority(PRIORITY);

	// 文字列を割当
	loadtext::BindString(m_pTitle, loadtext::LoadText(PASS, CStartManager::TEXT_NAMING));

	for (int i = 0; i < YSELECT_MAX; i++)
	{
		// 横一行分の配列を拡張
		m_vecSelect.emplace_back();

		for (int j = 0; j < XSELECT_MAX; j++)
		{
			// 選択肢の生成
			CString2D *pSelect = CString2D::Create
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

				// 失敗を返す
				assert(false);
				return E_FAIL;
			}

			// 優先順位を設定
			pSelect->SetPriority(PRIORITY);

			// 文字列を割当
			loadtext::BindString(pSelect, loadtext::LoadText(PASS, CStartManager::TEXT_HIRAGANA + (i * XSELECT_MAX) + j));

			// 現在の行列の最後尾に生成した文字を追加
			m_vecSelect.back().push_back(pSelect);
		}
	}

	// 配置の読込
	if (FAILED(ChangeChar(select::INIT_TYPE)))
	{ // 読込に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CStartStateCreateName::Uninit(void)
{
	// タイトルの終了
	SAFE_UNINIT(m_pTitle);

	for (int i = 0; i < (int)m_vecSelect.size(); i++)
	{ // 縦の文字数分繰り返す

		for (int j = 0; j < (int)m_vecSelect[i].size(); j++)
		{ // 横の文字数分繰り返す

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
void CStartStateCreateName::ControlSelect(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
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
void CStartStateCreateName::UpdateSelect(void)
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
void CStartStateCreateName::UpdateDecide(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_Z) || pKey->IsTrigger(DIK_RETURN))
	{
		// 選択肢に応じて操作を変更
		switch (m_curSelect.y)
		{ // 現在の行選択肢ごとの処理
		case YSELECT_CHAR_CHANGE:	// 文字変更

			// 選択中の文字に変更
			ChangeChar((ETypeChar)m_curSelect.x);
			break;

		case YSELECT_CHAR_DECIDE:	// 文字決定

			switch (m_curSelect.x)
			{ // 現在の列選択肢ごとの処理
			case XSELECT_LEFT:		// 止める

				// チュートリアル状態にする
				m_pContext->ChangeState(new CStartStateTutorial);
				break;

			case XSELECT_CENTER:	// 削除

				// 最後尾を一文字削除
				//m_pNaming->DeleteBackName();	// TODO
				break;

			case XSELECT_RIGHT:		// 確定

				// 名前決定状態にする
				//m_pContext->ChangeState(new CStartStateDecideName(m_pNaming->GetName()));	// TODO
				break;

			default:
				assert(false);
				break;
			}
			break;

		default:
			assert(false);
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

	// TODO
	for (int i = YSELECT_MAX; i < (int)m_vecSelect.size(); i++)
	{ // 縦の文字数分繰り返す

		for (int j = 0; j < (int)m_vecSelect[i].size(); j++)
		{ // 横の文字数分繰り返す

			// 選択文字の終了
			SAFE_UNINIT(m_vecSelect[i][j]);
		}
	}

	// 選択文字配列をクリア
	m_vecSelect.erase(m_vecSelect.begin() + YSELECT_MAX, m_vecSelect.end());

	// 配置の読込
	if (FAILED(LoadArray(typeChar)))
	{ // 読込に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	配置の読込処理
//============================================================
HRESULT CStartStateCreateName::LoadArray(const ETypeChar typeChar)
{
	D3DXVECTOR3 posOffset	= VEC3_ZERO;	// 文字生成位置
	D3DXVECTOR3 posStart	= VEC3_ZERO;	// 文字開始位置
	D3DXVECTOR2 charOffset	= VEC2_ZERO;	// 文字のオフセット
	float fSpaceOffset		= 0.0f;			// 空白のオフセット

	// ファイルを開く
	std::ifstream file(PASS_CHAR[typeChar]);	// ファイルストリーム
	if (file.fail())
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(nullptr, "文字セットアップの読み込みに失敗！", "警告！", MB_ICONWARNING);

		// 失敗を返す
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
							CString2D *pChar = CString2D::Create
							( // 引数
								select::FONT,					// フォントパス
								select::ITALIC,					// イタリック
								useful::MultiByteToWide(&str),	// 指定文字列
								posOffset,						// 原点位置
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

	// 成功を返す
	return S_OK;
}
