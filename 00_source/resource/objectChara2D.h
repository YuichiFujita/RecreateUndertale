//============================================================
//
//	オブジェクトキャラクター2Dヘッダー [objectChara2D.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _OBJECTCHARA2D_H_
#define _OBJECTCHARA2D_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "anim3D.h"

//************************************************************
//	クラス定義
//************************************************************
// オブジェクトキャラクター2Dクラス
class CObjectChara2D : public CAnim3D
{
public:
	// コンストラクタ
	explicit CObjectChara2D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// デストラクタ
	~CObjectChara2D() override;

	// キャラクター管理構造体
	struct SChara
	{
		// コンストラクタ
		SChara() :
			ptrnTexture	(GRID2_ZERO),	// テクスチャ分割数
			nMaxPtrn	(0),			// 最大パターン数
			sizeChara	(VEC3_ZERO),	// キャラクター大きさ
			pNextTime	(nullptr),		// パターン変更時間
			bLoop		(false)			// ループON/OFF
		{
			sPassTexture.clear();	// テクスチャパスをクリア
		}

		// デストラクタ
		~SChara() { SAFE_DEL_ARRAY(pNextTime); }	// TODO：なぜダメ？

		// テクスチャ分割数・パターン総数の設定処理
		HRESULT SetTexPtrn(const POSGRID2& rPtrn)
		{
			// テクスチャ分割数・パターン総数を設定
			ptrnTexture = rPtrn;
			nMaxPtrn = rPtrn.x * rPtrn.y;

			// パターン変更時間の破棄
			SAFE_DEL_ARRAY(pNextTime);

			// パターン変更時間の生成
			pNextTime = new float[nMaxPtrn];
			if (pNextTime == nullptr)
			{
				// 失敗を返す
				return E_FAIL;
			}

			// パターン変更時間を初期化
			SetNextTime(DEF_NEXT);
			return S_OK;
		}

		// パターン変更時間の設定処理
		HRESULT SetNextTime(const float fNextTime)
		{
			// 変更時間がプラスではない場合失敗
			if (fNextTime <= 0.0f) { return E_FAIL; }
			for (int i = 0; i < nMaxPtrn; i++)
			{
				// 引数のパターン変更時間を設定
				pNextTime[i] = fNextTime;
			}
			return S_OK;
		}

		// メンバ変数
		std::string sPassTexture;	// テクスチャパス
		POSGRID2 ptrnTexture;		// テクスチャ分割数
		int nMaxPtrn;				// 最大パターン数
		D3DXVECTOR3 sizeChara;		// キャラクター大きさ
		float *pNextTime;			// パターン変更時間
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

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CObjectChara2D *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot = VEC3_ZERO);	// 生成

	// メンバ関数
	void BindCharaData(const char *pCharaPass);	// キャラクター情報割当
	void SetMotion(const int nType);			// モーション設定
	void AddInfo(const SMotion& rMotion);		// モーション情報追加
	void SetAllInfo(const SInfo& rInfo);		// モーション情報全設定

	bool IsCancel(void) const;	// キャンセル取得
	bool IsCombo(void) const;	// コンボ取得
	int GetMotion(void) const	{ return m_info.nType; }			// モーション取得
	int GetNumType(void)		{ return m_info.GetNumMotion(); }	// 種類総数取得
	float GetCancelTime(const int nType) const	{ return m_info.vecMotion[nType].fCancelTime; }	// キャンセル時間取得
	float GetComboTime(const int nType) const	{ return m_info.vecMotion[nType].fComboTime; }	// コンボ時間取得

private:
	// メンバ変数
	SInfo m_info;	// モーション情報
};

#endif	// _OBJECTCHARA2D_H_
