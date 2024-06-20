//============================================================
//
//	���O�����ԃw�b�_�[ [startStateDecideName.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_STATE_DECIDE_NAME_H_
#define _START_STATE_DECIDE_NAME_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startState.h"

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X
class CText2D;		// �e�L�X�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ���O�����ԃN���X
class CStartStateDecideName : public CStartState
{
public:
	// �R���X�g���N�^
	CStartStateDecideName();

	// �f�X�g���N�^
	~CStartStateDecideName() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �I���
	enum ESelect
	{
		SELECT_NO = 0,	// ������
		SELECT_YES,		// �͂�
		SELECT_MAX		// ���̗񋓌^�̑���
	};

	// �����o�֐�
	void UpdateSelect(void);	// �I���X�V
	void UpdateDecide(void);	// ����X�V
	void UpdateShakeName(const float fDeltaTime);	// ���O�U���X�V

	// �����o�ϐ�
	CString2D *m_apSelect[SELECT_MAX];	// �I����
	CText2D *m_pTitle;		// �^�C�g��
	CString2D *m_pName;		// ���O
	int m_nCurSelect;		// ���݂̑I����
	int m_nOldSelect;		// �O��̑I����
	float m_fCurTimeShake;	// ���݂̐U���̌o�ߎ���
	float m_fCurTimeMove;	// ���݂̈ړ��̌o�ߎ���

	float f;

private:
	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,	// �������Ȃ����
		STATE_MOVE,		// ���O�̈ړ����
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �����o�֐�
	void StateUpdateNone(const float fDeltaTime);	// �������Ȃ���ԍX�V
	void StateUpdateMove(const float fDeltaTime);	// ���O�̈ړ���ԍX�V

	// �����o�ϐ�
	EState m_state;	// ���

	// ��ԍX�V�̊֐��|�C���^�^�G�C���A�X��`
	typedef void (CStartStateDecideName::*AFuncState)(const float);

	// ��Ԃ��Ƃ̍X�V�֐��|�C���^
	static constexpr AFuncState FUNC_STATE[] =
	{
		&CStartStateDecideName::StateUpdateNone,	// �������Ȃ���ԍX�V
		&CStartStateDecideName::StateUpdateMove,	// ���O�̈ړ���ԍX�V
	};

	// �X�^�e�B�b�N�A�T�[�g
	static_assert(NUM_ARRAY(FUNC_STATE) == STATE_MAX, "ERROR : Func Count Mismatch");
};

#endif	// _START_STATE_DECIDE_NAME_H_
