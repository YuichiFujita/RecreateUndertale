//============================================================
//
//	�I�u�W�F�N�g���b�V���T�[�N���w�b�_�[ [objectMeshCircle.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_MESHCIRCLE_H_
#define _OBJECT_MESHCIRCLE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g���b�V���T�[�N���N���X
class CObjectMeshCircle : public CObject
{
public:
	// �R���X�g���N�^
	explicit CObjectMeshCircle(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshCircle() override;

	// ���b�V���T�[�N���\����
	struct SMeshCircle
	{
		D3DXVECTOR3	pos;		// �ʒu
		D3DXVECTOR3	rot;		// ����
		D3DXCOLOR	col;		// �F
		D3DXMATRIX	mtxWorld;	// ���[���h�}�g���b�N�X
		float		fRadius;	// ���a
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override	{ return m_meshCircle.pos; }		// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override	{ return m_meshCircle.rot; }		// �����擾
	D3DXMATRIX *GetPtrMtxWorld(void) override			{ return &m_meshCircle.mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	D3DXMATRIX GetMtxWorld(void) const override			{ return m_meshCircle.mtxWorld; }	// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshCircle *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const D3DXCOLOR& rCol,		// �F
		const POSGRID2& rPart,		// ������
		const float fRadius			// ���a
	);

	// �����o�֐�
	CRenderState *GetRenderState(void);			// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureID);		// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char *pTexturePass);	// �e�N�X�`������ (�p�X)
	void SetColor(const D3DXCOLOR& rCol);		// �F�ݒ�
	void SetRadius(const float fRadius);		// ���a�ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);	// �������ݒ�
	int GetTextureIndex(void) const		{ return m_nTextureID; }			// �e�N�X�`���C���f�b�N�X�擾
	D3DXCOLOR GetColor(void) const		{ return m_meshCircle.col; }		// �F�擾
	float GetRadius(void) const			{ return m_meshCircle.fRadius; }	// ���a�擾
	POSGRID2 GetPattern(void) const		{ return m_part; }					// �������擾

protected:
	// �����o�֐�
	void SetVtx(void);	// ���_���̐ݒ�
	void SetIdx(void);	// �C���f�b�N�X���̐ݒ�

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void DrawNormal(void);	// �ʏ�`��
	void DrawShader(CShader *pShader);	// �V�F�[�_�[�`��

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	CRenderState *m_pRenderState;		// �����_�[�X�e�[�g�̏��

	SMeshCircle m_meshCircle;	// ���b�V���T�[�N���̏��
	POSGRID2 m_part;	// ������
	int m_nNumVtx;		// �K�v���_��
	int m_nNumIdx;		// �K�v�C���f�b�N�X��
	int m_nTextureID;	// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT_MESHCIRCLE_H_
