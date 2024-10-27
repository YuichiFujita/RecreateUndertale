//============================================================
//
//	�X�N���[��2D���� [scroll2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scroll2D.h"

//************************************************************
//	�q�N���X [CScroll2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CScroll2D::CScroll2D(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObject2D(label, dimension, nPriority),
	m_fTexU		(0.0f),	// �e�N�X�`�������W�̊J�n�ʒu
	m_fTexV		(0.0f),	// �e�N�X�`���c���W�̊J�n�ʒu
	m_fOffsetU	(0.0f),	// �e�N�X�`�������W�̃I�t�Z�b�g�ʒu
	m_fOffsetV	(0.0f),	// �e�N�X�`���c���W�̃I�t�Z�b�g�ʒu
	m_fMoveU	(0.0f),	// �e�N�X�`�������W�̈ړ���
	m_fMoveV	(0.0f),	// �e�N�X�`���c���W�̈ړ���
	m_nNumLoopU	(0),	// ���p�^�[���J��Ԃ���
	m_nNumLoopV	(0)		// �c�p�^�[���J��Ԃ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CScroll2D::~CScroll2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CScroll2D::Init()
{
	// �����o�ϐ���������
	m_fTexU		= 0.0f;	// �e�N�X�`�������W�̊J�n�ʒu
	m_fTexV		= 0.0f;	// �e�N�X�`���c���W�̊J�n�ʒu
	m_fOffsetU	= 1.0f;	// �e�N�X�`�������W�̃I�t�Z�b�g�ʒu
	m_fOffsetV	= 1.0f;	// �e�N�X�`���c���W�̃I�t�Z�b�g�ʒu
	m_fMoveU	= 0.0f;	// �e�N�X�`�������W�̈ړ���
	m_fMoveV	= 0.0f;	// �e�N�X�`���c���W�̈ړ���
	m_nNumLoopU	= 0;	// ���p�^�[���J��Ԃ���
	m_nNumLoopV	= 0;	// �c�p�^�[���J��Ԃ���

	// �I�u�W�F�N�g2D�̏�����
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CScroll2D::Uninit()
{
	// �I�u�W�F�N�g2D�̏I��
	CObject2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CScroll2D::Update(const float fDeltaTime)
{
	// �X�N���[���ړ��ʂ�^����
	m_fTexU += m_fMoveU;
	m_fTexV += m_fMoveV;

	// �����W�̐��K��
	if (NormalizeTexPos(&m_fTexU))
	{ // ���K�����s��ꂽ�ꍇ

		// ���p�^�[���J��Ԃ��������Z
		m_nNumLoopU++;
	}

	// �c���W�̐��K��
	if (NormalizeTexPos(&m_fTexV))
	{
		// �c�p�^�[���J��Ԃ��������Z
		m_nNumLoopV++;
	}

	// �I�u�W�F�N�g2D�̍X�V
	CObject2D::Update(fDeltaTime);

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	�`�揈��
//============================================================
void CScroll2D::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g2D�̕`��
	CObject2D::Draw(pShader);
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CScroll2D::SetVec3Position(const VECTOR3& rPos)
{
	// �ʒu�̐ݒ�
	CObject2D::SetVec3Position(rPos);

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CScroll2D::SetVec3Rotation(const VECTOR3& rRot)
{
	// �����̐ݒ�
	CObject2D::SetVec3Rotation(rRot);

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CScroll2D::SetVec3Size(const VECTOR3& rSize)
{
	// �傫���̐ݒ�
	CObject2D::SetVec3Size(rSize);

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	��������
//============================================================
CScroll2D* CScroll2D::Create
(
	const float fMoveU,		// �����W�̈ړ���
	const float fMoveV,		// �c���W�̈ړ���
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rSize,	// �傫��
	const VECTOR3& rRot,	// ����
	const COLOR& rCol		// �F
)
{
	// �X�N���[��2D�̐���
	CScroll2D* pScroll2D = new CScroll2D;
	if (pScroll2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �X�N���[��2D�̏�����
		if (FAILED(pScroll2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �X�N���[��2D�̔j��
			SAFE_DELETE(pScroll2D);
			return nullptr;
		}

		// �ʒu��ݒ�
		pScroll2D->SetVec3Position(rPos);

		// ������ݒ�
		pScroll2D->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pScroll2D->SetVec3Size(rSize);

		// �F��ݒ�
		pScroll2D->SetColor(rCol);

		// �����W�̈ړ��ʂ�ݒ�
		pScroll2D->SetMoveU(fMoveU);

		// �c���W�̈ړ��ʂ�ݒ�
		pScroll2D->SetMoveV(fMoveV);

		// �m�ۂ����A�h���X��Ԃ�
		return pScroll2D;
	}
}

//============================================================
//	�����x�̐ݒ菈��
//============================================================
void CScroll2D::SetAlpha(const float fAlpha)
{
	// �����x�̐ݒ�
	CObject2D::SetAlpha(fAlpha);

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CScroll2D::SetColor(const COLOR& rCol)
{
	// �F�̐ݒ�
	CObject2D::SetColor(rCol);

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	�����W�̊J�n�ʒu�ݒ菈��
//============================================================
void CScroll2D::SetTexU(const float fTexU)
{
	// �����̉����W�̊J�n�ʒu����
	m_fTexU = fTexU;

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	�c���W�̊J�n�ʒu�ݒ菈��
//============================================================
void CScroll2D::SetTexV(const float fTexV)
{
	// �����̏c���W�̊J�n�ʒu����
	m_fTexV = fTexV;

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	�����W�̃I�t�Z�b�g�ʒu�ݒ菈��
//============================================================
void CScroll2D::SetOffsetU(const float fOffsetU)
{
	// �����̉����W�̃I�t�Z�b�g�ʒu����
	m_fOffsetU = fOffsetU;

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	�c���W�̃I�t�Z�b�g�ʒu�ݒ菈��
//============================================================
void CScroll2D::SetOffsetV(const float fOffsetV)
{
	// �����̉����W�̃I�t�Z�b�g�ʒu����
	m_fOffsetV = fOffsetV;

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	�����W�̈ړ��ʐݒ菈��
//============================================================
void CScroll2D::SetMoveU(const float fMoveU)
{
	// �����̉����W�̈ړ��ʂ���
	m_fMoveU = fMoveU;

	// ���p�^�[���J��Ԃ�����������
	m_nNumLoopU = 0;

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	�c���W�̈ړ��ʐݒ菈��
//============================================================
void CScroll2D::SetMoveV(const float fMoveV)
{
	// �����̏c���W�̈ړ��ʂ���
	m_fMoveV = fMoveV;

	// �c�p�^�[���J��Ԃ�����������
	m_nNumLoopV = 0;

	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	CObject2D::SetScrollTex(m_fTexU, m_fTexV, m_fOffsetU, m_fOffsetV);
}

//============================================================
//	�e�N�X�`�����W�̐��K��
//============================================================
bool CScroll2D::NormalizeTexPos(float* pTexPos)
{
	if (*pTexPos > 1.0f)
	{
		// �J�n�n�_��␳
		*pTexPos -= 1.0f;

		return true;
	}
	else if (*pTexPos < 0.0f)
	{
		// �J�n�n�_��␳
		*pTexPos += 1.0f;

		return true;
	}

	return false;
}
