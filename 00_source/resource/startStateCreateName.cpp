//============================================================
//
//	������ԏ��� [startStateCreateName.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startStateCreateName.h"
#include "startManager.h"
#include "manager.h"
#include "string2D.h"
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
	const int PRIORITY = 6;	// �D�揇��

	namespace title
	{	
		const char	*FONT	= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC	= false;	// �C�^���b�N
		const float	HEIGHT	= 42.0f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 80.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// ����
		const D3DXCOLOR		COL = XCOL_WHITE;	// �F
	}
	
	namespace select
	{	
		const D3DXVECTOR3 POS[CStartStateCreateName::YSELECT_MAX][CStartStateCreateName::XSELECT_MAX] =	// �ʒu�z��
		{
			{ D3DXVECTOR3(180.0f, 530.0f, 0.0f), D3DXVECTOR3(440.0f, 530.0f, 0.0f), D3DXVECTOR3(750.0f, 530.0f, 0.0f) },
			{ D3DXVECTOR3(220.0f, 630.0f, 0.0f), D3DXVECTOR3(460.0f, 630.0f, 0.0f), D3DXVECTOR3(700.0f, 630.0f, 0.0f) },
		};

		const CStartStateCreateName::ETypeChar INIT_TYPE = CStartStateCreateName::TYPECHAR_HIRAGANA;	// ���������Z�b�g
		const POSGRID2 INIT_SELECT = POSGRID2(0, 2);	// �����I���ʒu

		const char	*FONT	= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC	= false;	// �C�^���b�N
		const float	HEIGHT	= 42.0f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;	// ���z�u
		const D3DXVECTOR3	ROT			= VEC3_ZERO;	// ����
		const D3DXCOLOR		COL_DEFAULT	= XCOL_WHITE;	// �ʏ�F
		const D3DXCOLOR		COL_CHOICE	= XCOL_YELLOW;	// �I��F
	}
}

//************************************************************
//	�q�N���X [CStartStateCreateName] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateCreateName::CStartStateCreateName() :
	m_pTitle	(nullptr),		// �^�C�g��
	m_curSelect	(GRID2_ZERO),	// ���݂̑I����
	m_oldSelect	(GRID2_ZERO)	// �O��̑I����
{
	// �I�𕶎��z����N���A
	m_vecSelect.clear();
}

//============================================================
//	�f�X�g���N�^
//============================================================
CStartStateCreateName::~CStartStateCreateName()
{

}

