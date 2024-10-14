//============================================================
//
//	便利関数ヘッダー [useful.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _USEFUL_H_
#define _USEFUL_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "renderState.h"

//************************************************************
//	マクロ定義
//************************************************************
// 便利マクロ
#define SCREEN_WIDTH	(960)	// ウインドウの横幅
#define SCREEN_HEIGHT	(720)	// ウインドウの縦幅
#define MAX_STRING		(128)	// 文字列の最大文字数
#define MAX_FILENAME	(256)	// ファイル名の最大文字数
#define NONE_IDX		(-1)	// インデックス非使用
#define NONE_STRING		("\0")	// 文字列非使用
#define SIZE_TILE		(60)	// マップタイルの大きさ

#define HALF_PI	(D3DX_PI * 0.5f)	// 二分の一の円周率 (π/２)
#define QRTR_PI	(D3DX_PI * 0.25f)	// 四分の一の円周率 (π/４)

#define NUM_ARRAY(a)	(sizeof((a)) / sizeof((a)[0]))	// 配列の要素数計算

// メモリ開放マクロ
#define SAFE_UNINIT(p)		if ((p) != nullptr) { (p)->Uninit();		(p) = nullptr; }	// Uninit関数の破棄マクロ
#define SAFE_FREE(p)		if ((p) != nullptr) { free((p));			(p) = nullptr; }	// free関数の破棄マクロ
#define SAFE_RELEASE(p)		if ((p) != nullptr) { (p)->Release();		(p) = nullptr; }	// Release関数の破棄マクロ
#define SAFE_DEL_OBJECT(p)	if ((p) != nullptr) { DeleteObject((p));	(p) = nullptr; }	// DeleteObject関数の破棄マクロ
#define SAFE_REF_RELEASE(p)	if ((p) != nullptr) { (p)->Release((p)); }						// 参照ポインタ付きRelease関数の破棄マクロ
#define SAFE_DELETE(p)		if ((p) != nullptr) { delete	(p);		(p) = nullptr; }	// 配列を使用しないdeleteを使用する破棄マクロ
#define SAFE_DEL_ARRAY(p)	if ((p) != nullptr) { delete[]	(p);		(p) = nullptr; }	// 配列を使用したdelete[]を使用する破棄マクロ

// マネージャー関係
#define GET_MANAGER		(CManager::GetInstance())					// マネージャーインスタンス取得
#define GET_INPUTKEY	(CManager::GetInstance()->GetKeyboard())	// キーボード情報取得
#define GET_INPUTMOUSE	(CManager::GetInstance()->GetMouse())		// マウス情報取得
#define GET_INPUTPAD	(CManager::GetInstance()->GetPad())			// パッド情報取得
#define GET_RETENTION	(CManager::GetInstance()->GetRetention())	// データ保存情報取得
#define GET_RENDERER	(CManager::GetInstance()->GetRenderer())	// レンダラー情報取得

#define GET_DEVICE			(CManager::GetInstance()->GetRenderer()->GetDevice())					// デバイス情報取得
#define PLAY_SOUND(label)	(CManager::GetInstance()->GetSound()->Play((CSound::ELabel)(label)))	// サウンド再生

// D3DXVECTOR2関係
#define VEC2_ZERO	(D3DXVECTOR2(0.0f, 0.0f))	// 0クリア
#define VEC2_ONE	(D3DXVECTOR2(1.0f, 1.0f))	// 1クリア
#define VEC2_ALL(f)	(D3DXVECTOR2((f), (f))		// 同値クリア

// D3DXVECTOR3関係
#define VEC3_ZERO	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))	// 0クリア
#define VEC3_ONE	(D3DXVECTOR3(1.0f, 1.0f, 1.0f))	// 1クリア
#define VEC3_ALL(f)	(D3DXVECTOR3((f), (f), (f)))	// 同値クリア

#define SCREEN_CENT	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f))	// ウインドウの中央座標
#define SCREEN_SIZE	(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f))	// ウインドウの画面サイズ

// POSGRID2関係
#define GRID2_ZERO	(POSGRID2(0, 0))	// 0クリア
#define GRID2_ONE	(POSGRID2(1, 1))	// 1クリア

// POSGRID3関係
#define GRID3_ZERO	(POSGRID3(0, 0, 0))	// 0クリア
#define GRID3_ONE	(POSGRID3(1, 1, 1))	// 1クリア

