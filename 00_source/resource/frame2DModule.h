//============================================================
//
//	フレーム2D機能ヘッダー [frame2DModule.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_MODULE_H_
#define _FRAME2D_MODULE_H_

//************************************************************
//	前方宣言
//************************************************************
class CFrame2D;				// フレーム2Dクラス
class CFrame2DModuleText;	// テキスト表示機能クラス

//************************************************************
//	クラス定義
//************************************************************
// フレーム2D機能クラス
class CFrame2DModule
{
public:
	// コンストラクタ
	CFrame2DModule();

	// デストラクタ
	virtual ~CFrame2DModule();

	// 純粋仮想関数
	virtual HRESULT Init()	= 0;	// 初期化
	virtual void Uninit()	= 0;	// 終了
	virtual void Update(const float fDeltaTime) = 0;	// 更新

	// 仮想関数
	inline virtual void SetPriority(const int)			{}	// 優先順位設定
	inline virtual void SetVec3Position(const VECTOR3&)	{}	// 位置設定
	inline virtual void SetVec3Rotation(const VECTOR3&)	{}	// 向き設定
	inline virtual void SetVec3Size(const VECTOR3&)		{}	// 大きさ設定
	inline virtual CFrame2DModuleText* GetModuleText()	{ return nullptr; }	// テキスト表示機能取得

	// メンバ関数
	inline void SetContext(CFrame2D* pContext) { m_pContext = pContext; }	// コンテキスト設定

protected:
	// メンバ変数
	CFrame2D* m_pContext;	// コンテキスト
};

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2DModuleText.h"

#endif	// _FRAME2D_MODULE_H_
