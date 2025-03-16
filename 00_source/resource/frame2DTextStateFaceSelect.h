//============================================================
//
//	�\��/�I��t���e�L�X�g��ԃw�b�_�[ [frame2DTextStateFaceSelect.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_FACE_SELECT_H_
#define _FRAME2D_TEXT_STATE_FACE_SELECT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateSelect.h"
#include "frame2D.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2DTextBuffer;	// �e�L�X�g���ۑ��o�b�t�@�N���X
class CFaceUI;				// �\��UI�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �\��/�I��t���e�L�X�g��ԃN���X
class CFrame2DTextStateFaceSelect : public CFrame2DTextStateSelect
{
public:
	// �R���X�g���N�^
	CFrame2DTextStateFaceSelect();
	CFrame2DTextStateFaceSelect(const VECTOR3& rOffsetText, const VECTOR3& rOffsetSelectL, const VECTOR3& rOffsetSelectR, const VECTOR3& rOffsetFace);

	// �f�X�g���N�^
	~CFrame2DTextStateFaceSelect() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void BindTextBuffer(CFrame2DTextBuffer* pBuffer) override;	// �e�L�X�g���ۑ��o�b�t�@����
	inline CFrame2DTextStateFaceSelect* GetStateFaceSelect() override { return this; }	// �\��/�I��t���e�L�X�g��Ԏ擾

protected:
	// �I�[�o�[���C�h�֐�
	VECTOR3 GetPresetOffset(const CFrame2D::EPreset preset) override;	// �v���Z�b�g�I�t�Z�b�g�擾
	void SetPositionRelative() override;	// ���Έʒu�ݒ�

private:
	// �����o�ϐ�
	CFaceUI* m_pFace;	// �\����
	VECTOR3 m_offset;	// �\��I�t�Z�b�g
	int m_nTypeTalkEmo;	// ��b���̕\����
	int m_nTypeIdolEmo;	// �ҋ@���̕\����
};

#endif	// _FRAME2D_TEXT_STATE_FACE_SELECT_H_
