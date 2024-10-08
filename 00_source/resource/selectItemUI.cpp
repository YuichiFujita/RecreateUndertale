//============================================================
//
//	アイテムメニュー処理 [selectItemUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "selectItemUI.h"
#include "manager.h"
#include "string2D.h"
#include "text2D.h"
#include "frameText2D.h"
#include "item.h"
#include "loadtext.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char	*FONT	 = "data\\FONT\\JFドット東雲ゴシック14.ttf";	// フォントパス
	const char	*PASS	 = "data\\TEXT\\selectItem.txt";				// テキストパス
	const bool	ITALIC	 = false;	// イタリック
	const float	HEIGHT	 = 42.0f;	// 文字縦幅
	const int	PRIORITY = 6;		// アイテムメニューの優先順位
	const D3DXVECTOR3 CURSOR_OFFSET = D3DXVECTOR3(22.0f, 0.0f, 0.0f);	// カーソルオフセット

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(545.0f, 347.5f, 0.0f);	// フレーム位置
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// フレーム向き
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(500.0f, 520.0f, 0.0f);	// フレーム大きさ
	}

	namespace select
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;	// 横配置
		const D3DXVECTOR3 POS	= D3DXVECTOR3(380.0f, 555.0f, 0.0f);	// 位置
		const D3DXVECTOR3 SPACE	= D3DXVECTOR3(160.0f, 0.0f, 0.0f);		// 空白
		const D3DXVECTOR3 ROT	= VEC3_ZERO;	// 向き
		const D3DXCOLOR COL		= XCOL_WHITE;	// 通常色
	}

	namespace item
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// 横配置
		const D3DXVECTOR3 POS	= D3DXVECTOR3(360.0f, 145.0f, 0.0f);	// 位置
		const D3DXVECTOR3 SPACE	= D3DXVECTOR3(0.0f, 49.0f, 0.0f);		// 空白
		const D3DXVECTOR3 ROT	= VEC3_ZERO;	// 向き
		const D3DXCOLOR COL		= XCOL_WHITE;	// 通常色
	}
}

//************************************************************
//	子クラス [CSelectItemUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSelectItemUI::CSelectItemUI(AFuncUninit funcUninit, CObject2D *pSoul) : CSelectUI(funcUninit, pSoul),
	m_pItemMenu		 (nullptr),		// アイテムメニュー情報
	m_state			 (STATE_ITEM),	// 状態
	m_nCurSelectItem (0),			// 現在の選択アイテム
	m_nCurSelect	 (0)			// 現在の選択肢
{
	// メンバ変数をクリア
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択情報
	m_vecItemName.clear();	// アイテム情報
}