//============================================================
//	����������
//============================================================
HRESULT CStartStateCreateName::Init(void)
{
	// �����o�ϐ���������
	m_pTitle	= nullptr;				// �^�C�g��
	m_curSelect	= select::INIT_SELECT;	// ���݂̑I����
	m_oldSelect	= select::INIT_SELECT;	// �O��̑I����

	// �I�𕶎��z���������
	m_vecSelect.clear();

	// �^�C�g���̐���
	m_pTitle = CString2D::Create
	( // ����
		title::FONT,	// �t�H���g�p�X
		title::ITALIC,	// �C�^���b�N
		L"",			// �w�蕶����
		title::POS,		// ���_�ʒu
		title::HEIGHT,	// �����c��
		title::ALIGN_X,	// ���z�u
		title::ROT,		// ���_����
		title::COL		// �F
	);
	if (m_pTitle == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pTitle->SetPriority(PRIORITY);

	// �����������
	loadtext::BindString(m_pTitle, loadtext::LoadText(PASS, CStartManager::TEXT_NAMING));

	for (int i = 0; i < YSELECT_MAX; i++)
	{
		// ����s���̔z����g��
		m_vecSelect.emplace_back();

		for (int j = 0; j < XSELECT_MAX; j++)
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
			loadtext::BindString(pSelect, loadtext::LoadText(PASS, CStartManager::TEXT_HIRAGANA + (i * XSELECT_MAX) + j));

			// ���݂̍s��̍Ō���ɐ�������������ǉ�
			m_vecSelect.back().push_back(pSelect);
		}
	}

	// �z�u�̓Ǎ�
	if (FAILED(ChangeChar(select::INIT_TYPE)))
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
void CStartStateCreateName::Uninit(void)
{
	// �^�C�g���̏I��
	SAFE_UNINIT(m_pTitle);

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

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CStartStateCreateName::Update(const float fDeltaTime)
{
	// �I���̍X�V
	UpdateSelect();

	// ����̍X�V
	UpdateDecide();
}

//============================================================
//	�I���̑��쏈��
//============================================================
void CStartStateCreateName::ControlSelect(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_LEFT))
	{
		do { // �I��悪�Ȃ��ꍇ����ɓ�����

			// ���ɑI�������炷
			int nMaxWidth = (int)m_vecSelect[m_curSelect.y].size();	// ��̍ő吔
			m_curSelect.x = (m_curSelect.x + (nMaxWidth - 1)) % nMaxWidth;

		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		do { // �I��悪�Ȃ��ꍇ����ɓ�����

			// �E�ɑI�������炷
			int nMaxWidth = (int)m_vecSelect[m_curSelect.y].size();	// ��̍ő吔
			m_curSelect.x = (m_curSelect.x + 1) % nMaxWidth;

		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		do { // �I��悪�Ȃ��ꍇ����ɓ�����

			// ��ɑI�������炷
			int nMaxHeight = (int)m_vecSelect.size();	// �s�̍ő吔
			m_curSelect.y = (m_curSelect.y + (nMaxHeight - 1)) % nMaxHeight;

			// �񂪑��������ꍇ�ɗ�C���f�b�N�X��␳
			int nPrevSelectY = (m_curSelect.y + 1) % nMaxHeight;
			if (m_vecSelect[m_curSelect.y].size() < m_vecSelect[nPrevSelectY].size())
			{ // �񂪌��������ꍇ

				// ��C���f�b�N�X�����������̍ő�l�ŕ␳
				m_curSelect.x /= m_vecSelect[m_oldSelect.y].size() / XSELECT_MAX;
			}
			else if (m_vecSelect[m_curSelect.y].size() > m_vecSelect[nPrevSelectY].size())
			{ // �񂪑��������ꍇ

				// ��C���f�b�N�X��傫�����̍ő�l�ŕ␳
				m_curSelect.x *= m_vecSelect[m_curSelect.y].size() / XSELECT_MAX;
			}

		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}
	if (pKey->IsTrigger(DIK_DOWN))
	{
		do { // �I��悪�Ȃ��ꍇ����ɓ�����

			// ���ɑI�������炷
			int nMaxHeight = (int)m_vecSelect.size();	// �s�̍ő吔
			m_curSelect.y = (m_curSelect.y + 1) % nMaxHeight;

			// �񂪑��������ꍇ�ɗ�C���f�b�N�X��␳
			int nPrevSelectY = (m_curSelect.y + (nMaxHeight - 1)) % nMaxHeight;	// ���̍s�I���C���f�b�N�X
			if (m_vecSelect[m_curSelect.y].size() < m_vecSelect[nPrevSelectY].size())
			{ // �񂪌��������ꍇ

				// ��C���f�b�N�X�����������̍ő�l�ŕ␳
				m_curSelect.x /= m_vecSelect[m_oldSelect.y].size() / XSELECT_MAX;
			}
			else if (m_vecSelect[m_curSelect.y].size() > m_vecSelect[nPrevSelectY].size())
			{ // �񂪑��������ꍇ

				// ��C���f�b�N�X��傫�����̍ő�l�ŕ␳
				m_curSelect.x *= m_vecSelect[m_curSelect.y].size() / XSELECT_MAX;
			}

		} while (m_vecSelect[m_curSelect.y][m_curSelect.x] == nullptr);
	}
}

//============================================================
//	�I���̍X�V����
//============================================================
void CStartStateCreateName::UpdateSelect(void)
{
	// �O��̑I������ۑ�
	m_oldSelect = m_curSelect;

	// �I���̑���
	ControlSelect();

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
void CStartStateCreateName::UpdateDecide(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_Z) || pKey->IsTrigger(DIK_RETURN))
	{
		// �I�����ɉ����đ����ύX
		switch (m_curSelect.y)
		{ // ���݂̍s�I�������Ƃ̏���
		case YSELECT_CHAR_CHANGE:	// �����ύX

			// �I�𒆂̕����ɕύX
			ChangeChar((ETypeChar)m_curSelect.x);
			break;

		case YSELECT_CHAR_DECIDE:	// ��������

			switch (m_curSelect.x)
			{ // ���݂̗�I�������Ƃ̏���
			case XSELECT_LEFT:		// �~�߂�

				// �`���[�g���A����Ԃɂ���
				m_pContext->ChangeState(new CStartStateTutorial);
				break;

			case XSELECT_CENTER:	// �폜

				// �Ō�����ꕶ���폜
				//m_pNaming->DeleteBackName();	// TODO
				break;

			case XSELECT_RIGHT:		// �m��

				// ���O�����Ԃɂ���
				//m_pContext->ChangeState(new CStartStateDecideName(m_pNaming->GetName()));	// TODO
				break;

			default:
				assert(false);
				break;
			}
			break;

		default:
			assert(false);
			break;
		}
	}
}

//============================================================
//	�����̕ύX����
//============================================================
HRESULT CStartStateCreateName::ChangeChar(const ETypeChar typeChar)
{
	// ������ނ��s���Ȓl�̏ꍇ������
	if (typeChar <= NONE_IDX || typeChar >= TYPECHAR_MAX) { assert(false); return E_FAIL; }

	// TODO
	for (int i = YSELECT_MAX; i < (int)m_vecSelect.size(); i++)
	{ // �c�̕��������J��Ԃ�

		for (int j = 0; j < (int)m_vecSelect[i].size(); j++)
		{ // ���̕��������J��Ԃ�

			// �I�𕶎��̏I��
			SAFE_UNINIT(m_vecSelect[i][j]);
		}
	}

	// �I�𕶎��z����N���A
	m_vecSelect.erase(m_vecSelect.begin() + YSELECT_MAX, m_vecSelect.end());

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
//	�z�u�̓Ǎ�����
//============================================================
HRESULT CStartStateCreateName::LoadArray(const ETypeChar typeChar)
{
	D3DXVECTOR3 posOffset	= VEC3_ZERO;	// ���������ʒu
	D3DXVECTOR3 posStart	= VEC3_ZERO;	// �����J�n�ʒu
	D3DXVECTOR2 charOffset	= VEC2_ZERO;	// �����̃I�t�Z�b�g
	float fSpaceOffset		= 0.0f;			// �󔒂̃I�t�Z�b�g

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
