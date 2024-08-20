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
class CText2D;		// �e�L�X�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �t���X�e�[�^�X���j���[�N���X
class CSelectStatusUI : public CSelect
{
public:
	// �R���X�g���N�^
	CSelectStatusUI(AFuncUninit funcUninit, CObject2D *pSoul);

	// �f�X�g���N�^
	~CSelectStatusUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

private:
	// �\���e�L�X�g��
	enum EText
	{
		TEXT_LV_HP = 0,	// LV/HP
		TEXT_ATK_DEF,	// ATK/DEF
		TEXT_EXP_NEXT,	// EXP/NEXT
		TEXT_WPN_AMR,	// WPN/AMR
		TEXT_GOLD,		// GOLD
		TEXT_KILLS,		// KILLS
		TEXT_MAX		// ���̗񋓌^�̑���
	};

	// �����o�ϐ�
	CString2D *m_pName;			// ���O���
	CText2D *m_pLvHpTitle;		// LV/HP�^�C�g�����
	CText2D *m_pLvHpValue;		// LV/HP���l���
	CText2D *m_pAtkDefTitle;	// ATK/DEF�^�C�g�����
	CText2D *m_pAtkDefValue;	// ATK/DEF���l���
	CText2D *m_pExpNextTitle;	// EXP/NEXT�^�C�g�����
	CText2D *m_pExpNextValue;	// EXP/NEXT���l���
};

#endif	// _SELECT_STATUS_UI_H_
