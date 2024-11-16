//============================================================
//
//	�v���C���[�X�e�[�^�X���� [playerStatus.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "playerStatus.h"
#include "playerItem.h"
#include "sceneGame.h"
#include "player.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	namespace love
	{
		const int MIN = 1;	// �ŏ����x��
		const int MAX = 20;	// �ő僌�x��
	}

	namespace hp
	{
		const int MAX_MIN_LOVE = 20;	// ���x��1�̍ő�̗�
		const int MAX_MAX_LOVE = 99;	// �ő僌�x�����̍ő�̗�
		const int PLUS = 4;				// ���x���㏸���̗͉̑��Z��
	}

	namespace atk
	{
		const int NUM_MIN_LOVE = 0;	// ���x��1�̍U����
		const int PLUS = 2;			// ���x���㏸���̍U���͉��Z��
	}

	namespace def
	{
		const int NUM_MIN_LOVE = 0;	// ���x��1�̖h���
		const int INTERVAL = 4;		// �h��͂��㏸���郌�x���Ԋu��
		const int PLUS = 1;			// ���x���㏸���̖h��͉��Z��
	}

	namespace exp
	{
		const int LV_NEXT[] =	// �����x���܂łɕK�v�Ȍo���l
		{
			10,		20,		40,		50,		80,
			100,	200,	300,	400,	500,
			800,	1000,	1500,	2000,	3000,
			5000,	10000,	25000,	49999,	0,
		};
	}
}

//************************************************************
//	�e�N���X [CPlayerStatus] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPlayerStatus::CPlayerStatus() :
	m_sName			(""),	// �v���C���[��
	m_nLove			(1),	// ���x��	// TODO�F�O���t�@�C������̓ǂݍ��ݍ������0�ɖ߂�
	m_nHP			(0),	// �̗�
	m_nMaxHP		(0),	// �ő�̗�
	m_nExp			(0),	// �o���l
	m_nWpnItemIdx	(0),	// ����A�C�e���C���f�b�N�X
	m_nAmrItemIdx	(0),	// �h��A�C�e���C���f�b�N�X
	m_nNumGold		(0),	// ������
	m_nNumKill		(0),	// �E�Q��
	m_fSpeed		(0.0f),	// �ړ����x
	m_fInvTime		(0.0f)	// ���G����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CPlayerStatus::~CPlayerStatus()
{

}

//============================================================
//	�̗͂̑�������
//============================================================
void CPlayerStatus::ChangeHP(const int nChange)
{
	if (nChange > 0)
	{ // �̗͂𑝉�������ꍇ

		// �̗͂̉��Z
		AddHP(nChange);
	}
	else if (nChange < 0)
	{ // �̗͂�����������ꍇ

		// �̗͂̌��Z
		SubHP(-nChange);
	}
}

//============================================================
//	����A�C�e���C���f�b�N�X�̓��֏���
//============================================================
void CPlayerStatus::SwapWeaponIdx(const int nBagIdx)
{
	CPlayerItem* pItem = CSceneGame::GetPlayer()->GetItem();	// �v���C���[�����A�C�e�����

	// �����A�C�e�����͈̔͊O�C���f�b�N�X�Ȃ甲����
	if (nBagIdx > pItem->GetNumItem()) { return; }

	// �A�C�e���C���f�b�N�X�̓���ւ�
	int nTempWpn = m_nWpnItemIdx;				// ���݂̕���C���f�b�N�X��ۑ�
	m_nWpnItemIdx = pItem->GetItemIdx(nBagIdx);	// �o�b�O���̕���C���f�b�N�X�ɕύX
	pItem->SetItemIdx(nBagIdx, nTempWpn);		// �o�b�N���Ɍ��̕���C���f�b�N�X�����
}

//============================================================
//	�h��A�C�e���C���f�b�N�X�̓��֏���
//============================================================
void CPlayerStatus::SwapArmorIdx(const int nBagIdx)
{
	CPlayerItem* pItem = CSceneGame::GetPlayer()->GetItem();	// �v���C���[�����A�C�e�����

	// �����A�C�e�����͈̔͊O�C���f�b�N�X�Ȃ甲����
	if (nBagIdx > pItem->GetNumItem()) { return; }

	// �A�C�e���C���f�b�N�X�̓���ւ�
	int nTempAmr = m_nAmrItemIdx;				// ���݂̖h��C���f�b�N�X��ۑ�
	m_nAmrItemIdx = pItem->GetItemIdx(nBagIdx);	// �o�b�O���̖h��C���f�b�N�X�ɕύX
	pItem->SetItemIdx(nBagIdx, nTempAmr);		// �o�b�N���Ɍ��̖h��C���f�b�N�X�����
}

