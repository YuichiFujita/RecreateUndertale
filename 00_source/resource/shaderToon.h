//============================================================
//
//	トゥーンシェーダーヘッダー [shaderToon.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SHADER_TOON_H_
#define _SHADER_TOON_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "shader.h"

//************************************************************
//	クラス定義
//************************************************************
// トゥーンシェーダークラス
class CToonShader : public CShader
{
public:
	// テクスチャ列挙
	enum ETexture
	{
		TEXTURE_TOON = 0,	// トゥーンマップテクスチャ
		TEXTURE_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CToonShader();

	// デストラクタ
	~CToonShader() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了

	// メンバ関数
	void SetLightDirect(MATRIX* pMtxWorld, const int nLightIdx);	// ライト方向ベクトル設定
	void SetTexture(const CTexture::STexture& rTexture);			// テクスチャ設定 (ポインタ)
	void SetTexture(const int nTextureIdx);							// テクスチャ設定 (インデックス)
	void SetMaterial(const D3DMATERIAL9& rMaterial);				// マテリアル設定
	void SetDiffuse(const COLOR& rDiffuse);							// 拡散光設定
	void SetAmbient(const COLOR& rAmbient);							// 環境光設定
	void SetEmissive(const COLOR& rEmissive);						// 放射光設定
	void SetOnlyDiffuse(const COLOR& rDiffuse);						// 拡散光のみ設定

	// 静的メンバ関数
	static CToonShader* Create();		// 生成
	static CToonShader* GetInstance();	// 取得
	static void Release();				// 破棄

private:
	// メンバ関数
	void SetToonMapTexture(const ETexture texture);	// トゥーンマップテクスチャ設定

	// 静的メンバ変数
	static CToonShader* m_pShader;	// シェーダー情報

	// メンバ変数
	D3DXHANDLE m_pTextureToon;	// トゥーンマップテクスチャ
	D3DXHANDLE m_pDirectLight;	// 平行光源の方向ベクトル
	D3DXHANDLE m_pDiffuse;		// 拡散光
	D3DXHANDLE m_pAmbient;		// 環境光
	D3DXHANDLE m_pEmissive;		// 放射光
	D3DXHANDLE m_pUseTexture;	// テクスチャの使用状況
};

#endif	// _SHADER_TOON_H_
