//============================================================
//
//	�P�F�`��V�F�[�_�[�w�b�_�[ [shaderMono.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SHADER_STENCIL_H_
#define _SHADER_STENCIL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "shader.h"

//************************************************************
//	�N���X��`
//************************************************************
// �P�F�`��V�F�[�_�[�N���X
class CMonoShader : public CShader
{
public:
	// �R���X�g���N�^
	CMonoShader();

	// �f�X�g���N�^
	~CMonoShader() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��

	// �����o�֐�
	void SetColor(const D3DXCOLOR& rCol);	// �s�N�Z���`��F�̐ݒ�

	// �ÓI�����o�֐�
	static CMonoShader *Create(void);		// ����
	static CMonoShader *GetInstance(void);	// �擾
	static void Release(void);					// �j��

private:
	// �ÓI�����o�ϐ�
	static CMonoShader *m_pShader;	// �V�F�[�_�[���

	// �����o�ϐ�
	D3DXHANDLE m_pColDraw;	// �s�N�Z���`��F
};

#endif	// _SHADER_STENCIL_H_
