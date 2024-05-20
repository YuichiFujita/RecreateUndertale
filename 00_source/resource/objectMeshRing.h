//============================================================
//
//	�I�u�W�F�N�g���b�V�������O�w�b�_�[ [objectMeshRing.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_MESHRING_H_
#define _OBJECT_MESHRING_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g���b�V�������O�N���X
class CObjectMeshRing : public CObject
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
	explicit CObjectMeshRing(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshRing() override;

	// ���b�V�������O�\����
	struct SMeshRing
	{
		D3DXVECTOR3	pos;			// �ʒu
		D3DXVECTOR3	rot;			// ����
		D3DXCOLOR	col;			// �F
		D3DXMATRIX	mtxWorld;		// ���[���h�}�g���b�N�X
		ETexDir		texDir;			// �e�N�X�`������
		float		fHoleRadius;	// ���̔��a
		float		fThickness;		// ����
		float		fOuterPlusY;	// �O����Y���W���Z��
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override	{ return m_meshRing.pos; }			// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override	{ return m_meshRing.rot; }			// �����擾
	D3DXMATRIX *GetPtrMtxWorld(void) override			{ return &m_meshRing.mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	D3DXMATRIX GetMtxWorld(void) const override			{ return m_meshRing.mtxWorld; }		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshRing *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const D3DXCOLOR& rCol,		// �F
		const POSGRID2& rPart,		// ������
		const POSGRID2& rTexPart,	// �e�N�X�`��������
		const float fHoleRadius,	// ���̔��a
		const float fThickness,		// ����
		const float fOuterPlusY		// �O����Y���W���Z��
	);

	// �����o�֐�
	CRenderState *GetRenderState(void);				// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureID);			// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char *pTexturePass);		// �e�N�X�`������ (�p�X)
	void SetColor(const D3DXCOLOR& rCol);			// �F�ݒ�
	void SetTexDir(const ETexDir texDir);			// �e�N�X�`�������ݒ�
	void SetHoleRadius(const float fHoleRadius);	// ���̔��a�ݒ�
	void SetThickness(const float fThickness);		// �����ݒ�
	void SetOuterPlusY(const float fOuterPlusY);	// �O����Y���W���Z�ʐݒ�
	HRESULT SetPattern(const POSGRID2& rPart);		// �������ݒ�
	void SetTexPattern(const POSGRID2& rTexPart);	// �e�N�X�`���������ݒ�
	int GetTextureIndex(void) const		{ return m_nTextureID; }			// �e�N�X�`���C���f�b�N�X�擾
	D3DXCOLOR GetColor(void) const		{ return m_meshRing.col; }			// �F�擾
	ETexDir GetTexDir(void) const		{ return m_meshRing.texDir; }		// �e�N�X�`�������擾
	float GetHoleRadius(void) const		{ return m_meshRing.fHoleRadius; }	// ���̔��a�擾
	float GetThickness(void) const		{ return m_meshRing.fThickness; }	// �����擾
	float GetOuterPlusY(void) const		{ return m_meshRing.fOuterPlusY; }	// �O����Y���W���Z�ʎ擾
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

	SMeshRing m_meshRing;	// ���b�V�������O�̏��
	POSGRID2 m_part;		// ������
	POSGRID2 m_texPart;		// �e�N�X�`��������
	int m_nNumVtx;			// �K�v���_��
	int m_nNumIdx;			// �K�v�C���f�b�N�X��
	int m_nTextureID;		// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT_MESHRING_H_
