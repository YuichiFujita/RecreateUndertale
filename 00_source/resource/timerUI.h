//============================================================
//
//	�^�C�}�[UI�w�b�_�[ [timerUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TIMER_UI_H_
#define _TIMER_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "timeUI.h"
#include "timer.h"
#include "value.h"

//************************************************************
//	�N���X��`
//************************************************************
// �^�C�}�[UI�N���X
class CTimerUI : public CTimeUI
{
public:
	// �R���X�g���N�^
	CTimerUI();

	// �f�X�g���N�^
	~CTimerUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��
	void SetTime(const float fTime) override;		// ���Ԑݒ�
	float GetTime(void) const override	{ return m_pTimer->GetTime(); }	// ���Ԏ擾
	int GetMin(void) const override		{ return m_pTimer->GetMin(); }	// ���擾
	int GetSec(void) const override		{ return m_pTimer->GetSec(); }	// �b�擾
	int GetMSec(void) const override	{ return m_pTimer->GetMSec(); }	// �~���b�擾

	// �ÓI�����o�֐�
	static CTimerUI *Create	// ����
	( // ����
		const float fTime,				// �J�n����
		const float fLimit,				// ��������
		const D3DXVECTOR3& rPos,		// �ʒu
		const D3DXVECTOR3& rSizeValue,	// �����̑傫��
		const D3DXVECTOR3& rSizePart,	// ��؂�̑傫��
		const D3DXVECTOR3& rSpaceValue,	// �����̋�
		const D3DXVECTOR3& rSpacePart,	// ��؂�̋�
		const CValue::EType type = CValue::TYPE_NORMAL,	// �������
		const EAlignX alignX = XALIGN_CENTER,			// ���z�u
		const EAlignY alignY = YALIGN_CENTER,			// �c�z�u
		const D3DXVECTOR3& rRot = VEC3_ZERO,			// ����
		const D3DXCOLOR& rCol = XCOL_WHITE				// �F
	);

	// �����o�֐�
	void Start(void)	{ m_pTimer->Start(); }	// �v���J�n
	void End(void)		{ m_pTimer->End(); }	// �v���I��
	void EnableStop(const bool bStop)	{ m_pTimer->EnableStop(bStop);}		// �v����~�ݒ�
	void AddTime(const float fTime)		{ m_pTimer->AddTime(fTime); }		// ���ԉ��Z
	void SetLimit(const float fLimit)	{ m_pTimer->SetLimit(fLimit); }		// �������Ԑݒ�
	float GetLimit(void) const			{ return m_pTimer->GetLimit(); }	// �������Ԏ擾
	CTimer::EState GetState(void) const	{ return m_pTimer->GetState(); }	// �v����Ԏ擾

private:
	// �����o�ϐ�
	CTimer *m_pTimer;	// �^�C�}�[�Ǘ����
};

#endif	// _TIMER_UI_H_
