//============================================================
//
//	���[�V�������� [motion.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "motion.h"
#include "multiModel.h"
#include "objectChara.h"

//************************************************************
//	�e�N���X [CMotion] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CMotion::CMotion(std::function<int(void)> funcGetNumParts) :
	m_funcGetNumParts(funcGetNumParts),	// �p�[�c���擾�֐��|�C���^
	m_ppModel	(nullptr),	// ���f�����
	m_pChara	(nullptr),	// �I�u�W�F�N�g�L�����N�^�[���
	m_bUpdate	(true)		// �X�V��
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CMotion::~CMotion()
{

}

//============================================================
//	����������
//============================================================
HRESULT CMotion::Init(void)
{
	// �����o�ϐ����N���A
	m_ppModel	= nullptr;	// ���f�����
	m_pChara	= nullptr;	// �I�u�W�F�N�g�L�����N�^�[���
	m_bUpdate	= true;		// �X�V��

	// ���[�V�������I����Ԃɂ���
	m_info.bFinish = true;

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CMotion::Uninit(void)
{
	// ���[�V�������̓��I�z��̃N���A
	ClearVector();
}

//============================================================
//	�X�V����
//============================================================
void CMotion::Update(const float fDeltaTime)
{
	if (!m_bUpdate) { return; }	// �X�V���Ȃ�
	if (m_info.vecMotion[m_info.nType].GetNumKey() <= 0) { return; }	// �L�[�����ݒ�

	if (m_blend.nFrame > 0)
	{ // �u�����h�t���[�����ݒ肳��Ă���ꍇ

		// �u�����h�̍X�V
		UpdateBlend();
	}
	else
	{ // �u�����h�t���[�����ݒ肳��Ă��Ȃ��ꍇ

		// ���[�V�����̍X�V
		UpdateMotion();
	}

	// �ړ��̍X�V
	UpdateMove();
}

//============================================================
//	�p�[�c���̐ݒ菈��
//============================================================
void CMotion::BindPartsData(CMultiModel **ppModel)
{
	// �����̃��f������ݒ�
	m_ppModel = ppModel;
}

//============================================================
//	���[�V�������S�ݒ菈��
//============================================================
void CMotion::SetAllInfo(const SInfo& rInfo)
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
void CMotion::AddInfo(const SMotion& rMotion)
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
void CMotion::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	m_bUpdate = bUpdate;
}

//============================================================
//	�p�[�c���ݒ�̐ݒ菈��
//============================================================
void CMotion::SetNumParts(const int nNumParts)
{
	// �p�[�c���_�����N���A
	m_info.vecOriginParts.clear();

	// �p�[�c���_�𐶐�
	m_info.vecOriginParts.resize((size_t)nNumParts);

	// �u�����h�J�n�p�[�c�����N���A
	m_blend.vecParts.clear();

	// �u�����h�J�n�p�[�c�𐶐�
	m_blend.vecParts.resize((size_t)nNumParts);
}

//============================================================
//	���[�V�������̓��I�z��̃N���A����
//============================================================
void CMotion::ClearVector(void)
{
	for (auto& rMotionInfo : m_info.vecMotion)
	{ // ���[�V�������̗v�f�����J��Ԃ�

		for (auto& rKeyInfo : rMotionInfo.vecKey)
		{ // �L�[���̗v�f�����J��Ԃ�

			// �p�[�c�����N���A
			rKeyInfo.vecParts.clear();
		}

		// �L�[�����N���A
		rMotionInfo.vecKey.clear();
	}

	// ���[�V���������N���A
	m_info.vecMotion.clear();

	// �p�[�c���_�����N���A
	m_info.vecOriginParts.clear();

	// �u�����h�J�n�p�[�c�����N���A
	m_blend.vecParts.clear();
}

