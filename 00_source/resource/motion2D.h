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

	// �L�����N�^�[�Ǘ��\����
	struct SChara
	{
		// �R���X�g���N�^
		SChara() :
			ptrnTexture	(GRID2_ZERO),	// �e�N�X�`��������
			sizeChara	(VEC3_ZERO),	// �L�����N�^�[�傫��
			fNextTime	(0.0f)			// �p�^�[���ύX����
		{
			sPassTexture.clear();	// �e�N�X�`���p�X���N���A
		}

		// �����o�ϐ�
		std::string sPassTexture;	// �e�N�X�`���p�X
		POSGRID2 ptrnTexture;		// �e�N�X�`��������
		D3DXVECTOR3 sizeChara;		// �L�����N�^�[�傫��
		float fNextTime;			// �p�^�[���ύX����
	};

	// ���[�V�����Ǘ��\����
	struct SMotion
	{
		// �R���X�g���N�^
		SMotion() :
			fWholeTime	(0.0f),		// ���[�V�����S�̎���
			fCancelTime	(-1.0f),	// �L�����Z���\����
			fComboTime	(-1.0f),	// �R���{�\����
			bLoop		(false)		// ���[�vON/OFF
		{}

		// �����o�ϐ�
		SChara infoChara;	// �L�����N�^�[���
		float fWholeTime;	// ���[�V�����S�̎���
		float fCancelTime;	// �L�����Z���\����
		float fComboTime;	// �R���{�\����
		bool bLoop;			// ���[�vON/OFF
	};

	// ���[�V�������\����
	struct SInfo
	{
		// �R���X�g���N�^
		SInfo() :
			fCurTime	(0.0f),	// ���݂̃��[�V�����S�̎���
			bFinish		(true),	// ���[�V�����I����
			nType		(0)		// ���[�V�������
		{
			vecMotion.clear();	// ���[�V���������N���A
		}

		// �����o�֐�
		int GetNumMotion(void) { return (int)vecMotion.size(); }	// ���[�V�������̑����擾

		// �����o�ϐ�
		std::vector<SMotion> vecMotion;	// ���[�V�������
		float fCurTime;	// ���݂̃��[�V�����S�̎���
		bool bFinish;	// ���[�V�����I����
		int nType;		// ���[�V�������
	};

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);		// �X�V
	void SetAllInfo(const SInfo& rInfo);		// ���[�V�������S�ݒ�
	void AddInfo(const SMotion& rMotion);		// ���[�V�������ǉ�
	void SetEnableUpdate(const bool bUpdate);	// �X�V�󋵐ݒ�
	void Set(const int nType);					// �ݒ�

	bool IsCancel(const int nType) const;	// �L�����Z���擾
	bool IsCombo(const int nType) const;	// �R���{�擾
	bool IsFinish(void) const			{ return m_info.bFinish; }					// �I���擾
	bool IsLoop(const int nType) const	{ return m_info.vecMotion[nType].bLoop; }	// ���[�v�擾
	int GetNumType(void)				{ return m_info.GetNumMotion(); }			// ��ޑ����擾
	int GetType(void) const				{ return m_info.nType; }					// ��ގ擾
	float GetCurWholeTime(void) const	{ return m_info.fCurTime; }					// ���݃��[�V�����S�̎��Ԏ擾
	float GetWholeTime(const int nType) const	{ return m_info.vecMotion[nType].fWholeTime; }	// ���[�V�����S�̎��Ԏ擾
	float GetCancelTime(const int nType) const	{ return m_info.vecMotion[nType].fCancelTime; }	// ���[�V�����L�����Z�����Ԏ擾
	float GetComboTime(const int nType) const	{ return m_info.vecMotion[nType].fComboTime; }	// ���[�V�����R���{���Ԏ擾

	// �ÓI�����o�֐�
	static CMotion2D *Create(CObjectChara2D *pChara);	// ����
	static void Release(CMotion2D *&prMotion);			// �j��

private:
	// �����o�֐�
	void UpdateMotion(void);	// ���[�V�����X�V

	// �����o�ϐ�
	CObjectChara2D *m_pChara;	// �I�u�W�F�N�g�L�����N�^�[2D���
	SInfo m_info;	// ���[�V�������
	bool m_bUpdate;	// �X�V��
};

#endif	// _MOTION2D_H_
