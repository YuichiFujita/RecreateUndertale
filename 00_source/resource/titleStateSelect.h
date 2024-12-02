//============================================================
//
//	遷移選択状態ヘッダー [titleStateSelect.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _TITLE_STATE_SELECT_H_
#define _TITLE_STATE_SELECT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "titleState.h"

//************************************************************
//	前方宣言
//************************************************************
class CString2D;	// 文字列2Dクラス
class CVersion;		// バージョン表記クラス

//************************************************************
//	クラス定義
//************************************************************
// 遷移選択状態クラス
class CTitleStateSelect : public CTitleState
{
public:
	// コンストラクタ
	CTitleStateSelect();

	// デストラクタ
	~CTitleStateSelect() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

private:
	// メンバ関数
	void UpdateSelect();	// 選択更新
	void UpdateDecide();	// 決定更新

	// メンバ変数
	std::vector<std::vector<CString2D*>> m_vecSelect;	// 選択肢情報
	CString2D* m_pName;		// 名前情報
	CString2D* m_pLove;		// レベル情報
	CString2D* m_pTime;		// 総プレイ時間情報
	CVersion* m_pVersion;	// バージョン表記情報
	POSGRID2 m_curSelect;	// 現在の選択肢
	POSGRID2 m_oldSelect;	// 前回の選択肢
};

#endif	// _TITLE_STATE_SELECT_H_
