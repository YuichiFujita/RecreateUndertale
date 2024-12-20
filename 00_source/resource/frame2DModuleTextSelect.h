//============================================================
//
//	�I��t���e�L�X�g�\���@�\�w�b�_�[ [frame2DModuleTextSelect.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_MODULE_TEXT_SELECT_H_
#define _FRAME2D_MODULE_TEXT_SELECT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DModuleText.h"
#include "frame2D.h"
#include "scrollText2D.h"

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �I��t���e�L�X�g�\���@�\�N���X
class CFrame2DModuleTextSelect : public CFrame2DModuleText
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
	CFrame2DModuleTextSelect(const CFrame2D::EPreset preset);
	CFrame2DModuleTextSelect(const VECTOR3& rOffset);

	// �f�X�g���N�^
	~CFrame2DModuleTextSelect() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	inline CFrame2DModuleTextSelect* GetModuleTextSelect() override { return this; }	// �I��t���e�L�X�g�\���@�\�擾

	// �����o�֐�
#if 0
	void ChangeText(const AText& rText);	// �e�L�X�g�ύX
	inline HRESULT PushFrontString(const ESelect select, const std::string& rStr)	{ return m_apSelect[select]->PushFrontString(rStr); }	// ������̐擪�ǉ� (�}���`�o�C�g������)
	inline HRESULT PushFrontString(const ESelect select, const std::wstring& rStr)	{ return m_apSelect[select]->PushFrontString(rStr); }	// ������̐擪�ǉ� (���C�h������)
	inline HRESULT PushBackString(const ESelect select, const std::string& rStr)	{ return m_apSelect[select]->PushBackString(rStr); }	// ������̍Ō���ǉ� (�}���`�o�C�g������)
	inline HRESULT PushBackString(const ESelect select, const std::wstring& rStr)	{ return m_apSelect[select]->PushBackString(rStr); }	// ������̍Ō���ǉ� (���C�h������)
	inline void DeleteString(const ESelect select, const int nStrIdx)		{ m_apSelect[select]->DeleteString(nStrIdx); }	// ������폜
	inline void DeleteStringAll(const ESelect select)						{ m_apSelect[select]->DeleteStringAll(); }		// ������S�폜
	inline void SetTextEnableDraw(const ESelect select, const bool bDraw)	{ m_apSelect[select]->SetEnableDraw(bDraw); };	// �`��󋵐ݒ�
	inline bool IsTextScroll(const ESelect select) const					{ return m_apSelect[select]->IsScroll(); }		// ��������󋵎擾
#endif

private:
	// �����o�֐�
	void UpdateSelect();		// �I���X�V
	void UpdateDecide();		// ����X�V
	void SetPositionRelative();	// ���Έʒu�ݒ�

	// �����o�ϐ�
	CScrollText2D* m_apSelect[SELECT_MAX];	// �I�������
	CObject2D* m_pSoul;	// �\�E���J�[�\�����
	int m_nCurSelect;	// ���݂̑I����
};

#endif	// _FRAME2D_MODULE_TEXT_SELECT_H_
