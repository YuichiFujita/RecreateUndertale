//============================================================
//
//	�^�C�}�[���� [timer.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "timer.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 0;	// �^�C�}�[�̗D�揇��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CListManager<CTimer> *CTimer::m_pList = nullptr;	// �I�u�W�F�N�g���X�g

//************************************************************
//	�q�N���X [CTimer] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTimer::CTimer() : CObject(CObject::LABEL_TIMER, CObject::DIM_3D, PRIORITY),
	m_funcCount	(nullptr),		// �v���֐��|�C���^
	m_state		(STATE_NONE),	// �v�����
	m_fTime		(0.0f),			// �v������
	m_fLimit	(0.0f),			// ��������
	m_bStop		(false),		// �v����~��
	m_lTime		(0),			// �v���~���b
	m_nMin		(0),			// ��
	m_nSec		(0),			// �b
	m_nMSec		(0)				// �~���b
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CTimer::~CTimer()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTimer::Init(void)
{
	// �����o�ϐ���������
	m_funcCount = nullptr;		// �v���֐��|�C���^
	m_state		= STATE_NONE;	// �v�����
	m_fTime		= 0.0f;			// �v������
	m_fLimit	= 0.0f;			// ��������
	m_bStop		= false;		// �v����~��
	m_lTime		= 0;			// �v���~���b
	m_nMin		= 0;			// ��
	m_nSec		= 0;			// �b
	m_nMSec		= 0;			// �~���b

	if (m_pList == nullptr)
	{ // ���X�g�}�l�[�W���[�����݂��Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̐���
		m_pList = CListManager<CTimer>::Create();
		if (m_pList == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}
	}

	// ���X�g�Ɏ��g�̃I�u�W�F�N�g��ǉ��E�C�e���[�^�[���擾
	m_iterator = m_pList->AddList(this);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CTimer::Uninit(void)
{
	// ���X�g���玩�g�̃I�u�W�F�N�g���폜
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // �I�u�W�F�N�g������Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̔j��
		m_pList->Release(m_pList);
	}

	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CTimer::Update(const float fDeltaTime)
{
	switch (m_state)
	{ // �v����Ԃ��Ƃ̏���
	case STATE_NONE:
		break;

	case STATE_COUNT:

		// ��~���̏ꍇ������
		if (m_bStop) { break; }

		// �^�C�����v��
		assert(m_funcCount != nullptr);
		m_funcCount(fDeltaTime);

		break;

	case STATE_END:
		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// ���Ԃ̌v�Z
	CalcTime();
}

//============================================================
//	�`�揈��
//============================================================
void CTimer::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	��������
//============================================================
CTimer *CTimer::Create
(
	const float fTime,	// �J�n����
	const float fLimit	// ��������
)
{
	// �^�C�}�[�̐���
	CTimer *pTimer = new CTimer;
	if (pTimer == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �^�C�}�[�̏�����
		if (FAILED(pTimer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �^�C�}�[�̔j��
			SAFE_DELETE(pTimer);
			return nullptr;
		}

		// �J�n���Ԃ�ݒ�
		pTimer->SetTime(fTime);

		// �������Ԃ�ݒ�
		pTimer->SetLimit(fLimit);

		// �m�ۂ����A�h���X��Ԃ�
		return pTimer;
	}
}

//============================================================
//	���X�g�擾����
//============================================================
CListManager<CTimer> *CTimer::GetList(void)
{
	// �I�u�W�F�N�g���X�g��Ԃ�
	return m_pList;
}

//============================================================
//	�v���J�n����
//============================================================
void CTimer::Start(void)
{
	if (m_state != STATE_COUNT)
	{ // �^�C���̌v�����ł͂Ȃ��ꍇ

		// ���~��Ԃɂ���
		EnableStop(false);

		// �v���J�n��Ԃɂ���
		m_state = STATE_COUNT;
	}
}

//============================================================
//	�v���I������
//============================================================
void CTimer::End(void)
{
	if (m_state == STATE_COUNT)
	{ // �^�C���̌v�����̏ꍇ

		// ��~��Ԃɂ���
		EnableStop(true);

		// �v���I����Ԃɂ���
		m_state = STATE_END;
	}
}

//============================================================
//	�v����~�̗L�������̐ݒ菈��
//============================================================
void CTimer::EnableStop(const bool bStop)
{
	// �����̒�~�󋵂���
	m_bStop = bStop;
}

//============================================================
//	���Ԃ̉��Z����
//============================================================
void CTimer::AddTime(const float fTime)
{
	// ���Ԃ����Z
	m_fTime += fTime;

	// ���Ԃ�␳
	useful::LimitNum(m_fTime, timer::TIME_MIN, timer::TIME_MAX);
}

//============================================================
//	���Ԃ̐ݒ菈��
//============================================================
void CTimer::SetTime(const float fTime)
{
	// ���Ԃ�ݒ�
	m_fTime = fTime;

	// ���Ԃ�␳
	useful::LimitNum(m_fTime, timer::TIME_MIN, timer::TIME_MAX);
}

//============================================================
//	�������Ԃ̐ݒ菈��
//============================================================
void CTimer::SetLimit(const float fLimit)
{
	// �������Ԃ�ۑ�
	m_fLimit = fLimit;

	// �������Ԃ�␳
	useful::LimitNum(m_fLimit, timer::TIME_MIN, timer::TIME_MAX);

	if (m_fLimit <= 0.0f)
	{ // �������Ԃ��Ȃ��ꍇ

		// �J�E���g�A�b�v�֐���ݒ�
		m_funcCount = std::bind(&CTimer::CountUp, this, std::placeholders::_1);
	}
	else
	{ // ���Ԑ���������ꍇ

		// �����̊J�n���Ԃ�ݒ�
		m_fTime = fLimit;

		// �J�E���g�_�E���֐���ݒ�
		m_funcCount = std::bind(&CTimer::CountDown, this, std::placeholders::_1);
	}
}

//============================================================
//	�J�E���g�A�b�v����
//============================================================
void CTimer::CountUp(const float fDeltaTime)
{
	// �f���^�^�C�������Z
	m_fTime += fDeltaTime;
}

//============================================================
//	�J�E���g�_�E������
//============================================================
void CTimer::CountDown(const float fDeltaTime)
{
	// �f���^�^�C�������Z
	m_fTime -= fDeltaTime;
	if (m_fTime <= 0.0f)
	{  // �J�E���g�I�������ꍇ

		// �^�C����␳
		m_fTime = 0.0f;

		// �v�����I��
		End();
	}
}

//============================================================
//	���Ԃ̌v�Z����
//============================================================
void CTimer::CalcTime(void)
{
	m_lTime	= (DWORD)(m_fTime * 1000.0f);	// �b���~���b�ɕϊ�
	m_nMin	= (int)(m_lTime / 60000);		// �����v�Z
	m_nSec	= (int)(m_lTime / 1000) % 60;	// �b���v�Z
	m_nMSec	= (int)(m_lTime % 1000);		// �~���b���v�Z
}