//============================================================
//	�ݒ菈��
//============================================================
void CMotion::Set(const int nType, const int nBlendFrame)
{
	// �w�肳�ꂽ���[�V���������݂��Ȃ��ꍇ������
	if (nType <= NONE_IDX || nType >= m_info.GetNumMotion()) { assert(false); return; }

	// �����̃��[�V�����̎�ނ�ݒ�
	m_info.nType = nType;

	// �����̃u�����h�t���[����ݒ�
	m_blend.nFrame = nBlendFrame;

	// ���[�V��������������
	m_info.nKey			 = 0;		// ���[�V�����L�[�ԍ�
	m_info.nKeyCounter	 = 0;		// ���[�V�����L�[�J�E���^�[
	m_info.nWholeCounter = 0;		// ���[�V�����S�̃J�E���^�[
	m_info.bFinish		 = false;	// ���[�V�����I����

	// �u�����h����������
	m_blend.nWholeCounter = 0;		// �u�����h�S�̃J�E���^�[

	// �p�[�c�̈ʒu�̏�����
	if (m_blend.nFrame > 0)
	{ // �u�����h�t���[�����ݒ肳��Ă���ꍇ

		for (int nCntParts = 0; nCntParts < m_funcGetNumParts(); nCntParts++)
		{ // �p�[�c�����J��Ԃ�

			// ���݈ʒu�ƌ��݌�����ۑ�
			m_blend.vecParts[nCntParts].pos = m_ppModel[nCntParts]->GetVec3Position();
			m_blend.vecParts[nCntParts].rot = m_ppModel[nCntParts]->GetVec3Rotation();
		}
	}
	else
	{ // �u�����h�t���[�����ݒ肳��Ă��Ȃ��ꍇ

		for (int nCntParts = 0; nCntParts < m_funcGetNumParts(); nCntParts++)
		{ // �p�[�c�����J��Ԃ�

			// �����ʒu�Ə���������ݒ�
			m_ppModel[nCntParts]->SetVec3Position(m_info.vecMotion[nType].vecKey[m_info.nKey].vecParts[nCntParts].pos);
			m_ppModel[nCntParts]->SetVec3Rotation(m_info.vecMotion[nType].vecKey[m_info.nKey].vecParts[nCntParts].rot);
		}
	}
}

//============================================================
//	���_�ʒu�̐ݒ菈��
//============================================================
void CMotion::SetOriginPosition(const D3DXVECTOR3& rPos, const int nParts)
{
	if (nParts > NONE_IDX && nParts < m_funcGetNumParts())
	{ // �g�p�\�ȃC���f�b�N�X�̏ꍇ

		// ���_�ʒu��ݒ�
		m_info.vecOriginParts[nParts].pos = rPos;
	}
	else { assert(false); }	// �g�p�s��
}

//============================================================
//	���_�����̐ݒ菈��
//============================================================
void CMotion::SetOriginRotation(const D3DXVECTOR3& rRot, const int nParts)
{
	if (nParts > NONE_IDX && nParts < m_funcGetNumParts())
	{ // �g�p�\�ȃC���f�b�N�X�̏ꍇ

		// ���_������ݒ�
		m_info.vecOriginParts[nParts].rot = rRot;
	}
	else { assert(false); }	// �g�p�s��
}

//============================================================
//	��ނ̑����擾����
//============================================================
int CMotion::GetNumType(void)
{
	// ���[�V�����̎�ނ̑�����Ԃ�
	return m_info.GetNumMotion();
}

//============================================================
//	�L�[�̑����擾����
//============================================================
int CMotion::GetNumKey(const int nType)
{
	// �������[�V�����̃L�[�̑�����Ԃ�
	int nSubKey = (m_info.vecMotion[m_info.GetNumMotion()].bLoop) ? 0 : 1;	// ���[�v���Ȃ��ꍇ�Ō�̃L�[�͊܂܂Ȃ�
	return m_info.vecMotion[nType].GetNumKey() - nSubKey;
}

//============================================================
//	�L�����Z���擾����
//============================================================
bool CMotion::IsCancel(const int nType) const
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
bool CMotion::IsCombo(const int nType) const
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
//	���̍U������t���O�̎擾����
//============================================================
bool CMotion::IsLeftWeaponCollision(void)
{
	SMotion *pMotion = &m_info.vecMotion[m_info.nType];			// ���݂̃��[�V�������
	if (pMotion->collLeft.nMin == NONE_IDX) { return false; }	// �J�n�J�E���g���ݒ�
	if (pMotion->collLeft.nMax == NONE_IDX) { return false; }	// �I���J�E���g���ݒ�

	if (m_info.nWholeCounter >= pMotion->collLeft.nMin
	&&  m_info.nWholeCounter <= pMotion->collLeft.nMax)
	{ // �J�E���^�[���J�n�ƏI���͈͓̔��̏ꍇ

		return true;
	}

	return false;
}

