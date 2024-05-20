//============================================================
//
//	�t���b�V���w�b�_�[ [flash.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FLASH_H_
#define _FLASH_H_

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �t���b�V���N���X
class CFlash
{
public:
	// �t���b�V����ԗ�
	enum EFlash
	{
		FLASH_NONE = 0,	// �������Ă��Ȃ����
		FLASH_IN,		// �t�F�[�h�C�����
		FLASH_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CFlash();

	// �f�X�g���N�^
	~CFlash();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);	// �X�V

	void Set(const float fStartAlpha, const float fSubAlpha);	// �t���b�V���ݒ�
	EFlash GetState(void) const { return m_flash; }				// �t���b�V����Ԏ擾

	// �ÓI�����o�֐�
	static CFlash *Create(void);			// ����
	static void Release(CFlash *&pFlash);	// �j��

private:
	// �����o�ϐ�
	CObject2D *m_pObject2D;	// �t���b�V���\���̏��
	EFlash m_flash;			// �t���b�V�����
	float m_fSubAlpha;		// �����x�̌��Z��
};

#endif	// _FLASH_H_
