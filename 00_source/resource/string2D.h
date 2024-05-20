//============================================================
//
//	������2D�w�b�_�[ [string2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _STRING2D_H_
#define _STRING2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�O���錾
//************************************************************
class CFontChar;	// �t�H���g�����N���X
class CChar2D;		// ����2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ������2D�N���X
class CString2D : public CObject
{
public:
	// ���z�u��
	enum EAlignX
	{
		XALIGN_LEFT = 0,	// ������
		XALIGN_CENTER,		// ��������
		XALIGN_RIGHT,		// �E����
		XALIGN_MAX,			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CString2D();

	// �f�X�g���N�^
	~CString2D() override;

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
	static CString2D *Create	// ����
	( // ����
		const std::string &rFilePass,	// �t�H���g�p�X
		const bool bItalic,				// �C�^���b�N
		const std::wstring &rStr,		// �w�蕶����
		const D3DXVECTOR3 &rPos,		// ���_�ʒu
		const float fHeight = 100.0f,			// �����c��
		const EAlignX alignX = XALIGN_CENTER,	// ���z�u
		const D3DXVECTOR3& rRot = VEC3_ZERO,	// ���_����
		const D3DXCOLOR& rCol = XCOL_WHITE		// �F
	);

	// ���z�֐�
	virtual HRESULT SetString(const std::wstring& rStr);	// ������̐ݒ�

	// �����o�֐�
	void SetFont	// �t�H���g�̐ݒ�
	( // ����
		const std::string &rFilePass,	// �t�H���g�p�X
		const bool bItalic = false		// �C�^���b�N
	);
	void SetColor(const D3DXCOLOR& rCol);			// �F�ݒ�
	void SetCharHeight(const float fHeight);		// �����̏c���ݒ�
	void SetAlignX(const EAlignX align);			// ���z�u�ݒ�
	float GetStrWidth(void) const;					// ������̉����擾
	CChar2D *GetChar2D(const int nCharID) const;	// �����̎擾
	D3DXCOLOR GetColor(void) const	{ return m_col; }				// �F�擾
	float GetCharHeight(void) const	{ return m_fCharHeight; }		// �����̏c���擾
	EAlignX GetAlignX(void) const	{ return m_alignX; }			// ���z�u�擾
	int GetNumChar(void) const		{ return (int)m_wsStr.size(); }	// �������擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetPositionRelative(void);	// ���Έʒu�ݒ�

	// �����o�ϐ�
	CChar2D **m_ppChar;		// �����|���S���̏��
	CFontChar *m_pFontChar;	// �t�H���g����
	std::wstring m_wsStr;	// �w�蕶����
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXCOLOR m_col;		// �F
	EAlignX m_alignX;		// ���z�u
	float m_fCharHeight;	// �����̏c��
};

#endif	// _STRING2D_H_