// D3DXCOLOR関係
#define XCOL_ABLACK		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))	// 黒色(透明)
#define XCOL_BLACK		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))	// 黒色(不透明)
#define XCOL_AWHITE		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))	// 白色(透明)
#define XCOL_WHITE		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// 白色(不透明)
#define XCOL_ARED		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f))	// 赤色(透明)
#define XCOL_RED		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))	// 赤色(不透明)
#define XCOL_AGREEN		(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f))	// 緑色(透明)
#define XCOL_GREEN		(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))	// 緑色(不透明)
#define XCOL_ABLUE		(D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f))	// 青色(透明)
#define XCOL_BLUE		(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))	// 青色(不透明)
#define XCOL_AYELLOW	(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f))	// 黄色(透明)
#define XCOL_YELLOW		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	// 黄色(不透明)
#define XCOL_ACYAN		(D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.0f))	// 水色(透明)
#define XCOL_CYAN		(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f))	// 水色(不透明)

// RenderState関係
#define RS_BL_NORMAL	(CRenderState::SBlendAlpha(D3DBLENDOP_ADD,			D3DBLEND_SRCALPHA,	D3DBLEND_INVSRCALPHA))	// 通常αブレンド
#define RS_BL_ADD		(CRenderState::SBlendAlpha(D3DBLENDOP_ADD,			D3DBLEND_SRCALPHA,	D3DBLEND_ONE))			// 加算αブレンド
#define RS_BL_SUB		(CRenderState::SBlendAlpha(D3DBLENDOP_REVSUBTRACT,	D3DBLEND_SRCALPHA,	D3DBLEND_ONE))			// 減算αブレンド

//************************************************************
//	構造体定義
//************************************************************
// 2整数座標
struct POSGRID2
{
	// デフォルトコンストラクタ
	POSGRID2() : x(0), y(0) {}

	// 引数付きコンストラクタ
	POSGRID2(const int XY) : x(XY), y(XY) {}
	POSGRID2(const int X, const int Y) : x(X), y(Y) {}

	// デストラクタ
	~POSGRID2() {}

	// メンバ変数
	int x;	// 方眼座標 (x)
	int y;	// 方眼座標 (y)

	//********************************************************
	//	演算子オーバーロード
	//********************************************************
	// 加算
	inline POSGRID2 operator+(const POSGRID2& grid) const	{ return POSGRID2(x + grid.x, y + grid.y); }
	inline POSGRID2 operator+(const int nVal) const			{ return POSGRID2(x + nVal, y + nVal); }

	// 減算
	inline POSGRID2 operator-(const POSGRID2& grid) const	{ return POSGRID2(x - grid.x, y - grid.y); }
	inline POSGRID2 operator-(const int nVal) const			{ return POSGRID2(x - nVal, y - nVal); }
	inline POSGRID2 operator-(void) const					{ return POSGRID2(-x, -y); }

	// 乗算
	inline POSGRID2 operator*(const int nVal) const	{ return POSGRID2(x * nVal, y * nVal); }

	// 除算
	inline POSGRID2 operator/(const int nVal) const	{ return POSGRID2(x / nVal, y / nVal); }

	// 加算代入
	inline POSGRID2& operator+=(const int nVal)
	{
		x += nVal;
		y += nVal;
		return *this;
	}
	inline POSGRID2& operator+=(const POSGRID2& grid)
	{
		x += grid.x;
		y += grid.y;
		return *this;
	}

	// 減算代入
	inline POSGRID2& operator-=(const int nVal)
	{
		x -= nVal;
		y -= nVal;
		return *this;
	}
	inline POSGRID2& operator-=(const POSGRID2& grid)
	{
		x -= grid.x;
		y -= grid.y;
		return *this;
	}

	// 乗算代入
	inline POSGRID2& operator*=(const int nVal)
	{
		x *= nVal;
		y *= nVal;
		return *this;
	}
	inline POSGRID2& operator*=(const POSGRID2& grid)
	{
		x *= grid.x;
		y *= grid.y;
		return *this;
	}

	// 除算代入
	inline POSGRID2& operator/=(const int nVal)
	{
		x /= nVal;
		y /= nVal;
		return *this;
	}
	inline POSGRID2& operator/=(const POSGRID2& grid)
	{
		x /= grid.x;
		y /= grid.y;
		return *this;
	}

	//********************************************************
	//	メンバ関数
	//********************************************************
	/*
		@brief	座標が一致するかの検証
		@return	判定結果
	*/
	inline bool operator==(const POSGRID2& grid) const
	{
		if (grid.x == x && grid.y == y) { return true; }
		return false;
	}

