#if 0
//============================================================
//
//	�j�����j���[���� [itemDropUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "itemDropUI.h"
#include "manager.h"
#include "item.h"
#include "menuManager.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// �j�����j���[�̗D�揇��
}

//************************************************************
//	�q�N���X [CItemDropUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CItemDropUI::CItemDropUI(const int nChoiceItemIdx, const int nChoiceBagIdx) : CItemUI(nChoiceItemIdx, nChoiceBagIdx)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CItemDropUI::~CItemDropUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CItemDropUI::Init()
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
	CFrame2DModuleText::ABuffTextArray mapBuffText = rItem.CreateDropBuffTextArray();

	// �e�L�X�g�o�b�t�@�A�z�z��̊���
	pModuleText->BindBuffTextArray(mapBuffText, "NONE", "NONE", "0");

	// �e�L�X�g�o�b�t�@�̊���
	pModuleText->BindText("0");



	// �A�C�e���j�����̃e�L�X�g������
	pModuleText->BindTextBox(sPath, "DROP");

	// �I���A�C�e����j���ς݂ɂ���
	int nItemIdx = GetChoiceItemIdx();	// �I���A�C�e���C���f�b�N�X
	int nBagIdx = GetChoiceBagIdx();	// �I���o�b�O�C���f�b�N�X
	pItem->GetInfo(nItemIdx).Drop(nBagIdx);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CItemDropUI::Uninit()
{
	// �A�C�e��UI�̏I��
	CItemUI::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CItemDropUI::Update(const float fDeltaTime)
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
void CItemDropUI::Draw(CShader* pShader)
{
	// �A�C�e��UI�̕`��
	CItemUI::Draw(pShader);
}
#endif