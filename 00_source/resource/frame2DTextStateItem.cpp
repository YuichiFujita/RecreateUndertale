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
#include "manager.h"
#include "item.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const std::string CMD_NAME = "/name";	// ������𖼑O�ɒu��������R�}���h
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

//============================================================
//	�e�L�X�g���ۑ��o�b�t�@�̊�������
//============================================================
void CFrame2DTextStateItem::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// �A�C�e���e�L�X�g�ۑ��o�b�t�@�ɕϊ��ł��Ȃ��ꍇ������
	CFrame2DTextBufferItem* pBuffItem = pBuffer->GetBufferItem();
	if (pBuffItem == nullptr) { assert(false); return; }

	// �e�L�X�g�p�X����A�C�e����������
	CItem* pItem = GET_MANAGER->GetItem();
	const CItemData& rItemData = pItem->GetInfo(pBuffItem->m_sPath);

	// ���e�L�X�g�̌����L�[������
	SetNextTextKey(pBuffItem->m_sNextTextKey);

	// �e�L�X�g��������
	int nNumStr = (int)pBuffItem->m_text.size();	// ������
	for (int i = 0; i < nNumStr; i++)
	{ // �����񐔕��J��Ԃ�

		// ��������̃R�}���h��u��
		ReplaceCommand(&pBuffItem->m_text[i], rItemData);

		// ��������Ō���ɒǉ�
		PushBackString(pBuffItem->m_text[i]);
	}

	// ����������J�n����
	SetTextEnableScroll(true);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	��������̃R�}���h�̒u������
//============================================================
void CFrame2DTextStateItem::ReplaceCommand(std::string* pStr, const CItemData& rItem)
{
	// ���O�ϊ��R�}���h�̌���
	size_t idxName = pStr->find(CMD_NAME);
	if (idxName != std::string::npos)
	{ // �R�}���h�����݂����ꍇ

		// �A�C�e�����ɕϊ�����
		pStr->replace(idxName, CMD_NAME.length(), rItem.GetName());
	}
}
