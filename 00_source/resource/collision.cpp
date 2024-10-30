//============================================================
//
//	����֐����� [collision.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "collision.h"

//============================================================
//	XY���ʂ̋�`�̓����蔻��
//============================================================
bool collision::BoxXY
(
	const VECTOR3& rCenterPos,		// ����ʒu
	const VECTOR3& rTargetPos,		// ����ڕW�ʒu
	const VECTOR3& rCenterSizeUp,	// ����傫�� (�E/��/��)
	const VECTOR3& rCenterSizeDown,	// ����傫�� (��/��/�O)
	const VECTOR3& rTargetSizeUp,	// ����ڕW�傫�� (�E/��/��)
	const VECTOR3& rTargetSizeDown	// ����ڕW�傫�� (��/��/�O)
)
{
	if (rCenterPos.x + rCenterSizeUp.x   > rTargetPos.x - rTargetSizeDown.x
	&&  rCenterPos.y + rCenterSizeUp.y   > rTargetPos.y - rTargetSizeDown.y
	&&  rCenterPos.x - rCenterSizeDown.x < rTargetPos.x + rTargetSizeUp.x
	&&  rCenterPos.y - rCenterSizeDown.y < rTargetPos.y + rTargetSizeUp.y)
	{ // ������̏ꍇ

		return true;
	}

	return false;
}

//============================================================
//	XZ���ʂ̋�`�̓����蔻��
//============================================================
bool collision::BoxXZ
(
	const VECTOR3& rCenterPos,		// ����ʒu
	const VECTOR3& rTargetPos,		// ����ڕW�ʒu
	const VECTOR3& rCenterSizeUp,	// ����傫�� (�E/��/��)
	const VECTOR3& rCenterSizeDown,	// ����傫�� (��/��/�O)
	const VECTOR3& rTargetSizeUp,	// ����ڕW�傫�� (�E/��/��)
	const VECTOR3& rTargetSizeDown	// ����ڕW�傫�� (��/��/�O)
)
{
	if (rCenterPos.x + rCenterSizeUp.x   > rTargetPos.x - rTargetSizeDown.x
	&&  rCenterPos.z + rCenterSizeUp.z   > rTargetPos.z - rTargetSizeDown.z
	&&  rCenterPos.x - rCenterSizeDown.x < rTargetPos.x + rTargetSizeUp.x
	&&  rCenterPos.z - rCenterSizeDown.z < rTargetPos.z + rTargetSizeUp.z)
	{ // ������̏ꍇ

		return true;
	}

	return false;
}

//============================================================
//	3���̋�`�̓����蔻��
//============================================================
bool collision::Box3D
(
	VECTOR3 centerPos,		// ����ʒu
	VECTOR3 targetPos,		// ����ڕW�ʒu
	VECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	VECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	VECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	VECTOR3 targetSizeDown	// ����ڕW�T�C�Y(���E���E�O)
)
{
	if (centerPos.x + centerSizeUp.x   > targetPos.x - targetSizeDown.x
	&&  centerPos.y + centerSizeUp.y   > targetPos.y - targetSizeDown.y
	&&  centerPos.z + centerSizeUp.z   > targetPos.z - targetSizeDown.z
	&&  centerPos.x - centerSizeDown.x < targetPos.x + targetSizeUp.x
	&&  centerPos.y - centerSizeDown.y < targetPos.y + targetSizeUp.y
	&&  centerPos.z - centerSizeDown.z < targetPos.z + targetSizeUp.z)
	{ // ������̏ꍇ

		return true;
	}

	return false;
}

//============================================================
//	XZ���ʂ̉~�̓����蔻��
//============================================================
bool collision::Circle2D
(
	VECTOR3 centerPos,		// ����ʒu
	VECTOR3 targetPos,		// ����ڕW�ʒu
	float fCenterRadius,	// ���蔼�a
	float fTargetRadius,	// ����ڕW���a
	float* pLength			// ����ڕW�Ƃ̋���
)
{
	// ����ʒu�Ɣ���ڕW�ʒu�̋��������߂�
	float fLength = (centerPos.x - targetPos.x) * (centerPos.x - targetPos.x)
				  + (centerPos.z - targetPos.z) * (centerPos.z - targetPos.z);

	if (pLength != nullptr)
	{ // �|�C���^���g�p����Ă���ꍇ

		// ����ڕW�Ƃ̋�������
		*pLength = fLength;
	}

	if (fLength < ((fCenterRadius + fTargetRadius) * (fCenterRadius + fTargetRadius)))
	{ // ������̏ꍇ

		return true;
	}

	return false;
}

