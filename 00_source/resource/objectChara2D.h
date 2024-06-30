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

	// �L�����N�^�[�Ǘ��\����
	struct SChara
	{
		// �R���X�g���N�^
		SChara() :
			ptrnTexture	(GRID2_ZERO),	// �e�N�X�`��������
			nMaxPtrn	(0),			// �ő�p�^�[����
			sizeChara	(VEC3_ZERO),	// �L�����N�^�[�傫��
			pNextTime	(nullptr),		// �p�^�[���ύX����
			bLoop		(false)			// ���[�vON/OFF
		{
			sPassTexture.clear();	// �e�N�X�`���p�X���N���A
		}

		// �f�X�g���N�^
		~SChara() { SAFE_DEL_ARRAY(pNextTime); }	// TODO�F�Ȃ��_���H

		// �e�N�X�`���������E�p�^�[�������̐ݒ菈��
		HRESULT SetTexPtrn(const POSGRID2& rPtrn)
		{
			// �e�N�X�`���������E�p�^�[��������ݒ�
			ptrnTexture = rPtrn;
			nMaxPtrn = rPtrn.x * rPtrn.y;

			// �p�^�[���ύX���Ԃ̔j��
			SAFE_DEL_ARRAY(pNextTime);

			// �p�^�[���ύX���Ԃ̐���
			pNextTime = new float[nMaxPtrn];
			if (pNextTime == nullptr)
			{
				// ���s��Ԃ�
				return E_FAIL;
			}

			// �p�^�[���ύX���Ԃ�������
			SetNextTime(DEF_NEXT);
			return S_OK;
		}

		// �p�^�[���ύX���Ԃ̐ݒ菈��
		HRESULT SetNextTime(const float fNextTime)
		{
			// �ύX���Ԃ��v���X�ł͂Ȃ��ꍇ���s
			if (fNextTime <= 0.0f) { return E_FAIL; }
			for (int i = 0; i < nMaxPtrn; i++)
			{
				// �����̃p�^�[���ύX���Ԃ�ݒ�
				pNextTime[i] = fNextTime;
			}
			return S_OK;
		}

		// �����o�ϐ�
		std::string sPassTexture;	// �e�N�X�`���p�X
		POSGRID2 ptrnTexture;		// �e�N�X�`��������
		int nMaxPtrn;				// �ő�p�^�[����
		D3DXVECTOR3 sizeChara;		// �L�����N�^�[�傫��
		float *pNextTime;			// �p�^�[���ύX����
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

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CObjectChara2D *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot = VEC3_ZERO);	// ����

	// �����o�֐�
	void BindCharaData(const char *pCharaPass);	// �L�����N�^�[��񊄓�
	void SetMotion(const int nType);			// ���[�V�����ݒ�
	void AddInfo(const SMotion& rMotion);		// ���[�V�������ǉ�
	void SetAllInfo(const SInfo& rInfo);		// ���[�V�������S�ݒ�

	bool IsCancel(void) const;	// �L�����Z���擾
	bool IsCombo(void) const;	// �R���{�擾
	int GetMotion(void) const	{ return m_info.nType; }			// ���[�V�����擾
	int GetNumType(void)		{ return m_info.GetNumMotion(); }	// ��ޑ����擾
	float GetCancelTime(const int nType) const	{ return m_info.vecMotion[nType].fCancelTime; }	// �L�����Z�����Ԏ擾
	float GetComboTime(const int nType) const	{ return m_info.vecMotion[nType].fComboTime; }	// �R���{���Ԏ擾

private:
	// �����o�ϐ�
	SInfo m_info;	// ���[�V�������
};

#endif	// _OBJECTCHARA2D_H_
