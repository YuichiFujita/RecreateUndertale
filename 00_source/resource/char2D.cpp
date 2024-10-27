//============================================================
//
//	����2D���� [char2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "char2D.h"
#include "manager.h"
#include "texture.h"
#include "font.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// ����2D�̗D�揇��
}

//************************************************************
//	�q�N���X [CChar2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CChar2D::CChar2D() : CObject2D(CObject::LABEL_UI, CObject::DIM_2D, PRIORITY),
	m_pFontChar		(nullptr),	// �t�H���g����
	m_wcChar		(0),		// �w�蕶��
	m_fCharHeight	(0.0f),		// �����̏c��
	m_fSizeRate		(0.0f),		// �c���̊���
	m_fAbsOriginX	(0.0f),		// X���_�I�t�Z�b�g�̐�Βl
	m_bTexEmpty		(false)		// �e�N�X�`�������t���O
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CChar2D::~CChar2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CChar2D::Init()
{
	// �����o�ϐ���������
	m_pFontChar		= nullptr;	// �t�H���g����
	m_wcChar		= 0;		// �w�蕶��
	m_fCharHeight	= 0.0f;		// �����̏c��
	m_fSizeRate		= 1.0f;		// �c���̊���
	m_fAbsOriginX	= 0.0f;		// X���_�I�t�Z�b�g�̐�Βl
	m_bTexEmpty		= false;	// �e�N�X�`�������t���O

	// �I�u�W�F�N�g2D�̏�����
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CChar2D::Uninit()
{
	// �I�u�W�F�N�g2D�̏I��
	CObject2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CChar2D::Update(const float fDeltaTime)
{
	// �I�u�W�F�N�g2D�̍X�V
	CObject2D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CChar2D::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g2D�̕`��
	CObject2D::Draw(pShader);
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CChar2D::SetVec3Size(const VECTOR3& /*rSize*/)
{
	/*
		�������ő傫�������R�ɕς������
		�����̔䗦�����������Ȃ�̂ƁA
		�c���̊����Ȃǂ��ύX�ł��Ȃ�����
		�傫���ύX�� SetCharHeight �𗘗p���ĂˁB
	*/

	assert(false);
}

//============================================================
//	�������� (�}���`�o�C�g����)
//============================================================
CChar2D* CChar2D::Create
(
	const std::string& rFilePath,	// �t�H���g�p�X
	const bool bItalic,				// �C�^���b�N
	const std::string& rChar,		// �w�蕶��
	const VECTOR3& rPos,			// �ʒu
	const float fHeight,			// �c��
	const VECTOR3& rRot,			// ����
	const COLOR& rCol				// �F
)
{
	// ����2D�̐���
	CChar2D* pChar2D = new CChar2D;
	if (pChar2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ����2D�̏�����
		if (FAILED(pChar2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ����2D�̔j��
			SAFE_DELETE(pChar2D);
			return nullptr;
		}

		// �t�H���g��ݒ�
		pChar2D->SetFont(rFilePath, bItalic);

		// ������ݒ�
		pChar2D->SetChar(rChar);

		// �ʒu��ݒ�
		pChar2D->SetVec3Position(rPos);

		// ������ݒ�
		pChar2D->SetVec3Rotation(rRot);

		// �����c����ݒ�
		pChar2D->SetCharHeight(fHeight);

		// �F��ݒ�
		pChar2D->SetColor(rCol);

		// �m�ۂ����A�h���X��Ԃ�
		return pChar2D;
	}
}

//============================================================
//	�������� (���C�h����)
//============================================================
CChar2D* CChar2D::Create
(
	const std::string& rFilePath,	// �t�H���g�p�X
	const bool bItalic,				// �C�^���b�N
	const wchar_t wcChar,			// �w�蕶��
	const VECTOR3& rPos,			// �ʒu
	const float fHeight,			// �c��
	const VECTOR3& rRot,			// ����
	const COLOR& rCol				// �F
)
{
	// ����2D�̐���
	CChar2D* pChar2D = new CChar2D;
	if (pChar2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ����2D�̏�����
		if (FAILED(pChar2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ����2D�̔j��
			SAFE_DELETE(pChar2D);
			return nullptr;
		}

		// �t�H���g��ݒ�
		pChar2D->SetFont(rFilePath, bItalic);

		// ������ݒ�
		pChar2D->SetChar(wcChar);

		// �ʒu��ݒ�
		pChar2D->SetVec3Position(rPos);

		// ������ݒ�
		pChar2D->SetVec3Rotation(rRot);

		// �����c����ݒ�
		pChar2D->SetCharHeight(fHeight);

		// �F��ݒ�
		pChar2D->SetColor(rCol);

		// �m�ۂ����A�h���X��Ԃ�
		return pChar2D;
	}
}

//============================================================
//	�t�H���g�̐ݒ菈��
//============================================================
void CChar2D::SetFont
(
	const std::string& rFilePath,	// �t�H���g�p�X
	const bool bItalic				// �C�^���b�N
)
{
	// �t�H���g��������ݒ�
	CFont* pFont = GET_MANAGER->GetFont();	// �t�H���g���
	m_pFontChar = pFont->Regist(rFilePath, bItalic).pFontChar;

	// �w�蕶�����Đݒ�
	SetChar(m_wcChar);
}

//============================================================
//	�����̐ݒ菈�� (�}���`�o�C�g����)
//============================================================
void CChar2D::SetChar(const std::string& rChar)
{
	// ���C�h�ϊ���̐擪������ݒ�
	SetChar(useful::MultiByteToWide(rChar)[0]);
}

//============================================================
//	�����̐ݒ菈�� (���C�h����)
//============================================================
void CChar2D::SetChar(const wchar_t wcChar)
{
	CFontChar::SChar infoChar = m_pFontChar->Regist(wcChar);	// �������

	// �w�蕶����ۑ�
	m_wcChar = wcChar;

	// X���_�I�t�Z�b�g�̐�Βl��ۑ�
	m_fAbsOriginX = fabsf((float)infoChar.glyph.gmptGlyphOrigin.x);

	// �e�N�X�`�������t���O��ۑ�
	m_bTexEmpty = infoChar.bEmpty;

	// �e�N�X�`����o�^�E����
	BindTexture(infoChar.nTexIdx);

	// �����c���̍Đݒ�
	SetCharHeight(m_fCharHeight);
}

//============================================================
//	�����c���̐ݒ菈��
//============================================================
void CChar2D::SetCharHeight(const float fHeight)
{
	int nTexIdx = GetTextureIndex();	// �t�H���g�̃e�N�X�`���C���f�b�N�X
	float fTexWidth = useful::GetTexWidthFromAspect(fHeight, nTexIdx);			// �e�N�X�`������
	D3DXIMAGE_INFO status = GET_MANAGER->GetTexture()->GetInfo(nTexIdx).status;	// �e�N�X�`���X�e�[�^�X

	// �����̏c����ۑ�
	m_fCharHeight = fHeight;

	// �c���̑���������ۑ�
	m_fSizeRate = fHeight / (float)status.Height;

	// �傫����ݒ�
	CObject2D::SetVec3Size(VECTOR3(fTexWidth, fHeight, 0.0f));
}

//============================================================
//	�u���b�N�{�b�N�X�̍���I�t�Z�b�g�擾����
//============================================================
VECTOR2 CChar2D::GetOffsetBlackBoxLU()
{
	CFontChar::SChar infoChar = m_pFontChar->Regist(m_wcChar);	// �������

	VECTOR2 tempOffset;	// float�ϊ��I�t�Z�b�g�i�[�p
	tempOffset.x = (float)infoChar.offsetBlackBox.lu.x;
	tempOffset.y = (float)infoChar.offsetBlackBox.lu.y;

	// �u���b�N�{�b�N�X�̍���I�t�Z�b�g��Ԃ�
	return tempOffset * m_fSizeRate;
}

//============================================================
//	�u���b�N�{�b�N�X�̉E���I�t�Z�b�g�擾����
//============================================================
VECTOR2 CChar2D::GetOffsetBlackBoxRD()
{
	CFontChar::SChar infoChar = m_pFontChar->Regist(m_wcChar);	// �������

	VECTOR2 tempOffset;	// float�ϊ��I�t�Z�b�g�i�[�p
	tempOffset.x = (float)infoChar.offsetBlackBox.rd.x;
	tempOffset.y = (float)infoChar.offsetBlackBox.rd.y;

	// �u���b�N�{�b�N�X�̉E���I�t�Z�b�g��Ԃ�
	return tempOffset * m_fSizeRate;
}

//============================================================
//	�����̎擾���� (�}���`�o�C�g����)
//============================================================
std::string CChar2D::GetChar() const
{
	std::wstring wsChar;	// ������ϊ��p

	// �ϊ�������ɕ���������
	wsChar = m_wcChar;

	// �}���`�o�C�g�ϊ���̕������Ԃ�
	return useful::WideToMultiByte(wsChar);
}

//============================================================
//	���_�̃I�t�Z�b�g�擾����
//============================================================
float CChar2D::GetOffsetOrigin()
{
	CFontChar::SChar infoChar = m_pFontChar->Regist(m_wcChar);	// �������

	// �����u���b�N�{�b�N�X�̉���
	float fBlackBoxX = (float)infoChar.glyph.gmBlackBoxX;

	// �������_�̃I�t�Z�b�g��Ԃ�
	return (m_fAbsOriginX + fBlackBoxX * 0.5f) * m_fSizeRate;
}

//============================================================
//	���̕����܂ł̋����擾����
//============================================================
float CChar2D::GetNext()
{
	CFontChar::SChar infoChar = m_pFontChar->Regist(m_wcChar);	// �������

	// ���̕����̋�����Ԃ�
	return (float)infoChar.glyph.gmCellIncX * m_fSizeRate;
}
