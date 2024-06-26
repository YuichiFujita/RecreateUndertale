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

	// キー管理構造体
	struct SKey
	{
		// コンストラクタ
		SKey() :
			move	(VEC3_ZERO),	// キー移動量
			nFrame	(0)				// キー再生フレーム数
		{}

		// メンバ変数
		D3DXVECTOR3 move;	// キー移動量
		int nFrame;			// キー再生フレーム数
	};

	// モーション管理構造体
	struct SMotion
	{
		// コンストラクタ
		SMotion() :
			nWholeFrame		(0),		// モーション全体フレーム数
			nCancelFrame	(NONE_IDX),	// キャンセル可能フレーム
			nComboFrame		(NONE_IDX),	// コンボ可能フレーム
			bLoop			(false)		// ループON/OFF
		{
			vecKey.clear();	// キー情報をクリア
		}

		// メンバ関数
		int GetNumKey(void) { return (int)vecKey.size(); }	// キー情報の総数取得

		// メンバ変数
		std::vector<SKey> vecKey;	// キー情報
		int  nWholeFrame;	// モーション全体フレーム数
		int  nCancelFrame;	// キャンセル可能フレーム
		int  nComboFrame;	// コンボ可能フレーム
		bool bLoop;			// ループON/OFF
	};

	// モーション情報構造体
	struct SInfo
	{
		// コンストラクタ
		SInfo() :
			nType			(0),	// モーション種類
			nKey			(0),	// モーションキー番号
			nKeyCounter		(0),	// モーションキーカウンター
			nWholeCounter	(0),	// モーション全体カウンター
			bFinish			(true)	// モーション終了状況
		{
			vecMotion.clear();	// モーション情報をクリア
		}

		// メンバ関数
		int GetNumMotion(void) { return (int)vecMotion.size(); }	// モーション情報の総数取得

		// メンバ変数
		std::vector<SMotion> vecMotion;	// モーション情報
		int  nType;			// モーション種類
		int  nKey;			// モーションキー番号
		int  nKeyCounter;	// モーションキーカウンター
		int  nWholeCounter;	// モーション全体カウンター
		bool bFinish;		// モーション終了状況
	};

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(const float fDeltaTime);		// 更新
	void BindPartsData(/*CMultiModel **ppModel*/);	// パーツ情報設定
	void SetAllInfo(const SInfo& rInfo);		// モーション情報全設定
	void AddInfo(const SMotion& rMotion);		// モーション情報追加
	void SetEnableUpdate(const bool bUpdate);	// 更新状況設定
	void ClearVector(void);						// モーション情報の動的配列クリア
	void Set(const int nType);					// 設定
	int GetNumType(void);						// 種類総数取得
	int GetNumKey(const int nType);				// キー総数取得
	bool IsCancel(const int nType) const;		// キャンセル取得
	bool IsCombo(const int nType) const;		// コンボ取得

	int GetType(void) const			{ return m_info.nType; }			// 種類取得
	int GetKey(void) const			{ return m_info.nKey; }				// キー番号取得
	int GetKeyCounter(void) const	{ return m_info.nKeyCounter; }		// モーションキーカウンター取得
	int GetWholeCounter(void) const	{ return m_info.nWholeCounter; }	// モーション全体カウンター取得
	bool IsFinish(void) const		{ return m_info.bFinish; }			// 終了取得
	bool IsLoop(const int nType) const			{ return m_info.vecMotion[nType].bLoop; }			// ループ取得
	int GetWholeFrame(const int nType) const	{ return m_info.vecMotion[nType].nWholeFrame; }		// モーション全体フレーム数取得
	int GetCancelFrame(const int nType) const	{ return m_info.vecMotion[nType].nCancelFrame; }	// モーションキャンセルフレーム取得
	int GetComboFrame(const int nType) const	{ return m_info.vecMotion[nType].nComboFrame; }		// モーションコンボフレーム取得

	// 静的メンバ関数
	static CMotion2D *Create(CObjectChara2D *pChara);	// 生成
	static void Release(CMotion2D *&prMotion);			// 破棄

private:
	// メンバ関数
	void UpdateMove(void);		// 移動更新
	void UpdateMotion(void);	// モーション更新

	// メンバ変数
	CObjectChara2D *m_pChara;	// オブジェクトキャラクター2D情報
	SInfo m_info;	// モーション情報
	bool m_bUpdate;	// 更新状況
};

#endif	// _MOTION2D_H_
