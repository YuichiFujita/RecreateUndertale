//============================================================
//
//	ステージヘッダー [stage.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _STAGE_H_
#define _STAGE_H_

//************************************************************
//	クラス定義
//************************************************************
// ステージクラス
class CStage
{
public:
	// コンストラクタ
	CStage();

	// デストラクタ
	~CStage();

	// ステージ範囲構造体
	struct SLimit
	{
		float fUp;		// 制限位置 (上)
		float fDown;	// 制限位置 (下)
		float fLeft;	// 制限位置 (左)
		float fRight;	// 制限位置 (右)
	};

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	HRESULT BindStage(const char *pStagePass);	// ステージ割当
	void LimitPosition(D3DXVECTOR3& rPos, const float fRadius);	// 位置範囲補正
	void SetLimit(const SLimit& rLimit)	{ m_limit = rLimit; }	// ステージ範囲設定
	SLimit GetLimit(void) const			{ return m_limit; }		// ステージ範囲取得

	// 静的メンバ関数
	static CStage *Create(void);			// 生成
	static void Release(CStage *&prStage);	// 破棄

private:
	// メンバ関数
	HRESULT LoadLimit(std::ifstream *pFile, std::string& rString);	// ステージ範囲情報の読込

	// メンバ変数
	SLimit m_limit;	// ステージ範囲情報
};

#endif	// _STAGE_H_
