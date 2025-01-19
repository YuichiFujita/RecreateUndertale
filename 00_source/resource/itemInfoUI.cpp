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
	pModuleText->BindTextBox(sPath, "INFO");

	//// �e�L�X�g���e�̐i�s
	//NextText();

	//// �A�C�e���ڍׂ�擪�ɒǉ�
	//const CItemData& rItemData = pItem->GetInfo(GetChoiceItemIdx());	// �A�C�e�������f�[�^
	//PushFrontString(rItemData.Detail());

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
}

//============================================================
//	�`�揈��
//============================================================
void CItemInfoUI::Draw(CShader* pShader)
{
	// �A�C�e��UI�̕`��
	CItemUI::Draw(pShader);
}

//============================================================
//	�e�L�X�g�{�b�N�X�i�s����
//============================================================
void CItemInfoUI::NextText()
{
	// TODO�FNextText�̍쐬
#if 0
	int nTextIdx = GetCurTextIdx();			// �e�L�X�g�i�s�x�C���f�b�N�X
	int nItemIdx = GetChoiceItemIdx();		// �I���A�C�e���C���f�b�N�X
	CItem* pItem = GET_MANAGER->GetItem();	// �A�C�e�����
	const CItemData& rItemData = pItem->GetInfo(nItemIdx);	// �A�C�e�������f�[�^

	// �A�C�e�����̊m�F���̃e�L�X�g�����擾
	ATextBox textData = rItemData.GetInfo();

	int nNumText = (int)textData.size();	// �e�L�X�g����
	if (nTextIdx >= nNumText)
	{ // �e�L�X�g���I�������ꍇ

		// �I���A�C�e���̏����m�F�ς݂ɂ���
		int nBagIdx = GetChoiceBagIdx();	// �I���o�b�O�C���f�b�N�X
		pItem->GetInfo(nItemIdx).Info(nBagIdx);

		// �t�B�[���h���j���[�̏I��
		CMenuManager::GetInstance()->SetEnableDrawMenu(false);
		return;
	}

	// ���݂̃e�L�X�g�i�s�x�ɍ��킹���e�L�X�g���e�ɕύX
	ChangeTextBox(textData[nTextIdx]);

	// �e�L�X�g�i�s�x��i�߂�
	CItemUI::NextText();
#endif
}
