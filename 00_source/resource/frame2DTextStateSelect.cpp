//============================================================
//
//	�I��t���e�L�X�g��ԏ��� [frame2DTextStateSelect.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateSelect.h"
#include "frame2DModuleText.h"
#include "frame2DTextBuffer.h"
#include "manager.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	namespace select
	{
		namespace L
		{
			const VECTOR3 OFFSET[] =	// �e�L�X�g�I�t�Z�b�g�v���Z�b�g
			{
				VECTOR3(-160.0f, -80.0f + 54.0f * 2.0f, 0.0f)	// �����z�u
			};
		}

		namespace R
		{
			const VECTOR3 OFFSET[] =	// �e�L�X�g�I�t�Z�b�g�v���Z�b�g
			{
				VECTOR3(160.0f, -80.0f + 54.0f * 2.0f, 0.0f)	// �����z�u
			};
		}

		const char*	FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const int	PRIORITY	= 6;				// �e�L�X�g�̗D�揇��
		const bool	ITALIC		= false;			// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;			// �����c��
		const float	LINE_HEIGHT	= 54.0f;			// �s�ԏc��
		const float	WAIT_TIME	= 0.045f;			// �����\���̑ҋ@����
		const EAlignX ALIGN_X	= XALIGN_CENTER;	// ���z�u
		const EAlignY ALIGN_Y	= YALIGN_TOP;		// �c�z�u
	}

	namespace soul
	{
		const char* PATH	= "data\\TEXTURE\\spr_heartsmall.png";	// �\�E���J�[�\���e�N�X�`���p�X
		const float OFFSET	= 10.0f;								// �\�E���J�[�\���I�t�Z�b�g
		const VECTOR3 SIZE	= VECTOR3(26.5f, 26.5f, 0.0f);			// �\�E���J�[�\���傫��
	}
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(select::L::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");
static_assert(NUM_ARRAY(select::R::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	�q�N���X [CFrame2DTextStateSelect] �̃����o�֐�
//************************************************************
//============================================================
//	�ڏ��R���X�g���N�^ (�f�t�H���g)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect() : CFrame2DTextStateSelect(VEC3_ZERO, VEC3_ZERO, VEC3_ZERO)	// TODO�F�R���X�g���N�^�Q���ꂼ��z�肵�������ɂȂ��Ă��邩����
{

}

//============================================================
//	�R���X�g���N�^ (�z�u�v���Z�b�g)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect(const CFrame2D::EPreset preset) : CFrame2DTextStateText(preset),
	m_pSoul		 (nullptr),	// �\�E���J�[�\�����
	m_nCurSelect (0)		// ���݂̑I����
{
	// �v���Z�b�g�͈͊O�G���[
	assert(preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX);

	// �����o�ϐ����N���A
	m_aOffset[SELECT_LEFT]	= select::L::OFFSET[preset];	// ���I�����I�t�Z�b�g
	m_aOffset[SELECT_RIGHT]	= select::R::OFFSET[preset];	// �E�I�����I�t�Z�b�g
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		m_aNextTextKey[i]	= {};		// ���e�L�X�g�̌����L�[
		m_apSelect[i]		= nullptr;	// �I�������
	}
}

//============================================================
//	�R���X�g���N�^ (�z�u�w��)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect(const VECTOR3& rOffsetText, const VECTOR3& rOffsetSelectL, const VECTOR3& rOffsetSelectR) : CFrame2DTextStateText(rOffsetText),
	m_pSoul		 (nullptr),	// �\�E���J�[�\�����
	m_nCurSelect (0)		// ���݂̑I����
{
	// �����o�ϐ����N���A
	m_aOffset[SELECT_LEFT]	= rOffsetSelectL;	// ���I�����I�t�Z�b�g
	m_aOffset[SELECT_RIGHT]	= rOffsetSelectR;	// �E�I�����I�t�Z�b�g
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		m_aNextTextKey[i]	= {};		// ���e�L�X�g�̌����L�[
		m_apSelect[i]		= nullptr;	// �I�������
	}
}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextStateSelect::~CFrame2DTextStateSelect()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFrame2DTextStateSelect::Init()
{
	// �����o�ϐ���������
	m_pSoul		 = nullptr;	// �\�E���J�[�\�����
	m_nCurSelect = 0;		// ���݂̑I����
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		m_aNextTextKey[i]	= "NONE";	// ���e�L�X�g�̌����L�[
		m_apSelect[i]		= nullptr;	// �I�������
	}

	// �e�N���X�̏�����
	if (FAILED(CFrame2DTextStateText::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	const int nPrioFrame = m_pContext->GetFramePriority();	// �R���e�L�X�g�̗D�揇��
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I�����̐���
		m_apSelect[i] = CScrollText2D::Create
		( // ����
			select::FONT,			// �t�H���g�p�X
			select::ITALIC,			// �C�^���b�N
			VEC3_ZERO,				// ���_�ʒu
			select::WAIT_TIME,		// �����\���̑ҋ@����
			select::CHAR_HEIGHT,	// �����c��
			select::LINE_HEIGHT,	// �s�ԏc��
			select::ALIGN_X,		// ���z�u
			select::ALIGN_Y			// �c�z�u
		);
		if (m_apSelect[i] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(nPrioFrame);

		// �������莞�̍Đ�SE��ݒ�
		m_apSelect[i]->SetScrollSE(CSound::LABEL_SE_TEXT01);
	}

	// �\�E���J�[�\���̐���
	m_pSoul = CObject2D::Create
	( // ����
		VEC3_ZERO,	// �ʒu
		soul::SIZE	// �傫��
	);
	if (m_pSoul == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �\�E���e�N�X�`��������
	m_pSoul->BindTexture(soul::PATH);

	// ���x����ݒ�
	m_pSoul->SetLabel(CObject::LABEL_UI);

	// �D�揇�ʂ�ݒ�
	m_pSoul->SetPriority(nPrioFrame);

	// �J�[�\���̎����`���OFF�ɂ���
	m_pSoul->SetEnableDraw(false);

	// ���Έʒu�̐ݒ�
	CFrame2DTextStateSelect::SetPositionRelative();	// ���g�̑��Έʒu

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFrame2DTextStateSelect::Uninit()
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̏I��
		SAFE_UNINIT(m_apSelect[i]);
	}

	// �\�E���J�[�\���̏I��
	SAFE_UNINIT(m_pSoul);

	// �e�N���X�̏I��
	CFrame2DTextStateText::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CFrame2DTextStateSelect::Update(const float fDeltaTime)
{
	if (!m_pSoul->IsDraw())
	{ // �J�[�\�����\������Ă��Ȃ��ꍇ

		if (input::Decide())
		{
			// ������S�\��������
			SetTextEnableDraw(true);
			m_apSelect[SELECT_LEFT]->SetEnableDraw(true);
			m_apSelect[SELECT_RIGHT]->SetEnableDraw(true);

			// �J�[�\���̎����`���ON�ɂ���
			m_pSoul->SetEnableDraw(true);
			return;
		}

		if (IsTextEndScroll())
		{ // �{���̕������肪�I�������ꍇ

			// ���I�����̕���������J�n
			m_apSelect[SELECT_LEFT]->SetEnableScroll(true);
		}
		else { return; }

		if (m_apSelect[SELECT_LEFT]->IsEndScroll())
		{ // ���I�����̕������肪�I�������ꍇ

			// �E�I�����̕���������J�n
			m_apSelect[SELECT_RIGHT]->SetEnableScroll(true);
		}
		else { return; }

		if (m_apSelect[SELECT_RIGHT]->IsEndScroll())
		{ // �E�I�����̕������肪�I�������ꍇ

			// �J�[�\���̎����`���ON�ɂ���
			m_pSoul->SetEnableDraw(true);
		}
	}
	else
	{ // �J�[�\�����\������Ă���ꍇ

		// �I���̍X�V
		UpdateSelect();

		// ����̍X�V
		UpdateDecide();
	}
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CFrame2DTextStateSelect::SetPriority(const int nPriority)
{
	// �e�N���X�̗D�揇�ʂ�ݒ�
	CFrame2DTextStateText::SetPriority(nPriority);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̗D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(nPriority);
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFrame2DTextStateSelect::SetVec3Position(const VECTOR3& rPos)
{
	// �e�N���X�̈ʒu��ݒ�
	CFrame2DTextStateText::SetVec3Position(rPos);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFrame2DTextStateSelect::SetVec3Rotation(const VECTOR3& rRot)
{
	// �e�N���X�̌�����ݒ�
	CFrame2DTextStateText::SetVec3Rotation(rRot);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̌�����ݒ�
		m_apSelect[i]->SetVec3Rotation(rRot);
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�e�L�X�g���ۑ��o�b�t�@�̊�������
//============================================================
void CFrame2DTextStateSelect::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// �I��t���e�L�X�g�ۑ��o�b�t�@�ɕϊ��ł��Ȃ��ꍇ������
	CFrame2DTextBufferSelect* pBuffSelect = pBuffer->GetBufferSelect();
	if (pBuffSelect == nullptr) { assert(false); return; }

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// ���e�L�X�g�̌����L�[������
		m_aNextTextKey[i] = pBuffSelect->m_aNextTextKey[i];

		// �I�����̃e�L�X�g��������
		int nNumSelect = (int)pBuffSelect->m_aSelect[i].size();	// ������
		for (int j = 0; j < nNumSelect; j++)
		{ // �����񐔕��J��Ԃ�

			// ��������Ō���ɒǉ�
			m_apSelect[i]->PushBackString(pBuffSelect->m_aSelect[i][j]);
		}
	}

	// �e�L�X�g��������
	int nNumStr = (int)pBuffSelect->m_text.size();	// ������
	for (int i = 0; i < nNumStr; i++)
	{ // �����񐔕��J��Ԃ�

		// ��������Ō���ɒǉ�
		PushBackString(pBuffSelect->m_text[i]);
	}

	// ����������J�n����
	SetTextEnableScroll(true);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�e�L�X�g�ύX����
//============================================================
void CFrame2DTextStateSelect::ChangeText(const ESelect select, const AText& rText)
{
	// �������S�č폜
	m_apSelect[select]->DeleteStringAll();

	// �e�L�X�g������
	int nLoop = (int)rText.size();	// ������
	for (int i = 0; i < nLoop; i++)
	{ // ������̐����J��Ԃ�

		// ��������Ō���ɒǉ�
		m_apSelect[select]->PushBackString(rText[i]);
	}

	// ����������J�n����
	m_apSelect[select]->SetEnableScroll(true);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CFrame2DTextStateSelect::SetPositionRelative()
{
	// �e�N���X�̑��Έʒu�̐ݒ�
	CFrame2DTextStateText::SetPositionRelative();

	VECTOR3 posFrame = m_pContext->GetFramePosition();	// �t���[���ʒu
	VECTOR3 rotFrame = m_pContext->GetFrameRotation();	// �t���[������
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		VECTOR3 posSelect = posFrame;	// �I�����ʒu

		// X���W�I�t�Z�b�g�����炷
		posSelect.x += sinf(rotFrame.z + HALF_PI) * m_aOffset[i].x;
		posSelect.y += cosf(rotFrame.z + HALF_PI) * m_aOffset[i].x;

		// Y���W�I�t�Z�b�g�����炷
		posSelect.x += sinf(rotFrame.z) * m_aOffset[i].y;
		posSelect.y += cosf(rotFrame.z) * m_aOffset[i].y;

		// �I�����ʒu�̔��f
		m_apSelect[i]->SetVec3Position(posSelect);
	}

	// �\�E���J�[�\���ʒu���v�Z
	VECTOR3 posCursor = m_apSelect[m_nCurSelect]->GetVec3Position();
	posCursor.x -= m_apSelect[m_nCurSelect]->GetTextWidth() * 0.5f + soul::OFFSET;
	posCursor.y += m_apSelect[m_nCurSelect]->GetCharHeight() * 0.5f;

	// �\�E���J�[�\���ʒu�̔��f
	m_pSoul->SetVec3Position(posCursor);
}

//============================================================
//	�I���̍X�V����
//============================================================
void CFrame2DTextStateSelect::UpdateSelect()
{
	// �I��������
	CInputKeyboard* pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// ���ɑI�������炷
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;

		// ���Έʒu�̐ݒ�
		SetPositionRelative();
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// �E�ɑI�������炷
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;

		// ���Έʒu�̐ݒ�
		SetPositionRelative();
	}
}

//============================================================
//	����̍X�V����
//============================================================
void CFrame2DTextStateSelect::UpdateDecide()
{
	if (input::Decide())
	{
		// �e�L�X�g�̑J��
		m_pContext->TransText(m_aNextTextKey[m_nCurSelect]);
	}
}