//============================================================
//	デストラクタ
//============================================================
CSelectItemUI::~CSelectItemUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSelectItemUI::Init(void)
{
	// メンバ変数を初期化
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択情報
	m_vecItemName.clear();			// アイテム情報
	m_pItemMenu		 = nullptr;		// アイテムメニュー情報
	m_state			 = STATE_ITEM;	// 状態
	m_nCurSelectItem = 0;			// 現在の選択アイテム
	m_nCurSelect	 = 0;			// 現在の選択肢

	//--------------------------------------------------------
	//	親クラスの初期化 / 設定
	//--------------------------------------------------------
	// セレクトUIの初期化
	if (FAILED(CSelectUI::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// フレームの位置を設定
	SetFramePosition(frame::POS);

	// フレームの向きを設定
	SetFrameRotation(frame::ROT);

	// フレームの大きさを設定
	SetFrameSizing(frame::SIZE);

	//--------------------------------------------------------
	//	選択の初期化 / 設定
	//--------------------------------------------------------
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 文字位置オフセットを計算
		D3DXVECTOR3 offset = select::SPACE * (float)i;

		// 選択の生成
		m_apSelect[i] = CString2D::Create
		( // 引数
			FONT,					// フォントパス
			ITALIC,					// イタリック
			L"",					// 指定文字列
			select::POS + offset,	// 原点位置
			HEIGHT,					// 文字縦幅
			select::ALIGN_X,		// 横配置
			select::ROT,			// 原点向き
			select::COL				// 色
		);
		if (m_apSelect[i] == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_apSelect[i]->SetPriority(PRIORITY);

		// 文字列を割当
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(PASS, TEXT_USE + i));
	}

	//--------------------------------------------------------
	//	アイテムの初期化 / 設定
	//--------------------------------------------------------
	CItem* pItem = GET_MANAGER->GetItem();	// アイテム情報
	for (int i = 0; i < 8; i++)	// TODO：アイテム数に応じた回数指定
	{ // 所持アイテム数分繰り返す

		// 空の要素を最後尾に追加
		m_vecItemName.emplace_back();

		// TODO：ここでアイテムデータのインデックスを保存する
#if 1
		// アイテムインデックスを保存
		m_vecItemName[i].nItemID = rand() % 2;
#endif

		// 文字位置オフセットを計算
		D3DXVECTOR3 offset = item::SPACE * (float)i;

		// アイテム名の生成
		m_vecItemName[i].m_pName = CString2D::Create
		( // 引数
			FONT,				// フォントパス
			ITALIC,				// イタリック
			L"",				// 指定文字列
			item::POS + offset,	// 原点位置
			HEIGHT,				// 文字縦幅
			item::ALIGN_X,		// 横配置
			item::ROT,			// 原点向き
			item::COL			// 色
		);
		if (m_vecItemName[i].m_pName == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_vecItemName[i].m_pName->SetPriority(PRIORITY);

		// アイテム名設定
		std::string sName = pItem->GetInfo(m_vecItemName[i].nItemID).GetName();	// アイテム名
		std::wstring wsName = useful::MultiByteToWide(sName);	// ワイド変換アイテム名
		m_vecItemName[i].m_pName->SetString(wsName);	// 文字列を設定
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSelectItemUI::Uninit(void)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // 選択肢の総数分繰り返す

		// 選択の終了
		SAFE_UNINIT(m_apSelect[i]);
	}

	for (auto& rVec : m_vecItemName)
	{ // 要素数分繰り返す

		// アイテム名の終了
		SAFE_UNINIT(rVec.m_pName);
	}

	// アイテム情報のクリア
	m_vecItemName.clear();

	// セレクトUIの終了
	CSelectUI::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSelectItemUI::Update(const float fDeltaTime)
{
	switch (m_state)
	{ // 状態ごとの処理
	case STATE_ITEM:

		// アイテム選択の更新
		UpdateSelectItem();

		// アイテム決定の更新
		UpdateDecideItem();

		// セレクトUIの更新
		CSelectUI::Update(fDeltaTime);
		break;

	case STATE_SELECT:

		// 選択の更新
		UpdateSelect();

		// 決定の更新
		UpdateDecide();
		break;

	case STATE_TEXT:

		break;

	default:
		assert(false);
		break;
	}
}

//============================================================
//	描画処理
//============================================================
void CSelectItemUI::Draw(CShader *pShader)
{
	// セレクトUIの描画
	CSelectUI::Draw(pShader);
}

//============================================================
//	アイテム選択の更新処理
//============================================================
void CSelectItemUI::UpdateSelectItem(void)
{
	// 選択肢操作
	CInputKeyboard *pKey = GET_INPUTKEY;		// キーボード情報
	int nMaxItem = (int)m_vecItemName.size();	// アイテムの総数
	if (pKey->IsTrigger(DIK_DOWN))
	{
		// 上に選択をずらす
		m_nCurSelectItem = (m_nCurSelectItem + 1) % nMaxItem;
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		// 下に選択をずらす
		m_nCurSelectItem = (m_nCurSelectItem + (nMaxItem - 1)) % nMaxItem;
	}

	// ソウルカーソルの位置を移動
	SetSoulPosition(m_vecItemName[m_nCurSelectItem].m_pName->GetVec3Position() - CURSOR_OFFSET);
}

//============================================================
//	アイテム決定の更新処理
//============================================================
void CSelectItemUI::UpdateDecideItem(void)
{
	if (input::Decide())
	{
		// 選択状態にする
		m_state = STATE_SELECT;
	}
}

//============================================================
//	選択の更新処理
//============================================================
void CSelectItemUI::UpdateSelect(void)
{
	// 選択肢操作
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// 右に選択をずらす
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// 左に選択をずらす
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}

	// ソウルカーソルの位置を移動
	const D3DXVECTOR3 offset = D3DXVECTOR3(m_apSelect[m_nCurSelect]->GetStrWidth() * 0.5f, 0.0f, 0.0f) + CURSOR_OFFSET;	// カーソルオフセット
	SetSoulPosition(m_apSelect[m_nCurSelect]->GetVec3Position() - offset);
}

//============================================================
//	決定の更新処理
//============================================================
void CSelectItemUI::UpdateDecide(void)
{
	if (input::Decide())
	{
		int nItemIdx = m_vecItemName[m_nCurSelectItem].nItemID;	// 選択中アイテムインデックス
		CItem* pItem = GET_MANAGER->GetItem();	// アイテム情報

		auto func = [pItem, nItemIdx]() { pItem->GetInfo(nItemIdx).Use(); };	// TODO

		// アイテムメニューの生成
		m_pItemMenu = CItemUI::Create
		( // 引数
			GetFuncUninit(),
			func,
			pItem->GetInfo(nItemIdx).GetUse()
		);

		// テキスト表示状態にする
		m_state = STATE_TEXT;
	}

	if (input::Cancel())
	{
		// 選択肢を初期化
		m_nCurSelect = 0;

		// アイテム選択状態にする
		m_state = STATE_ITEM;
	}
}

//************************************************************
//	子クラス [CItemUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CItemUI::CItemUI(CSelectUI::AFuncUninit funcUninit, AFuncUse funcUse, const ATextBox& rText) : CObject(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY),
	m_funcUninitMenu	(funcUninit),	// 選択メニュー終了関数ポインタ
	m_funcUse			(funcUse),		// 
	m_text				(rText),		// 表示テキスト
	m_pTextBox			(nullptr),		// テキストボックス情報
	m_nCurTextIdx		(0)				// 現在のテキストインデックス
{

}

//============================================================
//	デストラクタ
//============================================================
CItemUI::~CItemUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CItemUI::Init(void)
{
	// メンバ変数を初期化
	m_pTextBox = nullptr;	// テキストボックス情報
	m_nCurTextIdx = 0;		// 現在のテキストインデックス

	// テキストボックスの生成
	m_pTextBox = CFrameText2D::Create	// TODO：引数要素の作成
	( // 引数
		SCREEN_CENT,
		VEC3_ZERO,
		D3DXVECTOR3(1000.0f, 1000.0f, 0.0f)
	);
	if (m_pTextBox == nullptr)
	{ // 生成に失敗した場合

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
void CItemUI::Uninit(void)
{
	// テキストボックスの終了
	SAFE_UNINIT(m_pTextBox);

	// オブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CItemUI::Update(const float fDeltaTime)
{
	// 入力検知されていない場合抜ける
	if (!input::Decide()) { return; }

	if (m_pTextBox->IsTextScroll())
	{ // 文字送り中の場合

		// 文字を全表示させる
		m_pTextBox->SetTextEnableDraw(true);
		return;
	}

	if (m_nCurTextIdx >= (int)m_text.size())
	{ // テキストが終了した場合

		// 選択中アイテムの使用
		m_funcUse();

		// 選択メニューの終了
		m_funcUninitMenu();

		// アイテムUIの終了
		Uninit();
		return;
	}

	// 現在のテキスト進行度に合わせたテキストに変更
	m_pTextBox->ChangeText(m_text[m_nCurTextIdx]);

	// テキスト進行度を進める
	m_nCurTextIdx++;

#if 0
	if (m_pTextBox->IsTextScroll())
	{
		m_pTextBox->SetTextEnableDraw(true);
	}
	else
	{
		int nItemIdx = m_vecItemName[m_nCurSelectItem].nItemID;	// 選択中アイテムインデックス
		CItem* pItem = GET_MANAGER->GetItem();	// アイテム情報

		// TODO：選択ごとに表示を切り替え
		switch (m_nCurSelect)
		{ // 選択ごとの処理
		case SELECT_USE:
		{
			const ATextBox& rText = pItem->GetInfo(nItemIdx).GetUse();	// テキストボックス保存情報

			if (m_nCurTextIdx >= (int)rText.size())
			{ // テキストが終了した場合

				// 選択中アイテムの使用
				pItem->GetInfo(nItemIdx).Use();

				// 選択肢を初期化
				m_nCurSelect = 0;

				// アイテム選択状態にする
				m_state = STATE_ITEM;

				// テキストボックスの終了
				SAFE_UNINIT(m_pTextBox);

				break;
			}

			// 現在のテキスト進行度に合わせたテキストに変更
			m_pTextBox->ChangeText(rText[m_nCurTextIdx]);

			// テキスト進行度を進める
			m_nCurTextIdx++;
			break;
		}
		case SELECT_INFO:
		{
			const ATextBox& rText = pItem->GetInfo(nItemIdx).GetInfo();	// テキストボックス保存情報

			if (m_nCurTextIdx >= (int)rText.size())
			{ // テキストが終了した場合

				// 選択中アイテムの情報
				pItem->GetInfo(nItemIdx).Info();

				// 選択肢を初期化
				m_nCurSelect = 0;

				// アイテム選択状態にする
				m_state = STATE_ITEM;

				// テキストボックスの終了
				SAFE_UNINIT(m_pTextBox);

				break;
			}

			// 現在のテキスト進行度に合わせたテキストに変更
			m_pTextBox->ChangeText(rText[m_nCurTextIdx]);

			// テキスト進行度を進める
			m_nCurTextIdx++;
			break;
		}
		case SELECT_DROP:
		{
			// TODO：捨てるテキストはほんとにこれでいいの？
#if 0
			const ATextBox& rText = pItem->GetInfo(nItemIdx).GetDrop();	// テキストボックス保存情報

			if (m_nCurTextIdx >= (int)rText.size())
			{ // テキストが終了した場合

				// 選択中アイテムの破棄
				pItem->GetInfo(nItemIdx).Drop();

				// 選択肢を初期化
				m_nCurSelect = 0;

				// アイテム選択状態にする
				m_state = STATE_ITEM;

				// テキストボックスの終了
				SAFE_UNINIT(m_pTextBox);

				break;
			}

			// 現在のテキスト進行度に合わせたテキストに変更
			m_pTextBox->ChangeText(rText[m_nCurTextIdx]);

			// テキスト進行度を進める
			m_nCurTextIdx++;
#endif
			break;
		}
		default:
			assert(false);
			break;
		}
	}
#endif
}

//============================================================
//	描画処理
//============================================================
void CItemUI::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	生成処理
//============================================================
CItemUI *CItemUI::Create
(
	CSelectUI::AFuncUninit funcUninit,	// 選択メニュー終了関数
	AFuncUse funcUse,		// 
	const ATextBox& rText	// 表示テキスト
)
{
	// アイテムUIの生成
	CItemUI *pItemUI = new CItemUI(funcUninit, funcUse, rText);
	if (pItemUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// アイテムの初期化
		if (FAILED(pItemUI->Init()))
		{ // 初期化に失敗した場合

			// アイテムの破棄
			SAFE_DELETE(pItemUI);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pItemUI;
	}
}
