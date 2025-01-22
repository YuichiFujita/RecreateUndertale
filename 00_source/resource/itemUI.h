//============================================================
//
//	�A�C�e��UI�w�b�_�[ [itemUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ITEM_UI_H_
#define _ITEM_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2D.h"
#include "selectItemUI.h"

//************************************************************
//	�N���X��`
//************************************************************
// �A�C�e��UI�N���X
class CItemUI : public CFrame2D
{
public:
	// �R���X�g���N�^
	CItemUI(const CSelectItemUI::ESelect choiceAct, const int nChoiceItemIdx, const int nChoiceBagIdx);

	// �f�X�g���N�^
	~CItemUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CItemUI* Create	// ����
	( // ����
		const CSelectItemUI::ESelect choiceAct,	// �I�𒆍s��
		const int nChoiceItemIdx,				// �I�𒆃A�C�e���C���f�b�N�X
		const int nChoiceBagIdx					// �I�𒆃o�b�O�C���f�b�N�X
	);

private:
	// �G�C���A�X��`
	typedef HRESULT(CItemUI::*AFuncInitText)();	// �e�L�X�g�������֐��|�C���^
	typedef HRESULT(CItemUI::*AFuncBindText)();	// �e�L�X�g�����֐��|�C���^
	typedef void(CItemUI::*AFuncActItem)();		// �A�C�e���s���֐��|�C���^

	// �ÓI�����o�ϐ�
	static AFuncInitText m_aFuncInitText[];	// �e�L�X�g�������֐����X�g
	static AFuncBindText m_aFuncBindText[];	// �e�L�X�g�����֐����X�g
	static AFuncActItem	 m_aFuncActItem[];	// �A�C�e���s���֐����X�g

	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	HRESULT InitUseText();		// �g�p�e�L�X�g������
	HRESULT InitInfoText();		// ���e�L�X�g������
	HRESULT InitDropText();		// �j���e�L�X�g������
	HRESULT BindUseText();		// �g�p�e�L�X�g����
	HRESULT BindInfoText();		// ���e�L�X�g����
	HRESULT BindDropText();		// �j���e�L�X�g����
	void ActUseItem();			// �I���A�C�e���g�p�s��
	void ActInfoItem();			// �I���A�C�e�����s��
	void ActDropItem();			// �I���A�C�e���j���s��
	bool IsModuleText() const;	// �e�L�X�g�\���@�\���̊m�F

	// �����o�ϐ�
	const CSelectItemUI::ESelect m_choiceAct;	// �I�𒆍s��
	const int m_nChoiceItemIdx;	// �I�𒆃A�C�e���C���f�b�N�X
	const int m_nChoiceBagIdx;	// �I�𒆃o�b�O�C���f�b�N�X
};

#endif	// _ITEM_UI_H_
