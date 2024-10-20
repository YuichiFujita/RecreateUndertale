//============================================================
//
//	����֐��w�b�_�[ [collision.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _COLLISION_H_
#define _COLLISION_H_

//************************************************************
//	���O��Ԑ錾
//************************************************************
// ������
namespace collision
{
	bool BoxXY	// XY���ʂ̋�`�̓����蔻��
	( // ����
		const VECTOR3& rCenterPos,		// ����ʒu
		const VECTOR3& rTargetPos,		// ����ڕW�ʒu
		const VECTOR3& rCenterSizeUp,	// ����傫�� (�E/��/��)
		const VECTOR3& rCenterSizeDown,	// ����傫�� (��/��/�O)
		const VECTOR3& rTargetSizeUp,	// ����ڕW�傫�� (�E/��/��)
		const VECTOR3& rTargetSizeDown	// ����ڕW�傫�� (��/��/�O)
	);
	bool BoxXZ	// XZ���ʂ̋�`�̓����蔻��
	( // ����
		const VECTOR3& rCenterPos,		// ����ʒu
		const VECTOR3& rTargetPos,		// ����ڕW�ʒu
		const VECTOR3& rCenterSizeUp,	// ����傫�� (�E/��/��)
		const VECTOR3& rCenterSizeDown,	// ����傫�� (��/��/�O)
		const VECTOR3& rTargetSizeUp,	// ����ڕW�傫�� (�E/��/��)
		const VECTOR3& rTargetSizeDown	// ����ڕW�傫�� (��/��/�O)
	);
	bool Box3D	// 3���̋�`�̓����蔻��
	( // ����
		VECTOR3 centerPos,		// ����ʒu
		VECTOR3 targetPos,		// ����ڕW�ʒu
		VECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
		VECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
		VECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
		VECTOR3 targetSizeDown	// ����ڕW�T�C�Y(���E���E�O)
	);
	bool Circle2D	// XZ���ʂ̉~�̓����蔻��
	( // ����
		VECTOR3 centerPos,			// ����ʒu
		VECTOR3 targetPos,			// ����ڕW�ʒu
		float fCenterRadius,		// ���蔼�a
		float fTargetRadius,		// ����ڕW���a
		float* pLength = nullptr	// ����ڕW�Ƃ̋���
	);
	bool Circle3D	// 3���̉~�̓����蔻��
	( // ����
		VECTOR3 centerPos,		// ����ʒu
		VECTOR3 targetPos,		// ����ڕW�ʒu
		float fCenterRadius,	// ���蔼�a
		float fTargetRadius		// ����ڕW���a
	);
	bool Sector	// XZ���ʂ̐�`�̓����蔻��
	( // ����
		VECTOR3 centerPos,			// ����ʒu
		VECTOR3 targetPos,			// ����ڕW�ʒu
		float fCenterRot,			// �������
		float fRadius,				// ���E�͈�
		float fAngle,				// ����p
		float* pLength = nullptr	// ����ڕW�Ƃ̋���
	);

	bool ResponseBoxPillarXY	// XY���ʂ̊p���̏Փ˔���
	( // ����
		VECTOR3& rCenterPos,			// ����ʒu
		const VECTOR3& rCenterPosOld,	// ����ߋ��ʒu
		const VECTOR3& rTargetPos,		// ����ڕW�ʒu
		const VECTOR3& rCenterSizeUp,	// ����傫�� (�E/��/��)
		const VECTOR3& rCenterSizeDown,	// ����傫�� (��/��/�O)
		const VECTOR3& rTargetSizeUp,	// ����ڕW�傫�� (�E/��/��)
		const VECTOR3& rTargetSizeDown	// ����ڕW�傫�� (��/��/�O)
	);
	bool ResponseBoxPillarXZ	// XZ���ʂ̊p���̏Փ˔���
	( // ����
		VECTOR3& rCenterPos,			// ����ʒu
		const VECTOR3& rCenterPosOld,	// ����ߋ��ʒu
		const VECTOR3& rTargetPos,		// ����ڕW�ʒu
		const VECTOR3& rCenterSizeUp,	// ����傫�� (�E/��/��)
		const VECTOR3& rCenterSizeDown,	// ����傫�� (��/��/�O)
		const VECTOR3& rTargetSizeUp,	// ����ڕW�傫�� (�E/��/��)
		const VECTOR3& rTargetSizeDown	// ����ڕW�傫�� (��/��/�O)
	);
	bool CirclePillar	// �~���̏Փ˔���
	( // ����
		VECTOR3& rCenterPos,	// ����ʒu
		VECTOR3 targetPos,		// ����ڕW�ʒu
		float fCenterRadius,	// ���蔼�a
		float fTargetRadius		// ����ڕW���a
	);

