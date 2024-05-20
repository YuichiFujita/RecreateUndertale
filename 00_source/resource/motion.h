//============================================================
//
//	���[�V�����w�b�_�[ [motion.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MOTION_H_
#define _MOTION_H_

//************************************************************
//	�O���錾
//************************************************************
class CMultiModel;	// �}���`���f���N���X
class CObjectChara;	// �I�u�W�F�N�g�L�����N�^�[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ���[�V�����N���X
class CMotion
{
public:
	// �R���X�g���N�^
	CMotion(std::function<int(void)> funcGetNumParts);

	// �f�X�g���N�^
	~CMotion();

	// ����J�E���g�Ǘ��\����
	struct SCollTime
	{
		// �R���X�g���N�^
		SCollTime() :
			nMin(NONE_IDX),	// �U������̊J�n�J�E���g
			nMax(NONE_IDX)	// �U������̏I���J�E���g
		{}

		// �����o�ϐ�
		int nMin;	// �U������̊J�n�J�E���g
		int nMax;	// �U������̏I���J�E���g
	};

	// �p�[�c�Ǘ��\����
	struct SParts
	{
		// �R���X�g���N�^
		SParts() :
			pos(VEC3_ZERO),	// ���f���ʒu
			rot(VEC3_ZERO)	// ���f������
		{}

		// �����o�ϐ�
		D3DXVECTOR3 pos;	// ���f���ʒu
		D3DXVECTOR3 rot;	// ���f������
	};

	// �L�[�Ǘ��\����
	struct SKey
	{
		// �R���X�g���N�^
		SKey() :
			move	(VEC3_ZERO),	// �L�[�ړ���
			nFrame	(0)				// �L�[�Đ��t���[����
		{
			vecParts.clear();	// �p�[�c�����N���A
		}

		// �����o�ϐ�
		std::vector<SParts> vecParts;	// �p�[�c���
		D3DXVECTOR3 move;	// �L�[�ړ���
		int nFrame;			// �L�[�Đ��t���[����
	};

	// ���[�V�����Ǘ��\����
	struct SMotion
	{
		// �R���X�g���N�^
		SMotion() :
			nWholeFrame		(0),		// ���[�V�����S�̃t���[����
			nCancelFrame	(NONE_IDX),	// �L�����Z���\�t���[��
			nComboFrame		(NONE_IDX),	// �R���{�\�t���[��
			bLoop			(false),	// ���[�vON/OFF
			bWeaponDisp		(false)		// ����\��ON/OFF
		{
			vecKey.clear();	// �L�[�����N���A
		}

		// �����o�֐�
		int GetNumKey(void) { return (int)vecKey.size(); }	// �L�[���̑����擾

		// �����o�ϐ�
		std::vector<SKey> vecKey;	// �L�[���
		SCollTime collLeft;		// ���U������̃J�E���g
		SCollTime collRight;	// �E�U������̃J�E���g
		int  nWholeFrame;		// ���[�V�����S�̃t���[����
		int  nCancelFrame;		// �L�����Z���\�t���[��
		int  nComboFrame;		// �R���{�\�t���[��
		bool bLoop;				// ���[�vON/OFF
		bool bWeaponDisp;		// ����\��ON/OFF
	};

	// ���[�V�������\����
	struct SInfo
	{
		// �R���X�g���N�^
		SInfo() :
			nType			(0),	// ���[�V�������
			nKey			(0),	// ���[�V�����L�[�ԍ�
			nKeyCounter		(0),	// ���[�V�����L�[�J�E���^�[
			nWholeCounter	(0),	// ���[�V�����S�̃J�E���^�[
			bFinish			(false)	// ���[�V�����I����
		{
			vecMotion.clear();		// ���[�V���������N���A
			vecOriginParts.clear();	// �p�[�c���_�����N���A
		}

		// �����o�֐�
		int GetNumMotion(void) { return (int)vecMotion.size(); }	// ���[�V�������̑����擾

		// �����o�ϐ�
		std::vector<SMotion> vecMotion;		// ���[�V�������
		std::vector<SParts> vecOriginParts;	// �p�[�c���_���
		int  nType;			// ���[�V�������
		int  nKey;			// ���[�V�����L�[�ԍ�
		int  nKeyCounter;	// ���[�V�����L�[�J�E���^�[
		int  nWholeCounter;	// ���[�V�����S�̃J�E���^�[
		bool bFinish;		// ���[�V�����I����
	};

