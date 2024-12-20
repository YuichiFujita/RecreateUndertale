//============================================================
//
//	�e�L�X�g2D�w�b�_�[ [text2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TEXT2D_H_
#define _TEXT2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "string2D.h"

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
class CFontChar;	// �t�H���g�����N���X

//************************************************************
//	�N���X��`
//************************************************************
// �e�L�X�g2D�N���X
class CText2D : public CObject
{
public:
	// �R���X�g���N�^
	CText2D();

	// �f�X�g���N�^
	~CText2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	inline VECTOR3 GetVec3Position() const override { return m_pos; }	// �ʒu�擾
	inline VECTOR3 GetVec3Rotation() const override { return m_rot; }	// �����擾

	// �ÓI�����o�֐�
	static CText2D* Create	// ����
	( // ����
		const std::string& rFilePath,			// �t�H���g�p�X
		const bool bItalic,						// �C�^���b�N
		const VECTOR3& rPos,					// ���_�ʒu
		const float fCharHeight = 100.0f,		// �����c��
		const float fLineHeight = 100.0f,		// �s�ԏc��
		const EAlignX alignX = XALIGN_CENTER,	// ���z�u
		const EAlignY alignY = YALIGN_CENTER,	// �c�z�u
		const VECTOR3& rRot = VEC3_ZERO,		// ���_����
		const COLOR& rCol = color::White()		// �F
	);

	// ���z�֐�
	virtual HRESULT PushFrontString(const std::string& rStr);	// ������̐擪�ǉ� (�}���`�o�C�g������)
	virtual HRESULT PushFrontString(const std::wstring& rStr);	// ������̐擪�ǉ� (���C�h������)
	virtual HRESULT PushBackString(const std::string& rStr);	// ������̍Ō���ǉ� (�}���`�o�C�g������)
	virtual HRESULT PushBackString(const std::wstring& rStr);	// ������̍Ō���ǉ� (���C�h������)
	virtual void DeleteString(const int nStrIdx);	// ������폜
	virtual void DeleteStringAll();					// ������S�폜

	// �����o�֐�
	void SetFont	// �t�H���g�̐ݒ�
	( // ����
		const std::string& rFilePath,	// �t�H���g�p�X
		const bool bItalic = false		// �C�^���b�N
	);
	void SetAlpha(const float fAlpha);					// �����x�ݒ�
	void SetColor(const COLOR& rCol);					// �F�ݒ�
	void SetCharHeight(const float fHeight);			// �����̏c���ݒ�
	void SetLineHeight(const float fHeight);			// �s�Ԃ̏c���ݒ�
	void SetAlignX(const EAlignX align);				// ���z�u�ݒ�
	void SetAlignY(const EAlignY align);				// �c�z�u�ݒ�
	float GetTextWidth() const;							// �e�L�X�g�̉����擾
	float GetTextHeight() const;						// �e�L�X�g�̏c���擾
	CString2D* GetString2D(const int nStrIdx) const;	// ������̎擾
	inline float GetAlpha() const		{ return m_col.a; }			// �����x�擾
	inline COLOR GetColor() const		{ return m_col; }			// �F�擾
	inline float GetCharHeight() const	{ return m_fCharHeight; }	// �����̏c���擾
	inline float GetLineHeight() const	{ return m_fLineHeight; }	// �s�Ԃ̏c���擾
	inline EAlignX GetAlignX() const	{ return m_alignX; }		// ���z�u�擾
	inline EAlignY GetAlignY() const	{ return m_alignY; }		// �c�z�u�擾
	inline int GetNumString() const		{ return (int)m_listString.size(); }	// �����񐔎擾

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	CString2D* CreateString2D(const std::wstring& rStr);	// ������̐���
	void SetPositionRelative();	// ���Έʒu�ݒ�

	// �����o�ϐ�
	std::list<CString2D*> m_listString;	// �����񃊃X�g
	CFontChar* m_pFontChar;	// �t�H���g����
	VECTOR3 m_pos;			// �ʒu
	VECTOR3 m_rot;			// ����
	COLOR m_col;			// �F
	EAlignX m_alignX;		// ���z�u
	EAlignY m_alignY;		// �c�z�u
	float m_fCharHeight;	// �����̏c��
	float m_fLineHeight;	// �����̍s��
};

#endif	// _TEXT2D_H_
