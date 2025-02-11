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
			const float OFFSET_X[] =	// �e�L�X�g�I�t�Z�b�g�v���Z�b�g
			{
				-160.0f,	// �����z�u
			};
		}
		namespace R
		{
			const float OFFSET_X[] =	// �e�L�X�g�I�t�Z�b�g�v���Z�b�g
			{
				160.0f,		// �����z�u
			};
		}

		const char*	FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC		= false;		// �C�^���b�N
		const EAlignX ALIGN_X	= XALIGN_LEFT;	// ���z�u
		const EAlignY ALIGN_Y	= YALIGN_TOP;	// �c�z�u
	}

	namespace soul
	{
		const char* PATH	= "data\\TEXTURE\\spr_heartsmall.png";	// �\�E���J�[�\���e�N�X�`���p�X
		const float OFFSET	= 10.0f;								// �\�E���J�[�\���I�t�Z�b�g
		const VECTOR3 SIZE	= VECTOR3(26.5f, 26.5f, 0.0f);			// �\�E���J�[�\���傫��
	}
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CFrame2DTextStateSelect::AFuncOffset CFrame2DTextStateSelect::m_aFuncOffset[][SELECT_MAX] =	// �I�t�Z�b�g�擾�֐����X�g
{
	{ &CFrame2DTextStateSelect::GetOffsetDownLeft, &CFrame2DTextStateSelect::GetOffsetDownRight },	// �����z�u�I�t�Z�b�g
};

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(select::L::OFFSET_X) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");
static_assert(NUM_ARRAY(select::R::OFFSET_X) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	�q�N���X [CFrame2DTextStateSelect] �̃����o�֐�
//************************************************************
//============================================================
//	�ڏ��R���X�g���N�^ (�f�t�H���g)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect() : CFrame2DTextStateSelect(VEC3_ZERO, VEC3_ZERO, VEC3_ZERO)
{
	// �X�^�e�B�b�N�A�T�[�g
	static_assert(NUM_ARRAY(m_aFuncOffset) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");
}

//============================================================
//	�R���X�g���N�^ (�z�u�v���Z�b�g)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect(const CFrame2D::EPreset preset) : CFrame2DTextStateText(preset),
	m_sCutTextPath	(""),		// ���݃e�L�X�g�̕ۑ��p�X
	m_pSoul			(nullptr),	// �\�E���J�[�\�����
	m_nCurSelect	(0)			// ���݂̑I����
{
	// �����o�ϐ����N���A
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		m_aNextPath[i]	 = "";		// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
		m_aNextBoxKey[i] = "";		// ���e�L�X�g�{�b�N�X�̌����L�[
		m_aNextKey[i]	 = "";		// �e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[
		m_apSelect[i]	 = nullptr;	// �I�������
	}
	m_aOffset[SELECT_LEFT]	= GetPresetOffset(SELECT_LEFT, preset);		// ���I�����I�t�Z�b�g
	m_aOffset[SELECT_RIGHT]	= GetPresetOffset(SELECT_RIGHT, preset);	// �E�I�����I�t�Z�b�g
}

//============================================================
//	�R���X�g���N�^ (�z�u�w��)
//============================================================
CFrame2DTextStateSelect::CFrame2DTextStateSelect(const VECTOR3& rOffsetText, const VECTOR3& rOffsetSelectL, const VECTOR3& rOffsetSelectR) : CFrame2DTextStateText(rOffsetText),
	m_sCutTextPath	(""),		// ���݃e�L�X�g�̕ۑ��p�X
	m_pSoul			(nullptr),	// �\�E���J�[�\�����
	m_nCurSelect	(0)			// ���݂̑I����
{
	// �����o�ϐ����N���A
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		m_aNextPath[i]	 = "";		// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
		m_aNextBoxKey[i] = "";		// ���e�L�X�g�{�b�N�X�̌����L�[
		m_aNextKey[i]	 = "";		// �e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[
		m_apSelect[i]	 = nullptr;	// �I�������
	}
	m_aOffset[SELECT_LEFT]	= rOffsetSelectL;	// ���I�����I�t�Z�b�g
	m_aOffset[SELECT_RIGHT]	= rOffsetSelectR;	// �E�I�����I�t�Z�b�g
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
	m_sCutTextPath	= "NONE";	// ���݃e�L�X�g�̕ۑ��p�X
	m_pSoul			= nullptr;	// �\�E���J�[�\�����
	m_nCurSelect	= 0;		// ���݂̑I����
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		m_aNextPath[i]	 = "NONE";	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
		m_aNextBoxKey[i] = "NONE";	// ���e�L�X�g�{�b�N�X�̌����L�[
		m_aNextKey[i]	 = "NONE";	// �e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[
		m_apSelect[i]	 = nullptr;	// �I�������
	}

	// TODO�F�����ő��̃L�[���̏����l��ݒ�
	// TODO�F����Ƒ��̃L�[�������ł͉��̕��������Ă邩���m�F

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
			select::FONT,						// �t�H���g�p�X
			select::ITALIC,						// �C�^���b�N
			VEC3_ZERO,							// ���_�ʒu
			CFrame2DTextStateText::WAIT_TIME,	// �����\���̑ҋ@����
			CFrame2DTextStateText::CHAR_HEIGHT,	// �����c��
			CFrame2DTextStateText::LINE_HEIGHT,	// �s�ԏc��
			select::ALIGN_X,					// ���z�u
			select::ALIGN_Y						// �c�z�u
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

		// ��������̍X�V
		UpdateScroll();
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
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̗D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(nPriority);
	}

	// �\�E���J�[�\���̗D�揇�ʂ�ݒ�
	m_pSoul->SetPriority(nPriority);

	// �e�N���X�̗D�揇�ʂ�ݒ�
	CFrame2DTextStateText::SetPriority(nPriority);
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFrame2DTextStateSelect::SetVec3Position(const VECTOR3& rPos)
{
	// �e�N���X�̈ʒu��ݒ�
	CFrame2DTextStateText::SetVec3Position(rPos);
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFrame2DTextStateSelect::SetVec3Rotation(const VECTOR3& rRot)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̌�����ݒ�
		m_apSelect[i]->SetVec3Rotation(rRot);
	}

	// �\�E���J�[�\���̌�����ݒ�
	m_pSoul->SetVec3Rotation(rRot);

	// �e�N���X�̌�����ݒ�
	CFrame2DTextStateText::SetVec3Rotation(rRot);
}

