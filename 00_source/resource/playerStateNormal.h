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
	// �p�x��
	enum EAngle
	{
		ANGLE_UP = 0,	// ��
		ANGLE_DOWN,		// ��
		ANGLE_LEFT,		// ��
		ANGLE_RIGHT,	// �E
		ANGLE_MAX		// ���̗񋓌^�̑���
	};

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
	void UpdatePosition(const float fDeltaTime);	// �ʒu�X�V

	// �����o�ϐ�
	D3DXVECTOR3	m_move;	// �ړ���
	EAngle m_moveAngle;	// �ړ�����
};

#endif	// _PLAYER_STATE_NORMAL_H_
