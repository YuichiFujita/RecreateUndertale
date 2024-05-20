//============================================================
//
//	�������蕶����2D���� [scrollString2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scrollString2D.h"
#include "string2D.h"
#include "char2D.h"

//************************************************************
//	�q�N���X [CScrollString2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CScrollString2D::CScrollString2D() :
	m_nNextID	(0),	// ���\�����镶���C���f�b�N�X
	m_fNextTime	(0.0f),	// ���\������܂ł̎���
	m_fCurTime	(0.0f),	// ���݂̑ҋ@����
	m_bScroll	(false)	// ���������
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CScrollString2D::~CScrollString2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CScrollString2D::Init(void)
{
	// �����o�ϐ���������
	m_nNextID	= 0;		// ���\�����镶���C���f�b�N�X
	m_fNextTime	= 0.0f;		// ���\������܂ł̎���
	m_fCurTime	= 0.0f;		// ���݂̑ҋ@����
	m_bScroll	= false;	// ���������

	// ������2D�̏�����
	if (FAILED(CString2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CScrollString2D::Uninit(void)
{
	// ������2D�̏I��
	CString2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CScrollString2D::Update(const float fDeltaTime)
{
	// ��������̍X�V
	UpdateScroll(fDeltaTime);

	// ������2D�̍X�V
	CString2D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CScrollString2D::Draw(CShader *pShader)
{
	// ������2D�̕`��
	CString2D::Draw(pShader);
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CScrollString2D::SetEnableDraw(const bool bDraw)
{
	// ���\�����镶���C���f�b�N�X��`��ݒ�ɉ����Ĕ��f
	m_nNextID = (bDraw) ? GetNumChar() - 1 : 0;	// ON�Ȃ�Ō���AOFF�Ȃ�擪

	// ���݂̑ҋ@���Ԃ�������
	m_fCurTime = 0.0f;

	// �`��󋵂̐ݒ�
	CString2D::SetEnableDraw(bDraw);
}

//============================================================
//	������̒ǉ�����
//============================================================
HRESULT CScrollString2D::SetString(const std::wstring& rStr)
{
	// ������̐ݒ�
	if (FAILED(CString2D::SetString(rStr)))
	{ // �ǉ��Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �ݒ肵��������̎����`���OFF�ɂ���
	SetEnableDraw(false);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	��������
//============================================================
CScrollString2D *CScrollString2D::Create
(
	const std::string &rFilePass,	// �t�H���g�p�X
	const bool bItalic,				// �C�^���b�N
	const std::wstring &rStr,		// �w�蕶����
	const D3DXVECTOR3 &rPos,		// ���_�ʒu
	const float fNextTime,			// �����\���̑ҋ@����
	const float fHeight,			// �����c��
	const EAlignX alignX,			// ���z�u
	const D3DXVECTOR3& rRot,		// ���_����
	const D3DXCOLOR& rCol			// �F
)
{
	// �������蕶����2D�̐���
	CScrollString2D *pScrollString2D = new CScrollString2D;
	if (pScrollString2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �������蕶����2D�̏�����
		if (FAILED(pScrollString2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������蕶����2D�̔j��
			SAFE_DELETE(pScrollString2D);
			return nullptr;
		}

		// �t�H���g��ݒ�
		pScrollString2D->SetFont(rFilePass, bItalic);

		// �������ݒ�
		if (FAILED(pScrollString2D->SetString(rStr)))
		{ // �ݒ�Ɏ��s�����ꍇ

			// �������蕶����2D�̔j��
			SAFE_DELETE(pScrollString2D);
			return nullptr;
		}

		// ���_�ʒu��ݒ�
		pScrollString2D->SetVec3Position(rPos);

		// ���_������ݒ�
		pScrollString2D->SetVec3Rotation(rRot);

		// �F��ݒ�
		pScrollString2D->SetColor(rCol);

		// �����\���̑ҋ@���Ԃ�ݒ�
		pScrollString2D->SetNextTime(fNextTime);

		// �����c����ݒ�
		pScrollString2D->SetCharHeight(fHeight);

		// ���z�u��ݒ�
		pScrollString2D->SetAlignX(alignX);

		// �m�ۂ����A�h���X��Ԃ�
		return pScrollString2D;
	}
}

//============================================================
//	��������̍X�V����
//============================================================
void CScrollString2D::UpdateScroll(const float fDeltaTime)
{
	// �������肪OFF�Ȃ甲����
	if (!m_bScroll) { return; }

	// �������Ȃ��ꍇ������
	if (GetNumChar() <= 0) { m_bScroll = false; return; }

	// ���݂̑ҋ@���Ԃ����Z
	m_fCurTime += fDeltaTime;
	while (m_fCurTime >= m_fNextTime)
	{ // �ҋ@���I������ꍇ

		CChar2D *pChar = GetChar2D(m_nNextID);	// �\�������镶�����

		// �����̎����`���ON�ɂ���
		assert(pChar != nullptr);
		pChar->SetEnableDraw(true);

		// ���݂̑ҋ@���Ԃ���ҋ@���Ԃ����Z
		m_fCurTime -= m_fNextTime;

		// ���̕����C���f�b�N�X�Ɉڍs
		m_nNextID++;

		if (useful::LimitMaxNum(m_nNextID, GetNumChar() - 1))
		{ // �Ō�̕����ɓ��B�����ꍇ

			// ���݂̑ҋ@���Ԃ�������
			m_fCurTime = 0.0f;

			// ���������OFF�ɂ���
			m_bScroll = false;

			break;
		}
	}
}
