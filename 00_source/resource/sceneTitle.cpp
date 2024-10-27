//============================================================
//
//	�^�C�g����ʏ��� [sceneTitle.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "sceneTitle.h"
#include "manager.h"
#include "texture.h"
#include "sound.h"
#include "camera.h"
#include "titleManager.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CTitleManager* CSceneTitle::m_pTitleManager = nullptr;	// �^�C�g���}�l�[�W���[

//************************************************************
//	�q�N���X [CSceneTitle] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSceneTitle::CSceneTitle(const EMode mode) : CScene(mode)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CSceneTitle::~CSceneTitle()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSceneTitle::Init()
{
	// �V�[���̏�����
	if (FAILED(CScene::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �^�C�g���}�l�[�W���[�̐���
	m_pTitleManager = CTitleManager::Create();
	if (m_pTitleManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �Œ�J�����ɂ���
	CCamera* pCamera = GET_MANAGER->GetCamera();	// �J�������
	pCamera->SetState(CCamera::STATE_NONE);			// �Œ��Ԃ�ݒ�

	// BGM�̍Đ�
	PLAY_SOUND(CSound::LABEL_BGM_GENERAL);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSceneTitle::Uninit()
{
	// �^�C�g���}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pTitleManager);

	// �V�[���̏I��
	CScene::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSceneTitle::Update(const float fDeltaTime)
{
	// �^�C�g���}�l�[�W���[�̍X�V
	assert(m_pTitleManager != nullptr);
	m_pTitleManager->Update(fDeltaTime);

	// �V�[���̍X�V
	CScene::Update(fDeltaTime);
}

//============================================================
//	�^�C�g���}�l�[�W���[�擾����
//============================================================
CTitleManager* CSceneTitle::GetTitleManager()
{
	// �C���X�^���X���g�p
	assert(m_pTitleManager != nullptr);

	// �^�C�g���}�l�[�W���[��Ԃ�
	return m_pTitleManager;
}
