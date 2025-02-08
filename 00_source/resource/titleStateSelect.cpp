//============================================================
//
//	�J�ڑI����ԏ��� [titleStateSelect.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "titleStateSelect.h"
#include "titleManager.h"
#include "manager.h"
#include "playerStatus.h"
#include "userdataManager.h"
#include "string2D.h"
#include "version.h"
#include "loadtext.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* PATH	 = "data\\TEXT\\title.txt";	// �e�L�X�g�p�X
	const char*	FONT	 = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
	const bool	ITALIC	 = false;	// �C�^���b�N
	const float	HEIGHT	 = 42.0f;	// �����c��
	const int	PRIORITY = 6;		// �^�C�g���̗D�揇��

	namespace name
	{
		const VECTOR3	POS = VECTOR3(198.0f, 207.0f, 0.0f);	// �ʒu
		const VECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR		COL = color::White();	// �F
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// ���z�u
	}

	namespace love
	{
		const VECTOR3	POS = VECTOR3(480.0f, 207.0f, 0.0f);	// �ʒu
		const VECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR		COL = color::White();	// �F
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// ���z�u
	}

	namespace time
	{
		const VECTOR3	POS = VECTOR3(687.0f, 207.0f, 0.0f);	// �ʒu
		const VECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR		COL = color::White();	// �F
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// ���z�u
	}

	namespace save
	{
		const VECTOR3	POS = VECTOR3(SCREEN_CENT.x, 260.0f, 0.0f);	// �ʒu
		const VECTOR3	ROT = VEC3_ZERO;			// ����
		const COLOR		COL = color::White();		// �F
		const EAlignX	ALIGN_X = XALIGN_CENTER;	// ���z�u
	}

	namespace select
	{
		const VECTOR3 POS_CONTINUE	= VECTOR3(217.0f, 336.0f, 0.0f);	// �R���e�j���[�I���ʒu
		const VECTOR3 POS_RESET		= VECTOR3(597.0f, 336.0f, 0.0f);	// ���Z�b�g�I���ʒu
		const VECTOR3 POS_SETTING	= VECTOR3(399.0f, 396.0f, 0.0f);	// �ݒ�I���ʒu

		const VECTOR3 POS_SAVEDATA[] =	// �Z�[�u�f�[�^����̑I���ʒu
		{
			POS_CONTINUE,	// �R���e�j���[�I���ʒu
			POS_RESET,		// ���Z�b�g�I���ʒu
		};
		const int NUM_SAVEDATA = NUM_ARRAY(POS_SAVEDATA);	// �Z�[�u�f�[�^����̑I��

		const COLOR COL_DEFAULT = color::White();	// �ʏ�F
		const COLOR COL_CHOICE	= color::Yellow();	// �I��F
		const VECTOR3 ROT		= VEC3_ZERO;		// ����
		const EAlignX ALIGN_X	= XALIGN_LEFT;		// ���z�u
	}
}

//************************************************************
//	�q�N���X [CTitleStateSelect] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTitleStateSelect::CTitleStateSelect() :
	m_pName		(nullptr),		// ���O���
	m_pLove		(nullptr),		// ���x�����
	m_pTime		(nullptr),		// ���v���C���ԏ��
	m_pSave		(nullptr),		// �Z�[�u�n�_���
	m_pVersion	(nullptr),		// �o�[�W�����\�L���
	m_curSelect	(GRID2_ZERO),	// ���݂̑I����
	m_oldSelect	(GRID2_ZERO)	// �O��̑I����
{
	// �I�𕶎��z����N���A
	m_vecSelect.clear();
}

