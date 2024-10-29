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
	explicit CObjectMeshCircle(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshCircle() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	inline VECTOR3 GetVec3Position() const override	{ return m_pos; }		// �ʒu�擾
	inline VECTOR3 GetVec3Rotation() const override	{ return m_rot; }		// �����擾
	inline MATRIX* GetPtrMtxWorld() override		{ return &m_mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	inline MATRIX GetMtxWorld() const override		{ return m_mtxWorld; }	// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshCircle* Create	// ����
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const COLOR& rCol,		// �F
		const POSGRID2& rPart,	// ������
		const float fRadius		// ���a
	);

	// �����o�֐�
	CRenderState* GetRenderState();				// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureIdx);	// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char* pTexturePath);	// �e�N�X�`������ (�p�X)
	void SetAlpha(const float fAlpha);			// �����x�ݒ�
	void SetColor(const COLOR& rCol);			// �F�ݒ�
	void SetRadius(const float fRadius);		// ���a�ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);	// �������ݒ�
	inline int GetTextureIndex() const	{ return m_nTextureIdx; }	// �e�N�X�`���C���f�b�N�X�擾
	inline float GetAlpha() const		{ return m_col.a; }			// �����x�擾
	inline COLOR GetColor() const		{ return m_col; }			// �F�擾
	inline float GetRadius() const		{ return m_fRadius; }		// ���a�擾
	inline POSGRID2 GetPattern() const	{ return m_part; }			// �������擾

protected:
	// ���z�֐�
	virtual void CalcDrawMatrix();	// �`��}�g���b�N�X�v�Z

	// �����o�֐�
	void SetVtx();	// ���_���̐ݒ�
	void SetIdx();	// �C���f�b�N�X���̐ݒ�

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void DrawNormal();	// �ʏ�`��
	void DrawShader(CShader* pShader);	// �V�F�[�_�[�`��

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	CRenderState* m_pRenderState;		// �����_�[�X�e�[�g�̏��
	MATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	VECTOR3 m_pos;		// �ʒu
	VECTOR3 m_rot;		// ����
	COLOR m_col;		// �F
	POSGRID2 m_part;	// ������
	float m_fRadius;	// ���a
	int m_nNumVtx;		// �K�v���_��
	int m_nNumIdx;		// �K�v�C���f�b�N�X��
	int m_nTextureIdx;	// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT_MESHCIRCLE_H_