	/*
		@brief	座標が一致しないかの検証
		@return	判定結果
	*/
	inline bool operator!=(const POSGRID2& grid) const
	{
		if (grid.x != x || grid.y != y) { return true; }
		return false;
	}

	/*
		@brief	方眼座標の反転
		@return	反転された方眼座標
	*/
	inline POSGRID2 Invert() { return POSGRID2(-x, -y); }

	/*
		@brief	要素がすべてゼロか
		@return	判定結果
	*/
	inline bool IsZero() const
	{
		if (x == 0 && y == 0) { return true; }
		return false;
	}
};

// 3整数座標
struct POSGRID3
{
	// デフォルトコンストラクタ
	POSGRID3() : x(0), y(0), z(0) {}

	// 引数付きコンストラクタ
	POSGRID3(const int XYZ) : x(XYZ), y(XYZ), z(XYZ) {}
	POSGRID3(const int X, const int Y, const int Z) : x(X), y(Y), z(Z) {}

	// デストラクタ
	~POSGRID3() {}

	// メンバ変数
	int x;	// 方眼座標 (x)
	int y;	// 方眼座標 (y)
	int z;	// 方眼座標 (z)

	//********************************************************
	//	演算子オーバーロード
	//********************************************************
	// 加算
	inline POSGRID3 operator+(const POSGRID3& grid) const	{ return POSGRID3(x + grid.x, y + grid.y, z + grid.z); }
	inline POSGRID3 operator+(const int nVal) const			{ return POSGRID3(x + nVal, y + nVal, z + nVal); }

	// 減算
	inline POSGRID3 operator-(const POSGRID3& grid) const	{ return POSGRID3(x - grid.x, y - grid.y, z - grid.z); }
	inline POSGRID3 operator-(const int nVal) const			{ return POSGRID3(x - nVal, y - nVal, z - nVal); }
	inline POSGRID3 operator-(void) const					{ return POSGRID3(-x, -y, -z); }

	// 乗算
	inline POSGRID3 operator*(const int nVal) const	{ return POSGRID3(x * nVal, y * nVal, z * nVal); }

	// 除算
	inline POSGRID3 operator/(const int nVal) const	{ return POSGRID3(x / nVal, y / nVal, z / nVal); }

	// 加算代入
	inline POSGRID3& operator+=(const int nVal)
	{
		x += nVal;
		y += nVal;
		z += nVal;
		return *this;
	}
	inline POSGRID3& operator+=(const POSGRID3& grid)
	{
		x += grid.x;
		y += grid.y;
		z += grid.z;
		return *this;
	}

	// 減算代入
	inline POSGRID3& operator-=(const int nVal)
	{
		x -= nVal;
		y -= nVal;
		z -= nVal;
		return *this;
	}
	inline POSGRID3& operator-=(const POSGRID3& grid)
	{
		x -= grid.x;
		y -= grid.y;
		z -= grid.z;
		return *this;
	}

	// 乗算代入
	inline POSGRID3& operator*=(const int nVal)
	{
		x *= nVal;
		y *= nVal;
		z *= nVal;
		return *this;
	}
	inline POSGRID3& operator*=(const POSGRID3& grid)
	{
		x *= grid.x;
		y *= grid.y;
		z *= grid.z;
		return *this;
	}

	// 除算代入
	inline POSGRID3& operator/=(const int nVal)
	{
		x /= nVal;
		y /= nVal;
		z /= nVal;
		return *this;
	}
	inline POSGRID3& operator/=(const POSGRID3& grid)
	{
		x /= grid.x;
		y /= grid.y;
		z /= grid.z;
		return *this;
	}

	//********************************************************
	//	メンバ関数
	//********************************************************
	/*
		@brief	座標が一致するかの検証
		@return	判定結果
	*/
	inline bool operator==(const POSGRID3& grid) const
	{
		if (grid.x == x && grid.y == y && grid.z == z) { return true; }
		return false;
	}

	/*
		@brief	座標が一致しないかの検証
		@return	判定結果
	*/
	inline bool operator!=(const POSGRID3& grid) const
	{
		if (grid.x != x || grid.y != y || grid.z != z) { return true; }
		return false;
	}

	/*
		@brief	方眼座標の反転
		@return	反転された方眼座標
	*/
	inline POSGRID3 Invert() { return POSGRID3(-x, -y, -z); }

	/*
		@brief	要素がすべてゼロか
		@return	判定結果
	*/
	inline bool IsZero() const
	{
		if (x == 0 && y == 0 && z == 0) { return true; }
		return false;
	}
};

