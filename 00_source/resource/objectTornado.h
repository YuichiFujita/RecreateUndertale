//============================================================
//
//	�I�u�W�F�N�g�����w�b�_�[ [objectTornado.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_TORNADO_H_
#define _OBJECT_TORNADO_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�����N���X
class CObjectTornado : public CObject
{
public:
	// �R���X�g���N�^
	CObjectTornado();

	// �f�X�g���N�^
	~CObjectTornado() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	inline VECTOR3 GetVec3Position() const override	{ return m_pos; }		// �ʒu�擾
	inline MATRIX* GetPtrMtxWorld() override		{ return &m_mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	inline MATRIX GetMtxWorld() const override		{ return m_mtxWorld; }	// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectTornado* Create	// ����
	( // ����
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rGrowRot,	// ��������
		const COLOR& rCol,			// �F
		MATRIX* pMtxParent		= nullptr,	// �e�̃}�g���b�N�X
		const int	nNumAround	= 3,		// �Q�̎���
		const int	nPattern	= 16,		// �Q�̕�����
		const float	fMoveRot	= 0.3f,		// �����̕ύX��
		const float	fThickness	= 25.0f,	// �|���S���̑���
		const float	fOuterPlusY	= 35.0f,	// �|���S���O����Y���W���Z��
		const float	fSetWidth	= 80.0f,	// �������̉������
		const float	fSetAlpha	= 0.85f,	// �������̓����x
		const float	fAddWidth	= 7.0f,		// ������̉��Z��
		const float	fAddHeight	= 7.0f,		// �c����̉��Z��
		const float	fSubAlpha	= 0.015f,	// �����x�̌��Z��
		const float	fGrowWidth	= 0.0f,		// ������̐�����
		const float	fGrowHeight	= 0.0f,		// �c����̐�����
		const float	fGrowAlpha	= 0.0f		// �����x�̐�����
	);

	// �����o�֐�
	void SetGrow	// �����ݒ�
	( // ����
		const float fMoveRot,		// �����̕ύX��
		const float fGrowWidth,		// ������̐�����
		const float fGrowHeight,	// �c����̐�����
		const float fGrowAlpha		// �����x�̐�����
	);
	HRESULT SetVortex	// �Q�ݒ�
	( // ����
		const int nNumAround,	// �Q�̎���
		const int nPattern		// �Q�̕�����
	);

	CRenderState* GetRenderState();					// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureIdx);		// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char* pTexturePath);		// �e�N�X�`������ (�p�X)
	void DeleteMatrixParent();						// �e�}�g���b�N�X�폜
	void SetMatrixParent(MATRIX* pMtxParent);		// �e�}�g���b�N�X�ݒ�
	void SetAlpha(const float fAlpha);				// �����x�ݒ�
	void SetColor(const COLOR& rCol);				// �F�ݒ�
	void SetRotationGrow(const VECTOR3& rRot);		// ���������ݒ�
	void SetThickness(const float fThickness);		// �|���S���̑����ݒ�
	void SetOuterPlusY(const float fOuterPlusY);	// �|���S���O����Y���W���Z�ʐݒ�
	void SetCreateWidth(const float fSetWidth);		// �������̉�����ʐݒ�
	void SetCreateAlpha(const float fSetAlpha);		// �������̓����x�ݒ�
	void SetAddWidth(const float fAddWidth);		// ������̉��Z�ʐݒ�
	void SetAddHeight(const float fAddHeight);		// �c����̉��Z�ʐݒ�
	void SetSubAlpha(const float fSubAlpha);		// �����x�̌��Z�ʐݒ�
	inline int GetTextureIndex() const		{ return m_nTextureIdx; }	// �e�N�X�`���C���f�b�N�X�擾
	inline float GetAlpha() const			{ return m_col.a; }			// �����x�擾
	inline COLOR GetColor() const			{ return m_col; }			// �F�擾
	inline VECTOR3 GetRotationGrow() const	{ return m_growRot; }		// ���������擾
	inline float GetThickness() const		{ return m_fThickness; }	// �|���S���̑����擾
	inline float GetOuterPlusY() const		{ return m_fOuterPlusY; }	// �|���S���O����Y���W���Z�ʎ擾
	inline float GetCreateWidth() const		{ return m_fSetWidth; }		// �������̉�����ʎ擾
	inline float GetCreateAlpha() const		{ return m_fSetAlpha; }		// �������̓����x�擾
	inline float GetAddWidth() const		{ return m_fAddWidth; }		// ������̉��Z�ʎ擾
	inline float GetAddHeight() const		{ return m_fAddHeight; }	// �c����̉��Z�ʎ擾
	inline float GetSubAlpha() const		{ return m_fSubAlpha; }		// �����x�̌��Z�ʎ擾

protected:
	// ���z�֐�
	virtual void CalcDrawMatrix();	// �`��}�g���b�N�X�v�Z

	// �����o�֐�
	void SetVtx();	// ���_���̐ݒ�

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void DrawNormal();	// �ʏ�`��
	void DrawShader(CShader* pShader);	// �V�F�[�_�[�`��

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	CRenderState* m_pRenderState;		// �����_�[�X�e�[�g�̏��
	MATRIX* m_pMtxParent;	// �e�̃}�g���b�N�X
	MATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	VECTOR3 m_pos;			// �ʒu
	VECTOR3 m_rot;			// ����
	VECTOR3 m_growRot;		// ��������
	COLOR m_col;			// �F
	float m_fMoveRot;		// �����̕ύX��
	float m_fThickness;		// �|���S���̑���
	float m_fOuterPlusY;	// �|���S���O����Y���W���Z��
	float m_fSetWidth;		// �������̉������
	float m_fSetAlpha;		// �������̓����x
	float m_fAddWidth;		// ������̉��Z��
	float m_fAddHeight;		// �c����̉��Z��
	float m_fSubAlpha;		// �����x�̌��Z��
	float m_fGrowWidth;		// ������̐�����
	float m_fGrowHeight;	// �c����̐�����
	float m_fGrowAlpha;		// �����x�̐�����
	int m_nNumVtx;			// �K�v���_��
	int m_nNumAround;		// �Q�̎���
	int m_nPattern;			// �Q�̕�����
	int m_nTextureIdx;		// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT_TORNADO_H_
