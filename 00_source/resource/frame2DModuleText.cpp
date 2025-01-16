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
#include "frame2DTextBuffer.h"

//************************************************************
//	�q�N���X [CFrame2DModuleText] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2DModuleText::CFrame2DModuleText(const bool bAutoUninit) :
	m_mapBuffText		({}),			// �e�L�X�g�o�b�t�@�A�z�z��
	m_pState			(nullptr),		// ���
	m_sNextPath			({}),			// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	m_sNextBoxKey		({}),			// ���e�L�X�g�{�b�N�X�̌����L�[
	m_sNextStartKey		({}),			// ���e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[
	m_bAutoUninitFrame	(bAutoUninit)	// �t���[�������j���t���O
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
	m_mapBuffText	= {};		// �e�L�X�g�o�b�t�@�A�z�z��
	m_pState		= nullptr;	// ���
	m_sNextPath		= "NONE";	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	m_sNextBoxKey	= "NONE";	// ���e�L�X�g�{�b�N�X�̌����L�[
	m_sNextStartKey	= "NONE";	// ���e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[

	CFrame2D::EPreset preset = GetFramePreset();	// �z�u�v���Z�b�g
	if (preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX)
	{ // �v���Z�b�g���͈͓��̏ꍇ

		// �e�L�X�g��Ԃ𐶐�
		ChangeState(new CFrame2DTextStateText(preset));	// �z�u�w��
	}
	else
	{ // �v���Z�b�g���͈͊O�̏ꍇ

		// �e�L�X�g��Ԃ𐶐�
		ChangeState(new CFrame2DTextStateText);	// �f�t�H���g
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFrame2DModuleText::Uninit()
{
	// �e�L�X�g�o�b�t�@�̍폜
	DeleteBuffText();

	// ��Ԃ̏I��
	SAFE_UNINIT(m_pState);

	// �@�\�̏�����
	m_pContext->InitModule();

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CFrame2DModuleText::Update(const float fDeltaTime)
{
	// ��Ԃ��Ƃ̍X�V
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CFrame2DModuleText::SetPriority(const int nPriority)
{
	// �e�L�X�g��Ԃ̗D�揇�ʂ�ݒ�
	m_pState->SetPriority(nPriority);
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFrame2DModuleText::SetVec3Position(const VECTOR3& rPos)
{
	// �e�L�X�g��Ԃ̈ʒu��ݒ�
	m_pState->SetVec3Position(rPos);
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFrame2DModuleText::SetVec3Rotation(const VECTOR3& rRot)
{
	// �e�L�X�g��Ԃ̌�����ݒ�
	m_pState->SetVec3Rotation(rRot);
}

//============================================================
//	�e�L�X�g�{�b�N�X�̊�������
//============================================================
HRESULT CFrame2DModuleText::BindTextBox(const std::string& rFilePath, const std::string& rBoxKey, const std::string& rNextStartKey)
{
	// ���e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[��ۑ�
	const std::string sNextStartKey = rNextStartKey;

	// �e�L�X�g�o�b�t�@�̍폜
	DeleteBuffText();

	// �e�L�X�g�{�b�N�X�̓Ǎ�
	if (FAILED(LoadTextBox(rFilePath, rBoxKey)))
	{ // �Ǎ��Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �e�L�X�g�̊���
	if (FAILED(BindText(sNextStartKey)))
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�e�L�X�g�̑J�ڏ���
//============================================================
void CFrame2DModuleText::TransText(const std::string& rNextTextKey)
{
	if (rNextTextKey == "-1"
	||  rNextTextKey == "NONE"
	||  rNextTextKey.empty())
	{ // �e�L�X�g�J�ڐ悪�Ȃ��ꍇ

		if (m_sNextBoxKey == "-1"
		||  m_sNextBoxKey == "NONE"
		||  m_sNextBoxKey.empty())
		{ // �e�L�X�g�{�b�N�X�J�ڐ悪�Ȃ��ꍇ

			if (m_bAutoUninitFrame)
			{ // �t���[�������j����ON�̏ꍇ

				// �R���e�L�X�g�̏I��
				SAFE_UNINIT(m_pContext);
			}
			else
			{ // �t���[�������j����OFF�̏ꍇ

				// �e�L�X�g�\���@�\�̏I��
				Uninit();
			}
		}
		else
		{ // �e�L�X�g�{�b�N�X�J�ڐ悪����ꍇ

			// ���̃e�L�X�g�{�b�N�X������
			BindTextBox(m_sNextPath, m_sNextBoxKey, m_sNextStartKey);	// TODO�F�I�������ƂɈႤ�e�L�X�g�{�b�N�X�ɂ���ׂ�悤�ɂ���
		}
	}
	else
	{ // �e�L�X�g�J�ڐ悪����ꍇ

		// ���̃e�L�X�g������
		BindText(rNextTextKey);
	}
}

//============================================================
//	��Ԃ̕ύX����
//============================================================
HRESULT CFrame2DModuleText::ChangeState(CFrame2DTextState* pState)
{
	// ��Ԃ̐����Ɏ��s���Ă���ꍇ������
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// ��ԃC���X�^���X���I��
	SAFE_UNINIT(m_pState);

	// ��ԃC���X�^���X��ύX
	assert(m_pState == nullptr);
	m_pState = pState;

	// ��ԂɃR���e�L�X�g��ݒ�
	m_pState->SetContext(this);

	// ��ԃC���X�^���X��������
	if (FAILED(m_pState->Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�e�L�X�g��������
//============================================================
HRESULT CFrame2DModuleText::BindText(const std::string& rTextKey)
{
	// �����L�[�̃e�L�X�g������
	auto itr = m_mapBuffText.find(rTextKey);
	if (itr == m_mapBuffText.end()) { assert(false); return E_FAIL; }

	// �e�L�X�g�o�b�t�@���ȗ���
	CFrame2DTextBuffer* pNextBuffText = itr->second;

	// �e�L�X�g�@�\��Ԃ̕ύX
	ChangeState(pNextBuffText->CreateState(GetFramePreset()));	// ���e�L�X�g�Ɏg�p����@�\���擾	// TODO�F������ԂȂ�ύX�Ȃ��ɂ���Ή��Ȃ�

	// �e�L�X�g�o�b�t�@�̊���
	m_pState->BindTextBuffer(pNextBuffText);

	// TODO�F�A�C�e���e�L�X�g���e�L�X�g�i�s���ƂɃA�C�e���C���f�b�N�X��Y�����̉�����
	//  �P �F�����e�L�X�g�@�\��ԂȂ�ύX���Ȃ��Ńe�L�X�g�̏������̂ݍs��
	//  �Q �Fframe2DModuleTextItem���쐬���A�����o�ϐ��ŃA�C�e���C���f�b�N�X���Ǘ�����
	//  �R �Fframe2DTextStateItem���Ǎ����ɃA�C�e���̖��O��ǂݍ��݁A�A�C�e���Ǘ���map�ɂ��ăA�C�e��������C���f�b�N�X������
	//  �S �F�S���������̂�Ǝ��֐��Ƃ��čč쐬

	return S_OK;
}

//============================================================
//	�e�L�X�g�o�b�t�@�A�z�z��̍폜����
//============================================================
void CFrame2DModuleText::DeleteBuffText()
{
	for (auto& rMap : m_mapBuffText)
	{ // �v�f�����J��Ԃ�

		// �e�L�X�g�o�b�t�@�̔j��
		SAFE_DELETE(rMap.second);
	}

	// �e�L�X�g�o�b�t�@�A�z�z����N���A
	m_mapBuffText.clear();
}

//============================================================
//	�e�L�X�g�o�b�t�@�̐�������
//============================================================
CFrame2DTextBuffer* CFrame2DModuleText::CreateBuffText(const std::string& rCreateKey)
{
	// �����L�[�ɉ������ۑ��o�b�t�@�̐���
	if		(rCreateKey == "TEXT")			{ return new CFrame2DTextBufferText; }		// �e�L�X�g�ۑ��o�b�t�@
	else if	(rCreateKey == "SELECT")		{ return new CFrame2DTextBufferSelect; }	// �I��t���e�L�X�g�ۑ��o�b�t�@
	// TODO�F�ǉ�������C��
	else if	(rCreateKey == "TEXT_FACE")		{ return new CFrame2DTextBufferText; }		// �\��t���e�L�X�g�ۑ��o�b�t�@
	else if	(rCreateKey == "SELECT_FACE")	{ return new CFrame2DTextBufferSelect; }	// �\��/�I��t���e�L�X�g�ۑ��o�b�t�@
	else if	(rCreateKey == "ITEM")			{ return new CFrame2DTextBufferItem; }		// �A�C�e���e�L�X�g�ۑ��o�b�t�@

	// ���݂��Ȃ������L�[�̏ꍇ�G���[
	assert(false);
	return nullptr;
}

//============================================================
//	�e�L�X�g�{�b�N�X�̓Ǎ�����
//============================================================
HRESULT CFrame2DModuleText::LoadTextBox(const std::string& rFilePath, const std::string& rBoxKey)
{
	// �Ǎ��̊J�n��������쐬
	std::string sLoadStart = "TEXTBOX_";	// �F���p�̐擪������ݒ�
	sLoadStart.append(rBoxKey);				// �����̔F���p������ƘA��

	// �t�@�C�����J��
	std::ifstream file(rFilePath);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�e�L�X�g�t�@�C���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	while (file >> str)
	{ // �t�@�C���̏I�[�ł͂Ȃ��ꍇ���[�v

		if (str.front() == '#') { std::getline(file, str); }	// �R�����g�A�E�g
		else if (str == sLoadStart)
		{ // �Ǎ��J�n�̕�����ƈ�v�����ꍇ

			// �e�L�X�g�̓Ǎ�
			LoadText(rFilePath, &file);
		}
	}

	// �t�@�C�������
	file.close();

	return S_OK;
}

//============================================================
//	�e�L�X�g�̓Ǎ�����
//============================================================
HRESULT CFrame2DModuleText::LoadText(const std::string& rFilePath, std::ifstream* pFile)
{
	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return E_FAIL; }

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	do { // END_TEXTBOX��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// �R�����g�A�E�g
		else if (str == "NEXT_PATH")
		{
			*pFile >> str;				// ����Ǎ�
			*pFile >> m_sNextPath;		// ���e�L�X�g�{�b�N�X�̕ۑ��p�X��Ǎ�
		}
		else if (str == "NEXT_BOX")
		{
			*pFile >> str;				// ����Ǎ�
			*pFile >> m_sNextBoxKey;	// ���e�L�X�g�{�b�N�X�̌����L�[��Ǎ�
		}
		else if (str == "NEXT_START")
		{
			*pFile >> str;				// ����Ǎ�
			*pFile >> m_sNextStartKey;	// ���e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[��Ǎ�
		}

		// TODO�F������FACE��NAME�̃L�[�𔻒�
		//		 FACE = -1�łȂ��Ȃ炱��ȍ~�̃e�L�X�g�����͊��

		else if (size_t findIdx = str.find("TEXT_") != std::string::npos)	// TODO�F�����ǂ��������͗v����
		{ // �Ǎ��J�n�̕����񂪊܂܂�Ă����ꍇ

			// �e�L�X�g�̌����L�[��Ǎ�
			str.erase(0, findIdx + 4);	// TODO�F�萔

			// ������̓Ǎ�
			CFrame2DTextBuffer* pBuffText = LoadString(pFile);	// �ǂݍ��񂾃e�L�X�g�o�b�t�@�擾
			if (pBuffText == nullptr)
			{ // �����Ɏ��s�����ꍇ

				assert(false);
				return E_FAIL;
			}

			// �ǂݍ��񂾃t�@�C���p�X��ۑ�
			pBuffText->m_sPath = rFilePath;

			// �e�L�X�g�o�b�t�@��ۑ�
			m_mapBuffText.insert(std::make_pair(str, pBuffText));
		}
	} while (str != "END_TEXTBOX");	// END_TEXTBOX��ǂݍ��ނ܂Ń��[�v

	return S_OK;
}

//============================================================
//	������̓Ǎ�����
//============================================================
CFrame2DTextBuffer* CFrame2DModuleText::LoadString(std::ifstream* pFile)
{
	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return nullptr; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return nullptr; }

	// �t�@�C����Ǎ�
	CFrame2DTextBuffer* pBuffText = nullptr;	// �e�L�X�g���ۑ��o�b�t�@
	std::string str;	// �Ǎ�������
	do { // END_TEXT��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// �R�����g�A�E�g
		else if (str == "MODULE")
		{
			*pFile >> str;	// ����Ǎ�
			*pFile >> str;	// �������郂�W���[����Ǎ�

			// �e�L�X�g�o�b�t�@�̐���
			assert(pBuffText == nullptr);
			pBuffText = CreateBuffText(str);
		}
		else if (str == "STR")
		{
			*pFile >> str;					// ����Ǎ�
			pFile->seekg(1, std::ios::cur);	// �Ǎ��ʒu���󔒕����炷
			std::getline(*pFile, str);		// ��s�S�ēǂݍ���

			// ������̐擪�ɋ󔒂�ǉ�
			str.insert(0, " ");

			// ��������Ō���ɒǉ�
			pBuffText->m_text.push_back(str);
		}
		else if (pBuffText != nullptr)
		{
			// �o�b�t�@���Ƃ̃Z�b�g�A�b�v�Ǎ�
			pBuffText->LoadSetup(pFile, str);
		}
	} while (str != "END_TEXT");	// END_TEXT��ǂݍ��ނ܂Ń��[�v

	// �e�L�X�g���ۑ��o�b�t�@��Ԃ�
	return pBuffText;
}
