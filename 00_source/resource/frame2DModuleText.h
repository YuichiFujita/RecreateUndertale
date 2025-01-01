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
	HRESULT BindText(const std::string& rPath, const std::string& rBoxKey, const std::string& rTextKey);	// �e�L�X�g����
	inline HRESULT PushFrontString(const std::string& rStr)		{ return m_pText->PushFrontString(rStr); }	// ������̐擪�ǉ� (�}���`�o�C�g������)
	inline HRESULT PushFrontString(const std::wstring& rStr)	{ return m_pText->PushFrontString(rStr); }	// ������̐擪�ǉ� (���C�h������)
	inline HRESULT PushBackString(const std::string& rStr)		{ return m_pText->PushBackString(rStr); }	// ������̍Ō���ǉ� (�}���`�o�C�g������)
	inline HRESULT PushBackString(const std::wstring& rStr)		{ return m_pText->PushBackString(rStr); }	// ������̍Ō���ǉ� (���C�h������)
	inline void DeleteString(const int nStrIdx)			{ m_pText->DeleteString(nStrIdx); }		// ������폜
	inline void DeleteStringAll()						{ m_pText->DeleteStringAll(); }			// ������S�폜
	inline void SetTextEnableDraw(const bool bDraw)		{ m_pText->SetEnableDraw(bDraw); };		// �e�L�X�g�`��󋵐ݒ�
	inline void SetTextEnableScroll(const bool bScroll)	{ m_pText->SetEnableScroll(bScroll); };	// �e�L�X�g��������󋵐ݒ�
	inline bool IsTextScroll() const					{ return m_pText->IsScroll(); }			// �e�L�X�g��������󋵎擾
	inline bool IsTextEndScroll() const					{ return m_pText->IsEndScroll(); }		// �e�L�X�g��������I���󋵎擾
	inline VECTOR3 GetOffset() const					{ return m_offset; }					// �e�L�X�g�I�t�Z�b�g�擾

private:
	// �����o�֐�
	void SetPositionRelative();	// ���Έʒu�ݒ�
	bool IsNextTextBox(std::string* pPath, std::string* pBoxKey);	// ���e�L�X�g�{�b�N�X�����邩�̊m�F
	void LoadString(std::ifstream* pFile, AText* pText);			// ������Ǎ�
	void LoadText(std::ifstream* pFile, AText* pText, const std::string& rTextKey);	// �e�L�X�g�Ǎ�
	AText LoadTextBox(const std::string& rPath, const std::string& rBoxKey, const std::string& rTextKey);	// �e�L�X�g�{�b�N�X�Ǎ�

	// �����o�ϐ�
	CScrollText2D* m_pText;		// �e�L�X�g���
	VECTOR3 m_offset;			// �e�L�X�g�I�t�Z�b�g
	std::string m_sNextPath;	// ���e�L�X�g�{�b�N�X�̕ۑ��p�X
	std::string m_sNextBoxKey;	// ���e�L�X�g�{�b�N�X�̌����L�[
	std::string m_sNextTextKey;	// ���e�L�X�g�̌����L�[
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DModuleTextSelect.h"

#endif	// _FRAME2D_MODULE_TEXT_H_
