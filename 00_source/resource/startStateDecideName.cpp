//============================================================
//
//	���O�����ԏ��� [startStateDecideName.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startStateDecideName.h"
#include "startManager.h"
#include "manager.h"
#include "shakeString2D.h"
#include "string2D.h"
#include "text2D.h"
#include "loadtext.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *PASS		= "data\\TEXT\\start.txt";	// �e�L�X�g�p�X
	const int	PRIORITY	= 6;	// �D�揇��
	const float	MOVE_TIME	= 4.0f;	// �ړ�����

	namespace title
	{	
		const char	*FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const char	*PASS = "data\\TEXT\\naming.txt";	// �e�L�X�g�p�X
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;	// �����c��
		const float	LINE_HEIGHT	= 54.0f;	// �s�ԏc��

		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_CENTER;	// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(270.0f, 130.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// ����
		const D3DXCOLOR		COL = XCOL_WHITE;	// �F
	}

	namespace name
	{
		const char	*FONT	= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC	= false;		// �C�^���b�N
		const float	INIT_HEIGHT	= 42.0f;	// ���������c��
		const float	DEST_HEIGHT	= 148.0f;	// �ڕW�����c��
		const float	NEXT_TIME	= 0.035f;	// �����U���̑ҋ@����
		const float	MOVE		= 1.5f;		// �U���ړ���

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;			// ���z�u
		const D3DXVECTOR3	INIT_POS = D3DXVECTOR3(360.0f, 155.0f, 0.0f);	// �����ʒu
		const D3DXVECTOR3	DEST_POS = D3DXVECTOR3(60.0f, 385.0f, 0.0f);	// �ڕW�ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// ����
		const D3DXCOLOR		COL = XCOL_WHITE;	// �F
	}

	namespace select
	{
		const char	*FONT		= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;	// �����c��
		const float	LINE_WIDTH	= 500.0f;	// ��ԏc��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const D3DXVECTOR3 POS = D3DXVECTOR3(180.0f, 615.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3 ROT = VEC3_ZERO;			// ����
		const D3DXCOLOR COL_DEFAULT	= XCOL_WHITE;	// �ʏ�F
		const D3DXCOLOR COL_CHOICE	= XCOL_YELLOW;	// �I��F
	}
}

//************************************************************
//	�q�N���X [CStartStateDecideName] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateDecideName::CStartStateDecideName() :
	m_pTitle		(nullptr),		// �^�C�g��
	m_pName			(nullptr),		// ���O
	m_state			((EState)0),	// ���
	m_nCurSelect	(0),			// ���݂̑I����
	m_nOldSelect	(0),			// �O��̑I����
	m_fCurTimeShake	(0.0f),			// ���݂̐U���̌o�ߎ���
	m_fCurTimeMove	(0.0f)			// ���݂̈ړ��̌o�ߎ���
{
	// �����o�ϐ����N���A
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I����
}

//============================================================
//	�f�X�g���N�^
//============================================================
CStartStateDecideName::~CStartStateDecideName()
{

}