//============================================================
//	�e�L�X�g���ۑ��o�b�t�@�̊�������
//============================================================
void CFrame2DTextStateSelect::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// �I��t���e�L�X�g�ۑ��o�b�t�@�ɕϊ��ł��Ȃ��ꍇ������
	CFrame2DTextBufferSelect* pBuffSelect = pBuffer->GetBufferSelect();
	if (pBuffSelect == nullptr) { assert(false); return; }

	// ���蓖�Ă�e�L�X�g�̌����L�[��ۑ�
	SetCurTextKey(pBuffer->m_sKey);

	// ���蓖�Ă�e�L�X�g�̕ۑ��p�X��ۑ�
	m_sCutTextPath = pBuffer->m_sPath;

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̎��ʏ�������
		m_aNextPath[i]	 = pBuffSelect->m_aNextPath[i];		// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
		m_aNextBoxKey[i] = pBuffSelect->m_aNextBoxKey[i];	// ���e�L�X�g�{�b�N�X�̌����L�[
		m_aNextKey[i]	 = pBuffSelect->m_aNextKey[i];		// �e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[

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
//	�v���Z�b�g�I�t�Z�b�g�̎擾����
//============================================================
VECTOR3 CFrame2DTextStateSelect::GetPresetOffset(const ESelect select, const CFrame2D::EPreset preset)
{
	// �v���Z�b�g�͈͊O�G���[
	assert(preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX);

	// �����v���Z�b�g�̃I�t�Z�b�g��Ԃ�
	return (this->*(m_aFuncOffset[preset][select]))();
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CFrame2DTextStateSelect::SetPositionRelative()
{
	// �e�N���X�̑��Έʒu�̐ݒ�
	CFrame2DTextStateText::SetPositionRelative();

	CFrame2D::EPreset preset = m_pContext->GetFramePreset();	// �t���[���v���Z�b�g
	if (preset != CFrame2D::PRESET_NONE)
	{ // �v���Z�b�g���w�肳��Ă���ꍇ

		for (int i = 0; i < SELECT_MAX; i++)
		{ // �I�����̑������J��Ԃ�

			// �I�t�Z�b�g���X�V
			m_aOffset[i] = GetPresetOffset((ESelect)i, preset);
		}
	}

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

	// X���W�I�t�Z�b�g�����炷
	VECTOR3 posCursor = m_apSelect[m_nCurSelect]->GetVec3Position();
	posCursor.x -= sinf(rotFrame.z + HALF_PI) * soul::OFFSET;
	posCursor.y -= cosf(rotFrame.z + HALF_PI) * soul::OFFSET;

	// Y���W�I�t�Z�b�g�����炷
	float fOffsetY = m_apSelect[m_nCurSelect]->GetCharHeight() * 0.5f;
	posCursor.x += sinf(rotFrame.z) * fOffsetY;
	posCursor.y += cosf(rotFrame.z) * fOffsetY;

	// �\�E���J�[�\���ʒu�̔��f
	m_pSoul->SetVec3Position(posCursor);
}

//============================================================
//	��������̍X�V����
//============================================================
void CFrame2DTextStateSelect::UpdateScroll()
{
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
	// ���葀�삪����Ă��Ȃ��ꍇ������
	if (!input::Decide()) { return; }

	if (m_aNextPath[m_nCurSelect] == "-1"
	||  m_aNextPath[m_nCurSelect] == "NONE"
	||  m_aNextPath[m_nCurSelect].empty())
	{ // �e�L�X�g�J�ڐ悪����p�X�ɂ���ꍇ

		if (m_aNextBoxKey[m_nCurSelect] == "-1"
		||  m_aNextBoxKey[m_nCurSelect] == "NONE"
		||  m_aNextBoxKey[m_nCurSelect].empty())
		{ // �e�L�X�g�{�b�N�X�����L�[�̎w�肪�Ȃ��ꍇ

			// �e�L�X�g�̑J��
			m_pContext->TransText(m_aNextKey[m_nCurSelect]);	// �J�ڑO�Ɠ���̃e�L�X�g�o�b�t�@�A�z�z����g�p
		}
		else
		{ // �e�L�X�g�{�b�N�X�����L�[�̎w�肪����ꍇ

			// �e�L�X�g�{�b�N�X�̓Ǎ�
			m_pContext->LoadTextBox
			( // ����
				m_sCutTextPath,				// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
				m_aNextBoxKey[m_nCurSelect]	// ���e�L�X�g�{�b�N�X�̌����L�[
			);

			// �e�L�X�g�̊���
			m_pContext->BindText(m_aNextKey[m_nCurSelect]);
		}
	}
	else
	{ // �e�L�X�g�J�ڐ悪�ʃp�X�ɂ���ꍇ

		// �e�L�X�g�{�b�N�X�̓Ǎ�
		m_pContext->LoadTextBox
		( // ����
			m_aNextPath[m_nCurSelect],	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
			m_aNextBoxKey[m_nCurSelect]	// ���e�L�X�g�{�b�N�X�̌����L�[
		);

		// �e�L�X�g�̊���
		m_pContext->BindText(m_aNextKey[m_nCurSelect]);
	}
}

//============================================================
//	�I�����̍ő�s���̎擾����
//============================================================
int CFrame2DTextStateSelect::GetMaxSelectLine()
{
	int nMaxNumLine = 0;	// �ő�̍s��
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I�������������̏ꍇ����
		if (m_apSelect[i] == nullptr) { continue; }

		int nNumLine = m_apSelect[i]->GetNumString();	// ���݂̍s��
		if (nMaxNumLine < nNumLine)
		{ // ��葽���s���̏ꍇ

			// �s����ۑ�
			nMaxNumLine = nNumLine;
		}
	}

	// �ő�̍s����Ԃ�
	return nMaxNumLine;
}

//============================================================
//	�������z�u�I�t�Z�b�g�̎擾����
//============================================================
VECTOR3 CFrame2DTextStateSelect::GetOffsetDownLeft()
{
	// �I�t�Z�b�g�̌v�Z
	VECTOR3 offset;
	offset.x = select::L::OFFSET_X[CFrame2D::PRESET_DOWN];
	offset.y = GetPresetOffset(CFrame2D::PRESET_DOWN).y + CFrame2DTextStateText::LINE_HEIGHT * (float)(3 - GetMaxSelectLine());

	// �I�t�Z�b�g��Ԃ�
	return offset;
}

//============================================================
//	�E�����z�u�I�t�Z�b�g�̎擾����
//============================================================
VECTOR3 CFrame2DTextStateSelect::GetOffsetDownRight()
{
	// �I�t�Z�b�g�̌v�Z
	VECTOR3 offset;
	offset.x = select::R::OFFSET_X[CFrame2D::PRESET_DOWN];
	offset.y = GetPresetOffset(CFrame2D::PRESET_DOWN).y + CFrame2DTextStateText::LINE_HEIGHT * (float)(3 - GetMaxSelectLine());

	// �I�t�Z�b�g��Ԃ�
	return offset;
}