//============================================================
//	3���̉~�̓����蔻��
//============================================================
bool collision::Circle3D
(
	VECTOR3 centerPos,		// ����ʒu
	VECTOR3 targetPos,		// ����ڕW�ʒu
	float fCenterRadius,	// ���蔼�a
	float fTargetRadius		// ����ڕW���a
)
{
	// ����ʒu�Ɣ���ڕW�ʒu�̋��������߂�
	float fLength = (centerPos.x - targetPos.x) * (centerPos.x - targetPos.x)
				  + (centerPos.y - targetPos.y) * (centerPos.y - targetPos.y)
				  + (centerPos.z - targetPos.z) * (centerPos.z - targetPos.z);

	if (fLength < ((fCenterRadius + fTargetRadius) * (fCenterRadius + fTargetRadius)))
	{ // ������̏ꍇ

		return true;
	}

	return false;
}

//============================================================
//	XZ���ʂ̐�`�̓����蔻��
//============================================================
bool collision::Sector
(
	VECTOR3 centerPos,	// ����ʒu
	VECTOR3 targetPos,	// ����ڕW�ʒu
	float fCenterRot,	// �������
	float fRadius,		// ���E�͈�
	float fAngle,		// ����p
	float* pLength		// ����ڕW�Ƃ̋���
)
{
	bool bHit = false;	// �����蔻��̌���

	// ���S�ʒu�ƖڕW�ʒu�̋������߂�
	float fLength = (centerPos.x - targetPos.x) * (centerPos.x - targetPos.x)
				  + (centerPos.z - targetPos.z) * (centerPos.z - targetPos.z);

	if (pLength != nullptr)
	{ // �|�C���^���g�p����Ă���ꍇ

		// ����ڕW�Ƃ̋�������
		*pLength = fLength;
	}

	if (fLength < fRadius * fRadius)
	{ // �~�͈͓̔��̏ꍇ

		float fRotEdge[2];	// ��`�̉��̊p�x     [��] 0�F�� 1�F�E
		VECTOR3 posEdge[2];	// ��`�̉��̐�[�ʒu [��] 0�F�� 1�F�E
		VECTOR3 vecEdge[2];	// ��`�̉��x�N�g��   [��] 0�F�� 1�F�E

		// �����̊p�x�̔����̒l�����߂�
		float fHalfAngle = fAngle * 0.5f;

		// ��`�̍����̊p�x�����߂�
		fRotEdge[0] = fCenterRot + fHalfAngle;	// �p�x�����ɌX����
		useful::NormalizeRot(fRotEdge[0]);		// �����𐳋K��

		// ��`�̉E���̊p�x�����߂�
		fRotEdge[1] = fCenterRot - fHalfAngle;	// �p�x���E�ɌX����
		useful::NormalizeRot(fRotEdge[1]);		// �����𐳋K��

		// ��`�̍����̐�[�ʒu�����߂�
		posEdge[0].x = centerPos.x + sinf(fRotEdge[0]);
		posEdge[0].y = 0.0f;
		posEdge[0].z = centerPos.z + cosf(fRotEdge[0]);

		// ��`�̉E���̐�[�ʒu�����߂�
		posEdge[1].x = centerPos.x + sinf(fRotEdge[1]);
		posEdge[1].y = 0.0f;
		posEdge[1].z = centerPos.z + cosf(fRotEdge[1]);

		// ��`�̍����̃x�N�g�������߂�
		vecEdge[0] = posEdge[0] - centerPos;
		vecEdge[0].y = 0.0f;

		// ��`�̉E���̃x�N�g�������߂�
		vecEdge[1] = posEdge[1] - centerPos;
		vecEdge[1].y = 0.0f;

		// ���[�ƈʒu�̃x�N�g�������߂�
		VECTOR3 vecToPos = targetPos - centerPos;

		if ((vecEdge[0].z * vecToPos.x) - (vecEdge[0].x * vecToPos.z) < 0
		&&  (vecEdge[1].z * vecToPos.x) - (vecEdge[1].x * vecToPos.z) > 0)
		{ // ��`�̗����͈͓̔��̏ꍇ

			// �������Ă����Ԃɂ���
			bHit = true;
		}
	}

	// �����蔻��̌��ʂ�Ԃ�
	return bHit;
}

