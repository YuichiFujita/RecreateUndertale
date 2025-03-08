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
class CFrame2DModule;	// フレーム2D機能クラス
class CObject2D;		// オブジェクト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// フレーム2Dクラス
class CFrame2D : public CObject
{
public:
	// 配置プリセット列挙
	enum EPreset
	{
		PRESET_NONE = -1,	// 指定無し
		PRESET_DOWN,		// 下部配置
		PRESET_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CFrame2D();

	// デストラクタ
	~CFrame2D() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetPriority(const int nPriority) override;		// 優先順位設定
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定
	void SetVec3Rotation(const VECTOR3& rRot) override;	// 向き設定
	void SetVec3Size(const VECTOR3& rSize) override;	// 大きさ設定
	inline VECTOR3 GetVec3Position() const override	{ return m_pos; }	// 位置取得
	inline VECTOR3 GetVec3Rotation() const override	{ return m_rot; }	// 向き取得
	inline VECTOR3 GetVec3Size() const override		{ return m_size; }	// 大きさ取得

	// 静的メンバ関数
	static CFrame2D* Create(const EPreset preset);	// 生成 (配置プリセット)
	static CFrame2D* Create	// 生成 (配置指定)
	( // 引数
		const VECTOR3& rPos,	// 位置
		const VECTOR3& rRot,	// 向き
		const VECTOR3& rSize	// 大きさ
	);

	// メンバ関数
	HRESULT ChangeModule(CFrame2DModule* pModule);	// 機能変更
	void SetPreset(const EPreset preset);			// 配置プリセット設定
	inline void InitModule()				 { m_pModule = nullptr; }	// 機能初期化
	inline CFrame2DModule* GetModule() const { return m_pModule; }		// 機能取得
	inline EPreset GetPreset() const		 { return m_preset; }		// 配置プリセット取得

private:
	// ポリゴン列挙
	enum EPolygon
	{
		POLYGON_INSIDE = 0,	// 内側
		POLYGON_FRAME,		// 外枠
		POLYGON_MAX			// この列挙型の総数
	};

	// オーバーライド関数
	inline void Release() override { CObject::Release(); }	// 破棄

	// メンバ変数
	CObject2D* m_apFrame[POLYGON_MAX];	// フレーム情報
	CFrame2DModule* m_pModule;	// 機能
	VECTOR3 m_pos;		// 位置
	VECTOR3 m_rot;		// 向き
	VECTOR3 m_size;		// 大きさ
	EPreset m_preset;	// 配置プリセット
};

#endif	// _FRAME2D_H_
