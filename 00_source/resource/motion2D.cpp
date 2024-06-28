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
	m_pChara	(nullptr),	// �I�u�W�F�N�g�L�����N�^�[���
	m_bUpdate	(true)		// �X�V��
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
	m_pChara	= nullptr;	// �I�u�W�F�N�g�L�����N�^�[���
	m_bUpdate	= true;		// �X�V��

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
	// �X�V��~���̏ꍇ������
	if (!m_bUpdate) { return; }

	// ���[�V�������Ȃ��ꍇ������
	if (m_info.vecMotion.empty()) { return; }

	// ���[�V�����̍X�V
	UpdateMotion();
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CMotion2D::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	m_bUpdate = bUpdate;
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

	// ���[�V��������������
	m_info.fCurTime	= 0.0f;		// ���݂̃��[�V�����S�̎���
	m_info.bFinish	= false;	// ���[�V�����I����

	// �L�����N�^�[����ݒ�	// TODO�F����ő��v�H
	SChara *pInfoChara = &m_info.vecMotion[nType].infoChara;	// �L�����N�^�[���
	m_pChara->BindTexture(pInfoChara->sPassTexture.c_str());	// �e�N�X�`��������
	m_pChara->SetTexPtrn(pInfoChara->ptrnTexture);				// �e�N�X�`����������ݒ�
	m_pChara->SetNextTime(pInfoChara->fNextTime);				// �p�^�[���ύX���Ԃ�ݒ�
	m_pChara->SetVec3Sizing(pInfoChara->sizeChara);				// �傫����ݒ�
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

	// ���[�V�����S�̎��Ԃ�ݒ�	// TODO�F�����ł��Ă�H
	int nLoop = m_info.vecMotion[nSetMotionID].infoChara.nMaxPtrn;	// �J��Ԃ���
	for (int nCntPtrn = 0; nCntPtrn < nLoop; nCntPtrn++)
	{ // �p�^�[���̑������J��Ԃ�

		// �p�^�[���̕ύX���Ԃ����Z
		m_info.vecMotion[nSetMotionID].fWholeTime += m_info.vecMotion[nSetMotionID].infoChara.fNextTime;
	}
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
bool CMotion2D::IsCancel(const int nType) const
{
	if (m_info.vecMotion[nType].fCancelTime >= 0.0f)
	{ // �L�����Z���t���[�����ݒ肳��Ă���ꍇ

		// �������[�V�����̃L�����Z���󋵂�Ԃ�
		return (m_info.fCurTime >= m_info.vecMotion[nType].fCancelTime);
	}

	// �L�����Z���s��Ԃ�
	return false;
}

//============================================================
//	�R���{�擾����
//============================================================
bool CMotion2D::IsCombo(const int nType) const
{
	if (m_info.vecMotion[nType].fComboTime >= 0.0f)
	{ // �R���{�t���[�����ݒ肳��Ă���ꍇ

		// �������[�V�����̃R���{�󋵂�Ԃ�
		return (m_info.fCurTime >= m_info.vecMotion[nType].fComboTime);
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

//============================================================
//	���[�V�����̍X�V����
//============================================================
void CMotion2D::UpdateMotion(void)
{
#if 0
	int nType = m_info.nType;	// ���[�V�������
	int nKey  = m_info.nKey;	// ���[�V�����L�[�ԍ�

	// ���̃��[�V�����L�[�ԍ������߂�
	int nNextKey = (nKey + 1) % m_info.vecMotion[nType].GetNumKey();

	// �p�[�c�̈ʒu�̍X�V
	for (int nCntParts = 0; nCntParts < m_funcGetNumParts(); nCntParts++)
	{ // �p�[�c�����J��Ԃ�

		// �ʒu�E�����̍��������߂�
		D3DXVECTOR3 diffPos = m_info.vecMotion[nType].vecKey[nNextKey].vecParts[nCntParts].pos - m_info.vecMotion[nType].vecKey[nKey].vecParts[nCntParts].pos;
		D3DXVECTOR3 diffRot = m_info.vecMotion[nType].vecKey[nNextKey].vecParts[nCntParts].rot - m_info.vecMotion[nType].vecKey[nKey].vecParts[nCntParts].rot;
		useful::NormalizeRot(diffRot);	// ���������̐��K��

		// ���݂̃p�[�c�̈ʒu�E�������X�V
		float fRate = (float)m_info.nKeyCounter / (float)m_info.vecMotion[nType].vecKey[nKey].nFrame;	// �L�[�t���[������
		m_ppModel[nCntParts]->SetVec3Position(m_info.vecMotion[nType].vecKey[nKey].vecParts[nCntParts].pos + diffPos * fRate);
		m_ppModel[nCntParts]->SetVec3Rotation(m_info.vecMotion[nType].vecKey[nKey].vecParts[nCntParts].rot + diffRot * fRate);
	}

	// ���[�V�����̑J�ڂ̍X�V
	if (m_info.nKeyCounter < m_info.vecMotion[nType].vecKey[nKey].nFrame)
	{ // ���݂̃L�[�̍Đ����I�����Ă��Ȃ��ꍇ

		// �J�E���^�[�����Z
		m_info.nKeyCounter++;
		m_info.nWholeCounter++;
	}
	else
	{ // ���݂̃L�[�̍Đ����I�������ꍇ

		// ���̃L�[�Ɉڍs
		if (m_info.vecMotion[nType].bLoop)
		{ // ���[�V���������[�v����ꍇ

			// �L�[�J�E���^�[��������
			m_info.nKeyCounter = 0;

			// �L�[�J�E���g�����Z
			m_info.nKey = (m_info.nKey + 1) % m_info.vecMotion[nType].GetNumKey();	// �ő�l��0�ɖ߂�

			if (m_info.nKey == 0)
			{ // �L�[���ŏ��ɖ߂����ꍇ

				// �S�̃J�E���^�[��������
				m_info.nWholeCounter = 0;
			}
		}
		else
		{ // ���[�V���������[�v���Ȃ��ꍇ

			if (m_info.nKey < m_info.vecMotion[nType].GetNumKey() - 2)
			{ // ���݂̃L�[���ŏI�̃L�[�ł͂Ȃ��ꍇ

				// �L�[�J�E���^�[��������
				m_info.nKeyCounter = 0;

				// �L�[�J�E���g�����Z
				m_info.nKey++;
			}
			else
			{ // ���݂̃L�[���ŏI�̃L�[�̏ꍇ

				// ���[�V�������I����Ԃɂ���
				m_info.bFinish = true;
			}
		}
	}
#endif
}
