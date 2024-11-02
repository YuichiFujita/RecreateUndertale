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
	explicit CObjectMeshField(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshField() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec2Size(const VECTOR2& rSize) override;	// �傫���ݒ�
	inline VECTOR3 GetVec3Position() const override	{ return m_pos; }		// �ʒu�擾
	inline VECTOR3 GetVec3Rotation() const override	{ return m_rot; }		// �����擾
	inline VECTOR2 GetVec2Size() const override		{ return m_size; }		// �傫���擾
	inline MATRIX* GetPtrMtxWorld() override		{ return &m_mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	inline MATRIX GetMtxWorld() const override		{ return m_mtxWorld; }	// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshField* Create	// ����
	( // ����
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rRot,		// ����
		const VECTOR2& rSize,		// �傫��
		const COLOR& rCol,			// �F
		const POSGRID2& rPart,		// ������
		const POSGRID2& rTexPart	// �e�N�X�`��������
	);

	// �����o�֐�
	CRenderState* GetRenderState();					// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureIdx);		// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char* pTexturePath);		// �e�N�X�`������ (�p�X)
	void SetAlpha(const float fAlpha);				// �����x�ݒ�
	void SetColor(const COLOR& rCol);				// �F�ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);		// �������ݒ�
	void SetTexPattern(const POSGRID2& rTexPart);	// �e�N�X�`���������ݒ�
	inline int GetTextureIndex() const		{ return m_nTextureIdx; }	// �e�N�X�`���C���f�b�N�X�擾
	inline float GetAlpha() const			{ return m_col.a; }			// �����x�擾
	inline COLOR GetColor() const			{ return m_col; }			// �F�擾
	inline POSGRID2 GetPattern() const		{ return m_part; }			// �������擾
	inline POSGRID2 GetTexPattern() const	{ return m_texPart; }		// �e�N�X�`���������擾
	inline int GetNumVertex() const			{ return m_nNumVtx; }		// ���_���擾

	void SetGapPosition(const int nIdx, const VECTOR3& rPos);			// ���W�̂���ݒ�
	VECTOR3 GetGapPosition(const int nIdx);								// ���W�̂���擾
	void SetMeshVertexPosition(const int nIdx, const VECTOR3& rPos);	// ���b�V���̒��_�ʒu�ݒ�
	VECTOR3 GetMeshVertexPosition(const int nIdx);						// ���b�V���̒��_�ʒu�擾
	bool LandPosition(VECTOR3& rPos, VECTOR3& rMove);					// ���b�V�����n
	void SetTerrain(const POSGRID2& rPart, VECTOR3* pPosGap);			// �n�`�ݒ�
	bool IsPositionRange(const VECTOR3& rPos);		// ���b�V���͈͓̔��擾
	float GetPositionHeight(const VECTOR3& rPos);	// ���b�V���̒��n�ʒu�擾
	void NormalizeNormal();							// �@���̐��K��

protected:
	// ���z�֐�
	virtual void CalcDrawMatrix();	// �`��}�g���b�N�X�v�Z

	// �����o�֐�
	void SetVtx(bool bNor);	// ���_���̐ݒ�
	void SetIdx();			// �C���f�b�N�X���̐ݒ�
	void SetScrollTex		// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	( // ����
		const float fTexU,	// �e�N�X�`���̉����W�̊J�n�ʒu
		const float fTexV	// �e�N�X�`���̏c���W�̊J�n�ʒu
	);

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void DrawNormal();	// �ʏ�`��
	void DrawShader(CShader* pShader);	// �V�F�[�_�[�`��
	VECTOR3 GetNormalLeft(VERTEX_3D* pVtx);			// �@���̎擾 (��)
	VECTOR3 GetNormalLeftTop(VERTEX_3D* pVtx);		// �@���̎擾 (����)
	VECTOR3 GetNormalLeftBottom(VERTEX_3D* pVtx);	// �@���̎擾 (����)
	VECTOR3 GetNormalRight(VERTEX_3D* pVtx);		// �@���̎擾 (�E)
	VECTOR3 GetNormalRightTop(VERTEX_3D* pVtx);		// �@���̎擾 (�E��)
	VECTOR3 GetNormalRightBottom(VERTEX_3D* pVtx);	// �@���̎擾 (�E��)

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	CRenderState* m_pRenderState;		// �����_�[�X�e�[�g�̏��
	VECTOR3* m_pPosGapBuff;	// ���W�̂���o�b�t�@�ւ̃|�C���^
	VECTOR3* m_pNorBuff;	// �@���o�b�t�@�ւ̃|�C���^
	int* m_pNumNorBuff;		// �@���̎g�p���o�b�t�@�ւ̃|�C���^
	MATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	VECTOR3 m_pos;			// �ʒu
	VECTOR3 m_rot;			// ����
	VECTOR2 m_size;			// �傫��
	COLOR m_col;			// �F
	POSGRID2 m_part;		// ������
	POSGRID2 m_texPart;		// �e�N�X�`��������
	int m_nNumVtx;			// �K�v���_��
	int m_nNumIdx;			// �K�v�C���f�b�N�X��
	int m_nTextureIdx;		// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT_MESHFIELD_H_
