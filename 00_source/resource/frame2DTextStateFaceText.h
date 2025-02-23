//============================================================
//
//	�\��t���e�L�X�g��ԃw�b�_�[ [frame2DTextStateFaceText.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_FACE_TEXT_H_
#define _FRAME2D_TEXT_STATE_FACE_TEXT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateText.h"
#include "frame2D.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2DTextBuffer;	// �e�L�X�g���ۑ��o�b�t�@�N���X
class CFaceUI;				// �\��UI�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �\��t���e�L�X�g��ԃN���X
class CFrame2DTextStateFaceText : public CFrame2DTextStateText
{
public:
	// �R���X�g���N�^
	CFrame2DTextStateFaceText();
	CFrame2DTextStateFaceText(const CFrame2D::EPreset preset);
	CFrame2DTextStateFaceText(const VECTOR3& rOffsetText, const VECTOR3& rOffsetFace);

	// �f�X�g���N�^
	~CFrame2DTextStateFaceText() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void BindTextBuffer(CFrame2DTextBuffer* pBuffer) override;	// �e�L�X�g���ۑ��o�b�t�@����
	inline CFrame2DTextStateFaceText* GetStateFaceText() override { return this; }	// �\��t���e�L�X�g��Ԏ擾

protected:
	// �I�[�o�[���C�h�֐�
	VECTOR3 GetPresetOffset(const CFrame2D::EPreset preset) override;	// �v���Z�b�g�I�t�Z�b�g�擾
	void SetPositionRelative() override;	// ���Έʒu�ݒ�

private:
	// �����o�ϐ�
	CFaceUI* m_pFace;	// �\����
	VECTOR3 m_offset;	// �\��I�t�Z�b�g
};

#endif	// _FRAME2D_TEXT_STATE_FACE_TEXT_H_
