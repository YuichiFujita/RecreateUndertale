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
		const int	PRIORITY	= 6;		// �e�L�X�g�̗D�揇��
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 45.0f;	// �����c��
		const float	LINE_HEIGHT	= 62.0f;	// �s�ԏc��
		const float	WAIT_TIME	= 0.105f;	// �����\���̑ҋ@����

		const VECTOR3 POS = VECTOR3(100.0f, 460.0f, 0.0f);	// �e�L�X�g�ʒu
		const EAlignX ALIGN_X = XALIGN_LEFT;	// ���z�u
		const EAlignY ALIGN_Y = YALIGN_TOP;		// �c�z�u
	}
}

//************************************************************
//	�q�N���X [CFrameText2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrameText2D::CFrameText2D() :
	m_pText	(nullptr)	// �e�L�X�g���
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
	m_pText = nullptr;	// �e�L�X�g���

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
		text::POS,			// ���_�ʒu
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
//	��������
//============================================================
CFrameText2D* CFrameText2D::Create
(
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rRot,	// ����
	const VECTOR3& rSize	// �傫��
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
