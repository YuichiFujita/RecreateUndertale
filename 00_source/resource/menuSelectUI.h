//============================================================
//
//	セレクトメニューヘッダー [menuSelectUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _MENU_SELECT_UI_H_
#define _MENU_SELECT_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"
#include "frame2D.h"

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス
class CObject2D;	// オブジェクト2Dクラス
class CSelect;		// セレクトクラス

//************************************************************
//	クラス定義
//************************************************************
// セレクトメニュークラス
class CMenuSelectUI : public CObject
{
public:
	// 選択列挙
	enum ESelect
	{
		SELECT_ITEM = 0,	// アイテム
		SELECT_STATUS,		// ステータス
		SELECT_PHONE,		// 電話
		SELECT_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CMenuSelectUI();

	// デストラクタ
	~CMenuSelectUI() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CMenuSelectUI *Create(void);	// 生成

private:
	// オーバーライド関数
	void Release(void) override { CObject::Release(); }	// 破棄

	// メンバ関数
	void UpdateSelect(void);		// 選択更新
	void UpdateDecide(void);		// 決定更新
	void UninitSelectMenu(void);	// 選択メニュー終了
	HRESULT ChangeSelectMenu(const CMenuSelectUI::ESelect select);	// 選択メニュー変更

	// メンバ変数
	CString2D *m_apSelect[SELECT_MAX];	// 選択肢情報
	CFrame2D *m_pFrame;		// フレーム情報
	CObject2D *m_pSoul;		// ソウルカーソル情報
	CSelect *m_pSelectMenu;	// 選択メニュー情報
	int m_nCurSelect;		// 現在の選択肢
};

// セレクトクラス
class CSelect : public CObject
{
public:
	// コンストラクタ
	explicit CSelect(const std::function<void(void)> funcUninit);

	// デストラクタ
	~CSelect() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CSelect *Create	// 生成
	( // 引数
		const std::function<void(void)> funcUninit,	// 選択メニュー終了関数
		CObject2D *pSoul,							// ソウルカーソル情報
		const CMenuSelectUI::ESelect select			// 選択肢
	);

	// メンバ関数
	void SetFramePosition(const D3DXVECTOR3& rPos)	{ m_pFrame->SetVec3Position(rPos); }	// フレーム位置設定
	void SetFrameRotation(const D3DXVECTOR3& rRot)	{ m_pFrame->SetVec3Rotation(rRot); }	// フレーム向き設定
	void SetFrameSizing(const D3DXVECTOR3& rSize)	{ m_pFrame->SetVec3Sizing(rSize); }		// フレーム大きさ設定
	D3DXVECTOR3 GetFramePosition(void) const		{ return m_pFrame->GetVec3Position(); }	// フレーム位置取得
	D3DXVECTOR3 GetFrameRotation(void) const		{ return m_pFrame->GetVec3Rotation(); }	// フレーム向き取得
	D3DXVECTOR3 GetFrameSizing(void) const			{ return m_pFrame->GetVec3Sizing(); }	// フレーム大きさ取得

private:
	// オーバーライド関数
	void Release(void) override { CObject::Release(); }	// 破棄

	// メンバ変数
	const std::function<void(void)> m_funcUninitMenu;	// 選択メニュー終了関数ポインタ
	CObject2D *m_pSoul;	// ソウルカーソル情報
	CFrame2D *m_pFrame;	// フレーム情報
};

#endif	// _MENU_SELECT_UI_H_
