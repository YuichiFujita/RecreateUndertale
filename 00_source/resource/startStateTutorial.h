//============================================================
//
//	�`���[�g���A����ԃw�b�_�[ [startStateTutorial.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_STATE_TUTORIAL_H_
#define _START_STATE_TUTORIAL_H_

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
// �`���[�g���A����ԃN���X
class CStartStateTutorial : public CStartState
{
public:
	// �R���X�g���N�^
	CStartStateTutorial();

	// �f�X�g���N�^
	~CStartStateTutorial() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �I���
	enum ESelect
	{
		SELECT_START = 0,	// �Q�[���J�n
		SELECT_OPTION,		// �����ݒ�z
		SELECT_MAX			// ���̗񋓌^�̑���
	};

	// �����o�֐�
	void UpdateSelect(void);	// �I���X�V
	void UpdateDecide(void);	// ����X�V

	// �����o�ϐ�
	CString2D* m_apSelect[SELECT_MAX];	// �I����
	CText2D*   m_pCont;		// �������
	CString2D* m_pTitle;	// �^�C�g��
	CString2D* m_pRule;		// �Q�[���T�v
	CString2D* m_pVersion;	// �o�[�W�����\�L
	int m_nCurSelect;		// ���݂̑I����
	int m_nOldSelect;		// �O��̑I����
};

#endif	// _START_STATE_TUTORIAL_H_
