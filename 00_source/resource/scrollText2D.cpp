//============================================================
//
//	��������e�L�X�g2D���� [scrollText2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scrollText2D.h"
#include "string2D.h"
#include "char2D.h"

//************************************************************
//	�q�N���X [CScrollText2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CScrollText2D::CScrollText2D() :
	m_nNextID	(0),	// ���\�����镶���C���f�b�N�X
	m_fNextTime	(0.0f),	// ���\������܂ł̎���
	m_fCurTime	(0.0f),	// ���݂̑ҋ@����
	m_bScroll	(false)	// ���������
{
	// �S�������z����N���A
	m_vecChar.clear();
}

//============================================================
//	�f�X�g���N�^
//============================================================
CScrollText2D::~CScrollText2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CScrollText2D::Init(void)
{
	// �����o�ϐ���������
	m_nNextID	= 0;		// ���\�����镶���C���f�b�N�X
	m_fNextTime	= 0.0f;		// ���\������܂ł̎���
	m_fCurTime	= 0.0f;		// ���݂̑ҋ@����
	m_bScroll	= false;	// ���������

	// �S�������z���������
	m_vecChar.clear();

	// �e�L�X�g2D�̏�����
	if (FAILED(CText2D::Init()))
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
void CScrollText2D::Uninit(void)
{
	// �S�������z����N���A
	m_vecChar.clear();

	// �e�L�X�g2D�̏I��
	CText2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CScrollText2D::Update(const float fDeltaTime)
{
	// ��������̍X�V
	UpdateScroll(fDeltaTime);

	// �e�L�X�g2D�̍X�V
	CText2D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CScrollText2D::Draw(CShader *pShader)
{
	// �e�L�X�g2D�̕`��
	CText2D::Draw(pShader);
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CScrollText2D::SetEnableDraw(const bool bDraw)
{
	// ���\�����镶���C���f�b�N�X��`��ݒ�ɉ����Ĕ��f
	m_nNextID = (bDraw) ? (int)m_vecChar.size() - 1 : 0;	// ON�Ȃ�Ō���AOFF�Ȃ�擪

	// ���݂̑ҋ@���Ԃ�������
	m_fCurTime = 0.0f;

	// �`��󋵂̐ݒ�
	CText2D::SetEnableDraw(bDraw);
}

//============================================================
//	������̒ǉ�����
//============================================================
HRESULT CScrollText2D::AddString(const std::wstring& rStr)
{
	// ������̒ǉ�
	if (FAILED(CText2D::AddString(rStr)))
	{ // �ǉ��Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	int nTailStrID = GetNumString() - 1;			// �Ō���̕�����C���f�b�N�X
	CString2D *pTailStr = GetString2D(nTailStrID);	// �Ō���̕�������

	// �Ō��������̎����`���OFF�ɂ���
	pTailStr->SetEnableDraw(false);

	// ��������̕�����z��ɒǉ�
	int nNumChar = pTailStr->GetNumChar();	// ������
	for (int nCntChar = 0; nCntChar < nNumChar; nCntChar++)
	{ // ���������J��Ԃ�

		// �Ō���ɕ����A�h���X��ǉ�
		m_vecChar.push_back(pTailStr->GetChar2D(nCntChar));
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	������̍폜����
//============================================================
void CScrollText2D::DeleteString(const int nStrID)
{
	int nDelHead = 0;	// �폜����擪�����C���f�b�N�X
	for (int i = 0; i < nStrID; i++)
	{ // �폜���镶����̎�O�܂ŌJ��Ԃ�

		// �폜���镶���̐擪�C���f�b�N�X�܂Œl��i�߂�
		nDelHead += GetString2D(i)->GetNumChar();
	}

	// �폜����C�e���[�^�[�̐擪�����߂�
	auto itrDelHead = m_vecChar.begin();	// �폜����擪�C�e���[�^�[
	std::advance(itrDelHead, nDelHead);		// �擪�܂Ői�߂�

	// �폜����C�e���[�^�[�̍Ō�������߂�
	auto itrDelTail = m_vecChar.begin();	// �폜����Ō���C�e���[�^�[
	std::advance(itrDelTail, nDelHead + GetString2D(nStrID)->GetNumChar());	// �Ō���܂Ői�߂�

	// �擪����Ō���܂ł̃C�e���[�^�[���폜
	m_vecChar.erase(itrDelHead, itrDelTail);

	// ������̍폜
	CText2D::DeleteString(nStrID);

	// �����C���f�b�N�X�𐧌�����
	useful::LimitMaxNum(m_nNextID, (int)m_vecChar.size());
}

//============================================================
//	������̑S�폜����
//============================================================
void CScrollText2D::DeleteStringAll(void)
{
	// ������̑S�폜
	CText2D::DeleteStringAll();

	// �S�������z����N���A
	m_vecChar.clear();

	// �����C���f�b�N�X��������
	m_nNextID = 0;
}

//============================================================
//	��������
//============================================================
CScrollText2D *CScrollText2D::Create
(
	const std::string &rFilePass,		// �t�H���g�p�X
	const bool bItalic,					// �C�^���b�N
	const D3DXVECTOR3& rPos,			// ���_�ʒu
	const float fNextTime,				// �����\���̑ҋ@����
	const float fCharHeight,			// �����c��
	const float fLineHeight,			// �s�ԏc��
	const CString2D::EAlignX alignX,	// ���z�u
	const EAlignY alignY,				// �c�z�u
	const D3DXVECTOR3& rRot,			// ���_����
	const D3DXCOLOR& rCol				// �F
)
{
	// ��������e�L�X�g2D�̐���
	CScrollText2D *pScrollText2D = new CScrollText2D;
	if (pScrollText2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ��������e�L�X�g2D�̏�����
		if (FAILED(pScrollText2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��������e�L�X�g2D�̔j��
			SAFE_DELETE(pScrollText2D);
			return nullptr;
		}

		// �t�H���g��ݒ�
		pScrollText2D->SetFont(rFilePass, bItalic);

		// ���_�ʒu��ݒ�
		pScrollText2D->SetVec3Position(rPos);

		// ���_������ݒ�
		pScrollText2D->SetVec3Rotation(rRot);

		// �F��ݒ�
		pScrollText2D->SetColor(rCol);

		// �����\���̑ҋ@���Ԃ�ݒ�
		pScrollText2D->SetNextTime(fNextTime);

		// �����c����ݒ�
		pScrollText2D->SetCharHeight(fCharHeight);

		// �s�ԏc����ݒ�
		pScrollText2D->SetLineHeight(fLineHeight);

		// ���z�u��ݒ�
		pScrollText2D->SetAlignX(alignX);

		// �c�z�u��ݒ�
		pScrollText2D->SetAlignY(alignY);

		// �m�ۂ����A�h���X��Ԃ�
		return pScrollText2D;
	}
}

//============================================================
//	��������̍X�V����
//============================================================
void CScrollText2D::UpdateScroll(const float fDeltaTime)
{
	// �������肪OFF�Ȃ甲����
	if (!m_bScroll) { return; }

	// �������Ȃ��ꍇ������
	if (m_vecChar.empty()) { m_bScroll = false; return; }

	// ���݂̑ҋ@���Ԃ����Z
	m_fCurTime += fDeltaTime;
	while (m_fCurTime >= m_fNextTime)
	{ // �ҋ@���I������ꍇ

		// �����̎����`���ON�ɂ���
		assert(m_vecChar[m_nNextID] != nullptr);
		m_vecChar[m_nNextID]->SetEnableDraw(true);

		// ���݂̑ҋ@���Ԃ���ҋ@���Ԃ����Z
		m_fCurTime -= m_fNextTime;

		// ���̕����C���f�b�N�X�Ɉڍs
		m_nNextID++;

		if (useful::LimitMaxNum(m_nNextID, (int)m_vecChar.size() - 1))
		{ // �Ō�̕����ɓ��B�����ꍇ

			// ���݂̑ҋ@���Ԃ�������
			m_fCurTime = 0.0f;

			// ���������OFF�ɂ���
			m_bScroll = false;

			break;
		}
	}
}
