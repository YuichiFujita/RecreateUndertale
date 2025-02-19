//============================================================
//
//	表情アニメーション2Dヘッダー [faceAnim2D.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FACE_ANIM2D_H_
#define _FACE_ANIM2D_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "extension.h"
#include "anim2D.h"

//************************************************************
//	クラス定義
//************************************************************
// 表情アニメーション2Dクラス
class CFaceAnim2D
{
public:
	// コンストラクタ
	CFaceAnim2D();

	// デストラクタ
	~CFaceAnim2D();

	// 表情管理構造体
	struct SEmotion
	{
		// デフォルトコンストラクタ
		SEmotion() :
			vecNextTime	 ({}),			// パターン変更時間配列
			sPathTexture (""),			// テクスチャパス
			ptrnTexture	 (GRID2_ZERO),	// テクスチャ分割数
			nMaxPtrn	 (0),			// 最大パターン数
			offset		 (VEC3_ZERO),	// 原点オフセット
			size		 (VEC3_ZERO),	// キャラクター大きさ
			bLoop		 (false)		// ループON/OFF
		{}

		// デストラクタ
		~SEmotion() {}

		// テクスチャ分割数・パターン総数の設定
		inline HRESULT SetTexPtrn(const POSGRID2& rPtrn)
		{
			// テクスチャ分割数・パターン総数を設定
			ptrnTexture = rPtrn;
			nMaxPtrn = rPtrn.x * rPtrn.y;

			// パターン変更時間の破棄
			vecNextTime.clear();

			// パターン変更時間の生成
			vecNextTime.resize(nMaxPtrn);

			// パターン変更時間を初期化
			if (FAILED(SetNextTime(CAnim2D::DEF_NEXT))) { return E_FAIL; }

			return S_OK;
		}

		// パターン変更時間の設定
		inline HRESULT SetNextTime(const float fNextTime)
		{
			if (fNextTime <= 0.0f)					 { return E_FAIL; }	// 変更時間がプラスではない場合失敗
			if (nMaxPtrn != (int)vecNextTime.size()) { return E_FAIL; }	// パターン最大数と同じサイズではない場合失敗

			for (int i = 0; i < nMaxPtrn; i++)
			{
				// 引数のパターン変更時間を設定
				vecNextTime[i] = fNextTime;
			}

			return S_OK;
		}

		// メンバ変数
		std::vector<float> vecNextTime;	// パターン変更時間配列
		std::string sPathTexture;		// テクスチャパス
		POSGRID2 ptrnTexture;			// テクスチャ分割数
		int nMaxPtrn;	// 最大パターン数
		VECTOR3 offset;	// 原点オフセット
		VECTOR3 size;	// 顔大きさ
		bool bLoop;		// ループON/OFF
	};

	// 顔管理構造体
	struct SFace
	{
		// デフォルトコンストラクタ
		SFace() :
			vecEmotion	({})	// 表情情報
		{}

		// デストラクタ
		~SFace() {}

		// メンバ関数
		inline int GetNumEmotion() { return (int)vecEmotion.size(); }	// 表情情報の総数取得

		// メンバ変数
		std::vector<SEmotion> vecEmotion;	// 表情情報
	};

	// メンバ関数
	HRESULT Init();		// 初期化
	void Uninit();		// 終了
	HRESULT LoadAll();	// 全読込
	SFace GetInfo(const int nIdx);	// 顔情報取得

	// 静的メンバ関数
	static CFaceAnim2D* Create();	// 生成
	static void Release(CFaceAnim2D*& prFaceAnim2D);	// 破棄

private:
	// メンバ関数
	HRESULT LoadSetup();	// セットアップ
	HRESULT LoadFaceSetup(SFace* pInfoFace, const char* pFacePath);		// 顔情報セットアップ
	HRESULT LoadEmotionSetup(SFace* pInfoFace, const char* pEmoPath);	// 表情情報セットアップ

	// メンバ変数
	std::vector<SFace> m_vecFace;	// 顔情報
};

#endif	// _FACE_ANIM2D_H_
