//============================================================
//
//	フレーム2Dヘッダー [frame2D.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME2D_H_
#define _FRAME2D_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"

//************************************************************
//	前方宣言
//************************************************************
class CObject2D;	// オブジェクト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// フレーム2Dクラス
class CFrame2D : public CObject
{
public:
	// ポリゴン列挙
	enum EPolygon
	{
		POLYGON_INSIDE = 0,	// 内側
		POLYGON_FRAME,		// 外枠
		POLYGON_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CFrame2D();

	// デストラクタ
	~CFrame2D() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetPriority(const int nPriority) override;		// 優先順位設定
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	void SetVec3Size(const VECTOR3& rSize) override;	// 大きさ設定
	VECTOR3 GetVec3Position(void) const override	{ return m_pos; }	// 位置取得
	VECTOR3 GetVec3Rotation(void) const override	{ return m_rot; }	// 向き取得
	VECTOR3 GetVec3Size(void) const override		{ return m_size; }	// 大きさ取得

	// 静的メンバ関数
	static CFrame2D* Create	// 生成
	( // 引数
		const VECTOR3& rPos,	// 位置
		const VECTOR3& rRot,	// 向き
		const VECTOR3& rSize	// 大きさ
	);

private:
	// オーバーライド関数
	void Release(void) override { CObject::Release(); }	// 破棄

	// メンバ変数
	CObject2D* m_apFrame[POLYGON_MAX];	// フレーム情報
	VECTOR3 m_pos;	// 位置
	VECTOR3 m_rot;	// 向き
	VECTOR3 m_size;	// 大きさ
};

#endif	// _FRAME2D_H_
