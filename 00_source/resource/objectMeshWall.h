//============================================================
//
//	�I�u�W�F�N�g���b�V���E�H�[���w�b�_�[ [objectMeshWall.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_MESHWALL_H_
#define _OBJECT_MESHWALL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g���b�V���E�H�[���N���X
class CObjectMeshWall : public CObject
{
public:
	// �R���X�g���N�^
	explicit CObjectMeshWall(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshWall() override;

	// ���b�V���E�H�[���\����
	struct SMeshWall
	{
		D3DXVECTOR3	pos;		// �ʒu
		D3DXVECTOR3	rot;		// ����
		D3DXVECTOR2	size;		// �傫��
		D3DXCOLOR	col;		// �F
		D3DXMATRIX	mtxWorld;	// ���[���h�}�g���b�N�X
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	void SetVec2Sizing(const D3DXVECTOR2& rSize) override;	// �傫���ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override	{ return m_meshWall.pos; }			// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override	{ return m_meshWall.rot; }			// �����擾
	D3DXVECTOR2 GetVec2Sizing(void) const override		{ return m_meshWall.size; }			// �傫���擾
	D3DXMATRIX *GetPtrMtxWorld(void) override			{ return &m_meshWall.mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	D3DXMATRIX GetMtxWorld(void) const override			{ return m_meshWall.mtxWorld; }		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshWall *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const D3DXVECTOR2& rSize,	// �傫��
		const D3DXCOLOR& rCol,		// �F
		const POSGRID2& rPart		// ������
	);

	// �����o�֐�
	CRenderState *GetRenderState(void);			// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureID);		// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char *pTexturePass);	// �e�N�X�`������ (�p�X)
	void SetColor(const D3DXCOLOR& rCol);		// �F�ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);	// �������ݒ�
	int GetTextureIndex(void) const		{ return m_nTextureID; }	// �e�N�X�`���C���f�b�N�X�擾
	D3DXCOLOR GetColor(void) const		{ return m_meshWall.col; }	// �F�擾
	POSGRID2 GetPattern(void) const		{ return m_part; }			// �������擾

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

	SMeshWall m_meshWall;	// ���b�V���E�H�[���̏��
	POSGRID2 m_part;		// ������
	int m_nNumVtx;			// �K�v���_��
	int m_nNumIdx;			// �K�v�C���f�b�N�X��
	int m_nTextureID;		// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT_MESHWALL_H_
