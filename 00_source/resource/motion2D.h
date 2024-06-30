//============================================================
//
//	モーション2Dヘッダー [motion2D.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _MOTION2D_H_
#define _MOTION2D_H_

//************************************************************
//	前方宣言
//************************************************************
class CObjectChara2D;	// オブジェクトキャラクタークラス

//************************************************************
//	クラス定義
//************************************************************
// モーション2Dクラス
class CMotion2D
{
public:
	// コンストラクタ
	CMotion2D();

	// デストラクタ
	~CMotion2D();

	// キャラクター管理構造体
	struct SChara
	{
		// コンストラクタ
		SChara() :
			ptrnTexture	(GRID2_ZERO),	// テクスチャ分割数
			nMaxPtrn	(0),			// 最大パターン数
			sizeChara	(VEC3_ZERO),	// キャラクター大きさ
			fNextTime	(0.0f),			// パターン変更時間
			bLoop		(false)			// ループON/OFF
		{
			sPassTexture.clear();	// テクスチャパスをクリア
		}

		// メンバ変数
		std::string sPassTexture;	// テクスチャパス
		POSGRID2 ptrnTexture;		// テクスチャ分割数
		int nMaxPtrn;				// 最大パターン数
		D3DXVECTOR3 sizeChara;		// キャラクター大きさ
		float fNextTime;			// パターン変更時間
		bool bLoop;					// ループON/OFF
	};

	// モーション管理構造体
	struct SMotion
	{
		// コンストラクタ
		SMotion() :
			fCancelTime	(-1.0f),	// キャンセル可能時間
			fComboTime	(-1.0f)		// コンボ可能時間
		{}

		// メンバ変数
		SChara infoChara;	// キャラクター情報
		float fCancelTime;	// キャンセル可能時間
		float fComboTime;	// コンボ可能時間
	};

	// モーション情報構造体
	struct SInfo
	{
		// コンストラクタ
		SInfo() :
			nType	(0)	// モーション種類
		{
			vecMotion.clear();	// モーション情報をクリア
		}

		// メンバ関数
		int GetNumMotion(void) { return (int)vecMotion.size(); }	// モーション情報の総数取得

		// メンバ変数
		std::vector<SMotion> vecMotion;	// モーション情報
		int nType;	// モーション種類
	};

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(const float fDeltaTime);	// 更新
	void Set(const int nType);				// 設定
	void AddInfo(const SMotion& rMotion);	// モーション情報追加
	void SetAllInfo(const SInfo& rInfo);	// モーション情報全設定

	bool IsCancel(void) const;	// キャンセル取得
	bool IsCombo(void) const;	// コンボ取得
	int GetNumType(void)		{ return m_info.GetNumMotion(); }	// 種類総数取得
	int GetType(void) const		{ return m_info.nType; }			// 種類取得
	float GetCancelTime(const int nType) const	{ return m_info.vecMotion[nType].fCancelTime; }	// モーションキャンセル時間取得
	float GetComboTime(const int nType) const	{ return m_info.vecMotion[nType].fComboTime; }	// モーションコンボ時間取得

	// 静的メンバ関数
	static CMotion2D *Create(CObjectChara2D *pChara);	// 生成
	static void Release(CMotion2D *&prMotion);			// 破棄

private:
	// メンバ変数
	CObjectChara2D *m_pChara;	// オブジェクトキャラクター2D情報
	SInfo m_info;	// モーション情報
};

#endif	// _MOTION2D_H_
