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
	explicit CMotion(std::function<int()> funcGetNumParts);

	// �f�X�g���N�^
	~CMotion();

	// ����J�E���g�Ǘ��\����
	struct SCollTime
	{
		// �f�t�H���g�R���X�g���N�^
		SCollTime() :
			nMin (NONE_IDX),	// �U������̊J�n�J�E���g
			nMax (NONE_IDX)		// �U������̏I���J�E���g
		{}

		// �f�X�g���N�^
		~SCollTime() {}

		// �����o�ϐ�
		int nMin;	// �U������̊J�n�J�E���g
		int nMax;	// �U������̏I���J�E���g
	};

	// �p�[�c�Ǘ��\����
	struct SParts
	{
		// �f�t�H���g�R���X�g���N�^
		SParts() :
			pos	(VEC3_ZERO),	// ���f���ʒu
			rot	(VEC3_ZERO)		// ���f������
		{}

		// �f�X�g���N�^
		~SParts() {}

		// �����o�ϐ�
		VECTOR3 pos;	// ���f���ʒu
		VECTOR3 rot;	// ���f������
	};

	// �L�[�Ǘ��\����
	struct SKey
	{
		// �f�t�H���g�R���X�g���N�^
		SKey() :
			vecParts ({}),			// �p�[�c���
			move	 (VEC3_ZERO),	// �L�[�ړ���
			nFrame	 (0)			// �L�[�Đ��t���[����
		{}

		// �f�X�g���N�^
		~SKey() {}

		// �����o�ϐ�
		std::vector<SParts> vecParts;	// �p�[�c���
		VECTOR3 move;	// �L�[�ړ���
		int nFrame;		// �L�[�Đ��t���[����
	};

	// ���[�V�����Ǘ��\����
	struct SMotion
	{
		// �f�t�H���g�R���X�g���N�^
		SMotion() :
			vecKey		 ({}),			// �L�[���
			collLeft	 ({}),			// ���U������̃J�E���g
			collRight	 ({}),			// �E�U������̃J�E���g
			nWholeFrame	 (0),			// ���[�V�����S�̃t���[����
			nCancelFrame (NONE_IDX),	// �L�����Z���\�t���[��
			nComboFrame	 (NONE_IDX),	// �R���{�\�t���[��
			bLoop		 (false),		// ���[�vON/OFF
			bWeaponDisp	 (false)		// ����\��ON/OFF
		{}

		// �f�X�g���N�^
		~SMotion() {}

		// �����o�֐�
		inline int GetNumKey() { return (int)vecKey.size(); }	// �L�[���̑����擾

		// �����o�ϐ�
		std::vector<SKey> vecKey;	// �L�[���
		SCollTime collLeft;			// ���U������̃J�E���g
		SCollTime collRight;		// �E�U������̃J�E���g
		int  nWholeFrame;			// ���[�V�����S�̃t���[����
		int  nCancelFrame;			// �L�����Z���\�t���[��
		int  nComboFrame;			// �R���{�\�t���[��
		bool bLoop;					// ���[�vON/OFF
		bool bWeaponDisp;			// ����\��ON/OFF
	};

	// ���[�V�������\����
	struct SInfo
	{
		// �f�t�H���g�R���X�g���N�^
		SInfo() :
			vecMotion		({}),	// ���[�V�������
			vecOriginParts	({}),	// �p�[�c���_���
			nType			(0),	// ���[�V�������
			nKey			(0),	// ���[�V�����L�[�ԍ�
			nKeyCounter		(0),	// ���[�V�����L�[�J�E���^�[
			nWholeCounter	(0),	// ���[�V�����S�̃J�E���^�[
			bFinish			(false)	// ���[�V�����I����
		{}

		// �f�X�g���N�^
		~SInfo() {}

		// �����o�֐�
		inline int GetNumMotion() { return (int)vecMotion.size(); }	// ���[�V�������̑����擾

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
		// �f�t�H���g�R���X�g���N�^
		SBlend() :
			vecParts		({}),	// �u�����h�J�n�p�[�c���
			nFrame			(0),	// �u�����h�Đ��t���[����
			nWholeCounter	(0)		// �u�����h�S�̃J�E���^�[
		{}

		// �f�X�g���N�^
		~SBlend() {}

		// �����o�ϐ�
		std::vector<SParts> vecParts;	// �u�����h�J�n�p�[�c���
		int nFrame;			// �u�����h�Đ��t���[����
		int nWholeCounter;	// �u�����h�S�̃J�E���^�[
	};

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);		// �X�V
	void BindPartsData(CMultiModel** ppModel);	// �p�[�c���ݒ�
	void SetAllInfo(const SInfo& rInfo);		// ���[�V�������S�ݒ�
	void AddInfo(const SMotion& rMotion);		// ���[�V�������ǉ�
	void SetEnableUpdate(const bool bUpdate);	// �X�V�󋵐ݒ�
	void SetNumParts(const int nNumParts);		// �p�[�c���ݒ�
	void ClearVector();							// ���[�V�������̓��I�z��N���A
	void Set(const int nType, const int nBlendFrame = 0);			// �ݒ�
	void SetOriginPosition(const VECTOR3& rPos, const int nParts);	// ���_�ʒu�̐ݒ�
	void SetOriginRotation(const VECTOR3& rRot, const int nParts);	// ���_�����̐ݒ�

	int GetNumType();						// ��ޑ����擾
	int GetNumKey(const int nType);			// �L�[�����擾
	bool IsCancel(const int nType) const;	// �L�����Z���擾
	bool IsCombo(const int nType) const;	// �R���{�擾
	bool IsLeftWeaponCollision();			// ���̍U������t���O�擾
	bool IsRightWeaponCollision();			// �E�̍U������t���O�擾
	VECTOR3 GetOriginPosition(const int nParts);	// ���_�ʒu�̎擾
	VECTOR3 GetOriginRotation(const int nParts);	// ���_�����̎擾

	inline int GetType() const			{ return m_info.nType; }			// ��ގ擾
	inline int GetKey() const			{ return m_info.nKey; }				// �L�[�ԍ��擾
	inline int GetKeyCounter() const	{ return m_info.nKeyCounter; }		// ���[�V�����L�[�J�E���^�[�擾
	inline int GetWholeCounter() const	{ return m_info.nWholeCounter; }	// ���[�V�����S�̃J�E���^�[�擾
	inline bool IsFinish() const		{ return m_info.bFinish; }			// �I���擾
	inline bool IsLoop(const int nType) const			{ return m_info.vecMotion[nType].bLoop; }			// ���[�v�擾
	inline bool IsWeaponDisp(const int nType) const		{ return m_info.vecMotion[nType].bWeaponDisp; }		// ����\���擾
	inline int GetWholeFrame(const int nType) const		{ return m_info.vecMotion[nType].nWholeFrame; }		// ���[�V�����S�̃t���[�����擾
	inline int GetCancelFrame(const int nType) const	{ return m_info.vecMotion[nType].nCancelFrame; }	// ���[�V�����L�����Z���t���[���擾
	inline int GetComboFrame(const int nType) const		{ return m_info.vecMotion[nType].nComboFrame; }		// ���[�V�����R���{�t���[���擾

	// �ÓI�����o�֐�
	static CMotion* Create(CObjectChara* pChara);	// ����
	static void Release(CMotion*& prMotion);		// �j��

private:
	// �����o�֐�
	void UpdateMove();		// �ړ��X�V
	void UpdateMotion();	// ���[�V�����X�V
	void UpdateBlend();		// �u�����h�X�V

	// �����o�ϐ�
	const std::function<int()> m_funcGetNumParts;	// �p�[�c���擾�֐��|�C���^
	CMultiModel** m_ppModel;	// ���f�����
	CObjectChara* m_pChara;		// �I�u�W�F�N�g�L�����N�^�[���
	SInfo	m_info;		// ���[�V�������
	SBlend	m_blend;	// �u�����h���
	bool	m_bUpdate;	// �X�V��
};

#endif	// _MOTION_H_
