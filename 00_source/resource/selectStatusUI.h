//============================================================
//
//	�t���X�e�[�^�X���j���[�w�b�_�[ [selectStatusUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SELECT_STATUS_UI_H_
#define _SELECT_STATUS_UI_H_

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
// �t���X�e�[�^�X���j���[�N���X
class CSelectStatusUI : public CSelect
{
public:
	// �R���X�g���N�^
	explicit CSelectStatusUI(const std::function<void(void)> funcUninit);

	// �f�X�g���N�^
	~CSelectStatusUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

private:
	// �����o�ϐ�

};

#endif	// _SELECT_STATUS_UI_H_
