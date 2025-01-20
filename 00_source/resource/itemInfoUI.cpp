#if 0
//============================================================
//
//	��񃁃j���[���� [itemInfoUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "itemInfoUI.h"
#include "manager.h"
#include "item.h"
#include "menuManager.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// ��񃁃j���[�̗D�揇��
}

//************************************************************
//	�q�N���X [CItemInfoUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CItemInfoUI::CItemInfoUI(const int nChoiceItemIdx, const int nChoiceBagIdx) : CItemUI(nChoiceItemIdx, nChoiceBagIdx)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CItemInfoUI::~CItemInfoUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CItemInfoUI::Init()
{
	// �A�C�e��UI�̏�����
	if (FAILED(CItemUI::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModule* pModule = GetModule();
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// �e�L�X�g�@�\�����ݒ�̏ꍇ�G���[
	CFrame2DModuleText* pModuleText = pModule->GetModuleText();
	if (pModuleText == nullptr) { assert(false); return E_FAIL; }

	// �A�C�e������ǂݍ��񂾃p�X���擾
	CItem* pItem = GET_MANAGER->GetItem();							// �A�C�e�����
	const CItemData& rItem = pItem->GetInfo(GetChoiceItemIdx());	// �A�C�e�����
	const std::string sPath = rItem.GetDataPath();					// �A�C�e�����Ǎ��p�X



	// �e�L�X�g�̏������o�b�t�@���擾
	CFrame2DModuleText::ABuffTextArray mapBuffText = rItem.CreateInfoBuffTextArray();

	// �e�L�X�g�o�b�t�@�A�z�z��̊���
	pModuleText->BindBuffTextArray(mapBuffText, "NONE", "NONE", "0");

	// �e�L�X�g�o�b�t�@�̊���
	pModuleText->BindText("0");



	// �A�C�e�����̊m�F���̃e�L�X�g������
	if (SUCCEEDED(pModuleText->BindTextBox(sPath, "INFO")))
	{ // �����ɐ��������ꍇ

		// �A�C�e���ڍׂ�擪�ɒǉ�
		pModuleText->PushFrontString(rItem.Detail(), "0");
	}

	// �I���A�C�e���̏����m�F�ς݂ɂ���
	int nItemIdx = GetChoiceItemIdx();	// �I���A�C�e���C���f�b�N�X
	int nBagIdx = GetChoiceBagIdx();	// �I���o�b�O�C���f�b�N�X
	pItem->GetInfo(nItemIdx).Info(nBagIdx);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CItemInfoUI::Uninit()
{
	// �A�C�e��UI�̏I��
	CItemUI::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CItemInfoUI::Update(const float fDeltaTime)
{
	// �A�C�e��UI�̍X�V
	CItemUI::Update(fDeltaTime);

	if (!IsModuleText())
	{ // �e�L�X�g�\���@�\���I�������ꍇ

		// �t�B�[���h���j���[�̏I��
		CMenuManager::GetInstance()->SetEnableDrawMenu(false);
	}
}

//============================================================
//	�`�揈��
//============================================================
void CItemInfoUI::Draw(CShader* pShader)
{
	// �A�C�e��UI�̕`��
	CItemUI::Draw(pShader);
}
#endif