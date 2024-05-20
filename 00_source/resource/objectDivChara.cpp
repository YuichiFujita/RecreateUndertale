//============================================================
//
//	�I�u�W�F�N�g�����L�����N�^�[���� [objectDivChara.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectDivChara.h"
#include "manager.h"
#include "renderer.h"
#include "objectChara.h"
#include "multiModel.h"

//************************************************************
//	�q�N���X [CObjectDivChara] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectDivChara::CObjectDivChara(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObject(label, dimension, nPriority), m_nUpperParentID(0)
{
	// �����o�ϐ����N���A
	memset(&m_apBody[0], 0, sizeof(m_apBody));	// �g�̂̏��
}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectDivChara::~CObjectDivChara()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectDivChara::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apBody[0], 0, sizeof(m_apBody));	// �g�̂̏��
	m_nUpperParentID = 0;	// �㔼�g�e�C���f�b�N�X

	for (int i = 0; i < BODY_MAX; i++)
	{ // ���������g�̂̐����J��Ԃ�

		// �I�u�W�F�N�g�L�����N�^�[�̐���
		m_apBody[i] = CObjectChara::Create(VEC3_ZERO);
		if (m_apBody[i] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �����`���OFF�ɂ���
		m_apBody[i]->SetEnableDraw(false);
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectDivChara::Uninit(void)
{
	for (int i = 0; i < BODY_MAX; i++)
	{ // ���������g�̂̐����J��Ԃ�

		// �I�u�W�F�N�g�L�����N�^�[�̏I��
		m_apBody[i]->Uninit();
	}

	// �I�u�W�F�N�g�����L�����N�^�[��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CObjectDivChara::Update(const float fDeltaTime)
{
	for (int i = 0; i < BODY_MAX; i++)
	{ // ���������g�̂̐����J��Ԃ�

		// �I�u�W�F�N�g�L�����N�^�[�̍X�V
		m_apBody[i]->Update(fDeltaTime);
	}
}

//============================================================
//	�`�揈��
//============================================================
void CObjectDivChara::Draw(CShader *pShader)
{
	// �ϐ���錾
	D3DXVECTOR3 pos = GetVec3Position();	// �����g�̈ʒu
	D3DXVECTOR3 rot = GetVec3Rotation();	// �����g�̌���
	D3DXMATRIX  mtxRot, mtxTrans, mtxWorld;	// �v�Z�p�}�g���b�N�X

	// �ϐ��z���錾
	D3DXMATRIX *apMtxWorld[] = { &mtxWorld, GetMultiModel(BODY_LOWER, m_nUpperParentID)->GetPtrMtxWorld() };
	static_assert(NUM_ARRAY(apMtxWorld) == BODY_MAX, "ERROR : Body Count Mismatch");

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// �����g�̃��[���h�}�g���b�N�X�̔��f
	m_apBody[BODY_LOWER]->SetMtxWorld(mtxWorld);

	for (int nCntChara = 0; nCntChara < BODY_MAX; nCntChara++)
	{ // ���������g�̂̐����J��Ԃ�

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, apMtxWorld[nCntChara]);

		for (int nCntParts = 0; nCntParts < m_apBody[nCntChara]->GetNumParts(); nCntParts++)
		{ // �p�[�c�̑������J��Ԃ�

			// �p�[�c�̕`��
			GetMultiModel((EBody)nCntChara, nCntParts)->Draw(pShader);
		}
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CObjectDivChara::SetVec3Position(const D3DXVECTOR3 &rPos)
{
	// �����̈ʒu��ݒ�
	m_apBody[BODY_LOWER]->SetVec3Position(rPos);
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectDivChara::SetVec3Rotation(const D3DXVECTOR3 &rRot)
{
	// �����̌�����ݒ�
	m_apBody[BODY_LOWER]->SetVec3Rotation(rRot);
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CObjectDivChara::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);	// ���g
	for (int i = 0; i < BODY_MAX; i++)
	{ // ���������g�̂̐����J��Ԃ�

		m_apBody[i]->SetEnableUpdate(bUpdate);	// ��E�����g
	}
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CObjectDivChara::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);	// ���g
	for (int i = 0; i < BODY_MAX; i++)
	{ // ���������g�̂̐����J��Ԃ�

		m_apBody[i]->SetEnableDraw(bDraw);	// ��E�����g
	}
}

//============================================================
//	��������
//============================================================
CObjectDivChara *CObjectDivChara::Create
(
	const D3DXVECTOR3 &rPos,	// �ʒu
	const D3DXVECTOR3 &rRot,	// ����
	const int nUpperParentID	// �㔼�g�e�C���f�b�N�X
)
{
	// �I�u�W�F�N�g�����L�����N�^�[�̐���
	CObjectDivChara *pObjectDivChara = new CObjectDivChara;
	if (pObjectDivChara == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g�����L�����N�^�[�̏�����
		if (FAILED(pObjectDivChara->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g�����L�����N�^�[�̔j��
			SAFE_DELETE(pObjectDivChara);
			return nullptr;
		}

		// �㔼�g�̐e�C���f�b�N�X��ݒ�
		pObjectDivChara->SetUpperParentID(nUpperParentID);

		// �ʒu��ݒ�
		pObjectDivChara->SetVec3Position(rPos);

		// ������ݒ�
		pObjectDivChara->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pObjectDivChara;
	}
}

//============================================================
//	���[�V�����̐ݒ菈��
//============================================================
void CObjectDivChara::SetMotion
(
	const EBody bodyID,		// �g�̃C���f�b�N�X
	const int nType,		// ���[�V�������
	const int nBlendFrame	// �u�����h�t���[��
)
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V������ݒ�
		m_apBody[bodyID]->SetMotion(nType, nBlendFrame);
	}
	else { assert(false); }	// �C���f�b�N�X�G���[
}

//============================================================
//	�p�[�c���̐ݒ菈��
//============================================================
void CObjectDivChara::SetPartsInfo
(
	const EBody bodyID,			// �g�̃C���f�b�N�X
	const int nID,				// �p�[�c�C���f�b�N�X
	const int nParentID,		// �e�C���f�b�N�X
	const D3DXVECTOR3 &rPos,	// �ʒu
	const D3DXVECTOR3 &rRot,	// ����
	const char *pFileName		// �t�@�C����
)
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃p�[�c����ݒ�
		m_apBody[bodyID]->SetPartsInfo
		( // ����
			nID,		// �p�[�c�C���f�b�N�X
			nParentID,	// �e�C���f�b�N�X
			rPos,		// �ʒu
			rRot,		// ����
			pFileName	// �t�@�C����
		);
	}
	else { assert(false); }	// �C���f�b�N�X�G���[
}

//============================================================
//	�}�e���A���̐ݒ菈��
//============================================================
void CObjectDivChara::SetMaterial
(
	const D3DXMATERIAL &rMat,	// �ݒ�}�e���A��
	const EBody bodyID,			// �g�̃C���f�b�N�X
	const int nPartsID,			// �p�[�c�C���f�b�N�X
	const int nMatID			// �}�e���A���C���f�b�N�X
)
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃}�e���A����ݒ�
		m_apBody[bodyID]->SetMaterial(rMat, nPartsID, nMatID);
	}
	else { assert(false); }	// �C���f�b�N�X�G���[
}

