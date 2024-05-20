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
	// �c�z�u��
	enum EAlignY
	{
		YALIGN_TOP = 0,	// �㑵��
		YALIGN_CENTER,	// ��������
		YALIGN_BOTTOM,	// ������
		YALIGN_MAX,		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CText2D();

	// �f�X�g���N�^
	~CText2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetEnableDraw(const bool bDraw) override;			// �`��󋵐ݒ�
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override { return m_pos; }	// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override { return m_rot; }	// �����擾

	// �ÓI�����o�֐�
	static CText2D *Create	// ����
	( // ����
		const std::string &rFilePass,		// �t�H���g�p�X
		const bool bItalic,					// �C�^���b�N
		const D3DXVECTOR3& rPos,			// ���_�ʒu
		const float fCharHeight = 100.0f,	// �����c��
		const float fLineHeight = 100.0f,	// �s�ԏc��
		const CString2D::EAlignX alignX = CString2D::XALIGN_CENTER,	// ���z�u
		const EAlignY alignY = YALIGN_CENTER,						// �c�z�u
		const D3DXVECTOR3& rRot = VEC3_ZERO,						// ���_����
		const D3DXCOLOR& rCol = XCOL_WHITE							// �F
	);

	// ���z�֐�
	virtual HRESULT AddString(const std::wstring& rStr);	// ������̒ǉ�
	virtual void DeleteString(const int nStrID);			// ������폜
	virtual void DeleteStringAll(void);						// ������S�폜

	// �����o�֐�
	void SetFont	// �t�H���g�̐ݒ�
	( // ����
		const std::string &rFilePass,	// �t�H���g�p�X
		const bool bItalic = false		// �C�^���b�N
	);
	void SetColor(const D3DXCOLOR& rCol);			// �F�ݒ�
	void SetCharHeight(const float fHeight);		// �����̏c���ݒ�
	void SetLineHeight(const float fHeight);		// �s�Ԃ̏c���ݒ�
	void SetAlignX(const CString2D::EAlignX align);	// ���z�u�ݒ�
	void SetAlignY(const EAlignY align);			// �c�z�u�ݒ�
	float GetTextHeight(void) const;				// �e�L�X�g�̏c���擾
	CString2D *GetString2D(const int nStrID) const;	// ������̎擾
	D3DXCOLOR GetColor(void) const				{ return m_col; }			// �F�擾
	float GetCharHeight(void) const				{ return m_fCharHeight; }	// �����̏c���擾
	float GetLineHeight(void) const				{ return m_fLineHeight; }	// �s�Ԃ̏c���擾
	CString2D::EAlignX GetAlignX(void) const	{ return m_alignX; }		// ���z�u�擾
	EAlignY GetAlignY(void) const				{ return m_alignY; }		// �c�z�u�擾
	int GetNumString(void) const	{ return (int)m_listString.size(); }	// �����񐔎擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetPositionRelative(void);	// ���Έʒu�ݒ�

	// �����o�ϐ�
	std::list<CString2D*> m_listString;	// �����񃊃X�g
	CFontChar *m_pFontChar;				// �t�H���g����
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXCOLOR m_col;					// �F
	CString2D::EAlignX m_alignX;		// ���z�u
	EAlignY m_alignY;					// �c�z�u
	float m_fCharHeight;				// �����̏c��
	float m_fLineHeight;				// �����̍s��
};

#endif	// _TEXT2D_H_
