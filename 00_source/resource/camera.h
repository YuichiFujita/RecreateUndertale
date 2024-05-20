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
	// �J������
	enum EType
	{
		TYPE_MAIN = 0,	// ���C���J����
		TYPE_MODELUI,	// ���f��UI�\���J����
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,	// �Ȃɂ����Ȃ����
		STATE_CONTROL,	// ������
		STATE_ROTATE,	// ��]���
		STATE_FOLLOW,	// �Ǐ]���
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
		SSwing() {}
		SSwing(const float ShiftLength, const float SubAngle, const float SubLength)
		{
			shiftPos		= VEC3_ZERO;	// �ʒu�����
			fShiftAngle		= 0.0f;			// �ʒu�����炷�p�x
			fShiftLength	= ShiftLength;	// �ʒu�����炷����
			fSubAngle		= SubAngle;		// ���炷�p�x�̌��Z��
			fSubLength		= SubLength;	// ���炷�����̌��Z��
		}

		// �f�X�g���N�^
		~SSwing() {}

		// �����o�ϐ�
		D3DXVECTOR3	shiftPos;		// �ʒu�����
		float		fShiftAngle;	// �ʒu�����炷�p�x
		float		fShiftLength;	// �ʒu�����炷����
		float		fSubAngle;		// ���炷�p�x�̌��Z��
		float		fSubLength;		// ���炷�����̌��Z��
	};

	// �J�����\����
	struct SCamera
	{
		D3DXVECTOR3		posV;			// ���݂̎��_
		D3DXVECTOR3		posR;			// ���݂̒����_
		D3DXVECTOR3		destPosV;		// �ڕW�̎��_
		D3DXVECTOR3		destPosR;		// �ڕW�̒����_
		D3DXVECTOR3		vecU;			// ������x�N�g��
		D3DXVECTOR3		rot;			// ���݂̌���
		D3DXVECTOR3		destRot;		// �ڕW�̌���
		float			fDis;			// ���݂̎��_�ƒ����_�̋���
		float			fDestDis;		// �ڕW�̎��_�ƒ����_�̋���
		SSwing			swingInfo;		// �J�����h����
		D3DVIEWPORT9	viewportInfo;	// �r���[�|�[�g���
		D3DXMATRIX		mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX		mtxView;		// �r���[�}�g���b�N�X
	};

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);	// �X�V
	void Reset(void);						// �Đݒ�
	void SetCamera(const EType type);		// �J�����ݒ�
	SCamera GetCamera(const EType type);	// �J�����擾
	void SetState(const EState state);		// �J������Ԑݒ�
	EState GetState(void) const;			// �J������Ԏ擾
	void SetSwing(const EType type, const SSwing swing);	// �J�����h��ݒ�
	void SetEnableUpdate(const bool bUpdate);				// �X�V�󋵐ݒ�

	void SetDestRotate(void);	// �J�����ڕW�ʒu�ݒ� (��])
	void SetDestFollow(void);	// �J�����ڕW�ʒu�ݒ� (�Ǐ])
	void SetPositionV(const D3DXVECTOR3& rPos);	// ���_�ݒ�
	void SetPositionR(const D3DXVECTOR3& rPos);	// �����_�ݒ�
	void SetRotation(const D3DXVECTOR3& rRot);	// �����ݒ�
	void SetDistance(const float fDis);			// �����ݒ�
	D3DXVECTOR3 GetPositionV(void) const		{ return m_aCamera[TYPE_MAIN].posV; }		// ���݂̎��_�擾
	D3DXVECTOR3 GetDestPositionV(void) const	{ return m_aCamera[TYPE_MAIN].destPosV; }	// �ڕW�̎��_�擾
	D3DXVECTOR3 GetPositionR(void) const		{ return m_aCamera[TYPE_MAIN].posR; }		// ���݂̒����_�擾
	D3DXVECTOR3 GetDestPositionR(void) const	{ return m_aCamera[TYPE_MAIN].destPosR; }	// �ڕW�̒����_�擾
	D3DXVECTOR3 GetRotation(void) const			{ return m_aCamera[TYPE_MAIN].rot; }		// ���݂̌����擾
	D3DXVECTOR3 GetDestRotation(void) const		{ return m_aCamera[TYPE_MAIN].destRot; }	// �ڕW�̌����擾
	float GetDistance(void) const				{ return m_aCamera[TYPE_MAIN].fDis; }		// ���݂̋����擾
	float GetDestDistance(void) const			{ return m_aCamera[TYPE_MAIN].fDestDis; }	// �ڕW�̋����擾

	// �ÓI�����o�֐�
	static CCamera *Create(void);				// ����
	static void Release(CCamera *&prCamera);	// �j��

private:
	// �����o�֐�
	void Rotate(void);		// �J�����̍X�V (��])
	void Follow(void);		// �J�����̍X�V (�Ǐ])
	void Control(void);		// �J�����̍X�V (����)
	void Move(void);		// �ʒu�̍X�V (����)
	void Distance(void);	// �����̍X�V (����)
	void Rotation(void);	// �����̍X�V (����)
	void Swing(void);		// �J�����h��̍X�V

	// �����o�ϐ�
	SCamera	m_aCamera[TYPE_MAX];	// �J�����̏��
	EState	m_state;	// ���
	bool	m_bUpdate;	// �X�V��
};

#endif	// _CAMERA_H_
