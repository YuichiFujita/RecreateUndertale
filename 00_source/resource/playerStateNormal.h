//============================================================
//
//	�ʏ��ԃw�b�_�[ [playerStateNormal.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PLAYER_STATE_NORMAL_H_
#define _PLAYER_STATE_NORMAL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "playerState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �ʏ��ԃN���X
class CPlayerStateNormal : public CPlayerState
{
public:
	// �R���X�g���N�^
	CPlayerStateNormal();

	// �f�X�g���N�^
	~CPlayerStateNormal() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	int Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�֐�
	int ControlMove(void);	// �ړ�����
	void UpdatePosition(D3DXVECTOR3& rPos, const float fDeltaTime);	// �ʒu�X�V

	// �����o�ϐ�
	D3DXVECTOR3 m_move;	// �ړ���
};

#endif	// _PLAYER_STATE_NORMAL_H_
