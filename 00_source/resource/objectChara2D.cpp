//============================================================
//
//	�I�u�W�F�N�g�L�����N�^�[2D���� [objectChara2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectChara2D.h"
#include "manager.h"
#include "renderer.h"
#include "motion2D.h"

//************************************************************
//	�q�N���X [CObjectChara2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectChara2D::CObjectChara2D(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CAnim3D(label, dimension, nPriority),
	m_pMotion	(nullptr)	// ���[�V����2D���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectChara2D::~CObjectChara2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectChara2D::Init(void)
{
	// �����o�ϐ���������
	m_pMotion = nullptr;	// ���[�V����2D���

	// �A�j���[�V����3D�̏�����
	if (FAILED(CAnim3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���[�V����2D�̐���
	m_pMotion = CMotion2D::Create(this);
	if (m_pMotion == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectChara2D::Uninit(void)
{
	// ���[�V����2D�̔j��
	SAFE_REF_RELEASE(m_pMotion);

	// �A�j���[�V����3D�̏I��
	CAnim3D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CObjectChara2D::Update(const float fDeltaTime)
{
	// ���[�V����2D�̍X�V
	assert(m_pMotion != nullptr);
	m_pMotion->Update(fDeltaTime);

	// �A�j���[�V����3D�̍X�V
	CAnim3D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CObjectChara2D::Draw(CShader *pShader)
{
	// �A�j���[�V����3D�̕`��
	CAnim3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CObjectChara2D *CObjectChara2D::Create(const D3DXVECTOR3 &rPos, const D3DXVECTOR3 &rRot)
{
	// �I�u�W�F�N�g�L�����N�^�[2D�̐���
	CObjectChara2D *pObjectChara2D = new CObjectChara2D;
	if (pObjectChara2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g�L�����N�^�[2D�̏�����
		if (FAILED(pObjectChara2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g�L�����N�^�[2D�̔j��
			SAFE_DELETE(pObjectChara2D);
			return nullptr;
		}

		// �ʒu��ݒ�
		pObjectChara2D->SetVec3Position(rPos);

		// ������ݒ�
		pObjectChara2D->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pObjectChara2D;
	}
}

//============================================================
//	�L�����N�^�[��񊄓�
//============================================================
void CObjectChara2D::BindCharaData(const char *pCharaPass)
{
	// ���蓖�Ă郂�[�V�����p�X�����݂��Ȃ��ꍇ������
	if (pCharaPass == nullptr) { assert(false); return; }

	// �L�����N�^�[2D�����擾
	CMotion2D::SInfo data = GET_MANAGER->GetCharacter2D()->Regist(pCharaPass);

	// ���[�V�������̑S�ݒ�
	m_pMotion->SetAllInfo(data);
}

//============================================================
//	���[�V�����̐ݒ菈��
//============================================================
void CObjectChara2D::SetMotion(const int nType)
{
	// ���[�V�����̐ݒ�
	m_pMotion->Set(nType);
}
