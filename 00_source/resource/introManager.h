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
class CIntroState;		// �C���g����ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// �C���g���}�l�[�W���[�N���X
class CIntroManager
{
public:
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
	void Update(const float fDeltaTime);		// �X�V
	HRESULT ChangeState(CIntroState *pState);	// ��ԕύX

	// �ÓI�����o�֐�
	static CIntroManager *Create(void);	// ����
	static void Release(CIntroManager *&prIntroManager);	// �j��

//private:	// TODO�F�{����΃_���I
	// �����o�֐�
	void NextStory(void);	// ����̑J��

	// �����o�ϐ�
	CObject2D *m_pFade;		// �t�F�[�h
	CScroll2D *m_pStory;	// �X�g�[���[
	CScrollText2D *m_pText;	// �e�L�X�g
	CIntroState *m_pState;	// ���
	int m_nStory;			// ����C���f�b�N�X
};

#endif	// _INTROMANAGER_H_