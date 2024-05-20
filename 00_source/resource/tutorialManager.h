//============================================================
//
//	�`���[�g���A���}�l�[�W���[�w�b�_�[ [tutorialManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TUTORIAL_MANAGER_H_
#define _TUTORIAL_MANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X
class CGauge2D;		// �Q�[�W2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �`���[�g���A���}�l�[�W���[�N���X
class CTutorialManager
{
public:
	// �e�N�X�`����
	enum ETexture
	{
		TEXTURE_CONTROL = 0,	// ������@�\���̃e�N�X�`��
		TEXTURE_MAX				// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,		// �������Ȃ����
		STATE_NEXTWAIT,		// �����b�X���ҋ@���
		STATE_PROGRESSION,	// �i�s���
		STATE_END,			// �I�����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	// ���b�X����
	enum ELesson
	{
		LESSON_NONE = 0,	// ���b�X������
		LESSON_01,			// ���b�X��01�F�ړ��E�J����
		LESSON_02,			// ���b�X��02�F�W�����v
		LESSON_03,			// ���b�X��03�F���
		LESSON_04,			// ���b�X��04�F�U��
		LESSON_05,			// ���b�X��05�F�I��
		LESSON_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CTutorialManager();

	// �f�X�g���N�^
	~CTutorialManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);	// �X�V
	void AddLessonCounter(void);	// ���b�X���J�E���^�[���Z
	int GetLesson(void) const;		// ���b�X���擾
	EState GetState(void) const;	// ��Ԏ擾

	// �ÓI�����o�֐�
	static CTutorialManager *Create(void);						// ����
	static void Release(CTutorialManager *&prTutorialManager);	// �j��
	static int GetNextLessonCounter(const int nID);				// ���b�X���ڍs�J�E���g�擾

private:
	// �����o�֐�
	void SetEnableProgressionDraw(const bool bDraw);	// �i�s��Ԏ��ɕ\������UI�̕`��󋵐ݒ�
	void UpdateNextWait(void);	// �����b�X���ҋ@
	void NextLesson(void);		// �����b�X���ւ̈ڍs

	// �����o�ϐ�
	CGauge2D *m_pCounterLesson;	// ���b�X���Ǘ��J�E���^�[�̏��
	CObject2D *m_pGuide;		// �������\���̏��
	CObject2D *m_pGuideBG;		// �������\���̔w�i���
	CObject2D *m_pControl;		// ������@�\���̏��
	CObject2D *m_pControlBG;	// ������@�\���̔w�i���
	EState m_state;				// ���
	int m_nCounterState;		// ��ԊǗ��J�E���^�[
	int m_nLesson;				// ���b�X��
};

#endif	// _TUTORIAL_MANAGER_H_
