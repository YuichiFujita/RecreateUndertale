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
#include "manager.h"
#include "string2D.h"
#include "char2D.h"

//************************************************************
//	�q�N���X [CScrollText2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CScrollText2D::CScrollText2D() :
	m_labelSE	(CSound::LABEL_NONE),	// ��������Đ�SE���x��
	m_nNextIdx	(0),	// ���\�����镶���C���f�b�N�X
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
HRESULT CScrollText2D::Init()
{
	// �����o�ϐ���������
	m_labelSE	= CSound::LABEL_NONE;	// ��������Đ�SE���x��
	m_nNextIdx	= 0;		// ���\�����镶���C���f�b�N�X
	m_fNextTime	= 0.0f;		// ���\������܂ł̎���
	m_fCurTime	= 0.0f;		// ���݂̑ҋ@����
	m_bScroll	= false;	// ���������

	// �S�������z���������
	m_vecChar.clear();

	// �e�L�X�g2D�̏�����
	if (FAILED(CText2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CScrollText2D::Uninit()
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
void CScrollText2D::Draw(CShader* pShader)
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
	m_nNextIdx = (bDraw) ? (int)m_vecChar.size() - 1 : 0;	// ON�Ȃ�Ō���AOFF�Ȃ�擪

	// ���݂̑ҋ@���Ԃ�������
	m_fCurTime = 0.0f;

	// �`��󋵂̐ݒ�
	CText2D::SetEnableDraw(bDraw);
}

//============================================================
//	������̐擪�ǉ����� (�}���`�o�C�g������)
//============================================================
HRESULT CScrollText2D::PushFrontString(const std::string& rStr)
{
	// ����������C�h�ϊ�
	std::wstring wsStr = useful::MultiByteToWide(rStr);

	// �������擪�ɒǉ�
	if (FAILED(PushFrontString(wsStr)))
	{ // �ǉ��Ɏ��s�����ꍇ

		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	������̐擪�ǉ����� (���C�h������)
//============================================================
HRESULT CScrollText2D::PushFrontString(const std::wstring& rStr)
{
	// �������擪�ɒǉ�
	if (FAILED(CText2D::PushFrontString(rStr)))
	{ // �ǉ��Ɏ��s�����ꍇ

		return E_FAIL;
	}

	CString2D* pHeadStr = GetString2D(0);	// �擪�̕�������
	std::vector<CChar2D*> vecAdd;

	// �擪������̎����`���OFF�ɂ���
	pHeadStr->SetEnableDraw(false);

	// ��������̕�����z��ɒǉ�
	int nNumChar = pHeadStr->GetNumChar();	// ������
	for (int nCntChar = 0; nCntChar < nNumChar; nCntChar++)
	{ // ���������J��Ԃ�

		// �Ō���ɕ����A�h���X��ǉ�
		vecAdd.push_back(pHeadStr->GetChar2D(nCntChar));
	}

	// �����o�ϐ��̕����z��ɍ쐬���������z���ǉ�
	m_vecChar.reserve((int)m_vecChar.size() + nNumChar);				// �e�ʂ����炩���ߊm��
	m_vecChar.insert(m_vecChar.begin(), vecAdd.begin(), vecAdd.end());	// �擪�ɂ܂Ƃ߂đ}��

	return S_OK;
}

//============================================================
//	������̍Ō���ǉ����� (�}���`�o�C�g������)
//============================================================
HRESULT CScrollText2D::PushBackString(const std::string& rStr)
{
	// ����������C�h�ϊ�
	std::wstring wsStr = useful::MultiByteToWide(rStr);

	// ��������Ō���ɒǉ�
	if (FAILED(PushBackString(wsStr)))
	{ // �ǉ��Ɏ��s�����ꍇ

		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	������̍Ō���ǉ����� (���C�h������)
//============================================================
HRESULT CScrollText2D::PushBackString(const std::wstring& rStr)
{
	// ��������Ō���ɒǉ�
	if (FAILED(CText2D::PushBackString(rStr)))
	{ // �ǉ��Ɏ��s�����ꍇ

		return E_FAIL;
	}

	int nTailStrIdx = GetNumString() - 1;			// �Ō���̕�����C���f�b�N�X
	CString2D* pTailStr = GetString2D(nTailStrIdx);	// �Ō���̕�������

	// �Ō��������̎����`���OFF�ɂ���
	pTailStr->SetEnableDraw(false);

	// ��������̕�����z��ɒǉ�
	int nNumChar = pTailStr->GetNumChar();	// ������
	for (int nCntChar = 0; nCntChar < nNumChar; nCntChar++)
	{ // ���������J��Ԃ�

		// �Ō���ɕ����A�h���X��ǉ�
		m_vecChar.push_back(pTailStr->GetChar2D(nCntChar));
	}

	return S_OK;
}

//============================================================
//	������̍폜����
//============================================================
void CScrollText2D::DeleteString(const int nStrIdx)
{
	int nDelHead = 0;	// �폜����擪�����C���f�b�N�X
	for (int i = 0; i < nStrIdx; i++)
	{ // �폜���镶����̎�O�܂ŌJ��Ԃ�

		// �폜���镶���̐擪�C���f�b�N�X�܂Œl��i�߂�
		nDelHead += GetString2D(i)->GetNumChar();
	}

	// �폜����C�e���[�^�[�̐擪�����߂�
	auto itrDelHead = m_vecChar.begin();	// �폜����擪�C�e���[�^�[
	std::advance(itrDelHead, nDelHead);		// �擪�܂Ői�߂�

	// �폜����C�e���[�^�[�̍Ō�������߂�
	auto itrDelTail = m_vecChar.begin();	// �폜����Ō���C�e���[�^�[
	std::advance(itrDelTail, nDelHead + GetString2D(nStrIdx)->GetNumChar());	// �Ō���܂Ői�߂�

	// �擪����Ō���܂ł̃C�e���[�^�[���폜
	m_vecChar.erase(itrDelHead, itrDelTail);

	// ������̍폜
	CText2D::DeleteString(nStrIdx);

	// �����C���f�b�N�X�𐧌�����
	useful::LimitMaxNum(m_nNextIdx, (int)m_vecChar.size());
}

//============================================================
//	������̑S�폜����
//============================================================
void CScrollText2D::DeleteStringAll()
{
	// ������̑S�폜
	CText2D::DeleteStringAll();

	// �S�������z����N���A
	m_vecChar.clear();

	// �����C���f�b�N�X��������
	m_nNextIdx = 0;
}

//============================================================
//	��������
//============================================================
CScrollText2D* CScrollText2D::Create
(
	const std::string& rFilePath,	// �t�H���g�p�X
	const bool bItalic,				// �C�^���b�N
	const VECTOR3& rPos,			// ���_�ʒu
	const float fNextTime,			// �����\���̑ҋ@����
	const float fCharHeight,		// �����c��
	const float fLineHeight,		// �s�ԏc��
	const EAlignX alignX,			// ���z�u
	const EAlignY alignY,			// �c�z�u
	const VECTOR3& rRot,			// ���_����
	const COLOR& rCol				// �F
)
{
	// ��������e�L�X�g2D�̐���
	CScrollText2D* pScrollText2D = new CScrollText2D;
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
		pScrollText2D->SetFont(rFilePath, bItalic);

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
//	��������I���󋵂̎擾����
//============================================================
bool CScrollText2D::IsEndScroll() const
{
	// �I�[�����̎����`��t���O���當������̏I���𔻒肷��
	return m_vecChar.back()->IsDraw();
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
		assert(m_vecChar[m_nNextIdx] != nullptr);
		m_vecChar[m_nNextIdx]->SetEnableDraw(true);

		// ���݂̑ҋ@���Ԃ���ҋ@���Ԃ����Z
		m_fCurTime -= m_fNextTime;

		// �������蒆�̌��ʉ����Đ�
		PlayScrollSE(m_vecChar[m_nNextIdx]);

		// ���̕����C���f�b�N�X�Ɉڍs
		m_nNextIdx++;

		if (useful::LimitMaxNum(m_nNextIdx, (int)m_vecChar.size() - 1))
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
void CScrollText2D::PlayScrollSE(CChar2D* pChar2D)
{
	// ���x�����w��Ȃ��̏ꍇ������
	if (m_labelSE == CSound::LABEL_NONE) { return; }

	// �e�N�X�`���������ȏꍇ������
	if (pChar2D->IsTexEmpty()) { return; }

	// �w�胉�x����SE���Đ�
	PLAY_SOUND(m_labelSE);
}
