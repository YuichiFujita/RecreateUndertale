//============================================================
//
//	�I�u�W�F�N�g2D�w�b�_�[ [object2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g2D�N���X
class CObject2D : public CObject
{
public:
	// �R���X�g���N�^
	explicit CObject2D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_2D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObject2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Size(const VECTOR3& rSize) override;	// �傫���ݒ�
	VECTOR3 GetVec3Position(void) const override	{ return m_pos; }	// �ʒu�擾
	VECTOR3 GetVec3Rotation(void) const override	{ return m_rot; }	// �����擾
	VECTOR3 GetVec3Size(void) const override		{ return m_size; }	// �傫���擾

	// �����o�֐�
	CRenderState* GetRenderState(void);			// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureID);		// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char* pTexturePath);	// �e�N�X�`������ (�p�X)
	void SetAlpha(const float fAlpha);			// �����x�ݒ�
	void SetColor(const COLOR& rCol);			// �F�ݒ�
	int GetTextureIndex(void) const	{ return m_nTextureID; }	// �e�N�X�`���C���f�b�N�X�擾
	float GetAlpha(void) const		{ return m_col.a; }			// �����x�擾
	COLOR GetColor(void) const		{ return m_col; }			// �F�擾

	// �ÓI�����o�֐�
	static CObject2D* Create	// ����
	( // ����
		const VECTOR3& rPos,				// �ʒu
		const VECTOR3& rSize = VEC3_ONE,	// �傫��
		const VECTOR3& rRot = VEC3_ZERO,	// ����
		const COLOR& rCol = color::White()	// �F
	);

protected:
	// �����o�֐�
	void SetVtx(void);	// ���_���̐ݒ�
	void SetAnimTex		// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	( // ����
		const int nPattern,		// �A�j���[�V�����p�^�[��
		const int nWidthPtrn,	// �e�N�X�`���̉��̕�����
		const int nHeightPtrn	// �e�N�X�`���̏c�̕�����
	);
	void SetScrollTex	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	( // ����
		const float fTexU,		// �e�N�X�`���̉����W�̊J�n�ʒu
		const float fTexV,		// �e�N�X�`���̏c���W�̊J�n�ʒu
		const float fOffsetU,	// �e�N�X�`���̉����W�̃I�t�Z�b�g�ʒu
		const float fOffsetV	// �e�N�X�`���̏c���W�̃I�t�Z�b�g�ʒu
	);

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	CRenderState* m_pRenderState;		// �����_�[�X�e�[�g�̏��
	VECTOR3	m_pos;			// �ʒu
	VECTOR3	m_rot;			// ����
	VECTOR3	m_size;			// �傫��
	COLOR	m_col;			// �F
	float	m_fAngle;		// �Ίp���̊p�x
	float	m_fLength;		// �Ίp���̒���
	int		m_nTextureID;	// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT2D_H_
