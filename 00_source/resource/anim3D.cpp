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
//	�萔�錾
//************************************************************
namespace
{
	const POSGRID2 INIT_PTRN = GRID2_ONE;	// �e�N�X�`���������̏����l
}

//************************************************************
//	�q�N���X [CAnim3D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CAnim3D::CAnim3D(const CObject::ELabel label, const EDim dimension, const int nPriority) : CObject3D(label, dimension, nPriority),
	m_funcNext	(nullptr),		// �p�^�[���ύX�֐��|�C���^
	m_ptrn		(GRID2_ZERO),	// �e�N�X�`��������
	m_fNextTime	(0.0f),			// �p�^�[���ύX����
	m_fCurTime	(0.0f),			// ���݂̑ҋ@����
	m_nCurPtrn	(0),			// ���݂̃p�^�[��
	m_nMaxPtrn	(0),			// �p�^�[���̑���
	m_nNumLoop	(0),			// �p�^�[���J��Ԃ���
	m_bPlay		(false),		// �Đ���
	m_bPlayBack	(false)			// �t�Đ���
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
	m_funcNext	= nullptr;		// �p�^�[���ύX�֐��|�C���^
	m_ptrn		= INIT_PTRN;	// �e�N�X�`��������
	m_fNextTime	= 0.0f;			// �p�^�[���ύX����
	m_fCurTime	= 0.0f;			// ���݂̑ҋ@����
	m_nCurPtrn	= 0;			// ���݂̃p�^�[��
	m_nMaxPtrn	= 0;			// �p�^�[������
	m_nNumLoop	= 0;			// �p�^�[���J��Ԃ���
	m_bPlay		= true;			// �Đ���
	m_bPlayBack	= false;		// �t�Đ���

	// �ʏ�Đ���ݒ�
	SetEnablePlayBack(false);

	// �I�u�W�F�N�g3D�̏�����
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);

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
	if (!m_bPlay) { return; }

	// ���݂̑ҋ@���Ԃ����Z
	m_fCurTime += fDeltaTime;
	while (m_fCurTime >= m_fNextTime)
	{ // �ҋ@���I������ꍇ

		// ���݂̑ҋ@���Ԃ��獡��̑ҋ@���Ԃ����Z
		m_fCurTime -= m_fNextTime;

		// ���݂̃p�^�[����ύX
		assert(m_funcNext != nullptr);
		m_funcNext();

		if (m_nCurPtrn == 0)
		{ // �p�^�[�������ꖇ�ڂ̏ꍇ

			// �J��Ԃ��������Z
			m_nNumLoop++;
		}
	}

	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update(fDeltaTime);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
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
CAnim3D *CAnim3D::Create
(
	const POSGRID2& rPtrn,		// �e�N�X�`��������
	const D3DXVECTOR3& rPos,	// �ʒu
	const float fNextTime,		// �p�^�[���ύX����
	const D3DXVECTOR3& rSize,	// �傫��
	const D3DXVECTOR3& rRot,	// ����
	const D3DXCOLOR& rCol		// �F
)
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

		// �e�N�X�`����������ݒ�
		pAnim3D->SetTexPtrn(rPtrn);

		// �p�^�[���ύX���Ԃ�ݒ�
		pAnim3D->SetNextTime(fNextTime);

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
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CAnim3D::SetVec3Rotation(const D3DXVECTOR3& rRot)
{
	// �����̐ݒ�
	CObject3D::SetVec3Rotation(rRot);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CAnim3D::SetVec3Sizing(const D3DXVECTOR3& rSize)
{
	// �傫���̐ݒ�
	CObject3D::SetVec3Sizing(rSize);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CAnim3D::SetColor(const D3DXCOLOR& rCol)
{
	// �F�̐ݒ�
	CObject3D::SetColor(rCol);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	���݃p�^�[���̐ݒ菈��
//============================================================
void CAnim3D::SetCurPtrn(const int nPtrn)
{
	// �����̃p�^�[��������
	m_nCurPtrn = nPtrn;

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	�e�N�X�`���������̐ݒ菈��
//============================================================
void CAnim3D::SetTexPtrn(const POSGRID2& rPtrn)
{
	// �����̃e�N�X�`����������ݒ�
	m_ptrn = rPtrn;

	// �p�^�[��������ݒ�
	SetMaxPtrn(m_ptrn.x * m_ptrn.y);
}

//============================================================
//	�e�N�X�`�����������̐ݒ菈��
//============================================================
void CAnim3D::SetTexPtrnWidth(const int nTexPtrnW)
{
	// �����̃e�N�X�`������������ݒ�
	m_ptrn.x = nTexPtrnW;

	// �p�^�[��������ݒ�
	SetMaxPtrn(m_ptrn.x * m_ptrn.y);
}

//============================================================
//	�e�N�X�`���c�������̐ݒ菈��
//============================================================
void CAnim3D::SetTexPtrnHeight(const int nTexPtrnH)
{
	// �����̃e�N�X�`���c��������ݒ�
	m_ptrn.y = nTexPtrnH;

	// �p�^�[��������ݒ�
	SetMaxPtrn(m_ptrn.x * m_ptrn.y);
}

//============================================================
//	�p�^�[���ύX���Ԃ̐ݒ菈��
//============================================================
void CAnim3D::SetNextTime(const float fNextTime)
{
	// �ύX���Ԃ��v���X�ł͂Ȃ��ꍇ������
	if (fNextTime <= 0.0f) { assert(false); return; }

	// �����̃p�^�[���ύX���Ԃ�ݒ�
	m_fNextTime = fNextTime;
}

//============================================================
//	�Đ��t���O�̐ݒ菈��
//============================================================
void CAnim3D::SetEnablePlay(const bool bPlay)
{
	// �����̍Đ��󋵂�ݒ�
	m_bPlay = bPlay;

	// ��~�����ꍇ�Ƀp�^�[���J��Ԃ�����������
	if (!m_bPlay) { m_nNumLoop = 0; }
}

//============================================================
//	�t�Đ��t���O�̐ݒ菈��
//============================================================
void CAnim3D::SetEnablePlayBack(const bool bPlayBack)
{
	// �����̋t�Đ��󋵂�ݒ�
	m_bPlayBack = bPlayBack;

	if (!m_bPlayBack)
	{ // �ʏ�Đ��̏ꍇ

		// �p�^�[�����Z�֐���ݒ�
		m_funcNext = std::bind(&CAnim3D::NextPtrn, this);
	}
	else
	{ // �t�Đ��̏ꍇ

		// �p�^�[�����Z�֐���ݒ�
		m_funcNext = std::bind(&CAnim3D::BackPtrn, this);
	}
}

//============================================================
//	�p�^�[�������̐ݒ菈��
//============================================================
void CAnim3D::SetMaxPtrn(const int nMaxPtrn)
{
	// �����̃p�^�[���̑�������
	m_nMaxPtrn = nMaxPtrn;

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	�p�^�[�����Z����
//============================================================
void CAnim3D::NextPtrn(void)
{
	// �p�^�[�������Z
	m_nCurPtrn = (m_nCurPtrn + 1) % m_nMaxPtrn;
}

//============================================================
//	�p�^�[�����Z����
//============================================================
void CAnim3D::BackPtrn(void)
{
	// �p�^�[�������Z
	m_nCurPtrn = (m_nCurPtrn + (m_nMaxPtrn - 1)) % m_nMaxPtrn;
}
