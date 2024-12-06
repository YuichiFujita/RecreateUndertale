//============================================================
//
//	���O�ڋ߃}�l�[�W���[���� [nearNameManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "nearNameManager.h"
#include "manager.h"
#include "sound.h"
#include "shakeString2D.h"
#include "string2D.h"
#include "text2D.h"
#include "loadtext.h"
#include "userdataManager.h"
#include "playerStatus.h"
#include "playerItem.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char*	PATH		= "data\\TEXT\\start.txt";	// �e�L�X�g�p�X
	const int	PRIORITY	= 6;	// �D�揇��
	const float	MOVE_TIME	= 4.0f;	// �ړ�����
	const float FADE_ADDOUT	= 0.2f;	// �A�E�g�̃��l������
	const float FADE_SUBIN	= 3.0f;	// �C���̃��l������

	namespace title
	{	
		const char*	FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const char*	PATH = "data\\TEXT\\naming.txt";	// �e�L�X�g�p�X
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;	// �����c��
		const float	LINE_HEIGHT	= 54.0f;	// �s�ԏc��

		const VECTOR3	POS = VECTOR3(270.0f, 130.0f, 0.0f);	// �ʒu
		const VECTOR3	ROT = VEC3_ZERO;			// ����
		const COLOR		COL = color::White();		// �F
		const EAlignX	ALIGN_X = XALIGN_LEFT;		// ���z�u
		const EAlignY	ALIGN_Y = YALIGN_CENTER;	// �c�z�u
	}

	namespace name
	{
		const char*	FONT	= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC	= false;		// �C�^���b�N
		const float	INIT_HEIGHT	= 42.0f;	// ���������c��
		const float	DEST_HEIGHT	= 148.0f;	// �ڕW�����c��
		const float	DEST_POSY	= 385.0f;	// �ڕW�ʒuY
		const float	NEXT_TIME	= 0.035f;	// �����U���̑ҋ@����
		const float WAIT_TIME	= 0.018f;	// �U���̑ҋ@����
		const float	MOVE_POS	= 1.5f;		// �ʒu�̃����_���U����
		const float MOVE_ROT	= 0.011f;	// �����̃����_���ϓ���

		const VECTOR3	INIT_POS = VECTOR3(360.0f, 155.0f, 0.0f);	// �����ʒu
		const VECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR		COL = color::White();	// �F
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// ���z�u
	}

	namespace select
	{
		const char*	FONT		= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const char* STRING[]	= { "������", "�͂�" };		// �I����������
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;	// �����c��
		const float	LINE_WIDTH	= 500.0f;	// ��ԏc��

		const VECTOR3 POS = VECTOR3(180.0f, 615.0f, 0.0f);	// �ʒu
		const VECTOR3 ROT = VEC3_ZERO;				// ����
		const COLOR COL_DEFAULT	= color::White();	// �ʏ�F
		const COLOR COL_CHOICE	= color::Yellow();	// �I��F
		const EAlignX ALIGN_X	= XALIGN_LEFT;		// ���z�u
	}
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(select::STRING) == CNearNameManager::SELECT_MAX, "ERROR : Array Count Mismatch");

//************************************************************
//	�e�N���X [CNearNameManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CNearNameManager::CNearNameManager() :
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
CNearNameManager::~CNearNameManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CNearNameManager::Init()
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

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pTitle->SetPriority(PRIORITY);

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

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pName->SetPriority(PRIORITY);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �����ʒu�I�t�Z�b�g
		VECTOR3 offset = VECTOR3(select::LINE_WIDTH * i, 0.0f, 0.0f);

		// �I�����̐���
		m_apSelect[i] = CString2D::Create
		( // ����
			select::FONT,			// �t�H���g�p�X
			select::ITALIC,			// �C�^���b�N
			select::STRING[i],		// �w�蕶����
			select::POS + offset,	// ���_�ʒu
			select::CHAR_HEIGHT,	// �����c��
			select::ALIGN_X,		// ���z�u
			select::ROT,			// ���_����
			select::COL_DEFAULT		// �F
		);

		// �D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(PRIORITY);
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CNearNameManager::Uninit()
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
}

//============================================================
//	�X�V����
//============================================================
CNearNameManager::ESelect CNearNameManager::Update(const float fDeltaTime)
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
		return UpdateDecide();
	}

	return SELECT_NONE;
}

