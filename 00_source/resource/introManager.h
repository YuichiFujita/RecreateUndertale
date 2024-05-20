//============================================================
//
//	�C���g���}�l�[�W���[�w�b�_�[ [introManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INTROMANAGER_H_
#define _INTROMANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;		// �I�u�W�F�N�g2D�N���X
class CScroll2D;		// �X�N���[��2D�N���X
class CScrollText2D;	// ��������e�L�X�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �C���g���}�l�[�W���[�N���X
class CIntroManager
{
public:
	// ��ԗ�
	enum EState
	{
		STATE_LOGO = 0,	// ���S�\��
		STATE_TEXT,		// ��������
		STATE_WAIT,		// �ҋ@
		STATE_FADEIN,	// �t�F�[�h�C��
		STATE_FADEOUT,	// �t�F�[�h�A�E�g
		STATE_END,		// �I��
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �����
	enum EStory
	{
		STORY_00 = 0,	// �ނ����ނ���
		STORY_01,		// �Ƃ��낪����Ƃ�
		STORY_02,		// �j���Q�����傤��
		STORY_03,		// �����ɂƂ����߂܂���
		STORY_04,		// �Ȃ����Ƃ����Ȃ���
		STORY_05,		// �C�r�g�R
		STORY_06,		// �ł񂹂̎R
		STORY_07,		// �����낵
		STORY_08,		// �����|����
		STORY_09,		// ����
		STORY_10,		// ���n
		STORY_MAX,		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CIntroManager();

	// �f�X�g���N�^
	~CIntroManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);	// �X�V

	// �ÓI�����o�֐�
	static CIntroManager *Create(void);	// ����
	static void Release(CIntroManager *&prIntroManager);	// �j��

private:
	// �����o�֐�
	bool WaitTime(const float fDeltaTime, const float fDestTime);	// �ҋ@���Ԃ̊Ǘ�
	void NextStory(void);	// ����̑J��

	// �����o�ϐ�
	CObject2D *m_pLogo;		// �^�C�g�����S
	CObject2D *m_pFade;		// �t�F�[�h
	CScroll2D *m_pStory;	// �X�g�[���[
	CScrollText2D *m_pText;	// �e�L�X�g
	EState m_state;			// ���
	int m_nStory;			// ����C���f�b�N�X
	float m_fCurTime;		// ���݂̑ҋ@����
};

#endif	// _INTROMANAGER_H_
