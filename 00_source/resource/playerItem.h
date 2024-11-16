//============================================================
//
//	�v���C���[�A�C�e���w�b�_�[ [playerItem.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PLAYER_ITEM_H_
#define _PLAYER_ITEM_H_

//************************************************************
//	�\���̒�`
//************************************************************
// �v���C���[�A�C�e���\����
struct SPlayerItem
{
public:
	// �萔
	static constexpr int MAX_ITEM = 8;	// �ő�A�C�e����

	// �f�t�H���g�R���X�g���N�^
	SPlayerItem() :
		m_vecItemIdx({})	// �A�C�e���C���f�b�N�X
#if 1	// TODO
	{
		m_vecItemIdx.push_back(0);
		m_vecItemIdx.push_back(1);
		m_vecItemIdx.push_back(2);
		m_vecItemIdx.push_back(3);
		m_vecItemIdx.push_back(4);
		m_vecItemIdx.push_back(5);
	}
#else
	{}
#endif

	// �f�X�g���N�^
	~SPlayerItem() {}

	// �����o�֐�
	bool PushBackItem(const int nItemIdx);	// �A�C�e���ǉ�
	bool DeleteItem(const int nBagIdx);		// �A�C�e���폜
	int GetItemIdx(const int nBagIdx);		// �A�C�e���C���f�b�N�X�擾
	bool SwapItemIdx(int* pItemIdx, const int nBagIdx);					// �A�C�e���C���f�b�N�X����
	inline int GetNumItem() const { return (int)m_vecItemIdx.size(); }	// �A�C�e�����擾

private:
	// �����o�ϐ�
	std::vector<int> m_vecItemIdx;	// �A�C�e���C���f�b�N�X
};

#endif	// _PLAYER_ITEM_H_
