//============================================================
//
//	��������e�L�X�g2D�w�b�_�[ [scrollText2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCROLL_TEXT2D_H_
#define _SCROLL_TEXT2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "text2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// ��������e�L�X�g2D�N���X
class CScrollText2D : public CText2D
{
public:
	// �R���X�g���N�^
	CScrollText2D();

	// �f�X�g���N�^
	~CScrollText2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetEnableDraw(const bool bDraw) override;			// �`��󋵐ݒ�
	HRESULT AddString(const std::wstring& rStr) override;	// ������ǉ�
	void DeleteString(const int nStrID) override;			// ������폜
	void DeleteStringAll(void) override;					// ������S�폜

	// �ÓI�����o�֐�
	static CScrollText2D *Create	// ����
	( // ����
		const std::string &rFilePass,		// �t�H���g�p�X
		const bool bItalic,					// �C�^���b�N
		const D3DXVECTOR3& rPos,			// ���_�ʒu
		const float fNextTime = 0.1f,		// �����\���̑ҋ@����
		const float fCharHeight = 100.0f,	// �����c��
		const float fLineHeight = 100.0f,	// �s�ԏc��
		const CString2D::EAlignX alignX = CString2D::XALIGN_CENTER,	// ���z�u
		const EAlignY alignY = YALIGN_CENTER,						// �c�z�u
		const D3DXVECTOR3& rRot = VEC3_ZERO,						// ���_����
		const D3DXCOLOR& rCol = XCOL_WHITE							// �F
	);

	// �����o�֐�
	void SetNextTime(const float fNextTime)		{ m_fNextTime = fNextTime; }	// �����\���̑ҋ@���Ԑݒ�
	float GetNextTime(void) const				{ return m_fNextTime; }			// �����\���̑ҋ@���Ԏ擾
	void SetEnableScroll(const bool bScroll)	{ m_bScroll = bScroll; }		// ��������󋵐ݒ�
	bool IsScroll(void) const					{ return m_bScroll; }			// ��������󋵎擾

private:
	// �����o�֐�
	void UpdateScroll(const float fDeltaTime);	// ��������X�V

	// �����o�ϐ�
	std::vector<CChar2D*> m_vecChar;	// �S�������
	int m_nNextID;		// ���\�����镶���C���f�b�N�X
	float m_fNextTime;	// ���\���܂ł̑ҋ@����
	float m_fCurTime;	// ���݂̑ҋ@����
	bool m_bScroll;		// ���������
};

#endif	// _SCROLL_TEXT2D_H_
