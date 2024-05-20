//============================================================
//
//	�I�u�W�F�N�g���b�V���X�t�B�A�w�b�_�[ [objectMeshSphere.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_MESHSPHERE_H_
#define _OBJECT_MESHSPHERE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "objectMeshDome.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g���b�V���X�t�B�A�N���X
class CObjectMeshSphere : public CObject
{
public:
	// ������
	enum EDome
	{
		DOME_TOP = 0,	// �㔼��
		DOME_BOTTOM,	// ������
		DOME_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CObjectMeshSphere(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshSphere() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetPriority(const int nPriority) override;			// �D�揇�ʐݒ�
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override	{ return m_apDome[DOME_TOP]->GetVec3Position(); }	// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override	{ return m_apDome[DOME_TOP]->GetVec3Rotation(); }	// �����擾
	D3DXMATRIX *GetPtrMtxWorld(void) override			{ return m_apDome[DOME_TOP]->GetPtrMtxWorld(); }	// �}�g���b�N�X�|�C���^�擾
	D3DXMATRIX GetMtxWorld(void) const override			{ return m_apDome[DOME_TOP]->GetMtxWorld(); }		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshSphere *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const D3DXCOLOR& rCol,		// �F
		const POSGRID2& rPart,		// ������
		const POSGRID2& rTexPart,	// �e�N�X�`��������
		const float fRadius			// ���a
	);

	// �����o�֐�
	void SetRenderState(CRenderState renderState);	// �����_�[�X�e�[�g���ݒ�
	void BindTexture(const int nTextureID);			// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char *pTexturePass);		// �e�N�X�`������ (�p�X)
	void SetColor(const D3DXCOLOR& rCol);			// �F�ݒ�
	void SetRadius(const float fRadius);			// ���a�ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);		// �������ݒ�
	void SetTexPattern(const POSGRID2& rTexPart);	// �e�N�X�`���������ݒ�
	int GetTextureIndex(void) const		{ return m_apDome[DOME_TOP]->GetTextureIndex(); }	// �e�N�X�`���C���f�b�N�X�擾
	D3DXCOLOR GetColor(void) const		{ return m_apDome[DOME_TOP]->GetColor(); }			// �F�擾
	float GetRadius(void) const			{ return m_apDome[DOME_TOP]->GetRadius(); }			// ���a�擾
	POSGRID2 GetPattern(void) const		{ return m_apDome[DOME_TOP]->GetPattern(); }		// �������擾
	POSGRID2 GetTexPattern(void) const	{ return m_apDome[DOME_TOP]->GetTexPattern(); }		// �e�N�X�`���������擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	CObjectMeshDome *m_apDome[DOME_MAX];	// �����̏��
	POSGRID2 m_part;	// ������
	POSGRID2 m_texPart;	// �e�N�X�`��������
};

#endif	// _OBJECT_MESHSPHERE_H_
