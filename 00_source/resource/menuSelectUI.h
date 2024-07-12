//============================================================
//
//	�Z���N�g���j���[�w�b�_�[ [menuSelectUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MENU_SELECT_UI_H_
#define _MENU_SELECT_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2D;		// �t���[��2D�N���X
class CString2D;	// ������2D�N���X
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �Z���N�g���j���[�N���X
class CMenuSelectUI : public CObject
{
public:
	// �R���X�g���N�^
	CMenuSelectUI();

	// �f�X�g���N�^
	~CMenuSelectUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CMenuSelectUI *Create(void);	// ����

private:
	// �I���
	enum ESelect
	{
		SELECT_ITEM = 0,	// �A�C�e��
		SELECT_STATUS,		// �X�e�[�^�X
		SELECT_PHONE,		// �d�b
		SELECT_MAX			// ���̗񋓌^�̑���
	};

	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void UpdateSelect(void);	// �I���X�V
	void UpdateDecide(void);	// ����X�V

	// �����o�ϐ�
	CString2D *m_apSelect[SELECT_MAX];	// �I�������
	CFrame2D *m_pFrame;	// �t���[�����
	CObject2D *m_pSoul;	// �\�E���J�[�\�����
	int m_nCurSelect;	// ���݂̑I����
};

#endif	// _MENU_SELECT_UI_H_
