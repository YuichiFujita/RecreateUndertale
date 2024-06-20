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
#include "timerUI.h"
#include "cinemaScope.h"
#include "pause.h"
#include "hitStop.h"
#include "flash.h"
#include "stage.h"
#include "player.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	namespace timerInfo
	{
		const float TIME_START = 0.0f;		// �J�n����
		const float TIME_LIMIT = 180.0f;	// ��������
		const D3DXVECTOR3 POS		 = D3DXVECTOR3(1100.0f, 43.5f, 0.0f);	// �^�C�}�[�ʒu
		const D3DXVECTOR3 OFFSET	 = D3DXVECTOR3(146.0f, 13.0f, 0.0f);	// �^�C�}�[�w�i�I�t�Z�b�g
		const D3DXVECTOR3 VAL_SIZE	 = D3DXVECTOR3(46.8f, 62.4f, 0.0f);		// �^�C�}�[�����傫��
		const D3DXVECTOR3 PART_SIZE	 = D3DXVECTOR3(27.3f, 62.4f, 0.0f);		// �^�C�}�[��؂�傫��
		const D3DXVECTOR3 BG_SIZE	 = D3DXVECTOR3(397.5f, 33.5f, 0.0f);	// �^�C�}�[�w�i�傫��
		const D3DXVECTOR3 VAL_SPACE	 = D3DXVECTOR3(VAL_SIZE.x * 0.85f, 0.0f, 0.0f);		// �^�C�}�[������
		const D3DXVECTOR3 PART_SPACE = D3DXVECTOR3(PART_SIZE.x * 0.85f, 0.0f, 0.0f);	// �^�C�}�[��؂��
	}
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CGameManager	*CSceneGame::m_pGameManager	= nullptr;	// �Q�[���}�l�[�W���[
CTimerUI		*CSceneGame::m_pTimerUI		= nullptr;	// �^�C�}�[UI
CCinemaScope	*CSceneGame::m_pCinemaScope	= nullptr;	// �V�l�}�X�R�[�v
CPause			*CSceneGame::m_pPause		= nullptr;	// �|�[�Y
CHitStop		*CSceneGame::m_pHitStop		= nullptr;	// �q�b�g�X�g�b�v
CFlash			*CSceneGame::m_pFlash		= nullptr;	// �t���b�V��

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
	CScene::Init();	// �X�e�[�W�E�v���C���[�̐���

	// �^�C�}�[UI�̐���
	m_pTimerUI = CTimerUI::Create
	( // ����
		timerInfo::TIME_START,	// �J�n����
		timerInfo::TIME_LIMIT,	// ��������
		timerInfo::POS,			// �ʒu
		timerInfo::VAL_SIZE,	// �����̑傫��
		timerInfo::PART_SIZE,	// ��؂�̑傫��
		timerInfo::VAL_SPACE,	// �����̋�
		timerInfo::PART_SPACE	// ��؂�̋�
	);
	if (m_pTimerUI == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	m_pTimerUI->Start();

	// �V�l�}�X�R�[�v�̐���
	m_pCinemaScope = CCinemaScope::Create();
	if (m_pCinemaScope == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �|�[�Y�̐���
	m_pPause = CPause::Create();
	if (m_pPause == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �q�b�g�X�g�b�v�̐���
	m_pHitStop = CHitStop::Create();
	if (m_pHitStop == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �t���b�V���̐���
	m_pFlash = CFlash::Create();
	if (m_pFlash == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �Q�[���}�l�[�W���[�̐���
	m_pGameManager = CGameManager::Create();
	if (m_pGameManager == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	�����ݒ�
	//--------------------------------------------------------
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

	// �^�C�}�[UI�̏I��
	SAFE_UNINIT(m_pTimerUI);

	// �V�l�}�X�R�[�v�̔j��
	SAFE_REF_RELEASE(m_pCinemaScope);

	// �|�[�Y�̔j��
	SAFE_REF_RELEASE(m_pPause);

	// �q�b�g�X�g�b�v�̔j��
	SAFE_REF_RELEASE(m_pHitStop);

	// �t���b�V���̔j��
	SAFE_REF_RELEASE(m_pFlash);

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

	// �t���b�V���̍X�V
	assert(m_pFlash != nullptr);
	m_pFlash->Update(fDeltaTime);

	if (m_pGameManager->GetState() == CGameManager::STATE_NORMAL && !m_pHitStop->IsStop())
	{ // �Q�[�����ʏ��Ԃ̏ꍇ

		// �|�[�Y�̍X�V
		assert(m_pPause != nullptr);
		m_pPause->Update(fDeltaTime);
	}

	if (!m_pPause->IsPause()
	&&  !m_pHitStop->IsStop())
	{ // �|�[�Y���E�q�b�g�X�g�b�v���ł͂Ȃ��ꍇ

		// �V�l�}�X�R�[�v�̍X�V
		assert(m_pCinemaScope != nullptr);
		m_pCinemaScope->Update(fDeltaTime);

		// �V�[���̍X�V
		CScene::Update(fDeltaTime);
	}
	else if (m_pHitStop->IsStop())
	{ // �q�b�g�X�g�b�v���̏ꍇ

		// �V�l�}�X�R�[�v�̍X�V
		assert(m_pCinemaScope != nullptr);
		m_pCinemaScope->Update(fDeltaTime);

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
//	�^�C�}�[UI�擾����
//============================================================
CTimerUI *CSceneGame::GetTimerUI(void)
{
	// �C���X�^���X���g�p
	assert(m_pTimerUI != nullptr);

	// �^�C�}�[UI�̃|�C���^��Ԃ�
	return m_pTimerUI;
}

//============================================================
//	�V�l�}�X�R�[�v�擾����
//============================================================
CCinemaScope *CSceneGame::GetCinemaScope(void)
{
	// �C���X�^���X���g�p
	assert(m_pCinemaScope != nullptr);

	// �V�l�}�X�R�[�v�̃|�C���^��Ԃ�
	return m_pCinemaScope;
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

//============================================================
//	�t���b�V���擾����
//============================================================
CFlash *CSceneGame::GetFlash(void)
{
	// �C���X�^���X���g�p
	assert(m_pFlash != nullptr);

	// �t���b�V���̃|�C���^��Ԃ�
	return m_pFlash;
}