	bool ResponseBox3D	// �O���̋�`�̏Փ˔���
	( // ����
		VECTOR3& rCenterPos,			// ����ʒu
		const VECTOR3& rCenterPosOld,	// ����ߋ��ʒu
		const VECTOR3& rTargetPos,		// ����ڕW�ʒu
		const VECTOR3& rCenterSizeUp,	// ����T�C�Y(�E�E��E��)
		const VECTOR3& rCenterSizeDown,	// ����T�C�Y(���E���E�O)
		const VECTOR3& rTargetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
		const VECTOR3& rTargetSizeDown,	// ����ڕW�T�C�Y(���E���E�O)
		VECTOR3* pMove = nullptr,		// �ړ���
		bool* pUp = nullptr,	// �ォ��̔���
		bool* pSide = nullptr,	// ������̔���
		bool* pDown = nullptr	// ������̔���
	);
	bool ResponseCircle3D	// �O���̉~�̏Փ˔���
	( // ����
		VECTOR3& rCenterPos,	// ����ʒu
		VECTOR3 targetPos,		// ����ڕW�ʒu
		float fCenterRadius,	// ���蔼�a
		float fTargetRadius		// ����ڕW���a
	);
	bool ResponseCapsule3D	// �O���̃J�v�Z���̏Փ˔���
	( // ����
		VECTOR3* pCenterPos,	// ����ʒu
		VECTOR3& rTargetPos,	// ����ڕW�ʒu
		float fCenterRadius,	// ���蔼�a
		float fTargetRadius,	// ����ڕW���a
		float fTargetHeight		// ����ڕW�c��
	);

	bool ResponseSingleX	// X���̏Փ˔���
	( // ����
		VECTOR3& rCenterPos,		// ����ʒu
		VECTOR3& rCenterPosOld,		// ����ߋ��ʒu
		VECTOR3 targetPos,			// ����ڕW�ʒu
		VECTOR3 centerSizeUp,		// ����T�C�Y(�E�E��E��)
		VECTOR3 centerSizeDown,		// ����T�C�Y(���E���E�O)
		VECTOR3 targetSizeUp,		// ����ڕW�T�C�Y(�E�E��E��)
		VECTOR3 targetSizeDown,		// ����ڕW�T�C�Y(���E���E�O)
		VECTOR3* pMove = nullptr,	// �ړ���
		bool* pLeft = nullptr,		// ������̔���
		bool* pRight = nullptr		// �E����̔���
	);
	bool ResponseSingleY	// Y���̏Փ˔���
	( // ����
		VECTOR3& rCenterPos,		// ����ʒu
		VECTOR3& rCenterPosOld,		// ����ߋ��ʒu
		VECTOR3 targetPos,			// ����ڕW�ʒu
		VECTOR3 centerSizeUp,		// ����T�C�Y(�E�E��E��)
		VECTOR3 centerSizeDown,		// ����T�C�Y(���E���E�O)
		VECTOR3 targetSizeUp,		// ����ڕW�T�C�Y(�E�E��E��)
		VECTOR3 targetSizeDown,		// ����ڕW�T�C�Y(���E���E�O)
		VECTOR3* pMove = nullptr,	// �ړ���
		bool* pDown = nullptr,		// ������̔���
		bool* pUp = nullptr			// �ォ��̔���
	);
	bool ResponseSingleZ	// Z���̏Փ˔���
	( // ����
		VECTOR3& rCenterPos,		// ����ʒu
		VECTOR3& rCenterPosOld,		// ����ߋ��ʒu
		VECTOR3 targetPos,			// ����ڕW�ʒu
		VECTOR3 centerSizeUp,		// ����T�C�Y(�E�E��E��)
		VECTOR3 centerSizeDown,		// ����T�C�Y(���E���E�O)
		VECTOR3 targetSizeUp,		// ����ڕW�T�C�Y(�E�E��E��)
		VECTOR3 targetSizeDown,		// ����ڕW�T�C�Y(���E���E�O)
		VECTOR3* pMove = nullptr,	// �ړ���
		bool* pBefore = nullptr,	// �O����̔���
		bool* pAfter = nullptr		// �ォ��̔���
	);

