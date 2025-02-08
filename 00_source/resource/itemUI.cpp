//============================================================
//
//	�A�C�e��UI���� [itemUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "itemUI.h"
#include "manager.h"
#include "item.h"
#include "menuManager.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CItemUI::AFuncInitText CItemUI::m_aFuncInitText[] =	// �e�L�X�g�������֐����X�g
{
	&CItemUI::InitUseText,	// �g�p�e�L�X�g������
	&CItemUI::InitInfoText,	// ���e�L�X�g������
	&CItemUI::InitDropText,	// �j���e�L�X�g������
};
CItemUI::AFuncBindText CItemUI::m_aFuncBindText[] =	// �e�L�X�g�����֐����X�g
{
	&CItemUI::BindUseText,	// �g�p�e�L�X�g����
	&CItemUI::BindInfoText,	// ���e�L�X�g����
	&CItemUI::BindDropText,	// �j���e�L�X�g����
};
CItemUI::AFuncActItem CItemUI::m_aFuncActItem[] =	// �A�C�e���s���֐����X�g
{
	&CItemUI::ActUseItem,	// �I���A�C�e���g�p�s��
	&CItemUI::ActInfoItem,	// �I���A�C�e�����s��
	&CItemUI::ActDropItem,	// �I���A�C�e���j���s��
};

//************************************************************
//	�q�N���X [CItemUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CItemUI::CItemUI(const CSelectItemUI::ESelect choiceAct, const int nChoiceItemIdx, const int nChoiceBagIdx) :
	m_choiceAct			(choiceAct),		// �I�𒆍s��
	m_nChoiceItemIdx	(nChoiceItemIdx),	// �I�𒆃A�C�e���C���f�b�N�X
	m_nChoiceBagIdx		(nChoiceBagIdx)		// �I�𒆃o�b�O�C���f�b�N�X
{
	// �X�^�e�B�b�N�A�T�[�g
	static_assert(NUM_ARRAY(m_aFuncInitText) == CSelectItemUI::SELECT_MAX, "ERROR : Act Count Mismatch");
	static_assert(NUM_ARRAY(m_aFuncBindText) == CSelectItemUI::SELECT_MAX, "ERROR : Act Count Mismatch");
	static_assert(NUM_ARRAY(m_aFuncActItem)  == CSelectItemUI::SELECT_MAX, "ERROR : Act Count Mismatch");
}

