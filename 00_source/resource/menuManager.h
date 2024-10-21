//============================================================
//
//	�t�B�[���h���j���[�}�l�[�W���[�w�b�_�[ [menuManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MENUMANAGER_H_
#define _MENUMANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CMenuUI;	// �t�B�[���h���j���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �t�B�[���h���j���[�}�l�[�W���[�N���X
class CMenuManager
{
public:
	// �R���X�g���N�^
	CMenuManager();

	// �f�X�g���N�^
	~CMenuManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);		// �X�V
	void SetEnableDrawMenu(const bool bDraw);	// �t�B�[���h���j���[�`��󋵐ݒ�
	bool IsChoiceSelect() const;				// �I�𒆏󋵎擾
	inline bool IsDrawMenu() const { return (m_pMenu != nullptr); }	// �t�B�[���h���j���[�`��󋵎擾

	// �ÓI�����o�֐�
	static CMenuManager* Create();	// ����
	static void Release(CMenuManager*& prMenuManager);	// �j��

private:
	// �����o�ϐ�
	CMenuUI* m_pMenu;	// �t�B�[���h���j���[���
};

#endif	// _MENUMANAGER_H_
