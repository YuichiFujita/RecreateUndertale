//============================================================
//
//	�X�N���[���w�b�_�[ [screen.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCREEN_H_
#define _SCREEN_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �X�N���[���N���X
class CScreen : public CObject2D
{
public:
	// �R���X�g���N�^
	CScreen();

	// �f�X�g���N�^
	~CScreen();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CScreen *Create(const int nScreenTexID);	// ����
};

#endif	// _SCREEN_H_
