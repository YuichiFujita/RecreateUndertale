//============================================================
//
//	�e�L�X�g��ԃw�b�_�[ [frame2DTextStateText.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_TEXT_H_
#define _FRAME2D_TEXT_STATE_TEXT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextState.h"
#include "frame2D.h"
#include "scrollText2D.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2DTextBuffer;	// �e�L�X�g���ۑ��o�b�t�@�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �e�L�X�g��ԃN���X
class CFrame2DTextStateText : public CFrame2DTextState
{
public:
	// �萔
	static constexpr float CHAR_HEIGHT	= 42.0f;	// �����c��
	static constexpr float LINE_HEIGHT	= 54.0f;	// �s�ԏc��
	static constexpr float WAIT_TIME	= 0.045f;	// �����\���̑ҋ@����
	
	// �R���X�g���N�^
	CFrame2DTextStateText();
	CFrame2DTextStateText(const CFrame2D::EPreset preset);
	CFrame2DTextStateText(const VECTOR3& rOffset);

	// �f�X�g���N�^
	~CFrame2DTextStateText() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void BindTextBuffer(CFrame2DTextBuffer* pBuffer) override;	// �e�L�X�g���ۑ��o�b�t�@����
	inline CFrame2DTextStateText* GetStateText() override { return this; }	// �e�L�X�g��Ԏ擾

	// �����o�֐�
	void ChangeText(const AText& rText);	// �e�L�X�g�ύX
	void SetOffset(const VECTOR3& rOffset);	// �e�L�X�g�I�t�Z�b�g�ݒ�
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

protected:
	// ���z�֐�
	virtual VECTOR3 GetPresetOffset(const CFrame2D::EPreset preset);	// �v���Z�b�g�I�t�Z�b�g�擾
	virtual void SetPositionRelative();	// ���Έʒu�ݒ�

	// �����o�֐�
	inline void SetNextTextKey(const std::string& rKey) { m_sNextTextKey = rKey; }	// ���e�L�X�g�̌����L�[�ݒ�

private:
	// �����o�ϐ�
	std::string m_sNextTextKey;	// ���e�L�X�g�̌����L�[
	CScrollText2D* m_pText;		// �e�L�X�g���
	VECTOR3 m_offset;			// �e�L�X�g�I�t�Z�b�g
	// TODO�F������preset�ۑ���u�������Ȃ������B�R���X�g���N�^���̕ۑ��ɂ����g��Ȃ��悤�ɁAconst�w��q�Œu���Ƃ���
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateSelect.h"
#include "frame2DTextStateFaceText.h"
#include "frame2DTextStateItem.h"

#endif	// _FRAME2D_TEXT_STATE_TEXT_H_