//============================================================
//	�E�̍U������t���O�̎擾����
//============================================================
bool CMotion::IsRightWeaponCollision(void)
{
	SMotion *pMotion = &m_info.vecMotion[m_info.nType];			// ���݂̃��[�V�������
	if (pMotion->collRight.nMin == NONE_IDX) { return false; }	// �J�n�J�E���g���ݒ�
	if (pMotion->collRight.nMax == NONE_IDX) { return false; }	// �I���J�E���g���ݒ�

	if (m_info.nWholeCounter >= pMotion->collRight.nMin
	&&  m_info.nWholeCounter <= pMotion->collRight.nMax)
	{ // �J�E���^�[���J�n�ƏI���͈͓̔��̏ꍇ

		return true;
	}

	return false;
}

//============================================================
//	���_�ʒu�̎擾����
//============================================================
D3DXVECTOR3 CMotion::GetOriginPosition(const int nParts)
{
	if (nParts > NONE_IDX && nParts < m_funcGetNumParts())
	{ // �g�p�\�ȃC���f�b�N�X�̏ꍇ

		// ���_�ʒu��Ԃ�
		return m_info.vecOriginParts[nParts].pos;
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return VEC3_ZERO;
}

//============================================================
//	���_�����̎擾����
//============================================================
D3DXVECTOR3 CMotion::GetOriginRotation(const int nParts)
{
	if (nParts > NONE_IDX && nParts < m_funcGetNumParts())
	{ // �g�p�\�ȃC���f�b�N�X�̏ꍇ

		// ���_������Ԃ�
		return m_info.vecOriginParts[nParts].rot;
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return VEC3_ZERO;
}

//============================================================
//	��������
//============================================================
CMotion *CMotion::Create(CObjectChara *pChara)
{
	// ���[�V�����̐���
	CMotion *pMotion = new CMotion(std::bind(&CObjectChara::GetNumParts, pChara));
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
		pMotion->m_pChara = pChara;

		// �m�ۂ����A�h���X��Ԃ�
		return pMotion;
	}
}

//============================================================
//	�j������
//============================================================
void CMotion::Release(CMotion *&prMotion)
{
	// ���[�V�����̏I��
	assert(prMotion != nullptr);
	prMotion->Uninit();

	// �������J��
	SAFE_DELETE(prMotion);
}

//============================================================
//	�ړ��̍X�V����
//============================================================
void CMotion::UpdateMove(void)
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
void CMotion::UpdateMotion(void)
{
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
}

//============================================================
//	�u�����h�X�V����
//============================================================
void CMotion::UpdateBlend(void)
{
	// �p�[�c�̈ʒu�̍X�V
	for (int nCntParts = 0; nCntParts < m_funcGetNumParts(); nCntParts++)
	{ // �p�[�c�����J��Ԃ�

		// �ʒu�E�����̍��������߂�
		D3DXVECTOR3 diffPos = m_info.vecMotion[m_info.nType].vecKey[0].vecParts[nCntParts].pos - m_blend.vecParts[nCntParts].pos;
		D3DXVECTOR3 diffRot = m_info.vecMotion[m_info.nType].vecKey[0].vecParts[nCntParts].rot - m_blend.vecParts[nCntParts].rot;
		useful::NormalizeRot(diffRot);	// ���������̐��K��

		// ���݂̃p�[�c�̈ʒu�E�������X�V
		float fRate = (float)m_blend.nWholeCounter / (float)m_blend.nFrame;	// �L�[�t���[������
		m_ppModel[nCntParts]->SetVec3Position(m_blend.vecParts[nCntParts].pos + diffPos * fRate);
		m_ppModel[nCntParts]->SetVec3Rotation(m_blend.vecParts[nCntParts].rot + diffRot * fRate);
	}

	// ���[�V�����̑J�ڂ̍X�V
	if (m_blend.nWholeCounter < m_blend.nFrame)
	{ // �u�����h�̍Đ����I�����Ă��Ȃ��ꍇ

		// �J�E���^�[�����Z
		m_blend.nWholeCounter++;
	}
	else
	{ // �u�����h�̍Đ����I�������ꍇ

		// �u�����h�Đ��t���[������������
		m_blend.nFrame = 0;

		// �u�����h�S�̃J�E���^�[��������
		m_blend.nWholeCounter = 0;
	}
}
