//============================================================
//
//	�Q�[����ʏ��� [sceneGame.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "sceneGame.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"

#include "gameManager.h"
#include "pause.h"
#include "hitStop.h"

// TODO
#include "mapTile.h"
#include "objectChara2D.h"

// TODO
CObjectChara2D *g_pChara;

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CGameManager	*CSceneGame::m_pGameManager	= nullptr;	// �Q�[���}�l�[�W���[
CPause			*CSceneGame::m_pPause		= nullptr;	// �|�[�Y
CHitStop		*CSceneGame::m_pHitStop		= nullptr;	// �q�b�g�X�g�b�v

//************************************************************
//	�q�N���X [CSceneGame] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSceneGame::CSceneGame(const EMode mode) : CScene(mode)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CSceneGame::~CSceneGame()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSceneGame::Init(void)
{
	//--------------------------------------------------------
	//	��������
	//--------------------------------------------------------
	// �V�[���̏�����
	if (FAILED(CScene::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �Q�[���}�l�[�W���[�̐���
	m_pGameManager = CGameManager::Create();
	if (m_pGameManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �|�[�Y�̐���
	m_pPause = CPause::Create();
	if (m_pPause == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �q�b�g�X�g�b�v�̐���
	m_pHitStop = CHitStop::Create();
	if (m_pHitStop == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	�����ݒ�
	//--------------------------------------------------------
	// TODO
	CMapTile::Create(CMapTile::TYPE_FALL_POINT, VEC3_ZERO);

	// TODO
	g_pChara = CObjectChara2D::Create(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	g_pChara->SetLabel(CObject::LABEL_DEBUG);
	g_pChara->BindCharaData("data\\CHARACTER\\frisk.txt");
	g_pChara->SetMotion(0);

	// BGM�̍Đ�
	PLAY_SOUND(CSound::LABEL_BGM_GENERAL);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSceneGame::Uninit(void)
{
	// �Q�[���}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pGameManager);

	// �|�[�Y�̔j��
	SAFE_REF_RELEASE(m_pPause);

	// �q�b�g�X�g�b�v�̔j��
	SAFE_REF_RELEASE(m_pHitStop);

	// �V�[���̏I��
	CScene::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSceneGame::Update(const float fDeltaTime)
{
	// �Q�[���}�l�[�W���[�̍X�V
	assert(m_pGameManager != nullptr);
	m_pGameManager->Update(fDeltaTime);

	// �q�b�g�X�g�b�v�̍X�V
	assert(m_pHitStop != nullptr);
	m_pHitStop->Update(fDeltaTime);

	if (m_pGameManager->GetState() == CGameManager::STATE_NORMAL && !m_pHitStop->IsStop())
	{ // �Q�[�����ʏ��Ԃ̏ꍇ

		// �|�[�Y�̍X�V
		assert(m_pPause != nullptr);
		m_pPause->Update(fDeltaTime);
	}

	if (!m_pPause->IsPause()
	&&  !m_pHitStop->IsStop())
	{ // �|�[�Y���E�q�b�g�X�g�b�v���ł͂Ȃ��ꍇ

		// �V�[���̍X�V
		CScene::Update(fDeltaTime);
	}
	else if (m_pHitStop->IsStop())
	{ // �q�b�g�X�g�b�v���̏ꍇ

		// �J�����̍X�V
		GET_MANAGER->GetCamera()->Update(fDeltaTime);
	}

#ifdef _DEBUG

	else
	{ // �|�[�Y���̏ꍇ

		if (GET_MANAGER->GetCamera()->GetState() == CCamera::STATE_CONTROL)
		{ // �J�����������Ԃ̏ꍇ

			// �J�����̍X�V
			GET_MANAGER->GetCamera()->Update(fDeltaTime);
		}
	}

#endif	// _DEBUG

	// TODO
	D3DXVECTOR3 posChara = g_pChara->GetVec3Position();
	if (GET_INPUTKEY->IsPress(DIK_LEFT))
	{
		posChara.x -= 180.0f * fDeltaTime;

		if (g_pChara->GetMotion() != 2)
		g_pChara->SetMotion(2);
	}
	if (GET_INPUTKEY->IsPress(DIK_RIGHT))
	{
		posChara.x += 180.0f * fDeltaTime;

		if (g_pChara->GetMotion() != 3)
		g_pChara->SetMotion(3);
	}
	if (GET_INPUTKEY->IsPress(DIK_UP))
	{
		posChara.y += 180.0f * fDeltaTime;

		if (g_pChara->GetMotion() != 0)
		g_pChara->SetMotion(0);
	}
	if (GET_INPUTKEY->IsPress(DIK_DOWN))
	{
		posChara.y -= 180.0f * fDeltaTime;

		if (g_pChara->GetMotion() != 1)
		g_pChara->SetMotion(1);
	}
	g_pChara->SetVec3Position(posChara);
}

//============================================================
//	�Q�[���}�l�[�W���[�擾����
//============================================================
CGameManager *CSceneGame::GetGameManager(void)
{
	// �C���X�^���X���g�p
	assert(m_pGameManager != nullptr);

	// �Q�[���}�l�[�W���[�̃|�C���^��Ԃ�
	return m_pGameManager;
}

//============================================================
//	�|�[�Y�擾����
//============================================================
CPause *CSceneGame::GetPause(void)
{
	// �C���X�^���X���g�p
	assert(m_pPause != nullptr);

	// �|�[�Y�̃|�C���^��Ԃ�
	return m_pPause;
}

//============================================================
//	�q�b�g�X�g�b�v�擾����
//============================================================
CHitStop *CSceneGame::GetHitStop(void)
{
	// �C���X�^���X���g�p
	assert(m_pHitStop != nullptr);

	// �q�b�g�X�g�b�v�̃|�C���^��Ԃ�
	return m_pHitStop;
}