//============================================================
//	�L�����N�^�[��񊄓�
//============================================================
void CObjectDivChara::BindCharaData
(
	const char *pCharaPassLower,	// �����g�L�������p�X
	const char *pCharaPassUpper		// �㔼�g�L�������p�X
)
{
	// �����g�̃L�����N�^�[���̊���
	if (pCharaPassLower == nullptr) { assert(false); return; }	// �p�X�w��Ȃ�
	m_apBody[BODY_LOWER]->BindCharaData(pCharaPassLower);

	// �㔼�g�̃L�����N�^�[���̊���
	if (pCharaPassUpper == nullptr) { assert(false); return; }	// �p�X�w��Ȃ�
	m_apBody[BODY_UPPER]->BindCharaData(pCharaPassUpper);
}

//============================================================
//	���[�V�����̍X�V�󋵂̐ݒ菈��
//============================================================
void CObjectDivChara::SetEnableMotionUpdate(const bool bUpdate)
{
	for (int i = 0; i < BODY_MAX; i++)
	{ // ���������g�̂̐����J��Ԃ�

		// ���[�V�����̍X�V�󋵂�ݒ�
		m_apBody[i]->SetEnableMotionUpdate(bUpdate);
	}
}

//============================================================
//	���[�V�������̒ǉ�����
//============================================================
void CObjectDivChara::AddMotionInfo(const EBody bodyID, const CMotion::SMotion& rInfo)
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V��������ǉ�
		m_apBody[bodyID]->AddMotionInfo(rInfo);
	}
	else { assert(false); }	// �C���f�b�N�X�G���[
}

//============================================================
//	���[�V������ގ擾����
//============================================================
int CObjectDivChara::GetMotionType(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V������ނ�Ԃ�
		return m_apBody[bodyID]->GetMotionType();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return NONE_IDX;
}

//============================================================
//	���[�V������ނ̑����擾����
//============================================================
int CObjectDivChara::GetMotionNumType(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V������ނ̑�����Ԃ�
		return m_apBody[bodyID]->GetMotionNumType();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return NONE_IDX;
}

