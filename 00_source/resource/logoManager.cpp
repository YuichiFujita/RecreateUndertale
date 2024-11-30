//============================================================
//
//	���S�}�l�[�W���[���� [logoManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "logoManager.h"
#include "inputManager.h"
#include "introManager.h"
#include "manager.h"
#include "sound.h"
#include "object2D.h"
#include "string2D.h"
#include "loadtext.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char*	TEXTURE		= "data\\TEXTURE\\logo000.png";	// ���S�e�N�X�`��
	const int	PRIORITY	= 6;		// �D�揇��
	const float	DISP_TIME	= 3.0f;		// ���S�\������
	const float	TRANS_TIME	= 17.0f;	// �C���g���J�ڂ̗]�C����
	const char*	CMD_BALL	= "ball";	// BALL���ʉ���炷�R�}���h����

	namespace str
	{
		const char*	FONT	= "data\\FONT\\Crypt of Tomorrow.ttf";	// �t�H���g�p�X
		const char*	PATH	= "data\\TEXT\\start.txt";	// �e�L�X�g�p�X
		const char* STRING	= "[PRESS Z OR ENTER]";		// �\��������
		const bool	ITALIC	= false;	// �C�^���b�N
		const float	HEIGHT	= 22.5f;	// �����c��

		const VECTOR3	POS = VECTOR3(SCREEN_CENT.x, 545.0f, 0.0f);	// �ʒu
		const VECTOR3	ROT = VEC3_ZERO;							// ����
		const COLOR		COL = COLOR(0.5f, 0.5f, 0.5f, 1.0f);		// �F
		const EAlignX	ALIGN_X = XALIGN_CENTER;	// ���z�u
	}
}

//************************************************************
//	�e�N���X [CLogoManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CLogoManager::CLogoManager() :
	m_pLogo		(nullptr),	// �^�C�g�����S
	m_pCont		(nullptr),	// �������
	m_fCurTime	(0.0f),		// ���݂̑ҋ@����
	m_bSndBall	(false)		// BALL�R�}���h�Đ��t���O
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CLogoManager::~CLogoManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CLogoManager::Init()
{
	// �����o�ϐ���������
	m_pLogo		= nullptr;	// �^�C�g�����S
	m_pCont		= nullptr;	// �������
	m_fCurTime	= 0.0f;		// ���݂̑ҋ@����
	m_bSndBall	= false;	// BALL�R�}���h�Đ��t���O

	// �^�C�g�����S�̐���
	m_pLogo = CObject2D::Create(SCREEN_CENT, SCREEN_SIZE);
	if (m_pLogo == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pLogo->BindTexture(TEXTURE);

	// �D�揇�ʂ�ݒ�
	m_pLogo->SetPriority(PRIORITY);

	// �C���g���m�C�Y���Đ�
	PLAY_SOUND(CSound::LABEL_SE_INTRONOISE);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CLogoManager::Uninit()
{
	// �^�C�g�����S�̏I��
	SAFE_UNINIT(m_pLogo);

	// ��������̏I��
	SAFE_UNINIT(m_pCont);
}

//============================================================
//	�X�V����
//============================================================
bool CLogoManager::Update(const float fDeltaTime)
{
	// ����\���E�J�ڂ̍X�V
	UpdateDispTrans(fDeltaTime);

	// �R�}���h���͂̍X�V
	UpdateCommand();

	// ��ԑJ�ڂ̑��삪�������ꍇtrue��Ԃ�
	if (input::Decide()) { return true; }

	return false;
}

//============================================================
//	��������
//============================================================
CLogoManager* CLogoManager::Create()
{
	// ���S�}�l�[�W���[�̐���
	CLogoManager* pLogoManager = new CLogoManager;
	if (pLogoManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���S�}�l�[�W���[�̏�����
		if (FAILED(pLogoManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���S�}�l�[�W���[�̔j��
			SAFE_DELETE(pLogoManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pLogoManager;
	}
}

//============================================================
//	�j������
//============================================================
void CLogoManager::Release(CLogoManager*& prLogoManager)
{
	// ���S�}�l�[�W���[�̏I��
	assert(prLogoManager != nullptr);
	prLogoManager->Uninit();

	// �������J��
	SAFE_DELETE(prLogoManager);
}

//============================================================
//	����\���E�J�ڂ̍X�V����
//============================================================
void CLogoManager::UpdateDispTrans(const float fDeltaTime)
{
	if (m_pCont == nullptr)
	{ // �����������\���̏ꍇ

		// �ҋ@������i�߂�
		m_fCurTime += fDeltaTime;
		if (m_fCurTime >= DISP_TIME)
		{ // �ҋ@�I�������ꍇ

			// �ҋ@���Ԃ�������
			m_fCurTime = 0.0f;

			// ��������̐���
			m_pCont = CString2D::Create
			( // ����
				str::FONT,		// �t�H���g�p�X
				str::ITALIC,	// �C�^���b�N
				str::STRING,	// �w�蕶����
				str::POS,		// ���_�ʒu
				str::HEIGHT,	// �����c��
				str::ALIGN_X,	// ���z�u
				str::ROT,		// ���_����
				str::COL		// �F
			);

			// �D�揇�ʂ�ݒ�
			m_pCont->SetPriority(PRIORITY);
		}
	}
	else
	{ // ����������\���ς݂̏ꍇ

		// �ҋ@������i�߂�
		m_fCurTime += fDeltaTime;
		if (m_fCurTime >= TRANS_TIME)
		{ // �ҋ@�I�������ꍇ

			// �ҋ@���Ԃ�������
			m_fCurTime = 0.0f;

			// ���S�\�����X�L�b�v����
			CIntroManager::SetEnableLogoSkip(true);

			// �C���g����ʂɑJ�ڂ���
			GET_MANAGER->SetScene(CScene::MODE_INTRO);
		}
	}
}

//============================================================
//	�R�}���h���͂̍X�V����
//============================================================
void CLogoManager::UpdateCommand()
{
	// BALL���ʉ����Đ��ς݂̏ꍇ������
	if (m_bSndBall) { return; }

	// �Ō���ɓ��̓L�[�̃t���O��ǉ�
	CInputKeyboard* pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_B))
	{
		m_sFragInput.push_back('b');
	}
	if (pKey->IsTrigger(DIK_A))
	{
		m_sFragInput.push_back('a');
	}
	if (pKey->IsTrigger(DIK_L))
	{
		m_sFragInput.push_back('l');
	}

	// ���̓t���O�Q�ɃR�}���h���������Ă���u�Ԃ����邩���m�F
	if (m_sFragInput.find(CMD_BALL) != std::string::npos)
	{ // �R�}���h�����񂪑��݂����ꍇ

		// BALL���ʉ����Đ��ς݂ɂ���
		m_bSndBall = true;

		// BALL���͌��ʉ����Đ�
		PLAY_SOUND(CSound::LABEL_SE_BALLCHIME);
	}
}