//============================================================
//	XY���ʂ̊p���̏Փ˔���
//============================================================
bool collision::ResponseBoxPillarXY
(
	VECTOR3& rCenterPos,			// ����ʒu
	const VECTOR3& rCenterPosOld,	// ����ߋ��ʒu
	const VECTOR3& rTargetPos,		// ����ڕW�ʒu
	const VECTOR3& rCenterSizeUp,	// ����傫�� (�E/��/��)
	const VECTOR3& rCenterSizeDown,	// ����傫�� (��/��/�O)
	const VECTOR3& rTargetSizeUp,	// ����ڕW�傫�� (�E/��/��)
	const VECTOR3& rTargetSizeDown	// ����ڕW�傫�� (��/��/�O)
)
{
	bool bHit = false;	// �Փ˔��茋��

	// ���E�̓����蔻��
	if (rCenterPos.y + rCenterSizeUp.y > rTargetPos.y - rTargetSizeDown.y
	&&  rCenterPos.y - rCenterSizeDown.y < rTargetPos.y + rTargetSizeUp.y)
	{ // �O��͈͓̔��̏ꍇ

		if (rCenterPos.x    + rCenterSizeUp.x >  rTargetPos.x - rTargetSizeDown.x
		&&  rCenterPosOld.x + rCenterSizeUp.x <= rTargetPos.x - rTargetSizeDown.x)
		{ // ������̓����蔻��

			// �ʒu��␳
			rCenterPos.x = rTargetPos.x - rTargetSizeDown.x - rCenterSizeUp.x;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
		else if (rCenterPos.x    - rCenterSizeDown.x <  rTargetPos.x + rTargetSizeUp.x
		     &&  rCenterPosOld.x - rCenterSizeDown.x >= rTargetPos.x + rTargetSizeUp.x)
		{ // �E����̓����蔻��
			
			// �ʒu��␳
			rCenterPos.x = rTargetPos.x + rTargetSizeUp.x + rCenterSizeDown.x;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
	}

	// �㉺�̓����蔻��
	if (rCenterPos.x + rCenterSizeUp.x > rTargetPos.x - rTargetSizeDown.x
	&&  rCenterPos.x - rCenterSizeDown.x < rTargetPos.x + rTargetSizeUp.x)
	{ // ���E�͈͓̔��̏ꍇ

		if (rCenterPos.y    + rCenterSizeUp.y >  rTargetPos.y - rTargetSizeDown.y
		&&  rCenterPosOld.y + rCenterSizeUp.y <= rTargetPos.y - rTargetSizeDown.y)
		{ // �O����̓����蔻��

			// �ʒu��␳
			rCenterPos.y = rTargetPos.y - rTargetSizeDown.y - rCenterSizeUp.y;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
		else if (rCenterPos.y    - rCenterSizeDown.y <  rTargetPos.y + rTargetSizeUp.y
		     &&  rCenterPosOld.y - rCenterSizeDown.y >= rTargetPos.y + rTargetSizeUp.y)
		{ // �ォ��̓����蔻��

			// �ʒu��␳
			rCenterPos.y = rTargetPos.y + rTargetSizeUp.y + rCenterSizeDown.y;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	XZ���ʂ̊p���̏Փ˔���
//============================================================
bool collision::ResponseBoxPillarXZ
(
	VECTOR3& rCenterPos,			// ����ʒu
	const VECTOR3& rCenterPosOld,	// ����ߋ��ʒu
	const VECTOR3& rTargetPos,		// ����ڕW�ʒu
	const VECTOR3& rCenterSizeUp,	// ����傫�� (�E/��/��)
	const VECTOR3& rCenterSizeDown,	// ����傫�� (��/��/�O)
	const VECTOR3& rTargetSizeUp,	// ����ڕW�傫�� (�E/��/��)
	const VECTOR3& rTargetSizeDown	// ����ڕW�傫�� (��/��/�O)
)
{
	bool bHit = false;	// �Փ˔��茋��

	// �O��̓����蔻��
	if (rCenterPos.x + rCenterSizeUp.x > rTargetPos.x - rTargetSizeDown.x
	&&  rCenterPos.x - rCenterSizeDown.x < rTargetPos.x + rTargetSizeUp.x)
	{ // ���E�͈͓̔��̏ꍇ

		if (rCenterPos.z    + rCenterSizeUp.z >  rTargetPos.z - rTargetSizeDown.z
		&&  rCenterPosOld.z + rCenterSizeUp.z <= rTargetPos.z - rTargetSizeDown.z)
		{ // �O����̓����蔻��

			// �ʒu��␳
			rCenterPos.z = rTargetPos.z - rTargetSizeDown.z - rCenterSizeUp.z;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
		else if (rCenterPos.z    - rCenterSizeDown.z <  rTargetPos.z + rTargetSizeUp.z
		     &&  rCenterPosOld.z - rCenterSizeDown.z >= rTargetPos.z + rTargetSizeUp.z)
		{ // �ォ��̓����蔻��

			// �ʒu��␳
			rCenterPos.z = rTargetPos.z + rTargetSizeUp.z + rCenterSizeDown.z;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
	}

	// ���E�̓����蔻��
	if (rCenterPos.z + rCenterSizeUp.z > rTargetPos.z - rTargetSizeDown.z
	&&  rCenterPos.z - rCenterSizeDown.z < rTargetPos.z + rTargetSizeUp.z)
	{ // �O��͈͓̔��̏ꍇ

		if (rCenterPos.x    + rCenterSizeUp.x >  rTargetPos.x - rTargetSizeDown.x
		&&  rCenterPosOld.x + rCenterSizeUp.x <= rTargetPos.x - rTargetSizeDown.x)
		{ // ������̓����蔻��

			// �ʒu��␳
			rCenterPos.x = rTargetPos.x - rTargetSizeDown.x - rCenterSizeUp.x;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
		else if (rCenterPos.x    - rCenterSizeDown.x <  rTargetPos.x + rTargetSizeUp.x
		     &&  rCenterPosOld.x - rCenterSizeDown.x >= rTargetPos.x + rTargetSizeUp.x)
		{ // �E����̓����蔻��
			
			// �ʒu��␳
			rCenterPos.x = rTargetPos.x + rTargetSizeUp.x + rCenterSizeDown.x;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	�~���̏Փ˔���
//============================================================
bool collision::CirclePillar
(
	VECTOR3& rCenterPos,	// ����ʒu
	VECTOR3 targetPos,		// ����ڕW�ʒu
	float fCenterRadius,	// ���蔼�a
	float fTargetRadius		// ����ڕW���a
)
{
	// ����ʒu�Ɣ���ڕW�ʒu�̋��������߂�
	float fLength = (rCenterPos.x - targetPos.x) * (rCenterPos.x - targetPos.x)
				  + (rCenterPos.z - targetPos.z) * (rCenterPos.z - targetPos.z);

	if (fLength < (fCenterRadius + fTargetRadius) * (fCenterRadius + fTargetRadius))
	{ // ������̏ꍇ

		// �ʒu��␳
		float fCenterRot = atan2f(rCenterPos.x - targetPos.x, rCenterPos.z - targetPos.z);	// ����ڕW���猩���������
		rCenterPos.x = targetPos.x + sinf(fCenterRot) * (fCenterRadius + fTargetRadius);
		rCenterPos.z = targetPos.z + cosf(fCenterRot) * (fCenterRadius + fTargetRadius);

		return true;
	}

	return false;
}

//============================================================
//	�O���̋�`�̏Փ˔���
//============================================================
bool collision::ResponseBox3D
(
	VECTOR3& rCenterPos,			// ����ʒu
	const VECTOR3& rCenterPosOld,	// ����ߋ��ʒu
	const VECTOR3& rTargetPos,		// ����ڕW�ʒu
	const VECTOR3& rCenterSizeUp,	// ����T�C�Y(�E�E��E��)
	const VECTOR3& rCenterSizeDown,	// ����T�C�Y(���E���E�O)
	const VECTOR3& rTargetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	const VECTOR3& rTargetSizeDown,	// ����ڕW�T�C�Y(���E���E�O)
	VECTOR3* pMove,	// �ړ���
	bool* pUp,		// �ォ��̔���
	bool* pSide,	// ������̔���
	bool* pDown		// ������̔���
)
{
	// ���E�̓����蔻��
	bool bHit = false;	// �Փ˔��茋��
	if (rCenterPos.y + rCenterSizeUp.y   > rTargetPos.y - rTargetSizeDown.y
	&&  rCenterPos.y - rCenterSizeDown.y < rTargetPos.y + rTargetSizeUp.y
	&&  rCenterPos.z + rCenterSizeUp.z   > rTargetPos.z - rTargetSizeDown.z
	&&  rCenterPos.z - rCenterSizeDown.z < rTargetPos.z + rTargetSizeUp.z)
	{ // �㉺�ƑO��͈͓̔��̏ꍇ

		if (rCenterPos.x    + rCenterSizeUp.x >  rTargetPos.x - rTargetSizeDown.x
		&&  rCenterPosOld.x + rCenterSizeUp.x <= rTargetPos.x - rTargetSizeDown.x)
		{ // ������̓����蔻��

			// �ʒu��␳
			rCenterPos.x = rTargetPos.x - rTargetSizeDown.x - rCenterSizeUp.x;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->x = 0.0f;
			}

			if (pSide != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pSide = true;
			}
		}
		else if (rCenterPos.x    - rCenterSizeDown.x <  rTargetPos.x + rTargetSizeUp.x
		     &&  rCenterPosOld.x - rCenterSizeDown.x >= rTargetPos.x + rTargetSizeUp.x)
		{ // �E����̓����蔻��
			
			// �ʒu��␳
			rCenterPos.x = rTargetPos.x + rTargetSizeUp.x + rCenterSizeDown.x;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->x = 0.0f;
			}

			if (pSide != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pSide = true;
			}
		}
	}

	// �㉺�̓����蔻��
	if (rCenterPos.x + rCenterSizeUp.x   > rTargetPos.x - rTargetSizeDown.x
	&&  rCenterPos.x - rCenterSizeDown.x < rTargetPos.x + rTargetSizeUp.x
	&&  rCenterPos.z + rCenterSizeUp.z   > rTargetPos.z - rTargetSizeDown.z
	&&  rCenterPos.z - rCenterSizeDown.z < rTargetPos.z + rTargetSizeUp.z)
	{ // ���E�ƑO��͈͓̔��̏ꍇ

		if (rCenterPos.y    + rCenterSizeUp.y >  rTargetPos.y - rTargetSizeDown.y
		&&  rCenterPosOld.y + rCenterSizeUp.y <= rTargetPos.y - rTargetSizeDown.y)
		{ // ������̓����蔻��

			// �ʒu��␳
			rCenterPos.y = rTargetPos.y - rTargetSizeDown.y - rCenterSizeUp.y;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->y = 0.0f;
			}

			if (pDown != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pDown = true;
			}
		}
		else if (rCenterPos.y    - rCenterSizeDown.y <  rTargetPos.y + rTargetSizeUp.y
		     &&  rCenterPosOld.y - rCenterSizeDown.y >= rTargetPos.y + rTargetSizeUp.y)
		{ // �ォ��̓����蔻��
			
			// �ʒu��␳
			rCenterPos.y = rTargetPos.y + rTargetSizeUp.y + rCenterSizeDown.y;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->y = 0.0f;
			}

			if (pUp != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ��ɓ������Ă����Ԃ�ݒ�
				*pUp = true;
			}
		}
	}

	// �O��̓����蔻��
	if (rCenterPos.x + rCenterSizeUp.x   > rTargetPos.x - rTargetSizeDown.x
	&&  rCenterPos.x - rCenterSizeDown.x < rTargetPos.x + rTargetSizeUp.x
	&&  rCenterPos.y + rCenterSizeUp.y   > rTargetPos.y - rTargetSizeDown.y
	&&  rCenterPos.y - rCenterSizeDown.y < rTargetPos.y + rTargetSizeUp.y)
	{ // ���E�Ə㉺�͈͓̔��̏ꍇ

		if (rCenterPos.z    + rCenterSizeUp.z >  rTargetPos.z - rTargetSizeDown.z
		&&  rCenterPosOld.z + rCenterSizeUp.z <= rTargetPos.z - rTargetSizeDown.z)
		{ // �O����̓����蔻��

			// �ʒu��␳
			rCenterPos.z = rTargetPos.z - rTargetSizeDown.z - rCenterSizeUp.z;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->z = 0.0f;
			}

			if (pSide != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pSide = true;
			}
		}
		else if (rCenterPos.z    - rCenterSizeDown.z <  rTargetPos.z + rTargetSizeUp.z
		     &&  rCenterPosOld.z - rCenterSizeDown.z >= rTargetPos.z + rTargetSizeUp.z)
		{ // �ォ��̓����蔻��

			// �ʒu��␳
			rCenterPos.z = rTargetPos.z + rTargetSizeUp.z + rCenterSizeDown.z;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->z = 0.0f;
			}

			if (pSide != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pSide = true;
			}
		}
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	�O���̉~�̏Փ˔���
//============================================================
bool collision::ResponseCircle3D
(
	VECTOR3& rCenterPos,	// ����ʒu
	VECTOR3 targetPos,		// ����ڕW�ʒu
	float fCenterRadius,	// ���蔼�a
	float fTargetRadius		// ����ڕW���a
)
{
	// ����ʒu�Ɣ���ڕW�ʒu�̋��������߂�
	float fLength = (rCenterPos.x - targetPos.x) * (rCenterPos.x - targetPos.x)
				  + (rCenterPos.y - targetPos.y) * (rCenterPos.y - targetPos.y)
				  + (rCenterPos.z - targetPos.z) * (rCenterPos.z - targetPos.z);

	if (fLength < ((fCenterRadius + fTargetRadius) * (fCenterRadius + fTargetRadius)))
	{ // ������̏ꍇ

		VECTOR3 vecRev = rCenterPos - targetPos;	// �␳����
		VECTOR3 sphere;	// �����W
		float fPhi, fTheta;	// ���ʊp�E�p

		// �x�N�g���������ɕϊ����A�������狅���W�����߂�
		useful::VecToRot(vecRev, &fPhi, &fTheta);
		useful::RotToVec(fPhi, fTheta, &sphere);

		// �ʒu��␳
		rCenterPos = targetPos + sphere * (fCenterRadius + fTargetRadius);

		return true;
	}

	return false;
}

//============================================================
//	�O���̃J�v�Z���̏Փ˔���
//============================================================
bool collision::ResponseCapsule3D
(
	VECTOR3* pCenterPos,	// ����ʒu
	VECTOR3& rTargetPos,	// ����ڕW�ʒu
	float fCenterRadius,	// ���蔼�a
	float fTargetRadius,	// ����ڕW���a
	float fTargetHeight		// ����ڕW�c��
)
{
	bool bHit = false;	// �Փ˔��茋��
	float fHalfHeight = (fTargetHeight - (fTargetRadius * 2.0f)) * 0.5f;	// �~���c���̔���
	VECTOR3 centUp   = *pCenterPos + VECTOR3(0.0f, fCenterRadius, 0.0f);	// ����ʒu�̏�
	VECTOR3 centDown = *pCenterPos - VECTOR3(0.0f, fCenterRadius, 0.0f);	// ����ʒu�̉�
	VECTOR3 targUp   = rTargetPos + VECTOR3(0.0f, fHalfHeight, 0.0f);		// ����ڕW�ʒu�̏�
	VECTOR3 targDown = rTargetPos - VECTOR3(0.0f, fHalfHeight, 0.0f);		// ����ڕW�ʒu�̉�
	if (centDown.y >= targUp.y)
	{ // �~������̏㑤�ɂ���ꍇ

		// ��̋�����
		bHit = collision::ResponseCircle3D
		( // ����
			*pCenterPos,	// ����ʒu
			targUp,			// ����ڕW�ʒu
			fCenterRadius,	// ���蔼�a
			fTargetRadius	// ����ڕW���a
		);
	}
	else if (centUp.y <= targDown.y)
	{ // �~������̉����ɂ���ꍇ

		// ���̋�����
		bHit = collision::ResponseCircle3D
		( // ����
			*pCenterPos,	// ����ʒu
			targDown,		// ����ڕW�ʒu
			fCenterRadius,	// ���蔼�a
			fTargetRadius	// ����ڕW���a
		);
	}
	else
	{ // �㉺�͈͓̔��̏ꍇ

		// �~���̔���
		bHit = collision::CirclePillar
		( // ����
			*pCenterPos,	// ����ʒu
			rTargetPos,		// ����ڕW�ʒu
			fCenterRadius,	// ���蔼�a
			fTargetRadius	// ����ڕW���a
		);
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	X���̏Փ˔���
//============================================================
bool collision::ResponseSingleX
(
	VECTOR3& rCenterPos,	// ����ʒu
	VECTOR3& rCenterPosOld,	// ����ߋ��ʒu
	VECTOR3 targetPos,		// ����ڕW�ʒu
	VECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	VECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	VECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	VECTOR3 targetSizeDown,	// ����ڕW�T�C�Y(���E���E�O)
	VECTOR3* pMove,	// �ړ���
	bool* pLeft,	// ������̔���
	bool* pRight	// �E����̔���
)
{
	// ���E�̓����蔻��
	bool bHit = false;	// �Փ˔��茋��
	if (rCenterPos.y + centerSizeUp.y   > targetPos.y - targetSizeDown.y
	&&  rCenterPos.y - centerSizeDown.y < targetPos.y + targetSizeUp.y
	&&  rCenterPos.z + centerSizeUp.z   > targetPos.z - targetSizeDown.z
	&&  rCenterPos.z - centerSizeDown.z < targetPos.z + targetSizeUp.z)
	{ // �㉺�ƑO��͈͓̔��̏ꍇ

		if (rCenterPos.x    + centerSizeUp.x >  targetPos.x - targetSizeDown.x
		&&  rCenterPosOld.x + centerSizeUp.x <= targetPos.x - targetSizeDown.x)
		{ // ������̓����蔻��

			// �ʒu��␳
			rCenterPos.x = targetPos.x - targetSizeDown.x - centerSizeUp.x;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->x = 0.0f;
			}

			if (pLeft != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pLeft = true;
			}
		}
		else if (rCenterPos.x    - centerSizeDown.x <  targetPos.x + targetSizeUp.x
		     &&  rCenterPosOld.x - centerSizeDown.x >= targetPos.x + targetSizeUp.x)
		{ // �E����̓����蔻��
			
			// �ʒu��␳
			rCenterPos.x = targetPos.x + targetSizeUp.x + centerSizeDown.x;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->x = 0.0f;
			}

			if (pRight != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �E�ɓ������Ă����Ԃ�ݒ�
				*pRight = true;
			}
		}
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	Y���̏Փ˔���
//============================================================
bool collision::ResponseSingleY
(
	VECTOR3& rCenterPos,	// ����ʒu
	VECTOR3& rCenterPosOld,	// ����ߋ��ʒu
	VECTOR3 targetPos,		// ����ڕW�ʒu
	VECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	VECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	VECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	VECTOR3 targetSizeDown,	// ����ڕW�T�C�Y(���E���E�O)
	VECTOR3* pMove,	// �ړ���
	bool* pDown,	// ������̔���
	bool* pUp		// �ォ��̔���
)
{
	// �㉺�̓����蔻��
	bool bHit = false;	// �Փ˔��茋��
	if (rCenterPos.x + centerSizeUp.x   > targetPos.x - targetSizeDown.x
	&&  rCenterPos.x - centerSizeDown.x < targetPos.x + targetSizeUp.x
	&&  rCenterPos.z + centerSizeUp.z   > targetPos.z - targetSizeDown.z
	&&  rCenterPos.z - centerSizeDown.z < targetPos.z + targetSizeUp.z)
	{ // ���E�ƑO��͈͓̔��̏ꍇ

		if (rCenterPos.y    + centerSizeUp.y >  targetPos.y - targetSizeDown.y
		&&  rCenterPosOld.y + centerSizeUp.y <= targetPos.y - targetSizeDown.y)
		{ // ������̓����蔻��

			// �ʒu��␳
			rCenterPos.y = targetPos.y - targetSizeDown.y - centerSizeUp.y;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->y = 0.0f;
			}

			if (pDown != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pDown = true;
			}
		}
		else if (rCenterPos.y    - centerSizeDown.y <  targetPos.y + targetSizeUp.y
		     &&  rCenterPosOld.y - centerSizeDown.y >= targetPos.y + targetSizeUp.y)
		{ // �ォ��̓����蔻��
			
			// �ʒu��␳
			rCenterPos.y = targetPos.y + targetSizeUp.y + centerSizeDown.y;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->y = 0.0f;
			}

			if (pUp != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ��ɓ������Ă����Ԃ�ݒ�
				*pUp = true;
			}
		}
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	Z���̏Փ˔���
//============================================================
bool collision::ResponseSingleZ
(
	VECTOR3& rCenterPos,	// ����ʒu
	VECTOR3& rCenterPosOld,	// ����ߋ��ʒu
	VECTOR3 targetPos,		// ����ڕW�ʒu
	VECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	VECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	VECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	VECTOR3 targetSizeDown,	// ����ڕW�T�C�Y(���E���E�O)
	VECTOR3* pMove,	// �ړ���
	bool* pBefore,	// �O����̔���
	bool* pAfter	// �ォ��̔���
)
{
	// �O��̓����蔻��
	bool bHit = false;	// �Փ˔��茋��
	if (rCenterPos.x + centerSizeUp.x   > targetPos.x - targetSizeDown.x
	&&  rCenterPos.x - centerSizeDown.x < targetPos.x + targetSizeUp.x
	&&  rCenterPos.y + centerSizeUp.y   > targetPos.y - targetSizeDown.y
	&&  rCenterPos.y - centerSizeDown.y < targetPos.y + targetSizeUp.y)
	{ // ���E�Ə㉺�͈͓̔��̏ꍇ

		if (rCenterPos.z    + centerSizeUp.z >  targetPos.z - targetSizeDown.z
		&&  rCenterPosOld.z + centerSizeUp.z <= targetPos.z - targetSizeDown.z)
		{ // �O����̓����蔻��

			// �ʒu��␳
			rCenterPos.z = targetPos.z - targetSizeDown.z - centerSizeUp.z;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->z = 0.0f;
			}

			if (pBefore != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �O�ɓ������Ă����Ԃ�ݒ�
				*pBefore = true;
			}
		}
		else if (rCenterPos.z    - centerSizeDown.z <  targetPos.z + targetSizeUp.z
		     &&  rCenterPosOld.z - centerSizeDown.z >= targetPos.z + targetSizeUp.z)
		{ // �ォ��̓����蔻��

			// �ʒu��␳
			rCenterPos.z = targetPos.z + targetSizeUp.z + centerSizeDown.z;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->z = 0.0f;
			}

			if (pAfter != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ��ɓ������Ă����Ԃ�ݒ�
				*pAfter = true;
			}
		}
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	XY���ʊp���̓�������
//============================================================
bool collision::InBoxPillarXY
(
	VECTOR3& rCenterPos,			// ����ʒu
	const VECTOR3& rOriginPos,		// ���茴�_�ʒu
	const VECTOR3& rCenterSizeUp,	// ����T�C�Y(�E�E��E��)
	const VECTOR3& rCenterSizeDown,	// ����T�C�Y(���E���E�O)
	const VECTOR3& rOriginSizeUp,	// ���茴�_�T�C�Y(�E�E��E��)
	const VECTOR3& rOriginSizeDown	// ���茴�_�T�C�Y(���E���E�O)
)
{
	bool bHit = false;	// ���茋��

	// ���E�̕␳
	if (useful::LimitNum(rCenterPos.x, rOriginPos.x - rOriginSizeDown.x + rCenterSizeUp.x, rOriginPos.x + rOriginSizeUp.x - rCenterSizeDown.x))
	{ // �␳���s��ꂽ�ꍇ

		// ���肵����Ԃɂ���
		bHit = true;
	}

	// �㉺�̕␳
	if (useful::LimitNum(rCenterPos.y, rOriginPos.y - rOriginSizeDown.y + rCenterSizeUp.y, rOriginPos.y + rOriginSizeUp.y - rCenterSizeDown.y))
	{ // �␳���s��ꂽ�ꍇ

		// ���肵����Ԃɂ���
		bHit = true;
	}

	// ���茋�ʂ�Ԃ�
	return bHit;
}

//============================================================
//	XZ���ʊp���̓�������
//============================================================
bool collision::InBoxPillarXZ
(
	VECTOR3& rCenterPos,			// ����ʒu
	const VECTOR3& rOriginPos,		// ���茴�_�ʒu
	const VECTOR3& rCenterSizeUp,	// ����T�C�Y(�E�E��E��)
	const VECTOR3& rCenterSizeDown,	// ����T�C�Y(���E���E�O)
	const VECTOR3& rOriginSizeUp,	// ���茴�_�T�C�Y(�E�E��E��)
	const VECTOR3& rOriginSizeDown	// ���茴�_�T�C�Y(���E���E�O)
)
{
	bool bHit = false;	// ���茋��

	// ���E�̕␳
	if (useful::LimitNum(rCenterPos.x, rOriginPos.x - rOriginSizeDown.x + rCenterSizeUp.x, rOriginPos.x + rOriginSizeUp.x - rCenterSizeDown.x))
	{ // �␳���s��ꂽ�ꍇ

		// ���肵����Ԃɂ���
		bHit = true;
	}

	// �O��̕␳
	if (useful::LimitNum(rCenterPos.z, rOriginPos.z - rOriginSizeDown.z + rCenterSizeUp.z, rOriginPos.z + rOriginSizeUp.z - rCenterSizeDown.z))
	{ // �␳���s��ꂽ�ꍇ

		// ���肵����Ԃɂ���
		bHit = true;
	}

	// ���茋�ʂ�Ԃ�
	return bHit;
}

//============================================================
//	�~���̓�������
//============================================================
bool collision::InCirclePillar
(
	VECTOR3& rCenterPos,	// ����ʒu
	VECTOR3 originPos,		// ���茴�_�ʒu
	float fCenterRadius,	// ���蔼�a
	float fOriginRadius		// ���茴�_���a
)
{
	// ����ʒu�Ɣ���ڕW�ʒu�̋��������߂�
	float fLength = (rCenterPos.x - originPos.x) * (rCenterPos.x - originPos.x)
				  + (rCenterPos.z - originPos.z) * (rCenterPos.z - originPos.z);

	if (fLength > (fOriginRadius - fCenterRadius) * (fOriginRadius - fCenterRadius))
	{ // ����O�̏ꍇ

		// �ʒu��␳
		float fCenterRot = atan2f(rCenterPos.x - originPos.x, rCenterPos.z - originPos.z);	// ����ڕW���猩���������
		rCenterPos.x = originPos.x + sinf(fCenterRot) * (fOriginRadius - fCenterRadius);
		rCenterPos.z = originPos.z + cosf(fCenterRot) * (fOriginRadius - fCenterRadius);

		return true;
	}

	return false;
}

//============================================================
//	�O�ς̍��E����
//============================================================
//	���E�����猩�č��E�ǂ���ɂ��邩�̔���Ɏg�p
//============================================================
float collision::LineOuterProduct
(
	VECTOR3 posLeft,	// ���E�������W
	VECTOR3 posRight,	// ���E���E���W
	VECTOR3 pos			// ����ʒu
)
{
	// ���E���x�N�g�������߂�
	VECTOR3 vecLine = posRight - posLeft;

	// ���[�ƈʒu�̃x�N�g�������߂�
	VECTOR3 vecToPos = pos - posLeft;

	// �O�ς̌v�Z���ʂ�Ԃ�
	return (vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z);
}

//============================================================
//	�O�ς̏㉺����
//============================================================
//	���E�����猩�ď㉺�ǂ���ɂ��邩�̔���Ɏg�p
//============================================================
float collision::LineHeightOuterProduct
(
	VECTOR3 posLeft,	// ���E�������W
	VECTOR3 posRight,	// ���E���E���W
	VECTOR3 pos			// ����ʒu
)
{
	// ���E���x�N�g�������߂�
	VECTOR3 vecLine = posRight - posLeft;

	// ���[�ƈʒu�̃x�N�g�������߂�
	VECTOR3 vecToPos = pos - posLeft;

	// �O�ς̌v�Z���ʂ�Ԃ�
	return (vecLine.y * vecToPos.x) - (vecLine.x * vecToPos.y);
}

//============================================================
//	�O�p���̓����蔻��
//============================================================
bool collision::TriangleOuterPillar
(
	VECTOR3 pos0,	// �O�p�̊e���_
	VECTOR3 pos1,	// �O�p�̊e���_
	VECTOR3 pos2,	// �O�p�̊e���_
	VECTOR3 pos		// ����ʒu
)
{
	if (collision::LineOuterProduct(pos0, pos1, pos) <= 0.0f
	&&  collision::LineOuterProduct(pos1, pos2, pos) <= 0.0f
	&&  collision::LineOuterProduct(pos2, pos0, pos) <= 0.0f)
	{ // ������̏ꍇ

		return true;
	}

	return false;
}

//============================================================
//	�l�p���̓����蔻��
//============================================================
bool collision::BoxOuterPillar
(
	VECTOR3 pos0,	// �l�p�̊e���_
	VECTOR3 pos1,	// �l�p�̊e���_
	VECTOR3 pos2,	// �l�p�̊e���_
	VECTOR3 pos3,	// �l�p�̊e���_
	VECTOR3 pos		// ����ʒu
)
{
	if (collision::LineOuterProduct(pos0, pos1, pos) <= 0.0f
	&&  collision::LineOuterProduct(pos1, pos2, pos) <= 0.0f
	&&  collision::LineOuterProduct(pos2, pos3, pos) <= 0.0f
	&&  collision::LineOuterProduct(pos3, pos0, pos) <= 0.0f)
	{ // ������̏ꍇ

		return true;
	}

	return false;
}
