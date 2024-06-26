//============================================================
//
//	���[�V�������� [motion2D.cpp]
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
	// ���[�V�������̓��I�z��̃N���A
	ClearVector();
}

//============================================================
//	�X�V����
//============================================================
void CMotion2D::Update(const float fDeltaTime)
{
	// �X�V��~���̏ꍇ������
	if (!m_bUpdate) { return; }

	// �L�[�������ݒ�̏ꍇ������
	if (m_info.vecMotion[m_info.nType].GetNumKey() <= 0) { return; }

	// ���[�V�����̍X�V
	UpdateMotion();

	// �ړ��̍X�V
	UpdateMove();
}

//============================================================
//	�p�[�c���̐ݒ菈��
//============================================================
void CMotion2D::BindPartsData(/*CMultiModel **ppModel*/)
{
#if 0
	// �����̃��f������ݒ�
	m_ppModel = ppModel;
#endif
}

//============================================================
//	���[�V�������S�ݒ菈��
//============================================================
void CMotion2D::SetAllInfo(const SInfo& rInfo)
{
	for (auto& rVec : rInfo.vecMotion)
	{ // �ǂݍ��񂾃��[�V���������J��Ԃ�

		// ���[�V�������̒ǉ�
		AddInfo(rVec);
	}
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

	// ���[�V�����S�̃t���[������ݒ�
	int nSubKey = (m_info.vecMotion[nSetMotionID].bLoop) ? 0 : 1;		// ���[�v���Ȃ��ꍇ�Ō�̃L�[�͊܂܂Ȃ�
	int nLoop = m_info.vecMotion[nSetMotionID].GetNumKey() - nSubKey;	// �J��Ԃ��������߂�
	for (int nCntKey = 0; nCntKey < nLoop; nCntKey++)
	{ // �L�[�̑������J��Ԃ�

		// �L�[�̃t���[���������Z
		m_info.vecMotion[nSetMotionID].nWholeFrame += m_info.vecMotion[nSetMotionID].vecKey[nCntKey].nFrame;
	}
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
//	���[�V�������̓��I�z��̃N���A����
//============================================================
void CMotion2D::ClearVector(void)
{
	for (auto& rMotionInfo : m_info.vecMotion)
	{ // ���[�V�������̗v�f�����J��Ԃ�

		// �L�[�����N���A
		rMotionInfo.vecKey.clear();
	}

	// ���[�V���������N���A
	m_info.vecMotion.clear();
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
	m_info.nKey			 = 0;		// ���[�V�����L�[�ԍ�
	m_info.nKeyCounter	 = 0;		// ���[�V�����L�[�J�E���^�[
	m_info.nWholeCounter = 0;		// ���[�V�����S�̃J�E���^�[
	m_info.bFinish		 = false;	// ���[�V�����I����

	// TODO�F�����ŕύX��̃h�b�g�G�ɑJ��
}

//============================================================
//	��ނ̑����擾����
//============================================================
int CMotion2D::GetNumType(void)
{
	// ���[�V�����̎�ނ̑�����Ԃ�
	return m_info.GetNumMotion();
}

//============================================================
//	�L�[�̑����擾����
//============================================================
int CMotion2D::GetNumKey(const int nType)
{
	// �������[�V�����̃L�[�̑�����Ԃ�
	int nSubKey = (m_info.vecMotion[m_info.GetNumMotion()].bLoop) ? 0 : 1;	// ���[�v���Ȃ��ꍇ�Ō�̃L�[�͊܂܂Ȃ�
	return m_info.vecMotion[nType].GetNumKey() - nSubKey;
}

//============================================================
//	�L�����Z���擾����
//============================================================
bool CMotion2D::IsCancel(const int nType) const
{
	if (m_info.vecMotion[nType].nCancelFrame != NONE_IDX)
	{ // �L�����Z���t���[�����ݒ肳��Ă���ꍇ

		// �������[�V�����̃L�����Z���󋵂�Ԃ�
		return (m_info.nWholeCounter >= m_info.vecMotion[nType].nCancelFrame);
	}

	// �L�����Z���s��Ԃ�
	return false;
}

//============================================================
//	�R���{�擾����
//============================================================
bool CMotion2D::IsCombo(const int nType) const
{
	if (m_info.vecMotion[nType].nComboFrame != NONE_IDX)
	{ // �R���{�t���[�����ݒ肳��Ă���ꍇ

		// �������[�V�����̃R���{�󋵂�Ԃ�
		return (m_info.nWholeCounter >= m_info.vecMotion[nType].nComboFrame);
	}

	// �R���{�s��Ԃ�
	return false;
}

//============================================================
//	��������
//============================================================
CMotion2D *CMotion2D::Create(CObjectChara2D *pChara2D)
{
	// ���[�V�����̐���
	CMotion2D *pMotion = new CMotion2D;
	if (pMotion == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���[�V�����̏�����
		if (FAILED(pMotion->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���[�V�����̔j��
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
	// ���[�V�����̏I��
	assert(prMotion2D != nullptr);
	prMotion2D->Uninit();

	// �������J��
	SAFE_DELETE(prMotion2D);
}

//============================================================
//	�ړ��̍X�V����
//============================================================
void CMotion2D::UpdateMove(void)
{
	if (m_pChara == nullptr) { return; }	// �I�u�W�F�N�g�L�����N�^�[���ݒ�

	// �ϐ���錾
	D3DXMATRIX  mtxChara	= m_pChara->GetMtxWorld();				// �L�����}�g���b�N�X
	D3DXVECTOR3 posSetChara	= m_pChara->GetVec3Position();			// �L�����ݒ�ʒu
	D3DXVECTOR3 posOldChara	= useful::GetMatrixPosition(mtxChara);	// �L�����ߋ��ʒu
	D3DXVECTOR3 posCurChara	= VEC3_ZERO;							// �L�������݈ʒu

	// �ړ��ʂ����߂�
	float fRate = 1.0f / (float)m_info.vecMotion[m_info.nType].vecKey[m_info.nKey].nFrame;	// �L�[�t���[������
	D3DXVECTOR3 moveRate = m_info.vecMotion[m_info.nType].vecKey[m_info.nKey].move * fRate;	// �t���[���ړ���

	if (m_info.vecMotion[m_info.nType].vecKey[m_info.nKey].nFrame > 0)
	{ // �t���[�����ݒ肳��Ă���ꍇ

		// �ړ��ʂ��}�g���b�N�X�ɔ��f
		D3DXMATRIX mtxMove;	// �}�g���b�N�X�v�Z�p
		D3DXMatrixTranslation(&mtxMove, moveRate.x, moveRate.y, moveRate.z);
		D3DXMatrixMultiply(&mtxChara, &mtxMove, &mtxChara);

		// �ړ��ʂ�^�����}�g���b�N�X�̃��[���h���W�����߂�
		posCurChara = useful::GetMatrixPosition(mtxChara);

		// �ߋ��ƌ��݂̈ʒu����ړ��ʂ����߁A�ʒu�ɗ^����
		posSetChara += posOldChara - posCurChara;

		// �ʒu�𔽉f
		m_pChara->SetVec3Position(posSetChara);
	}
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
