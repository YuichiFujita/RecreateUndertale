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
#include "sound.h"
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
	const float FADE_ADDOUT	= 0.2f;	// �A�E�g�̃��l������
	const float FADE_SUBIN	= 3.0f;	// �C���̃��l������

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
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
	}

	namespace name
	{
		const char	*FONT	= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC	= false;		// �C�^���b�N
		const float	INIT_HEIGHT	= 42.0f;	// ���������c��
		const float	DEST_HEIGHT	= 148.0f;	// �ڕW�����c��
		const float	DEST_POSY	= 385.0f;	// �ڕW�ʒuY
		const float	NEXT_TIME	= 0.035f;	// �����U���̑ҋ@����
		const float WAIT_TIME	= 0.018f;	// �U���̑ҋ@����
		const float	MOVE_POS	= 1.5f;		// �ʒu�̃����_���U����
		const float MOVE_ROT	= 0.011f;	// �����̃����_���ϓ���

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;			// ���z�u
		const D3DXVECTOR3	INIT_POS = D3DXVECTOR3(360.0f, 155.0f, 0.0f);	// �����ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
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
		const COLOR COL_DEFAULT	= color::White();	// �ʏ�F
		const COLOR COL_CHOICE	= color::Yellow();	// �I��F
	}
}

//************************************************************
//	�q�N���X [CStartStateDecideName] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateDecideName::CStartStateDecideName() :
	m_pTitle		(nullptr),	// �^�C�g��
	m_pName			(nullptr),	// ���O
	m_nCurSelect	(0),		// ���݂̑I����
	m_nOldSelect	(0),		// �O��̑I����
	m_fCurTimeShake	(0.0f),		// ���݂̐U���̌o�ߎ���
	m_fCurTimeMove	(0.0f),		// ���݂̈ړ��̌o�ߎ���
	m_fNameDestPosX	(0.0f),		// ���O�̖ڕW�ʒuX
	m_bMove			(false)		// ���O�̈ړ���
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
	m_pTitle		= nullptr;	// �^�C�g��
	m_pName			= nullptr;	// ���O
	m_nCurSelect	= 0;		// ���݂̑I����
	m_nOldSelect	= 0;		// �O��̑I����
	m_fCurTimeShake	= 0.0f;		// ���݂̐U���̌o�ߎ���
	m_fCurTimeMove	= 0.0f;		// ���݂̈ړ��̌o�ߎ���
	m_fNameDestPosX	= 0.0f;		// ���O�̖ڕW�ʒuX
	m_bMove			= true;		// ���O�̈ړ���

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
		name::MOVE_POS,		// �U���ړ���
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

	// ���O�̖ڕWX���W���v�Z
	float fDestStrWidth = m_pName->GetStrWidth() * (name::DEST_HEIGHT / name::INIT_HEIGHT);	// ������̖ڕW����
	m_fNameDestPosX = SCREEN_CENT.x - fDestStrWidth * 0.5f;

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
	// ���O�̈ړ�
	MoveName(fDeltaTime);

	// ���O�̐U��
	ShakeName(fDeltaTime);

	if (!GET_MANAGER->GetFade()->IsFade())
	{ // �t�F�[�h���Ă��Ȃ��ꍇ

		// �I���̍X�V
		UpdateSelect();

		// ����̍X�V
		UpdateDecide();
	}
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
	if (input::Decide())
	{
		// �I�����ɉ����đJ�ڐ��ύX
		switch (m_nCurSelect)
		{ // ���݂̑I�������Ƃ̏���
		case SELECT_NO:

			// ������Ԃɂ���
			m_pContext->ChangeState(new CStartStateCreateName);
			break;

		case SELECT_YES:

			// �Q�[����ʂɑJ�ڂ���
			TransGame();
			break;

		default:
			assert(false);
			break;
		}
	}
}

//============================================================
//	�Q�[����ʂ̑J�ڏ���
//============================================================
void CStartStateDecideName::TransGame(void)
{
	// �^�C�g���̏I��
	SAFE_UNINIT(m_pTitle);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I�����̏I��
		SAFE_UNINIT(m_apSelect[i]);
	}

	// �t�V���o�����Đ�
	PLAY_SOUND(CSound::LABEL_SE_CYMBAL);

	// �Q�[����ʂɑJ�ڂ���
	GET_MANAGER->SetFadeScene(CScene::MODE_GAME, 0.0f, FADE_ADDOUT, FADE_SUBIN, color::White(0.0f));
}

//============================================================
//	���O�̐U������
//============================================================
void CStartStateDecideName::ShakeName(const float fDeltaTime)
{
	// ���݂̑ҋ@���Ԃ����Z
	m_fCurTimeShake += fDeltaTime;
	if (m_fCurTimeShake >= name::WAIT_TIME)
	{ // �ҋ@���I������ꍇ

		D3DXVECTOR3 rotName = VEC3_ZERO;			// ���O����
		float fRefRand = (float)(rand() % 3 - 1);	// �����_���Q�ƒl

		// ���݂̑ҋ@���Ԃ�������
		m_fCurTimeShake = 0.0f;

		// �����������_���ɐU��������
		rotName.z = name::MOVE_ROT * fRefRand;	// �����_���������v�Z
		m_pName->SetVec3Rotation(rotName);		// ���O�����𔽉f
	}
}

//============================================================
//	���O�̈ړ���Ԃ̍X�V����
//============================================================
void CStartStateDecideName::MoveName(const float fDeltaTime)
{
	// �ړ����Ȃ��󋵂Ȃ甲����
	if (!m_bMove) { return; }

	// �o�ߎ����̊������v�Z
	float fRate = easing::Liner(m_fCurTimeMove, 0.0f, MOVE_TIME);

	// �ڕW�ւ̍������v�Z
	D3DXVECTOR3 posDest = D3DXVECTOR3(m_fNameDestPosX, name::DEST_POSY, 0.0f);	// �ڕW�ʒu
	D3DXVECTOR3 posDiff = posDest - name::INIT_POS;				// �����ʒu
	float fHeightDiff = name::DEST_HEIGHT - name::INIT_HEIGHT;	// �����c��

	// �o�ߎ�����i�߂�
	m_fCurTimeMove += fDeltaTime;
	if (useful::LimitMaxNum(m_fCurTimeMove, MOVE_TIME))
	{ // �ړ����������ꍇ

		// �ړ����~
		m_bMove = false;
	}

	// ���݈ʒu�𔽉f
	m_pName->SetVec3Position(name::INIT_POS + posDiff * fRate);

	// ���ݏc���𔽉f
	m_pName->SetCharHeight(name::INIT_HEIGHT + fHeightDiff * fRate);
}
