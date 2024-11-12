//============================================================
//
//	プレイヤーヘッダー [player.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "objectCharaAnim3D.h"
#include "playerStatus.h"
#include "playerItem.h"

//************************************************************
//	前方宣言
//************************************************************
class CPlayerState;	// プレイヤー状態クラス

//************************************************************
//	クラス定義
//************************************************************
// プレイヤークラス
class CPlayer : public CObjectCharaAnim3D
{
public:
	// 角度列挙
	enum EAngle
	{
		ANGLE_UP = 0,	// 上
		ANGLE_DOWN,		// 下
		ANGLE_LEFT,		// 左
		ANGLE_RIGHT,	// 右
		ANGLE_MAX		// この列挙型の総数
	};

	// モーション列挙
	enum EMotion
	{
		MOTION_IDOL_U = 0,	// 上待機モーション
		MOTION_IDOL_D,		// 下待機モーション
		MOTION_IDOL_L,		// 左待機モーション
		MOTION_IDOL_R,		// 右待機モーション
		MOTION_MOVE_U,		// 上移動モーション
		MOTION_MOVE_D,		// 下移動モーション
		MOTION_MOVE_L,		// 左移動モーション
		MOTION_MOVE_R,		// 右移動モーション
		MOTION_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CPlayer();

	// デストラクタ
	~CPlayer();

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画
	HRESULT ChangeState(CPlayerState* pState);		// 状態変更

	// 静的メンバ関数
	static CPlayer* Create(const VECTOR3& rPos);	// 生成
	static CListManager<CPlayer>* GetList();		// リスト取得

	// メンバ関数
	void TransRoom(const VECTOR3& rPos, const EAngle angle);			// 部屋遷移
	inline void SetAngle(const EAngle angle)	{ m_angle = angle; }	// 向き設定
	inline EAngle GetAngle() const				{ return m_angle; }		// 向き取得
	inline VECTOR3 GetOldPosition() const		{ return m_oldPos; }	// 過去位置取得
	inline SPlayerStatus GetStatus() const		{ return m_status; }	// ステータス情報取得
	inline SPlayerItem GetItem() const			{ return m_item; }		// アイテム情報取得

private:
	// メンバ関数
	void UpdateOldPosition();	// 過去位置の更新
	void UpdateMotion(int nCurMotion, const float fDeltaTime);	// モーション・キャラクター2Dの更新

	// 静的メンバ変数
	static CListManager<CPlayer>* m_pList;	// オブジェクトリスト

	// メンバ変数
	CListManager<CPlayer>::AIterator m_iterator;	// イテレーター
	SPlayerStatus m_status;	// ステータス情報
	SPlayerItem m_item;		// アイテム情報
	CPlayerState* m_pState;	// 状態
	VECTOR3 m_oldPos;		// 過去位置
	EAngle m_angle;			// 向き
};

#endif	// _PLAYER_H_
