//============================================================
//
//	�g�p���j���[���� [itemUseUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "itemUseUI.h"
#include "manager.h"
#include "item.h"
#include "menuManager.h"
#include "frame2DTextBuffer.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// �g�p���j���[�̗D�揇��
}

//************************************************************
//	�q�N���X [CItemUseUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CItemUseUI::CItemUseUI(const int nChoiceItemIdx, const int nChoiceBagIdx) : CItemUI(nChoiceItemIdx, nChoiceBagIdx)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CItemUseUI::~CItemUseUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CItemUseUI::Init()
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
	CFrame2DModuleText::ABuffTextArray mapBuffText = rItem.CreateUseBuffTextArray();

	// �e�L�X�g�o�b�t�@�A�z�z��̊���
	pModuleText->BindBuffTextArray(mapBuffText, "NONE", "NONE", "0");

	// �e�L�X�g�o�b�t�@�̊���
	pModuleText->BindText("0");



	// �A�C�e���g�p���̃e�L�X�g������
	pModuleText->BindTextBox(sPath, "USE");

	// �e�L�X�g���e�̐i�s
	//NextText();

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CItemUseUI::Uninit()
{
	// �A�C�e��UI�̏I��
	CItemUI::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CItemUseUI::Update(const float fDeltaTime)
{
	// �A�C�e��UI�̍X�V
	CItemUI::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CItemUseUI::Draw(CShader* pShader)
{
	// �A�C�e��UI�̕`��
	CItemUI::Draw(pShader);
}

//============================================================
//	�e�L�X�g�{�b�N�X�i�s����
//============================================================
void CItemUseUI::NextText()
{
	// TODO�FNextText�̍쐬
#if 0
	int nTextIdx = GetCurTextIdx();			// �e�L�X�g�i�s�x�C���f�b�N�X
	int nItemIdx = GetChoiceItemIdx();		// �I���A�C�e���C���f�b�N�X
	CItem* pItem = GET_MANAGER->GetItem();	// �A�C�e�����
	const CItemData& rItemData = pItem->GetInfo(nItemIdx);	// �A�C�e�������f�[�^

	// �A�C�e���g�p���̃e�L�X�g�����擾
	ATextBox textData = rItemData.GetUse();

	int nNumText = (int)textData.size();	// �e�L�X�g����
	if (nTextIdx >= nNumText)
	{ // �e�L�X�g���I�������ꍇ

		// �I���A�C�e�����g�p�ς݂ɂ���
		int nBagIdx = GetChoiceBagIdx();	// �I���o�b�O�C���f�b�N�X
		pItem->GetInfo(nItemIdx).Use(nBagIdx);

		// �t�B�[���h���j���[�̏I��
		CMenuManager::GetInstance()->SetEnableDrawMenu(false);
		return;
	}

	// ���݂̃e�L�X�g�i�s�x�ɍ��킹���e�L�X�g���e�ɕύX
	ChangeTextBox(textData[nTextIdx]);

	// �e�L�X�g�i�s�x��i�߂�
	CItemUI::NextText();

	if (nTextIdx + 1 >= nNumText)
	{ // �ŏI�e�L�X�g�̏ꍇ

		// �A�C�e���g�p��̕�������Ō���ɒǉ�
		PushBackString(rItemData.UseEnd());
	}
#endif
}
