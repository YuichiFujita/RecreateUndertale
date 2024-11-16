//============================================================
//
//	�v���C���[�A�C�e������ [playerItem.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "playerItem.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{

}

//************************************************************
//	�\���� [SPlayerItem] �̃����o�֐�
//************************************************************
//============================================================
//	�A�C�e���̒ǉ�����
//============================================================
bool SPlayerItem::PushBackItem(const int nItemIdx)
{
	// �A�C�e��������ȏ㎝�ĂȂ��ꍇ������
	if (SPlayerItem::MAX_ITEM >= GetNumItem()) { return false; }

	// �Ō���Ɉ����̃A�C�e���C���f�b�N�X��ǉ�
	m_vecItemIdx.push_back(nItemIdx);
	return true;
}

//============================================================
//	�A�C�e���̍폜����
//============================================================
bool SPlayerItem::DeleteItem(const int nBagIdx)
{
	// �����A�C�e�����͈̔͊O�C���f�b�N�X�Ȃ甲����
	if (nBagIdx > GetNumItem()) { return false; }

	// �����o�b�O�C���f�b�N�X�̃A�C�e�����폜
	m_vecItemIdx.erase(m_vecItemIdx.begin() + nBagIdx);
	return true;
}

//============================================================
//	�A�C�e���̃C���f�b�N�X�擾����
//============================================================
int SPlayerItem::GetItemIdx(const int nBagIdx)
{
	// �����A�C�e�����͈̔͊O�C���f�b�N�X�Ȃ甲����
	if (nBagIdx > GetNumItem()) { return NONE_IDX; }

	// �����o�b�O�C���f�b�N�X�̃A�C�e����Ԃ�
	return m_vecItemIdx[nBagIdx];
}

//============================================================
//	�A�C�e���̃C���f�b�N�X���֏���
//============================================================
bool SPlayerItem::SwapItemIdx(int* pItemIdx, const int nBagIdx)
{
	// �����A�C�e�����͈̔͊O�C���f�b�N�X�Ȃ甲����
	if (nBagIdx > GetNumItem()) { return false; }

	// �A�C�e���C���f�b�N�X�̓���ւ�
	int nTemp = *pItemIdx;
	*pItemIdx = m_vecItemIdx[nBagIdx];
	m_vecItemIdx[nBagIdx] = nTemp;

	return true;
}