//============================================================
//	�f�X�g���N�^
//============================================================
CTitleStateSelect::~CTitleStateSelect()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTitleStateSelect::Init()
{
	CUserDataManager* pUserDataManager = CUserDataManager::GetInstance();	// ���[�U�[�f�[�^�}�l�[�W���[
	CPlayerStatus status;	// �v���C���[�X�e�[�^�X���

	// �����o�ϐ���������
	m_pName		= nullptr;		// ���O���
	m_pLove		= nullptr;		// ���x�����
	m_pTime		= nullptr;		// ���v���C���ԏ��
	m_pSave		= nullptr;		// �Z�[�u�n�_���
	m_pVersion	= nullptr;		// �o�[�W�����\�L���
	m_curSelect	= GRID2_ZERO;	// ���݂̑I����
	m_oldSelect	= GRID2_ZERO;	// �O��̑I����

	// �I�𕶎��z���������
	m_vecSelect.clear();

	// �v���C���[�X�e�[�^�X�̓Ǎ�
	pUserDataManager->LoadPlayerStatus(&status);

	//--------------------------------------------------------
	//	���O�̏�����/�ݒ�
	//--------------------------------------------------------
	// ���O�̐���
	m_pName = CString2D::Create
	( // ����
		FONT,				// �t�H���g�p�X
		ITALIC,				// �C�^���b�N
		status.GetName(),	// �w�蕶����
		name::POS,			// ���_�ʒu
		HEIGHT,				// �����c��
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

	//--------------------------------------------------------
	//	���x���̏�����/�ݒ�
	//--------------------------------------------------------
	const std::string sLove = "LV " + std::to_string(status.GetLove());	// ���x��������

	// ���x���̐���
	m_pLove = CString2D::Create
	( // ����
		FONT,			// �t�H���g�p�X
		ITALIC,			// �C�^���b�N
		sLove,			// �w�蕶����
		love::POS,		// ���_�ʒu
		HEIGHT,			// �����c��
		love::ALIGN_X,	// ���z�u
		love::ROT,		// ���_����
		love::COL		// �F
	);
	if (m_pLove == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pLove->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	���v���C���Ԃ̏�����/�ݒ�
	//--------------------------------------------------------
	const std::string sTime = pUserDataManager->GetStrPlayTime();	// ���v���C���ԕ�����

	// ���v���C���Ԃ̐���
	m_pTime = CString2D::Create
	( // ����
		FONT,			// �t�H���g�p�X
		ITALIC,			// �C�^���b�N
		sTime,			// �w�蕶����
		time::POS,		// ���_�ʒu
		HEIGHT,			// �����c��
		time::ALIGN_X,	// ���z�u
		time::ROT,		// ���_����
		time::COL		// �F
	);
	if (m_pTime == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pTime->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	�Z�[�u�n�_�̏�����/�ݒ�
	//--------------------------------------------------------
	// �Z�[�u�n�_�̐���
	m_pSave = CString2D::Create
	( // ����
		FONT,				// �t�H���g�p�X
		ITALIC,				// �C�^���b�N
		L"�����ɃZ�[�u��",	// �w�蕶����	// TODO�F�����ɃZ�[�u�n�_�̖��O
		save::POS,			// ���_�ʒu
		HEIGHT,				// �����c��
		save::ALIGN_X,		// ���z�u
		save::ROT,			// ���_����
		save::COL			// �F
	);
	if (m_pSave == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pSave->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	�Z�[�u�f�[�^����I�����̏�����/�ݒ�
	//--------------------------------------------------------
	// ����s���̔z����g��
	m_vecSelect.emplace_back();

	for (int i = 0; i < select::NUM_SAVEDATA; i++)
	{ // ��̑I�����̑������J��Ԃ�

		// �Z�[�u�f�[�^����̑I��������
		CString2D* pSelect = CString2D::Create
		( // ����
			FONT,						// �t�H���g�p�X
			ITALIC,						// �C�^���b�N
			L"",						// �w�蕶����
			select::POS_SAVEDATA[i],	// ���_�ʒu
			HEIGHT,						// �����c��
			select::ALIGN_X,			// ���z�u
			select::ROT,				// ���_����
			select::COL_DEFAULT			// �F
		);
		if (pSelect == nullptr)
		{ // �����Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		pSelect->SetPriority(PRIORITY);

		// �����������
		loadtext::BindString(pSelect, loadtext::LoadText(PATH, CTitleManager::TEXT_CONTINUE + i));

		// ���݂̍s��̍Ō���ɐ�������������ǉ�
		m_vecSelect.back().push_back(pSelect);
	}

	//--------------------------------------------------------
	//	�ݒ�I�����̏�����/�ݒ�
	//--------------------------------------------------------
	// ����s���̔z����g��
	m_vecSelect.emplace_back();

	// �ݒ�̑I��������
	CString2D* pSetting = CString2D::Create
	( // ����
		FONT,					// �t�H���g�p�X
		ITALIC,					// �C�^���b�N
		L"",					// �w�蕶����
		select::POS_SETTING,	// ���_�ʒu
		HEIGHT,					// �����c��
		select::ALIGN_X,		// ���z�u
		select::ROT,			// ���_����
		select::COL_DEFAULT		// �F
	);
	if (pSetting == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	pSetting->SetPriority(PRIORITY);

	// �����������
	loadtext::BindString(pSetting, loadtext::LoadText(PATH, CTitleManager::TEXT_SETTING));

	// ���݂̍s��̍Ō���ɐ�������������ǉ�
	m_vecSelect.back().push_back(pSetting);

	//--------------------------------------------------------
	//	�o�[�W�����\�L�̏�����/�ݒ�
	//--------------------------------------------------------
	// �o�[�W�����\�L�̐���
	m_pVersion = CVersion::Create();
	if (m_pVersion == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CTitleStateSelect::Uninit()
{
	// ���O�̏I��
	SAFE_UNINIT(m_pName);

	// ���x���̏I��
	SAFE_UNINIT(m_pLove);

	// ���v���C���Ԃ̏I��
	SAFE_UNINIT(m_pTime);

	// �Z�[�u�n�_�̏I��
	SAFE_UNINIT(m_pSave);

	// �o�[�W�����\�L�̏I��
	SAFE_UNINIT(m_pVersion);

	for (int i = 0; i < (int)m_vecSelect.size(); i++)
	{ // �s�̑������J��Ԃ�

		for (int j = 0; j < (int)m_vecSelect[i].size(); j++)
		{ // ��̑������J��Ԃ�

			// �I�𕶎��̏I��
			SAFE_UNINIT(m_vecSelect[i][j]);
		}
	}

	// �I�𕶎��z����N���A
	m_vecSelect.clear();

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CTitleStateSelect::Update(const float fDeltaTime)
{
	// �I���̍X�V
	UpdateSelect();

	// ����̍X�V
	UpdateDecide();
}

//============================================================
//	�I���̍X�V����
//============================================================
void CTitleStateSelect::UpdateSelect()
{
	CInputKeyboard* pKey = GET_INPUTKEY;	// �L�[�{�[�h���

	// �O��̑I������ۑ�
	m_oldSelect = m_curSelect;

	// �I��������
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// ���ɑI�������炷
		int nMaxWidth = (int)m_vecSelect[m_curSelect.y].size();	// ��̍ő吔
		m_curSelect.x = (m_curSelect.x + (nMaxWidth - 1)) % nMaxWidth;
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// �E�ɑI�������炷
		int nMaxWidth = (int)m_vecSelect[m_curSelect.y].size();	// ��̍ő吔
		m_curSelect.x = (m_curSelect.x + 1) % nMaxWidth;
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		// ��ɑI�������炷
		int nMaxHeight = (int)m_vecSelect.size();	// �s�̍ő吔
		m_curSelect.y = (m_curSelect.y + (nMaxHeight - 1)) % nMaxHeight;

		// ��̑I����������
		m_curSelect.x = 0;
	}
	if (pKey->IsTrigger(DIK_DOWN))
	{
		// ���ɑI�������炷
		int nMaxHeight = (int)m_vecSelect.size();	// �s�̍ő吔
		m_curSelect.y = (m_curSelect.y + 1) % nMaxHeight;

		// ��̑I����������
		m_curSelect.x = 0;
	}

	// �O��̑I��v�f�̐F�𔒐F�ɐݒ�
	assert(m_vecSelect[m_oldSelect.y][m_oldSelect.x] != nullptr);
	m_vecSelect[m_oldSelect.y][m_oldSelect.x]->SetColor(select::COL_DEFAULT);

	// ���݂̑I��v�f�̐F�����F�ɐݒ�
	assert(m_vecSelect[m_curSelect.y][m_curSelect.x] != nullptr);
	m_vecSelect[m_curSelect.y][m_curSelect.x]->SetColor(select::COL_CHOICE);
}

//============================================================
//	����̍X�V����
//============================================================
void CTitleStateSelect::UpdateDecide()
{
	if (input::Decide())
	{
		// �I�����ɉ����đJ�ڐ��ύX
		switch (m_curSelect.x + m_curSelect.y * select::NUM_SAVEDATA)
		{ // ���݂̑I�������Ƃ̏���
		case SELECT_CONTINUE:
			GET_MANAGER->SetScene(CScene::MODE_GAME);		// �Q�[����ʂɑJ�ڂ���
			break;

		case SELECT_RESET:
			m_pContext->ChangeState(new CTitleStateReset);	// ���Z�b�g���
			break;

		case SELECT_SETTING:
			m_pContext->ChangeState(new CTitleStateOption);	// �ݒ���
			break;

		default:
			assert(false);
			break;
		}
	}
}
