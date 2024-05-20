//============================================================
//
//	�I�u�W�F�N�g3D�w�b�_�[ [object3D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g3D�N���X
class CObject3D : public CObject
{
public:
	// ���_��
	enum EOrigin
	{
		ORIGIN_CENTER = 0,	// ���S���_
		ORIGIN_DOWN,		// �����_
		ORIGIN_MAX,			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CObject3D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObject3D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Sizing(const D3DXVECTOR3& rSize) override;	// �傫���ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override	{ return m_pos; }		// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override	{ return m_rot; }		// �����擾
	D3DXVECTOR3 GetVec3Sizing(void) const override		{ return m_size; }		// �傫���擾
	D3DXMATRIX *GetPtrMtxWorld(void) override			{ return &m_mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	D3DXMATRIX GetMtxWorld(void) const override			{ return m_mtxWorld; }	// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObject3D *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,				// �ʒu
		const D3DXVECTOR3& rSize,				// �傫��
		const D3DXVECTOR3& rRot = VEC3_ZERO,	// ����
		const D3DXCOLOR& rCol = XCOL_WHITE,		// �F
		const EOrigin origin = ORIGIN_CENTER	// ���_
	);

	// �����o�֐�
	CRenderState *GetRenderState(void);			// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureID);		// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char *pTexturePass);	// �e�N�X�`������ (�p�X)
	void SetColor(const D3DXCOLOR& rCol);		// �F�ݒ�
	void SetOrigin(const EOrigin origin);		// ���_�ݒ�
	int GetTextureIndex(void) const		{ return m_nTextureID; }	// �e�N�X�`���C���f�b�N�X�擾
	D3DXCOLOR GetColor(void) const		{ return m_col; }			// �F�擾
	EOrigin GetOrigin(void) const		{ return m_origin; }		// ���_�擾
	void SetVertexPosition(const int nID, const D3DXVECTOR3& rPos);	// ���_�ʒu�ݒ�
	D3DXVECTOR3 GetVertexPosition(const int nID);					// ���_�ʒu�擾
	void SetGapPosition(const int nID, const D3DXVECTOR3& rPos);	// ���W�̂���ݒ�
	D3DXVECTOR3 GetGapPosition(const int nID);						// ���W�̂���擾
	float GetPositionHeight(const D3DXVECTOR3&rPos);				// �|���S���̒��n�擾

protected:
	// �����o�֐�
	void SetVtx(void);	// ���_���̐ݒ�

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void DrawNormal(void);				// �ʏ�`��
	void DrawShader(CShader *pShader);	// �V�F�[�_�[�`��
	void NormalizeNormal(void);			// �@���̐��K��

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	CRenderState *m_pRenderState;		// �����_�[�X�e�[�g�̏��
	D3DXVECTOR3 *m_pPosGapBuff;			// ���W�̂���o�b�t�@�ւ̃|�C���^
	D3DXMATRIX	m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3	m_pos;			// �ʒu
	D3DXVECTOR3	m_rot;			// ����
	D3DXVECTOR3	m_size;			// �傫��
	D3DXCOLOR	m_col;			// �F
	EOrigin		m_origin;		// ���_
	int			m_nTextureID;	// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT3D_H_
