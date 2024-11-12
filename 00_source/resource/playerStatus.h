//============================================================
//
//	�v���C���[�X�e�[�^�X�w�b�_�[ [playerStatus.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PLAYER_STATUS_H_
#define _PLAYER_STATUS_H_

//************************************************************
//	�\���̒�`
//************************************************************
// �v���C���[�X�e�[�^�X�\����
struct SPlayerStatus
{
public:
	// �f�t�H���g�R���X�g���N�^
	SPlayerStatus() :
		sName		(""),	// �v���C���[��
		nLove		(1),	// ���x��	// TODO�F�O���t�@�C������̓ǂݍ��ݍ������0�ɖ߂�
		nHP			(0),	// �̗�
		nMaxHP		(0),	// �ő�̗�
		nCurExp		(0),	// ���݌o���l
		nWpnItemIdx	(0),	// ����A�C�e���C���f�b�N�X
		nAmrItemIdx	(0),	// �h��A�C�e���C���f�b�N�X
		nGold		(0),	// �c��
		nKills		(0),	// �E�Q��
		fSpeed		(0.0f),	// �ړ����x
		fInvTime	(0.0f)	// ���G����
	{}

	// �f�X�g���N�^
	~SPlayerStatus() {}

	// �����o�֐�
	int GetMaxHP() const;				// �ő�HP�擾 (�ő僌�x��)
	int GetMaxHP(const int nLv) const;	// �ő�HP�擾 (���x���w��)
	int GetCurMaxHP() const;			// ���݂̍ő�HP�擾
	int GetAtk(const int nLv) const;	// �U���͎擾
	int GetCurAtk() const;				// ���݂̍U���͎擾
	int GetDef(const int nLv) const;	// �h��͎擾
	int GetCurDef() const;				// ���݂̖h��͎擾
	int GetNext(const int nLv) const;	// �����x���܂ł�EXP�擾
	int GetCurNext() const;				// ���݂̎����x���܂ł�EXP�擾

	// �����o�ϐ�
	std::string sName;	// �v���C���[��
	int nLove;			// ���x��
	int nHP;			// �̗�		// TODO�F�퓬����HP�o�[�̎����͂��̒l���|�C���^�Ŏ����Ĉ�����
	int nMaxHP;			// �ő�̗�
	int nCurExp;		// ���݌o���l
	int nWpnItemIdx;	// ����A�C�e���C���f�b�N�X
	int nAmrItemIdx;	// �h��A�C�e���C���f�b�N�X
	int nGold;			// �c��
	int nKills;			// �E�Q��
	float fSpeed;		// �ړ����x
	float fInvTime;		// ���G����
};

#endif	// _PLAYER_STATUS_H_
