//============================================================
//
//	�^�C�}�[UI���� [timerUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "timerUI.h"
#include "timer.h"

//************************************************************
//	�e�N���X [CTimerUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTimerUI::CTimerUI() : m_pTimer(nullptr)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CTimerUI::~CTimerUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTimerUI::Init()
{
	// �����o�ϐ���������
	m_pTimer = nullptr;	// �^�C�}�[�Ǘ����

	// �^�C��UI�̏�����
	if (FAILED(CTimeUI::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �^�C�}�[�̐���
	m_pTimer = CTimer::Create(0.0f, 0.0f);
	if (m_pTimer == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �^�C�}�[�̎����X�V�E�����I����OFF�ɂ���
	m_pTimer->SetLabel(LABEL_NONE);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CTimerUI::Uninit()
{
	// �^�C�}�[�̏I��
	SAFE_UNINIT(m_pTimer);

	// �^�C��UI�̏I��
	CTimeUI::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CTimerUI::Update(const float fDeltaTime)
{
	// �^�C�}�[�̍X�V
	m_pTimer->Update(fDeltaTime);

	// �\�����Ԃ̐ݒ�
	SetTime(m_pTimer->GetTime());

	// �^�C��UI�̍X�V
	CTimeUI::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CTimerUI::Draw(CShader* pShader)
{
	// �^�C�}�[�̕`��
	m_pTimer->Draw(pShader);

	// �^�C��UI�̕`��
	CTimeUI::Draw(pShader);
}

//============================================================
//	�\�����Ԃ̐ݒ菈��
//============================================================
void CTimerUI::SetTime(const float fTime)
{
	// �^�C�}�[���Ԃ̐ݒ�
	m_pTimer->SetTime(fTime);

	// �\�����Ԃ̐ݒ�
	CTimeUI::SetTime(fTime);
}

//============================================================
//	��������
//============================================================
CTimerUI* CTimerUI::Create
(
	const float fTime,			// �J�n����
	const float fLimit,			// ��������
	const VECTOR3& rPos,		// �ʒu
	const VECTOR3& rSizeValue,	// �����̑傫��
	const VECTOR3& rSizePart,	// ��؂�̑傫��
	const VECTOR3& rSpaceValue,	// �����̋�
	const VECTOR3& rSpacePart,	// ��؂�̋�
	const CValue::EType type,	// �������
	const EAlignX alignX,		// ���z�u
	const EAlignY alignY,		// �c�z�u
	const VECTOR3& rRot,		// ����
	const COLOR& rCol			// �F
)
{
	// �^�C�}�[UI�̐���
	CTimerUI* pTimerUI = new CTimerUI;
	if (pTimerUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �^�C�}�[UI�̏�����
		if (FAILED(pTimerUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �^�C�}�[UI�̔j��
			SAFE_DELETE(pTimerUI);
			return nullptr;
		}

		// �J�n���Ԃ�ݒ�
		pTimerUI->SetTime(fTime);

		// �������Ԃ�ݒ�
		pTimerUI->SetLimit(fLimit);

		// ������ނ�ݒ�
		pTimerUI->SetValueType(type);

		// ���_�ʒu��ݒ�
		pTimerUI->SetVec3Position(rPos);

		// ���_������ݒ�
		pTimerUI->SetVec3Rotation(rRot);

		// �����̑傫����ݒ�
		pTimerUI->SetSizeValue(rSizeValue);

		// ��؂�̑傫����ݒ�
		pTimerUI->SetSizePart(rSizePart);

		// �����̋󔒂�ݒ�
		pTimerUI->SetSpaceValue(rSpaceValue);

		// ��؂�̋󔒂�ݒ�
		pTimerUI->SetSpacePart(rSpacePart);

		// �F��ݒ�
		pTimerUI->SetColor(rCol);

		// ���z�u��ݒ�
		pTimerUI->SetAlignX(alignX);

		// �c�z�u��ݒ�
		pTimerUI->SetAlignY(alignY);

		// �m�ۂ����A�h���X��Ԃ�
		return pTimerUI;
	}
}
