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
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scrollText2D.h"

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X
class CScroll2D;	// �X�N���[��2D�N���X
class CIntroState;	// �C���g����ԃN���X

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

	void NextStory(void);	// ����̑J��
	void ChangeStory(const int nStoryID);		// �X�g�[���[�ύX
	void ChangeText(const int nStoryID);		// �e�L�X�g�ύX
	void SetEnableSlowText(const bool bSlow);	// ��������̑��x�ݒ�
	int GetStoryID(void)	{ return m_nStoryID; }					// ����C���f�b�N�X�擾
	int GetNextCharID(void)	{ return m_pText->GetNextCharID(); }	// ���̕\�������C���f�b�N�X�擾
	bool IsTextScroll(void)	{ return m_pText->IsScroll(); }			// �e�L�X�g��������󋵎擾

	// �ÓI�����o�֐�
	static CIntroManager *Create(void);	// ����
	static void Release(CIntroManager *&prIntroManager);	// �j��

private:
	// �����o�ϐ�
	CScroll2D *m_pStory;	// �X�g�[���[
	CScrollText2D *m_pText;	// �e�L�X�g
	CIntroState *m_pState;	// ���
	int m_nStoryID;			// ����C���f�b�N�X
};

#endif	// _INTROMANAGER_H_
