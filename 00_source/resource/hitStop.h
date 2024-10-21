//============================================================
//
//	ヒットストップヘッダー [hitStop.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _HITSTOP_H_
#define _HITSTOP_H_

//************************************************************
//	クラス定義
//************************************************************
// ヒットストップクラス
class CHitStop
{
public:
	// コンストラクタ
	CHitStop();

	// デストラクタ
	~CHitStop();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);	// 更新
	void Draw();							// 描画
	void SetStop(const int nCounter);		// 停止状況設定
	inline bool IsStop() const { return m_bStop; }	// 停止状況取得

	// 静的メンバ関数
	static CHitStop* Create();					// 生成
	static void Release(CHitStop*& prHitStop);	// 破棄

private:
	// メンバ変数
	bool m_bStop;	// 停止状況
	int m_nCounter;	// 停止時間
};

#endif	// _HITSTOP_H_
