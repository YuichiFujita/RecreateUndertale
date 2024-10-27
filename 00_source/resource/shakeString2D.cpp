//============================================================
//
//	�U��������2D���� [shakeString2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "shakeString2D.h"
#include "string2D.h"

//************************************************************
//	�q�N���X [CShakeString2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CShakeString2D::CShakeString2D() :
	m_posSave		(VEC3_ZERO),	// �ۑ��ʒu
	m_fShakeMove	(0.0f),			// �U���̈ړ���
	m_fNextTime		(0.0f),			// ���U���܂ł̑ҋ@����
	m_fCurTime		(0.0f)			// ���݂̑ҋ@����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CShakeString2D::~CShakeString2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CShakeString2D::Init()
{
	// �����o�ϐ���������
	m_posSave	 = VEC3_ZERO;	// �ۑ��ʒu
	m_fShakeMove = 0.0f;		// �U���̈ړ���
	m_fNextTime	 = 0.0f;		// ���U���܂ł̑ҋ@����
	m_fCurTime	 = 0.0f;		// ���݂̑ҋ@����

	// ������2D�̏�����
	if (FAILED(CString2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CShakeString2D::Uninit()
{
	// ������2D�̏I��
	CString2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CShakeString2D::Update(const float fDeltaTime)
{
	// �U���̍X�V
	UpdateShake(fDeltaTime);

	// ������2D�̍X�V
	CString2D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CShakeString2D::Draw(CShader* pShader)
{
	// ������2D�̕`��
	CString2D::Draw(pShader);
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CShakeString2D::SetVec3Position(const VECTOR3& rPos)
{
	// �e�N���X�̈ʒu��ݒ�
	CString2D::SetVec3Position(rPos);

	// �ݒ肳�ꂽ�ʒu��ۑ�
	m_posSave = rPos;
}

//============================================================
//	�������� (�}���`�o�C�g������)
//============================================================
CShakeString2D* CShakeString2D::Create
(
	const std::string& rFilePath,	// �t�H���g�p�X
	const bool bItalic,				// �C�^���b�N
	const std::string& rStr,		// �w�蕶����
	const VECTOR3& rPos,			// ���_�ʒu
	const float fNextTime,			// �����U���̑ҋ@����
	const float fMove,				// �U���ړ���
	const float fHeight,			// �����c��
	const EAlignX alignX,			// ���z�u
	const VECTOR3& rRot,			// ���_����
	const COLOR& rCol				// �F
)
{
	// �U��������2D�̐���
	CShakeString2D* pShakeString2D = new CShakeString2D;
	if (pShakeString2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �U��������2D�̏�����
		if (FAILED(pShakeString2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �U��������2D�̔j��
			SAFE_DELETE(pShakeString2D);
			return nullptr;
		}

		// �t�H���g��ݒ�
		pShakeString2D->SetFont(rFilePath, bItalic);

		// �������ݒ�
		if (FAILED(pShakeString2D->SetString(rStr)))
		{ // �ݒ�Ɏ��s�����ꍇ

			// �U��������2D�̔j��
			SAFE_DELETE(pShakeString2D);
			return nullptr;
		}

		// ���_�ʒu��ݒ�
		pShakeString2D->SetVec3Position(rPos);

		// ���_������ݒ�
		pShakeString2D->SetVec3Rotation(rRot);

		// �F��ݒ�
		pShakeString2D->SetColor(rCol);

		// �����U���̑ҋ@���Ԃ�ݒ�
		pShakeString2D->SetNextTime(fNextTime);

		// �U���̈ړ��ʂ�ݒ�
		pShakeString2D->SetShakeMove(fMove);

		// �����c����ݒ�
		pShakeString2D->SetCharHeight(fHeight);

		// ���z�u��ݒ�
		pShakeString2D->SetAlignX(alignX);

		// �m�ۂ����A�h���X��Ԃ�
		return pShakeString2D;
	}
}

//============================================================
//	�������� (���C�h������)
//============================================================
CShakeString2D* CShakeString2D::Create
(
	const std::string& rFilePath,	// �t�H���g�p�X
	const bool bItalic,				// �C�^���b�N
	const std::wstring& rStr,		// �w�蕶����
	const VECTOR3& rPos,			// ���_�ʒu
	const float fNextTime,			// �����U���̑ҋ@����
	const float fMove,				// �U���ړ���
	const float fHeight,			// �����c��
	const EAlignX alignX,			// ���z�u
	const VECTOR3& rRot,			// ���_����
	const COLOR& rCol				// �F
)
{
	// �U��������2D�̐���
	CShakeString2D* pShakeString2D = new CShakeString2D;
	if (pShakeString2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �U��������2D�̏�����
		if (FAILED(pShakeString2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �U��������2D�̔j��
			SAFE_DELETE(pShakeString2D);
			return nullptr;
		}

		// �t�H���g��ݒ�
		pShakeString2D->SetFont(rFilePath, bItalic);

		// �������ݒ�
		if (FAILED(pShakeString2D->SetString(rStr)))
		{ // �ݒ�Ɏ��s�����ꍇ

			// �U��������2D�̔j��
			SAFE_DELETE(pShakeString2D);
			return nullptr;
		}

		// ���_�ʒu��ݒ�
		pShakeString2D->SetVec3Position(rPos);

		// ���_������ݒ�
		pShakeString2D->SetVec3Rotation(rRot);

		// �F��ݒ�
		pShakeString2D->SetColor(rCol);

		// �����U���̑ҋ@���Ԃ�ݒ�
		pShakeString2D->SetNextTime(fNextTime);

		// �U���̈ړ��ʂ�ݒ�
		pShakeString2D->SetShakeMove(fMove);

		// �����c����ݒ�
		pShakeString2D->SetCharHeight(fHeight);

		// ���z�u��ݒ�
		pShakeString2D->SetAlignX(alignX);

		// �m�ۂ����A�h���X��Ԃ�
		return pShakeString2D;
	}
}

//============================================================
//	�U���̍X�V����
//============================================================
void CShakeString2D::UpdateShake(const float fDeltaTime)
{
	// ���݂̑ҋ@���Ԃ����Z
	m_fCurTime += fDeltaTime;
	if (m_fCurTime >= m_fNextTime)
	{ // �ҋ@���I������ꍇ

		// ���݂̑ҋ@���Ԃ�������
		m_fCurTime = 0.0f;

		// �����_���ɐU��������
		VECTOR3 offset = VEC3_ZERO;	// �ʒu�I�t�Z�b�g
		offset.x = m_fShakeMove * (float)(rand() % 3 - 1);
		offset.y = m_fShakeMove * (float)(rand() % 3 - 1);

		// �e�N���X�̈ʒu��ݒ�
		CString2D::SetVec3Position(m_posSave + offset);
	}
}
