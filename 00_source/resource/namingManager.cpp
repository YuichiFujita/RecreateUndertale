//============================================================
//
//	�����}�l�[�W���[���� [namingManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "namingManager.h"
#include "manager.h"
#include "string2D.h"
#include "startStateCreateName.h"

#include "startManager.h"
#include "loadtext.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *PASS_CHAR[] =	// �����z�u���̑��΃p�X
	{
		"data\\CSV\\char_hiragana.csv",	// �Ђ炪�Ȕz�u���
		"data\\CSV\\char_katakana.csv",	// �J�^�J�i�z�u���
		"data\\CSV\\char_alphabet.csv",	// �A���t�@�x�b�g�z�u���
	};
	const char *PASS = "data\\TEXT\\start.txt";	// �e�L�X�g�p�X

	const CNamingManager::ETypeChar INIT_TYPE = CNamingManager::TYPECHAR_HIRAGANA;	// ���������Z�b�g
	const int PRIORITY = 6;	// �D�揇��

	namespace select
	{
		const D3DXVECTOR3 POS[CStartStateCreateName::YSELECT_POLY_MAX][CStartStateCreateName::XSELECT_MAX] =	// �ʒu�z��
		{
			{ D3DXVECTOR3(180.0f, 530.0f, 0.0f), D3DXVECTOR3(440.0f, 530.0f, 0.0f), D3DXVECTOR3(750.0f, 530.0f, 0.0f) },
			{ D3DXVECTOR3(220.0f, 630.0f, 0.0f), D3DXVECTOR3(460.0f, 630.0f, 0.0f), D3DXVECTOR3(700.0f, 630.0f, 0.0f) },
		};

		const char	*FONT	= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC	= false;	// �C�^���b�N
		const float	HEIGHT	= 42.0f;	// �����c��

		const CString2D::EAlignX ALIGN_X	= CString2D::XALIGN_CENTER;	// ���z�u
		const D3DXVECTOR3	ROT			= VEC3_ZERO;	// ����
		const D3DXCOLOR		COL_DEFAULT	= XCOL_WHITE;	// �ʏ�F
		const D3DXCOLOR		COL_CHOICE	= XCOL_YELLOW;	// �I��F
	}
}

//************************************************************
//	�q�N���X [CNamingManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CNamingManager::CNamingManager(CStartStateCreateName *pParent) :
	m_pParent	(pParent),		// ���g���Ǘ�����e
	m_curSelect	(GRID2_ZERO),	// ���݂̑I�𕶎�
	m_oldSelect	(GRID2_ZERO)	// �O��̑I�𕶎�
{
	// �I�𕶎��z����N���A
	m_vecSelect.clear();
}