//============================================================
//	����������
//============================================================
HRESULT CStartStateDecideName::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I����
	m_pTitle		= nullptr;		// �^�C�g��
	m_pName			= nullptr;		// ���O
	m_state			= STATE_MOVE;	// ���
	m_nCurSelect	= 0;			// ���݂̑I����
	m_nOldSelect	= 0;			// �O��̑I����
	m_fCurTimeShake	= 0.0f;			// ���݂̐U���̌o�ߎ���
	m_fCurTimeMove	= 0.0f;			// ���݂̈ړ��̌o�ߎ���

	// �^�C�g���̐���
	m_pTitle = CText2D::Create
	( // ����
		title::FONT,		// �t�H���g�p�X
		title::ITALIC,		// �C�^���b�N
		title::POS,			// ���_�ʒu
		title::CHAR_HEIGHT,	// �����c��
		title::LINE_HEIGHT,	// �s�ԏc��
		title::ALIGN_X,		// ���z�u
		title::ALIGN_Y,		// �c�z�u
		title::ROT,			// ���_����
		title::COL			// �F
	);
	if (m_pTitle == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pTitle->SetPriority(PRIORITY);

	// �e�L�X�g������
	loadtext::BindText(m_pTitle, loadtext::LoadText(title::PASS, m_pContext->GetName().c_str()));

	// ���O�̐���
	m_pName = CShakeString2D::Create
	( // ����
		name::FONT,			// �t�H���g�p�X
		name::ITALIC,		// �C�^���b�N
		L"",				// �w�蕶����
		name::INIT_POS,		// ���_�ʒu
		name::NEXT_TIME,	// �����U���̑ҋ@����
		name::MOVE,			// �U���ړ���
		name::INIT_HEIGHT,	// �����c��
		name::ALIGN_X,		// ���z�u
		name::ROT,			// ���_����
		name::COL			// �F
	);
	if (m_pName == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pName->SetPriority(PRIORITY);

	// �ۑ����̖��O��ݒ�
	m_pName->SetString(useful::MultiByteToWide(m_pContext->GetName()));

	f = m_pName->GetStrWidth() * (name::DEST_HEIGHT / name::INIT_HEIGHT);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �����ʒu�I�t�Z�b�g
		D3DXVECTOR3 offset = D3DXVECTOR3(select::LINE_WIDTH * i, 0.0f, 0.0f);

		// �I�����̐���
		m_apSelect[i] = CString2D::Create
		( // ����
			select::FONT,			// �t�H���g�p�X
			select::ITALIC,			// �C�^���b�N
			L"",					// �w�蕶����
			select::POS + offset,	// ���_�ʒu
			select::CHAR_HEIGHT,	// �����c��
			select::ALIGN_X,		// ���z�u
			select::ROT,			// ���_����
			select::COL_DEFAULT		// �F
		);

		// �D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(PRIORITY);

		// �����������
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(PASS, CStartManager::TEXT_DESIDE_NO + i));
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CStartStateDecideName::Uninit(void)
{
	// �^�C�g���̏I��
	SAFE_UNINIT(m_pTitle);

	// ���O�̏I��
	SAFE_UNINIT(m_pName);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I�����̏I��
		SAFE_UNINIT(m_apSelect[i]);
	}

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CStartStateDecideName::Update(const float fDeltaTime)
{
	// ��Ԃ��Ƃ̍X�V
	assert(m_state > NONE_IDX && m_state < STATE_MAX);
	(this->*(FUNC_STATE[m_state]))(fDeltaTime);

	// ���O�U���̍X�V
	UpdateShakeName(fDeltaTime);

	// �I���̍X�V
	UpdateSelect();

	// ����̍X�V
	UpdateDecide();
}

//============================================================
//	�I���̍X�V����
//============================================================
void CStartStateDecideName::UpdateSelect(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���

	// �O��̑I������ۑ�
	m_nOldSelect = m_nCurSelect;

	// �I��������
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// ���ɑI�������炷
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// �E�ɑI�������炷
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}

	// �O��̑I��v�f�̐F�𔒐F�ɐݒ�
	m_apSelect[m_nOldSelect]->SetColor(select::COL_DEFAULT);

	// ���݂̑I��v�f�̐F�����F�ɐݒ�
	m_apSelect[m_nCurSelect]->SetColor(select::COL_CHOICE);
}

//============================================================
//	����̍X�V����
//============================================================
void CStartStateDecideName::UpdateDecide(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_Z) || pKey->IsTrigger(DIK_RETURN))
	{
		// �I�����ɉ����đJ�ڐ��ύX
		switch (m_nCurSelect)
		{ // ���݂̑I�������Ƃ̏���
		case SELECT_NO:
			m_pContext->ChangeState(new CStartStateCreateName);	// �������
			break;

		case SELECT_YES:
			// TODO�F���O�m�莞�̉��o�I
			break;

		default:
			assert(false);
			break;
		}
	}
}

//============================================================
//	���O�U���̍X�V����
//============================================================
void CStartStateDecideName::UpdateShakeName(const float fDeltaTime)
{
	// ���݂̑ҋ@���Ԃ����Z
	m_fCurTimeShake += fDeltaTime;
	if (m_fCurTimeShake >= 0.018f)
	{ // �ҋ@���I������ꍇ

		// ���݂̑ҋ@���Ԃ�������
		m_fCurTimeShake = 0.0f;

		// �������Ԃ�Ԃ񓮂���
		D3DXVECTOR3 rot = m_pName->GetVec3Rotation();
		rot.z = 0.011f * (float)(rand() % 3 - 1);
		m_pName->SetVec3Rotation(rot);
	}
}

//============================================================
//	�������Ȃ���Ԃ̍X�V����
//============================================================
void CStartStateDecideName::StateUpdateNone(const float fDeltaTime)
{

}

//============================================================
//	���O�̈ړ���Ԃ̍X�V����
//============================================================
void CStartStateDecideName::StateUpdateMove(const float fDeltaTime)
{
	// �o�ߎ�����i�߂�
	m_fCurTimeMove += fDeltaTime;
	if (useful::LimitMaxNum(m_fCurTimeMove, MOVE_TIME))
	{ // �o�߂��������ꍇ

		// �������Ȃ���Ԃɂ���
		m_state = STATE_NONE;
	}

	// �o�ߎ����̊������v�Z
	float fRate = easeing::Liner(m_fCurTimeMove, 0.0f, MOVE_TIME);

	D3DXVECTOR3 posDest = name::DEST_POS;
	posDest.x = SCREEN_CENT.x - f * 0.75f;

	D3DXVECTOR3 pos = posDest - name::INIT_POS;
	m_pName->SetVec3Position(name::INIT_POS + pos * fRate);

	float fHeight = name::DEST_HEIGHT - name::INIT_HEIGHT;
	m_pName->SetCharHeight(name::INIT_HEIGHT + fHeight * fRate);
}