// 色
struct Color : public D3DXCOLOR
{
	// デフォルトコンストラクタ
	Color() : D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) {}

	// 引数付きコンストラクタ
	Color(const float all) : D3DXCOLOR(all, all, all, all) {}
	Color(const float col, const float alpha) : D3DXCOLOR(col, col, col, alpha) {}
	Color(const float r, const float g, const float b, const float a) : D3DXCOLOR(r, g, b, a) {}

	/*
		@brief	D3DCOLOR型(DWORD)からの初期化コンストラクタ
	*/
	Color(const D3DCOLOR argb)
	{
		const float fRate = 1.0f / 255.0f;
		a = fRate * (float)(unsigned char)(argb >> 24);
		r = fRate * (float)(unsigned char)(argb >> 16);
		g = fRate * (float)(unsigned char)(argb >> 8);
		b = fRate * (float)(unsigned char)(argb >> 0);
	}

	/*
		@brief	D3DXCOLOR型(float4)からの初期化コンストラクタ
	*/
	Color(const D3DXCOLOR col) : D3DXCOLOR(col) {}

	// デストラクタ
	~Color() {}

	//********************************************************
	//	メンバ関数
	//********************************************************
	inline void Black(void)					{ *this = Color(0.0f, 0.0f, 0.0f, 1.0f); }		// 黒色/不透明
	inline void Black(const float fAlpha)	{ *this = Color(0.0f, 0.0f, 0.0f, fAlpha); }	// 黒色/透明度
	inline void White(void)					{ *this = Color(1.0f, 1.0f, 1.0f, 1.0f); }		// 白色/不透明
	inline void White(const float fAlpha)	{ *this = Color(1.0f, 1.0f, 1.0f, fAlpha); }	// 白色/透明度
	inline void Red(void)					{ *this = Color(1.0f, 0.0f, 0.0f, 1.0f); }		// 赤色/不透明
	inline void Red(const float fAlpha)		{ *this = Color(1.0f, 0.0f, 0.0f, fAlpha); }	// 赤色/透明度
	inline void Green(void)					{ *this = Color(0.0f, 1.0f, 0.0f, 1.0f); }		// 緑色/不透明
	inline void Green(const float fAlpha)	{ *this = Color(0.0f, 1.0f, 0.0f, fAlpha); }	// 緑色/透明度
	inline void Blue(void)					{ *this = Color(0.0f, 0.0f, 1.0f, 1.0f); }		// 青色/不透明
	inline void Blue(const float fAlpha)	{ *this = Color(0.0f, 0.0f, 1.0f, fAlpha); }	// 青色/透明度
	inline void Yellow(void)				{ *this = Color(1.0f, 1.0f, 0.0f, 1.0f); }		// 黄色/不透明
	inline void Yellow(const float fAlpha)	{ *this = Color(1.0f, 1.0f, 0.0f, fAlpha); }	// 黄色/透明度
	inline void Cyan(void)					{ *this = Color(0.0f, 1.0f, 1.0f, 1.0f); }		// 水色/不透明
	inline void Cyan(const float fAlpha)	{ *this = Color(0.0f, 1.0f, 1.0f, fAlpha); }	// 水色/透明度
	inline void Purple(void)				{ *this = Color(1.0f, 0.0f, 1.0f, 1.0f); }		// 紫色/不透明
	inline void Purple(const float fAlpha)	{ *this = Color(1.0f, 0.0f, 1.0f, fAlpha); }	// 紫色/透明度

	/*
		@brief	カラーコードから色/透明度の設定
	*/
	inline void Code(const std::string& rCode, const float fAlpha)
	{
		assert((int)rCode.size() == 6);
		int R = std::stoi(rCode.substr(0, 2), nullptr, 16);
		int G = std::stoi(rCode.substr(2, 2), nullptr, 16);
		int B = std::stoi(rCode.substr(4, 2), nullptr, 16);
		*this = D3DCOLOR_RGBA(R, G, B, (int)(fAlpha * 255.0f));
	}

	/*
		@brief	カラーコードから色の設定
	*/
	inline void Code(const std::string& rCode)
	{
		this->Code(rCode, 1.0f);
	}

	/*
		@brief	透明度がゼロか
		@return	判定結果
	*/
	inline bool IsAlpha(void) const
	{
		if (a <= 0.0f) { return true; }
		return false;
	}
};

//************************************************************
//	エイリアス定義
//************************************************************
using AText = std::vector<std::string>;	// テキスト保存型
using ATextBox = std::vector<AText>;	// 複数テキスト保存型

