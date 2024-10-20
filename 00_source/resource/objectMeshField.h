//============================================================
//
//	�I�u�W�F�N�g���b�V���t�B�[���h�w�b�_�[ [objectMeshField.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_MESHFIELD_H_
#define _OBJECT_MESHFIELD_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g���b�V���t�B�[���h�N���X
class CObjectMeshField : public CObject
{
public:
	// �R���X�g���N�^
	explicit CObjectMeshField(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshField() override;

	// ���b�V���t�B�[���h�\����
	struct SMeshField
	{
		VECTOR3	pos;		// �ʒu
		VECTOR3	rot;		// ����
		VECTOR2	size;		// �傫��
		COLOR	col;		// �F
		MATRIX	mtxWorld;	// ���[���h�}�g���b�N�X
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec2Size(const VECTOR2& rSize) override;	// �傫���ݒ�
	VECTOR3 GetVec3Position(void) const override	{ return m_meshField.pos; }			// �ʒu�擾
	VECTOR3 GetVec3Rotation(void) const override	{ return m_meshField.rot; }			// �����擾
	VECTOR2 GetVec2Size(void) const override		{ return m_meshField.size; }		// �傫���擾
	MATRIX *GetPtrMtxWorld(void) override			{ return &m_meshField.mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	MATRIX GetMtxWorld(void) const override			{ return m_meshField.mtxWorld; }	// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshField *Create	// ����
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const VECTOR2& rSize,	// �傫��
		const COLOR& rCol,		// �F
		const POSGRID2& rPart	// ������
	);

	// �����o�֐�
	CRenderState *GetRenderState(void);			// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureID);		// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char *pTexturePath);	// �e�N�X�`������ (�p�X)
	void SetAlpha(const float fAlpha);			// �����x�ݒ�
	void SetColor(const COLOR& rCol);			// �F�ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);	// �������ݒ�
	int GetTextureIndex(void) const	{ return m_nTextureID; }		// �e�N�X�`���C���f�b�N�X�擾
	float GetAlpha(void) const		{ return m_meshField.col.a; }	// �����x�擾
	COLOR GetColor(void) const		{ return m_meshField.col; }		// �F�擾
	POSGRID2 GetPattern(void) const	{ return m_part; }				// �������擾
	int GetNumVertex(void) const	{ return m_nNumVtx; }			// ���_���擾

	void SetGapPosition(const int nID, const VECTOR3& rPos);		// ���W�̂���ݒ�
	VECTOR3 GetGapPosition(const int nID);							// ���W�̂���擾
	void NormalizeNormal(void);										// �@���̐��K��
	bool LandPosition(VECTOR3& rPos, VECTOR3& rMove);				// ���b�V�����n
	void SetMeshVertexPosition(const int nID, const VECTOR3& rPos);	// ���b�V���̒��_�ʒu�ݒ�
	void SetTerrain(const POSGRID2& rPart, VECTOR3 *pPosGap);		// �n�`�ݒ�

	VECTOR3 GetMeshVertexPosition(const int nID);		// ���b�V���̒��_�ʒu�擾
	bool IsPositionRange(const VECTOR3& rPos);			// ���b�V���͈͓̔��擾
	float GetPositionHeight(const VECTOR3& rPos);		// ���b�V���̒��n�ʒu�擾 (��]��l��)
	float GetPositionRotateHeight(const VECTOR3& rPos);	// ���b�V���̒��n�ʒu�擾 (��]�l��)

protected:
	// �����o�֐�
	void SetVtx(bool bNor);	// ���_���̐ݒ�
	void SetIdx(void);		// �C���f�b�N�X���̐ݒ�
	void SetScrollTex		// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	( // ����
		const float fTexU,	// �e�N�X�`���̉����W�̊J�n�ʒu
		const float fTexV	// �e�N�X�`���̏c���W�̊J�n�ʒu
	);

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void DrawNormal(void);	// �ʏ�`��
	void DrawShader(CShader* pShader);	// �V�F�[�_�[�`��
	VECTOR3 GetNormalLeft(VERTEX_3D *pVtx);			// �@���̎擾 (��)
	VECTOR3 GetNormalLeftTop(VERTEX_3D *pVtx);		// �@���̎擾 (����)
	VECTOR3 GetNormalLeftBottom(VERTEX_3D *pVtx);	// �@���̎擾 (����)
	VECTOR3 GetNormalRight(VERTEX_3D *pVtx);		// �@���̎擾 (�E)
	VECTOR3 GetNormalRightTop(VERTEX_3D *pVtx);		// �@���̎擾 (�E��)
	VECTOR3 GetNormalRightBottom(VERTEX_3D *pVtx);	// �@���̎擾 (�E��)

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	CRenderState *m_pRenderState;		// �����_�[�X�e�[�g�̏��
	VECTOR3 *m_pPosGapBuff;	// ���W�̂���o�b�t�@�ւ̃|�C���^
	VECTOR3 *m_pNorBuff;	// �@���o�b�t�@�ւ̃|�C���^
	int *m_pNumNorBuff;		// �@���̎g�p���o�b�t�@�ւ̃|�C���^
	SMeshField m_meshField;	// ���b�V���t�B�[���h�̏��
	POSGRID2 m_part;		// ������
	int m_nNumVtx;			// �K�v���_��
	int m_nNumIdx;			// �K�v�C���f�b�N�X��
	int m_nTextureID;		// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT_MESHFIELD_H_
