//============================================================
//
//	フレームテキスト2Dヘッダー [frameText2D.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FRAME_TEXT2D_H_
#define _FRAME_TEXT2D_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2D.h"
#include "scrollText2D.h"

//************************************************************
//	クラス定義
//************************************************************
// フレームテキスト2Dクラス
class CFrameText2D : public CFrame2D
{
public:
	// コンストラクタ
	CFrameText2D();

	// デストラクタ
	~CFrameText2D() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CFrameText2D* Create	// 生成
	( // 引数
		const VECTOR3& rPos,	// 位置
		const VECTOR3& rRot,	// 向き
		const VECTOR3& rSize	// 大きさ
	);

	// メンバ関数
	void ChangeText(const AText& rText);	// テキスト変更
	inline HRESULT PushFrontString(const std::string& rStr)		{ return m_pText->PushFrontString(rStr); }	// 文字列の先頭追加 (マルチバイト文字列)
	inline HRESULT PushFrontString(const std::wstring& rStr)	{ return m_pText->PushFrontString(rStr); }	// 文字列の先頭追加 (ワイド文字列)
	inline HRESULT PushBackString(const std::string& rStr)		{ return m_pText->PushBackString(rStr); }	// 文字列の最後尾追加 (マルチバイト文字列)
	inline HRESULT PushBackString(const std::wstring& rStr)		{ return m_pText->PushBackString(rStr); }	// 文字列の最後尾追加 (ワイド文字列)
	inline void DeleteString(const int nStrIdx)		{ m_pText->DeleteString(nStrIdx); }	// 文字列削除
	inline void DeleteStringAll()					{ m_pText->DeleteStringAll(); }		// 文字列全削除
	inline void SetTextEnableDraw(const bool bDraw)	{ m_pText->SetEnableDraw(bDraw); };	// 描画状況設定
	inline bool IsTextScroll() const				{ return m_pText->IsScroll(); }		// 文字送り状況取得

private:
	// メンバ変数
	CScrollText2D* m_pText;	// テキスト情報
};

#endif	// _FRAME_TEXT2D_H_