	// �u�����h���\����
	struct SBlend
	{
		// �R���X�g���N�^
		SBlend() :
			nFrame			(0),	// �u�����h�Đ��t���[����
			nWholeCounter	(0)		// �u�����h�S�̃J�E���^�[
		{
			vecParts.clear();	// �u�����h�J�n�p�[�c�����N���A
		}

		// �����o�ϐ�
		std::vector<SParts> vecParts;	// �u�����h�J�n�p�[�c���
		int nFrame;			// �u�����h�Đ��t���[����
		int nWholeCounter;	// �u�����h�S�̃J�E���^�[
	};

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);		// �X�V
	void BindPartsData(CMultiModel **ppModel);	// �p�[�c���ݒ�
	void SetAllInfo(const SInfo& rInfo);		// ���[�V�������S�ݒ�
	void AddInfo(const SMotion& rMotion);		// ���[�V�������ǉ�
	void SetEnableUpdate(const bool bUpdate);	// �X�V�󋵐ݒ�
	void SetNumParts(const int nNumParts);		// �p�[�c���ݒ�
	void ClearVector(void);						// ���[�V�������̓��I�z��N���A
	void Set(const int nType, const int nBlendFrame = 0);				// �ݒ�
	void SetOriginPosition(const D3DXVECTOR3& rPos, const int nParts);	// ���_�ʒu�̐ݒ�
	void SetOriginRotation(const D3DXVECTOR3& rRot, const int nParts);	// ���_�����̐ݒ�

	int GetNumType(void);					// ��ޑ����擾
	int GetNumKey(const int nType);			// �L�[�����擾
	bool IsCancel(const int nType) const;	// �L�����Z���擾
	bool IsCombo(const int nType) const;	// �R���{�擾
	bool IsLeftWeaponCollision(void);		// ���̍U������t���O�擾
	bool IsRightWeaponCollision(void);		// �E�̍U������t���O�擾
	D3DXVECTOR3 GetOriginPosition(const int nParts);	// ���_�ʒu�̎擾
	D3DXVECTOR3 GetOriginRotation(const int nParts);	// ���_�����̎擾

	int GetType(void) const			{ return m_info.nType; }			// ��ގ擾
	int GetKey(void) const			{ return m_info.nKey; }				// �L�[�ԍ��擾
	int GetKeyCounter(void) const	{ return m_info.nKeyCounter; }		// ���[�V�����L�[�J�E���^�[�擾
	int GetWholeCounter(void) const	{ return m_info.nWholeCounter; }	// ���[�V�����S�̃J�E���^�[�擾
	bool IsFinish(void) const		{ return m_info.bFinish; }			// �I���擾
	bool IsLoop(const int nType) const			{ return m_info.vecMotion[nType].bLoop; }			// ���[�v�擾
	bool IsWeaponDisp(const int nType) const	{ return m_info.vecMotion[nType].bWeaponDisp; }		// ����\���擾
	int GetWholeFrame(const int nType) const	{ return m_info.vecMotion[nType].nWholeFrame; }		// ���[�V�����S�̃t���[�����擾
	int GetCancelFrame(const int nType) const	{ return m_info.vecMotion[nType].nCancelFrame; }	// ���[�V�����L�����Z���t���[���擾
	int GetComboFrame(const int nType) const	{ return m_info.vecMotion[nType].nComboFrame; }		// ���[�V�����R���{�t���[���擾

	// �ÓI�����o�֐�
	static CMotion *Create(CObjectChara *pChara);	// ����
	static void Release(CMotion *&prMotion);		// �j��

private:
	// �����o�֐�
	void UpdateMove(void);		// �ړ��X�V
	void UpdateMotion(void);	// ���[�V�����X�V
	void UpdateBlend(void);		// �u�����h�X�V

	// �����o�ϐ�
	const std::function<int(void)> m_funcGetNumParts;	// �p�[�c���擾�֐��|�C���^
	CMultiModel **m_ppModel;	// ���f�����
	CObjectChara *m_pChara;		// �I�u�W�F�N�g�L�����N�^�[���
	SInfo  m_info;	// ���[�V�������
	SBlend m_blend;	// �u�����h���
	bool m_bUpdate;	// �X�V��
};

#endif	// _MOTION_H_
