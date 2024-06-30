//============================================================
//
//	���[�V����2D���� [motion2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "motion2D.h"
#include "objectChara2D.h"

//************************************************************
//	�e�N���X [CMotion2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CMotion2D::CMotion2D() :
	m_pChara	(nullptr)	// �I�u�W�F�N�g�L�����N�^�[���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CMotion2D::~CMotion2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CMotion2D::Init(void)
{
	// �����o�ϐ����N���A
	m_pChara = nullptr;	// �I�u�W�F�N�g�L�����N�^�[���

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CMotion2D::Uninit(void)
{
	// ���[�V���������N���A
	m_info.vecMotion.clear();
}

//============================================================
//	�X�V����
//============================================================
void CMotion2D::Update(const float fDeltaTime)
{
	// ���[�V�������Ȃ��ꍇ������
	if (m_info.vecMotion.empty()) { return; }
}

//============================================================
//	�ݒ菈��
//============================================================
void CMotion2D::Set(const int nType)
{
	// �w�肳�ꂽ���[�V���������݂��Ȃ��ꍇ������
	if (nType <= NONE_IDX || nType >= m_info.GetNumMotion()) { assert(false); return; }

	// �����̃��[�V�����̎�ނ�ݒ�
	m_info.nType = nType;

	// �ϐ����|�C���^�����ȗ���
	SChara *pInfoChara = &m_info.vecMotion[nType].infoChara;	// �L�����N�^�[���

	// �w��e�N�X�`���̊���
	m_pChara->BindTexture(pInfoChara->sPassTexture.c_str());

	// �L�����N�^�[����ݒ�
	m_pChara->SetTexPtrn(pInfoChara->ptrnTexture);	// �e�N�X�`��������
	m_pChara->SetNextTime(pInfoChara->fNextTime);	// �p�^�[���ύX����
	m_pChara->SetEnableLoop(pInfoChara->bLoop);		// ���[�vON/OFF
	m_pChara->SetVec3Sizing(pInfoChara->sizeChara);	// �傫��

	// �L�����N�^�[����������
	m_pChara->ResetCurPtrn();	// �J�n�p�^�[��
	m_pChara->ResetNumLoop();	// �J��Ԃ���
}

//============================================================
//	���[�V�������̒ǉ�����
//============================================================
void CMotion2D::AddInfo(const SMotion& rMotion)
{
	int nSetMotionID = m_info.GetNumMotion();	// ���[�V������ݒ肷��z��ԍ�

	// ��̗v�f���Ō���ɒǉ�
	m_info.vecMotion.emplace_back();

	// �����̃��[�V��������ݒ�
	m_info.vecMotion[nSetMotionID] = rMotion;
}

//============================================================
//	���[�V�������S�ݒ菈��
//============================================================
void CMotion2D::SetAllInfo(const SInfo& rInfo)
{
	// ���[�V���������N���A
	m_info.vecMotion.clear();

	for (auto& rVec : rInfo.vecMotion)
	{ // �ǂݍ��񂾃��[�V���������J��Ԃ�

		// ���[�V�������̒ǉ�
		AddInfo(rVec);
	}
}

//============================================================
//	�L�����Z���擾����
//============================================================
bool CMotion2D::IsCancel(void) const
{
	float fCancelTime = m_info.vecMotion[m_info.nType].fCancelTime;	// �L�����Z���\����
	if (fCancelTime >= 0.0f)
	{ // �L�����Z���\���Ԃ��ݒ肳��Ă���ꍇ

		// ���[�V�����̃L�����Z���󋵂�Ԃ�
		return (m_pChara->GetCurWholeTime() >= fCancelTime);
	}

	// �L�����Z���s��Ԃ�
	return false;
}

//============================================================
//	�R���{�擾����
//============================================================
bool CMotion2D::IsCombo(void) const
{
	float fComboTime = m_info.vecMotion[m_info.nType].fComboTime;	// �R���{�\����
	if (fComboTime >= 0.0f)
	{ // �R���{�\���Ԃ��ݒ肳��Ă���ꍇ

		// ���[�V�����̃R���{�󋵂�Ԃ�
		return (m_pChara->GetCurWholeTime() >= fComboTime);
	}

	// �R���{�s��Ԃ�
	return false;
}

//============================================================
//	��������
//============================================================
CMotion2D *CMotion2D::Create(CObjectChara2D *pChara2D)
{
	// ���[�V����2D�̐���
	CMotion2D *pMotion = new CMotion2D;
	if (pMotion == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���[�V����2D�̏�����
		if (FAILED(pMotion->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���[�V����2D�̔j��
			SAFE_DELETE(pMotion);
			return nullptr;
		}

		// �I�u�W�F�N�g�L�����N�^�[��ݒ�
		pMotion->m_pChara = pChara2D;

		// �m�ۂ����A�h���X��Ԃ�
		return pMotion;
	}
}

//============================================================
//	�j������
//============================================================
void CMotion2D::Release(CMotion2D *&prMotion2D)
{
	// ���[�V����2D�̏I��
	assert(prMotion2D != nullptr);
	prMotion2D->Uninit();

	// �������J��
	SAFE_DELETE(prMotion2D);
}
