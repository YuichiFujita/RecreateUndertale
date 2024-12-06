//============================================================
//
//	���Z�b�g��ԃw�b�_�[ [titleStateReset.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TITLE_STATE_RESET_H_
#define _TITLE_STATE_RESET_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "titleState.h"
#include "nearNameManager.h"

//************************************************************
//	�N���X��`
//************************************************************
// ���Z�b�g��ԃN���X
class CTitleStateReset : public CTitleState
{
public:
	// �R���X�g���N�^
	CTitleStateReset();

	// �f�X�g���N�^
	~CTitleStateReset() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�֐�
	void UpdateDecide(const CNearNameManager::ESelect select);	// ����X�V

	// �����o�ϐ�
	CNearNameManager* m_pNearNameManager;	// ���O�ڋ߃}�l�[�W���[
};

#endif	// _TITLE_STATE_RESET_H_
