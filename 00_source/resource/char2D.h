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
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetVec3Sizing(const D3DXVECTOR3& rSize) override;	// �傫���ݒ�

	// �ÓI�����o�֐�
	static CChar2D *Create	// ����
	( // ����
		const std::string &rFilePass,	// �t�H���g�p�X
		const bool bItalic,				// �C�^���b�N
		const wchar_t wcChar,			// �w�蕶��
		const D3DXVECTOR3& rPos = VEC3_ZERO,	// �ʒu
		const float fHeight = 100.0f,			// �c��
		const D3DXVECTOR3& rRot = VEC3_ZERO,	// ����
		const D3DXCOLOR& rCol = XCOL_WHITE		// �F
	);

	// �����o�֐�
	void SetFont	// �t�H���g�̐ݒ�
	( // ����
		const std::string &rFilePass,	// �t�H���g�p�X
		const bool bItalic = false		// �C�^���b�N
	);
	void SetChar(const wchar_t wcChar);			// �����̐ݒ�
	void SetCharHeight(const float fHeight);	// �����̏c���ݒ�
	D3DXVECTOR2 GetOffsetBlackBoxLU(void);		// �u���b�N�{�b�N�X�̍���I�t�Z�b�g�擾
	D3DXVECTOR2 GetOffsetBlackBoxRD(void);		// �u���b�N�{�b�N�X�̉E���I�t�Z�b�g�擾
	float GetOffsetOrigin(void);				// ���_�̃I�t�Z�b�g�擾
	float GetNext(void);						// ���̕����܂ł̋����擾

private:
	// �����o�ϐ�
	CFontChar *m_pFontChar;	// �t�H���g����
	wchar_t m_wcChar;		// �w�蕶��
	float m_fCharHeight;	// �����̏c��
	float m_fSizeRate;		// �c���̊���
	float m_fAbsOriginX;	// X���_�I�t�Z�b�g�̐�Βl
};

#endif	// _CHAR2D_H_
