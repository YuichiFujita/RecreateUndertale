//============================================================
//
//	�e�L�X�g�\���@�\���� [frame2DModuleText.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DModuleText.h"
#include "frame2D.h"

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
		const int	PRIORITY	= 6;			// �e�L�X�g�̗D�揇��
		const bool	ITALIC		= false;		// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;		// �����c��
		const float	LINE_HEIGHT	= 54.0f;		// �s�ԏc��
		const float	WAIT_TIME	= 0.045f;		// �����\���̑ҋ@����
		const EAlignX ALIGN_X	= XALIGN_LEFT;	// ���z�u
		const EAlignY ALIGN_Y	= YALIGN_TOP;	// �c�z�u
	}
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(text::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	�q�N���X [CFrame2DModuleText] �̃����o�֐�
//************************************************************
//============================================================
//	�ڏ��R���X�g���N�^ (�z�u�v���Z�b�g)
//============================================================
CFrame2DModuleText::CFrame2DModuleText(const CFrame2D::EPreset preset) : CFrame2DModuleText(text::OFFSET[preset])
{
	// �v���Z�b�g�͈͊O�G���[
	assert(preset > NONE_IDX && preset < CFrame2D::PRESET_MAX);
}

//============================================================
//	�R���X�g���N�^ (�z�u�w��)
//============================================================
CFrame2DModuleText::CFrame2DModuleText(const VECTOR3& rOffset) :
	m_pText	 (nullptr),	// �e�L�X�g���
	m_offset (rOffset)	// �e�L�X�g�I�t�Z�b�g
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DModuleText::~CFrame2DModuleText()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFrame2DModuleText::Init()
{
	// �����o�ϐ���������
	m_pText = nullptr;	// �e�L�X�g���

	// �e�L�X�g�̐���
	m_pText = CScrollText2D::Create
	( // ����
		text::FONT,			// �t�H���g�p�X
		text::ITALIC,		// �C�^���b�N
		VEC3_ZERO,			// ���_�ʒu
		text::WAIT_TIME,	// �����\���̑ҋ@����
		text::CHAR_HEIGHT,	// �����c��
		text::LINE_HEIGHT,	// �s�ԏc��
		text::ALIGN_X,		// ���z�u
		text::ALIGN_Y		// �c�z�u
	);
	if (m_pText == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pText->SetPriority(m_pContext->GetPriority());

	// �������莞�̍Đ�SE��ݒ�
	m_pText->SetScrollSE(CSound::LABEL_SE_TEXT01);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFrame2DModuleText::Uninit()
{
	// �e�L�X�g�̏I��
	SAFE_UNINIT(m_pText);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CFrame2DModuleText::Update(const float fDeltaTime)
{
	if (input::Decide())
	{
		if (!m_pText->IsEndScroll())
		{ // �������蒆�̏ꍇ

			// ������S�\��������
			m_pText->SetEnableDraw(true);
			return;
		}

		if (m_sNextTextKey == "-1"
		||  m_sNextTextKey == "NONE")
		{ // �e�L�X�g�J�ڐ悪�Ȃ��ꍇ

			if (IsNextTextBox(&m_sNextPath, &m_sNextBoxKey))
			{ // �e�L�X�g�{�b�N�X�J�ڐ悪����ꍇ

				// ���̃e�L�X�g������
				BindText(m_sNextPath, m_sNextBoxKey, "0");
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
			BindText(m_sNextPath, m_sNextBoxKey, m_sNextTextKey);
		}
	}
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CFrame2DModuleText::SetPriority(const int nPriority)
{
	// �e�L�X�g�̗D�揇�ʂ�ݒ�
	m_pText->SetPriority(nPriority);
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFrame2DModuleText::SetVec3Position(const VECTOR3& /*rPos*/)
{
	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFrame2DModuleText::SetVec3Rotation(const VECTOR3& rRot)
{
	// �e�L�X�g�̌�����ݒ�
	m_pText->SetVec3Rotation(rRot);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�e�L�X�g�ύX����
//============================================================
void CFrame2DModuleText::ChangeText(const AText& rText)
{
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
}

//============================================================
//	�e�L�X�g�I�t�Z�b�g�̐ݒ菈��
//============================================================
void CFrame2DModuleText::SetOffset(const VECTOR3& rOffset)
{
	// �e�L�X�g�I�t�Z�b�g�̐ݒ�
	m_offset = rOffset;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�e�L�X�g��������
//============================================================
HRESULT CFrame2DModuleText::BindText(const std::string& rPath, const std::string& rBoxKey, const std::string& rTextKey)
{
#if 0
	// �R���e�L�X�g�̕ۑ�
	CFrame2D* pFrame2D = m_pContext;

	// �������̕ۑ�
	std::string sNextPath		= rPath;	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	std::string sNextBoxKey		= rBoxKey;	// ���e�L�X�g�{�b�N�X�̌����L�[
	std::string sNextTextKey	= rTextKey;	// ���e�L�X�g�̌����L�[

	// �e�L�X�g�\���@�\��ݒ�
	if (FAILED(pFrame2D->ChangeModule(new CFrame2DModuleText(CFrame2D::PRESET_DOWN))))	// TODO�FSelect�Ή�
	{ // �ݒ�Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �e�L�X�g�\���@�\���擾
	CFrame2DModuleText* pModule = pFrame2D->GetModule()->GetModuleText();
	if (pModule == nullptr)
	{ // �擾�Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �������̕ۑ�
	pModule->m_sNextPath	= sNextPath;	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	pModule->m_sNextBoxKey	= sNextBoxKey;	// ���e�L�X�g�{�b�N�X�̌����L�[
	pModule->m_sNextTextKey	= sNextTextKey;	// ���e�L�X�g�̌����L�[

	// �e�L�X�g�{�b�N�X����Ǎ�
	AText text = pModule->LoadTextBox(sNextPath, sNextBoxKey, sNextTextKey);

	// �e�L�X�g��������
	for (int i = 0; i < (int)text.size(); i++)
	{ // �����񐔕��J��Ԃ�

		// ��������Ō���ɒǉ�
		pModule->PushBackString(text[i]);
	}

	// ����������J�n����
	pModule->SetTextEnableScroll(true);
#else
	// �R���e�L�X�g�̕ۑ�
	CFrame2D* pFrame2D = m_pContext;

	// �������̕ۑ�
	const std::string sNextPath		= rPath;	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	const std::string sNextBoxKey	= rBoxKey;	// ���e�L�X�g�{�b�N�X�̌����L�[
	const std::string sNextTextKey	= rTextKey;	// ���e�L�X�g�̌����L�[

	// �e�L�X�g�\���@�\��ݒ�
	if (FAILED(pFrame2D->ChangeModule(new CFrame2DModuleText(CFrame2D::PRESET_DOWN))))	// TODO�FSelect�Ή�	// TODO�FCFrame2D��PresetGetter�쐬�A���BindText�̃v���Z�b�g���w��
	{ // �ݒ�Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �e�L�X�g�\���@�\���擾
	CFrame2DModuleText* pModule = pFrame2D->GetModule()->GetModuleText();
	if (pModule == nullptr)
	{ // �擾�Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �������̕ۑ�
	pModule->m_sNextPath	= sNextPath;	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	pModule->m_sNextBoxKey	= sNextBoxKey;	// ���e�L�X�g�{�b�N�X�̌����L�[
	pModule->m_sNextTextKey	= sNextTextKey;	// ���e�L�X�g�̌����L�[

	// �e�L�X�g�{�b�N�X����Ǎ�
	AText text = pModule->LoadTextBox(sNextPath, sNextBoxKey, sNextTextKey);	// AText�{�K�v��Module�񋓎w��/���ۑ��������̂�Ԃ��� (static�Ȃ�\)

	// TODO�F�eModule���Ƃ̊����֐��쐬
#if 1
	// �e�L�X�g��������
	for (int i = 0; i < (int)text.size(); i++)
	{ // �����񐔕��J��Ԃ�

		// ��������Ō���ɒǉ�
		pModule->PushBackString(text[i]);
	}
#endif

	// ����������J�n����
	pModule->SetTextEnableScroll(true);
#endif

	return S_OK;
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CFrame2DModuleText::SetPositionRelative()
{
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
}

//============================================================
//	�e�L�X�g�{�b�N�X�̓Ǎ�����
//============================================================
AText CFrame2DModuleText::LoadTextBox(const std::string& rPath, const std::string& rBoxKey, const std::string& rTextKey)
{
	// �Ǎ��̊J�n��������쐬
	std::string sLoadStart = "TEXTBOX_";	// �F���p�̐擪������ݒ�
	sLoadStart.append(rBoxKey);				// �����̔F���p������ƘA��

	// �t�@�C�����J��
	std::ifstream file(rPath);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�e�L�X�g�t�@�C���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return {};
	}

	// �t�@�C����Ǎ�
	AText text;			// �e�L�X�g���
	std::string str;	// �Ǎ�������
	while (file >> str)
	{ // �t�@�C���̏I�[�ł͂Ȃ��ꍇ���[�v

		if (str.front() == '#') { std::getline(file, str); }	// �R�����g�A�E�g
		else if (str == sLoadStart)
		{ // �Ǎ��J�n�̕�����ƈ�v�����ꍇ

			// �e�L�X�g�̓Ǎ�
			LoadText(&file, &text, rTextKey);
		}
	}

	// �t�@�C�������
	file.close();

	// �e�L�X�g����Ԃ�
	return text;
}

//============================================================
//	�e�L�X�g�̓Ǎ�����
//============================================================
void CFrame2DModuleText::LoadText(std::ifstream* pFile, AText* pText, const std::string& rTextKey)
{
	// �e�L�X�g�ۑ��|�C���^���Ȃ��ꍇ������
	if (pText == nullptr) { assert(false); return; }

	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return; }

	// �Ǎ��̊J�n��������쐬
	std::string sLoadStart = "TEXT_";	// �F���p�̐擪������ݒ�
	sLoadStart.append(rTextKey);		// �����̔F���p������ƘA��

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	do { // END_TEXTBOX��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// �R�����g�A�E�g
		else if (str == sLoadStart)
		{ // �Ǎ��J�n�̕�����ƈ�v�����ꍇ

			// ������̓Ǎ�
			LoadString(pFile, pText);
		}
	} while (str != "END_TEXTBOX");	// END_TEXTBOX��ǂݍ��ނ܂Ń��[�v
}

//============================================================
//	������̓Ǎ�����
//============================================================
void CFrame2DModuleText::LoadString(std::ifstream* pFile, AText* pText)
{
	// �e�L�X�g�ۑ��|�C���^���Ȃ��ꍇ������
	if (pText == nullptr) { assert(false); return; }

	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return; }

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	do { // END_TEXT��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// �R�����g�A�E�g
		else if (str == "NEXT")
		{
			*pFile >> str;				// ����Ǎ�
			*pFile >> m_sNextTextKey;	// ���e�L�X�g�̌����L�[��Ǎ�
		}
		else if (str == "STR")
		{
			*pFile >> str;					// ����Ǎ�
			pFile->seekg(1, std::ios::cur);	// �Ǎ��ʒu���󔒕����炷
			std::getline(*pFile, str);		// ��s�S�ēǂݍ���

			// ������̐擪�ɋ󔒂�ǉ�
			str.insert(0, " ");

			// ��������Ō���ɒǉ�
			pText->push_back(str);
		}

	} while (str != "END_TEXT");	// END_TEXT��ǂݍ��ނ܂Ń��[�v
}

//============================================================
//	���e�L�X�g�{�b�N�X�����邩�̊m�F����
//============================================================
bool CFrame2DModuleText::IsNextTextBox(std::string* pPath, std::string* pBoxKey)
{
	// �Ǎ��̊J�n��������쐬
	std::string sLoadStart = "TEXTBOX_";	// �F���p�̐擪������ݒ�
	sLoadStart.append(*pBoxKey);			// �����̔F���p������ƘA��

	// �t�@�C�����J��
	std::ifstream file(*pPath);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�e�L�X�g�t�@�C���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �t�@�C����Ǎ�
	AText text;			// �e�L�X�g���
	std::string str;	// �Ǎ�������
	while (file >> str)
	{ // �t�@�C���̏I�[�ł͂Ȃ��ꍇ���[�v

		if (str.front() == '#') { std::getline(file, str); }	// �R�����g�A�E�g
		else if (str == sLoadStart)
		{ // �Ǎ��J�n�̕�����ƈ�v�����ꍇ

			do { // END_TEXTBOX��ǂݍ��ނ܂Ń��[�v

				// �������ǂݍ���
				file >> str;

				if (str.front() == '#') { std::getline(file, str); }	// �R�����g�A�E�g
				else if (str == "NEXT_PATH")
				{
					file >> str;		// ����Ǎ�
					file >> *pPath;		// ���e�L�X�g�{�b�N�X�̕ۑ��p�X��Ǎ�
				}
				else if (str == "NEXT_KEY")
				{
					file >> str;		// ����Ǎ�
					file >> *pBoxKey;	// ���e�L�X�g�{�b�N�X�̌����L�[��Ǎ�
				}
			} while (str != "END_TEXTBOX");	// END_TEXTBOX��ǂݍ��ނ܂Ń��[�v
		}
	}

	// �t�@�C�������
	file.close();

	// ���̃e�L�X�g�{�b�N�X�����邩��Ԃ�
	return !(*pBoxKey == "-1" || *pBoxKey == "NONE");
}
