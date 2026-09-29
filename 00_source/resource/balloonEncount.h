//============================================================
//
//	エンカウント吹き出しヘッダー [balloonEncount.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _BALLOON_ENCOUNT_H_
#define _BALLOON_ENCOUNT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object3D.h"

//************************************************************
//	クラス定義
//************************************************************
// エンカウント吹き出しクラス
class CBalloonEncount : public CObject3D
{
public:
	// 種類列挙
	enum EType
	{
		TYPE_ENCOUNT = 0,	// 通常エンカウント
		TYPE_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CBalloonEncount();

	// デストラクタ
	~CBalloonEncount();

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CBalloonEncount* Create(const EType type, const VECTOR3& rPos, const VECTOR3& rRot, const VECTOR2& rOffset);	// 生成

	// メンバ関数
	void SetPositionRelative(const VECTOR3& rPos, const VECTOR3& rRot, const VECTOR2& rOffset);	// 相対位置設定
	void SetType(const EType type);					// 種類設定
	inline EType GetType() const { return m_type; }	// 種類取得

private:
	// メンバ変数
	EType m_type;	// 種類
};

#endif	// _BALLOON_ENCOUNT_H_
