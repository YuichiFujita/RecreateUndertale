//============================================================
//
//	�I�u�W�F�N�g���b�V���V�����_�[�w�b�_�[ [objectMeshCylinder.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_MESHCYLINDER_H_
#define _OBJECT_MESHCYLINDER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g���b�V���V�����_�[�N���X
class CObjectMeshCylinder : public CObject
{
public:
	// �e�N�X�`��������
	enum ETexDir
	{
		TEXDIR_OUTSIDE = 0,	// �e�N�X�`���O������
		TEXDIR_INSIDE,		// �e�N�X�`����������
		TEXDIR_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CObjectMeshCylinder(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshCylinder() override;

	// ���b�V���V�����_�[�\����
	struct SMeshCylinder
	{
		D3DXVECTOR3	pos;		// �ʒu
		D3DXVECTOR3	rot;		// ����
		D3DXCOLOR	col;		// �F
		D3DXMATRIX	mtxWorld;	// ���[���h�}�g���b�N�X
		ETexDir		texDir;		// �e�N�X�`������
		float		fRadius;	// ���a
		float		fHeight;	// �c��
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override	{ return m_meshCylinder.pos; }			// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override	{ return m_meshCylinder.rot; }			// �����擾
	D3DXMATRIX *GetPtrMtxWorld(void) override			{ return &m_meshCylinder.mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	D3DXMATRIX GetMtxWorld(void) const override			{ return m_meshCylinder.mtxWorld; }		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshCylinder *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const D3DXCOLOR& rCol,		// �F
		const POSGRID2& rPart,		// ������
		const POSGRID2& rTexPart,	// �e�N�X�`��������
		const float fRadius,		// ���a
		const float fHeight			// �c��
	);

	// �����o�֐�
	CRenderState *GetRenderState(void);				// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureID);			// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char *pTexturePass);		// �e�N�X�`������ (�p�X)
	void SetColor(const D3DXCOLOR& rCol);			// �F�ݒ�
	void SetRadius(const float fRadius);			// ���a�ݒ�
	void SetHeight(const float fHeight);			// �c���ݒ�
	void SetTexDir(const ETexDir texDir);			// �e�N�X�`�������ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);		// �������ݒ�
	void SetTexPattern(const POSGRID2& rTexPart);	// �e�N�X�`���������ݒ�
	int GetTextureIndex(void) const		{ return m_nTextureID; }			// �e�N�X�`���C���f�b�N�X�擾
	D3DXCOLOR GetColor(void) const		{ return m_meshCylinder.col; }		// �F�擾
	float GetRadius(void) const			{ return m_meshCylinder.fRadius; }	// ���a�擾
	float GetHeight(void) const			{ return m_meshCylinder.fHeight; }	// �c���擾
	ETexDir GetTexDir(void) const		{ return m_meshCylinder.texDir; }	// �e�N�X�`�������擾
	POSGRID2 GetPattern(void) const		{ return m_part; }					// �������擾
	POSGRID2 GetTexPattern(void) const	{ return m_texPart; }				// �e�N�X�`���������擾

protected:
	// �����o�֐�
	void SetVtx(void);	// ���_���̐ݒ�
	void SetIdx(void);	// �C���f�b�N�X���̐ݒ�
	void SetScrollTex	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	( // ����
		const float fTexU,	// �e�N�X�`���̉����W�̊J�n�ʒu
		const float fTexV	// �e�N�X�`���̏c���W�̊J�n�ʒu
	);

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

	SMeshCylinder m_meshCylinder;	// ���b�V���V�����_�[�̏��
	POSGRID2 m_part;	// ������
	POSGRID2 m_texPart;	// �e�N�X�`��������
	int m_nNumVtx;		// �K�v���_��
	int m_nNumIdx;		// �K�v�C���f�b�N�X��
	int m_nTextureID;	// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT_MESHCYLINDER_H_
