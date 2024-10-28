//============================================================
//
//	�J�����w�b�_�[ [camera.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�N���X��`
//************************************************************
// �J�����N���X
class CCamera
{
public:
	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,	// �Œ���
		STATE_FOLLOW,	// �Ǐ]���
		STATE_CONTROL,	// ������
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CCamera();

	// �f�X�g���N�^
	~CCamera();

	// �J�����h��\����
	struct SSwing
	{
	public:
		// �R���X�g���N�^
		SSwing() :
			shiftPos	 (VEC3_ZERO),	// �ʒu�����
			fShiftAngle	 (0.0f),		// �ʒu�����炷�p�x
			fShiftLength (0.0f),		// �ʒu�����炷����
			fSubAngle	 (0.0f),		// ���炷�p�x�̌��Z��
			fSubLength	 (0.0f)			// ���炷�����̌��Z��
		{}

		// �����t���R���X�g���N�^
		SSwing(const float ShiftLength, const float SubAngle, const float SubLength) :
			shiftPos	 (VEC3_ZERO),	// �ʒu�����
			fShiftAngle	 (0.0f),		// �ʒu�����炷�p�x
			fShiftLength (ShiftLength),	// �ʒu�����炷����
			fSubAngle	 (SubAngle),	// ���炷�p�x�̌��Z��
			fSubLength	 (SubLength)	// ���炷�����̌��Z��
		{}

		// �f�X�g���N�^
		~SSwing() {}

		// �����o�ϐ�
		VECTOR3	shiftPos;		// �ʒu�����
		float	fShiftAngle;	// �ʒu�����炷�p�x
		float	fShiftLength;	// �ʒu�����炷����
		float	fSubAngle;		// ���炷�p�x�̌��Z��
		float	fSubLength;		// ���炷�����̌��Z��
	};

	// �J�����\����
	struct SCamera
	{
		VECTOR3 posV;			// ���݂̎��_
		VECTOR3 posR;			// ���݂̒����_
		VECTOR3 destPosV;		// �ڕW�̎��_
		VECTOR3 destPosR;		// �ڕW�̒����_
		VECTOR3 vecU;			// ������x�N�g��
		VECTOR3 rot;			// ���݂̌���
		VECTOR3 destRot;		// �ڕW�̌���
		float fDis;				// ���݂̎��_�ƒ����_�̋���
		float fDestDis;			// �ڕW�̎��_�ƒ����_�̋���
		SSwing swing;			// �J�����h����
		D3DVIEWPORT9 viewport;	// �r���[�|�[�g���
		MATRIX mtxProj;			// �v���W�F�N�V�����}�g���b�N�X
		MATRIX mtxView;			// �r���[�}�g���b�N�X
	};

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);	// �X�V
	void SetCamera();		// �J�����ݒ�
	SCamera GetCamera();	// �J�����擾
	void InitNone();		// �Œ�J����������
	void InitFollow();		// �Ǐ]�J����������
	void ResetSwing();		// �J�����h�ꏉ����

	void SetState(const EState state, const bool bInit = true);	// �J������Ԑݒ�
	EState GetState() const;					// �J������Ԏ擾
	void SetSwing(const SSwing swing);			// �J�����h��ݒ�
	void SetEnableUpdate(const bool bUpdate);	// �X�V�󋵐ݒ�
	void SetPositionV(const VECTOR3& rPos);		// ���_�ݒ�
	void SetPositionR(const VECTOR3& rPos);		// �����_�ݒ�
	void SetRotation(const VECTOR3& rRot);		// �����ݒ�
	void SetDistance(const float fDis);			// �����ݒ�
	inline VECTOR3 GetPositionV() const		{ return m_camera.posV; }		// ���݂̎��_�擾
	inline VECTOR3 GetDestPositionV() const	{ return m_camera.destPosV; }	// �ڕW�̎��_�擾
	inline VECTOR3 GetPositionR() const		{ return m_camera.posR; }		// ���݂̒����_�擾
	inline VECTOR3 GetDestPositionR() const	{ return m_camera.destPosR; }	// �ڕW�̒����_�擾
	inline VECTOR3 GetRotation() const		{ return m_camera.rot; }		// ���݂̌����擾
	inline VECTOR3 GetDestRotation() const	{ return m_camera.destRot; }	// �ڕW�̌����擾
	inline float GetDistance() const		{ return m_camera.fDis; }		// ���݂̋����擾
	inline float GetDestDistance() const	{ return m_camera.fDestDis; }	// �ڕW�̋����擾

	// �ÓI�����o�֐�
	static CCamera* Create();					// ����
	static void Release(CCamera*& prCamera);	// �j��

private:
	// �����o�֐�
	void UpdateNone();		// �Œ�J�����X�V
	void UpdateFollow();	// �Ǐ]�J�����X�V
	void UpdateControl();	// ����J�����X�V
	void UpdateMove();		// �ʒu�X�V
	void UpdateDistance();	// �����X�V
	void UpdateRotation();	// �����X�V
	void UpdateSwing();		// �J�����h��X�V

	// �����o�ϐ�
	SCamera	m_camera;	// �J�������
	EState	m_state;	// ���
	bool	m_bUpdate;	// �X�V��
};

#endif	// _CAMERA_H_
