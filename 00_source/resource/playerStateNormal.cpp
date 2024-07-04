//============================================================
//
//	�ʏ��ԏ��� [playerStateNormal.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "playerStateNormal.h"
#include "player.h"
#include "manager.h"

// TODO
#include "tileColl.h"
#include "tileTrans.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const float	MOVE = 260.0f;	// �ړ���
}

//************************************************************
//	�q�N���X [CPlayerStateNormal] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPlayerStateNormal::CPlayerStateNormal() :
	m_move		(VEC3_ZERO),	// �ړ���
	m_moveAngle	((EAngle)0)		// �ړ�����

{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CPlayerStateNormal::~CPlayerStateNormal()
{

}

//============================================================
//	����������
//============================================================
HRESULT CPlayerStateNormal::Init(void)
{
	// �����o�ϐ���������
	m_move		= VEC3_ZERO;	// �ړ���
	m_moveAngle	= ANGLE_DOWN;	// �ړ�����

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CPlayerStateNormal::Uninit(void)
{
	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
int CPlayerStateNormal::Update(const float fDeltaTime)
{
	// �v���C���[�ʒu���擾
	D3DXVECTOR3 posPlayer = m_pContext->GetVec3Position();

	// �ړ��̑���
	int nCurMotion = ControlMove();	// ���݂̃��[�V�����擾

	// �ʒu�̍X�V
	UpdatePosition(posPlayer, fDeltaTime);

	// TODO
	// ����^�C���Ƃ̓����蔻��
	CTileColl::CollisionTile(posPlayer, m_pContext->GetOldPosition(), (m_pContext->GetVec3Sizing() + D3DXVECTOR3(0.0f, 0.0f, 50.0f)) * 0.5f);

	// TODO
	// �J�ڃ^�C���Ƃ̓����蔻��
	CTileTrans::CollisionTile(posPlayer, (m_pContext->GetVec3Sizing() + D3DXVECTOR3(0.0f, 0.0f, 50.0f)) * 0.5f);

	// �v���C���[�ʒu�𔽉f
	m_pContext->SetVec3Position(posPlayer);

	// ���݂̃��[�V������Ԃ�
	return nCurMotion;
}

//============================================================
//	�ړ��̑��쏈��
//============================================================
int CPlayerStateNormal::ControlMove(void)
{
	if (GET_INPUTKEY->IsPress(DIK_UP))
	{
		if (GET_INPUTKEY->IsPress(DIK_LEFT))
		{
			// �ړ��ʂ�ݒ�
			m_move.x += sinf(-D3DX_PI * 0.25f) * MOVE;
			m_move.y += cosf(-D3DX_PI * 0.25f) * MOVE;

			// �O��̈ړ������ɉ����ă��[�V������Ԃ�
			if (m_moveAngle == ANGLE_LEFT)	{ return CPlayer::MOTION_MOVE_L; }	// �O�񂪍��ړ��Ȃ獶�ړ����[�V����
			else							{ return CPlayer::MOTION_MOVE_U; }	// ����ȊO�Ȃ��ړ����[�V����
		}
		else if (GET_INPUTKEY->IsPress(DIK_RIGHT))
		{
			// �ړ��ʂ�ݒ�
			m_move.x -= sinf(-D3DX_PI * 0.75f) * MOVE;
			m_move.y -= cosf(-D3DX_PI * 0.75f) * MOVE;

			// �O��̈ړ������ɉ����ă��[�V������Ԃ�
			if (m_moveAngle == ANGLE_RIGHT)	{ return CPlayer::MOTION_MOVE_R; }	// �O�񂪉E�ړ��Ȃ�E�ړ����[�V����
			else							{ return CPlayer::MOTION_MOVE_U; }	// ����ȊO�Ȃ��ړ����[�V����
		}
		else
		{
			// �ړ��ʂ�ݒ�
			m_move.x += sinf(0.0f) * MOVE;
			m_move.y += cosf(0.0f) * MOVE;

			// ��ړ���ۑ�
			m_moveAngle = ANGLE_UP;

			// ��ړ����[�V������Ԃ�
			return CPlayer::MOTION_MOVE_U;
		}
	}
	else if (GET_INPUTKEY->IsPress(DIK_DOWN))
	{
		if (GET_INPUTKEY->IsPress(DIK_LEFT))
		{
			// �ړ��ʂ�ݒ�
			m_move.x += sinf(-D3DX_PI * 0.75f) * MOVE;
			m_move.y += cosf(-D3DX_PI * 0.75f) * MOVE;

			// �O��̈ړ������ɉ����ă��[�V������Ԃ�
			if (m_moveAngle == ANGLE_LEFT)	{ return CPlayer::MOTION_MOVE_L; }	// �O�񂪍��ړ��Ȃ獶�ړ����[�V����
			else							{ return CPlayer::MOTION_MOVE_D; }	// ����ȊO�Ȃ牺�ړ����[�V����
		}
		else if (GET_INPUTKEY->IsPress(DIK_RIGHT))
		{
			// �ړ��ʂ�ݒ�
			m_move.x -= sinf(-D3DX_PI * 0.25f) * MOVE;
			m_move.y -= cosf(-D3DX_PI * 0.25f) * MOVE;

			// �O��̈ړ������ɉ����ă��[�V������Ԃ�
			if (m_moveAngle == ANGLE_RIGHT)	{ return CPlayer::MOTION_MOVE_R; }	// �O�񂪉E�ړ��Ȃ�E�ړ����[�V����
			else							{ return CPlayer::MOTION_MOVE_D; }	// ����ȊO�Ȃ牺�ړ����[�V����
		}
		else
		{
			// �ړ��ʂ�ݒ�
			m_move.x -= sinf(0.0f) * MOVE;
			m_move.y -= cosf(0.0f) * MOVE;

			// ���ړ���ۑ�
			m_moveAngle = ANGLE_DOWN;

			// ���ړ����[�V������Ԃ�
			return CPlayer::MOTION_MOVE_D;
		}
	}
	else if (GET_INPUTKEY->IsPress(DIK_LEFT))
	{
		// �ړ��ʂ�ݒ�
		m_move.x += sinf(-D3DX_PI * 0.5f) * MOVE;
		m_move.y += cosf(-D3DX_PI * 0.5f) * MOVE;

		// ���ړ���ۑ�
		m_moveAngle = ANGLE_LEFT;

		// ���ړ����[�V������Ԃ�
		return CPlayer::MOTION_MOVE_L;
	}
	else if (GET_INPUTKEY->IsPress(DIK_RIGHT))
	{
		// �ړ��ʂ�ݒ�
		m_move.x -= sinf(-D3DX_PI * 0.5f) * MOVE;
		m_move.y -= cosf(-D3DX_PI * 0.5f) * MOVE;

		// �E�ړ���ۑ�
		m_moveAngle = ANGLE_RIGHT;

		// �E�ړ����[�V������Ԃ�
		return CPlayer::MOTION_MOVE_R;
	}

	// �O��ړ����������̑ҋ@���[�V������Ԃ�
	return (CPlayer::EMotion)m_moveAngle;
}

//============================================================
//	�ʒu�̍X�V����
//============================================================
void CPlayerStateNormal::UpdatePosition(D3DXVECTOR3& rPosPlayer, const float fDeltaTime)
{
	// �v���C���[���ړ�������
	rPosPlayer += m_move * fDeltaTime;

	// �ړ��ʂ�������
	m_move = VEC3_ZERO;
}
