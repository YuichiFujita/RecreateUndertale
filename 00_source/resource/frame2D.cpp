//============================================================
//
//	フレーム2D処理 [frame2D.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "frame2D.h"
#include "frame2DModule.h"
#include "object2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const VECTOR3 FRAME_POS[] =		// フレーム位置プリセット
	{
		VECTOR3(SCREEN_CENT.x, SCREEN_CENT.y, 0.0f)	// 下部配置
	};
	const VECTOR3 FRAME_ROT[] =		// フレーム向きプリセット
	{
		VEC3_ZERO	// 下部配置
	};
	const VECTOR3 FRAME_SIZE[] =	// フレーム大きさプリセット
	{
		VECTOR3(850.0f, 210.0f, 0.0f)	// 下部配置
	};
	const COLOR	COL_FRAME[]	= { color::White(), color::Black() };	// フレーム色
	const int	PRIORITY	= 6;		// フレーム2Dの優先順位
	const float	BORD_THICK	= 18.0f;	// 縁取り太さ
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(FRAME_POS)  == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");
static_assert(NUM_ARRAY(FRAME_ROT)  == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");
static_assert(NUM_ARRAY(FRAME_SIZE) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	子クラス [CFrame2D] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFrame2D::CFrame2D() : CObject(LABEL_UI, DIM_2D, PRIORITY),
	m_pModule	(nullptr),		// 機能
	m_pos		(VEC3_ZERO),	// 位置
	m_rot		(VEC3_ZERO),	// 向き
	m_size		(VEC3_ZERO),	// 大きさ
	m_preset	(PRESET_NONE)	// 配置プリセット
{
	// メンバ変数をクリア
	memset(&m_apFrame[0], 0, sizeof(m_apFrame));	// フレーム情報
}

//============================================================
//	デストラクタ
//============================================================
CFrame2D::~CFrame2D()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFrame2D::Init()
{
	// メンバ変数を初期化
	memset(&m_apFrame[0], 0, sizeof(m_apFrame));	// フレーム情報
	m_pModule	= nullptr;		// 機能
	m_pos		= VEC3_ZERO;	// 位置
	m_rot		= VEC3_ZERO;	// 向き
	m_size		= VEC3_ZERO;	// 大きさ
	m_preset	= PRESET_NONE;	// 配置プリセット

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの生成
		m_apFrame[i] = CObject2D::Create(VEC3_ZERO);
		if (m_apFrame[i] == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}

		// 色を設定
		m_apFrame[i]->SetColor(COL_FRAME[i]);

		// 自動更新・自動描画をOFFにする
		m_apFrame[i]->SetEnableUpdate(false);
		m_apFrame[i]->SetEnableDraw(false);
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFrame2D::Uninit()
{
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの終了
		SAFE_UNINIT(m_apFrame[i]);
	}

	// 機能の終了
	SAFE_UNINIT(m_pModule);

	// オブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CFrame2D::Update(const float fDeltaTime)
{
	// TODO
#if 1
	static float fOffsetRot = 0.0f;
	static float fRot = 0.0f;

	// 加算
	fOffsetRot	+= 0.01f;
	fRot		+= 0.01f;

	// 補正
	useful::NormalizeRot(fOffsetRot);
	useful::NormalizeRot(fRot);

	// 位置ずらす
	VECTOR3 pos = m_originPos;
	pos.x += sinf(fOffsetRot) * 300.0f;
	pos.y += cosf(fOffsetRot) * 300.0f;
	SetVec3Position(pos);

	// 向きずらす
	SetVec3Rotation(VECTOR3(0.0f, 0.0f, fRot));
#endif

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの更新
		m_apFrame[i]->Update(fDeltaTime);
	}

	if (m_pModule != nullptr)
	{ // 機能が割り当てられている場合

		// 機能の更新
		m_pModule->Update(fDeltaTime);
	}
}

//============================================================
//	描画処理
//============================================================
void CFrame2D::Draw(CShader* pShader)
{
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの描画
		m_apFrame[i]->Draw(pShader);
	}
}

//============================================================
//	優先順位の設定処理
//============================================================
void CFrame2D::SetPriority(const int nPriority)
{
	// 自身の優先順位を設定
	CObject::SetPriority(nPriority);

	if (m_pModule != nullptr)
	{ // 機能が割り当てられている場合

		// 機能の優先順位を設定
		m_pModule->SetPriority(nPriority);
	}

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの優先順位を設定
		m_apFrame[i]->SetPriority(nPriority);
	}
}