//************************************************************
//	名前空間宣言
//************************************************************
// 便利関数空間
namespace useful
{
	// 通常関数
	void DivideDigitNum		// 数値の桁数ごとの分解
	( // 引数
		int *pNumDivide,	// 分解結果の格納配列
		const int nNum,		// 分解する数値
		const int nMaxDigit	// 分解する数字の桁数
	);
	void NormalizeNormal	// 法線の正規化
	( // 引数
		const D3DXVECTOR3& rPosLeft,	// 左位置
		const D3DXVECTOR3& rPosCenter,	// 中心位置
		const D3DXVECTOR3& rPosRight,	// 右位置
		D3DXVECTOR3& rNor				// 法線
	);
	void ReplaceConsecChar	// 文字列内の連続文字の置換
	( // 引数
		std::string *pDestStr,		// 置き換えを行う文字列
		const char cRepChar,		// 検出する文字
		const std::string& rRepStr,	// 置き換える文字列
		const int nRepStrLength		// 置き換える文字列の長さ (通常はstringのsize)
	);

	D3DXVECTOR2 CalcPosParabola		// 経過時間・X移動量・重力から放物線の位置を求める処理
	( // 引数
		const float fGravity,		// 重力
		const float fMoveX,			// X移動量
		const float fDestPosX,		// 最大X座標
		const float fDestPosY,		// 最大Y座標
		const float fTime,			// 経過時間
		float *pMaxTime = nullptr,	// 最大経過時間
		float *pMaxPosY = nullptr	// 最大到達Y座標
	);
	D3DXVECTOR2 CalcMoveParabola	// 経過時間・X移動量・重力から放物線の移動量を求める処理
	( // 引数
		const float fGravity,		// 重力
		const float fMoveX,			// X移動量
		const float fDestPosX,		// 最大X座標
		const float fDestPosY,		// 最大Y座標
		const float fTime,			// 経過時間
		float *pMaxTime = nullptr,	// 最大経過時間
		float *pMaxPosY = nullptr	// 最大到達Y座標
	);

	float RandomRot(void);			// ランダム向き取得
	void NormalizeRot(float& rRot);	// 向きの正規化
	void NormalizeRot(D3DXVECTOR3& rRot);			// 三軸向きの正規化
	void PathToBaseName(std::string *pPath);		// パスのベースネーム変換
	void StandardizePathPart(std::string *pPath);	// パス区切りの標準化
	std::string SandString(const std::string &rTop, const std::string &rMain, const std::string &rCur);		// 文字列の左右追加 (マルチバイト文字列)
	std::wstring SandString(const std::wstring &rTop, const std::wstring &rMain, const std::wstring &rCur);	// 文字列の左右追加 (ワイド文字列)
	std::wstring MultiByteToWide(const std::string &rSrcStr);	// マルチバイト文字列のワイド文字列変換
	std::string WideToMultiByte(const std::wstring &rSrcStr);	// ワイド文字列のマルチバイト文字列変換
	void VecToRot(const D3DXVECTOR3& rVec, float *pPhi, float *pTheta);		// ベクトルの向き変換
	void RotToVec(const float fPhi, const float fTheta, D3DXVECTOR3 *pVec);	// 向きのベクトル変換
	float GetTexWidthFromAspect(const float fHeight, const int nTexID);		// 縦幅からアスペクト比を考慮した横幅取得
	float GetTexHeightFromAspect(const float fWidth, const int nTexID);		// 横幅からアスペクト比を考慮した縦幅取得
	D3DXVECTOR3 GetMatrixPosition(const D3DXMATRIX& rMtx);	// マトリックス位置取得
	D3DXVECTOR3 GetMatrixRotation(const D3DXMATRIX& rMtx);	// マトリックス向き取得
	D3DXVECTOR3 GetMatrixScaling(const D3DXMATRIX& rMtx);	// マトリックス拡大率取得

	// テンプレート関数
	template<class T> T *ZeroClear(T *pClear);	// ゼロクリア
	template<class T> bool LimitNum		// 値の範囲内制限
	( // 引数
		T& rNum,		// 制限数値
		const T min,	// 最小範囲
		const T max		// 最大範囲
	);
	template<class T> bool LimitMinNum	// 値の最小値制限
	( // 引数
		T& rNum,		// 制限数値
		const T min		// 最小範囲
	);
	template<class T> bool LimitMaxNum	// 値の最大値制限
	( // 引数
		T& rNum,		// 制限数値
		const T max		// 最大範囲
	);
	template<class T> float ValueToRate	// 値の割合変換
	( // 引数
		const T num,	// 割合化する数値
		const T min,	// 最小範囲
		const T max		// 最大範囲
	);
	template<class T> T RateToValue		// 割合の値変換
	( // 引数
		const float fRate,	// 値化する数値
		const T min,		// 最小範囲
		const T max			// 最大範囲
	);
	template<class T> void SortNum		// 値のソート
	( // 引数
		T *pSortNum,		// ソート配列
		const int nMaxKeep	// 配列サイズ
	);
	template<class T> void Shuffle		// シャッフル
	(
		T *pShuffleData,		// シャッフル配列
		const int nMaxShuffle	// 配列サイズ
	);
}

