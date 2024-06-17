//============================================================
//
//	������ԃw�b�_�[ [startStateCreateName.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_STATE_CREATE_NAME_H_
#define _START_STATE_CREATE_NAME_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startState.h"

//************************************************************
//	�O���錾
//************************************************************
class CString2D;		// ������2D�N���X
class CNamingManager;	// �����}�l�[�W���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ������ԃN���X
class CStartStateCreateName : public CStartState
{
public:
	// ��I���
	enum ESelectX
	{
		XSELECT_LEFT = 0,	// ��
		XSELECT_CENTER,		// ����
		XSELECT_RIGHT,		// �E
		XSELECT_MAX			// ���̗񋓌^�̑���
	};

	// �s�I���
	enum ESelectY
	{
		YSELECT_TOP = 0,	// ��
		YSELECT_CENTER,		// ����
		YSELECT_BOTTOM,		// ��
		YSELECT_MAX			// ���̗񋓌^�̑���
	};

	// �萔
	static constexpr int YSELECT_POLY_MAX = YSELECT_MAX - 1;

	// �R���X�g���N�^
	CStartStateCreateName();

	// �f�X�g���N�^
	~CStartStateCreateName() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�֐�
	void UpdateSelect(const float fDeltaTime);	// �I���X�V
	void UpdateDecide(void);	// ����X�V

	// �����o�ϐ�
	CString2D *m_pTitle;		// �^�C�g��
	CNamingManager *m_pNaming;	// �����}�l�[�W���[
	POSGRID2 m_curSelect;		// ���݂̑I����
	POSGRID2 m_oldSelect;		// �O��̑I����
};

#endif	// _START_STATE_CREATE_NAME_H_
