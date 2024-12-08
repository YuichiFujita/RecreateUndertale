//============================================================
//
//	�t���[���e�L�X�g2D���� [frameText2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frameText2D.h"
#include "string2D.h"
#include "text2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	namespace text
	{
		const char*	FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const int	PRIORITY	= 6;			// �e�L�X�g�̗D�揇��
		const bool	ITALIC		= false;		// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;		// �����c��
		const float	LINE_HEIGHT	= 54.0f;		// �s�ԏc��
		const float	WAIT_TIME	= 0.045f;		// �����\���̑ҋ@����
		const EAlignX ALIGN_X	= XALIGN_LEFT;	// ���z�u
		const EAlignY ALIGN_Y	= YALIGN_TOP;	// �c�z�u
	}
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const VECTOR3 CFrameText2D::POS[]	 = { VECTOR3(SCREEN_CENT.x, 594.0f, 0.0f) };	// �e�L�X�g�{�b�N�X�ʒu
const VECTOR3 CFrameText2D::ROT[]	 = { VEC3_ZERO };								// �e�L�X�g�{�b�N�X����
const VECTOR3 CFrameText2D::SIZE[]	 = { VECTOR3(850.0f, 210.0f, 0.0f) };			// �e�L�X�g�{�b�N�X�傫��
const VECTOR3 CFrameText2D::OFFSET[] = { VECTOR3(-410.0f, -80.0f, 0.0f) };			// �e�L�X�g�I�t�Z�b�g

//************************************************************
//	�q�N���X [CFrameText2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrameText2D::CFrameText2D() :
	m_pText	 (nullptr),		// �e�L�X�g���
	m_offset (VEC3_ZERO)	// �e�L�X�g�I�t�Z�b�g
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrameText2D::~CFrameText2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFrameText2D::Init()
{
	// �����o�ϐ���������
	m_pText	 = nullptr;		// �e�L�X�g���
	m_offset = VEC3_ZERO;	// �e�L�X�g�I�t�Z�b�g

	// �t���[��2D�̏�����
	if (FAILED(CFrame2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �e�L�X�g�̐���
	m_pText = CScrollText2D::Create
	( // ����
		text::FONT,			// �t�H���g�p�X
		text::ITALIC,		// �C�^���b�N
		VEC3_ZERO,			// ���_�ʒu
		text::WAIT_TIME,	// �����\���̑ҋ@����
		text::CHAR_HEIGHT,	// �����c��
		text::LINE_HEIGHT,	// �s�ԏc��
		text::ALIGN_X,		// ���z�u
		text::ALIGN_Y		// �c�z�u
	);
	if (m_pText == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ��t�F�[�h����ɂ���
	m_pText->SetPriority(GetPriority());

	// �������莞�̍Đ�SE��ݒ�
	m_pText->SetScrollSE(CSound::LABEL_SE_TEXT01);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFrameText2D::Uninit()
{
	// �e�L�X�g�̏I��
	SAFE_UNINIT(m_pText);

	// �t���[��2D�̏I��
	CFrame2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CFrameText2D::Update(const float fDeltaTime)
{
	// �t���[��2D�̍X�V
	CFrame2D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CFrameText2D::Draw(CShader* pShader)
{
	// �t���[��2D�̕`��
	CFrame2D::Draw(pShader);
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFrameText2D::SetVec3Position(const VECTOR3& rPos)
{
	// �e�N���X�̈ʒu��ݒ�
	CFrame2D::SetVec3Position(rPos);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFrameText2D::SetVec3Rotation(const VECTOR3& rRot)
{
	// �e�N���X�̌�����ݒ�
	CFrame2D::SetVec3Rotation(rRot);

	// �e�L�X�g�̌�����ݒ�
	m_pText->SetVec3Rotation(rRot);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�������� (�z�u�v���Z�b�g)
//============================================================
CFrameText2D* CFrameText2D::Create(const EPlace place)
{
	// �t���[���e�L�X�g2D�̐���
	return CFrameText2D::Create
	( // ����
		POS[place],		// �ʒu
		ROT[place],		// ����
		SIZE[place],	// �傫��
		OFFSET[place]	// �I�t�Z�b�g
	);
}

//============================================================
//	�������� (�z�u�w��)
//============================================================
CFrameText2D* CFrameText2D::Create
(
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rRot,	// ����
	const VECTOR3& rSize,	// �傫��
	const VECTOR3& rOffset	// �I�t�Z�b�g
)
{
	// �t���[���e�L�X�g2D�̐���
	CFrameText2D* pFrameText2D = new CFrameText2D;
	if (pFrameText2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �t���[���e�L�X�g2D�̏�����
		if (FAILED(pFrameText2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �t���[���e�L�X�g2D�̔j��
			SAFE_DELETE(pFrameText2D);
			return nullptr;
		}

		// �ʒu��ݒ�
		pFrameText2D->SetVec3Position(rPos);

		// ������ݒ�
		pFrameText2D->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pFrameText2D->SetVec3Size(rSize);

		// �e�L�X�g�I�t�Z�b�g��ݒ�
		pFrameText2D->SetOffset(rOffset);

		// �m�ۂ����A�h���X��Ԃ�
		return pFrameText2D;
	}
}

//============================================================
//	�e�L�X�g�ύX����
//============================================================
void CFrameText2D::ChangeText(const AText& rText)
{
	// �������S�č폜
	m_pText->DeleteStringAll();

	// �e�L�X�g������
	int nLoop = (int)rText.size();	// ������
	for (int i = 0; i < nLoop; i++)
	{ // ������̐����J��Ԃ�

		// ��������Ō���ɒǉ�
		m_pText->PushBackString(rText[i]);
	}

	// �������S�Ĕ�\���ɂ���
	m_pText->SetEnableScroll(true);
}

//============================================================
//	�e�L�X�g�I�t�Z�b�g�̐ݒ菈��
//============================================================
void CFrameText2D::SetOffset(const VECTOR3& rOffset)
{
	// �e�L�X�g�I�t�Z�b�g�̐ݒ�
	m_offset = rOffset;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CFrameText2D::SetPositionRelative()
{
	VECTOR3 posFrame = GetVec3Position();	// �t���[���ʒu
	VECTOR3 rotFrame = GetVec3Rotation();	// �t���[������

	// X���W�I�t�Z�b�g�����炷
	posFrame.x += sinf(rotFrame.z + HALF_PI) * m_offset.x;
	posFrame.y += cosf(rotFrame.z + HALF_PI) * m_offset.x;

	// Y���W�I�t�Z�b�g�����炷
	posFrame.x += sinf(rotFrame.z) * m_offset.y;
	posFrame.y += cosf(rotFrame.z) * m_offset.y;

	// �e�L�X�g�ʒu�̔��f
	m_pText->SetVec3Position(posFrame);
}