//============================================================
//	位置の設定処理
//============================================================
void CFrame2D::SetVec3Position(const VECTOR3& rPos)
{
	// 自身の位置を設定
	m_pos = rPos;

	if (m_pModule != nullptr)
	{ // 機能が割り当てられている場合

		// 機能の位置を設定
		m_pModule->SetVec3Position(rPos);
	}

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの位置を設定
		m_apFrame[i]->SetVec3Position(rPos);
	}
}

//============================================================
//	向きの設定処理
//============================================================
void CFrame2D::SetVec3Rotation(const VECTOR3& rRot)
{
	// 自身の向きを設定
	m_rot = rRot;

	// 向きの正規化
	useful::NormalizeRot(m_rot);

	if (m_pModule != nullptr)
	{ // 機能が割り当てられている場合

		// 機能の向きを設定
		m_pModule->SetVec3Rotation(rRot);
	}

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの向きを設定
		m_apFrame[i]->SetVec3Rotation(rRot);
	}
}

//============================================================
//	大きさの設定処理
//============================================================
void CFrame2D::SetVec3Size(const VECTOR3& rSize)
{
	// 配置プリセットの初期化
	m_preset = PRESET_NONE;

	// 自身の大きさを設定
	m_size = rSize;

	if (m_pModule != nullptr)
	{ // 機能が割り当てられている場合

		// 機能の大きさを設定
		m_pModule->SetVec3Size(rSize);
	}

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // ポリゴンの総数分繰り返す

		// フレームの大きさを設定
		VECTOR3 bord = VECTOR3(BORD_THICK, BORD_THICK, 0.0f);	// 縁取り太さ
		float fCalcScale = (-1.0f * (i - 1));					// 大きさ調整値
		m_apFrame[i]->SetVec3Size(rSize + fCalcScale * bord);	// 大きさ設定
	}
}

//============================================================
//	生成処理 (配置プリセット)
//============================================================
CFrame2D* CFrame2D::Create(const EPreset preset)
{
	// プリセット範囲外エラー
	assert(preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX);

	// フレーム2Dの生成
	CFrame2D* pFrame2D = CFrame2D::Create
	( // 引数
		FRAME_POS[preset],	// 位置
		FRAME_ROT[preset],	// 向き
		FRAME_SIZE[preset]	// 大きさ
	);
	if (pFrame2D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}

	// 配置プリセットの初期化
	pFrame2D->m_preset = preset;

	// 確保したアドレスを返す
	return pFrame2D;
}

//============================================================
//	生成処理 (配置指定)
//============================================================
CFrame2D* CFrame2D::Create
(
	const VECTOR3& rPos,	// 位置
	const VECTOR3& rRot,	// 向き
	const VECTOR3& rSize	// 大きさ
)
{
	// フレーム2Dの生成
	CFrame2D* pFrame2D = new CFrame2D;
	if (pFrame2D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// フレーム2Dの初期化
		if (FAILED(pFrame2D->Init()))
		{ // 初期化に失敗した場合

			// フレーム2Dの破棄
			SAFE_DELETE(pFrame2D);
			return nullptr;
		}

		// 位置を設定
		pFrame2D->SetVec3Position(rPos);
		pFrame2D->m_originPos = rPos;

		// 向きを設定
		pFrame2D->SetVec3Rotation(rRot);

		// 大きさを設定
		pFrame2D->SetVec3Size(rSize);

		// 確保したアドレスを返す
		return pFrame2D;
	}
}

//============================================================
//	機能の変更処理
//============================================================
HRESULT CFrame2D::ChangeModule(CFrame2DModule* pModule)
{
	// 機能の生成に失敗している場合抜ける
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// 機能インスタンスを終了
	SAFE_UNINIT(m_pModule);

	// 機能インスタンスを変更
	assert(m_pModule == nullptr);
	m_pModule = pModule;

	// 機能にコンテキストを設定
	m_pModule->SetContext(this);

	// 機能インスタンスを初期化
	if (FAILED(m_pModule->Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	配置プリセットの設定処理
//============================================================
void CFrame2D::SetPreset(const EPreset preset)
{
	// 位置を設定
	SetVec3Position(FRAME_POS[preset]);

	// 向きを設定
	SetVec3Rotation(FRAME_ROT[preset]);

	// 大きさを設定
	SetVec3Size(FRAME_SIZE[preset]);

	// 配置プリセットの保存
	m_preset = preset;
}
