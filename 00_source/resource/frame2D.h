//============================================================
//
//	�t���[��2D�w�b�_�[ [frame2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_H_
#define _FRAME2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �t���[��2D�N���X
class CFrame2D : public CObject
{
public:
	// �|���S����
	enum EPolygon
	{
		POLYGON_INSIDE = 0,	// ����
		POLYGON_FRAME,		// �O�g
		POLYGON_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CFrame2D();

	// �f�X�g���N�^
	~CFrame2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Size(const VECTOR3& rSize) override;	// �傫���ݒ�
	VECTOR3 GetVec3Position(void) const override	{ return m_pos; }	// �ʒu�擾
	VECTOR3 GetVec3Rotation(void) const override	{ return m_rot; }	// �����擾
	VECTOR3 GetVec3Size(void) const override		{ return m_size; }	// �傫���擾

	// �ÓI�����o�֐�
	static CFrame2D* Create	// ����
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const VECTOR3& rSize	// �傫��
	);

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	CObject2D* m_apFrame[POLYGON_MAX];	// �t���[�����
	VECTOR3 m_pos;	// �ʒu
	VECTOR3 m_rot;	// ����
	VECTOR3 m_size;	// �傫��
};

#endif	// _FRAME2D_H_
