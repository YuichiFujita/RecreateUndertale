//============================================================
//
//	�t���[��2D���� [frame2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2D.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const COLOR COL_FRAME[] = { color::White(), color::Black() };	// �t���[���F
	const VECTOR3 BORD_THICK = VECTOR3(18.0f, 18.0f, 0.0f);	// ����葾��
	const int PRIORITY = 6;	// �t���[��2D�̗D�揇��
}

//************************************************************
//	�q�N���X [CFrame2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2D::CFrame2D() : CObject(LABEL_UI, DIM_2D, PRIORITY),
	m_pos	(VEC3_ZERO),	// �ʒu
	m_rot	(VEC3_ZERO),	// ����
	m_size	(VEC3_ZERO)		// �傫��
{
	// �����o�ϐ����N���A
	memset(&m_apFrame[0], 0, sizeof(m_apFrame));	// �t���[�����
}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2D::~CFrame2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFrame2D::Init()
{
	// �����o�ϐ���������
	memset(&m_apFrame[0], 0, sizeof(m_apFrame));	// �t���[�����
	m_pos	= VEC3_ZERO;	// �ʒu
	m_rot	= VEC3_ZERO;	// ����
	m_size	= VEC3_ZERO;	// �傫��

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̐���
		m_apFrame[i] = CObject2D::Create(VEC3_ZERO);
		if (m_apFrame[i] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �F��ݒ�
		m_apFrame[i]->SetColor(COL_FRAME[i]);

		// �����X�V�E�����`���OFF�ɂ���
		m_apFrame[i]->SetEnableUpdate(false);
		m_apFrame[i]->SetEnableDraw(false);
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFrame2D::Uninit()
{
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̏I��
		SAFE_UNINIT(m_apFrame[i]);
	}

	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CFrame2D::Update(const float fDeltaTime)
{
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̍X�V
		m_apFrame[i]->Update(fDeltaTime);
	}
}

//============================================================
//	�`�揈��
//============================================================
void CFrame2D::Draw(CShader* pShader)
{
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̕`��
		m_apFrame[i]->Draw(pShader);
	}
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CFrame2D::SetPriority(const int nPriority)
{
	// �����̗D�揇�ʂ�ݒ�
	CObject::SetPriority(nPriority);	// ���g
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		m_apFrame[i]->SetPriority(nPriority);	// �t���[��
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFrame2D::SetVec3Position(const VECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		m_apFrame[i]->SetVec3Position(rPos);	// �t���[��
	}
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFrame2D::SetVec3Rotation(const VECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_rot = rRot;

	// �����̐��K��
	useful::NormalizeRot(m_rot);

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		m_apFrame[i]->SetVec3Rotation(rRot);	// �t���[��
	}
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CFrame2D::SetVec3Size(const VECTOR3& rSize)
{
	// �����̑傫����ݒ�
	m_size = rSize;
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		float fCalcScale = (-1.0f * (i - 1));	// �傫�������l
		m_apFrame[i]->SetVec3Size(rSize + fCalcScale * BORD_THICK);	// �t���[��
	}
}

//============================================================
//	��������
//============================================================
CFrame2D* CFrame2D::Create
(
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rRot,	// ����
	const VECTOR3& rSize	// �傫��
)
{
	// �t���[��2D�̐���
	CFrame2D* pFrame2D = new CFrame2D;
	if (pFrame2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �t���[��2D�̏�����
		if (FAILED(pFrame2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �t���[��2D�̔j��
			SAFE_DELETE(pFrame2D);
			return nullptr;
		}

		// �ʒu��ݒ�
		pFrame2D->SetVec3Position(rPos);

		// ������ݒ�
		pFrame2D->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pFrame2D->SetVec3Size(rSize);

		// �m�ۂ����A�h���X��Ԃ�
		return pFrame2D;
	}
}
