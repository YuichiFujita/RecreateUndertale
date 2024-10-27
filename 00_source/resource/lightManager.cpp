//============================================================
//
//	���C�g�}�l�[�W���[���� [lightManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "lightManager.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const COLOR DIFFUSE[] =	// �ݒ�p�g�U���J���[
	{
		COLOR(1.0f, 1.0f, 1.0f, 1.0f),
		COLOR(0.7f, 0.7f, 0.7f, 1.0f),
		COLOR(0.6f, 0.6f, 0.6f, 1.0f),
		COLOR(0.4f, 0.4f, 0.4f, 1.0f),
	};

	const VECTOR3 DIRECTION[] =	// �ݒ�p�����x�N�g��
	{
		VECTOR3( 0.22f, -0.97f,  0.54f),
		VECTOR3(-0.38f,  0.78f, -0.54f),
		VECTOR3( 0.89f, -0.21f,  0.44f),
		VECTOR3(-0.96f,  0.15f, -0.44f),
	};
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(DIFFUSE)   == CLightManager::MAX_NUM, "ERROR : Light Count Mismatch");
static_assert(NUM_ARRAY(DIRECTION) == CLightManager::MAX_NUM, "ERROR : Light Count Mismatch");

//************************************************************
//	�e�N���X [CLightManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CLightManager::CLightManager()
{
	// �����o�ϐ����N���A
	memset(&m_apLight[0], 0, sizeof(m_apLight));	// ���C�g���
}

//============================================================
//	�f�X�g���N�^
//============================================================
CLightManager::~CLightManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CLightManager::Init()
{
	for (int i = 0; i < MAX_NUM; i++)
	{ // �g�p���郉�C�g�����J��Ԃ�

		// ���C�g�̐���
		m_apLight[i] = CLightDir::Create();
		if (m_apLight[i] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}

		// ���C�g�̃��x����ύX
		m_apLight[i]->SetLabel(CObject::LABEL_NONE);	// �����j��/�����X�V���~

		// ���C�g�̊g�U����ݒ�
		m_apLight[i]->SetDiffuse(DIFFUSE[i]);

		// ���C�g�̕�����ݒ�
		m_apLight[i]->SetDirection(DIRECTION[i]);
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CLightManager::Uninit()
{
	for (int i = 0; i < MAX_NUM; i++)
	{ // �g�p���郉�C�g�����J��Ԃ�

		// ���C�g�̏I��
		SAFE_UNINIT(m_apLight[i]);
	}
}

//============================================================
//	�X�V����
//============================================================
void CLightManager::Update(const float fDeltaTime)
{
	for (int i = 0; i < MAX_NUM; i++)
	{ // �g�p���郉�C�g�����J��Ԃ�

		// ���C�g�̍X�V
		m_apLight[i]->Update(fDeltaTime);
	}
}

//============================================================
//	��������
//============================================================
CLightManager* CLightManager::Create()
{
	// ���C�g�}�l�[�W���[�̐���
	CLightManager* pLightManager = new CLightManager;
	if (pLightManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���C�g�}�l�[�W���[�̏�����
		if (FAILED(pLightManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���C�g�}�l�[�W���[�̔j��
			SAFE_DELETE(pLightManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pLightManager;
	}
}

//============================================================
//	�j������
//============================================================
void CLightManager::Release(CLightManager*& prLightManager)
{
	// ���C�g�}�l�[�W���[�̏I��
	assert(prLightManager != nullptr);
	prLightManager->Uninit();

	// �������J��
	SAFE_DELETE(prLightManager);
}
