//============================================================
//
//	�I�u�W�F�N�g�L�����N�^�[2D���� [objectChara2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectChara2D.h"
#include "manager.h"
#include "renderer.h"
#include "multiModel.h"
#include "motion.h"

//************************************************************
//	�q�N���X [CObjectChara2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectChara2D::CObjectChara2D(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CAnim3D(label, dimension, nPriority),
	m_pMotion	(nullptr)	// ���[�V�������
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectChara2D::~CObjectChara2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectChara2D::Init(void)
{
	// �����o�ϐ���������
	m_pMotion = nullptr;	// ���[�V�������

	// ���[�V�����̐���
	//m_pMotion = CMotion::Create(this);	// TODO
	if (m_pMotion == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectChara2D::Uninit(void)
{
	// ���[�V�����̔j��
	SAFE_REF_RELEASE(m_pMotion);
}

//============================================================
//	�X�V����
//============================================================
void CObjectChara2D::Update(const float fDeltaTime)
{
	// ���[�V�����̍X�V
	assert(m_pMotion != nullptr);
	m_pMotion->Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CObjectChara2D::Draw(CShader *pShader)
{

}

//============================================================
//	��������
//============================================================
CObjectChara2D *CObjectChara2D::Create(const D3DXVECTOR3 &rPos, const D3DXVECTOR3 &rRot)
{
	// �I�u�W�F�N�g�L�����N�^�[2D�̐���
	CObjectChara2D *pObjectChara2D = new CObjectChara2D;
	if (pObjectChara2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g�L�����N�^�[2D�̏�����
		if (FAILED(pObjectChara2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g�L�����N�^�[2D�̔j��
			SAFE_DELETE(pObjectChara2D);
			return nullptr;
		}

		// �ʒu��ݒ�
		pObjectChara2D->SetVec3Position(rPos);

		// ������ݒ�
		pObjectChara2D->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pObjectChara2D;
	}
}

//============================================================
//	�p�[�c���̐ݒ菈��
//============================================================
void CObjectChara2D::SetPartsInfo
(
	const int nID,				// �p�[�c�C���f�b�N�X
	const int nParentID,		// �e�C���f�b�N�X
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot,	// ����
	const char *pFileName		// �t�@�C����
)
{
#if 0
	// �C���f�b�N�X���񐳋K�̏ꍇ������
	int nNumParts = GetNumParts();	// �p�[�c�̑���
	if (nID <= NONE_IDX || nID >= nNumParts) { assert(false); return; }
	if (nParentID <= NONE_IDX - 1 || nParentID >= nNumParts) { assert(false); return; }

	// �t�@�C���w�肪�Ȃ��ꍇ������
	if (pFileName == nullptr) { assert(false); return; }

	// ���f���̌��_�ʒu�E������ݒ�
	m_pMotion->SetOriginPosition(rPos, nID);
	m_pMotion->SetOriginRotation(rRot, nID);

	// ���f���̐���
	m_vecParts[nID] = CMultiModel::Create(rPos, rRot);

	// ���f��������
	m_vecParts[nID]->BindModel(pFileName);

	// �e���f���̐ݒ�
	if (nParentID == NONE_IDX)
	{ // �e���Ȃ��ꍇ

		// nullptr��ݒ�
		m_vecParts[nID]->SetParentModel(nullptr);
	}
	else
	{ // �e������ꍇ

		// �e�̃A�h���X��ݒ�
		m_vecParts[nID]->SetParentModel(m_vecParts[nParentID]);
	}
#endif
}

//============================================================
//	�L�����N�^�[��񊄓�
//============================================================
void CObjectChara2D::BindCharaData(const char *pCharaPass)
{
	// ���蓖�Ă郂�[�V�����p�X�����݂��Ȃ��ꍇ������
	if (pCharaPass == nullptr) { assert(false); return; }

#if 0
	CCharacter::SCharaData data = GET_MANAGER->GetCharacter()->Regist(pCharaPass);	// �L�����N�^�[���

	// ���[�V�������̓��I�z��̃N���A
	m_pMotion->ClearVector();

	// ���g�ƃ��[�V�����̃p�[�c����ݒ�
	SetNumParts(data.infoParts.GetNumParts());

	// ���g�̃p�[�c����ݒ�
	SetPartsInfo(data.infoParts);

	// ���[�V�����Ƀp�[�c��������
	m_pMotion->BindPartsData(&m_vecParts[0]);

	// ���[�V�����Ƀ��[�V�������̑S�ݒ�
	m_pMotion->SetAllInfo(data.infoMotion);
#endif
}

//============================================================
//	�p�[�c���̐ݒ菈��
//============================================================
void CObjectChara2D::SetPartsInfo(CCharacter::SPartsInfo& rInfo)
{
	for (int nCntParts = 0; nCntParts < rInfo.GetNumParts(); nCntParts++)
	{ // �p�[�c�����J��Ԃ�

		// �p�[�c���̐ݒ�
		CCharacter::SParts *pParts = &rInfo.vecParts[nCntParts];	// �p�[�c���
		CObjectChara2D::SetPartsInfo
		( // ����
			nCntParts,				// �p�[�c�C���f�b�N�X
			pParts->nParentID,		// �e�C���f�b�N�X
			pParts->pos,			// �ʒu
			pParts->rot,			// ����
			pParts->strPass.c_str()	// �t�@�C����
		);
	}
}

//============================================================
//	���[�V�����̐ݒ菈��
//============================================================
void CObjectChara2D::SetMotion(const int nType)
{
	// ���[�V�����̐ݒ�
	m_pMotion->Set(nType);
}
