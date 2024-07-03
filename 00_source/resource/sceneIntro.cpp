//============================================================
//
//	�C���g����ʏ��� [sceneIntro.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "sceneIntro.h"
#include "manager.h"
#include "texture.h"
#include "sound.h"
#include "camera.h"
#include "introManager.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CIntroManager *CSceneIntro::m_pIntroManager = nullptr;	// �C���g���}�l�[�W���[

//************************************************************
//	�q�N���X [CSceneIntro] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSceneIntro::CSceneIntro(const EMode mode) : CScene(mode)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CSceneIntro::~CSceneIntro()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSceneIntro::Init(void)
{
	// �V�[���̏�����
	if (FAILED(CScene::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �C���g���}�l�[�W���[�̐���
	m_pIntroManager = CIntroManager::Create();
	if (m_pIntroManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �Œ�J�����ɂ���
	CCamera *pCamera = GET_MANAGER->GetCamera();	// �J�������
	pCamera->SetState(CCamera::STATE_NONE);			// �Œ��Ԃ�ݒ�

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSceneIntro::Uninit(void)
{
	// �C���g���}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pIntroManager);

	// �V�[���̏I��
	CScene::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSceneIntro::Update(const float fDeltaTime)
{
	// �C���g���}�l�[�W���[�̍X�V
	assert(m_pIntroManager != nullptr);
	m_pIntroManager->Update(fDeltaTime);

	// �V�[���̍X�V
	CScene::Update(fDeltaTime);
}

//============================================================
//	�C���g���}�l�[�W���[�擾����
//============================================================
CIntroManager *CSceneIntro::GetIntroManager(void)
{
	// �C���X�^���X���g�p
	assert(m_pIntroManager != nullptr);

	// �C���g���}�l�[�W���[��Ԃ�
	return m_pIntroManager;
}
