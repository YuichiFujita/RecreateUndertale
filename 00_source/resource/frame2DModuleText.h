//============================================================
//
//	�e�L�X�g�\���@�\�w�b�_�[ [frame2DModuleText.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_MODULE_TEXT_H_
#define _FRAME2D_MODULE_TEXT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DModule.h"
#include "frame2D.h"
#include "scrollText2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �e�L�X�g�\���@�\�N���X
class CFrame2DModuleText : public CFrame2DModule
{
public:
	// �R���X�g���N�^
	CFrame2DModuleText(const CFrame2D::EPreset preset);
	CFrame2DModuleText(const VECTOR3& rOffset);

	// �f�X�g���N�^
	~CFrame2DModuleText() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	inline CFrame2DModuleText* GetModuleText() override { return this; }	// �e�L�X�g�\���@�\�擾

	// �����o�֐�
	void ChangeText(const AText& rText);	// �e�L�X�g�ύX
	void SetOffset(const VECTOR3& rOffset);	// �e�L�X�g�I�t�Z�b�g�ݒ�
	inline HRESULT PushFrontString(const std::string& rStr)		{ return m_pText->PushFrontString(rStr); }	// ������̐擪�ǉ� (�}���`�o�C�g������)
	inline HRESULT PushFrontString(const std::wstring& rStr)	{ return m_pText->PushFrontString(rStr); }	// ������̐擪�ǉ� (���C�h������)
	inline HRESULT PushBackString(const std::string& rStr)		{ return m_pText->PushBackString(rStr); }	// ������̍Ō���ǉ� (�}���`�o�C�g������)
	inline HRESULT PushBackString(const std::wstring& rStr)		{ return m_pText->PushBackString(rStr); }	// ������̍Ō���ǉ� (���C�h������)
	inline void DeleteString(const int nStrIdx)			{ m_pText->DeleteString(nStrIdx); }		// ������폜
	inline void DeleteStringAll()						{ m_pText->DeleteStringAll(); }			// ������S�폜
	inline void SetTextEnableDraw(const bool bDraw)		{ m_pText->SetEnableDraw(bDraw); };		// �`��󋵐ݒ�
	inline void SetTextEnableScroll(const bool bScroll)	{ m_pText->SetEnableScroll(bScroll); };	// ��������󋵐ݒ�
	inline bool IsTextScroll() const					{ return m_pText->IsScroll(); }			// ��������󋵎擾
	inline bool IsTextEndScroll() const					{ return m_pText->IsEndScroll(); }		// ��������I���󋵎擾
	inline VECTOR3 GetOffset() const					{ return m_offset; }					// �e�L�X�g�I�t�Z�b�g�擾

private:
	// �����o�֐�
	void SetPositionRelative();	// ���Έʒu�ݒ�

	// �����o�ϐ�
	CScrollText2D* m_pText;	// �e�L�X�g���
	VECTOR3 m_offset;		// �e�L�X�g�I�t�Z�b�g
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DModuleTextSelect.h"

#endif	// _FRAME2D_MODULE_TEXT_H_