//============================================================
//	�f�X�g���N�^
//============================================================
CNamingManager::~CNamingManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CNamingManager::Init(void)
{
	// �����o�ϐ���������
	m_curSelect = GRID2_ZERO;	// ���݂̑I�𕶎�
	m_oldSelect = GRID2_ZERO;	// �O��̑I�𕶎�

	// �I�𕶎��z���������
	m_vecSelect.clear();

	for (int i = 0; i < 2; i++)
	{
		// ����s���̔z����g��
		m_vecSelect.emplace_back();

		for (int j = 0; j < 3; j++)
		{
			// �I�����̐���
			CString2D *pSelect = CString2D::Create
			( // ����
				select::FONT,		// �t�H���g�p�X
				select::ITALIC,		// �C�^���b�N
				L"",				// �w�蕶����
				select::POS[i][j],	// ���_�ʒu
				select::HEIGHT,		// �����c��
				select::ALIGN_X,	// ���z�u
				select::ROT,		// ���_����
				select::COL_DEFAULT	// �F
			);
			if (pSelect == nullptr)
			{ // �����Ɏ��s�����ꍇ

				// ���s��Ԃ�
				assert(false);
				return E_FAIL;
			}

			// �D�揇�ʂ�ݒ�
			pSelect->SetPriority(PRIORITY);

			// �����������
			loadtext::BindString(pSelect, loadtext::LoadText(PASS, CStartManager::TEXT_HIRAGANA + (i * 3) + j));

			// ���݂̍s��̍Ō���ɐ�������������ǉ�
			m_vecSelect.back().push_back(pSelect);
		}
	}

	// �z�u�̓Ǎ�
	if (FAILED(ChangeChar(INIT_TYPE)))
	{ // �Ǎ��Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CNamingManager::Uninit(void)
{
	for (int i = 0; i < (int)m_vecSelect.size(); i++)
	{ // �c�̕��������J��Ԃ�

		for (int j = 0; j < (int)m_vecSelect[i].size(); j++)
		{ // ���̕��������J��Ԃ�

			// �I�𕶎��̏I��
			SAFE_UNINIT(m_vecSelect[i][j]);
		}
	}

	// �I�𕶎��z����N���A
	m_vecSelect.clear();
}

//============================================================
//	�X�V����
//============================================================
void CNamingManager::Update(const float fDeltaTime)
{
	// �I���̍X�V
	UpdateSelect();

	// ����̍X�V
	UpdateDecide();
}

//============================================================
//	�����̕ύX����
//============================================================
HRESULT CNamingManager::ChangeChar(const ETypeChar typeChar)
{
	// ������ނ��s���Ȓl�̏ꍇ������
	if (typeChar <= NONE_IDX || typeChar >= TYPECHAR_MAX) { assert(false); return E_FAIL; }

	// �I�𕶎��̓��I�z��̃N���A
	ClearVector();

	// �z�u�̓Ǎ�
	if (FAILED(LoadArray(typeChar)))
	{ // �Ǎ��Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	��������
//============================================================
CNamingManager *CNamingManager::Create(CStartStateCreateName *pParent)
{
	// �����}�l�[�W���[�̐���
	CNamingManager *pNamingManager = new CNamingManager(pParent);
	if (pNamingManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �����}�l�[�W���[�̏�����
		if (FAILED(pNamingManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �����}�l�[�W���[�̔j��
			SAFE_DELETE(pNamingManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pNamingManager;
	}
}

//============================================================
//	�j������
//============================================================
void CNamingManager::Release(CNamingManager *&prNamingManager)
{
	// �����}�l�[�W���[�̏I��
	assert(prNamingManager != nullptr);
	prNamingManager->Uninit();

	// �������J��
	SAFE_DELETE(prNamingManager);
}

//============================================================
//	�I���̍X�V����
//============================================================
void CNamingManager::UpdateSelect(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	int nCharWidth	= GetSelectWidth();		// ���̕�����
	int nCharHeight = GetSelectHeight();	// �c�̕�����

	// �O��̑I������ۑ�
	m_oldSelect = m_curSelect;

	// �I��������
	if (pKey->IsTrigger(DIK_LEFT))
	{
		do {
			// ���ɑI�������炷
			m_curSelect.x = (m_curSelect.x + (nCharWidth - 1)) % nCharWidth;
		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		do {
			// �E�ɑI�������炷
			m_curSelect.x = (m_curSelect.x + 1) % nCharWidth;
		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		do {
			// ��ɑI�������炷
			m_curSelect.y = (m_curSelect.y + (nCharHeight - 1)) % nCharHeight;
		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}
	if (pKey->IsTrigger(DIK_DOWN))
	{
		do {
			// ���ɑI�������炷
			m_curSelect.y = (m_curSelect.y + 1) % nCharHeight;
		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}

	assert(m_vecSelect[m_oldSelect.y][m_oldSelect.x] != nullptr);

	// �O��̑I��v�f�̐F�𔒐F�ɐݒ�
	m_vecSelect[m_oldSelect.y][m_oldSelect.x]->SetColor(select::COL_DEFAULT);

	// ���݂̑I��v�f�̐F�����F�ɐݒ�
	m_vecSelect[m_curSelect.y][m_curSelect.x]->SetColor(select::COL_CHOICE);
}

//============================================================
//	����̍X�V����
//============================================================
void CNamingManager::UpdateDecide(void)
{
#if 0
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_Z) || pKey->IsTrigger(DIK_RETURN))
	{
		// �I�����ɉ����đJ�ڐ��ύX
		switch (m_nCurSelect)
		{ // ���݂̑I�������Ƃ̏���
		case SELECT_CLOSE:
			m_pContext->ChangeState(new CStartStateTutorial);	// �`���[�g���A�����
			break;

		default:
			assert(false);
			break;
		}
	}
#endif
}

//============================================================
//	�I�𕶎��̓��I�z��̃N���A����
//============================================================
void CNamingManager::ClearVector(void)
{
	for (int i = 2; i < (int)m_vecSelect.size(); i++)
	{ // �c�̕��������J��Ԃ�

		for (int j = 0; j < (int)m_vecSelect[i].size(); j++)
		{ // ���̕��������J��Ԃ�

			// �I�𕶎��̏I��
			SAFE_UNINIT(m_vecSelect[i][j]);
		}
	}

	// �I�𕶎��z����N���A
	m_vecSelect.resize(2);
}

//============================================================
//	�z�u�̓Ǎ�����
//============================================================
HRESULT CNamingManager::LoadArray(const ETypeChar typeChar)
{
	D3DXVECTOR3 posOffset = VEC3_ZERO;	// ���������ʒu
	D3DXVECTOR3 posStart = VEC3_ZERO;	// �����J�n�ʒu
	D3DXVECTOR2 charOffset = VEC2_ZERO;	// �����̃I�t�Z�b�g
	float fSpaceOffset = 0.0f;			// �󔒂̃I�t�Z�b�g

	// �t�@�C�����J��
	std::ifstream file(PASS_CHAR[typeChar]);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�����Z�b�g�A�b�v�̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	while (std::getline(file, str))
	{ // �t�@�C���̏I�[�ł͂Ȃ��ꍇ���[�v

		// �J���}��؂育�ƂɃf�[�^��Ǎ�
		std::istringstream iss(str);	// ������X�g���[��
		while (std::getline(iss, str, ','))
		{
			if (str == "START_POS")
			{
				// �J�n�ʒu��Ǎ�
				iss >> posStart.x >> posStart.y >> posStart.z;

				// �J�n�ʒu�𐶐��ʒu�ɐݒ�
				posOffset = posStart;
			}
			else if (str == "CHAR_OFFSET")
			{
				// �����̃I�t�Z�b�g��Ǎ�
				iss >> charOffset.x >> charOffset.y;
			}
			else if (str == "SAPCE_OFFSET")
			{
				// �󔒂̃I�t�Z�b�g��Ǎ�
				iss >> fSpaceOffset;
			}
			else if (str == "SETCHAR")
			{
				while (std::getline(file, str))
				{ // �t�@�C���̏I�[�ł͂Ȃ��ꍇ���[�v

					// �I�[�̏ꍇ���������𔲂���
					if (str == "END_SETCHAR") { break; }

					// ����s���̔z����g��
					m_vecSelect.emplace_back();

					// �J���}��؂育�ƂɃf�[�^��Ǎ�
					std::istringstream issChar(str);	// ������X�g���[��
					while (std::getline(issChar, str, ','))
					{
						if (str == "") { continue; }	// �󔒂͖�������
						else if (str == "/s")
						{ // �󔒂�ǂݍ��񂾏ꍇ

							// ���ʒu�ɋ󔒕��̃I�t�Z�b�g��^����
							posOffset.x += fSpaceOffset;
							continue;	// �z��C���f�b�N�X�͐i�߂Ȃ�
						}
						else if (str == "/e")
						{ // �󕶎���ǂݍ��񂾏ꍇ

							// ���݂̍s��̍Ō����nullptr��ǉ�
							m_vecSelect.back().push_back(nullptr);

							// ���ʒu�ɕ������̃I�t�Z�b�g��^����
							posOffset.x += charOffset.x;
						}
						else
						{ // ���ꑀ��ł͂Ȃ��ꍇ

							// �ǂݍ��񂾕����̐���
							CString2D *pChar = CString2D::Create
							( // ����
								select::FONT,					// �t�H���g�p�X
								select::ITALIC,					// �C�^���b�N
								useful::MultiByteToWide(&str),	// �w�蕶����
								posOffset,						// ���_�ʒu
								select::HEIGHT,					// �����c��
								select::ALIGN_X,				// ���z�u
								select::ROT,					// ���_����
								select::COL_DEFAULT				// �F
							);

							// �D�揇�ʂ�ݒ�
							pChar->SetPriority(PRIORITY);

							// ���݂̍s��̍Ō���ɐ�������������ǉ�
							m_vecSelect.back().push_back(pChar);

							// ���ʒu�ɕ������̃I�t�Z�b�g��^����
							posOffset.x += charOffset.x;
						}
					}

					// ���ʒu��擪�ɖ߂�
					posOffset.x = posStart.x;

					// �c�ʒu�ɕ������̃I�t�Z�b�g��^����
					posOffset.y += charOffset.y;
				}
			}
		}
	}

	// �t�@�C�������
	file.close();

	// ������Ԃ�
	return S_OK;
}
