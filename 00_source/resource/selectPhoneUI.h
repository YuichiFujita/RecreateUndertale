//============================================================
//
//	�d�b���j���[�w�b�_�[ [selectPhoneUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SELECT_PHONE_UI_H_
#define _SELECT_PHONE_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "menuSelectUI.h"

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �d�b���j���[�N���X
class CSelectPhoneUI : public CSelectUI
{
public:
	// �R���X�g���N�^
	explicit CSelectPhoneUI(AFuncUninit funcUninit, CObject2D *pSoul);

	// �f�X�g���N�^
	~CSelectPhoneUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

private:
	// �����o�ϐ�

};

#endif	// _SELECT_PHONE_UI_H_
