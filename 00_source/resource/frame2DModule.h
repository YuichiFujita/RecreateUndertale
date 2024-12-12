//============================================================
//
//	�t���[��2D�@�\�w�b�_�[ [frame2DModule.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_MODULE_H_
#define _FRAME2D_MODULE_H_

//************************************************************
//	�O���錾
//************************************************************
class CFrame2D;				// �t���[��2D�N���X
class CFrame2DModuleText;	// �e�L�X�g�\���@�\�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �t���[��2D�@�\�N���X
class CFrame2DModule
{
public:
	// �R���X�g���N�^
	CFrame2DModule();

	// �f�X�g���N�^
	virtual ~CFrame2DModule();

	// �������z�֐�
	virtual HRESULT Init()	= 0;	// ������
	virtual void Uninit()	= 0;	// �I��
	virtual void Update(const float fDeltaTime) = 0;	// �X�V

	// ���z�֐�
	inline virtual void SetPriority(const int)			{}	// �D�揇�ʐݒ�
	inline virtual void SetVec3Position(const VECTOR3&)	{}	// �ʒu�ݒ�
	inline virtual void SetVec3Rotation(const VECTOR3&)	{}	// �����ݒ�
	inline virtual void SetVec3Size(const VECTOR3&)		{}	// �傫���ݒ�
	inline virtual CFrame2DModuleText* GetModuleText()	{ return nullptr; }	// �e�L�X�g�\���@�\�擾

	// �����o�֐�
	inline void SetContext(CFrame2D* pContext) { m_pContext = pContext; }	// �R���e�L�X�g�ݒ�

protected:
	// �����o�ϐ�
	CFrame2D* m_pContext;	// �R���e�L�X�g
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DModuleText.h"

#endif	// _FRAME2D_MODULE_H_
