//============================================================
//
//	�t�B�[���h���j���[�w�b�_�[ [menuUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MENU_UI_H_
#define _MENU_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�O���錾
//************************************************************
class CMenuStatusUI;	// �X�e�[�^�X���j���[�N���X
class CMenuSelectUI;	// �Z���N�g���j���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �t�B�[���h���j���[�N���X
class CMenuUI : public CObject
{
public:
	// �\���e�L�X�g��
	enum EText
	{
		TEXT_MINI_STATUS = 0,	// �~�j�X�e�[�^�X�\��
		TEXT_ITEM,				// ITEM
		TEXT_STATUS,			// STAT
		TEXT_PHONE,				// PHONE
		TEXT_MAX				// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CMenuUI();

	// �f�X�g���N�^
	~CMenuUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CMenuUI *Create(void);	// ����

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	CMenuStatusUI *m_pStatusMenu;	// �X�e�[�^�X���j���[���
	CMenuSelectUI *m_pSelectMenu;	// �Z���N�g���j���[���
};

#endif	// _MENU_UI_H_