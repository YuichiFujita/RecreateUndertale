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
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	VECTOR3 GetVec3Position() const override	{ return m_apDome[DOME_TOP]->GetVec3Position(); }	// �ʒu�擾
	VECTOR3 GetVec3Rotation() const override	{ return m_apDome[DOME_TOP]->GetVec3Rotation(); }	// �����擾
	MATRIX* GetPtrMtxWorld() override			{ return m_apDome[DOME_TOP]->GetPtrMtxWorld(); }	// �}�g���b�N�X�|�C���^�擾
	MATRIX GetMtxWorld() const override			{ return m_apDome[DOME_TOP]->GetMtxWorld(); }		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshSphere* Create	// ����
	( // ����
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rRot,		// ����
		const COLOR& rCol,			// �F
		const POSGRID2& rPart,		// ������
		const POSGRID2& rTexPart,	// �e�N�X�`��������
		const float fRadius			// ���a
	);

	// �����o�֐�
	void SetRenderState(CRenderState renderState);	// �����_�[�X�e�[�g���ݒ�
	void BindTexture(const int nTextureID);			// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char* pTexturePath);		// �e�N�X�`������ (�p�X)
	void SetAlpha(const float fAlpha);				// �����x�ݒ�
	void SetColor(const COLOR& rCol);				// �F�ݒ�
	void SetRadius(const float fRadius);			// ���a�ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);		// �������ݒ�
	void SetTexPattern(const POSGRID2& rTexPart);	// �e�N�X�`���������ݒ�
	int GetTextureIndex() const		{ return m_apDome[DOME_TOP]->GetTextureIndex(); }	// �e�N�X�`���C���f�b�N�X�擾
	float GetAlpha() const			{ return m_apDome[DOME_TOP]->GetAlpha(); }			// �����x�擾
	COLOR GetColor() const			{ return m_apDome[DOME_TOP]->GetColor(); }			// �F�擾
	float GetRadius() const			{ return m_apDome[DOME_TOP]->GetRadius(); }			// ���a�擾
	POSGRID2 GetPattern() const		{ return m_apDome[DOME_TOP]->GetPattern(); }		// �������擾
	POSGRID2 GetTexPattern() const	{ return m_apDome[DOME_TOP]->GetTexPattern(); }		// �e�N�X�`���������擾

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	CObjectMeshDome* m_apDome[DOME_MAX];	// �����̏��
	POSGRID2 m_part;	// ������
	POSGRID2 m_texPart;	// �e�N�X�`��������
};

#endif	// _OBJECT_MESHSPHERE_H_
