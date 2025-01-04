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
#include "menuManager.h"
#include "pause.h"
#include "stage.h"
#include "player.h"

// TODO
#include "frame2D.h"
#include "loadtext.h"
#include "frame2DModule.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CGameManager* CSceneGame::m_pGameManager = nullptr;	// �Q�[���}�l�[�W���[
CPause* CSceneGame::m_pPause = nullptr;	// �|�[�Y���
CStage* CSceneGame::m_pStage = nullptr;	// �X�e�[�W���

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
HRESULT CSceneGame::Init()
{
	//--------------------------------------------------------
	//	��������
	//--------------------------------------------------------
	// �V�[���̏�����
	if (FAILED(CScene::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �Q�[���}�l�[�W���[�̐���
	m_pGameManager = CGameManager::Create();
	if (m_pGameManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �|�[�Y�̐���
	m_pPause = CPause::Create();
	if (m_pPause == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// ���j���[�}�l�[�W���[�̐���
	if (CMenuManager::Create() == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

#if 1
	// TODO�F�v���C���[�̐���
	if (CPlayer::Create(VECTOR3(0.0f, 0.0f, -1.0f)) == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}
#endif

	// �X�e�[�W�̐���
	m_pStage = CStage::Create();
	if (m_pStage == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �Ǐ]�J�����ɂ���
	CCamera* pCamera = GET_MANAGER->GetCamera();	// �J�������
	pCamera->SetState(CCamera::STATE_FOLLOW);		// �Ǐ]��Ԃ�ݒ�

	// BGM�̍Đ�
	PLAY_SOUND(CSound::LABEL_BGM_GENERAL);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSceneGame::Uninit()
{
	// �Q�[���}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pGameManager);

	// ���j���[�}�l�[�W���[�̔j��
	CMenuManager::GetInstance()->Release();

	// �|�[�Y�̔j��
	SAFE_REF_RELEASE(m_pPause);

	// �X�e�[�W�̔j��
	SAFE_REF_RELEASE(m_pStage);

	// �V�[���̏I��
	CScene::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSceneGame::Update(const float fDeltaTime)
{
	// �t�F�[�h���̏ꍇ������
	if (GET_MANAGER->GetFade()->IsFade()) { return; }

	// �Q�[���}�l�[�W���[�̍X�V
	assert(m_pGameManager != nullptr);
	m_pGameManager->Update(fDeltaTime);

	// ���j���[�}�l�[�W���[�̍X�V
	CMenuManager::GetInstance()->Update(fDeltaTime);

	if (m_pGameManager->GetState() == CGameManager::STATE_NORMAL)
	{ // �Q�[�����ʏ��Ԃ̏ꍇ

		// �|�[�Y�̍X�V
		assert(m_pPause != nullptr);
		m_pPause->Update(fDeltaTime);
	}

	if (!m_pPause->IsPause())
	{ // �|�[�Y���ł͂Ȃ��ꍇ

		// �V�[���̍X�V
		CScene::Update(fDeltaTime);
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
#if 1
	if (GET_INPUTKEY->IsTrigger(DIK_0))
	{
		CFrame2D* pFrame = CFrame2D::Create(CFrame2D::PRESET_DOWN);
		pFrame->ChangeModule(new CFrame2DModuleText);
		pFrame->GetModule()->GetModuleText()->BindTextBox
		(
			"data\\TXT\\���؃e�L�X�g.txt",
			"0"
		);
	}
#endif
}

//============================================================
//	�Q�[���}�l�[�W���[�擾����
//============================================================
CGameManager* CSceneGame::GetGameManager()
{
	// �C���X�^���X���g�p
	assert(m_pGameManager != nullptr);

	// �Q�[���}�l�[�W���[�̃|�C���^��Ԃ�
	return m_pGameManager;
}

//============================================================
//	�|�[�Y�擾����
//============================================================
CPause* CSceneGame::GetPause()
{
	// �C���X�^���X���g�p
	assert(m_pPause != nullptr);

	// �|�[�Y�̃|�C���^��Ԃ�
	return m_pPause;
}

//============================================================
//	�X�e�[�W�擾����
//============================================================
CStage* CSceneGame::GetStage()
{
	// �C���X�^���X���g�p
	assert(m_pStage != nullptr);

	// �X�e�[�W�̃|�C���^��Ԃ�
	return m_pStage;
}

//============================================================
//	�v���C���[�擾����
//============================================================
CPlayer* CSceneGame::GetPlayer()
{
	CListManager<CPlayer>* pListManager = CPlayer::GetList();	// �v���C���[���X�g�}�l�[�W���[
	if (pListManager == nullptr)		{ return nullptr; }		// ���X�g���g�p�̏ꍇ������
	if (pListManager->GetNumAll() != 1)	{ return nullptr; }		// �v���C���[��1�l�ł͂Ȃ��ꍇ������
	CPlayer* pPlayer = pListManager->GetList().front();			// �v���C���[���

	// �C���X�^���X���g�p
	assert(pPlayer != nullptr);

	// �v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}
