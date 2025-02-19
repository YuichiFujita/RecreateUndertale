//============================================================
//
//	オブジェクト表情アニメーション2Dヘッダー [objectFaceAnim2D.h]	// TODO：顔UI
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _OBJECTFACE_ANIM2D_H_
#define _OBJECTFACE_ANIM2D_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "anim2D.h"
#include "faceAnim2D.h"

//************************************************************
//	クラス定義
//************************************************************
// オブジェクト表情アニメーション2Dクラス
class CObjectFaceAnim2D : public CAnim2D
{
public:
	// コンストラクタ
	explicit CObjectFaceAnim2D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_2D, const int nPriority = DEFAULT_PRIO);

	// デストラクタ
	~CObjectFaceAnim2D() override;

	// エイリアス定義
	using AEmotion = CFaceAnim2D::SEmotion;	// 表情管理型
	using AFace = CFaceAnim2D::SFace;		// 顔管理型

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetVec3Position(const VECTOR3& rPos) override;	// 位置設定

	// 静的メンバ関数
	static CObjectFaceAnim2D* Create(const int nIdxFace, const int nTypeEmo, const VECTOR3& rPos, const VECTOR3& rRot = VEC3_ZERO);	// 生成

	// メンバ関数
	void BindFaceData(const int nIdxFace);	// 顔割当
	void SetEmotion(const int nTypeEmo);	// 表情設定
	void AddInfo(const AEmotion& rEmotion);	// 表情追加
	void SetAllInfo(const AFace& rFace);	// 表情全設定
	inline VECTOR3 GetOriginPosition() const	{ return m_pos; }		// 原点位置取得
	inline int GetEmotion() const	{ return m_nTypeEmo; }				// 表情取得
	inline int GetNumEmotion()		{ return m_info.GetNumEmotion(); }	// 表情総数取得

private:
	// メンバ関数
	void SetPositionRelative();	// 相対位置設定

	// メンバ変数
	VECTOR3 m_pos;	// 原点位置
	AFace m_info;	// 表情情報
	int m_nTypeEmo;	// 表情種類
};

#endif	// _OBJECTFACE_ANIM2D_H_
