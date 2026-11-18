//============================================================
//
//	戦闘時の名前表示ヘッダー [battleNameUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _BATTLE_NAME_UI_H_
#define _BATTLE_NAME_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// 戦闘時の名前表示クラス
class CBattleNameUI : public CObject
{
public:
	// コンストラクタ
	CBattleNameUI();

	// デストラクタ
	~CBattleNameUI() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetPriority(const int nPriority) override;		// 優先順位設定
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	inline VECTOR3 GetVec3Position() const override	{ return m_pos; }	// 位置取得
	inline VECTOR3 GetVec3Rotation() const override	{ return m_rot; }	// 向き取得

	// 静的メンバ関数
	static CBattleNameUI* Create	// 生成 (マルチバイト文字列)
	( // 引数
		const std::string& rName,	// 名前
		const int nLv				// LV
	);
	static CBattleNameUI* Create	// 生成
	( // 引数
		const std::wstring& rName,	// 名前 (ワイド文字列)
		const int nLv				// LV
	);

	// メンバ関数
	HRESULT SetName(const std::string& rName);	// 名前の設定 (マルチバイト文字列)
	HRESULT SetName(const std::wstring& rName);	// 名前の設定 (ワイド文字列)
	void SetLv(const int nLv);					// LVの設定

private:
	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ関数
	void SetPositionRelative();	// 相対位置設定

	// メンバ変数
	CString2D*	m_pName;	// 名前情報
	CString2D*	m_pLv;		// LV情報
	VECTOR3		m_pos;		// 原点位置
	VECTOR3		m_rot;		// 原点向き
};

#endif	// _BATTLE_NAME_UI_H_
