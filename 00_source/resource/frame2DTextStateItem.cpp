//============================================================
//
//	�A�C�e���e�L�X�g��ԏ��� [frame2DTextStateItem.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateItem.h"
#include "frame2DModuleText.h"
#include "frame2DTextBuffer.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{

}

//************************************************************
//	�q�N���X [CFrame2DTextStateItem] �̃����o�֐�
//************************************************************
//============================================================
//	�ڏ��R���X�g���N�^ (�f�t�H���g)
//============================================================
CFrame2DTextStateItem::CFrame2DTextStateItem() : CFrame2DTextStateItem(VEC3_ZERO)
{

}

//============================================================
//	�R���X�g���N�^ (�z�u�v���Z�b�g)
//============================================================
CFrame2DTextStateItem::CFrame2DTextStateItem(const CFrame2D::EPreset preset) : CFrame2DTextStateText(preset)
{

}

//============================================================
//	�R���X�g���N�^ (�z�u�w��)
//============================================================
CFrame2DTextStateItem::CFrame2DTextStateItem(const VECTOR3& rOffset) : CFrame2DTextStateText(rOffset)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextStateItem::~CFrame2DTextStateItem()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFrame2DTextStateItem::Init()
{
	// �e�N���X�̏�����
	if (FAILED(CFrame2DTextStateText::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// ���Έʒu�̐ݒ�
	CFrame2DTextStateItem::SetPositionRelative();	// ���g�̑��Έʒu

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFrame2DTextStateItem::Uninit()
{
	// �e�N���X�̏I��
	CFrame2DTextStateText::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CFrame2DTextStateItem::Update(const float fDeltaTime)
{
	// �e�N���X�̍X�V
	CFrame2DTextStateText::Update(fDeltaTime);
}
