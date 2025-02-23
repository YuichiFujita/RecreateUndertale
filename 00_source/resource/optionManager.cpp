//============================================================
//
//	�ݒ�}�l�[�W���[���� [optionManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "optionManager.h"
#include "manager.h"
#include "string2D.h"
#include "loadtext.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char*	PATH = "data\\TXT\\TEXT\\option.txt";				// �e�L�X�g�p�X
	const char*	FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
	const bool	ITALIC = false;	// �C�^���b�N
	const int	PRIORITY = 6;	// �D�揇��

	namespace title
	{	
		const VECTOR3	POS = VECTOR3(SCREEN_CENT.x, 70.0f, 0.0f);	// �ʒu
		const VECTOR3	ROT = VEC3_ZERO;			// ����
		const COLOR		COL = color::White();		// �F
		const EAlignX	ALIGN_X = XALIGN_CENTER;	// ���z�u
		const float		HEIGHT = 90.0f;				// �����c��
	}

	namespace select
	{
		const VECTOR3	POS = VECTOR3(55.0f, 140.0f, 0.0f);	// �ʒu
		const VECTOR3	ROT = VEC3_ZERO;					// ����
		const COLOR		COL_DEFAULT	= color::White();		// �ʏ�F
		const COLOR		COL_CHOICE	= color::Yellow();		// �I��F
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// ���z�u
		const float		CHAR_HEIGHT = 42.0f;	// �����c��
		const float		LINE_HEIGHT = 54.0f;	// �s�ԏc��
	}
}

//************************************************************
//	�e�N���X [COptionManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
COptionManager::COptionManager() :
	m_pTitle	 (nullptr),	// �^�C�g��
	m_nCurSelect (0),		// ���݂̑I����
	m_nOldSelect (0)		// �O��̑I����
{
	// �����o�ϐ����N���A
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I����
}

//============================================================
//	�f�X�g���N�^
//============================================================
COptionManager::~COptionManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT COptionManager::Init()
{
	// �����o�ϐ���������
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I����
	m_pTitle	 = nullptr;	// �^�C�g��
	m_nCurSelect = 0;		// ���݂̑I����
	m_nOldSelect = 0;		// �O��̑I����

	// �^�C�g���̐���
	m_pTitle = CString2D::Create
	( // ����
		FONT,			// �t�H���g�p�X
		ITALIC,			// �C�^���b�N
		L"",			// �w�蕶����
		title::POS,		// ���_�ʒu
		title::HEIGHT,	// �����c��
		title::ALIGN_X,	// ���z�u
		title::ROT,		// ���_����
		title::COL		// �F
	);

	// �D�揇�ʂ�ݒ�
	m_pTitle->SetPriority(PRIORITY);

	// �����������
	loadtext::BindString(m_pTitle, loadtext::LoadText(PATH, TEXT_TITLE));

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �����ʒu�I�t�Z�b�g
		VECTOR3 offset = VECTOR3(0.0f, select::LINE_HEIGHT * i, 0.0f);

		// �I�����̐���
		m_apSelect[i] = CString2D::Create
		( // ����
			FONT,					// �t�H���g�p�X
			ITALIC,					// �C�^���b�N
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
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(PATH, TEXT_CLOSE + i));
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void COptionManager::Uninit()
{
	// �^�C�g���̏I��
	SAFE_UNINIT(m_pTitle);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I�����̏I��
		SAFE_UNINIT(m_apSelect[i]);
	}
}

//============================================================
//	�X�V����
//============================================================
bool COptionManager::Update(const float fDeltaTime)
{
	// �I���̍X�V
	UpdateSelect();

	// ����̍X�V
	return UpdateDecide();	// ��ԑJ�ڂ̑��삪�������ꍇtrue��Ԃ�
}

//============================================================
//	��������
//============================================================
COptionManager* COptionManager::Create()
{
	// �ݒ�}�l�[�W���[�̐���
	COptionManager* pOptionManager = new COptionManager;
	if (pOptionManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �ݒ�}�l�[�W���[�̏�����
		if (FAILED(pOptionManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �ݒ�}�l�[�W���[�̔j��
			SAFE_DELETE(pOptionManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pOptionManager;
	}
}

//============================================================
//	�j������
//============================================================
void COptionManager::Release(COptionManager*& prOptionManager)
{
	// �ݒ�}�l�[�W���[�̏I��
	assert(prOptionManager != nullptr);
	prOptionManager->Uninit();

	// �������J��
	SAFE_DELETE(prOptionManager);
}

//============================================================
//	�I���̍X�V����
//============================================================
void COptionManager::UpdateSelect()
{
	// �O��̑I������ۑ�
	m_nOldSelect = m_nCurSelect;

	// �I��������
	CInputKeyboard* pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_DOWN))
	{
		// ��ɑI�������炷
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		// ���ɑI�������炷
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}

	// �O��̑I��v�f�̐F�𔒐F�ɐݒ�
	m_apSelect[m_nOldSelect]->SetColor(select::COL_DEFAULT);

	// ���݂̑I��v�f�̐F�����F�ɐݒ�
	m_apSelect[m_nCurSelect]->SetColor(select::COL_CHOICE);
}

//============================================================
//	����̍X�V����
//============================================================
bool COptionManager::UpdateDecide()
{
	if (input::Decide())
	{
		// �I�����ɉ����đJ�ڐ��ύX
		switch (m_nCurSelect)
		{ // ���݂̑I�������Ƃ̏���
		case SELECT_CLOSE:
			return true;

		default:
			assert(false);
			break;
		}
	}

	return false;
}
