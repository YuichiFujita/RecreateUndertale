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
	void ShakeName(const float fDeltaTime);	// ���O�U��
	void MoveName(const float fDeltaTime);	// ���O�ړ�

	// �����o�ϐ�
	CString2D *m_apSelect[SELECT_MAX];	// �I����
	CText2D *m_pTitle;		// �^�C�g��
	CString2D *m_pName;		// ���O
	int m_nCurSelect;		// ���݂̑I����
	int m_nOldSelect;		// �O��̑I����
	float m_fCurTimeShake;	// ���݂̐U���̌o�ߎ���
	float m_fCurTimeMove;	// ���݂̈ړ��̌o�ߎ���
	float m_fNameDestPosX;	// ���O�̖ڕW�ʒuX
	bool m_bMove;			// ���O�̈ړ���
};

#endif	// _START_STATE_DECIDE_NAME_H_
