//============================================================
//
//	�������蕶����2D�w�b�_�[ [scrollString2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCROLL_STRING2D_H_
#define _SCROLL_STRING2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "string2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �������蕶����2D�N���X
class CScrollString2D : public CString2D
{
public:
	// �R���X�g���N�^
	CScrollString2D();

	// �f�X�g���N�^
	~CScrollString2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetEnableDraw(const bool bDraw) override;			// �`��󋵐ݒ�
	HRESULT SetString(const std::wstring& rStr) override;	// ������ݒ�

	// �ÓI�����o�֐�
	static CScrollString2D *Create	// ����
	( // ����
		const std::string &rFilePass,	// �t�H���g�p�X
		const bool bItalic,				// �C�^���b�N
		const std::wstring &rStr,		// �w�蕶����
		const D3DXVECTOR3 &rPos,		// ���_�ʒu
		const float fNextTime = 0.1f,			// �����\���̑ҋ@����
		const float fHeight = 100.0f,			// �����c��
		const EAlignX alignX = XALIGN_CENTER,	// ���z�u
		const D3DXVECTOR3& rRot = VEC3_ZERO,	// ���_����
		const D3DXCOLOR& rCol = XCOL_WHITE		// �F
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
	int m_nNextID;		// ���\�����镶���C���f�b�N�X
	float m_fNextTime;	// ���\���܂ł̑ҋ@����
	float m_fCurTime;	// ���݂̑ҋ@����
	bool m_bScroll;		// ���������
};

#endif	// _SCROLL_STRING2D_H_
