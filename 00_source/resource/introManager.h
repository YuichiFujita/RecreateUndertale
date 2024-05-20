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
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �C���g���}�l�[�W���[�N���X
class CIntroManager
{
public:
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
};

#endif	// _INTROMANAGER_H_
