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
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��
	void SetTime(const float fTime) override;		// ���Ԑݒ�
	inline float GetTime() const override	{ return m_pTimer->GetTime(); }	// ���Ԏ擾
	inline int GetMin() const override		{ return m_pTimer->GetMin(); }	// ���擾
	inline int GetSec() const override		{ return m_pTimer->GetSec(); }	// �b�擾
	inline int GetMSec() const override		{ return m_pTimer->GetMSec(); }	// �~���b�擾

	// �ÓI�����o�֐�
	static CTimerUI* Create	// ����
	( // ����
		const float fTime,			// �J�n����
		const float fLimit,			// ��������
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rSizeValue,	// �����̑傫��
		const VECTOR3& rSizePart,	// ��؂�̑傫��
		const VECTOR3& rSpaceValue,	// �����̋�
		const VECTOR3& rSpacePart,	// ��؂�̋�
		const CValue::EType type = CValue::TYPE_NORMAL,	// �������
		const EAlignX alignX = XALIGN_CENTER,			// ���z�u
		const EAlignY alignY = YALIGN_CENTER,			// �c�z�u
		const VECTOR3& rRot = VEC3_ZERO,				// ����
		const COLOR& rCol = color::White()				// �F
	);

	// �����o�֐�
	inline void Start()	{ m_pTimer->Start(); }	// �v���J�n
	inline void End()	{ m_pTimer->End(); }	// �v���I��
	inline void EnableStop(const bool bStop)	{ m_pTimer->EnableStop(bStop);}		// �v����~�ݒ�
	inline void AddTime(const float fTime)		{ m_pTimer->AddTime(fTime); }		// ���ԉ��Z
	inline void SetLimit(const float fLimit)	{ m_pTimer->SetLimit(fLimit); }		// �������Ԑݒ�
	inline float GetLimit() const				{ return m_pTimer->GetLimit(); }	// �������Ԏ擾
	inline CTimer::EState GetState() const		{ return m_pTimer->GetState(); }	// �v����Ԏ擾

private:
	// �����o�ϐ�
	CTimer* m_pTimer;	// �^�C�}�[�Ǘ����
};

#endif	// _TIMER_UI_H_
