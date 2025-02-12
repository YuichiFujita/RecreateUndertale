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
//	�萔�錾
//************************************************************
namespace
{
	const std::string KEY_TEXT = "TEXT_";				// �e�L�X�g�Ǎ��J�n�L�[
	const int KET_TEXT_LEN = (int)KEY_TEXT.length();	// �Ǎ��J�n�e�L�X�g�L�[�̕�����
}

//************************************************************
//	�q�N���X [CFrame2DModuleText] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2DModuleText::CFrame2DModuleText(const bool bAutoUninit) :
	m_pState			(nullptr),		// ���
	m_pMapBuffText		(nullptr),		// �e�L�X�g�o�b�t�@�A�z�z��
	m_sNextPath			(""),			// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	m_sNextBoxKey		(""),			// ���e�L�X�g�{�b�N�X�̌����L�[
	m_sStartKey			(""),			// �e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[
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
	m_pState		= nullptr;	// ���
	m_pMapBuffText	= nullptr;	// �e�L�X�g�o�b�t�@�A�z�z��
	m_sNextPath		= "NONE";	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	m_sNextBoxKey	= "NONE";	// ���e�L�X�g�{�b�N�X�̌����L�[
	m_sStartKey		= "NONE";	// �e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[

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
	// �e�L�X�g�o�b�t�@�̔j��
	ReleaseBuffText();

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
//	�e�L�X�g�o�b�t�@�A�z�z��̊�������
//============================================================
void CFrame2DModuleText::BindMapBuffText
(
	AMapBuffText* pMapBuffText,		// �e�L�X�g�o�b�t�@�A�z�z��|�C���^
	const std::string& rFilePath,	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	const std::string& rBoxKey,		// ���e�L�X�g�{�b�N�X�̌����L�[
	const std::string& rStartKey	// �e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[
)
{
	// �e�L�X�g�o�b�t�@�̔j��
	ReleaseBuffText();

	// �e�L�X�g�o�b�t�@�A�z�z��̊���
	m_pMapBuffText = pMapBuffText;

	// ���e�L�X�g�{�b�N�X���̊���
	m_sNextPath		= rFilePath;	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	m_sNextBoxKey	= rBoxKey;		// ���e�L�X�g�{�b�N�X�̌����L�[
	m_sStartKey		= rStartKey;	// �e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[
}

//============================================================
//	�e�L�X�g�{�b�N�X�̊������� (���s����)
//============================================================
CFrame2DModuleText::ETextResult CFrame2DModuleText::BindTextBoxIgnoreFail
(
	const std::string& rFilePath,	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	const std::string& rBoxKey		// ���e�L�X�g�{�b�N�X�̌����L�[
)
{
	// �e�L�X�g�{�b�N�X�̓Ǎ�
	ETextResult tr = LoadTextBoxIgnoreFail(rFilePath, rBoxKey);
	if (TR_SAFE_FAIL(tr))
	{ // �Ǎ��Ɏ��s�����ꍇ

		return tr;
	}

	// �e�L�X�g�̊���
	if (FAILED(BindText(m_sStartKey)))
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return RES_FAIL;
	}

	return RES_OK;
}

