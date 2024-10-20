//============================================================
//
//	�t���[���e�L�X�g2D�w�b�_�[ [frameText2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME_TEXT2D_H_
#define _FRAME_TEXT2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2D.h"
#include "scrollText2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �t���[���e�L�X�g2D�N���X
class CFrameText2D : public CFrame2D
{
public:
	// �R���X�g���N�^
	CFrameText2D();

	// �f�X�g���N�^
	~CFrameText2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CFrameText2D *Create	// ����
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const VECTOR3& rSize	// �傫��
	);

	// �����o�֐�
	void ChangeText(const AText& rText);	// �e�L�X�g�ύX
	HRESULT PushFrontString(const std::string& rStr)	{ return m_pText->PushFrontString(rStr); }	// ������̐擪�ǉ� (�}���`�o�C�g������)
	HRESULT PushFrontString(const std::wstring& rStr)	{ return m_pText->PushFrontString(rStr); }	// ������̐擪�ǉ� (���C�h������)
	HRESULT PushBackString(const std::string& rStr)		{ return m_pText->PushBackString(rStr); }	// ������̍Ō���ǉ� (�}���`�o�C�g������)
	HRESULT PushBackString(const std::wstring& rStr)	{ return m_pText->PushBackString(rStr); }	// ������̍Ō���ǉ� (���C�h������)
	void DeleteString(const int nStrID)			{ m_pText->DeleteString(nStrID); }	// ������폜
	void DeleteStringAll(void)					{ m_pText->DeleteStringAll(); }		// ������S�폜
	void SetTextEnableDraw(const bool bDraw)	{ m_pText->SetEnableDraw(bDraw); };	// �`��󋵐ݒ�
	bool IsTextScroll(void) const				{ return m_pText->IsScroll(); }		// ��������󋵎擾

private:
	// �����o�ϐ�
	CScrollText2D *m_pText;	// �e�L�X�g���
};

#endif	// _FRAME_TEXT2D_H_