//============================================================
//	���x����̍ő�HP�擾���� (�ő僌�x��)
//============================================================
int CPlayerStatus::GetBaseMaxHP() const
{
	// �ő僌�x������HP��Ԃ�
	return hp::MAX_MAX_LOVE;
}

//============================================================
//	���x����̍ő�HP�擾���� (���x���w��)
//============================================================
int CPlayerStatus::GetBaseMaxHP(const int nLv) const
{
	// ���x�����͈͊O�̏ꍇ������
	if (nLv <= 0 || nLv > love::MAX) { assert(false); return 0; }

	if (nLv < love::MAX)
	{ // �ő僌�x�������̏ꍇ

		// �w�背�x�����̍ő�HP��Ԃ�
		return hp::MAX_MIN_LOVE + (hp::PLUS * (nLv - 1));
	}

	// �ő僌�x�����̍ő�HP��Ԃ�
	return hp::MAX_MAX_LOVE;
}

//============================================================
//	���x����̍ő�HP�擾���� (���݃��x��)
//============================================================
int CPlayerStatus::GetCurBaseMaxHP() const
{
	// ���݂̍ő�HP��Ԃ�
	return GetBaseMaxHP(m_nLove);
}

//============================================================
//	�U���͂̎擾���� (���x���w��)
//============================================================
int CPlayerStatus::GetAtk(const int nLv) const
{
	// ���x�����͈͊O�̏ꍇ������
	if (nLv <= 0 || nLv > love::MAX) { assert(false); return 0; }

	// �w�背�x�����̍U���͂�Ԃ�
	return atk::NUM_MIN_LOVE + (atk::PLUS * (nLv - 1));
}

//============================================================
//	�U���͂̎擾���� (���݃��x��)
//============================================================
int CPlayerStatus::GetCurAtk() const
{
	// ���݂̍U���͂�Ԃ�
	return GetAtk(m_nLove);
}

//============================================================
//	�h��͂̎擾���� (���x���w��)
//============================================================
int CPlayerStatus::GetDef(const int nLv) const
{
	// ���x�����͈͊O�̏ꍇ������
	if (nLv <= 0 || nLv > love::MAX) { assert(false); return 0; }

	// �w�背�x�����̖h��͂�Ԃ�
	return def::NUM_MIN_LOVE + (def::PLUS * ((nLv - 1) / def::INTERVAL));
}

//============================================================
//	�h��͂̎擾���� (���݃��x��)
//============================================================
int CPlayerStatus::GetCurDef() const
{
	// ���݂̖h��͂�Ԃ�
	return GetDef(m_nLove);
}

//============================================================
//	�����x���܂ł�EXP�擾���� (���x���w��)
//============================================================
int CPlayerStatus::GetNext(const int nLv) const
{
	// ���x�����͈͊O�̏ꍇ������
	if (nLv <= 0 || nLv > love::MAX) { assert(false); return 0; }

	// �w�背�x������EXP��Ԃ�
	return exp::LV_NEXT[nLv];
}

//============================================================
//	�����x���܂ł�EXP�擾���� (���݃��x��)
//============================================================
int CPlayerStatus::GetCurNext() const
{
	// ���݂�EXP��Ԃ�
	return GetNext(m_nLove);
}

//============================================================
//	�̗͂̉��Z����
//============================================================
void CPlayerStatus::AddHP(const int nAdd)
{
	// �̗͂��񕜂�����
	m_nHP += nAdd;

	// �̗͂̒l��␳
	useful::LimitNum(m_nHP, 0, GetCurBaseMaxHP());
}

//============================================================
//	�̗͂̌��Z����
//============================================================
void CPlayerStatus::SubHP(const int nSub)
{
	int nDamage = nSub;					// �_���[�W��
	int nBaseMaxHP = GetCurBaseMaxHP();	// ���x����̍ő�HP
	if (m_nMaxHP > nBaseMaxHP)
	{ // ���݂̍ő�HP�����x����̍ő�HP��葽���ꍇ

		int nDiffHP = m_nMaxHP - nBaseMaxHP;	// �ő�HP�̍���
		if (nDamage > nDiffHP)
		{ // �_���[�W�ʂ��ő�HP�̍�����葽���ꍇ

			// �ő�̗͂����x����ɏC��
			m_nMaxHP = nBaseMaxHP;

			// �^����_���[�W�ʂ��y��
			nDamage -= nDiffHP;
		}
		else
		{ // �_���[�W�ʂ��ő�HP�̍�����菭�Ȃ��ꍇ

			// �ő�̗͂Ƀ_���[�W��^����
			m_nMaxHP -= nDamage;
			return;
		}
	}

	// �̗͂Ƀ_���[�W��^����
	m_nHP -= nDamage;

	// �̗͂̒l��␳
	useful::LimitNum(m_nHP, 0, nBaseMaxHP);
}
