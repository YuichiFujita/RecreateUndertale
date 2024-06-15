//============================================================
//
//	�Ђ炪�ȏ�ԏ��� [charStateHiragana.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "charStateHiragana.h"
#include "manager.h"
#include "string2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// �D�揇��

	namespace select
	{	
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
//	�q�N���X [CCharStateHiragana] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CCharStateHiragana::CCharStateHiragana() :
	m_selectMax	(GRID2_ZERO),	// �I�𕶎��̍ő��
	m_curSelect	(GRID2_ZERO),	// ���݂̑I�𕶎�
	m_oldSelect	(GRID2_ZERO)	// �O��̑I�𕶎�
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CCharStateHiragana::~CCharStateHiragana()
{

}

//============================================================
//	����������
//============================================================
HRESULT CCharStateHiragana::Init(void)
{
	// �����o�ϐ���������
	m_selectMax = GRID2_ZERO;	// �I�𕶎��̍ő��
	m_curSelect = GRID2_ZERO;	// ���݂̑I�𕶎�
	m_oldSelect = GRID2_ZERO;	// �O��̑I�𕶎�

#if 0
	m_vecSelect = new CString2D**[Y];
	for (int i = 0; i < Y; i++)
	{
		m_vecSelect[i] = new CString2D*[X];
	}
#endif

	// �z�u�̓Ǎ�
	if (FAILED(LoadArray()))
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
void CCharStateHiragana::Uninit(void)
{
	for (int i = 0; i < GetSelectHeight(); i++)
	{
		for (int j = 0; j < GetSelectWidth(); j++)
		{
			// �I�𕶎��̏I��
			SAFE_UNINIT(m_vecSelect[i][j]);
		}
	}

#if 0
	for (int i = 0; i < Y; i++)
	{
		SAFE_DEL_ARRAY(m_vecSelect[i]);
	}
	SAFE_DEL_ARRAY(m_vecSelect);
#endif

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CCharStateHiragana::Update(const float fDeltaTime)
{
	// �I���̍X�V
	UpdateSelect();

	// ����̍X�V
	UpdateDecide();
}

//============================================================
//	�I���̍X�V����
//============================================================
void CCharStateHiragana::UpdateSelect(void)
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

	// TODO�F�����ǂ��ɂ����Ȃ��H
	//if (m_oldSelect.y != YSELECT_TOP)
	{
		// �O��̑I��v�f�̐F�𔒐F�ɐݒ�
		assert(m_vecSelect[m_oldSelect.y][m_oldSelect.x] != nullptr);
		m_vecSelect[m_oldSelect.y][m_oldSelect.x]->SetColor(select::COL_DEFAULT);
	}
	//if (m_curSelect.y != YSELECT_TOP)
	{
		// ���݂̑I��v�f�̐F�����F�ɐݒ�
		assert(m_vecSelect[m_curSelect.y][m_curSelect.x] != nullptr);
		m_vecSelect[m_curSelect.y][m_curSelect.x]->SetColor(select::COL_CHOICE);
	}
}

//============================================================
//	����̍X�V����
//============================================================
void CCharStateHiragana::UpdateDecide(void)
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
//	�z�u�̓Ǎ�����
//============================================================
HRESULT CCharStateHiragana::LoadArray(void)
{
	D3DXVECTOR3 posOffset = VEC3_ZERO;	// ���������ʒu
	D3DXVECTOR3 posStart = VEC3_ZERO;	// �����J�n�ʒu
	float fCharOffset = 0.0f;	// �����̃I�t�Z�b�g
	float fSpaceOffset = 0.0f;	// �󔒂̃I�t�Z�b�g

	// �t�@�C�����J��
	std::ifstream file("data\\CSV\\char_hiragana.csv");	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�Ђ炪�ȃZ�b�g�A�b�v�̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);

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
				iss >> fCharOffset;
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
							posOffset.x += fCharOffset;
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
							posOffset.x += fCharOffset;
						}
					}

					// ���ʒu��擪�ɖ߂�
					posOffset.x = posStart.x;

					// �c�ʒu�ɕ������̃I�t�Z�b�g��^����
					posOffset.y += fCharOffset;
				}
			}
		}
	}

	// �t�@�C�������
	file.close();

	// ������Ԃ�
	return S_OK;
}
