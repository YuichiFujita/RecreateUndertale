//============================================================
//
//	コマンドヘッダー [command.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _COMMAND_H_
#define _COMMAND_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "anim2D.h"

//************************************************************
//	クラス定義
//************************************************************
// コマンドクラス
class CCommand : public CAnim2D
{
public:
	// 種類列挙
	enum EType
	{
		TYPE_FIGHT = 0,	// たたかう
		TYPE_ACT,		// こうどう
		TYPE_ITEM,		// アイテム
		TYPE_MERCY,		// みのがす
		TYPE_MAX		// この列挙型の総数
	};

	// 状態列挙
	enum EState
	{
		STATE_OFF = 0,	// 選択
		STATE_ON,		// 非選択
		STATE_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CCommand();

	// デストラクタ
	~CCommand() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CCommand* Create	// 生成
	( // 引数
		const EType type = TYPE_FIGHT,	// コマンド種類
		const VECTOR3& rPos = VEC3_ZERO	// 位置
	);

	// メイン関数
	void SetType(const EType type);				// 種類設定
	void SetState(const EState state);			// 状態設定
	EType GetType() const	{ return m_type; }	// 種類取得
	EState GetState() const	{ return m_state; }	// 状態取得

private:
	// メンバ変数
	EType  m_type;	// 種類
	EState m_state;	// 状態
};

#endif	// _COMMAND_H_
