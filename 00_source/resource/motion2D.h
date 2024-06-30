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
			nMaxPtrn	(0),			// �ő�p�^�[����
			sizeChara	(VEC3_ZERO),	// �L�����N�^�[�傫��
			fNextTime	(0.0f),			// �p�^�[���ύX����
			bLoop		(false)			// ���[�vON/OFF
		{
			sPassTexture.clear();	// �e�N�X�`���p�X���N���A
		}

		// �����o�ϐ�
		std::string sPassTexture;	// �e�N�X�`���p�X
		POSGRID2 ptrnTexture;		// �e�N�X�`��������
		int nMaxPtrn;				// �ő�p�^�[����
		D3DXVECTOR3 sizeChara;		// �L�����N�^�[�傫��
		float fNextTime;			// �p�^�[���ύX����
		bool bLoop;					// ���[�vON/OFF
	};

	// ���[�V�����Ǘ��\����
	struct SMotion
	{
		// �R���X�g���N�^
		SMotion() :
			fCancelTime	(-1.0f),	// �L�����Z���\����
			fComboTime	(-1.0f)		// �R���{�\����
		{}

		// �����o�ϐ�
		SChara infoChara;	// �L�����N�^�[���
		float fCancelTime;	// �L�����Z���\����
		float fComboTime;	// �R���{�\����
	};

	// ���[�V�������\����
	struct SInfo
	{
		// �R���X�g���N�^
		SInfo() :
			nType	(0)	// ���[�V�������
		{
			vecMotion.clear();	// ���[�V���������N���A
		}

		// �����o�֐�
		int GetNumMotion(void) { return (int)vecMotion.size(); }	// ���[�V�������̑����擾

		// �����o�ϐ�
		std::vector<SMotion> vecMotion;	// ���[�V�������
		int nType;	// ���[�V�������
	};

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);	// �X�V
	void Set(const int nType);				// �ݒ�
	void AddInfo(const SMotion& rMotion);	// ���[�V�������ǉ�
	void SetAllInfo(const SInfo& rInfo);	// ���[�V�������S�ݒ�

	bool IsCancel(void) const;	// �L�����Z���擾
	bool IsCombo(void) const;	// �R���{�擾
	int GetNumType(void)		{ return m_info.GetNumMotion(); }	// ��ޑ����擾
	int GetType(void) const		{ return m_info.nType; }			// ��ގ擾
	float GetCancelTime(const int nType) const	{ return m_info.vecMotion[nType].fCancelTime; }	// ���[�V�����L�����Z�����Ԏ擾
	float GetComboTime(const int nType) const	{ return m_info.vecMotion[nType].fComboTime; }	// ���[�V�����R���{���Ԏ擾

	// �ÓI�����o�֐�
	static CMotion2D *Create(CObjectChara2D *pChara);	// ����
	static void Release(CMotion2D *&prMotion);			// �j��

private:
	// �����o�ϐ�
	CObjectChara2D *m_pChara;	// �I�u�W�F�N�g�L�����N�^�[2D���
	SInfo m_info;	// ���[�V�������
};

#endif	// _MOTION2D_H_
