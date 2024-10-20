//============================================================
//
//	�I�u�W�F�N�g�L�����N�^�[2D�w�b�_�[ [objectChara2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECTCHARA2D_H_
#define _OBJECTCHARA2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "anim3D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�L�����N�^�[2D�N���X
class CObjectChara2D : public CAnim3D
{
public:
	// �R���X�g���N�^
	explicit CObjectChara2D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectChara2D() override;

	// �����蔻��Ǘ��\����
	struct SColl
	{
		// �R���X�g���N�^
		SColl() :
			offset	(VEC3_ZERO),	// ���茴�_�I�t�Z�b�g
			size	(VEC3_ZERO)		// ����傫��
		{}

		// �����o�ϐ�
		VECTOR3 offset;	// ���茴�_�I�t�Z�b�g
		VECTOR3 size;	// ����傫��
	};

	// �L�����N�^�[�Ǘ��\����
	struct SChara
	{
		// �R���X�g���N�^
		SChara() :
			ptrnTexture	(GRID2_ZERO),	// �e�N�X�`��������
			nMaxPtrn	(0),			// �ő�p�^�[����
			offset		(VEC3_ZERO),	// ���_�I�t�Z�b�g
			size		(VEC3_ZERO),	// �L�����N�^�[�傫��
			bLoop		(false)			// ���[�vON/OFF
		{
			vecNextTime.clear();	// �p�^�[���ύX���Ԕz����N���A
			sPathTexture.clear();	// �e�N�X�`���p�X���N���A
		}

		// �e�N�X�`���������E�p�^�[�������̐ݒ�
		HRESULT SetTexPtrn(const POSGRID2& rPtrn)
		{
			// �e�N�X�`���������E�p�^�[��������ݒ�
			ptrnTexture = rPtrn;
			nMaxPtrn = rPtrn.x * rPtrn.y;

			// �p�^�[���ύX���Ԃ̔j��
			vecNextTime.clear();

			// �p�^�[���ύX���Ԃ̐���
			vecNextTime.resize(nMaxPtrn);

			// �p�^�[���ύX���Ԃ�������
			if (FAILED(SetNextTime(DEF_NEXT))) { return E_FAIL; }

			return S_OK;
		}

		// �p�^�[���ύX���Ԃ̐ݒ�
		HRESULT SetNextTime(const float fNextTime)
		{
			if (fNextTime <= 0.0f)					 { return E_FAIL; }	// �ύX���Ԃ��v���X�ł͂Ȃ��ꍇ���s
			if (nMaxPtrn != (int)vecNextTime.size()) { return E_FAIL; }	// �p�^�[���ő吔�Ɠ����T�C�Y�ł͂Ȃ��ꍇ���s

			for (int i = 0; i < nMaxPtrn; i++)
			{
				// �����̃p�^�[���ύX���Ԃ�ݒ�
				vecNextTime[i] = fNextTime;
			}

			return S_OK;
		}

		// �����o�ϐ�
		std::vector<float> vecNextTime;	// �p�^�[���ύX���Ԕz��
		std::string sPathTexture;		// �e�N�X�`���p�X
		POSGRID2 ptrnTexture;			// �e�N�X�`��������
		int nMaxPtrn;	// �ő�p�^�[����
		VECTOR3 offset;	// ���_�I�t�Z�b�g
		VECTOR3 size;	// �L�����N�^�[�傫��
		bool bLoop;		// ���[�vON/OFF
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
		SColl infoColl;		// �����蔻����
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

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CObjectChara2D *Create(const VECTOR3& rPos, const VECTOR3& rRot = VEC3_ZERO);	// ����

	// �����o�֐�
	void BindCharaData(const char *pCharaPath);	// �L�����N�^�[��񊄓�
	void SetMotion(const int nType);			// ���[�V�����ݒ�
	void AddInfo(const SMotion& rMotion);		// ���[�V�������ǉ�
	void SetAllInfo(const SInfo& rInfo);		// ���[�V�������S�ݒ�

	bool IsCancel(void) const;	// �L�����Z���擾
	bool IsCombo(void) const;	// �R���{�擾
	int GetMotion(void) const	{ return m_info.nType; }			// ���[�V�����擾
	int GetNumType(void)		{ return m_info.GetNumMotion(); }	// ��ޑ����擾
	float GetCancelTime(const int nType) const	{ return m_info.vecMotion[nType].fCancelTime; }				// �L�����Z�����Ԏ擾
	float GetComboTime(const int nType) const	{ return m_info.vecMotion[nType].fComboTime; }				// �R���{���Ԏ擾
	VECTOR3 GetCollSize(void) const				{ return m_info.vecMotion[m_info.nType].infoColl.size; }	// ����傫���擾

	VECTOR3 CalcOriginOffsetPosition(const VECTOR3& rPos, const VECTOR3& rRot) const;	// ���_�I�t�Z�b�g���f�ʒu�v�Z
	VECTOR3 CalcCollOffsetPosition(const VECTOR3& rPos, const VECTOR3& rRot) const;		// ���茴�_�I�t�Z�b�g���f�ʒu�v�Z
	VECTOR3 GetOriginOffsetPosition(void) const;	// ���_�I�t�Z�b�g���f�ʒu�擾
	VECTOR3 GetCollOffsetPosition(void) const;		// ���茴�_�I�t�Z�b�g���f�ʒu�擾

private:
	// �I�[�o�[���C�h�֐�
	void CalcDrawMatrix(void) override;	// �`��}�g���b�N�X�v�Z

	// �����o�֐�
	VECTOR3 CalcOffsetPosition	// �I�t�Z�b�g���f�ʒu�v�Z
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const VECTOR3& rOffset	// �I�t�Z�b�g
	) const;

	// �����o�ϐ�
	SInfo m_info;	// ���[�V�������
};

#endif	// _OBJECTCHARA2D_H_
