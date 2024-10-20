//============================================================
//
//	�����ݒ��ԃw�b�_�[ [startStateOption.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_STATE_OPTION_H_
#define _START_STATE_OPTION_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startState.h"

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �����ݒ��ԃN���X
class CStartStateOption : public CStartState
{
public:
	// �R���X�g���N�^
	CStartStateOption();

	// �f�X�g���N�^
	~CStartStateOption() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �I���
	enum ESelect
	{
		SELECT_CLOSE = 0,	// ����
		SELECT_MAX			// ���̗񋓌^�̑���
	};

	// �����o�֐�
	void UpdateSelect(void);	// �I���X�V
	void UpdateDecide(void);	// ����X�V

	// �����o�ϐ�
	CString2D* m_apSelect[SELECT_MAX];	// �I����
	CString2D* m_pTitle;	// �^�C�g��
	int m_nCurSelect;		// ���݂̑I����
	int m_nOldSelect;		// �O��̑I����
};

#endif	// _START_STATE_OPTION_H_