	bool InBoxPillarXY	// XY���ʊp���̓�������
	( // ����
		VECTOR3& rCenterPos,			// ����ʒu
		const VECTOR3& rOriginPos,		// ���茴�_�ʒu
		const VECTOR3& rCenterSizeUp,	// ����T�C�Y(�E�E��E��)
		const VECTOR3& rCenterSizeDown,	// ����T�C�Y(���E���E�O)
		const VECTOR3& rOriginSizeUp,	// ���茴�_�T�C�Y(�E�E��E��)
		const VECTOR3& rOriginSizeDown	// ���茴�_�T�C�Y(���E���E�O)
	);
	bool InBoxPillarXZ	// XZ���ʊp���̓�������
	( // ����
		VECTOR3& rCenterPos,			// ����ʒu
		const VECTOR3& rOriginPos,		// ���茴�_�ʒu
		const VECTOR3& rCenterSizeUp,	// ����T�C�Y(�E�E��E��)
		const VECTOR3& rCenterSizeDown,	// ����T�C�Y(���E���E�O)
		const VECTOR3& rOriginSizeUp,	// ���茴�_�T�C�Y(�E�E��E��)
		const VECTOR3& rOriginSizeDown	// ���茴�_�T�C�Y(���E���E�O)
	);
	bool InCirclePillar	// �~���̓�������
	( // ����
		VECTOR3& rCenterPos,	// ����ʒu
		VECTOR3 originPos,		// ���茴�_�ʒu
		float fCenterRadius,	// ���蔼�a
		float fOriginRadius		// ���茴�_���a
	);

	float LineOuterProduct	// �O�ς̍��E����
	( // ����
		VECTOR3 posLeft,	// ���E�������W
		VECTOR3 posRight,	// ���E���E���W
		VECTOR3 pos			// ����ʒu
	);
	float LineHeightOuterProduct	// �O�ς̏㉺����
	( // ����
		VECTOR3 posLeft,	// ���E�������W
		VECTOR3 posRight,	// ���E���E���W
		VECTOR3 pos			// ����ʒu
	);

	bool TriangleOuterPillar	// �O�p���̓����蔻��
	( // ����
		VECTOR3 pos0,	// �O�p�̊e���_
		VECTOR3 pos1,	// �O�p�̊e���_
		VECTOR3 pos2,	// �O�p�̊e���_
		VECTOR3 pos		// ����ʒu
	);
	bool BoxOuterPillar		// �l�p���̓����蔻��
	( // ����
		VECTOR3 pos0,	// �l�p�̊e���_
		VECTOR3 pos1,	// �l�p�̊e���_
		VECTOR3 pos2,	// �l�p�̊e���_
		VECTOR3 pos3,	// �l�p�̊e���_
		VECTOR3 pos		// ����ʒu
	);
}

#endif	// _COLLISION_H_
