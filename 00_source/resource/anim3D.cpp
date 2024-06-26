//============================================================
//
//	�A�j���[�V����3D���� [anim3D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "anim3D.h"

//************************************************************
//	�q�N���X [CAnim3D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CAnim3D::CAnim3D(const CObject::ELabel label, const EDim dimension, const int nPriority) : CObject3D(label, dimension, nPriority),
	m_nCounter		(0),	// �A�j���[�V�����J�E���^�[
	m_nCntChange	(0),	// �p�^�[���ύX�J�E���g
	m_nPattern		(0),	// �A�j���[�V�����p�^�[��
	m_nMaxPtrn		(0),	// �p�^�[���̑���
	m_nWidthPtrn	(0),	// �e�N�X�`���̉��̕�����
	m_nHeightPtrn	(0),	// �e�N�X�`���̏c�̕�����
	m_nNumLoop		(0),	// �p�^�[���J��Ԃ���
	m_bStop		(false),	// ��~��
	m_bPlayBack	(false)		// �t�Đ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CAnim3D::~CAnim3D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CAnim3D::Init(void)
{
	// �����o�ϐ���������
	m_nCounter		= 0;	// �A�j���[�V�����J�E���^�[
	m_nCntChange	= 0;	// �p�^�[���ύX�J�E���g
	m_nPattern		= 0;	// �A�j���[�V�����p�^�[��
	m_nMaxPtrn		= 0;	// �p�^�[���̑���
	m_nWidthPtrn	= 1;	// �e�N�X�`���̉��̕�����
	m_nHeightPtrn	= 1;	// �e�N�X�`���̏c�̕�����
	m_nNumLoop		= 0;	// �p�^�[���J��Ԃ���
	m_bStop		= false;	// ��~��
	m_bPlayBack	= false;	// �t�Đ���

	// �I�u�W�F�N�g3D�̏�����
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CAnim3D::Uninit(void)
{
	// �I�u�W�F�N�g3D�̏I��
	CObject3D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CAnim3D::Update(const float fDeltaTime)
{
	// ��~���̏ꍇ������
	if (m_bStop) { return; }

	if (m_nCntChange > 0)
	{ // �ύX�J�E���g�� 0���傫���ꍇ

		// �J�E���^�[�����Z
		m_nCounter++;

		if (m_nCounter % m_nCntChange == 0)
		{ // �J�E���^�[���ύX�J�E���g�ɂȂ����ꍇ

			// �J�E���^�[��������
			m_nCounter = 0;

			if (!m_bPlayBack)
			{ // �ʏ�Đ��̏ꍇ

				// �p�^�[�������Z
				m_nPattern = (m_nPattern + 1) % m_nMaxPtrn;
			}
			else
			{ // �t�Đ��̏ꍇ

				// �p�^�[�������Z
				m_nPattern = (m_nPattern + (m_nMaxPtrn - 1)) % m_nMaxPtrn;
			}

			if (m_nPattern == 0)
			{ // �p�^�[�������ꖇ�ڂ̏ꍇ

				// �J��Ԃ��������Z
				m_nNumLoop++;
			}
		}
	}

	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update(fDeltaTime);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	�`�揈��
//============================================================
void CAnim3D::Draw(CShader *pShader)
{
	// �I�u�W�F�N�g3D�̕`��
	CObject3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CAnim3D *CAnim3D::Create(const int nWidthPtrn, const int nHeightPtrn, const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize, const D3DXVECTOR3& rRot, const D3DXCOLOR& rCol)
{
	// �A�j���[�V����3D�̐���
	CAnim3D *pAnim3D = new CAnim3D;
	if (pAnim3D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �A�j���[�V����3D�̏�����
		if (FAILED(pAnim3D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �A�j���[�V����3D�̔j��
			SAFE_DELETE(pAnim3D);
			return nullptr;
		}

		// �e�N�X�`������������ݒ�
		pAnim3D->SetWidthPattern(nWidthPtrn);

		// �e�N�X�`���c��������ݒ�
		pAnim3D->SetHeightPattern(nHeightPtrn);

		// �ʒu��ݒ�
		pAnim3D->SetVec3Position(rPos);

		// ������ݒ�
		pAnim3D->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pAnim3D->SetVec3Sizing(rSize);

		// �F��ݒ�
		pAnim3D->SetColor(rCol);

		// �m�ۂ����A�h���X��Ԃ�
		return pAnim3D;
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CAnim3D::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �ʒu�̐ݒ�
	CObject3D::SetVec3Position(rPos);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CAnim3D::SetVec3Rotation(const D3DXVECTOR3& rRot)
{
	// �����̐ݒ�
	CObject3D::SetVec3Rotation(rRot);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CAnim3D::SetVec3Sizing(const D3DXVECTOR3& rSize)
{
	// �傫���̐ݒ�
	CObject3D::SetVec3Sizing(rSize);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CAnim3D::SetColor(const D3DXCOLOR& rCol)
{
	// �F�̐ݒ�
	CObject3D::SetColor(rCol);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	�p�^�[���̐ݒ菈��
//============================================================
void CAnim3D::SetPattern(const int nPattern)
{
	// �����̃p�^�[��������
	m_nPattern = nPattern;

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	�p�^�[���̑����̐ݒ菈��
//============================================================
void CAnim3D::SetMaxPattern(const int nMaxPtrn)
{
	// �����̃p�^�[���̑�������
	m_nMaxPtrn = nMaxPtrn;

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	�e�N�X�`���̉��������̐ݒ菈��
//============================================================
void CAnim3D::SetWidthPattern(const int nWidthPtrn)
{
	// �����̃e�N�X�`������������ݒ�
	m_nWidthPtrn = nWidthPtrn;

	// �p�^�[���̑�����ݒ�
	m_nMaxPtrn = m_nWidthPtrn * m_nHeightPtrn;

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	�e�N�X�`���̏c�������̐ݒ菈��
//============================================================
void CAnim3D::SetHeightPattern(const int nHeightPtrn)
{
	// �����̃e�N�X�`���c��������ݒ�
	m_nHeightPtrn = nHeightPtrn;

	// �p�^�[���̑�����ݒ�
	m_nMaxPtrn = m_nWidthPtrn * m_nHeightPtrn;

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nPattern, m_nWidthPtrn, m_nHeightPtrn);
}

//============================================================
//	�J�E���^�[�̐ݒ菈��
//============================================================
void CAnim3D::SetCounter(const int nCntChange)
{
	// �����̃p�^�[���ύX�J�E���g����
	m_nCntChange = nCntChange;
}

//============================================================
//	��~�󋵂̐ݒ菈��
//============================================================
void CAnim3D::SetEnableStop(const bool bStop)
{
	// �����̒�~�󋵂���
	m_bStop = bStop;

	if (m_bStop)
	{ // ��~���ꂽ�ꍇ

		// �J��Ԃ�����������
		m_nNumLoop = 0;
	}
}

//============================================================
//	�t�Đ��󋵂̐ݒ菈��
//============================================================
void CAnim3D::SetEnablePlayBack(const bool bPlayBack)
{
	// �����̋t�Đ��󋵂���
	m_bPlayBack = bPlayBack;
}