// イージング関数空間
namespace easeing
{
	// 通常関数
	inline float Liner(const float x)		{ return x; }

	inline float InSine(const float x)		{ return 1.0f - cosf((x * D3DX_PI) * 0.5f); }
	inline float OutSine(const float x)		{ return sinf((x * D3DX_PI) * 0.5f); }
	inline float InOutSine(const float x)	{ return -(cosf(x * D3DX_PI) - 1.0f) * 0.5f; }

	inline float InQuad(const float x)		{ return x * x; }
	inline float OutQuad(const float x)		{ return 1.0f - (1.0f - x) * (1.0f - x); }
	inline float InOutQuad(const float x)	{ return (x < 0.5f) ? (2.0f * x * x) : (1.0f - powf(-2.0f * x + 2.0f, 2.0f) * 0.5f); }

	inline float InCubic(const float x)		{ return x * x * x; }
	inline float OutCubic(const float x)	{ return 1.0f - powf(1.0f - x, 3.0f); }
	inline float InOutCubic(const float x)	{ return (x < 0.5f) ? (4.0f * x * x * x) : (1.0f - powf(-2.0f * x + 2.0f, 3.0f) * 0.5f); }

	inline float InQuart(const float x)		{ return x * x * x * x; }
	inline float OutQuart(const float x)	{ return 1.0f - powf(1.0f - x, 4.0f); }
	inline float InOutQuart(const float x)	{ return (x < 0.5f) ? (8.0f * x * x * x * x) : (1.0f - powf(-2.0f * x + 2.0f, 4.0f) * 0.5f); }

	inline float InQuint(const float x)		{ return x * x * x * x * x; }
	inline float OutQuint(const float x)	{ return 1.0f - powf(1.0f - x, 5.0f); }
	inline float InOutQuint(const float x)	{ return (x < 0.5f) ? (16.0f * x * x * x * x * x) : (1.0f - powf(-2.0f * x + 2.0f, 5.0f) * 0.5f); }

	// テンプレート関数
	template<class T> inline float Liner(T num, const T min, const T max)		{ return Liner(useful::ValueToRate(num, min, max)); }

	template<class T> inline float InSine(T num, const T min, const T max)		{ return InSine(useful::ValueToRate(num, min, max)); }
	template<class T> inline float OutSine(T num, const T min, const T max)		{ return OutSine(useful::ValueToRate(num, min, max)); }
	template<class T> inline float InOutSine(T num, const T min, const T max)	{ return InOutSine(useful::ValueToRate(num, min, max)); }

	template<class T> inline float InQuad(T num, const T min, const T max)		{ return InQuad(useful::ValueToRate(num, min, max)); }
	template<class T> inline float OutQuad(T num, const T min, const T max)		{ return OutQuad(useful::ValueToRate(num, min, max)); }
	template<class T> inline float InOutQuad(T num, const T min, const T max)	{ return InOutQuad(useful::ValueToRate(num, min, max)); }

	template<class T> inline float InCubic(T num, const T min, const T max)		{ return InCubic(useful::ValueToRate(num, min, max)); }
	template<class T> inline float OutCubic(T num, const T min, const T max)	{ return OutCubic(useful::ValueToRate(num, min, max)); }
	template<class T> inline float InOutCubic(T num, const T min, const T max)	{ return InOutCubic(useful::ValueToRate(num, min, max)); }

	template<class T> inline float InQuart(T num, const T min, const T max)		{ return InQuart(useful::ValueToRate(num, min, max)); }
	template<class T> inline float OutQuart(T num, const T min, const T max)	{ return OutQuart(useful::ValueToRate(num, min, max)); }
	template<class T> inline float InOutQuart(T num, const T min, const T max)	{ return InOutQuart(useful::ValueToRate(num, min, max)); }

