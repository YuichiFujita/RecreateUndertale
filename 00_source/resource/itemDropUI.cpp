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

// TODO
#include "sceneGame.h"
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
CItemDropUI::CItemDropUI(const int nChoiceItemIdx) : CItemUI(nChoiceItemIdx)
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
HRESULT CItemDropUI::Init(void)
{
	// �A�C�e��UI�̏�����
	if (FAILED(CItemUI::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�L�X�g���e�̐i�s
	NextText();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CItemDropUI::Uninit(void)
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
}

//============================================================
//	�`�揈��
//============================================================
void CItemDropUI::Draw(CShader *pShader)
{
	// �A�C�e��UI�̕`��
	CItemUI::Draw(pShader);
}

//============================================================
//	�e�L�X�g�{�b�N�X�i�s����
//============================================================
void CItemDropUI::NextText(void)
{
	int nTextIdx = GetCurTextIdx();			// �e�L�X�g�i�s�x�C���f�b�N�X
	int nItemIdx = GetChoiceItemIdx();		// �I���A�C�e���C���f�b�N�X
	CItem* pItem = GET_MANAGER->GetItem();	// �A�C�e�����
	const CItemData& rItemData = pItem->GetInfo(nItemIdx);	// �A�C�e�������f�[�^

	// �A�C�e���j�����̃e�L�X�g�����擾
	ATextBox textData = rItemData.GetInfo();	// TODO�FDrop�ɕύX

	int nNumText = (int)textData.size();	// �e�L�X�g����
	if (nTextIdx >= nNumText)
	{ // �e�L�X�g���I�������ꍇ

		// �I���A�C�e����j���ς݂ɂ���
		pItem->GetInfo(nItemIdx).Drop();

		// �t�B�[���h���j���[�̏I��
		CSceneGame::GetMenuManager()->SetEnableDrawMenu(false);
		return;
	}

	// ���݂̃e�L�X�g�i�s�x�ɍ��킹���e�L�X�g���e�ɕύX
	ChangeTextBox(textData[nTextIdx]);

	// �e�L�X�g�i�s�x��i�߂�
	CItemUI::NextText();
}
