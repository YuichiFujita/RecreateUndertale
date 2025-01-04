//============================================================
//
//	�I��t���e�L�X�g��ԃw�b�_�[ [frame2DTextStateSelect.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_SELECT_H_
#define _FRAME2D_TEXT_STATE_SELECT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateText.h"
#include "frame2D.h"
#include "scrollText2D.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2DTextBuffer;	// �e�L�X�g���ۑ��o�b�t�@�N���X
class CObject2D;			// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �I��t���e�L�X�g��ԃN���X
class CFrame2DTextStateSelect : public CFrame2DTextStateText
{
public:
	// �I���
	enum ESelect
	{
		SELECT_LEFT = 0,	// ���I��
		SELECT_RIGHT,		// �E�I��
		SELECT_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CFrame2DTextStateSelect(const CFrame2D::EPreset preset);
	CFrame2DTextStateSelect(const VECTOR3& rOffset);

	// �f�X�g���N�^
	~CFrame2DTextStateSelect() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void BindTextBuffer(CFrame2DTextBuffer* pBuffer) override;	// �e�L�X�g���ۑ��o�b�t�@����
	inline CFrame2DTextStateSelect* GetStateSelect() override { return this; }	// �I��t���e�L�X�g��Ԏ擾

	// �����o�֐�
	//void ChangeText(const ESelect select, const AText& rText);	// �e�L�X�g�ύX	// TODO
	inline HRESULT PushFrontString(const ESelect select, const std::string& rStr)	{ return m_apSelect[select]->PushFrontString(rStr); }	// ������̐擪�ǉ� (�}���`�o�C�g������)
	inline HRESULT PushFrontString(const ESelect select, const std::wstring& rStr)	{ return m_apSelect[select]->PushFrontString(rStr); }	// ������̐擪�ǉ� (���C�h������)
	inline HRESULT PushBackString(const ESelect select, const std::string& rStr)	{ return m_apSelect[select]->PushBackString(rStr); }	// ������̍Ō���ǉ� (�}���`�o�C�g������)
	inline HRESULT PushBackString(const ESelect select, const std::wstring& rStr)	{ return m_apSelect[select]->PushBackString(rStr); }	// ������̍Ō���ǉ� (���C�h������)
	inline void DeleteString(const ESelect select, const int nStrIdx)				{ m_apSelect[select]->DeleteString(nStrIdx); }			// ������폜
	inline void DeleteStringAll(const ESelect select)								{ m_apSelect[select]->DeleteStringAll(); }				// ������S�폜
	inline void SetTextEnableDraw(const ESelect select, const bool bDraw)			{ m_apSelect[select]->SetEnableDraw(bDraw); };			// �e�L�X�g�`��󋵐ݒ�
	inline void SetTextEnableScroll(const ESelect select, const bool bScroll)		{ m_apSelect[select]->SetEnableScroll(bScroll); };		// �e�L�X�g��������󋵐ݒ�
	inline bool IsTextScroll(const ESelect select) const							{ return m_apSelect[select]->IsScroll(); }				// �e�L�X�g��������󋵎擾
	inline bool IsTextEndScroll(const ESelect select) const							{ return m_apSelect[select]->IsEndScroll(); }			// �e�L�X�g��������I���󋵎擾

	// �I�[�o�[���[�h�֐��Č��J
	using CFrame2DTextStateText::ChangeText;			// �e�L�X�g�ύX
	using CFrame2DTextStateText::PushFrontString;		// ������̐擪�ǉ�
	using CFrame2DTextStateText::PushBackString;		// ������̍Ō���ǉ�
	using CFrame2DTextStateText::DeleteString;			// ������폜
	using CFrame2DTextStateText::DeleteStringAll;		// ������S�폜
	using CFrame2DTextStateText::SetTextEnableDraw;		// �e�L�X�g�`��󋵐ݒ�
	using CFrame2DTextStateText::SetTextEnableScroll;	// �e�L�X�g��������󋵐ݒ�
	using CFrame2DTextStateText::IsTextScroll;			// �e�L�X�g��������󋵎擾
	using CFrame2DTextStateText::IsTextEndScroll;		// �e�L�X�g��������I���󋵎擾

private:
	// �����o�֐�
	void UpdateSelect();		// �I���X�V
	void UpdateDecide();		// ����X�V
	void SetPositionRelative();	// ���Έʒu�ݒ�

	// �����o�ϐ�
	std::string m_aNextTextKey[SELECT_MAX];	// ���e�L�X�g�̌����L�[
	CScrollText2D* m_apSelect[SELECT_MAX];	// �I�������
	CObject2D* m_pSoul;	// �\�E���J�[�\�����
	int m_nCurSelect;	// ���݂̑I����
};

#endif	// _FRAME2D_TEXT_STATE_SELECT_H_
