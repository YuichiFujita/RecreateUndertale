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
#include "manager.h"
#include "string2D.h"
#include "char2D.h"

//************************************************************
//	�q�N���X [CScrollString2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CScrollString2D::CScrollString2D() :
	m_labelSE	(CSound::LABEL_NONE),	// ��������Đ�SE���x��
	m_nNextIdx	(0),	// ���\�����镶���C���f�b�N�X
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
HRESULT CScrollString2D::Init()
{
	// �����o�ϐ���������
	m_labelSE	= CSound::LABEL_NONE;	// ��������Đ�SE���x��
	m_nNextIdx	= 0;		// ���\�����镶���C���f�b�N�X
	m_fNextTime	= 0.0f;		// ���\������܂ł̎���
	m_fCurTime	= 0.0f;		// ���݂̑ҋ@����
	m_bScroll	= false;	// ���������

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
void CScrollString2D::Uninit()
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
void CScrollString2D::Draw(CShader* pShader)
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
	m_nNextIdx = (bDraw) ? GetNumChar() - 1 : 0;	// ON�Ȃ�Ō���AOFF�Ȃ�擪

	// ���݂̑ҋ@���Ԃ�������
	m_fCurTime = 0.0f;

	// �`��󋵂̐ݒ�
	CString2D::SetEnableDraw(bDraw);
}

//============================================================
//	������̐ݒ菈�� (�}���`�o�C�g������)
//============================================================
HRESULT CScrollString2D::SetString(const std::string& rStr)
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
HRESULT CScrollString2D::SetString(const std::wstring& rStr)
{
	// ������̐ݒ�
	if (FAILED(CString2D::SetString(rStr)))
	{ // �ǉ��Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �ݒ肵��������̎����`���OFF�ɂ���
	SetEnableDraw(false);

	return S_OK;
}

//============================================================
//	�������� (�}���`�o�C�g������)
//============================================================
CScrollString2D* CScrollString2D::Create
(
	const std::string& rFilePath,	// �t�H���g�p�X
	const bool bItalic,				// �C�^���b�N
	const std::string& rStr,		// �w�蕶����
	const VECTOR3& rPos,			// ���_�ʒu
	const float fNextTime,			// �����\���̑ҋ@����
	const float fHeight,			// �����c��
	const EAlignX alignX,			// ���z�u
	const VECTOR3& rRot,			// ���_����
	const COLOR& rCol				// �F
)
{
	// �������蕶����2D�̐���
	CScrollString2D* pScrollString2D = new CScrollString2D;
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
		pScrollString2D->SetFont(rFilePath, bItalic);

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
//	�������� (���C�h������)
//============================================================
CScrollString2D* CScrollString2D::Create
(
	const std::string& rFilePath,	// �t�H���g�p�X
	const bool bItalic,				// �C�^���b�N
	const std::wstring& rStr,		// �w�蕶����
	const VECTOR3& rPos,			// ���_�ʒu
	const float fNextTime,			// �����\���̑ҋ@����
	const float fHeight,			// �����c��
	const EAlignX alignX,			// ���z�u
	const VECTOR3& rRot,			// ���_����
	const COLOR& rCol				// �F
)
{
	// �������蕶����2D�̐���
	CScrollString2D* pScrollString2D = new CScrollString2D;
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
		pScrollString2D->SetFont(rFilePath, bItalic);

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
//	��������I���󋵂̎擾����
//============================================================
bool CScrollString2D::IsEndScroll() const
{
	// �I�[�����̎����`��t���O���當������̏I���𔻒肷��
	return GetChar2D(GetNumChar() - 1)->IsDraw();
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

		CChar2D* pChar = GetChar2D(m_nNextIdx);	// �\�������镶�����

		// �����̎����`���ON�ɂ���
		assert(pChar != nullptr);
		pChar->SetEnableDraw(true);

		// ���݂̑ҋ@���Ԃ���ҋ@���Ԃ����Z
		m_fCurTime -= m_fNextTime;

		// �������蒆�̌��ʉ����Đ�
		PlayScrollSE(pChar);

		// ���̕����C���f�b�N�X�Ɉڍs
		m_nNextIdx++;

		if (useful::LimitMaxNum(m_nNextIdx, GetNumChar() - 1))
		{ // �Ō�̕����ɓ��B�����ꍇ

			// ���݂̑ҋ@���Ԃ�������
			m_fCurTime = 0.0f;

			// ���������OFF�ɂ���
			m_bScroll = false;

			break;
		}
	}
}

//============================================================
//	����������ʉ��̍Đ�����
//============================================================
void CScrollString2D::PlayScrollSE(CChar2D* pChar2D)
{
	// ���x�����w��Ȃ��̏ꍇ������
	if (m_labelSE == CSound::LABEL_NONE) { return; }

	// �e�N�X�`���������ȏꍇ������
	if (pChar2D->IsTexEmpty()) { return; }

	// �w�胉�x����SE���Đ�
	PLAY_SOUND(m_labelSE);
}
