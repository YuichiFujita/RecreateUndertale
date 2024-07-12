//============================================================
//
//	�X�e�[�^�X���j���[�w�b�_�[ [menuStatusUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MENU_STATUS_UI_H_
#define _MENU_STATUS_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2D;		// �t���[��2D�N���X
class CString2D;	// ������2D�N���X
class CText2D;		// �e�L�X�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �X�e�[�^�X���j���[�N���X
class CMenuStatusUI : public CObject
{
public:
	// �R���X�g���N�^
	CMenuStatusUI();

	// �f�X�g���N�^
	~CMenuStatusUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CMenuStatusUI *Create(void);	// ����

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	CFrame2D *m_pFrame;	// �t���[�����
	CString2D *m_pName;	// ���O���
	CText2D *m_pStatus;	// �X�e�[�^�X���
	CText2D *m_pValue;	// �X�e�[�^�X���l���
};

#endif	// _MENU_STATUS_UI_H_
