//============================================================
//
//	�^�C�g���}�l�[�W���[�w�b�_�[ [titleManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TITLEMANAGER_H_
#define _TITLEMANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CTitleState;	// �^�C�g����ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// �^�C�g���}�l�[�W���[�N���X
class CTitleManager
{
public:
	// �\���e�L�X�g��
	enum EText
	{
		TEXT_CONTINUE = 0,	// �R���e�B�j���[
		TEXT_RESET,			// ���Z�b�g
		TEXT_SETTING,		// �ݒ�
		TEXT_RESET_TITLE,	// ���łɂȂ܂��������Ă��܂�
		TEXT_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CTitleManager();

	// �f�X�g���N�^
	~CTitleManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);		// �X�V
	HRESULT ChangeState(CTitleState* pState);	// ��ԕύX

	// �ÓI�����o�֐�
	static CTitleManager* Create();	// ����
	static void Release(CTitleManager*& prTitleManager);	// �j��

private:
	// �����o�ϐ�
	CTitleState* m_pState;	// ���
};

#endif	// _TITLEMANAGER_H_
