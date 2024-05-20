//============================================================
//
//	�I�u�W�F�N�g���b�V���`���[�u�w�b�_�[ [objectMeshTube.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_MESHTUBE_H_
#define _OBJECT_MESHTUBE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "objectMeshCylinder.h"

//************************************************************
//	�O���錾
//************************************************************
class CObjectMeshCircle;	// �I�u�W�F�N�g���b�V���T�[�N���N���X
class CRenderState;			// �����_�[�X�e�[�g�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g���b�V���`���[�u�N���X
class CObjectMeshTube : public CObject
{
public:
	// �W��
	enum ECover
	{
		COVER_BOTTOM = 0,	// ���W
		COVER_TOP,			// ��W
		COVER_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CObjectMeshTube(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshTube() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetPriority(const int nPriority) override;			// �D�揇�ʐݒ�
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override	{ return m_pCylinder->GetVec3Position(); }	// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override	{ return m_pCylinder->GetVec3Rotation(); }	// �����擾
	D3DXMATRIX *GetPtrMtxWorld(void) override			{ return m_pCylinder->GetPtrMtxWorld(); }	// �}�g���b�N�X�|�C���^�擾
	D3DXMATRIX GetMtxWorld(void) const override			{ return m_pCylinder->GetMtxWorld(); }		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshTube *Create	// ����
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
	void SetRenderState(CRenderState renderState);	// �����_�[�X�e�[�g���ݒ�
	void BindTexture(const int nTextureID);			// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char *pTexturePass);		// �e�N�X�`������ (�p�X)
	void SetColor(const D3DXCOLOR& rCol);			// �F�ݒ�
	void SetRadius(const float fRadius);			// ���a�ݒ�
	void SetHeight(const float fHeight);			// �c���ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);		// �������ݒ�
	void SetTexPattern(const POSGRID2& rTexPart);	// �e�N�X�`���������ݒ�
	int GetTextureIndex(void) const		{ return m_pCylinder->GetTextureIndex(); }	// �e�N�X�`���C���f�b�N�X�擾
	D3DXCOLOR GetColor(void) const		{ return m_pCylinder->GetColor(); }			// �F�擾
	float GetRadius(void) const			{ return m_pCylinder->GetRadius(); }		// ���a�擾
	float GetHeight(void) const			{ return m_pCylinder->GetHeight(); }		// �c���擾
	POSGRID2 GetPattern(void) const		{ return m_pCylinder->GetPattern(); }		// �������擾
	POSGRID2 GetTexPattern(void) const	{ return m_pCylinder->GetTexPattern(); }	// �e�N�X�`���������擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetPositionRelative(void);					// ���Έʒu�ݒ�
	D3DXMATRIX CalcCylinderMtxWorld(void) const;	// �V�����_�[�}�g���b�N�X�v�Z���ʎ擾

	// �����o�ϐ�
	CObjectMeshCircle *m_apCover[COVER_MAX];	// �W�̏��
	CObjectMeshCylinder *m_pCylinder;			// ���̏��
	POSGRID2 m_part;	// ������
	POSGRID2 m_texPart;	// �e�N�X�`��������
};

#endif	// _OBJECT_MESHTUBE_H_
