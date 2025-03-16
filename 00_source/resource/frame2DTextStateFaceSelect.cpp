//============================================================
//
//	�\��/�I��t���e�L�X�g��ԏ��� [frame2DTextStateFaceSelect.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateFaceSelect.h"
#include "frame2DModuleText.h"
#include "frame2DTextBuffer.h"
#include "faceUI.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	namespace text
	{
		const VECTOR3 OFFSET[] =	// �e�L�X�g�I�t�Z�b�g�v���Z�b�g
		{
			VECTOR3(-210.0f, -80.0f, 0.0f)	// �����z�u
		};
	}

	namespace face
	{
		const VECTOR3 OFFSET[] =	// �\��I�t�Z�b�g�v���Z�b�g
		{
			VECTOR3(315.0f, 0.0f, 0.0f)	// �����z�u
		};
		const char*	FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC		= false;		// �C�^���b�N
		const EAlignX ALIGN_X	= XALIGN_LEFT;	// ���z�u
		const EAlignY ALIGN_Y	= YALIGN_TOP;	// �c�z�u
	}
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(face::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	�q�N���X [CFrame2DTextStateFaceSelect] �̃����o�֐�
//************************************************************
//============================================================
//	�ڏ��R���X�g���N�^ (�f�t�H���g)
//============================================================
CFrame2DTextStateFaceSelect::CFrame2DTextStateFaceSelect() : CFrame2DTextStateFaceSelect(VEC3_ZERO, VEC3_ZERO, VEC3_ZERO, VEC3_ZERO)
{

}

//============================================================
//	�R���X�g���N�^ (�z�u�w��)
//============================================================
CFrame2DTextStateFaceSelect::CFrame2DTextStateFaceSelect(const VECTOR3& rOffsetText, const VECTOR3& rOffsetSelectL, const VECTOR3& rOffsetSelectR, const VECTOR3& rOffsetFace) : CFrame2DTextStateSelect(rOffsetText, rOffsetSelectL, rOffsetSelectR),
	m_pFace			(nullptr),		// �\����
	m_offset		(rOffsetFace),	// �\��I�t�Z�b�g
	m_nTypeTalkEmo	(0),			// ��b���̕\����
	m_nTypeIdolEmo	(0)				// �ҋ@���̕\����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextStateFaceSelect::~CFrame2DTextStateFaceSelect()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFrame2DTextStateFaceSelect::Init()
{
	// �����o�ϐ���������
	m_pFace			= nullptr;	// �\����
	m_nTypeTalkEmo	= 0;		// ��b���̕\����
	m_nTypeIdolEmo	= 0;		// �ҋ@���̕\����

	// �e�N���X�̏�����
	if (FAILED(CFrame2DTextStateSelect::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	CFrame2D::EPreset preset = m_pContext->GetFramePreset();	// �t���[���z�u�v���Z�b�g
	if (preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX)
	{ // �v���Z�b�g���͈͓��̏ꍇ

		// �e�L�X�g�I�t�Z�b�g�̐ݒ�
		SetOffset(GetPresetOffset(preset));

		// ��I�t�Z�b�g�̐ݒ�
		m_offset = face::OFFSET[preset];
	}

	// �\��̐���
	m_pFace = CFaceUI::Create(0, 0, VEC3_ZERO);
	if (m_pFace == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pFace->SetPriority(m_pContext->GetFramePriority());

	// ���Έʒu�̐ݒ�
	CFrame2DTextStateFaceSelect::SetPositionRelative();	// ���g�̑��Έʒu

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFrame2DTextStateFaceSelect::Uninit()
{
	// �\��̏I��
	SAFE_UNINIT(m_pFace);

	// �e�N���X�̏I��
	CFrame2DTextStateSelect::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CFrame2DTextStateFaceSelect::Update(const float fDeltaTime)
{
	// �O��̃��[�v����ۑ�
	int nOldNumLoop = m_pFace->GetLoopAnim();

	// �\��̍X�V
	m_pFace->Update(fDeltaTime);

	if (m_pFace->GetEmotion() != m_nTypeIdolEmo)
	{ // �\��ύX�O�̏ꍇ

		if (IsTextEndScroll() && m_pFace->GetLoopAnim() > nOldNumLoop)
		{ // �������肪�I�����Ă��銎�A���[�v���X�V���ꂽ�ꍇ

			// �ҋ@�\��̐ݒ�
			m_pFace->SetEmotion(m_nTypeIdolEmo);
		}
	}

	// �e�N���X�̍X�V
	CFrame2DTextStateSelect::Update(fDeltaTime);
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CFrame2DTextStateFaceSelect::SetPriority(const int nPriority)
{
	// �\��̗D�揇�ʂ�ݒ�
	m_pFace->SetPriority(nPriority);

	// �e�N���X�̗D�揇�ʂ�ݒ�
	CFrame2DTextStateSelect::SetPriority(nPriority);
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFrame2DTextStateFaceSelect::SetVec3Position(const VECTOR3& rPos)
{
	// �e�N���X�̈ʒu��ݒ�
	CFrame2DTextStateSelect::SetVec3Position(rPos);
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFrame2DTextStateFaceSelect::SetVec3Rotation(const VECTOR3& rRot)
{
	// �\��̌�����ݒ�
	m_pFace->SetVec3Rotation(rRot);

	// �e�N���X�̌�����ݒ�
	CFrame2DTextStateSelect::SetVec3Rotation(rRot);
}

//============================================================
//	�e�L�X�g���ۑ��o�b�t�@�̊�������
//============================================================
void CFrame2DTextStateFaceSelect::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// �\��/�I��t���e�L�X�g�ۑ��o�b�t�@�ɕϊ��ł��Ȃ��ꍇ������
	CFrame2DTextBufferFaceSelect* pBuffFaceSelect = pBuffer->GetBufferFaceSelect();
	if (pBuffFaceSelect == nullptr) { assert(false); return; }

	// ����̊���
	m_pFace->BindFaceData(pBuffFaceSelect->m_nIdxFace);

	// �\���ނ̕ۑ�
	m_nTypeTalkEmo = pBuffFaceSelect->m_nTypeTalkEmo;	// ��b��
	m_nTypeIdolEmo = pBuffFaceSelect->m_nTypeIdolEmo;	// �ҋ@��

	// �����\��̐ݒ�
	m_pFace->SetEmotion(m_nTypeTalkEmo);	// ��b�\���n�߂�

	// �e�N���X�̃e�L�X�g���ۑ��o�b�t�@�̊���
	CFrame2DTextStateSelect::BindTextBuffer(pBuffer);
}

//============================================================
//	�v���Z�b�g�I�t�Z�b�g�̎擾����
//============================================================
VECTOR3 CFrame2DTextStateFaceSelect::GetPresetOffset(const CFrame2D::EPreset preset)
{
	// �v���Z�b�g�͈͊O�G���[
	assert(preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX);

	// �����v���Z�b�g�̃I�t�Z�b�g��Ԃ�
	return text::OFFSET[preset];
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CFrame2DTextStateFaceSelect::SetPositionRelative()
{
	// �e�N���X�̑��Έʒu�̐ݒ�
	CFrame2DTextStateSelect::SetPositionRelative();

	if (m_pFace != nullptr)
	{ // �\������ς݂̏ꍇ

		VECTOR3 posFrame = m_pContext->GetFramePosition();	// �t���[���ʒu
		VECTOR3 rotFrame = m_pContext->GetFrameRotation();	// �t���[������

		// X���W�I�t�Z�b�g�����炷
		posFrame.x -= sinf(rotFrame.z + HALF_PI) * m_offset.x;
		posFrame.y -= cosf(rotFrame.z + HALF_PI) * m_offset.x;

		// Y���W�I�t�Z�b�g�����炷
		posFrame.x += sinf(rotFrame.z) * m_offset.y;
		posFrame.y += cosf(rotFrame.z) * m_offset.y;

		// �\��ʒu�̔��f
		m_pFace->SetVec3Position(posFrame);
		m_pFace->SetVec3Rotation(rotFrame);
	}
}
