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
	m_funcPattern	(nullptr),		// �p�^�[���ύX�֐��|�C���^
	m_ptrn			(GRID2_ZERO),	// �e�N�X�`��������
	m_pNextTime		(nullptr),		// �p�^�[���ύX����
	m_fCurTime		(0.0f),			// ���݂̑ҋ@����
	m_fCurWholeTime	(0.0f),			// ���݂̑S�̎���
	m_fMaxWholeTime	(0.0f),			// ���S�̎���
	m_nCurPtrn		(0),			// ���݂̃p�^�[��
	m_nMaxPtrn		(0),			// �p�^�[���̑���
	m_nNumLoop		(0),			// �p�^�[���J��Ԃ���
	m_bPlay			(false),		// �Đ��t���O
	m_bPlayBack		(false),		// �t�Đ��t���O
	m_bLoop			(false),		// ���[�v�t���O
	m_bFinish		(false)			// �I���t���O
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
HRESULT CAnim3D::Init()
{
	// �����o�ϐ���������
	m_funcPattern	= nullptr;		// �p�^�[���ύX�֐��|�C���^
	m_ptrn			= GRID2_ZERO;	// �e�N�X�`��������
	m_pNextTime		= nullptr;		// �p�^�[���ύX����
	m_fCurTime		= 0.0f;			// ���݂̑ҋ@����
	m_fCurWholeTime	= 0.0f;			// ���݂̑S�̎���
	m_fMaxWholeTime	= 0.0f;			// ���S�̎���
	m_nCurPtrn		= 0;			// ���݂̃p�^�[��
	m_nMaxPtrn		= 0;			// �p�^�[������
	m_nNumLoop		= 0;			// �p�^�[���J��Ԃ���
	m_bPlay			= true;			// �Đ��t���O
	m_bPlayBack		= false;		// �t�Đ��t���O
	m_bLoop			= true;			// ���[�v�t���O
	m_bFinish		= false;		// �I���t���O

	// �e�N�X�`����������������
	SetTexPtrn(INIT_PTRN);

	// �ʏ�Đ���������
	SetEnablePlayBack(false);

	// �I�u�W�F�N�g3D�̏�����
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CAnim3D::Uninit()
{
	// �p�^�[���ύX���Ԃ̔j��
	SAFE_DEL_ARRAY(m_pNextTime);

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

	// �p�^�[���̍X�V
	assert(m_funcPattern != nullptr);
	m_funcPattern(fDeltaTime);

	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update(fDeltaTime);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	�`�揈��
//============================================================
void CAnim3D::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g3D�̕`��
	CObject3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CAnim3D* CAnim3D::Create
(
	const POSGRID2& rPtrn,	// �e�N�X�`��������
	const VECTOR3& rPos,	// �ʒu
	const float fNextTime,	// �p�^�[���ύX����
	const VECTOR3& rSize,	// �傫��
	const VECTOR3& rRot,	// ����
	const COLOR& rCol		// �F
)
{
	// �A�j���[�V����3D�̐���
	CAnim3D* pAnim3D = new CAnim3D;
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
		pAnim3D->SetVec3Size(rSize);

		// �F��ݒ�
		pAnim3D->SetColor(rCol);

		// �m�ۂ����A�h���X��Ԃ�
		return pAnim3D;
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CAnim3D::SetVec3Position(const VECTOR3& rPos)
{
	// �ʒu�̐ݒ�
	CObject3D::SetVec3Position(rPos);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CAnim3D::SetVec3Rotation(const VECTOR3& rRot)
{
	// �����̐ݒ�
	CObject3D::SetVec3Rotation(rRot);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CAnim3D::SetVec3Size(const VECTOR3& rSize)
{
	// �傫���̐ݒ�
	CObject3D::SetVec3Size(rSize);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	�����x�̐ݒ菈��
//============================================================
void CAnim3D::SetAlpha(const float fAlpha)
{
	// �����x�̐ݒ�
	CObject3D::SetAlpha(fAlpha);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CAnim3D::SetColor(const COLOR& rCol)
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
	// �����̃p�^�[������ݒ�
	m_nCurPtrn = nPtrn;

	// �I���t���O��OFF�ɂ���
	m_bFinish = false;

	// �S�̎��Ԃ̏�����
	m_fCurWholeTime = 0.0f;

	// �S�̎��Ԃ��p�^�[���̊J�n���Ԃɐݒ�
	int nAddTime = (!m_bPlayBack) ? 0 : 1;	// �t�Đ��̏ꍇ�͌��݃p�^�[���̑ҋ@���Ԃ��܂�
	int nLoop = m_nCurPtrn + nAddTime;		// �J��Ԃ��������߂�
	for (int i = 0; i < nLoop; i++)
	{ // �J�n�p�^�[���܂ŌJ��Ԃ�

		// �ҋ@���Ԃ����Z
		m_fCurWholeTime += m_pNextTime[i];
	}

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
//	�Đ��t���O�̐ݒ菈��
//============================================================
void CAnim3D::SetEnablePlay(const bool bPlay)
{
	// ��~�����ꍇ�ɌJ��Ԃ�����������
	if (!bPlay) { m_nNumLoop = 0; }

	// �����̍Đ��󋵂�ݒ�
	m_bPlay = bPlay;
}

//============================================================
//	�t�Đ��t���O�̐ݒ菈��
//============================================================
void CAnim3D::SetEnablePlayBack(const bool bPlayBack)
{
	// �Đ�/�t�Đ������]�����ꍇ�ɌJ��Ԃ����ƏI���t���O��������
	if (m_bPlayBack != bPlayBack) { m_nNumLoop = 0; m_bFinish = false; }

	// �����̋t�Đ��󋵂�ݒ�
	m_bPlayBack = bPlayBack;

	if (!m_bPlayBack)
	{ // �ʏ�Đ��̏ꍇ

		// �p�^�[�����Z�֐���ݒ�
		m_funcPattern = std::bind(&CAnim3D::NextPtrn, this, std::placeholders::_1);
	}
	else
	{ // �t�Đ��̏ꍇ

		// �p�^�[�����Z�֐���ݒ�
		m_funcPattern = std::bind(&CAnim3D::BackPtrn, this, std::placeholders::_1);
	}
}

//============================================================
//	���[�v�t���O�̐ݒ菈��
//============================================================
void CAnim3D::SetEnableLoop(const bool bLoop)
{
	// ���[�v����ꍇ�I���t���O��������
	if (bLoop) { m_bFinish = false; }

	// �����̃��[�v�󋵂�ݒ�
	m_bLoop = bLoop;
}

//============================================================
//	���݃p�^�[���̏���������
//============================================================
void CAnim3D::ResetCurPtrn()
{
	// �I���t���O��OFF�ɂ���
	m_bFinish = false;

	if (!m_bPlayBack)
	{ // �ʏ�Đ��̏ꍇ

		// �J�n�p�^�[���̏�����
		m_nCurPtrn = 0;

		// �ҋ@���Ԃ̏�����
		m_fCurTime = 0.0f;
		m_fCurWholeTime = 0.0f;
	}
	else
	{ // �t�Đ��̏ꍇ

		// �J�n�p�^�[���̏�����
		m_nCurPtrn = m_nMaxPtrn - 1;

		// �ҋ@���Ԃ̏�����
		m_fCurTime = m_pNextTime[m_nCurPtrn];
		m_fCurWholeTime = m_fMaxWholeTime;
	}
}

//============================================================
//	�p�^�[���ύX���Ԃ̐ݒ菈�� (�p�^�[���w��)
//============================================================
void CAnim3D::SetNextTime(const int nPtrnIdx, const float fNextTime)
{
	// �p�^�[���C���f�b�N�X���͈͊O�̏ꍇ������
	if (nPtrnIdx <= NONE_IDX || nPtrnIdx >= m_nMaxPtrn) { assert(false); return; }

	// �ύX���Ԃ��v���X�ł͂Ȃ��ꍇ������
	if (fNextTime <= 0.0f) { assert(false); return; }

	// �ύX�O�̃p�^�[���ύX���Ԃ�ۑ�
	float fOldNextTime = m_pNextTime[nPtrnIdx];

	// �����̃p�^�[���ύX���Ԃ�ݒ�
	m_pNextTime[nPtrnIdx] = fNextTime;

	// ���S�̎��Ԃ�ύX
	m_fMaxWholeTime -= fOldNextTime;
	m_fMaxWholeTime += fNextTime;
}

//============================================================
//	�p�^�[���ύX���Ԃ̐ݒ菈�� (�S�p�^�[��)
//============================================================
void CAnim3D::SetNextTime(const float fNextTime)
{
	// �ύX���Ԃ��v���X�ł͂Ȃ��ꍇ������
	if (fNextTime <= 0.0f) { assert(false); return; }

	for (int i = 0; i < m_nMaxPtrn; i++)
	{ // �p�^�[���̑������J��Ԃ�

		// �����̃p�^�[���ύX���Ԃ�ݒ�
		m_pNextTime[i] = fNextTime;
	}

	// ���S�̎��Ԃ�ύX
	m_fMaxWholeTime = fNextTime * (float)m_nMaxPtrn;
}

//============================================================
//	�p�^�[�������̐ݒ菈��
//============================================================
HRESULT CAnim3D::SetMaxPtrn(const int nMaxPtrn)
{
	// �����̃p�^�[���̑�����ݒ�
	m_nMaxPtrn = nMaxPtrn;

	// �p�^�[���ύX���Ԃ̔j��
	SAFE_DEL_ARRAY(m_pNextTime);

	// �p�^�[���ύX���Ԃ̍Đ���
	m_pNextTime = new float[m_nMaxPtrn];
	if (m_pNextTime == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �p�^�[���ύX���Ԃ�������
	SetNextTime(DEF_NEXT);

	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	CObject3D::SetAnimTex(m_nCurPtrn, m_ptrn.x, m_ptrn.y);

	return S_OK;
}

//============================================================
//	�p�^�[�����Z����
//============================================================
void CAnim3D::NextPtrn(const float fDeltaTime)
{
	// �A�j���[�V�������I�����Ă���ꍇ������
	if (m_bFinish) { return; }

	// ���݂̑ҋ@���Ԃ����Z
	m_fCurTime += fDeltaTime;
	m_fCurWholeTime += fDeltaTime;

	while (m_fCurTime >= m_pNextTime[m_nCurPtrn])
	{ // �ҋ@���I������ꍇ

		// ���݂̑ҋ@���Ԃ��獡��̑ҋ@���Ԃ����Z
		m_fCurTime -= m_pNextTime[m_nCurPtrn];

		// �p�^�[�������Z
		m_nCurPtrn = (m_nCurPtrn + 1) % m_nMaxPtrn;
		if (m_nCurPtrn == 0)
		{ // �擪�p�^�[���̏ꍇ

			if (m_bLoop)
			{ // ���[�v����ꍇ

				// �J��Ԃ��������Z
				m_nNumLoop++;

				// �S�̎��Ԃ�������
				m_fCurWholeTime = 0.0f;
			}
			else
			{ // ���[�v���Ȃ��ꍇ

				// �p�^�[����␳
				m_nCurPtrn = m_nMaxPtrn - 1;

				// �S�̎��Ԃ�������
				m_fCurWholeTime = m_fMaxWholeTime;

				// �A�j���[�V�����I����ۑ�
				m_bFinish = true;
			}
		}
	}
}

//============================================================
//	�p�^�[�����Z����
//============================================================
void CAnim3D::BackPtrn(const float fDeltaTime)
{
	// �A�j���[�V�������I�����Ă���ꍇ������
	if (m_bFinish) { return; }

	// ���݂̑ҋ@���Ԃ����Z
	m_fCurTime -= fDeltaTime;
	m_fCurWholeTime -= fDeltaTime;

	while (m_fCurTime <= 0.0f)
	{ // �ҋ@���I������ꍇ

		// ���݂̑ҋ@���Ԃ��獡��̑ҋ@���Ԃ����Z
		m_fCurTime += m_pNextTime[m_nCurPtrn];

		// �p�^�[�������Z
		m_nCurPtrn = (m_nCurPtrn + (m_nMaxPtrn - 1)) % m_nMaxPtrn;

		if (m_nCurPtrn == m_nMaxPtrn - 1)
		{ // �ŏI�p�^�[���̏ꍇ

			if (m_bLoop)
			{ // ���[�v����ꍇ

				// �J��Ԃ��������Z
				m_nNumLoop++;

				// �S�̎��Ԃ�������
				m_fCurWholeTime = m_fMaxWholeTime;
			}
			else
			{ // ���[�v���Ȃ��ꍇ

				// �p�^�[����␳
				m_nCurPtrn = 0;

				// �S�̎��Ԃ�������
				m_fCurWholeTime = 0.0f;

				// �A�j���[�V�����I����ۑ�
				m_bFinish = true;
			}
		}
	}
}
