//============================================================
//
//	�A�C�e���e�L�X�g��ԃw�b�_�[ [frame2DTextStateItem.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_ITEM_H_
#define _FRAME2D_TEXT_STATE_ITEM_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateText.h"
#include "frame2D.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2DTextBuffer;	// �e�L�X�g���ۑ��o�b�t�@�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �A�C�e���e�L�X�g��ԃN���X
class CFrame2DTextStateItem : public CFrame2DTextStateText
{
public:
	// �R���X�g���N�^
	CFrame2DTextStateItem();
	CFrame2DTextStateItem(const CFrame2D::EPreset preset);
	CFrame2DTextStateItem(const VECTOR3& rOffset);

	// �f�X�g���N�^
	~CFrame2DTextStateItem() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	inline CFrame2DTextStateItem* GetStateItem() override { return this; }	// �A�C�e���e�L�X�g��Ԏ擾
};

#endif	// _FRAME2D_TEXT_STATE_ITEM_H_
