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
class CString2D;	// ������2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ������ԃN���X
class CStartStateCreateName : public CStartState
{
public:
	// ������ޗ�
	enum ETypeChar
	{
		TYPECHAR_HIRAGANA = 0,	// �Ђ炪��
		TYPECHAR_KATAKANA,		// �J�^�J�i
		TYPECHAR_ALPHABET,		// �A���t�@�x�b�g
		TYPECHAR_MAX			// ���̗񋓌^�̑���
	};

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
		YSELECT_CHAR_CHANGE,	// �����ύX
		YSELECT_CHAR_DECIDE,	// ��������
		YSELECT_MAX				// ���̗񋓌^�̑���
	};

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
	void ControlSelect(void);	// �I�𑀍�
	void UpdateSelect(void);	// �I���X�V
	void UpdateDecide(void);	// ����X�V
	HRESULT ChangeChar(const ETypeChar typeChar);	// �����ύX
	HRESULT LoadArray(const ETypeChar typeChar);	// �z�u�Ǎ�

	// �����o�ϐ�
	std::vector<std::vector<CString2D*>> m_vecSelect;	// �I�𕶎�
	CString2D *m_pTitle;	// �^�C�g��
	CString2D *m_pName;		// ���O
	POSGRID2 m_curSelect;	// ���݂̑I����
	POSGRID2 m_oldSelect;	// �O��̑I����
};

#endif	// _START_STATE_CREATE_NAME_H_
