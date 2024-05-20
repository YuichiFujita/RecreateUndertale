//============================================================
//
//	�I�u�W�F�N�g�r���{�[�h�w�b�_�[ [objectBillboard.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECTBILLBOARD_H_
#define _OBJECTBILLBOARD_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�r���{�[�h�N���X
class CObjectBillboard : public CObject
{
public:
	// ���_��
	enum EOrigin
	{
		ORIGIN_CENTER = 0,	// ���S���_
		ORIGIN_DOWN,		// �����_
		ORIGIN_MAX,			// ���̗񋓌^�̑���
	};

	// ��]��
	enum ERotate
	{
		ROTATE_NORMAL = 0,	// �ʏ��]
		ROTATE_LATERAL,		// ����]
		ROTATE_MAX,			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CObjectBillboard(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectBillboard() override;

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
	static CObjectBillboard *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rSize,	// �傫��
		const D3DXVECTOR3& rRot = VEC3_ZERO,	// ����
		const D3DXCOLOR& rCol = XCOL_WHITE,		// �F
		const EOrigin origin = ORIGIN_CENTER,	// ���_
		const ERotate rotate = ROTATE_NORMAL	// ��]
	);

	// �����o�֐�
	CRenderState *GetRenderState(void);			// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureID);		// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char *pTexturePass);	// �e�N�X�`������ (�p�X)
	void SetColor(const D3DXCOLOR& rCol);		// �F�ݒ�
	void SetOrigin(const EOrigin origin);		// ���_�ݒ�
	void SetRotate(const ERotate rotate);		// ��]�ݒ�
	int GetTextureIndex(void) const	{ return m_nTextureID; }	// �e�N�X�`���C���f�b�N�X�擾
	D3DXCOLOR GetColor(void) const	{ return m_col; }			// �F�擾
	EOrigin GetOrigin(void) const	{ return m_origin; }		// ���_�擾
	ERotate GetRotate(void) const	{ return m_rotate; }		// ��]�擾

protected:
	// �����o�֐�
	void SetVtx(void);	// ���_���̐ݒ�

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void DrawNormal(void);	// �ʏ�`��
	void DrawShader(CShader *pShader);	// �V�F�[�_�[�`��

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	CRenderState *m_pRenderState;		// �����_�[�X�e�[�g�̏��
	D3DXMATRIX	m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3	m_pos;		// �ʒu
	D3DXVECTOR3	m_rot;		// ����
	D3DXVECTOR3	m_size;		// �傫��
	D3DXCOLOR	m_col;		// �F
	EOrigin		m_origin;	// ���_
	ERotate		m_rotate;	// ��]
	float m_fAngle;			// �Ίp���̊p�x
	float m_fLength;		// �Ίp���̒���
	int   m_nTextureID;		// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECTBILLBOARD_H_
