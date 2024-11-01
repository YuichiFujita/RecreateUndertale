//============================================================
//
//	�}���`���f������ [multiModel.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "multiModel.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "renderState.h"

//************************************************************
//	�q�N���X [CMultiModel] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CMultiModel::CMultiModel(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObjectModel(label, dimension, nPriority), m_pParent(nullptr)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CMultiModel::~CMultiModel()
{

}

//============================================================
//	����������
//============================================================
HRESULT CMultiModel::Init()
{
	// �����o�ϐ���������
	m_pParent = nullptr;	// �e���f���ւ̃|�C���^

	// �I�u�W�F�N�g���f���̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �����`���OFF�ɂ���
	SetEnableDraw(false);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CMultiModel::Uninit()
{
	// �I�u�W�F�N�g���f���̏I��
	CObjectModel::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CMultiModel::Update(const float fDeltaTime)
{
	// �I�u�W�F�N�g���f���̍X�V
	CObjectModel::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CMultiModel::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g���f���̕`��
	CObjectModel::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CMultiModel* CMultiModel::Create(const VECTOR3& rPos, const VECTOR3& rRot, const VECTOR3& rScale)
{
	// �}���`���f���̐���
	CMultiModel* pMultiModel = new CMultiModel;
	if (pMultiModel == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �}���`���f���̏�����
		if (FAILED(pMultiModel->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �}���`���f���̔j��
			SAFE_DELETE(pMultiModel);
			return nullptr;
		}

		// �ʒu��ݒ�
		pMultiModel->SetVec3Position(rPos);

		// ������ݒ�
		pMultiModel->SetVec3Rotation(rRot);

		// �g�嗦��ݒ�
		pMultiModel->SetVec3Scale(rScale);

		// �m�ۂ����A�h���X��Ԃ�
		return pMultiModel;
	}
}

//============================================================
//	�e�I�u�W�F�N�g�̐ݒ菈��
//============================================================
void CMultiModel::SetParentObject(CObject* pObject)
{
	// �����̃I�u�W�F�N�g�|�C���^��e�ɐݒ�
	m_pParent = pObject;
}

//============================================================
//	�e�I�u�W�F�N�g�폜����
//============================================================
void CMultiModel::DeleteParentObject()
{
	// �e�I�u�W�F�N�g��nullptr�ɂ���
	m_pParent = nullptr;
}

//============================================================
//	�`��}�g���b�N�X�̌v�Z����
//============================================================
void CMultiModel::CalcDrawMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^
	MATRIX* pMtxWorld = GetPtrMtxWorld();	// ���[���h�}�g���b�N�X
	MATRIX mtxScale, mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X
	MATRIX mtxParent;						// �e�̃}�g���b�N�X
	VECTOR3 pos = GetVec3Position();		// ���f���̈ʒu
	VECTOR3 rot = GetVec3Rotation();		// ���f���̌���
	VECTOR3 scale = GetVec3Scale();			// ���f���̊g�嗦

	// ���[���h�}�g���b�N�X�̏�����
	pMtxWorld->Identity();

	// �g�嗦�𔽉f
	mtxScale.Scaling(scale);
	pMtxWorld->Multiply(*pMtxWorld, mtxScale);

	// �����𔽉f
	mtxRot.Rotation(rot);
	pMtxWorld->Multiply(*pMtxWorld, mtxRot);

	// �ʒu�𔽉f
	mtxTrans.Translation(pos);
	pMtxWorld->Multiply(*pMtxWorld, mtxTrans);

	// �e�}�g���b�N�X��ݒ�
	if (m_pParent == nullptr)
	{ // �e�����݂��Ȃ��ꍇ

		// ���݂̃}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);	// �ݒ肳�ꂽ�ŐV�̃}�g���b�N�X (���̂̃}�g���b�N�X)
	}
	else
	{ // �e�����݂���ꍇ

		// �e�̃}�g���b�N�X��ݒ�
		mtxParent = *m_pParent->GetPtrMtxWorld();
	}

	// ���[���h�}�g���b�N�X�Ɛe�}�g���b�N�X���|�����킹��
	pMtxWorld->Multiply(*pMtxWorld, mtxParent);
}
