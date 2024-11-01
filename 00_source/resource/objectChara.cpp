//============================================================
//
//	�I�u�W�F�N�g�L�����N�^�[���� [objectChara.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectChara.h"
#include "manager.h"
#include "renderer.h"
#include "multiModel.h"
#include "motion.h"

//************************************************************
//	�q�N���X [CObjectChara] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectChara::CObjectChara(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObject(label, dimension, nPriority),
	m_pMotion	(nullptr),		// ���[�V�����̏��
	m_mtxWorld	(MTX_IDENT),	// ���[���h�}�g���b�N�X
	m_pos		(VEC3_ZERO),	// �ʒu
	m_rot		(VEC3_ZERO)		// ����
{
	// �p�[�c���z����N���A
	m_vecParts.clear();
}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectChara::~CObjectChara()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectChara::Init()
{
	// �����o�ϐ���������
	m_pMotion	= nullptr;		// ���[�V�����̏��
	m_mtxWorld	= MTX_IDENT;	// ���[���h�}�g���b�N�X
	m_pos		= VEC3_ZERO;	// �ʒu
	m_rot		= VEC3_ZERO;	// ����

	// �p�[�c���z���������
	m_vecParts.clear();

	// ���[�V�����̐���
	m_pMotion = CMotion::Create(this);
	if (m_pMotion == nullptr)
	{ // ��g�p���̏ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectChara::Uninit()
{
	// ���[�V�����̔j��
	SAFE_REF_RELEASE(m_pMotion);

	for (auto& rVec : m_vecParts)
	{ // �p�[�c�����J��Ԃ�

		// �p�[�c�̏I��
		SAFE_UNINIT(rVec);
	}

	// �p�[�c���z����N���A
	m_vecParts.clear();

	// �I�u�W�F�N�g�L�����N�^�[��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CObjectChara::Update(const float fDeltaTime)
{
	if (m_pMotion != nullptr)
	{ // ���[�V���������݂���ꍇ

		// ���[�V�����̍X�V
		m_pMotion->Update(fDeltaTime);
	}
}

//============================================================
//	�`�揈��
//============================================================
void CObjectChara::Draw(CShader* pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �`��}�g���b�N�X�̌v�Z
	CalcDrawMatrix();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (auto& rVec : m_vecParts)
	{ // �p�[�c�����J��Ԃ�

		// �p�[�c�̕`��
		rVec->Draw(pShader);
	}
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CObjectChara::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);	// ���g
	for (auto& rVec : m_vecParts)
	{ // �p�[�c�����J��Ԃ�

		rVec->SetEnableUpdate(bUpdate);
	}
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CObjectChara::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);	// ���g
	for (auto& rVec : m_vecParts)
	{ // �p�[�c�����J��Ԃ�

		rVec->SetEnableDraw(bDraw);
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CObjectChara::SetVec3Position(const VECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectChara::SetVec3Rotation(const VECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_rot = rRot;

	// �����̐��K��
	useful::NormalizeRot(m_rot);
}

//============================================================
//	�g�嗦�̐ݒ菈��
//============================================================
void CObjectChara::SetVec3Scale(const VECTOR3& rScale)
{
	for (auto& rVec : m_vecParts)
	{ // �p�[�c�����J��Ԃ�

		if (rVec->GetParentObject() == nullptr)
		{ // �e�����Ȃ��ꍇ

			// �p�[�c�̊g�嗦��ݒ�
			rVec->SetVec3Scale(rScale);
		}
	}
}

//============================================================
//	��������
//============================================================
CObjectChara* CObjectChara::Create(const VECTOR3& rPos, const VECTOR3& rRot)
{
	// �I�u�W�F�N�g�L�����N�^�[�̐���
	CObjectChara* pObjectChara = new CObjectChara;
	if (pObjectChara == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g�L�����N�^�[�̏�����
		if (FAILED(pObjectChara->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g�L�����N�^�[�̔j��
			SAFE_DELETE(pObjectChara);
			return nullptr;
		}

		// �ʒu��ݒ�
		pObjectChara->SetVec3Position(rPos);

		// ������ݒ�
		pObjectChara->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pObjectChara;
	}
}

//============================================================
//	���[�V�����̐ݒ菈��
//============================================================
void CObjectChara::SetMotion(const int nType, const int nBlendFrame)
{
	// ���[�V�����̐ݒ�
	m_pMotion->Set(nType, nBlendFrame);
}

//============================================================
//	�p�[�c���̐ݒ菈��
//============================================================
void CObjectChara::SetPartsInfo
(
	const int nPartsIdx,	// �p�[�c�C���f�b�N�X
	const int nParentIdx,	// �e�C���f�b�N�X
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rRot,	// ����
	const char* pFileName	// �t�@�C����
)
{
	// �C���f�b�N�X���񐳋K�̏ꍇ������
	int nNumParts = GetNumParts();	// �p�[�c�̑���
	if (nPartsIdx  <= NONE_IDX     || nPartsIdx  >= nNumParts) { assert(false); return; }
	if (nParentIdx <= NONE_IDX - 1 || nParentIdx >= nNumParts) { assert(false); return; }

	// �t�@�C���w�肪�Ȃ��ꍇ������
	if (pFileName == nullptr) { assert(false); return; }

	// ���f���̌��_�ʒu�E������ݒ�
	m_pMotion->SetOriginPosition(rPos, nPartsIdx);
	m_pMotion->SetOriginRotation(rRot, nPartsIdx);

	// ���f���̐���
	m_vecParts[nPartsIdx] = CMultiModel::Create(rPos, rRot);

	// ���f��������
	m_vecParts[nPartsIdx]->BindModel(pFileName);

	// �e���f���̐ݒ�
	if (nParentIdx == NONE_IDX)
	{ // �e���Ȃ��ꍇ

		// nullptr��ݒ�
		m_vecParts[nPartsIdx]->SetParentObject(nullptr);
	}
	else
	{ // �e������ꍇ

		// �e�̃A�h���X��ݒ�
		m_vecParts[nPartsIdx]->SetParentObject(m_vecParts[nParentIdx]);
	}
}

//============================================================
//	�L�����N�^�[��񊄓�
//============================================================
void CObjectChara::BindCharaData(const char* pCharaPath)
{
	// ���蓖�Ă郂�[�V�����p�X�����݂��Ȃ��ꍇ������
	if (pCharaPath == nullptr) { assert(false); return; }

	CCharacter::SCharaData data = GET_MANAGER->GetCharacter()->Regist(pCharaPath);	// �L�����N�^�[���

	// ���[�V�������̓��I�z��̃N���A
	m_pMotion->ClearVector();

	// ���g�ƃ��[�V�����̃p�[�c����ݒ�
	SetNumParts(data.infoParts.GetNumParts());

	// ���g�̃p�[�c����S�ݒ�
	SetPartsInfoAll(data.infoParts);

	// ���[�V�����Ƀp�[�c��������
	m_pMotion->BindPartsData(&m_vecParts[0]);

	// ���[�V�����Ƀ��[�V�������̑S�ݒ�
	m_pMotion->SetAllInfo(data.infoMotion);
}

//============================================================
//	�p�[�c���̐ݒ菈��
//============================================================
void CObjectChara::SetNumParts(const int nNumParts)
{
	//--------------------------------------------------------
	//	���݂̃p�[�c��j��
	//--------------------------------------------------------
	for (auto& rVec : m_vecParts)
	{ // �p�[�c�����J��Ԃ�

		// �p�[�c�̏I��
		SAFE_UNINIT(rVec);
	}

	// �p�[�c���z����N���A
	m_vecParts.clear();

	//--------------------------------------------------------
	//	�p�[�c����ݒ�
	//--------------------------------------------------------
	// ���[�V�����̃p�[�c���̐ݒ�
	m_pMotion->SetNumParts(nNumParts);

	// ���g�̃p�[�c���̐ݒ�
	m_vecParts.resize(nNumParts);
}

//============================================================
//	�p�[�c���̑S�ݒ菈��
//============================================================
void CObjectChara::SetPartsInfoAll(CCharacter::SPartsInfo& rInfo)
{
	for (int nCntParts = 0; nCntParts < rInfo.GetNumParts(); nCntParts++)
	{ // �p�[�c�����J��Ԃ�

		// �p�[�c���̐ݒ�
		CCharacter::SParts* pParts = &rInfo.vecParts[nCntParts];	// �p�[�c���
		SetPartsInfo
		( // ����
			nCntParts,				// �p�[�c�C���f�b�N�X
			pParts->nParentIdx,		// �e�C���f�b�N�X
			pParts->pos,			// �ʒu
			pParts->rot,			// ����
			pParts->sPath.c_str()	// �t�@�C����
		);
	}
}

//============================================================
//	�p�[�c�ʒu�̐ݒ菈��
//============================================================
void CObjectChara::SetPartsPosition(const int nPartsIdx, const VECTOR3& rPos)
{
	if (nPartsIdx < GetNumParts())
	{ // �g�p�\�ȃC���f�b�N�X�̏ꍇ

		// �����̃C���f�b�N�X�̈ʒu��ݒ�
		m_vecParts[nPartsIdx]->SetVec3Position(rPos);
	}
	else { assert(false); }	// �g�p�s��
}

//============================================================
//	�p�[�c�����̐ݒ菈��
//============================================================
void CObjectChara::SetPartsRotation(const int nPartsIdx, const VECTOR3& rRot)
{
	if (nPartsIdx < GetNumParts())
	{ // �g�p�\�ȃC���f�b�N�X�̏ꍇ

		// �����̃C���f�b�N�X�̌�����ݒ�
		m_vecParts[nPartsIdx]->SetVec3Rotation(rRot);
	}
	else { assert(false); }	// �g�p�s��
}

//============================================================
//	�p�[�c�ʒu�擾����
//============================================================
VECTOR3 CObjectChara::GetPartsPosition(const int nPartsIdx) const
{
	if (nPartsIdx < GetNumParts())
	{ // �g�p�\�ȃC���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃p�[�c�̈ʒu��Ԃ�
		return m_vecParts[nPartsIdx]->GetVec3Position();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return VEC3_ZERO;
}

//============================================================
//	�p�[�c�����擾����
//============================================================
VECTOR3 CObjectChara::GetPartsRotation(const int nPartsIdx) const
{
	if (nPartsIdx < GetNumParts())
	{ // �g�p�\�ȃC���f�b�N�X�̏ꍇ

		// �����C���f�b�N�X�̃p�[�c�̌�����Ԃ�
		return m_vecParts[nPartsIdx]->GetVec3Rotation();
	}

	// �C���f�b�N�X�G���[
	assert(false);
	return VEC3_ZERO;
}

//============================================================
//	�p�[�c�擾����
//============================================================
CMultiModel* CObjectChara::GetParts(const int nPartsIdx) const
{
	if (nPartsIdx < GetNumParts())
	{ // �g�p�\�ȃC���f�b�N�X�̏ꍇ

		// �p�[�c�̏���Ԃ�
		return m_vecParts[nPartsIdx];
	}
	
	// �C���f�b�N�X�G���[
	assert(false);
	return nullptr;
}

//============================================================
//	�}�e���A���̐ݒ菈��
//============================================================
void CObjectChara::SetMaterial(const D3DXMATERIAL& rMat, const int nPartsIdx, const int nMatIdx)
{
	if (nPartsIdx < GetNumParts())
	{ // �g�p�\�ȃC���f�b�N�X�̏ꍇ

		// �����̃}�e���A����ݒ�
		m_vecParts[nPartsIdx]->SetMaterial(rMat, nMatIdx);
	}
	else { assert(false); }	// �g�p�s��
}

//============================================================
//	�}�e���A���S�ݒ菈��
//============================================================
void CObjectChara::SetAllMaterial(const D3DXMATERIAL& rMat)
{
	for (auto& rVec : m_vecParts)
	{ // �p�[�c�����J��Ԃ�

		// �����̃}�e���A����S�}�e���A���ɐݒ�
		rVec->SetAllMaterial(rMat);
	}
}

//============================================================
//	�}�e���A���Đݒ菈��
//============================================================
void CObjectChara::ResetMaterial()
{
	for (auto& rVec : m_vecParts)
	{ // �p�[�c�����J��Ԃ�

		// �S�}�e���A���ɏ����}�e���A�����Đݒ�
		rVec->ResetMaterial();
	}
}

//============================================================
//	�����x�̐ݒ菈��
//============================================================
void CObjectChara::SetAlpha(const float fAlpha)
{
	for (auto& rVec : m_vecParts)
	{ // �p�[�c�����J��Ԃ�

		// �����̓����x��ݒ�
		rVec->SetAlpha(fAlpha);
	}
}

//============================================================
//	�����x�擾����
//============================================================
float CObjectChara::GetAlpha() const
{
	// �ł��s�����ȓ����x��T��
	float fAlpha = 0.0f;	// �ł��s�����ȃ}�e���A���̓����x
	for (auto& rVec : m_vecParts)
	{ // �p�[�c�����J��Ԃ�

		float fCurAlpha = rVec->GetAlpha();	// ���݂̃��f���̓����x
		if (fCurAlpha > fAlpha)
		{ // �}�e���A���̓����x�����s�����������ꍇ

			// ���݂̃}�e���A���̓����x��ۑ�
			fAlpha = fCurAlpha;
		}
	}

	// �S�p�[�c���ōł��s�����������}�e���A���̓����x��Ԃ�
	return fAlpha;
}

//============================================================
//	�ő哧���x�擾����
//============================================================
float CObjectChara::GetMaxAlpha() const
{
	// �ł��s�����ȓ����x��T��
	float fAlpha = 0.0f;	// �ł��s�����ȃ}�e���A���̓����x
	for (int nCntParts = 0; nCntParts < GetNumParts(); nCntParts++)
	{ // �p�[�c�̍ő吔���J��Ԃ�

		if (m_vecParts[nCntParts]->GetMaxAlpha() > fAlpha)
		{ // �}�e���A���̓����x�����s�����������ꍇ

			// ���݂̃}�e���A���̓����x��ۑ�
			fAlpha = m_vecParts[nCntParts]->GetMaxAlpha();
		}
	}

	// �S�p�[�c���ōł��s�����������}�e���A���̓����x��Ԃ�
	return fAlpha;
}

//============================================================
//	�`��}�g���b�N�X�̌v�Z����
//============================================================
void CObjectChara::CalcDrawMatrix()
{
	MATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	m_mtxWorld.Identity();

	// �����𔽉f
	mtxRot.Rotation(m_rot);
	m_mtxWorld.Multiply(m_mtxWorld, mtxRot);

	// �ʒu�𔽉f
	mtxTrans.Translation(m_pos);
	m_mtxWorld.Multiply(m_mtxWorld, mtxTrans);
}
