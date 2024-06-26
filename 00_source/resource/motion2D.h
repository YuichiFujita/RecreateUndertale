//============================================================
//
//	���[�V����2D�w�b�_�[ [motion2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MOTION2D_H_
#define _MOTION2D_H_

//************************************************************
//	�O���錾
//************************************************************
class CObjectChara2D;	// �I�u�W�F�N�g�L�����N�^�[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ���[�V����2D�N���X
class CMotion2D
{
public:
	// �R���X�g���N�^
	CMotion2D();

	// �f�X�g���N�^
	~CMotion2D();

	// �L�[�Ǘ��\����
	struct SKey
	{
		// �R���X�g���N�^
		SKey() :
			move	(VEC3_ZERO),	// �L�[�ړ���
			nFrame	(0)				// �L�[�Đ��t���[����
		{}

		// �����o�ϐ�
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
			bLoop			(false)		// ���[�vON/OFF
		{
			vecKey.clear();	// �L�[�����N���A
		}

		// �����o�֐�
		int GetNumKey(void) { return (int)vecKey.size(); }	// �L�[���̑����擾

		// �����o�ϐ�
		std::vector<SKey> vecKey;	// �L�[���
		int  nWholeFrame;	// ���[�V�����S�̃t���[����
		int  nCancelFrame;	// �L�����Z���\�t���[��
		int  nComboFrame;	// �R���{�\�t���[��
		bool bLoop;			// ���[�vON/OFF
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
			bFinish			(true)	// ���[�V�����I����
		{
			vecMotion.clear();	// ���[�V���������N���A
		}

		// �����o�֐�
		int GetNumMotion(void) { return (int)vecMotion.size(); }	// ���[�V�������̑����擾

		// �����o�ϐ�
		std::vector<SMotion> vecMotion;	// ���[�V�������
		int  nType;			// ���[�V�������
		int  nKey;			// ���[�V�����L�[�ԍ�
		int  nKeyCounter;	// ���[�V�����L�[�J�E���^�[
		int  nWholeCounter;	// ���[�V�����S�̃J�E���^�[
		bool bFinish;		// ���[�V�����I����
	};

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);		// �X�V
	void BindPartsData(/*CMultiModel **ppModel*/);	// �p�[�c���ݒ�
	void SetAllInfo(const SInfo& rInfo);		// ���[�V�������S�ݒ�
	void AddInfo(const SMotion& rMotion);		// ���[�V�������ǉ�
	void SetEnableUpdate(const bool bUpdate);	// �X�V�󋵐ݒ�
	void ClearVector(void);						// ���[�V�������̓��I�z��N���A
	void Set(const int nType);					// �ݒ�
	int GetNumType(void);						// ��ޑ����擾
	int GetNumKey(const int nType);				// �L�[�����擾
	bool IsCancel(const int nType) const;		// �L�����Z���擾
	bool IsCombo(const int nType) const;		// �R���{�擾

	int GetType(void) const			{ return m_info.nType; }			// ��ގ擾
	int GetKey(void) const			{ return m_info.nKey; }				// �L�[�ԍ��擾
	int GetKeyCounter(void) const	{ return m_info.nKeyCounter; }		// ���[�V�����L�[�J�E���^�[�擾
	int GetWholeCounter(void) const	{ return m_info.nWholeCounter; }	// ���[�V�����S�̃J�E���^�[�擾
	bool IsFinish(void) const		{ return m_info.bFinish; }			// �I���擾
	bool IsLoop(const int nType) const			{ return m_info.vecMotion[nType].bLoop; }			// ���[�v�擾
	int GetWholeFrame(const int nType) const	{ return m_info.vecMotion[nType].nWholeFrame; }		// ���[�V�����S�̃t���[�����擾
	int GetCancelFrame(const int nType) const	{ return m_info.vecMotion[nType].nCancelFrame; }	// ���[�V�����L�����Z���t���[���擾
	int GetComboFrame(const int nType) const	{ return m_info.vecMotion[nType].nComboFrame; }		// ���[�V�����R���{�t���[���擾

	// �ÓI�����o�֐�
	static CMotion2D *Create(CObjectChara2D *pChara);	// ����
	static void Release(CMotion2D *&prMotion);			// �j��

private:
	// �����o�֐�
	void UpdateMove(void);		// �ړ��X�V
	void UpdateMotion(void);	// ���[�V�����X�V

	// �����o�ϐ�
	CObjectChara2D *m_pChara;	// �I�u�W�F�N�g�L�����N�^�[2D���
	SInfo m_info;	// ���[�V�������
	bool m_bUpdate;	// �X�V��
};

#endif	// _MOTION2D_H_
