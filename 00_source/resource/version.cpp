//============================================================
//
//	�o�[�W�����\�L���� [version.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "version.h"
#include "loadtext.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char*	PATH	 = "data\\TEXT\\version.txt";			// �e�L�X�g�p�X
	const char*	FONT	 = "data\\FONT\\Crypt of Tomorrow.ttf";	// �t�H���g�p�X
	const int	PRIORITY = 6;		// �D�揇��
	const bool	ITALIC	 = false;	// �C�^���b�N
	const float	HEIGHT	 = 22.5f;	// �����c��

	const VECTOR3	POS = VECTOR3(SCREEN_CENT.x, 706.0f, 0.0f);	// �ʒu
	const VECTOR3	ROT = VEC3_ZERO;							// ����
	const COLOR		COL = COLOR(0.5f, 0.5f, 0.5f, 1.0f);		// �F
	const EAlignX	ALIGN_X = XALIGN_CENTER;					// ���z�u
}

//************************************************************
//	�q�N���X [CVersion] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CVersion::CVersion()
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CVersion::~CVersion()
{

}

//============================================================
//	����������
//============================================================
HRESULT CVersion::Init()
{
	// ������2D�̏�����
	if (FAILED(CString2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �t�H���g��ݒ�
	SetFont(FONT, ITALIC);

	// ���_�ʒu��ݒ�
	SetVec3Position(POS);

	// �F��ݒ�
	SetColor(COL);

	// �����c����ݒ�
	SetCharHeight(HEIGHT);

	// ���z�u��ݒ�
	SetAlignX(ALIGN_X);

	// �D�揇�ʂ�ݒ�
	SetPriority(PRIORITY);

	// �����������
	loadtext::BindString(this, loadtext::LoadText(PATH, 0));

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CVersion::Uninit()
{
	// ������2D�̏I��
	CString2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CVersion::Update(const float fDeltaTime)
{
	// ������2D�̍X�V
	CString2D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CVersion::Draw(CShader* pShader)
{
	// ������2D�̕`��
	CString2D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CVersion* CVersion::Create()
{
	// �o�[�W�����\�L�̐���
	CVersion* pVersion = new CVersion;
	if (pVersion == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �o�[�W�����\�L�̏�����
		if (FAILED(pVersion->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �o�[�W�����\�L�̔j��
			SAFE_DELETE(pVersion);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pVersion;
	}
}
