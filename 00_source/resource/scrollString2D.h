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
#include "sound.h"

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
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader* pShader = nullptr) override;			// �`��
	void SetEnableDraw(const bool bDraw) override;			// �`��󋵐ݒ�
	HRESULT SetString(const std::string& rStr) override;	// ������ݒ� (�}���`�o�C�g������)
	HRESULT SetString(const std::wstring& rStr) override;	// ������ݒ� (���C�h������)

	// �ÓI�����o�֐�
	static CScrollString2D* Create	// ���� (�}���`�o�C�g������)
	( // ����
		const std::string& rFilePath,	// �t�H���g�p�X
		const bool bItalic,				// �C�^���b�N
		const std::string& rStr,		// �w�蕶����
		const VECTOR3& rPos,			// ���_�ʒu
		const float fNextTime = 0.1f,			// �����\���̑ҋ@����
		const float fHeight = 100.0f,			// �����c��
		const EAlignX alignX = XALIGN_CENTER,	// ���z�u
		const VECTOR3& rRot = VEC3_ZERO,		// ���_����
		const COLOR& rCol = color::White()		// �F
	);
	static CScrollString2D* Create	// ���� (���C�h������)
	( // ����
		const std::string& rFilePath,	// �t�H���g�p�X
		const bool bItalic,				// �C�^���b�N
		const std::wstring& rStr,		// �w�蕶����
		const VECTOR3& rPos,			// ���_�ʒu
		const float fNextTime = 0.1f,			// �����\���̑ҋ@����
		const float fHeight = 100.0f,			// �����c��
		const EAlignX alignX = XALIGN_CENTER,	// ���z�u
		const VECTOR3& rRot = VEC3_ZERO,		// ���_����
		const COLOR& rCol = color::White()		// �F
	);

	// �����o�֐�
	bool IsEndScroll() const;	// ��������I���󋵎擾
	inline void SetNextTime(const float fNextTime)			{ m_fNextTime = fNextTime; }		// �����\���̑ҋ@���Ԑݒ�
	inline float GetNextTime() const						{ return m_fNextTime; }				// �����\���̑ҋ@���Ԏ擾
	inline void SetEnableScroll(const bool bScroll)			{ m_bScroll = bScroll; }			// ��������󋵐ݒ�
	inline bool IsScroll() const							{ return m_bScroll; }				// ��������󋵎擾
	inline void SetScrollSE(const CSound::ELabel labelSE)	{ m_labelSE = labelSE; }			// �������莞�̌��ʉ��ݒ�
	inline CSound::ELabel GetScrollSE() const				{ return m_labelSE; }				// �������莞�̌��ʉ��擾
	inline int GetNextCharIdx()								{ return m_nNextIdx; }				// ���̕\�������C���f�b�N�X�擾
	inline CChar2D* GetNextChar2D()							{ return GetChar2D(m_nNextIdx); }	// ���̕\�������擾

private:
	// �����o�֐�
	void UpdateScroll(const float fDeltaTime);	// ��������X�V
	void PlayScrollSE(CChar2D* pChar2D);		// ����������ʉ��̍Đ�

	// �����o�ϐ�
	CSound::ELabel m_labelSE;	// ��������Đ�SE���x��
	int m_nNextIdx;		// ���\�����镶���C���f�b�N�X
	float m_fNextTime;	// ���\���܂ł̑ҋ@����
	float m_fCurTime;	// ���݂̑ҋ@����
	bool m_bScroll;		// ���������
};

#endif	// _SCROLL_STRING2D_H_
