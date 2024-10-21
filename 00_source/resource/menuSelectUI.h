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
#include "object2D.h"
#include "frame2D.h"

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス
class CSelectUI;	// セレクトUIクラス

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
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CMenuSelectUI* Create();	// 生成

	// メンバ関数
	inline bool IsChoiceSelect() const { return (m_pSelectMenu != nullptr); }	// 選択中状況取得

private:
	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ関数
	void UpdateSelect();		// 選択更新
	void UpdateDecide();		// 決定更新
	void UninitSelectMenu();	// 選択メニュー終了
	HRESULT ChangeSelectMenu(const CMenuSelectUI::ESelect select);	// 選択メニュー変更

	// メンバ変数
	CString2D* m_apSelect[SELECT_MAX];	// 選択肢情報
	CFrame2D* m_pFrame;			// フレーム情報
	CObject2D* m_pSoul;			// ソウルカーソル情報
	CSelectUI* m_pSelectMenu;	// 選択メニュー情報
	int m_nCurSelect;			// 現在の選択肢
};

// セレクトUIクラス
class CSelectUI : public CObject
{
public:
	// エイリアス定義
	using AFuncUninit = const std::function<void()>;	// 選択メニュー終了関数のポインタ型

	// コンストラクタ
	CSelectUI(AFuncUninit funcUninit, CObject2D* pSoul);

	// デストラクタ
	~CSelectUI() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画
	void SetEnableDraw(const bool bDraw) override;	// 描画状況設定

	// 静的メンバ関数
	static CSelectUI* Create	// 生成
	( // 引数
		AFuncUninit funcUninit,	// 選択メニュー終了関数
		CObject2D* pSoul,		// ソウルカーソル情報
		const CMenuSelectUI::ESelect select	// 選択肢
	);

	// メンバ関数
	inline void SetFramePosition(const VECTOR3& rPos)	{ m_pFrame->SetVec3Position(rPos); }	// フレーム位置設定
	inline void SetFrameRotation(const VECTOR3& rRot)	{ m_pFrame->SetVec3Rotation(rRot); }	// フレーム向き設定
	inline void SetFrameSize(const VECTOR3& rSize)		{ m_pFrame->SetVec3Size(rSize); }		// フレーム大きさ設定
	inline void SetSoulPosition(const VECTOR3& rPos)	{ m_pSoul->SetVec3Position(rPos); }		// ソウルカーソル位置設定
	inline void SetSoulCursorDraw(const bool bDraw)		{ m_pSoul->SetEnableDraw(bDraw); }		// ソウルカーソル描画状況設定
	inline VECTOR3 GetFramePosition() const	{ return m_pFrame->GetVec3Position(); }	// フレーム位置取得
	inline VECTOR3 GetFrameRotation() const	{ return m_pFrame->GetVec3Rotation(); }	// フレーム向き取得
	inline VECTOR3 GetFrameSize() const		{ return m_pFrame->GetVec3Size(); }		// フレーム大きさ取得
	inline VECTOR3 GetSoulPosition() const	{ return m_pSoul->GetVec3Position(); }	// ソウルカーソル位置取得
	inline bool IsSoulCursorDraw() const	{ return m_pSoul->IsDraw(); }			// ソウルカーソル描画状況取得

private:
	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ変数
	AFuncUninit m_funcUninitMenu;	// 選択メニュー終了関数ポインタ
	CObject2D* m_pSoul;	// ソウルカーソル情報
	CFrame2D* m_pFrame;	// フレーム情報
};

#endif	// _MENU_SELECT_UI_H_
