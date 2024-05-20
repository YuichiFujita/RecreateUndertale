//============================================================
//
//	�Q�[���}�l�[�W���[�w�b�_�[ [gameManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "retentionManager.h"

//************************************************************
//	�N���X��`
//************************************************************
// �Q�[���}�l�[�W���[�N���X
class CGameManager
{
public:
	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,	// �������Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CGameManager();

	// �f�X�g���N�^
	~CGameManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);	// �X�V
	void SetState(const EState state);		// ��Ԑݒ�
	EState GetState(void) const;			// ��Ԏ擾
	void TransitionResult(const CRetentionManager::EWin win);	// ���U���g��ʑJ��

	// �ÓI�����o�֐�
	static CGameManager *Create(void);	// ����
	static void Release(CGameManager *&prGameManager);	// �j��

private:
	// �����o�ϐ�
	EState m_state;	// ���
};

#endif	// _GAMEMANAGER_H_