	template<class T> inline float InQuint(T num, const T min, const T max)		{ return InQuint(useful::ValueToRate(num, min, max)); }
	template<class T> inline float OutQuint(T num, const T min, const T max)	{ return OutQuint(useful::ValueToRate(num, min, max)); }
	template<class T> inline float InOutQuint(T num, const T min, const T max)	{ return InOutQuint(useful::ValueToRate(num, min, max)); }
}

// カラー関数空間
namespace color
{
	inline Color Black(void)				{ return Color(0.0f, 0.0f, 0.0f, 1.0f); }	// 黒色/不透明
	inline Color Black(const float fAlpha)	{ return Color(0.0f, 0.0f, 0.0f, fAlpha); }	// 黒色/透明度
	inline Color White(void)				{ return Color(1.0f, 1.0f, 1.0f, 1.0f); }	// 白色/不透明
	inline Color White(const float fAlpha)	{ return Color(1.0f, 1.0f, 1.0f, fAlpha); }	// 白色/透明度
	inline Color Red(void)					{ return Color(1.0f, 0.0f, 0.0f, 1.0f); }	// 赤色/不透明
	inline Color Red(const float fAlpha)	{ return Color(1.0f, 0.0f, 0.0f, fAlpha); }	// 赤色/透明度
	inline Color Green(void)				{ return Color(0.0f, 1.0f, 0.0f, 1.0f); }	// 緑色/不透明
	inline Color Green(const float fAlpha)	{ return Color(0.0f, 1.0f, 0.0f, fAlpha); }	// 緑色/透明度
	inline Color Blue(void)					{ return Color(0.0f, 0.0f, 1.0f, 1.0f); }	// 青色/不透明
	inline Color Blue(const float fAlpha)	{ return Color(0.0f, 0.0f, 1.0f, fAlpha); }	// 青色/透明度
	inline Color Yellow(void)				{ return Color(1.0f, 1.0f, 0.0f, 1.0f); }	// 黄色/不透明
	inline Color Yellow(const float fAlpha)	{ return Color(1.0f, 1.0f, 0.0f, fAlpha); }	// 黄色/透明度
	inline Color Cyan(void)					{ return Color(0.0f, 1.0f, 1.0f, 1.0f); }	// 水色/不透明
	inline Color Cyan(const float fAlpha)	{ return Color(0.0f, 1.0f, 1.0f, fAlpha); }	// 水色/透明度
	inline Color Purple(void)				{ return Color(1.0f, 0.0f, 1.0f, 1.0f); }	// 紫色/不透明
	inline Color Purple(const float fAlpha)	{ return Color(1.0f, 0.0f, 1.0f, fAlpha); }	// 紫色/透明度

	// カラーコード/不透明
	inline Color Code(const std::string& rCode, const float fAlpha)
	{
		assert((int)rCode.size() == 6);
		int R = std::stoi(rCode.substr(0, 2), nullptr, 16);
		int G = std::stoi(rCode.substr(2, 2), nullptr, 16);
		int B = std::stoi(rCode.substr(4, 2), nullptr, 16);
		Color col = D3DCOLOR_RGBA(R, G, B, (int)(fAlpha * 255.0f));
		return col;
	}

	// カラーコード/透明度
	inline Color Code(const std::string& rCode)
	{
		return Code(rCode, 1.0f);
	}
}

// マテリアル関数空間
namespace material
{
	// 黒色マテリアル取得
	inline D3DXMATERIAL Black(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Black();
		return mat;
	}

	// 白色マテリアル取得
	inline D3DXMATERIAL White(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::White();
		return mat;
	}

	// 赤色マテリアル取得
	inline D3DXMATERIAL Red(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Red();
		return mat;
	}

	// 緑色マテリアル取得
	inline D3DXMATERIAL Green(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Green();
		return mat;
	}

	// 青色マテリアル取得
	inline D3DXMATERIAL Blue(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Blue();
		return mat;
	}

	// 黄色マテリアル取得
	inline D3DXMATERIAL Yellow(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Yellow();
		return mat;
	}

	// 水色マテリアル取得
	inline D3DXMATERIAL Cyan(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Cyan();
		return mat;
	}

	// 紫色マテリアル取得
	inline D3DXMATERIAL Purple(void)
	{
		D3DXMATERIAL mat;
		ZeroMemory(&mat, sizeof(mat));
		mat.MatD3D.Diffuse = color::Purple();
		return mat;
	}
}

//************************************************************
//	テンプレート関数
//************************************************************
//	便利関数空間
//************************************************************
//============================================================
//	ゼロクリア
//============================================================
template<class T> T *useful::ZeroClear(T *pClear)
{
	// 引数情報をゼロクリア
	memset(pClear, 0, sizeof(*pClear));

	// クリア後のアドレスを返す
	return pClear;
}

