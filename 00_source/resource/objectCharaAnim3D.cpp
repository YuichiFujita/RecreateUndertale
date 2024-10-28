//============================================================
//
//	�I�u�W�F�N�g�L�����N�^�[�A�j���[�V����3D���� [objectCharaAnim3D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectCharaAnim3D.h"
#include "manager.h"
#include "renderer.h"
#include "characterAnim3D.h"

//************************************************************
//	�q�N���X [CObjectCharaAnim3D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectCharaAnim3D::CObjectCharaAnim3D(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CAnim3D(label, dimension, nPriority)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectCharaAnim3D::~CObjectCharaAnim3D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectCharaAnim3D::Init()
{
	// �A�j���[�V����3D�̏�����
	if (FAILED(CAnim3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectCharaAnim3D::Uninit()
{
	// �A�j���[�V����3D�̏I��
	CAnim3D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CObjectCharaAnim3D::Update(const float fDeltaTime)
{
	// ���[�V�������Ȃ��ꍇ������
	if (m_info.vecMotion.empty()) { assert(false); return; }

	// �A�j���[�V����3D�̍X�V
	CAnim3D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CObjectCharaAnim3D::Draw(CShader* pShader)
{
	// �A�j���[�V����3D�̕`��
	CAnim3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CObjectCharaAnim3D* CObjectCharaAnim3D::Create(const VECTOR3& rPos, const VECTOR3& rRot)
{
	// �I�u�W�F�N�g�L�����N�^�[�A�j���[�V����3D�̐���
	CObjectCharaAnim3D* pObjectCharaAnim3D = new CObjectCharaAnim3D;
	if (pObjectCharaAnim3D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g�L�����N�^�[�A�j���[�V����3D�̏�����
		if (FAILED(pObjectCharaAnim3D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g�L�����N�^�[�A�j���[�V����3D�̔j��
			SAFE_DELETE(pObjectCharaAnim3D);
			return nullptr;
		}

		// �ʒu��ݒ�
		pObjectCharaAnim3D->SetVec3Position(rPos);

		// ������ݒ�
		pObjectCharaAnim3D->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pObjectCharaAnim3D;
	}
}

//============================================================
//	�L�����N�^�[��񊄓�
//============================================================
void CObjectCharaAnim3D::BindCharaData(const char* pCharaPath)
{
	// ���蓖�Ă郂�[�V�����p�X�����݂��Ȃ��ꍇ������
	if (pCharaPath == nullptr) { assert(false); return; }

	// ���[�V�������̑S�ݒ�
	SetAllInfo(GET_MANAGER->GetCharacterAnim3D()->Regist(pCharaPath));
}

//============================================================
//	���[�V�����̐ݒ菈��
//============================================================
void CObjectCharaAnim3D::SetMotion(const int nType)
{
	// �w�肳�ꂽ���[�V���������݂��Ȃ��ꍇ������
	if (nType <= NONE_IDX || nType >= m_info.GetNumMotion()) { assert(false); return; }

	// �����̃��[�V�����̎�ނ�ݒ�
	m_info.nType = nType;

	// �ϐ����|�C���^�����ȗ���
	SChara* pInfoChara = &m_info.vecMotion[nType].infoChara;	// �L�����N�^�[���

	// �w��e�N�X�`���̊���
	BindTexture(pInfoChara->sPathTexture.c_str());

	// �L�����N�^�[����ݒ�
	SetTexPtrn(pInfoChara->ptrnTexture);	// �e�N�X�`��������
	SetEnableLoop(pInfoChara->bLoop);		// ���[�vON/OFF
	SetVec3Size(pInfoChara->size);			// �傫��

	assert((int)pInfoChara->vecNextTime.size() == pInfoChara->nMaxPtrn);
	for (int i = 0; i < pInfoChara->nMaxPtrn; i++)
	{
		// �p�^�[���ύX���Ԃ�ݒ�
		SetNextTime(pInfoChara->vecNextTime[i]);
	}

	// �L�����N�^�[����������
	ResetCurPtrn();	// �J�n�p�^�[��
	ResetNumLoop();	// �J��Ԃ���
}

//============================================================
//	���[�V�������̒ǉ�����
//============================================================
void CObjectCharaAnim3D::AddInfo(const SMotion& rMotion)
{
	int nSetMotionIdx = m_info.GetNumMotion();	// ���[�V������ݒ肷��z��ԍ�

	// ��̗v�f���Ō���ɒǉ�
	m_info.vecMotion.emplace_back();

	// �����̃��[�V��������ݒ�
	m_info.vecMotion[nSetMotionIdx] = rMotion;
}

//============================================================
//	���[�V�������S�ݒ菈��
//============================================================
void CObjectCharaAnim3D::SetAllInfo(const SInfo& rInfo)
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
bool CObjectCharaAnim3D::IsCancel() const
{
	float fCancelTime = m_info.vecMotion[m_info.nType].fCancelTime;	// �L�����Z���\����
	if (fCancelTime >= 0.0f)
	{ // �L�����Z���\���Ԃ��ݒ肳��Ă���ꍇ

		// ���[�V�����̃L�����Z���󋵂�Ԃ�
		return (GetCurWholeTime() >= fCancelTime);
	}

	// �L�����Z���s��Ԃ�
	return false;
}

//============================================================
//	�R���{�擾����
//============================================================
bool CObjectCharaAnim3D::IsCombo() const
{
	float fComboTime = m_info.vecMotion[m_info.nType].fComboTime;	// �R���{�\����
	if (fComboTime >= 0.0f)
	{ // �R���{�\���Ԃ��ݒ肳��Ă���ꍇ

		// ���[�V�����̃R���{�󋵂�Ԃ�
		return (GetCurWholeTime() >= fComboTime);
	}

	// �R���{�s��Ԃ�
	return false;
}

//============================================================
//	���_�I�t�Z�b�g���f�ʒu�̌v�Z����
//============================================================
VECTOR3 CObjectCharaAnim3D::CalcOriginOffsetPosition(const VECTOR3& rPos, const VECTOR3& rRot) const
{
	// �I�t�Z�b�g���f�ʒu�̌v�Z���ʂ�Ԃ�
	const VECTOR3& rOffset = m_info.vecMotion[m_info.nType].infoChara.offset;	// �I�t�Z�b�g
	return CalcOffsetPosition(rPos, rRot, rOffset);
}

//============================================================
//	���茴�_�I�t�Z�b�g���f�ʒu�̌v�Z����
//============================================================
VECTOR3 CObjectCharaAnim3D::CalcCollOffsetPosition(const VECTOR3& rPos, const VECTOR3& rRot) const
{
	// �I�t�Z�b�g���f�ʒu�̌v�Z���ʂ�Ԃ�
	const VECTOR3& rOffset = m_info.vecMotion[m_info.nType].infoColl.offset;	// �I�t�Z�b�g
	return CalcOffsetPosition(rPos, rRot, rOffset);
}

//============================================================
//	���_�I�t�Z�b�g���f�ʒu�̎擾����
//============================================================
VECTOR3 CObjectCharaAnim3D::GetOriginOffsetPosition() const
{
	// ���_�I�t�Z�b�g���f�ʒu�̌v�Z���ʂ�Ԃ�
	const VECTOR3& rPos = GetVec3Position();	// �ʒu
	const VECTOR3& rRot = GetVec3Rotation();	// ����
	return CalcOriginOffsetPosition(rPos, rRot);
}

//============================================================
//	���茴�_�I�t�Z�b�g���f�ʒu�̎擾����
//============================================================
VECTOR3 CObjectCharaAnim3D::GetCollOffsetPosition() const
{
	// ���茴�_�I�t�Z�b�g���f�ʒu�̌v�Z���ʂ�Ԃ�
	const VECTOR3& rPos = GetVec3Position();	// �ʒu
	const VECTOR3& rRot = GetVec3Rotation();	// ����
	return CalcCollOffsetPosition(rPos, rRot);
}

//============================================================
//	�`��}�g���b�N�X�̌v�Z����
//============================================================
void CObjectCharaAnim3D::CalcDrawMatrix()
{
	VECTOR3 offset = m_info.vecMotion[m_info.nType].infoChara.offset;	// �I�t�Z�b�g
	MATRIX* pMtxWorld = GetPtrMtxWorld();	// ���[���h�}�g���b�N�X
	MATRIX mtxRot, mtxTrans, mtxOffset;		// �v�Z�p�}�g���b�N�X
	VECTOR3 pos = GetVec3Position();		// �ʒu
	VECTOR3 rot = GetVec3Rotation();		// ����

	// ���[���h�}�g���b�N�X�̏�����
	pMtxWorld->Identity();

	// �I�t�Z�b�g�𔽉f
	mtxOffset.Translation(offset);
	pMtxWorld->Multiply(*pMtxWorld, mtxOffset);

	// �����𔽉f
	mtxRot.Rotation(rot);
	pMtxWorld->Multiply(*pMtxWorld, mtxRot);

	// �ʒu�𔽉f
	mtxTrans.Translation(pos);
	pMtxWorld->Multiply(*pMtxWorld, mtxTrans);
}

//============================================================
//	�I�t�Z�b�g���f�ʒu�̌v�Z����
//============================================================
VECTOR3 CObjectCharaAnim3D::CalcOffsetPosition
(
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rRot,	// ����
	const VECTOR3& rOffset	// �I�t�Z�b�g
) const
{
	MATRIX mtxWorld, mtxRot, mtxTrans, mtxOffset;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld.Identity();

	// �I�t�Z�b�g�𔽉f
	mtxOffset.Translation(rOffset);
	mtxWorld.Multiply(mtxWorld, mtxOffset);

	// �����𔽉f
	mtxRot.Rotation(rRot);
	mtxWorld.Multiply(mtxWorld, mtxRot);

	// �ʒu�𔽉f
	mtxTrans.Translation(rPos);
	mtxWorld.Multiply(mtxWorld, mtxTrans);

	// �Z�o�����}�g���b�N�X�̈ʒu��Ԃ�
	return mtxWorld.GetPosition();
}
