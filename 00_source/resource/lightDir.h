//============================================================
//
//	�f�B���N�V���i�����C�g�w�b�_�[ [lightDir.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _LIGHT_DIR_H_
#define _LIGHT_DIR_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "light.h"

//************************************************************
//	�N���X��`
//************************************************************
// �f�B���N�V���i�����C�g�N���X
class CLightDir : public CLight
{
public:
	// �R���X�g���N�^
	CLightDir();

	// �f�X�g���N�^
	~CLightDir() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CLightDir* Create();	// ����
};

#endif	// _LIGHT_DIR_H_
