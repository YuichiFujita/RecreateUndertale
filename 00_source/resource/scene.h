//============================================================
//
//	�V�[���w�b�_�[ [scene.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

//************************************************************
//	�O���錾
//************************************************************
class CPlayer;	// �v���C���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �V�[���N���X
class CScene
{
public:
	// ���[�h��
	enum EMode
	{
		MODE_INTRO = 0,	// �C���g�����
		MODE_START,		// �X�^�[�g���
		MODE_TITLE,		// �^�C�g�����
		MODE_GAME,		// �Q�[�����
		MODE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CScene(const EMode mode);

	// �f�X�g���N�^
	virtual ~CScene();

	// ���z�֐�
	virtual HRESULT Init(void);	// ������
	virtual void Uninit(void);	// �I��
	virtual void Update(const float fDeltaTime);	// �X�V

	// �ÓI�����o�֐�
	static CScene *Create(EMode mode);		// ����
	static void Release(CScene *&prScene);	// �j��
	static CPlayer *GetPlayer(void);		// �v���C���[�擾

	// �����o�֐�
	void SetMode(const EMode mode);	// ���[�h�ݒ�
	EMode GetMode(void) const;		// ���[�h�擾

private:
	// �����o�ϐ�
	EMode m_mode;	// ���[�h
};

#endif	// _SCENE_H_
