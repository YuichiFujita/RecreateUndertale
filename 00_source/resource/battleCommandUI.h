//============================================================
//
//	戦闘時のコマンド表示ヘッダー [battleCommandUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _BATTLE_COMMAND_UI_H_
#define _BATTLE_COMMAND_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"

//************************************************************
//	インクルードファイル
//************************************************************
class CCommand;	// コマンドクラス

//************************************************************
//	クラス定義
//************************************************************
// 戦闘時のコマンド表示クラス
class CBattleCommandUI : public CObject
{
public:
	// 定数
	static constexpr int NUM_COMMAND = 4;	// 表示コマンド数

	// コンストラクタ
	CBattleCommandUI();

	// デストラクタ
	~CBattleCommandUI() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画
	void SetPriority(const int nPriority) override;	// 優先順位設定

	// 静的メンバ関数
	static CBattleCommandUI* Create();	// 生成

private:
	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ変数
	CCommand* m_apCommand[NUM_COMMAND];	// コマンド情報
};

#endif	// _BATTLE_COMMAND_UI_H_
