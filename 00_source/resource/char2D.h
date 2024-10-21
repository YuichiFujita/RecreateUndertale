//============================================================
//
//	����2D�w�b�_�[ [char2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _CHAR2D_H_
#define _CHAR2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object2D.h"
#include "fontChar.h"

//************************************************************
//	�N���X��`
//************************************************************
// ����2D�N���X
class CChar2D : public CObject2D
{
public:
	// �R���X�g���N�^
	CChar2D();

	// �f�X�g���N�^
	~CChar2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Size(const VECTOR3& rSize) override;	// �傫���ݒ�

	// �ÓI�����o�֐�
	static CChar2D* Create	// ���� (�}���`�o�C�g����)
	( // ����
		const std::string& rFilePath,		// �t�H���g�p�X
		const bool bItalic,					// �C�^���b�N
		const std::string& rChar,			// �w�蕶��
		const VECTOR3& rPos = VEC3_ZERO,	// �ʒu
		const float fHeight = 100.0f,		// �c��
		const VECTOR3& rRot = VEC3_ZERO,	// ����
		const COLOR& rCol = color::White()	// �F
	);
	static CChar2D* Create	// ���� (���C�h����)
	( // ����
		const std::string& rFilePath,		// �t�H���g�p�X
		const bool bItalic,					// �C�^���b�N
		const wchar_t wcChar,				// �w�蕶��
		const VECTOR3& rPos = VEC3_ZERO,	// �ʒu
		const float fHeight = 100.0f,		// �c��
		const VECTOR3& rRot = VEC3_ZERO,	// ����
		const COLOR& rCol = color::White()	// �F
	);

	// �����o�֐�
	void SetFont	// �t�H���g�̐ݒ�
	( // ����
		const std::string& rFilePath,	// �t�H���g�p�X
		const bool bItalic = false		// �C�^���b�N
	);
	void SetChar(const std::string& rChar);		// �����̐ݒ� (�}���`�o�C�g����)
	void SetChar(const wchar_t wcChar);			// �����̐ݒ� (���C�h����)
	void SetCharHeight(const float fHeight);	// �����̏c���ݒ�
	VECTOR2 GetOffsetBlackBoxLU();				// �u���b�N�{�b�N�X�̍���I�t�Z�b�g�擾
	VECTOR2 GetOffsetBlackBoxRD();				// �u���b�N�{�b�N�X�̉E���I�t�Z�b�g�擾

	inline bool IsTexEmpty() const		{ return m_bTexEmpty; }	// �e�N�X�`�������t���O�擾
	inline wchar_t GetWideChar() const	{ return m_wcChar; }	// �����擾 (���C�h����)
	std::string GetChar() const;	// �����擾 (�}���`�o�C�g����)
	float GetOffsetOrigin();		// ���_�̃I�t�Z�b�g�擾
	float GetNext();				// ���̕����܂ł̋����擾

private:
	// �����o�ϐ�
	CFontChar* m_pFontChar;	// �t�H���g����
	wchar_t m_wcChar;		// �w�蕶��
	float m_fCharHeight;	// �����̏c��
	float m_fSizeRate;		// �c���̊���
	float m_fAbsOriginX;	// X���_�I�t�Z�b�g�̐�Βl
	bool m_bTexEmpty;		// �e�N�X�`�������t���O
};

#endif	// _CHAR2D_H_