//============================================================
//	�Q�[����ʂ̑J�ڏ���
//============================================================
void CNearNameManager::TransGame()
{
	CUserDataManager* pUserData = CUserDataManager::GetInstance();	// ���[�U�[�f�[�^�}�l�[�W���[
	CPlayerStatus status;	// �X�e�[�^�X���
	CPlayerItem item;		// �����A�C�e�����

	// ���[�U�[�f�[�^���Ȃ��ꍇ�G���[
	assert(pUserData != nullptr);

	// �^�C�g���̏I��
	SAFE_UNINIT(m_pTitle);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I�����̏I��
		SAFE_UNINIT(m_apSelect[i]);
	}

	// �����f�[�^�̏�����
	pUserData->InitAllData(&status, &item);

	// �쐬�������O�̐ݒ�
	status.SetName(m_pName->GetStr());

	// �����f�[�^�̏����o��
	pUserData->SaveAllData(&status, &item);

	// �t�V���o�����Đ�
	PLAY_SOUND(CSound::LABEL_SE_CYMBAL);

	// �Q�[����ʂɑJ�ڂ���
	GET_MANAGER->SetFadeScene(CScene::MODE_GAME, 0.0f, FADE_ADDOUT, FADE_SUBIN, color::White(0.0f));
}

//============================================================
//	��������
//============================================================
CNearNameManager* CNearNameManager::Create
(
	const std::string& rName,					// �\����
	const std::vector<std::wstring>& rVecStr	// �^�C�g�������e�L�X�g
)
{
	// ���O�ڋ߃}�l�[�W���[�̐���
	CNearNameManager* pNearNameManager = new CNearNameManager;
	if (pNearNameManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���O�ڋ߃}�l�[�W���[�̏�����
		if (FAILED(pNearNameManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���O�ڋ߃}�l�[�W���[�̔j��
			SAFE_DELETE(pNearNameManager);
			return nullptr;
		}

		// ���O��ݒ�
		pNearNameManager->SetName(rName);

		// �^�C�g���e�L�X�g������
		loadtext::BindText(pNearNameManager->m_pTitle, rVecStr);

		// �m�ۂ����A�h���X��Ԃ�
		return pNearNameManager;
	}
}

//============================================================
//	�j������
//============================================================
void CNearNameManager::Release(CNearNameManager*& prNearNameManager)
{
	// ���O�ڋ߃}�l�[�W���[�̏I��
	assert(prNearNameManager != nullptr);
	prNearNameManager->Uninit();

	// �������J��
	SAFE_DELETE(prNearNameManager);
}

//============================================================
//	�I���̍X�V����
//============================================================
void CNearNameManager::UpdateSelect()
{
	CInputKeyboard* pKey = GET_INPUTKEY;	// �L�[�{�[�h���

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
CNearNameManager::ESelect CNearNameManager::UpdateDecide()
{
	if (input::Decide())
	{
		// ���݂̑I������Ԃ�
		return (ESelect)m_nCurSelect;
	}

	// �I�𖳂���Ԃ�
	return SELECT_NONE;
}

//============================================================
//	���O�̐U������
//============================================================
void CNearNameManager::ShakeName(const float fDeltaTime)
{
	// ���݂̑ҋ@���Ԃ����Z
	m_fCurTimeShake += fDeltaTime;
	if (m_fCurTimeShake >= name::WAIT_TIME)
	{ // �ҋ@���I������ꍇ

		VECTOR3 rotName = VEC3_ZERO;				// ���O����
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
void CNearNameManager::MoveName(const float fDeltaTime)
{
	// �ړ����Ȃ��󋵂Ȃ甲����
	if (!m_bMove) { return; }

	// �o�ߎ����̊������v�Z
	float fRate = easing::Liner(m_fCurTimeMove, 0.0f, MOVE_TIME);

	// �ڕW�ւ̍������v�Z
	VECTOR3 posDest = VECTOR3(m_fNameDestPosX, name::DEST_POSY, 0.0f);	// �ڕW�ʒu
	VECTOR3 posDiff = posDest - name::INIT_POS;					// �����ʒu
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

//============================================================
//	���O�̐ݒ菈��
//============================================================
void CNearNameManager::SetName(const std::string& rName)
{
	// �������̖��O��ݒ�
	m_pName->SetString(rName);

	// ���O�̖ڕWX���W���v�Z
	float fDestStrWidth = m_pName->GetStrWidth() * (name::DEST_HEIGHT / name::INIT_HEIGHT);	// ������̖ڕW����
	m_fNameDestPosX = SCREEN_CENT.x - fDestStrWidth * 0.5f;
}
