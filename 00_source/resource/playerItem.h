//============================================================
//
//	�v���C���[�����A�C�e���w�b�_�[ [playerItem.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PLAYER_ITEM_H_
#define _PLAYER_ITEM_H_

//************************************************************
//	�N���X��`
//************************************************************
// �v���C���[�����A�C�e���N���X
struct CPlayerItem
{
public:
	// �萔
	static constexpr int MAX_ITEM = 8;	// �ő�A�C�e����

	// �R���X�g���N�^
	CPlayerItem();

	// �f�X�g���N�^
	~CPlayerItem();

	// �����o�֐�
	void PushBackItem(const int nItemIdx);	// �A�C�e���ǉ�
	void DeleteItem(const int nBagIdx);		// �A�C�e���폜
	int GetItemIdx(const int nBagIdx);		// �A�C�e���C���f�b�N�X�擾
	void SetItemIdx(const int nBagIdx, const int nItemIdx);				// �A�C�e���C���f�b�N�X�ݒ�
	inline int GetNumItem() const { return (int)m_vecItemIdx.size(); }	// �A�C�e�����擾

private:
	// �����o�ϐ�
	std::vector<int> m_vecItemIdx;	// �A�C�e���C���f�b�N�X
};

#endif	// _PLAYER_ITEM_H_
