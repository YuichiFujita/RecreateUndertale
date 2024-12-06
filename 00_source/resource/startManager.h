//============================================================
//
//	�X�^�[�g�}�l�[�W���[�w�b�_�[ [startManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _STARTMANAGER_H_
#define _STARTMANAGER_H_

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
		TEXT_BUTTON_TITLE = 0,	// �� �{�^�������� ��
		TEXT_BUTTON_KINDS,		// �e�푀��{�^��
		TEXT_RULE,				// HP��0�ɂȂ�ƃQ�[���I�[�o�[
		TEXT_START,				// �Q�[�����͂��߂�
		TEXT_OPTION,			// �����Ă�
		TEXT_NAMING,			// �Ȃ܂������Ă�������
		TEXT_HIRAGANA,			// �Ђ炪��
		TEXT_KATAKANA,			// �J�^�J�i
		TEXT_ALPHABET,			// �A���t�@�x�b�g
		TEXT_NAMING_QUIT,		// ��߂�
		TEXT_NAMING_DEL,		// ��������
		TEXT_NAMING_DEC,		// �����Ă�
		TEXT_MAX				// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CStartManager();

	// �f�X�g���N�^
	~CStartManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);		// �X�V
	HRESULT ChangeState(CStartState* pState);	// ��ԕύX
	inline void SetName(const std::string& rName)	{ m_sName = rName; }	// ���O�ݒ�
	inline std::string GetName() const				{ return m_sName; }		// ���O�擾

	// �ÓI�����o�֐�
	static CStartManager* Create();	// ����
	static void Release(CStartManager*& prStartManager);	// �j��

private:
	// �����o�ϐ�
	CStartState* m_pState;	// ���
	std::string m_sName;	// ���O
};

#endif	// _STARTMANAGER_H_
