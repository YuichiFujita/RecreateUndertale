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
	explicit CObjectMeshTube(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshTube() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	inline VECTOR3 GetVec3Position() const override	{ return m_pCylinder->GetVec3Position(); }	// �ʒu�擾
	inline VECTOR3 GetVec3Rotation() const override	{ return m_pCylinder->GetVec3Rotation(); }	// �����擾
	inline MATRIX* GetPtrMtxWorld() override		{ return m_pCylinder->GetPtrMtxWorld(); }	// �}�g���b�N�X�|�C���^�擾
	inline MATRIX GetMtxWorld() const override		{ return m_pCylinder->GetMtxWorld(); }		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshTube* Create	// ����
	( // ����
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rRot,		// ����
		const COLOR& rCol,			// �F
		const POSGRID2& rPart,		// ������
		const POSGRID2& rTexPart,	// �e�N�X�`��������
		const float fRadius,		// ���a
		const float fHeight			// �c��
	);

	// �����o�֐�
	void SetRenderState(CRenderState renderState);	// �����_�[�X�e�[�g���ݒ�
	void BindTexture(const int nTextureIdx);		// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char* pTexturePath);		// �e�N�X�`������ (�p�X)
	void SetAlpha(const float fAlpha);				// �����x�ݒ�
	void SetColor(const COLOR& rCol);				// �F�ݒ�
	void SetRadius(const float fRadius);			// ���a�ݒ�
	void SetHeight(const float fHeight);			// �c���ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);		// �������ݒ�
	void SetTexPattern(const POSGRID2& rTexPart);	// �e�N�X�`���������ݒ�
	inline int GetTextureIndex() const		{ return m_pCylinder->GetTextureIndex(); }	// �e�N�X�`���C���f�b�N�X�擾
	inline float GetAlpha() const			{ return m_pCylinder->GetAlpha(); }			// �����x�擾
	inline COLOR GetColor() const			{ return m_pCylinder->GetColor(); }			// �F�擾
	inline float GetRadius() const			{ return m_pCylinder->GetRadius(); }		// ���a�擾
	inline float GetHeight() const			{ return m_pCylinder->GetHeight(); }		// �c���擾
	inline POSGRID2 GetPattern() const		{ return m_pCylinder->GetPattern(); }		// �������擾
	inline POSGRID2 GetTexPattern() const	{ return m_pCylinder->GetTexPattern(); }	// �e�N�X�`���������擾

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetPositionRelative();				// ���Έʒu�ݒ�
	MATRIX CalcCylinderMtxWorld() const;	// �V�����_�[�}�g���b�N�X�v�Z���ʎ擾

	// �����o�ϐ�
	CObjectMeshCircle* m_apCover[COVER_MAX];	// �W�̏��
	CObjectMeshCylinder* m_pCylinder;			// ���̏��
	POSGRID2 m_part;	// ������
	POSGRID2 m_texPart;	// �e�N�X�`��������
};

#endif	// _OBJECT_MESHTUBE_H_
