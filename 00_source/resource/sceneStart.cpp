//============================================================
//
//	�X�^�[�g��ʏ��� [sceneStart.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "sceneStart.h"
#include "manager.h"
#include "texture.h"
#include "sound.h"
#include "camera.h"
#include "startManager.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CStartManager* CSceneStart::m_pStartManager = nullptr;	// �X�^�[�g�}�l�[�W���[

//************************************************************
//	�q�N���X [CSceneStart] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSceneStart::CSceneStart(const EMode mode) : CScene(mode)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CSceneStart::~CSceneStart()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSceneStart::Init()
{
	// �V�[���̏�����
	if (FAILED(CScene::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �X�^�[�g�}�l�[�W���[�̐���
	m_pStartManager = CStartManager::Create();
	if (m_pStartManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �Œ�J�����ɂ���
	CCamera* pCamera = GET_MANAGER->GetCamera();	// �J�������
	pCamera->SetState(CCamera::STATE_NONE);			// �Œ��Ԃ�ݒ�

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSceneStart::Uninit()
{
	// �X�^�[�g�}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pStartManager);

	// �V�[���̏I��
	CScene::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSceneStart::Update(const float fDeltaTime)
{
	// �X�^�[�g�}�l�[�W���[�̍X�V
	assert(m_pStartManager != nullptr);
	m_pStartManager->Update(fDeltaTime);

	// �V�[���̍X�V
	CScene::Update(fDeltaTime);
}

//============================================================
//	�X�^�[�g�}�l�[�W���[�擾����
//============================================================
CStartManager* CSceneStart::GetStartManager()
{
	// �C���X�^���X���g�p
	assert(m_pStartManager != nullptr);

	// �X�^�[�g�}�l�[�W���[��Ԃ�
	return m_pStartManager;
}
