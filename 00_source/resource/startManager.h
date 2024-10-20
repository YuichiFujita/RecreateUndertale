//============================================================
//
//	�X�^�[�g�}�l�[�W���[�w�b�_�[ [startManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CStartState;	// �X�^�[�g��ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// �X�^�[�g�}�l�[�W���[�N���X
class CStartManager
{
public:
	// �\���e�L�X�g��
	enum EText
	{
		TEXT_PRESS_Z = 0,	// [PRESS Z OR ENTER]
		TEXT_BUTTON_TITLE,	// �� �{�^�������� ��
		TEXT_BUTTON_KINDS,	// �e�푀��{�^��
		TEXT_RULE,			// HP��0�ɂȂ�ƃQ�[���I�[�o�[
		TEXT_START,			// �Q�[�����͂��߂�
		TEXT_OPTION,		// �����Ă�
		TEXT_VIRSION,		// �o�[�W�������
		TEXT_OPTION_TITLE,	// �����Ă�
		TEXT_OPTION_CLOSE,	// �Ƃ���
		TEXT_NAMING,		// �Ȃ܂������Ă�������
		TEXT_HIRAGANA,		// �Ђ炪��
		TEXT_KATAKANA,		// �J�^�J�i
		TEXT_ALPHABET,		// �A���t�@�x�b�g
		TEXT_NAMING_QUIT,	// ��߂�
		TEXT_NAMING_DEL,	// ��������
		TEXT_NAMING_DEC,	// �����Ă�
		TEXT_DESIDE_NO,		// ������
		TEXT_DESIDE_YES,	// �͂�
		TEXT_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CStartManager();

	// �f�X�g���N�^
	~CStartManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);		// �X�V
	HRESULT ChangeState(CStartState* pState);	// ��ԕύX
	void SetName(const std::string& rName)	{ m_sName = rName; }	// ���O�ݒ�
	std::string GetName(void) const			{ return m_sName; }		// ���O�擾

	// �ÓI�����o�֐�
	static CStartManager* Create(void);	// ����
	static void Release(CStartManager*& prStartManager);	// �j��

private:
	// �����o�ϐ�
	CStartState* m_pState;	// ���
	std::string m_sName;	// ���O
};

#endif	// _STATEMANAGER_H_
