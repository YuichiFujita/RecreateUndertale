//============================================================
//
//	カメラヘッダー [camera.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"

//************************************************************
//	クラス定義
//************************************************************
// カメラクラス
class CCamera
{
public:
	// 状態列挙
	enum EState
	{
		STATE_NONE = 0,	// 固定状態
		STATE_FOLLOW,	// 追従状態
		STATE_CONTROL,	// 操作状態
		STATE_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CCamera();

	// デストラクタ
	~CCamera();

	// カメラ揺れ構造体
	struct SSwing
	{
	public:
		// コンストラクタ
		SSwing() {}
		SSwing(const float ShiftLength, const float SubAngle, const float SubLength) :
			shiftPos	 (VEC3_ZERO),	// 位置ずれ量
			fShiftAngle	 (0.0f),		// 位置をずらす角度
			fShiftLength (ShiftLength),	// 位置をずらす距離
			fSubAngle	 (SubAngle),	// ずらす角度の減算量
			fSubLength	 (SubLength)	// ずらす距離の減算量
		{}

		// デストラクタ
		~SSwing() {}

		// メンバ変数
		VECTOR3	shiftPos;		// 位置ずれ量
		float	fShiftAngle;	// 位置をずらす角度
		float	fShiftLength;	// 位置をずらす距離
		float	fSubAngle;		// ずらす角度の減算量
		float	fSubLength;		// ずらす距離の減算量
	};

	// カメラ構造体
	struct SCamera
	{
		VECTOR3 posV;			// 現在の視点
		VECTOR3 posR;			// 現在の注視点
		VECTOR3 destPosV;		// 目標の視点
		VECTOR3 destPosR;		// 目標の注視点
		VECTOR3 vecU;			// 上方向ベクトル
		VECTOR3 rot;			// 現在の向き
		VECTOR3 destRot;		// 目標の向き
		float fDis;				// 現在の視点と注視点の距離
		float fDestDis;			// 目標の視点と注視点の距離
		SSwing swing;			// カメラ揺れ情報
		D3DVIEWPORT9 viewport;	// ビューポート情報
		MATRIX mtxProj;			// プロジェクションマトリックス
		MATRIX mtxView;			// ビューマトリックス
	};

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(const float fDeltaTime);	// 更新
	void SetCamera(void);		// カメラ設定
	SCamera GetCamera(void);	// カメラ取得
	void InitNone(void);		// 固定カメラ初期化
	void InitFollow(void);		// 追従カメラ初期化
	void ResetSwing(void);		// カメラ揺れ初期化

	void SetState(const EState state, const bool bInit = true);	// カメラ状態設定
	EState GetState(void) const;				// カメラ状態取得
	void SetSwing(const SSwing swing);			// カメラ揺れ設定
	void SetEnableUpdate(const bool bUpdate);	// 更新状況設定
	void SetPositionV(const VECTOR3& rPos);		// 視点設定
	void SetPositionR(const VECTOR3& rPos);		// 注視点設定
	void SetRotation(const VECTOR3& rRot);		// 向き設定
	void SetDistance(const float fDis);			// 距離設定
	VECTOR3 GetPositionV(void) const		{ return m_camera.posV; }		// 現在の視点取得
	VECTOR3 GetDestPositionV(void) const	{ return m_camera.destPosV; }	// 目標の視点取得
	VECTOR3 GetPositionR(void) const		{ return m_camera.posR; }		// 現在の注視点取得
	VECTOR3 GetDestPositionR(void) const	{ return m_camera.destPosR; }	// 目標の注視点取得
	VECTOR3 GetRotation(void) const			{ return m_camera.rot; }		// 現在の向き取得
	VECTOR3 GetDestRotation(void) const		{ return m_camera.destRot; }	// 目標の向き取得
	float GetDistance(void) const			{ return m_camera.fDis; }		// 現在の距離取得
	float GetDestDistance(void) const		{ return m_camera.fDestDis; }	// 目標の距離取得

	// 静的メンバ関数
	static CCamera* Create(void);				// 生成
	static void Release(CCamera*& prCamera);	// 破棄

private:
	// メンバ関数
	void UpdateNone(void);		// 固定カメラ更新
	void UpdateFollow(void);	// 追従カメラ更新
	void UpdateControl(void);	// 操作カメラ更新
	void UpdateMove(void);		// 位置更新
	void UpdateDistance(void);	// 距離更新
	void UpdateRotation(void);	// 向き更新
	void UpdateSwing(void);		// カメラ揺れ更新

	// メンバ変数
	SCamera	m_camera;	// カメラの情報
	EState	m_state;	// 状態
	bool	m_bUpdate;	// 更新状況
};

#endif	// _CAMERA_H_
