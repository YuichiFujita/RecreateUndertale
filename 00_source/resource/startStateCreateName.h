//============================================================
//
//	������ԃw�b�_�[ [startStateCreateName.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_STATE_CREATE_NAME_H_
#define _START_STATE_CREATE_NAME_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startState.h"

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ������ԃN���X
class CStartStateCreateName : public CStartState
{
public:
	// �萔
	static constexpr int SELECT_Y_MAX = 2;	// �I�����̏c�̍ő吔
	static constexpr int SELECT_X_MAX = 3;	// �I�����̉��̍ő吔

	// �R���X�g���N�^
	CStartStateCreateName();

	// �f�X�g���N�^
	~CStartStateCreateName() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�֐�
	void UpdateSelect(void);	// �I���X�V
	void UpdateDecide(void);	// ����X�V

	// �����o�ϐ�
	CString2D *m_apSelect[SELECT_Y_MAX][SELECT_X_MAX];	// �I����
	CString2D *m_pTitle;	// �^�C�g��
};

#endif	// _START_STATE_CREATE_NAME_H_
