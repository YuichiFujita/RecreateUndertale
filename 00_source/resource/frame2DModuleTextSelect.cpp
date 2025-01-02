//============================================================
//
//	�I��t���e�L�X�g�\���@�\���� [frame2DModuleTextSelect.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DModuleTextSelect.h"
#include "manager.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	namespace text
	{
		const VECTOR3 OFFSET[] =	// �e�L�X�g�I�t�Z�b�g�v���Z�b�g
		{
			VECTOR3(-410.0f, -80.0f, 0.0f)	// �����z�u
		};
		const char*	FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const int	PRIORITY	= 6;				// �e�L�X�g�̗D�揇��
		const bool	ITALIC		= false;			// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;			// �����c��
		const float	LINE_HEIGHT	= 54.0f;			// �s�ԏc��
		const float	WAIT_TIME	= 0.045f;			// �����\���̑ҋ@����
		const EAlignX ALIGN_X	= XALIGN_CENTER;	// ���z�u
		const EAlignY ALIGN_Y	= YALIGN_TOP;		// �c�z�u
	}

	namespace soul
	{
		const char* PATH	= "data\\TEXTURE\\spr_heartsmall.png";	// �\�E���J�[�\���e�N�X�`���p�X
		const VECTOR3 SIZE	= VECTOR3(26.5f, 26.5f, 0.0f);			// �\�E���J�[�\���傫��
	}
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(text::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	�q�N���X [CFrame2DModuleTextSelect] �̃����o�֐�
//************************************************************
//============================================================
//	�ڏ��R���X�g���N�^ (�z�u�v���Z�b�g)
//============================================================
CFrame2DModuleTextSelect::CFrame2DModuleTextSelect(const CFrame2D::EPreset preset) : CFrame2DModuleTextSelect(text::OFFSET[preset])
{
	// �v���Z�b�g�͈͊O�G���[
	assert(preset > NONE_IDX && preset < CFrame2D::PRESET_MAX);
}

//============================================================
//	�R���X�g���N�^ (�z�u�w��)
//============================================================
CFrame2DModuleTextSelect::CFrame2DModuleTextSelect(const VECTOR3& rOffset) : CFrame2DModuleText(rOffset),
	m_pSoul		 (nullptr),	// �\�E���J�[�\�����
	m_nCurSelect (0)		// ���݂̑I����
{
	// �����o�ϐ����N���A
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I�������
}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DModuleTextSelect::~CFrame2DModuleTextSelect()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFrame2DModuleTextSelect::Init()
{
	// �����o�ϐ���������
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I�������
	m_pSoul		 = nullptr;	// �\�E���J�[�\�����
	m_nCurSelect = 0;		// ���݂̑I����

	// �e�N���X�̏�����
	if (FAILED(CFrame2DModuleText::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	const int nPrioContext = m_pContext->GetPriority();	// �R���e�L�X�g�̗D�揇��
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I�����̐���
		m_apSelect[i] = CScrollText2D::Create
		( // ����
			text::FONT,			// �t�H���g�p�X
			text::ITALIC,		// �C�^���b�N
// TODO
#if 0
			VEC3_ZERO,			// ���_�ʒu
#else
			VECTOR3(SCREEN_CENT.x - 150.0f + 300.0f * (float)i, 600.0f, 0.0f),	// ���_�ʒu
#endif
			text::WAIT_TIME,	// �����\���̑ҋ@����
			text::CHAR_HEIGHT,	// �����c��
			text::LINE_HEIGHT,	// �s�ԏc��
			text::ALIGN_X,		// ���z�u
			text::ALIGN_Y		// �c�z�u
		);
		if (m_apSelect[i] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(nPrioContext);

		// �������莞�̍Đ�SE��ݒ�
		m_apSelect[i]->SetScrollSE(CSound::LABEL_SE_TEXT01);
	}

	// �\�E���J�[�\���̐���
	m_pSoul = CObject2D::Create
	( // ����
		VEC3_ZERO,	// �ʒu
		soul::SIZE	// �傫��
	);
	if (m_pSoul == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �\�E���e�N�X�`��������
	m_pSoul->BindTexture(soul::PATH);

	// ���x����ݒ�
	m_pSoul->SetLabel(CObject::LABEL_UI);

	// �D�揇�ʂ�ݒ�
	m_pSoul->SetPriority(nPrioContext);

	// �J�[�\���̎����`���OFF�ɂ���
	m_pSoul->SetEnableDraw(false);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFrame2DModuleTextSelect::Uninit()
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̏I��
		SAFE_UNINIT(m_apSelect[i]);
	}

	// �\�E���J�[�\���̏I��
	SAFE_UNINIT(m_pSoul);

	// �e�N���X�̏I��
	CFrame2DModuleText::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CFrame2DModuleTextSelect::Update(const float fDeltaTime)
{
	if (!m_pSoul->IsDraw())
	{ // �J�[�\�����\������Ă��Ȃ��ꍇ

		if (input::Decide())
		{
			// ������S�\��������
			SetTextEnableDraw(true);
			m_apSelect[SELECT_LEFT]->SetEnableDraw(true);
			m_apSelect[SELECT_RIGHT]->SetEnableDraw(true);

			// �J�[�\���̎����`���ON�ɂ���
			m_pSoul->SetEnableDraw(true);
			return;
		}

		if (IsTextEndScroll())
		{ // �{���̕������肪�I�������ꍇ

			// ���I�����̕���������J�n
			m_apSelect[SELECT_LEFT]->SetEnableScroll(true);
		}
		else { return; }

		if (m_apSelect[SELECT_LEFT]->IsEndScroll())
		{ // ���I�����̕������肪�I�������ꍇ

			// �E�I�����̕���������J�n
			m_apSelect[SELECT_RIGHT]->SetEnableScroll(true);
		}
		else { return; }

		if (m_apSelect[SELECT_RIGHT]->IsEndScroll())
		{ // �E�I�����̕������肪�I�������ꍇ

			// �J�[�\���̎����`���ON�ɂ���
			m_pSoul->SetEnableDraw(true);
		}
	}
	else
	{ // �J�[�\�����\������Ă���ꍇ

		// �I���̍X�V
		UpdateSelect();

		// ����̍X�V
		UpdateDecide();
	}
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CFrame2DModuleTextSelect::SetPriority(const int nPriority)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̗D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(nPriority);
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFrame2DModuleTextSelect::SetVec3Position(const VECTOR3& /*rPos*/)
{
	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFrame2DModuleTextSelect::SetVec3Rotation(const VECTOR3& rRot)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̌�����ݒ�
		m_apSelect[i]->SetVec3Rotation(rRot);
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

#if 0
//============================================================
//	�e�L�X�g�ύX����
//============================================================
void CFrame2DModuleTextSelect::ChangeText(const ESelect select, const AText& rText)
{
#if 0
	// �������S�č폜
	m_pText->DeleteStringAll();

	// �e�L�X�g������
	int nLoop = (int)rText.size();	// ������
	for (int i = 0; i < nLoop; i++)
	{ // ������̐����J��Ԃ�

		// ��������Ō���ɒǉ�
		m_pText->PushBackString(rText[i]);
	}

	// ����������J�n����
	m_pText->SetEnableScroll(true);
#else

#endif
}
#endif

//============================================================
//	�ۑ��@�\�̊�������
//============================================================
void CFrame2DModuleTextSelect::BindTextSave(CFrame2DModule* pModule, CTextSave* pText)
{
	// �I��t���e�L�X�g�\���@�\�ɕϊ��ł��Ȃ��ꍇ������
	CFrame2DModuleTextSelect* pModuleSelect = pModule->GetModuleTextSelect();
	if (pModuleSelect == nullptr) { assert(false); return; }

	// �I��t���e�L�X�g�ۑ��|�C���^�ɕϊ��ł��Ȃ��ꍇ������
	CTextSaveSelect* pSaveSelect = pText->GetSelect();
	if (pSaveSelect == nullptr) { assert(false); return; }

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// ���e�L�X�g�̌����L�[������
		pModuleSelect->m_aNextTextKey[i] = pSaveSelect->m_aNextTextKey[i];

		// �I�����̃e�L�X�g��������
		for (int j = 0; j < (int)pSaveSelect->m_aSelect[i].size(); j++)
		{ // �����񐔕��J��Ԃ�

			// ��������Ō���ɒǉ�
			pModuleSelect->m_apSelect[i]->PushBackString(pSaveSelect->m_aSelect[i][j]);
		}
	}

	// �e�L�X�g��������
	for (int i = 0; i < (int)pSaveSelect->m_text.size(); i++)
	{ // �����񐔕��J��Ԃ�

		// ��������Ō���ɒǉ�
		pModuleSelect->PushBackString(pSaveSelect->m_text[i]);
	}
}

//============================================================
//	�I���̍X�V����
//============================================================
void CFrame2DModuleTextSelect::UpdateSelect()
{
	// �I��������
	CInputKeyboard* pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// ���ɑI�������炷
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// �E�ɑI�������炷
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}

	// TODO
	VECTOR3 posSelect = m_apSelect[m_nCurSelect]->GetVec3Position();
	posSelect.x -= m_apSelect[m_nCurSelect]->GetTextWidth() * 0.5f + 30.0f;
	posSelect.y += m_apSelect[m_nCurSelect]->GetCharHeight() * 0.5f;

	// �\�E���J�[�\���̈ʒu���ړ�
	m_pSoul->SetVec3Position(posSelect);
}

//============================================================
//	����̍X�V����
//============================================================
void CFrame2DModuleTextSelect::UpdateDecide()
{
	if (input::Decide())
	{
		const std::string& rSelectTextKey = m_aNextTextKey[m_nCurSelect];	// �I�𒆂̎��e�L�X�g�����L�[
		std::string sNextPath = GetNextPath();		// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
		std::string sNextBoxKey = GetNextBoxKey();	// ���e�L�X�g�{�b�N�X�̌����L�[
		if (rSelectTextKey == "-1"
		||  rSelectTextKey == "NONE")
		{ // �e�L�X�g�J�ڐ悪�Ȃ��ꍇ

			if (IsNextTextBox(&sNextPath, &sNextBoxKey))
			{ // �e�L�X�g�{�b�N�X�J�ڐ悪����ꍇ

				SetNextPath(sNextPath);
				SetNextBoxKey(sNextBoxKey);

				// ���̃e�L�X�g������
				BindText(sNextPath, sNextBoxKey, "0");
			}
			else
			{ // �e�L�X�g�{�b�N�X�J�ڐ悪�Ȃ��ꍇ

				// �R���e�L�X�g�̏I��
				SAFE_UNINIT(m_pContext);
			}
		}
		else
		{ // �e�L�X�g�J�ڐ悪����ꍇ

			// ���̃e�L�X�g������
			BindText(sNextPath, sNextBoxKey, rSelectTextKey);
		}
	}
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CFrame2DModuleTextSelect::SetPositionRelative()
{
#if 0
	VECTOR3 posFrame = m_pContext->GetVec3Position();	// �t���[���ʒu
	VECTOR3 rotFrame = m_pContext->GetVec3Rotation();	// �t���[������

	// X���W�I�t�Z�b�g�����炷
	posFrame.x += sinf(rotFrame.z + HALF_PI) * m_offset.x;
	posFrame.y += cosf(rotFrame.z + HALF_PI) * m_offset.x;

	// Y���W�I�t�Z�b�g�����炷
	posFrame.x += sinf(rotFrame.z) * m_offset.y;
	posFrame.y += cosf(rotFrame.z) * m_offset.y;

	// �e�L�X�g�ʒu�̔��f
	m_pText->SetVec3Position(posFrame);
#else
	// TODO�F1F�����ʒu���ꂵ�Ă�
	VECTOR3 posSelect = m_apSelect[m_nCurSelect]->GetVec3Position();
	posSelect.x -= m_apSelect[m_nCurSelect]->GetTextWidth() * 0.5f + 30.0f;
	posSelect.y += m_apSelect[m_nCurSelect]->GetCharHeight() * 0.5f;

	// �\�E���J�[�\���̈ʒu���ړ�
	m_pSoul->SetVec3Position(posSelect);
#endif
}

//************************************************************
//	�q�N���X [CTextSaveText] �̃����o�֐�
//************************************************************
//============================================================
//	�e�L�X�g�@�\�̐�������
//============================================================
CFrame2DModule* CTextSaveSelect::CreateModule(const CFrame2D::EPreset preset)
{
	// �I��t���e�L�X�g�\���@�\�𐶐����Ԃ�
	return new CFrame2DModuleTextSelect(preset);
}

//============================================================
//	���݃L�[�̕�����Ǎ�����
//============================================================
void CTextSaveSelect::LoadKeyString(std::ifstream* pFile, std::string& rString)
{
	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return; }

	if (rString == "SELECT_LEFT")
	{
		// �I����������̓Ǎ�
		LoadSelect(pFile, CFrame2DModuleTextSelect::SELECT_LEFT);
	}
	else if (rString == "SELECT_RIGHT")
	{
		// �I����������̓Ǎ�
		LoadSelect(pFile, CFrame2DModuleTextSelect::SELECT_RIGHT);
	}
}

//============================================================
//	�I����������̓Ǎ�����
//============================================================
void CTextSaveSelect::LoadSelect(std::ifstream* pFile, const CFrame2DModuleTextSelect::ESelect select)
{
	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return; }

	// �I��t���e�L�X�g�ۑ��|�C���^�ɕϊ��ł��Ȃ��ꍇ������
	CTextSaveSelect* pSelect = GetSelect();
	if (pSelect == nullptr) { assert(false); return; }

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	do { // END_SELECT��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// �R�����g�A�E�g
		else if (str == "NEXT")
		{
			*pFile >> str;						// ����Ǎ�
			*pFile >> m_aNextTextKey[select];	// ���e�L�X�g�̌����L�[��Ǎ�
		}
		else if (str == "STR")
		{
			*pFile >> str;					// ����Ǎ�
			pFile->seekg(1, std::ios::cur);	// �Ǎ��ʒu���󔒕����炷
			std::getline(*pFile, str);		// ��s�S�ēǂݍ���

			// ������̐擪�ɋ󔒂�ǉ�
			str.insert(0, " ");

			// ��������Ō���ɒǉ�
			pSelect->m_aSelect[select].push_back(str);
		}
	} while (str != "END_SELECT");	// END_SELECT��ǂݍ��ނ܂Ń��[�v
}
