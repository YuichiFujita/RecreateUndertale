//============================================================
//
//	�Ђ炪�ȏ�ԃw�b�_�[ [charStateHiragana.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _CHAR_STATE_HIRAGANA_H_
#define _CHAR_STATE_HIRAGANA_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "charState.h"

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �Ђ炪�ȏ�ԃN���X
class CCharStateHiragana : public CCharState
{
public:
	// �R���X�g���N�^
	CCharStateHiragana();

	// �f�X�g���N�^
	~CCharStateHiragana() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�֐�
	int GetSelectWidth(void)	{ return (int)m_vecSelect[0].size(); }	// ���̕������擾
	int GetSelectHeight(void)	{ return (int)m_vecSelect.size(); }		// �c�̕������擾
	void UpdateSelect(void);	// �I���X�V
	void UpdateDecide(void);	// ����X�V
	HRESULT LoadArray(void);	// �z�u�Ǎ�

	// �����o�ϐ�
	std::vector<std::vector<CString2D*>> m_vecSelect;	// �I�𕶎�
	POSGRID2 m_selectMax;	// �I�𕶎��̍ő��
	POSGRID2 m_curSelect;	// ���݂̑I�𕶎�
	POSGRID2 m_oldSelect;	// �O��̑I�𕶎�
};

#endif	// _CHAR_STATE_HIRAGANA_H_
