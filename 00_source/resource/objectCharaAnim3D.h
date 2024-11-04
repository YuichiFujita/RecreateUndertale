//============================================================
//
//	�I�u�W�F�N�g�L�����N�^�[�A�j���[�V����3D�w�b�_�[ [objectCharaAnim3D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECTCHARA_ANIM3D_H_
#define _OBJECTCHARA_ANIM3D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "anim3D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�L�����N�^�[�A�j���[�V����3D�N���X
class CObjectCharaAnim3D : public CAnim3D
{
public:
	// �R���X�g���N�^
	explicit CObjectCharaAnim3D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectCharaAnim3D() override;

	// �����蔻��Ǘ��\����
	struct SColl
	{
		// �f�t�H���g�R���X�g���N�^
		SColl() :
			offset	(VEC3_ZERO),	// ���茴�_�I�t�Z�b�g
			size	(VEC3_ZERO)		// ����傫��
		{}

		// �f�X�g���N�^
		~SColl() {}

		// �����o�ϐ�
		VECTOR3 offset;	// ���茴�_�I�t�Z�b�g
		VECTOR3 size;	// ����傫��
	};

	// �L�����N�^�[�Ǘ��\����
	struct SChara
	{
		// �f�t�H���g�R���X�g���N�^
		SChara() :
			vecNextTime	 ({}),			// �p�^�[���ύX���Ԕz��
			sPathTexture (""),			// �e�N�X�`���p�X���N���A
			ptrnTexture	 (GRID2_ZERO),	// �e�N�X�`��������
			nMaxPtrn	 (0),			// �ő�p�^�[����
			offset		 (VEC3_ZERO),	// ���_�I�t�Z�b�g
			size		 (VEC3_ZERO),	// �L�����N�^�[�傫��
			bLoop		 (false)		// ���[�vON/OFF
		{}

		// �f�X�g���N�^
		~SChara() {}

		// �e�N�X�`���������E�p�^�[�������̐ݒ�
		inline HRESULT SetTexPtrn(const POSGRID2& rPtrn)
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
		inline HRESULT SetNextTime(const float fNextTime)
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
		// �f�t�H���g�R���X�g���N�^
		SMotion() :
			infoChara	({}),		// �L�����N�^�[���
			infoColl	({}),		// �����蔻����
			fCancelTime	(-1.0f),	// �L�����Z���\����
			fComboTime	(-1.0f)		// �R���{�\����
		{}

		// �f�X�g���N�^
		~SMotion() {}

		// �����o�ϐ�
		SChara infoChara;	// �L�����N�^�[���
		SColl infoColl;		// �����蔻����
		float fCancelTime;	// �L�����Z���\����
		float fComboTime;	// �R���{�\����
	};

	// ���[�V�������\����
	struct SInfo
	{
		// �f�t�H���g�R���X�g���N�^
		SInfo() :
			vecMotion	({}),	// ���[�V�������
			nType		(0)		// ���[�V�������
		{}

		// �f�X�g���N�^
		~SInfo() {}

		// �����o�֐�
		inline int GetNumMotion() { return (int)vecMotion.size(); }	// ���[�V�������̑����擾

		// �����o�ϐ�
		std::vector<SMotion> vecMotion;	// ���[�V�������
		int nType;	// ���[�V�������
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CObjectCharaAnim3D* Create(const VECTOR3& rPos, const VECTOR3& rRot = VEC3_ZERO);	// ����

	// �����o�֐�
	void BindCharaData(const char* pCharaPath);	// �L�����N�^�[��񊄓�
	void SetMotion(const int nType);			// ���[�V�����ݒ�
	void AddInfo(const SMotion& rMotion);		// ���[�V�������ǉ�
	void SetAllInfo(const SInfo& rInfo);		// ���[�V�������S�ݒ�

	bool IsCancel() const;	// �L�����Z���擾
	bool IsCombo() const;	// �R���{�擾
	inline int GetMotion() const	{ return m_info.nType; }			// ���[�V�����擾
	inline int GetNumType()			{ return m_info.GetNumMotion(); }	// ��ޑ����擾
	inline float GetCancelTime(const int nType) const	{ return m_info.vecMotion[nType].fCancelTime; }				// �L�����Z�����Ԏ擾
	inline float GetComboTime(const int nType) const	{ return m_info.vecMotion[nType].fComboTime; }				// �R���{���Ԏ擾
	inline VECTOR3 GetCollSize() const					{ return m_info.vecMotion[m_info.nType].infoColl.size; }	// ����傫���擾

	VECTOR3 CalcOriginOffsetPosition(const VECTOR3& rPos, const VECTOR3& rRot) const;	// ���_�I�t�Z�b�g���f�ʒu�v�Z
	VECTOR3 CalcCollOffsetPosition(const VECTOR3& rPos, const VECTOR3& rRot) const;		// ���茴�_�I�t�Z�b�g���f�ʒu�v�Z
	VECTOR3 GetOriginOffsetPosition() const;	// ���_�I�t�Z�b�g���f�ʒu�擾
	VECTOR3 GetCollOffsetPosition() const;		// ���茴�_�I�t�Z�b�g���f�ʒu�擾

private:
	// �I�[�o�[���C�h�֐�
	void CalcDrawMatrix() override;	// �`��}�g���b�N�X�v�Z

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

#endif	// _OBJECTCHARA_ANIM3D_H_