//============================================================
//	値の範囲内制限処理
//============================================================
template<class T> bool useful::LimitNum
(
	T& rNum,		// 制限数値
	const T min,	// 最小範囲
	const T max		// 最大範囲
)
{
	if (rNum < min)
	{ // 制限数値が最小範囲を超えていた場合

		// 範囲内に補正
		rNum = min;

		// 真を返す
		return true;
	}
	else if (rNum > max)
	{ // 制限数値が最大範囲を超えていた場合

		// 範囲内に補正
		rNum = max;

		// 真を返す
		return true;
	}

	// 偽を返す
	return false;
}

//============================================================
//	値の最小値制限処理
//============================================================
template<class T> bool useful::LimitMinNum
(
	T& rNum,	// 制限数値
	const T min	// 最小範囲
)
{
	if (rNum < min)
	{ // 制限数値が最小範囲を超えていた場合

		// 範囲内に補正
		rNum = min;

		// 真を返す
		return true;
	}

	// 偽を返す
	return false;
}

//============================================================
//	値の最大値制限処理
//============================================================
template<class T> bool useful::LimitMaxNum
(
	T& rNum,	// 制限数値
	const T max	// 最大範囲
)
{
	if (rNum > max)
	{ // 制限数値が最大範囲を超えていた場合

		// 範囲内に補正
		rNum = max;

		// 真を返す
		return true;
	}

	// 偽を返す
	return false;
}

//============================================================
//	値の割合変換
//============================================================
template<class T> float useful::ValueToRate
(
	const T num,	// 割合化する数値
	const T min,	// 最小範囲
	const T max		// 最大範囲
)
{
	// 割る数を求める
	float fDiv = static_cast<float>(max) - static_cast<float>(min);
	if (fDiv == 0.0f) { return 0.0f; }	// 0除算対策

	// 割合変換した値を返す
	return (static_cast<float>(num) - static_cast<float>(min)) / fDiv;
}

//============================================================
//	割合の値変換
//============================================================
template<class T> T useful::RateToValue
(
	const float fRate,	// 値化する数値
	const T min,		// 最小範囲
	const T max			// 最大範囲
)
{
	// 値変換した割合を返す
	return static_cast<T>((fRate * (max - min)) + min);
}

//============================================================
//	ソート処理
//============================================================
template<class T> void useful::SortNum
(
	T *pSortNum,		// ソート配列
	const int nMaxKeep	// 配列サイズ
)
{
	// 変数を宣言
	T	keepNum;		// ソート用
	int	nCurrentMaxID;	// 最大値のインデックス

	for (int nCntKeep = 0; nCntKeep < (nMaxKeep - 1); nCntKeep++)
	{ // 入れ替える値の総数 -1回分繰り返す

		// 現在の繰り返し数を代入 (要素1とする)
		nCurrentMaxID = nCntKeep;

		for (int nCntSort = nCntKeep + 1; nCntSort < nMaxKeep; nCntSort++)
		{ // 入れ替える値の総数 -nCntKeep分繰り返す

			if (pSortNum[nCurrentMaxID] < pSortNum[nCntSort])
			{ // 最大値に設定されている値より、現在の値のほうが大きい場合

				// 現在の要素番号を最大値に設定
				nCurrentMaxID = nCntSort;
			}
		}

		if (nCntKeep != nCurrentMaxID)
		{ // 最大値の要素番号に変動があった場合

			// 要素の入れ替え
			keepNum					= pSortNum[nCntKeep];
			pSortNum[nCntKeep]		= pSortNum[nCurrentMaxID];
			pSortNum[nCurrentMaxID]	= keepNum;
		}
	}
}

//============================================================
//	シャッフル処理
//============================================================
template<class T> void useful::Shuffle
(
	T *pShuffleData,		// シャッフル配列
	const int nMaxShuffle	// 配列サイズ
)
{
	for (int nCntShu = nMaxShuffle - 1; nCntShu > 0; nCntShu--)
	{ // 引数の総数分繰り返す

		// 変数を宣言
		T swap;		// 要素の入れ替え用
		int nRandom = rand() % nCntShu;	// 要素を入れ替えるインデックス

		// 要素の入れ替え
		swap					= pShuffleData[nRandom];
		pShuffleData[nRandom]	= pShuffleData[nCntShu];
		pShuffleData[nCntShu]	= swap;
	}
}

#endif	// _USEFUL_H_
