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
class CFrame2DModule;	// �t���[��2D�@�\�N���X
class CObject2D;		// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �t���[��2D�N���X
class CFrame2D : public CObject
{
public:
	// �z�u�v���Z�b�g��
	enum EPreset
	{
		PRESET_NONE = -1,	// �w�薳��
		PRESET_DOWN,		// �����z�u
		PRESET_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CFrame2D();

	// �f�X�g���N�^
	~CFrame2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Size(const VECTOR3& rSize) override;	// �傫���ݒ�
	inline VECTOR3 GetVec3Position() const override	{ return m_pos; }	// �ʒu�擾
	inline VECTOR3 GetVec3Rotation() const override	{ return m_rot; }	// �����擾
	inline VECTOR3 GetVec3Size() const override		{ return m_size; }	// �傫���擾

	// �ÓI�����o�֐�
	static CFrame2D* Create(const EPreset preset);	// ���� (�z�u�v���Z�b�g)
	static CFrame2D* Create	// ���� (�z�u�w��)
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const VECTOR3& rSize	// �傫��
	);

	// �����o�֐�
	HRESULT ChangeModule(CFrame2DModule* pModule);	// �@�\�ύX
	void SetPreset(const EPreset preset);			// �z�u�v���Z�b�g�ݒ�
	inline void InitModule()				 { m_pModule = nullptr; }	// �@�\������
	inline CFrame2DModule* GetModule() const { return m_pModule; }		// �@�\�擾
	inline EPreset GetPreset() const		 { return m_preset; }		// �z�u�v���Z�b�g�擾

private:
	// �|���S����
	enum EPolygon
	{
		POLYGON_INSIDE = 0,	// ����
		POLYGON_FRAME,		// �O�g
		POLYGON_MAX			// ���̗񋓌^�̑���
	};

	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	CObject2D* m_apFrame[POLYGON_MAX];	// �t���[�����
	CFrame2DModule* m_pModule;	// �@�\
	VECTOR3 m_pos;		// �ʒu
	VECTOR3 m_rot;		// ����
	VECTOR3 m_size;		// �傫��
	EPreset m_preset;	// �z�u�v���Z�b�g
};

#endif	// _FRAME2D_H_