//============================================================
//	���[�V�����L�[�ԍ��擾����
//============================================================
int CObjectDivChara::GetMotionKey(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V�����L�[�ԍ���Ԃ�
		return m_apBody[bodyID]->GetMotionKey();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return NONE_IDX;
}

//============================================================
//	���[�V�����L�[�̑����擾����
//============================================================
int CObjectDivChara::GetMotionNumKey(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V�����L�[�̑�����Ԃ�
		return m_apBody[bodyID]->GetMotionNumKey();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return NONE_IDX;
}

//============================================================
//	���[�V�����L�[�J�E���^�[�擾����
//============================================================
int CObjectDivChara::GetMotionKeyCounter(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V�����L�[�J�E���^�[��Ԃ�
		return m_apBody[bodyID]->GetMotionKeyCounter();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return NONE_IDX;
}

//============================================================
//	���[�V�����S�̃J�E���^�[�擾����
//============================================================
int CObjectDivChara::GetMotionWholeCounter(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V�����S�̃J�E���^�[��Ԃ�
		return m_apBody[bodyID]->GetMotionWholeCounter();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return NONE_IDX;
}

//============================================================
//	���[�V�����S�̃t���[�����擾����
//============================================================
int CObjectDivChara::GetMotionWholeFrame(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V�����S�̃t���[������Ԃ�
		return m_apBody[bodyID]->GetMotionWholeFrame();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return NONE_IDX;
}

//============================================================
//	���[�V�����L�����Z���t���[���擾����
//============================================================
int CObjectDivChara::GetMotionCancelFrame(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V�����L�����Z���t���[����Ԃ�
		return m_apBody[bodyID]->GetMotionCancelFrame();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return NONE_IDX;
}

//============================================================
//	���[�V�����R���{�t���[���擾����
//============================================================
int CObjectDivChara::GetMotionComboFrame(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V�����R���{�t���[����Ԃ�
		return m_apBody[bodyID]->GetMotionComboFrame();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return NONE_IDX;
}

//============================================================
//	���[�V�����I���󋵂̎擾����
//============================================================
bool CObjectDivChara::IsMotionFinish(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V�����I���󋵂�Ԃ�
		return m_apBody[bodyID]->IsMotionFinish();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return false;
}

//============================================================
//	���[�V�������[�v�󋵂̎擾����
//============================================================
bool CObjectDivChara::IsMotionLoop(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V�������[�v�󋵂�Ԃ�
		return m_apBody[bodyID]->IsMotionLoop();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return false;
}

//============================================================
//	���[�V�����L�����Z���擾����
//============================================================
bool CObjectDivChara::IsMotionCancel(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V�����L�����Z���󋵂�Ԃ�
		return m_apBody[bodyID]->IsMotionCancel();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return false;
}

//============================================================
//	���[�V�����R���{�擾����
//============================================================
bool CObjectDivChara::IsMotionCombo(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V�����R���{�󋵂�Ԃ�
		return m_apBody[bodyID]->IsMotionCombo();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return false;
}

//============================================================
//	���[�V��������\���̎擾����
//============================================================
bool CObjectDivChara::IsWeaponDisp(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃��[�V��������\���󋵂�Ԃ�
		return m_apBody[bodyID]->IsWeaponDisp();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return false;
}

//============================================================
//	���̍U������t���O�̎擾����
//============================================================
bool CObjectDivChara::IsLeftWeaponCollision(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̍��̍U������󋵂�Ԃ�
		return m_apBody[bodyID]->IsLeftWeaponCollision();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return false;
}

//============================================================
//	�E�̍U������t���O�̎擾����
//============================================================
bool CObjectDivChara::IsRightWeaponCollision(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̉E�̍U������󋵂�Ԃ�
		return m_apBody[bodyID]->IsRightWeaponCollision();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return false;
}

//============================================================
//	�p�[�c�ʒu�̐ݒ菈��
//============================================================
void CObjectDivChara::SetPartsPosition(const EBody bodyID, const int nPartsID, const D3DXVECTOR3 &rPos)
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃p�[�c�ʒu��ݒ�
		m_apBody[bodyID]->SetPartsPosition(nPartsID, rPos);
	}
	else { assert(false); }	// �C���f�b�N�X�G���[
}

//============================================================
//	�p�[�c�����̐ݒ菈��
//============================================================
void CObjectDivChara::SetPartsRotation(const EBody bodyID, const int nPartsID, const D3DXVECTOR3 &rRot)
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃p�[�c������ݒ�
		m_apBody[bodyID]->SetPartsRotation(nPartsID, rRot);
	}
	else { assert(false); }	// �C���f�b�N�X�G���[
}

//============================================================
//	�p�[�c�ʒu�擾����
//============================================================
D3DXVECTOR3 CObjectDivChara::GetPartsPosition(const EBody bodyID, const int nPartsID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃p�[�c�ʒu��Ԃ�
		return m_apBody[bodyID]->GetPartsPosition(nPartsID);
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return VEC3_ZERO;
}

//============================================================
//	�p�[�c�����擾����
//============================================================
D3DXVECTOR3 CObjectDivChara::GetPartsRotation(const EBody bodyID, const int nPartsID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃p�[�c������Ԃ�
		return m_apBody[bodyID]->GetPartsRotation(nPartsID);
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return VEC3_ZERO;
}

//============================================================
//	�}�e���A���S�ݒ菈��
//============================================================
void CObjectDivChara::SetAllMaterial(const D3DXMATERIAL &rMat)
{
	for (int i = 0; i < BODY_MAX; i++)
	{ // ���������g�̂̐����J��Ԃ�

		// �����̃}�e���A����S�}�e���A���ɐݒ�
		m_apBody[i]->SetAllMaterial(rMat);
	}
}

//============================================================
//	�}�e���A���Đݒ菈��
//============================================================
void CObjectDivChara::ResetMaterial(void)
{
	for (int i = 0; i < BODY_MAX; i++)
	{ // ���������g�̂̐����J��Ԃ�

		// �S�}�e���A���ɏ����}�e���A�����Đݒ�
		m_apBody[i]->ResetMaterial();
	}
}

//============================================================
//	�����x�̐ݒ菈��
//============================================================
void CObjectDivChara::SetAlpha(const float fAlpha)
{
	for (int i = 0; i < BODY_MAX; i++)
	{ // ���������g�̂̐����J��Ԃ�

		// �����x�̐ݒ�
		m_apBody[i]->SetAlpha(fAlpha);
	}
}

//============================================================
//	�����x�̎擾����
//============================================================
float CObjectDivChara::GetAlpha(void) const
{
	// �ϐ���錾
	float fAlpha = 0.0f;	// �ł��s�����ȃ}�e���A���̓����x

	// �ł��s�����ȓ����x��T��
	for (int i = 0; i < BODY_MAX; i++)
	{ // ���������g�̂̐����J��Ԃ�

		float fCurAlpha = m_apBody[i]->GetAlpha();	// ���݂̃��f���̓����x
		if (fCurAlpha > fAlpha)
		{ // �}�e���A���̓����x�����s�����������ꍇ

			// ���݂̃L�����N�^�[�̓����x��ۑ�
			fAlpha = fCurAlpha;
		}
	}

	// �S�L�����N�^�[���ōł��s�����������}�e���A���̓����x��Ԃ�
	return fAlpha;
}

//============================================================
//	�ő哧���x�̎擾����
//============================================================
float CObjectDivChara::GetMaxAlpha(void) const
{
	// �ϐ���錾
	float fAlpha = 0.0f;	// �ł��s�����ȃ}�e���A���̓����x

	// �ł��s�����ȓ����x��T��
	for (int i = 0; i < BODY_MAX; i++)
	{ // ���������g�̂̐����J��Ԃ�

		float fCurAlpha = m_apBody[i]->GetMaxAlpha();	// ���݂̃��f���̓����x
		if (fCurAlpha > fAlpha)
		{ // �}�e���A���̓����x�����s�����������ꍇ

			// ���݂̃L�����N�^�[�̓����x��ۑ�
			fAlpha = fCurAlpha;
		}
	}

	// �S�L�����N�^�[���ōł��s�����������}�e���A���̓����x��Ԃ�
	return fAlpha;
}

//============================================================
//	�㔼�g�̐e�C���f�b�N�X�̐ݒ菈��
//============================================================
void CObjectDivChara::SetUpperParentID(const int nUpperParentID)
{
	if (nUpperParentID > NONE_IDX && nUpperParentID < m_apBody[BODY_LOWER]->GetNumParts())
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �㔼�g�̐e�C���f�b�N�X��ݒ�
		m_nUpperParentID = nUpperParentID;
	}
	else { assert(false); }	// �C���f�b�N�X�G���[
}

//============================================================
//	�I�u�W�F�N�g�L�����N�^�[�擾����
//============================================================
CObjectChara *CObjectDivChara::GetObjectChara(const EBody bodyID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̔��g��Ԃ�
		return m_apBody[bodyID];
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return nullptr;
}

//============================================================
//	�}���`���f���擾����
//============================================================
CMultiModel *CObjectDivChara::GetMultiModel(const EBody bodyID, const int nModelID) const
{
	if (bodyID > NONE_IDX && bodyID < BODY_MAX)
	{
		if (nModelID > NONE_IDX && nModelID < m_apBody[bodyID]->GetNumParts())
		{ // ���K�C���f�b�N�X�̏ꍇ

			// �����C���f�b�N�X�̃p�[�c��Ԃ�
			return m_apBody[bodyID]->GetParts(nModelID);
		}
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return nullptr;
}
