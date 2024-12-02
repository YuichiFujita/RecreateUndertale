//============================================================
//
//	�J�ڑI����ԃw�b�_�[ [titleStateSelect.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TITLE_STATE_SELECT_H_
#define _TITLE_STATE_SELECT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "titleState.h"

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X
class CVersion;		// �o�[�W�����\�L�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �J�ڑI����ԃN���X
class CTitleStateSelect : public CTitleState
{
public:
	// �R���X�g���N�^
	CTitleStateSelect();

	// �f�X�g���N�^
	~CTitleStateSelect() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�֐�
	void UpdateSelect();	// �I���X�V
	void UpdateDecide();	// ����X�V

	// �����o�ϐ�
	std::vector<std::vector<CString2D*>> m_vecSelect;	// �I�������
	CString2D* m_pName;		// ���O���
	CString2D* m_pLove;		// ���x�����
	CString2D* m_pTime;		// ���v���C���ԏ��
	CVersion* m_pVersion;	// �o�[�W�����\�L���
	POSGRID2 m_curSelect;	// ���݂̑I����
	POSGRID2 m_oldSelect;	// �O��̑I����
};

#endif	// _TITLE_STATE_SELECT_H_