//============================================================
//	�e�L�X�g�{�b�N�X�̊������� (���s��~)
//============================================================
HRESULT CFrame2DModuleText::BindTextBox
(
	const std::string& rFilePath,	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	const std::string& rBoxKey		// ���e�L�X�g�{�b�N�X�̌����L�[
)
{
	// �e�L�X�g�{�b�N�X�̊���
	ETextResult tr = BindTextBoxIgnoreFail(rFilePath, rBoxKey);
	if (TR_SAFE_FAIL(tr))
	{ // �����Ɏ��s�����ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		switch (tr)
		{ // �e�L�X�g���U���g���Ƃ̏���
		case RES_TEXTBOX_FAIL:
			MessageBox(nullptr, "�e�L�X�g�{�b�N�X�̊��蓖�ĂɎ��s�I", "�x���I", MB_ICONWARNING);
			break;

		case RES_TEXT_FAIL:
			MessageBox(nullptr, "�e�L�X�g�̊��蓖�ĂɎ��s�I", "�x���I", MB_ICONWARNING);
			break;

		default:
			MessageBox(nullptr, "�e�L�X�g�{�b�N�X�̊��蓖�Ď��ɗ�O�������I", "�x���I", MB_ICONWARNING);
			break;
		}

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
	auto itr = m_pMapBuffText->find(rTextKey);
	if (itr == m_pMapBuffText->end()) { assert(false); return E_FAIL; }

	// �e�L�X�g�o�b�t�@���ȗ���
	CFrame2DTextBuffer* pNextBuffText = itr->second;

	// �e�L�X�g�@�\��Ԃ̕ύX
	CFrame2D::EPreset preset = GetFramePreset();					// �t���[���v���Z�b�g
	CFrame2DTextState* pState = pNextBuffText->CreateState(preset);	// �e�L�X�g�@�\���
	if (FAILED(ChangeState(pState)))
	{ // �ύX�Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �e�L�X�g�o�b�t�@�̊���
	m_pState->BindTextBuffer(pNextBuffText);

	return S_OK;
}

//============================================================
//	�e�L�X�g�̑J�ڏ���
//============================================================
HRESULT CFrame2DModuleText::TransText(const std::string& rNextTextKey)
{
	if (rNextTextKey == "-1"
	||  rNextTextKey == "NONE"
	||  rNextTextKey.empty())
	{ // �e�L�X�g�J�ڐ悪�Ȃ��ꍇ

		if (m_sNextPath == "-1"
		||  m_sNextPath == "NONE"
		||  m_sNextPath.empty()
		||  m_sNextBoxKey == "-1"
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
			if (FAILED(BindTextBox(m_sNextPath, m_sNextBoxKey)))
			{ // �����Ɏ��s�����ꍇ

				assert(false);
				return E_FAIL;
			}
		}
	}
	else
	{ // �e�L�X�g�J�ڐ悪����ꍇ

		// ���̃e�L�X�g������
		if (FAILED(BindText(rNextTextKey)))
		{ // �����Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}
	}

	return S_OK;
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
//	������̐擪�ǉ����� (�}���`�o�C�g������)
//============================================================
HRESULT CFrame2DModuleText::PushFrontString(const std::string& rStr, const std::string& rTextKey)
{
	// �����L�[�̃e�L�X�g������
	auto itr = m_pMapBuffText->find(rTextKey);
	if (itr == m_pMapBuffText->end()) { assert(false); return E_FAIL; }

	// �e�L�X�g���ȗ���
	AText* pText = &itr->second->m_text;

	// �擪�ɕ������ǉ�
	pText->insert(pText->begin(), rStr);

	// ��Ԃ����ݒ�̏ꍇ������
	if (m_pState == nullptr) { return S_OK; }

	if (rTextKey == m_pState->GetCurTextKey())
	{ // ���݂̊����e�L�X�g�ۑ��L�[�Ɠ���̏ꍇ

		// �ǉ������e�L�X�g�𔽉f
		if (FAILED(BindText(rTextKey)))
		{ // �����Ɏ��s�����ꍇ

			return E_FAIL;
		}
	}

	return S_OK;
}

//============================================================
//	������̐擪�ǉ����� (���C�h������)
//============================================================
HRESULT CFrame2DModuleText::PushFrontString(const std::wstring& rStr, const std::string& rTextKey)
{
	// ��������}���`�o�C�g�ϊ�
	std::string sStr = useful::WideToMultiByte(rStr);

	// �������擪�ɒǉ�
	if (FAILED(PushFrontString(sStr, rTextKey)))
	{ // �ǉ��Ɏ��s�����ꍇ

		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	������̍Ō���ǉ����� (�}���`�o�C�g������)
//============================================================
HRESULT CFrame2DModuleText::PushBackString(const std::string& rStr, const std::string& rTextKey)
{
	// �����L�[�̃e�L�X�g������
	auto itr = m_pMapBuffText->find(rTextKey);
	if (itr == m_pMapBuffText->end()) { assert(false); return E_FAIL; }

	// �e�L�X�g���ȗ���
	AText* pText = &itr->second->m_text;

	// �Ō���ɕ������ǉ�
	pText->push_back(rStr);

	// ��Ԃ����ݒ�̏ꍇ������
	if (m_pState == nullptr) { return S_OK; }

	if (rTextKey == m_pState->GetCurTextKey())
	{ // ���݂̊����e�L�X�g�ۑ��L�[�Ɠ���̏ꍇ

		// �ǉ������e�L�X�g�𔽉f
		if (FAILED(BindText(rTextKey)))
		{ // �����Ɏ��s�����ꍇ

			return E_FAIL;
		}
	}

	return S_OK;
}

//============================================================
//	������̍Ō���ǉ����� (���C�h������)
//============================================================
HRESULT CFrame2DModuleText::PushBackString(const std::wstring& rStr, const std::string& rTextKey)
{
	// ��������}���`�o�C�g�ϊ�
	std::string sStr = useful::WideToMultiByte(rStr);

	// ��������Ō���ɒǉ�
	if (FAILED(PushBackString(sStr, rTextKey)))
	{ // �ǉ��Ɏ��s�����ꍇ

		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�s���̎擾����
//============================================================
int CFrame2DModuleText::GetNumString(const std::string& rTextKey) const
{
	// �����L�[�̃e�L�X�g������
	auto itr = m_pMapBuffText->find(rTextKey);
	if (itr == m_pMapBuffText->end()) { assert(false); return NONE_IDX; }

	// �e�L�X�g���ȗ���
	AText* pText = &itr->second->m_text;

	// �e�L�X�g�̍s����Ԃ�
	return (int)pText->size();
}

//============================================================
//	�e�L�X�g���̎擾����
//============================================================
int CFrame2DModuleText::GetNumText() const
{
	// �e�L�X�g�o�b�t�@�z�񂪂Ȃ��ꍇ�G���[
	if (m_pMapBuffText == nullptr) { assert(false); return 0; }

	// ���݂̃e�L�X�g����Ԃ�
	return (int)m_pMapBuffText->size();
}

//============================================================
//	�e�L�X�g�o�b�t�@�A�z�z��̔j������
//============================================================
void CFrame2DModuleText::ReleaseBuffText()
{
	// �e�L�X�g�����݂��Ȃ��ꍇ������
	if (m_pMapBuffText == nullptr) { return; }

	for (auto& rMap : *m_pMapBuffText)
	{ // �v�f�����J��Ԃ�

		// �e�L�X�g�o�b�t�@�̔j��
		SAFE_DELETE(rMap.second);
	}

	// �e�L�X�g�o�b�t�@�A�z�z����N���A
	m_pMapBuffText->clear();

	// �e�L�X�g�o�b�t�@�A�z�z��̔j��
	SAFE_DELETE(m_pMapBuffText);
}

//============================================================
//	�e�L�X�g�o�b�t�@�̐�������
//============================================================
CFrame2DTextBuffer* CFrame2DModuleText::CreateBuffText(const std::string& rCreateKey, const int nFaceIdx)
{
	// TODO�F�ǉ�������C��
	// �����L�[�ɉ������ۑ��o�b�t�@�̐���
	if		(rCreateKey == "TEXT")
	{
		// ��C���f�b�N�X�ɉ����Đ����ύX
		if (nFaceIdx == -1)	{ return new CFrame2DTextBufferText; }			// �e�L�X�g�ۑ��o�b�t�@
		else				{ return new CFrame2DTextBufferText; }			// �\��t���e�L�X�g�ۑ��o�b�t�@
	}
	else if	(rCreateKey == "SELECT")
	{
		// ��C���f�b�N�X�ɉ����Đ����ύX
		if (nFaceIdx == -1)	{ return new CFrame2DTextBufferSelect; }		// �I��t���e�L�X�g�ۑ��o�b�t�@
		else				{ return new CFrame2DTextBufferSelect; }		// �\��/�I��t���e�L�X�g�ۑ��o�b�t�@
	}
	else if	(rCreateKey == "ITEM") { return new CFrame2DTextBufferItem; }	// �A�C�e���e�L�X�g�ۑ��o�b�t�@

	// ���݂��Ȃ������L�[�̏ꍇ�G���[
	assert(false);
	return nullptr;
}

//============================================================
//	�e�L�X�g�{�b�N�X�̓Ǎ����� (��O����)
//============================================================
CFrame2DModuleText::ETextResult CFrame2DModuleText::LoadTextBoxIgnoreFail(const std::string& rFilePath, const std::string& rBoxKey)
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
		return RES_FAIL;
	}

	// �t�@�C����Ǎ�
	std::string str;					// �Ǎ�������
	ETextResult tr = RES_TEXTBOX_FAIL;	// �Ǎ��t���O
	while (file >> str)
	{ // �t�@�C���̏I�[�ł͂Ȃ��ꍇ���[�v

		if (str.front() == '#') { std::getline(file, str); }	// �R�����g�A�E�g
		else if (str == sLoadStart)
		{ // �Ǎ��J�n�̕�����ƈ�v�����ꍇ

			// �e�L�X�g�̓Ǎ�
			tr = LoadText(&file, rFilePath);
			break;
		}
	}

	// �t�@�C�������
	file.close();

	// �e�L�X�g�����݂�������Ԃ�
	return tr;
}

//============================================================
//	�e�L�X�g�{�b�N�X�̓Ǎ����� (���s��~)
//============================================================
HRESULT CFrame2DModuleText::LoadTextBox(const std::string& rFilePath, const std::string& rBoxKey)
{
	// �e�L�X�g�{�b�N�X�̓Ǎ�
	ETextResult tr = LoadTextBoxIgnoreFail(rFilePath, rBoxKey);
	if (TR_SAFE_FAIL(tr))
	{ // �Ǎ��Ɏ��s�����ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		switch (tr)
		{ // �e�L�X�g���U���g���Ƃ̏���
		case RES_TEXTBOX_FAIL:
			MessageBox(nullptr, "�e�L�X�g�{�b�N�X�̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
			break;

		case RES_TEXT_FAIL:
			MessageBox(nullptr, "�e�L�X�g�̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
			break;

		default:
			MessageBox(nullptr, "�e�L�X�g�{�b�N�X�̓ǂݍ��ݎ��ɗ�O�������I", "�x���I", MB_ICONWARNING);
			break;
		}

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�e�L�X�g�̓Ǎ�����
//============================================================
CFrame2DModuleText::ETextResult CFrame2DModuleText::LoadText(std::ifstream* pFile, const std::string& rFilePath)
{
	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return RES_FAIL; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return RES_FAIL; }

	// �t�@�C����Ǎ�
	std::string str;			// �Ǎ�������
	std::string sModuleKey;		// ���W���[�������L�[
	int nFaceIdx = NONE_IDX;	// ��C���f�b�N�X
	std::string sNextPath		= rFilePath;	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	std::string sNextBoxKey		= "NONE";		// ���e�L�X�g�{�b�N�X�̌����L�[
	std::string sStartKey		= "0";			// �e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[
	AMapBuffText* pMapBuffText	= nullptr;		// �e�L�X�g�o�b�t�@�A�z�z��
	do { // END_TEXTBOX��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> str;

		// �e�L�X�g�J�n�L�[������
		size_t idxFind = str.find(KEY_TEXT);

		if (str.front() == '#') { std::getline(*pFile, str); }	// �R�����g�A�E�g
		else if (idxFind != std::string::npos)
		{ // �e�L�X�g�J�n�L�[���������ꍇ

			// ������̓Ǎ�
			CFrame2DTextBuffer* pBuffText = LoadString(pFile, sModuleKey, nFaceIdx);	// �ǂݍ��񂾃e�L�X�g�o�b�t�@�擾
			if (pBuffText == nullptr)
			{ // �����Ɏ��s�����ꍇ

				assert(false);
				return RES_FAIL;
			}

			// �e�L�X�g�̌����L�[�ȊO�̕������폜
			str.erase(0, idxFind + KET_TEXT_LEN);

			// �ǂݍ��񂾃t�@�C���p�X��ۑ�
			pBuffText->m_sPath = rFilePath;

			// �e�L�X�g�̌����L�[��ۑ�
			pBuffText->m_sKey = str;

			if (pMapBuffText == nullptr)
			{ // �e�L�X�g�o�b�t�@�A�z�z�񂪖������̏ꍇ

				// �e�L�X�g�o�b�t�@�A�z�z��̐���
				pMapBuffText = new AMapBuffText;
				if (pMapBuffText == nullptr)
				{ // �����Ɏ��s�����ꍇ

					assert(false);
					return RES_FAIL;
				}
			}

			// �e�L�X�g�o�b�t�@��ۑ�
			pMapBuffText->insert(std::make_pair(str, pBuffText));
		}
		else if (str == "NEXT_PATH")
		{
			*pFile >> str;			// ����Ǎ�
			*pFile >> sNextPath;	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X��Ǎ�
		}
		else if (str == "NEXT_BOX")
		{
			*pFile >> str;			// ����Ǎ�
			*pFile >> sNextBoxKey;	// ���e�L�X�g�{�b�N�X�̌����L�[��Ǎ�
		}
		else if (str == "START_KEY")
		{
			*pFile >> str;			// ����Ǎ�
			*pFile >> sStartKey;	// �e�L�X�g�{�b�N�X�̃e�L�X�g�J�n�L�[��Ǎ�
		}
		else if (str == "ALL_MODULE")
		{
			*pFile >> str;			// ����Ǎ�
			*pFile >> sModuleKey;	// �������郂�W���[����Ǎ�
		}
		else if (str == "FACE")
		{
			*pFile >> str;			// ����Ǎ�
			*pFile >> nFaceIdx;		// ��C���f�b�N�X��Ǎ�
		}
	} while (str != "END_TEXTBOX");	// END_TEXTBOX��ǂݍ��ނ܂Ń��[�v

	if (pMapBuffText != nullptr)
	{ // �e�L�X�g�����݂���ꍇ

		// �e�L�X�g�o�b�t�@�A�z�z��̊���
		BindMapBuffText(pMapBuffText, sNextPath, sNextBoxKey, sStartKey);
		return RES_OK;
	}

	return RES_TEXT_FAIL;
}

//============================================================
//	������̓Ǎ�����
//============================================================
CFrame2DTextBuffer* CFrame2DModuleText::LoadString(std::ifstream* pFile, const std::string& rModuleKey, const int nFaceIdx)
{
	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return nullptr; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return nullptr; }

	CFrame2DTextBuffer* pBuffText = nullptr;	// �e�L�X�g���ۑ��o�b�t�@
	if (!rModuleKey.empty())
	{ // �����L�[���ݒ肳��Ă���ꍇ

		// �e�L�X�g�o�b�t�@�̐���
		assert(pBuffText == nullptr);
		pBuffText = CreateBuffText(rModuleKey, nFaceIdx);
	}

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	do { // END_TEXT��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// �R�����g�A�E�g
		else if (str == "MODULE")
		{
			*pFile >> str;	// ����Ǎ�
			*pFile >> str;	// �������郂�W���[����Ǎ�

			if (pBuffText != nullptr)
			{ // �e�L�X�g�o�b�t�@�������ς݂̏ꍇ

				// �G���[���b�Z�[�W�{�b�N�X
				MessageBox(nullptr, "�e�L�X�g�o�b�t�@�͐����ς݂ł��I", "�x���I", MB_ICONWARNING);
			}
			else
			{ // �e�L�X�g�o�b�t�@���������̏ꍇ

				// �e�L�X�g�o�b�t�@�̐���
				pBuffText = CreateBuffText(str, nFaceIdx);
			}
		}
		else if (str == "STR")
		{
			*pFile >> str;					// ����Ǎ�
			pFile->seekg(1, std::ios::cur);	// �Ǎ��ʒu���󔒕����炷
			std::getline(*pFile, str);		// ��s�S�ēǂݍ���

			// ������̐擪�ɋ󔒂�ǉ�
			str.insert(0, " ");

			// ��������Ō���ɒǉ�
			assert(pBuffText != nullptr);
			pBuffText->m_text.push_back(str);
		}
		else if (pBuffText != nullptr)
		{
			// �o�b�t�@���Ƃ̃Z�b�g�A�b�v�Ǎ�
			assert(pBuffText != nullptr);
			pBuffText->LoadSetup(pFile, str);
		}
	} while (str != "END_TEXT");	// END_TEXT��ǂݍ��ނ܂Ń��[�v

	// �e�L�X�g���ۑ��o�b�t�@��Ԃ�
	return pBuffText;
}
