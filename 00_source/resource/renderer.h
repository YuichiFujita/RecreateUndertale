//============================================================
//
//	レンダラーヘッダー [renderer.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_

//************************************************************
//	前方宣言
//************************************************************
class CScreen;	// スクリーンクラス

//************************************************************
//	クラス定義
//************************************************************
// レンダラークラス
class CRenderer
{
public:
	// コンストラクタ
	CRenderer();

	// デストラクタ
	~CRenderer();

	// メンバ関数
	HRESULT Init(HWND hWnd, BOOL bWindow);	// 初期化
	void Uninit();						// 終了
	void Update(const float fDeltaTime);	// 更新
	void Draw();						// 描画

	HRESULT CreateRenderTexture();			// レンダーテクスチャー生成
	LPDIRECT3DDEVICE9 GetDevice() const;	// デバイス取得
	COLOR GetClearColor() const;			// 画面クリア色取得

	// 静的メンバ関数
	static CRenderer* Create(HWND hWnd, BOOL bWindow);	// 生成
	static void Release(CRenderer*& prRenderer);		// 破棄

private:
	// メンバ関数
	HRESULT CreateDevice(HWND hWnd, D3DPRESENT_PARAMETERS d3dpp);	// デバイス生成

	// メンバ変数
	LPDIRECT3D9			m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9	m_pD3DDevice;	// Direct3Dデバイス

	int m_nScreenTexID;		// スクリーンテクスチャのインデックス
	CScreen* m_pDrawScreen;	// スクリーン描画ポリゴン
	LPDIRECT3DSURFACE9 m_pDefSurScreen;	// 元のスクリーン描画サーフェイス保存用
	LPDIRECT3DSURFACE9 m_pSurScreen;	// スクリーン描画サーフェイスへのポインタ
};

#endif	// _RENDERER_H_
