//============================================================
//
//	������2D���� [string2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "string2D.h"
#include "manager.h"
#include "font.h"
#include "char2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// ������2D�̗D�揇��
}

//************************************************************
//	�q�N���X [CString2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CString2D::CString2D() : CObject(CObject::LABEL_UI, CObject::DIM_2D, PRIORITY),
	m_ppChar		(nullptr),			// �����|���S���̏��
	m_pFontChar		(nullptr),			// �t�H���g����
	m_pos			(VEC3_ZERO),		// �ʒu
	m_rot			(VEC3_ZERO),		// ����
	m_col			(color::White()),	// �F
	m_alignX		(XALIGN_CENTER),	// ���z�u
	m_fCharHeight	(0.0f)				// �����̏c��
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CString2D::~CString2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CString2D::Init()
{
	// �����o�ϐ���������
	m_ppChar		= nullptr;			// �����|���S���̏��
	m_pFontChar		= nullptr;			// �t�H���g����
	m_pos			= VEC3_ZERO;		// �ʒu
	m_rot			= VEC3_ZERO;		// ����
	m_col			= color::White();	// �F
	m_alignX		= XALIGN_CENTER;	// ���z�u
	m_fCharHeight	= 0.0f;				// �����̏c��

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CString2D::Uninit()
{
	if (m_ppChar != nullptr)
	{ // �����񂪔j������Ă��Ȃ��ꍇ

		for (int i = 0; i < (int)m_wsStr.size(); i++)
		{ // ���������J��Ԃ�

			// �����̔j��
			SAFE_UNINIT(m_ppChar[i]);
		}
	}

	// ������̔j��
	SAFE_DEL_ARRAY(m_ppChar);

	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CString2D::Update(const float fDeltaTime)
{
	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�`�揈��
//============================================================
void CString2D::Draw(CShader* /*pShader*/)
{

}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CString2D::SetPriority(const int nPriority)
{
	// ���g�̗D�揇�ʂ�ݒ�
	CObject::SetPriority(nPriority);

	for (int i = 0; i < (int)m_wsStr.size(); i++)
	{ // ���������J��Ԃ�

		// �����̗D�揇�ʂ�ݒ�
		m_ppChar[i]->SetPriority(nPriority);
	}
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CString2D::SetEnableUpdate(const bool bUpdate)
{
	for (int i = 0; i < (int)m_wsStr.size(); i++)
	{ // ���������J��Ԃ�

		// �����̍X�V�󋵂�ݒ�
		m_ppChar[i]->SetEnableUpdate(bUpdate);
	}
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CString2D::SetEnableDraw(const bool bDraw)
{
	for (int i = 0; i < (int)m_wsStr.size(); i++)
	{ // ���������J��Ԃ�

		// �����̕`��󋵂�ݒ�
		m_ppChar[i]->SetEnableDraw(bDraw);
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CString2D::SetVec3Position(const VECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CString2D::SetVec3Rotation(const VECTOR3& rRot)
{
	// �ݒ肷�������ۑ�
	m_rot = rRot;

	for (int i = 0; i < (int)m_wsStr.size(); i++)
	{ // ���������J��Ԃ�

		// ���������̐ݒ�
		assert(m_ppChar[i] != nullptr);
		m_ppChar[i]->SetVec3Rotation(rRot);
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�������� (�}���`�o�C�g������)
//============================================================
CString2D* CString2D::Create
(
	const std::string& rFilePath,	// �t�H���g�p�X
	const bool bItalic,				// �C�^���b�N
	const std::string& rStr,		// �w�蕶����
	const VECTOR3& rPos,			// ���_�ʒu
	const float fHeight,			// �����c��
	const EAlignX alignX,			// ���z�u
	const VECTOR3& rRot,			// ���_����
	const COLOR& rCol				// �F
)
{
	// ������2D�̐���
	CString2D* pString2D = new CString2D;
	if (pString2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ������2D�̏�����
		if (FAILED(pString2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ������2D�̔j��
			SAFE_DELETE(pString2D);
			return nullptr;
		}

		// �t�H���g��ݒ�
		pString2D->SetFont(rFilePath, bItalic);

		// �������ݒ�
		if (FAILED(pString2D->SetString(rStr)))
		{ // �ݒ�Ɏ��s�����ꍇ

			// ������2D�̔j��
			SAFE_DELETE(pString2D);
			return nullptr;
		}

		// ���_�ʒu��ݒ�
		pString2D->SetVec3Position(rPos);

		// ���_������ݒ�
		pString2D->SetVec3Rotation(rRot);

		// �F��ݒ�
		pString2D->SetColor(rCol);

		// �����c����ݒ�
		pString2D->SetCharHeight(fHeight);

		// ���z�u��ݒ�
		pString2D->SetAlignX(alignX);

		// �m�ۂ����A�h���X��Ԃ�
		return pString2D;
	}
}

//============================================================
//	�������� (���C�h������)
//============================================================
CString2D* CString2D::Create
(
	const std::string& rFilePath,	// �t�H���g�p�X
	const bool bItalic,				// �C�^���b�N
	const std::wstring& rStr,		// �w�蕶����
	const VECTOR3& rPos,			// ���_�ʒu
	const float fHeight,			// �����c��
	const EAlignX alignX,			// ���z�u
	const VECTOR3& rRot,			// ���_����
	const COLOR& rCol				// �F
)
{
	// ������2D�̐���
	CString2D* pString2D = new CString2D;
	if (pString2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ������2D�̏�����
		if (FAILED(pString2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ������2D�̔j��
			SAFE_DELETE(pString2D);
			return nullptr;
		}

		// �t�H���g��ݒ�
		pString2D->SetFont(rFilePath, bItalic);

		// �������ݒ�
		if (FAILED(pString2D->SetString(rStr)))
		{ // �ݒ�Ɏ��s�����ꍇ

			// ������2D�̔j��
			SAFE_DELETE(pString2D);
			return nullptr;
		}

		// ���_�ʒu��ݒ�
		pString2D->SetVec3Position(rPos);

		// ���_������ݒ�
		pString2D->SetVec3Rotation(rRot);

		// �F��ݒ�
		pString2D->SetColor(rCol);

		// �����c����ݒ�
		pString2D->SetCharHeight(fHeight);

		// ���z�u��ݒ�
		pString2D->SetAlignX(alignX);

		// �m�ۂ����A�h���X��Ԃ�
		return pString2D;
	}
}

//============================================================
//	������̐ݒ菈�� (�}���`�o�C�g������)
//============================================================
HRESULT CString2D::SetString(const std::string& rStr)
{
	// ����������C�h�ϊ�
	std::wstring wsStr = useful::MultiByteToWide(rStr);

	// �������ݒ�
	if (FAILED(SetString(wsStr)))
	{ // �ݒ�Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	������̐ݒ菈�� (���C�h������)
//============================================================
HRESULT CString2D::SetString(const std::wstring& rStr)
{
	// ��������ۑ�����
	int nOldStrLen = (int)m_wsStr.size();	// �j�����镶����
	int nCurStrLen = (int)rStr.size();		// �������镶����

	// �w�蕶�����ύX
	m_wsStr = rStr;

	//--------------------------------------------------------
	//	���Ɏg�p���Ă��镶����j��
	//--------------------------------------------------------
	for (int i = 0; i < nOldStrLen; i++)
	{ // �j�����镶�������J��Ԃ�

		// ������j��
		SAFE_UNINIT(m_ppChar[i]);
	}

	// �������j��
	SAFE_DEL_ARRAY(m_ppChar);

	//--------------------------------------------------------
	//	�V���������𐶐�
	//--------------------------------------------------------
	// �������i�[����z��𐶐�
	m_ppChar = new CChar2D*[nCurStrLen];
	for (int i = 0; i < nCurStrLen; i++)
	{ // �������镶�������J��Ԃ�

		// �����𐶐�
		m_ppChar[i] = CChar2D::Create
		( // ����
			m_pFontChar->GetFilePath(),	// �t�H���g�p�X
			m_pFontChar->GetItalic(),	// �C�^���b�N
			m_wsStr[i],		// �w�蕶��
			m_pos,			// ���_�ʒu
			m_fCharHeight,	// �����c��
			m_rot,			// ���_����
			m_col			// �F
		);
		if (m_ppChar[i] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}

		// �����̃��x�����w��Ȃ��ɂ���
		m_ppChar[i]->SetLabel(LABEL_NONE);

		// �����̗D�揇�ʂ����g�̂��̂ɂ���
		m_ppChar[i]->SetPriority(GetPriority());
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();

	return S_OK;
}

//============================================================
//	�t�H���g�̐ݒ菈��
//============================================================
void CString2D::SetFont
(
	const std::string& rFilePath,	// �t�H���g�p�X
	const bool bItalic				// �C�^���b�N
)
{
	// �t�H���g��������ݒ�
	CFont* pFont = GET_MANAGER->GetFont();	// �t�H���g���
	m_pFontChar = pFont->Regist(rFilePath, bItalic).pFontChar;

	// ������̍Đݒ�
	SetString(m_wsStr);
}

//============================================================
//	�����x�̐ݒ菈��
//============================================================
void CString2D::SetAlpha(const float fAlpha)
{
	// �����̓����x��ۑ�
	m_col.a = fAlpha;

	// �F�̐ݒ�
	SetColor(m_col);
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CString2D::SetColor(const COLOR& rCol)
{
	// �ݒ肷��F��ۑ�
	m_col = rCol;

	for (int i = 0; i < (int)m_wsStr.size(); i++)
	{ // ���������J��Ԃ�

		// �����F�̐ݒ�
		assert(m_ppChar[i] != nullptr);
		m_ppChar[i]->SetColor(rCol);
	}
}

//============================================================
//	�����c���̐ݒ菈��
//============================================================
void CString2D::SetCharHeight(const float fHeight)
{
	// �ݒ肷�镶���̏c����ۑ�
	m_fCharHeight = fHeight;

	for (int i = 0; i < (int)m_wsStr.size(); i++)
	{ // ���������J��Ԃ�

		// �����c���̐ݒ�
		assert(m_ppChar[i] != nullptr);
		m_ppChar[i]->SetCharHeight(fHeight);
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	���z�u�̐ݒ菈��
//============================================================
void CString2D::SetAlignX(const EAlignX alignX)
{
	// �����̉��z�u��ݒ�
	m_alignX = alignX;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	������̉����擾����
//============================================================
float CString2D::GetStrWidth() const
{
	// �����񂪂Ȃ��ꍇ������
	if ((int)m_wsStr.size() <= 0) { assert(false); return 0.0f; }

	float fStrWidth = 0.0f;	// ������̉���
	int nEndCharIdx = (int)m_wsStr.size() - 1;	// �I�[�����̃C���f�b�N�X

	for (int i = 0; i < nEndCharIdx; i++)
	{ // �I�[�����𔲂������������J��Ԃ�

		// ���̕����܂ł̋��������Z
		assert(m_ppChar[i] != nullptr);
		fStrWidth += m_ppChar[i]->GetNext();
	}

	// �擪�����̃T�C�Y���u���b�N�{�b�N�X������̑傫���ɕ␳
	assert(m_ppChar[0] != nullptr);
	float fHeadWidth = m_ppChar[0]->GetVec3Size().x * 0.5f;			// �擪�����̉���
	fStrWidth += fHeadWidth - m_ppChar[0]->GetOffsetOrigin();		// ���_���O�̋�Ԃ����Z
	fStrWidth -= fHeadWidth + m_ppChar[0]->GetOffsetBlackBoxLU().x;	// �u���b�N�{�b�N�X�J�n���O�̋�Ԃ����Z

	// �I�[�����̃T�C�Y���u���b�N�{�b�N�X�E�܂ł̑傫���ɕ␳
	assert(m_ppChar[nEndCharIdx] != nullptr);
	float fTailWidth = m_ppChar[nEndCharIdx]->GetVec3Size().x * 0.5f;			// �I�[�����̉���
	fStrWidth -= fTailWidth - m_ppChar[nEndCharIdx]->GetOffsetOrigin();			// ���_���O�̋�Ԃ����Z
	fStrWidth += fTailWidth + m_ppChar[nEndCharIdx]->GetOffsetBlackBoxRD().x;	// �u���b�N�{�b�N�X�I�����O�̋�Ԃ����Z

	// ������̉�����Ԃ�
	return fStrWidth;
}

//============================================================
//	�����̎擾����
//============================================================
CChar2D *CString2D::GetChar2D(const int nCharIdx) const
{
	// �����񂪂Ȃ��ꍇ������
	int nStrLen = (int)m_wsStr.size();
	if (nStrLen <= 0) { assert(false); return nullptr; }

	// �C���f�b�N�X���͈͊O�̏ꍇ������
	if (nCharIdx <= NONE_IDX || nCharIdx >= nStrLen) { assert(false); return nullptr; }

	// �����C���f�b�N�X�̕�����Ԃ�
	return m_ppChar[nCharIdx];
}

//============================================================
//	������̎擾���� (�}���`�o�C�g������)
//============================================================
std::string CString2D::GetStr() const
{
	// ��������}���`�o�C�g�ϊ����ĕԂ�
	return useful::WideToMultiByte(m_wsStr);
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CString2D::SetPositionRelative()
{
	// �����񂪂Ȃ��ꍇ������
	if ((int)m_wsStr.size() <= 0) { return; }

	assert(m_ppChar[0] != nullptr);
	float fHeadOffsetOrigin	= m_ppChar[0]->GetOffsetOrigin();			// �擪�����̌��_�I�t�Z�b�g
	float fHeadOffsetLU	= m_ppChar[0]->GetOffsetBlackBoxLU().x;			// �擪�����̃u���b�N�{�b�N�X�I�t�Z�b�g
	float fHeadRot		= m_ppChar[0]->GetVec3Rotation().z - HALF_PI;	// �擪�����̌���
	float fHeadWidth	= m_ppChar[0]->GetVec3Size().x * 0.5f;			// �擪�����̉���
	float fStrWidth		= GetStrWidth() * 0.5f;							// ������S�̂̉���

	float fStartOffset = fStrWidth;	// �����̊J�n�ʒu�I�t�Z�b�g
	fStartOffset -= fHeadWidth - fHeadOffsetOrigin;	// �擪�����̌��_�����炷
	fStartOffset += fHeadWidth + fHeadOffsetLU;		// �擪�����̃u���b�N�{�b�N�X�����炷
	fStartOffset += (fStrWidth * (m_alignX - 1));	// �w�肳�ꂽ���z�u�ɂ���

	VECTOR3 posStart = VEC3_ZERO;	// �����̊J�n�ʒu
	posStart.x = m_pos.x + sinf(fHeadRot) * fStartOffset;	// �J�n�ʒuX
	posStart.y = m_pos.y + cosf(fHeadRot) * fStartOffset;	// �J�n�ʒuY

	for (int i = 0; i < (int)m_wsStr.size(); i++)
	{ // ���������J��Ԃ�

		assert(m_ppChar[i] != nullptr);
		float fOffset = m_ppChar[i]->GetOffsetOrigin();	// ���_�I�t�Z�b�g
		float fNext = m_ppChar[i]->GetNext();			// �������܂ł̋���

		// �ݒ���W�Ɍ��_�I�t�Z�b�g��^����
		posStart.x -= sinf(fHeadRot) * fOffset;
		posStart.y -= cosf(fHeadRot) * fOffset;

		// �ʒu�𔽉f
		m_ppChar[i]->SetVec3Position(posStart);

		// ���̐ݒ���W�̊J�n�_��ۑ�
		float fNextStart = fOffset - fNext;	// ���̊J�n�_
		posStart.x += sinf(fHeadRot) * fNextStart;
		posStart.y += cosf(fHeadRot) * fNextStart;
	}
}