//============================================================
//	�f�X�g���N�^
//============================================================
CItemUI::~CItemUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CItemUI::Init()
{
	// �e�N���X�̏�����
	if (FAILED(CFrame2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �����j��/�X�V�����Ȃ����x���ɂ���
	SetLabel(LABEL_NONE);

	// �v���Z�b�g��ݒ�
	SetPreset(PRESET_DOWN);	// TODO�F���͌Œ�

	// �e�L�X�g�\���@�\��ݒ�
	ChangeModule(new CFrame2DModuleText(false));

	// �e�L�X�g�̏�����
	assert(m_aFuncInitText != nullptr);
	(this->*(m_aFuncInitText[m_choiceAct]))();

	// �e�L�X�g�̊���
	assert(m_aFuncBindText != nullptr);
	(this->*(m_aFuncBindText[m_choiceAct]))();

	// �s���̓K��
	assert(m_aFuncActItem != nullptr);
	(this->*(m_aFuncActItem[m_choiceAct]))();

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CItemUI::Uninit()
{
	// �e�N���X�̏I��
	CFrame2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CItemUI::Update(const float fDeltaTime)
{
	// �e�N���X�̍X�V
	CFrame2D::Update(fDeltaTime);

	if (!IsModuleText())
	{ // �e�L�X�g�\���@�\���I�������ꍇ

		// �t�B�[���h���j���[�̏I��
		CMenuManager::GetInstance()->SetEnableDrawMenu(false);
	}
}

//============================================================
//	�`�揈��
//============================================================
void CItemUI::Draw(CShader* pShader)
{
	// �e�N���X�̕`��
	CFrame2D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CItemUI* CItemUI::Create
(
	const CSelectItemUI::ESelect choiceAct,	// �I�𒆍s��
	const int nChoiceItemIdx,				// �I�𒆃A�C�e���C���f�b�N�X
	const int nChoiceBagIdx					// �I�𒆃o�b�O�C���f�b�N�X
)
{
	// �A�C�e��UI�̐���
	CItemUI* pItemUI = new CItemUI(choiceAct, nChoiceItemIdx, nChoiceBagIdx);
	if (pItemUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �A�C�e���̏�����
		if (FAILED(pItemUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �A�C�e���̔j��
			SAFE_DELETE(pItemUI);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pItemUI;
	}
}

//============================================================
//	�g�p�e�L�X�g����������
//============================================================
HRESULT CItemUI::InitUseText()
{
	// �@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// �e�L�X�g�@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// �A�C�e������ǂݍ��񂾃p�X���擾
	CItem* pItem = GET_MANAGER->GetItem();							// �A�C�e�����
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// �A�C�e�����

	// �e�L�X�g�̏������o�b�t�@���擾
	CFrame2DModuleText::AMapBuffText* pMapBuffText = rItemData.CreateUseBuffText();

	// �e�L�X�g�o�b�t�@�A�z�z��̊���
	pModuleText->BindBuffTextArray(pMapBuffText, "NONE", "NONE");

	// �e�L�X�g�o�b�t�@�̊���
	pModuleText->BindText("0");

	return S_OK;
}

//============================================================
//	���e�L�X�g����������
//============================================================
HRESULT CItemUI::InitInfoText()
{
	// �@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// �e�L�X�g�@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// �A�C�e������ǂݍ��񂾃p�X���擾
	CItem* pItem = GET_MANAGER->GetItem();							// �A�C�e�����
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// �A�C�e�����

	// �e�L�X�g�̏������o�b�t�@���擾
	CFrame2DModuleText::AMapBuffText* pMapBuffText = rItemData.CreateInfoBuffText();

	// �e�L�X�g�o�b�t�@�A�z�z��̊���
	pModuleText->BindBuffTextArray(pMapBuffText, "NONE", "NONE");

	// �e�L�X�g�o�b�t�@�̊���
	pModuleText->BindText("0");

	return S_OK;
}

//============================================================
//	�j���e�L�X�g����������
//============================================================
HRESULT CItemUI::InitDropText()
{
	// �@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// �e�L�X�g�@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// �A�C�e������ǂݍ��񂾃p�X���擾
	CItem* pItem = GET_MANAGER->GetItem();							// �A�C�e�����
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// �A�C�e�����

	// �e�L�X�g�̏������o�b�t�@���擾
	CFrame2DModuleText::AMapBuffText* pMapBuffText = rItemData.CreateDropBuffText();

	// �e�L�X�g�o�b�t�@�A�z�z��̊���
	pModuleText->BindBuffTextArray(pMapBuffText, "NONE", "NONE");

	// �e�L�X�g�o�b�t�@�̊���
	pModuleText->BindText("0");

	return S_OK;
}

//============================================================
//	�g�p�e�L�X�g��������
//============================================================
HRESULT CItemUI::BindUseText()
{
	// �@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// �e�L�X�g�@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// �A�C�e������ǂݍ��񂾃p�X���擾
	CItem* pItem = GET_MANAGER->GetItem();							// �A�C�e�����
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// �A�C�e�����

	// �A�C�e���g�p���̃e�L�X�g������
	if (SUCCEEDED(pModuleText->BindTextBox(rItemData.GetDataPath(), "USE")))
	{ // �����ɐ��������ꍇ

		// �A�C�e���g�p��̕�������Ō���ɒǉ�
		const std::string sKey = std::to_string(pModuleText->GetNumText() - 1);
		if (FAILED(pModuleText->PushBackString(rItemData.UseEnd(), sKey)))
		{ // �ǉ��Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}
	}

	return S_OK;
}

//============================================================
//	���e�L�X�g��������
//============================================================
HRESULT CItemUI::BindInfoText()
{
	// �@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// �e�L�X�g�@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// �A�C�e������ǂݍ��񂾃p�X���擾
	CItem* pItem = GET_MANAGER->GetItem();							// �A�C�e�����
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// �A�C�e�����

	// �A�C�e�����̊m�F���̃e�L�X�g������
	if (SUCCEEDED(pModuleText->BindTextBox(rItemData.GetDataPath(), "INFO")))
	{ // �����ɐ��������ꍇ

		// �A�C�e���ڍׂ�擪�ɒǉ�
		if (FAILED(pModuleText->PushFrontString(rItemData.Detail(), "0")))
		{ // �ǉ��Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}
	}

	return S_OK;
}

//============================================================
//	�j���e�L�X�g��������
//============================================================
HRESULT CItemUI::BindDropText()
{
	// �@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// �e�L�X�g�@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// �A�C�e������ǂݍ��񂾃p�X���擾
	CItem* pItem = GET_MANAGER->GetItem();							// �A�C�e�����
	const CItemData& rItemData = pItem->GetInfo(m_nChoiceItemIdx);	// �A�C�e�����

	// �A�C�e���j�����̃e�L�X�g������
	pModuleText->BindTextBox(rItemData.GetDataPath(), "DROP");

	return S_OK;
}

//============================================================
//	�I���A�C�e���g�p�s������
//============================================================
void CItemUI::ActUseItem()
{
	// �I���A�C�e�����g�p�ς݂ɂ���
	CItem* pItem = GET_MANAGER->GetItem();	// �A�C�e�����
	pItem->GetInfo(m_nChoiceItemIdx).Use(m_nChoiceBagIdx);
}

//============================================================
//	�I���A�C�e�����s������
//============================================================
void CItemUI::ActInfoItem()
{
	// �I���A�C�e���̏����m�F�ς݂ɂ���
	CItem* pItem = GET_MANAGER->GetItem();	// �A�C�e�����
	pItem->GetInfo(m_nChoiceItemIdx).Info(m_nChoiceBagIdx);
}

//============================================================
//	�I���A�C�e���j���s������
//============================================================
void CItemUI::ActDropItem()
{
	// �I���A�C�e����j���ς݂ɂ���
	CItem* pItem = GET_MANAGER->GetItem();	// �A�C�e�����
	pItem->GetInfo(m_nChoiceItemIdx).Drop(m_nChoiceBagIdx);
}

//============================================================
//	�e�L�X�g�\���@�\���̊m�F����
//============================================================
bool CItemUI::IsModuleText() const
{
	// �@�\�����蓖�Ă��Ă��Ȃ��ꍇ������
	CFrame2DModule* pModule = GetModule();		// ���݋@�\
	if (pModule == nullptr) { return false; }	// �e�L�X�g�\���ł͂Ȃ�

	// �@�\���e�L�X�g�\������Ԃ�
	return (typeid(*pModule) == typeid(CFrame2DModuleText));
}
