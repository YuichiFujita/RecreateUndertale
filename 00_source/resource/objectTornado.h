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
//	�萔�錾
//************************************************************
namespace tornado
{
	const int	NUM_AROUND	= 3;		// �Q�̎���
	const int	NUM_PTRN	= 16;		// �Q�̕�����
	const float	MOVE_ROT	= 0.3f;		// �����̕ύX��
	const float	THICKNESS	= 25.0f;	// �|���S���̑���
	const float	OUTER_PLUSY	= 35.0f;	// �|���S���O����Y���W���Z��
	const float	SET_WIDTH	= 80.0f;	// �������̉������
	const float	SET_ALPHA	= 0.85f;	// �������̓����x
	const float	ADD_WIDTH	= 7.0f;		// ������̉��Z��
	const float	ADD_HEIGHT	= 7.0f;		// �c����̉��Z��
	const float	SUB_ALPHA	= 0.015f;	// �����x�̌��Z��
	const float	GROW_WIDTH	= 0.0f;		// ������̐�����
	const float	GROW_HEIGHT	= 0.0f;		// �c����̐�����
	const float	GROW_ALPHA	= 0.0f;		// �����x�̐�����
}

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

	// �����\����
	struct STornado
	{
		VECTOR3 pos;		// �ʒu
		VECTOR3 rot;		// ����
		VECTOR3 growRot;	// ��������
		COLOR col;			// �F
		MATRIX mtxWorld;	// ���[���h�}�g���b�N�X
		MATRIX* pMtxParent;	// �e�̃}�g���b�N�X
		float fMoveRot;		// �����̕ύX��
		float fThickness;	// �|���S���̑���
		float fOuterPlusY;	// �|���S���O����Y���W���Z��
		float fSetWidth;	// �������̉������
		float fSetAlpha;	// �������̓����x
		float fAddWidth;	// ������̉��Z��
		float fAddHeight;	// �c����̉��Z��
		float fSubAlpha;	// �����x�̌��Z��
		float fGrowWidth;	// ������̐�����
		float fGrowHeight;	// �c����̐�����
		float fGrowAlpha;	// �����x�̐�����
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	VECTOR3 GetVec3Position() const override	{ return m_tornado.pos; }		// �ʒu�擾
	MATRIX* GetPtrMtxWorld() override			{ return &m_tornado.mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	MATRIX GetMtxWorld() const override			{ return m_tornado.mtxWorld; }	// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectTornado* Create	// ����
	( // ����
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rGrowRot,	// ��������
		const COLOR& rCol,			// �F
		MATRIX* pMtxParent		= nullptr,				// �e�̃}�g���b�N�X
		const int	nNumAround	= tornado::NUM_AROUND,	// �Q�̎���
		const int	nPattern	= tornado::NUM_PTRN,	// �Q�̕�����
		const float	fMoveRot	= tornado::MOVE_ROT,	// �����̕ύX��
		const float	fThickness	= tornado::THICKNESS,	// �|���S���̑���
		const float	fOuterPlusY	= tornado::OUTER_PLUSY,	// �|���S���O����Y���W���Z��
		const float	fSetWidth	= tornado::SET_WIDTH,	// �������̉������
		const float	fSetAlpha	= tornado::SET_ALPHA,	// �������̓����x
		const float	fAddWidth	= tornado::ADD_WIDTH,	// ������̉��Z��
		const float	fAddHeight	= tornado::ADD_HEIGHT,	// �c����̉��Z��
		const float	fSubAlpha	= tornado::SUB_ALPHA,	// �����x�̌��Z��
		const float	fGrowWidth	= tornado::GROW_WIDTH,	// ������̐�����
		const float	fGrowHeight	= tornado::GROW_HEIGHT,	// �c����̐�����
		const float	fGrowAlpha	= tornado::GROW_ALPHA	// �����x�̐�����
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

	CRenderState* GetRenderState();				// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureID);			// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char* pTexturePath);		// �e�N�X�`������ (�p�X)
	void DeleteMatrixParent();					// �e�}�g���b�N�X�폜
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
	int GetTextureIndex() const		{ return m_nTextureID; }			// �e�N�X�`���C���f�b�N�X�擾
	float GetAlpha() const			{ return m_tornado.col.a; }			// �����x�擾
	COLOR GetColor() const			{ return m_tornado.col; }			// �F�擾
	VECTOR3 GetRotationGrow() const	{ return m_tornado.growRot; }		// ���������擾
	float GetThickness() const		{ return m_tornado.fThickness; }	// �|���S���̑����擾
	float GetOuterPlusY() const		{ return m_tornado.fOuterPlusY; }	// �|���S���O����Y���W���Z�ʎ擾
	float GetCreateWidth() const	{ return m_tornado.fSetWidth; }		// �������̉�����ʎ擾
	float GetCreateAlpha() const	{ return m_tornado.fSetAlpha; }		// �������̓����x�擾
	float GetAddWidth() const		{ return m_tornado.fAddWidth; }		// ������̉��Z�ʎ擾
	float GetAddHeight() const		{ return m_tornado.fAddHeight; }	// �c����̉��Z�ʎ擾
	float GetSubAlpha() const		{ return m_tornado.fSubAlpha; }		// �����x�̌��Z�ʎ擾

protected:
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
	STornado m_tornado;	// �����̏��
	int m_nNumVtx;		// �K�v���_��
	int m_nNumAround;	// �Q�̎���
	int m_nPattern;		// �Q�̕�����
	int m_nTextureID;	// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT_TORNADO_H_
