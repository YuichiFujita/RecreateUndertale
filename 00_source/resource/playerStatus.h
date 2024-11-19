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
//	�N���X��`
//************************************************************
// �v���C���[�X�e�[�^�X�N���X
class CPlayerStatus
{
public:
	// �R���X�g���N�^
	CPlayerStatus();

	// �f�X�g���N�^
	~CPlayerStatus();

	// �����o�֐�
	void ChangeHP(const int nChange);		// �̗͑���
	void SwapWeaponIdx(const int nBagIdx);	// ����A�C�e���C���f�b�N�X����
	void SwapArmorIdx(const int nBagIdx);	// �h��A�C�e���C���f�b�N�X����
	int GetBaseMaxHP() const;				// ���x����̍ő�HP�擾 (�ő僌�x��)
	int GetBaseMaxHP(const int nLv) const;	// ���x����̍ő�HP�擾 (���x���w��)
	int GetCurBaseMaxHP() const;			// ���x����̍ő�HP�擾 (���݃��x��)
	int GetAtk(const int nLv) const;		// �U���͎擾 (���x���w��)
	int GetCurAtk() const;					// �U���͎擾 (���݃��x��)
	int GetDef(const int nLv) const;		// �h��͎擾 (���x���w��)
	int GetCurDef() const;					// �h��͎擾 (���݃��x��)
	int GetNext(const int nLv) const;		// �����x���܂ł�EXP�擾 (���x���w��)
	int GetCurNext() const;					// �����x���܂ł�EXP�擾 (���݃��x��)
	inline void SetName(const std::string& rName)	{ m_sName = rName; }			// �v���C���[���擾
	inline void SetLove(const int nLove)			{ m_nLove = nLove; }			// ���x���擾
	inline void SetHP(const int nHP)				{ m_nHP = nHP; }				// �̗͎擾
	inline void SetMaxHP(const int nMaxHP)			{ m_nMaxHP = nMaxHP; }			// �ő�̗͎擾
	inline void SetExp(const int nExp)				{ m_nExp = nExp; }				// �o���l�擾
	inline void SetWpnItemIdx(const int nItemIdx)	{ m_nWpnItemIdx = nItemIdx; }	// ����A�C�e���C���f�b�N�X�擾
	inline void SetAmrItemIdx(const int nItemIdx)	{ m_nAmrItemIdx = nItemIdx; }	// �h��A�C�e���C���f�b�N�X�擾
	inline void SetNumGold(const int nNumGold)		{ m_nNumGold = nNumGold; }		// �������擾
	inline void SetNumKill(const int nNumKill)		{ m_nNumKill = nNumKill; }		// �E�Q���擾
	inline void SetSpeed(const float fSpeed)		{ m_fSpeed = fSpeed; }			// �ړ����x�擾
	inline void SetInvTime(const float fInvTime)	{ m_fInvTime = fInvTime; }		// ���G���Ԏ擾
	inline std::string GetName() const	{ return m_sName; }			// �v���C���[���擾
	inline int GetLove() const			{ return m_nLove; }			// ���x���擾
	inline int GetHP() const			{ return m_nHP; }			// �̗͎擾
	inline int GetMaxHP() const			{ return m_nMaxHP; }		// �ő�̗͎擾
	inline int GetExp() const			{ return m_nExp; }			// �o���l�擾
	inline int GetWpnItemIdx() const	{ return m_nWpnItemIdx; }	// ����A�C�e���C���f�b�N�X�擾
	inline int GetAmrItemIdx() const	{ return m_nAmrItemIdx; }	// �h��A�C�e���C���f�b�N�X�擾
	inline int GetNumGold() const		{ return m_nNumGold; }		// �������擾
	inline int GetNumKill() const		{ return m_nNumKill; }		// �E�Q���擾
	inline float GetSpeed() const		{ return m_fSpeed; }		// �ړ����x�擾
	inline float GetInvTime() const		{ return m_fInvTime; }		// ���G���Ԏ擾

private:
	// �����o�֐�
	void AddHP(const int nAdd);	// �̗͉��Z
	void SubHP(const int nSub);	// �̗͌��Z

	// �����o�ϐ�
	std::string m_sName;	// �v���C���[��
	int m_nLove;			// ���x��
	int m_nHP;				// �̗�		// TODO�F�퓬����HP�o�[�̎����͂��̒l���|�C���^�Ŏ����Ĉ�����
	int m_nMaxHP;			// �ő�̗�
	int m_nExp;				// �o���l
	int m_nWpnItemIdx;		// ����A�C�e���C���f�b�N�X
	int m_nAmrItemIdx;		// �h��A�C�e���C���f�b�N�X
	int m_nNumGold;			// ������
	int m_nNumKill;			// �E�Q��
	float m_fSpeed;			// �ړ����x
	float m_fInvTime;		// ���G����
};

#endif	// _PLAYER_STATUS_H_
