//============================================================
//
//	�I�u�W�F�N�g���f������ [objectModel.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectModel.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�q�N���X [CObjectModel] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectModel::CObjectModel(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObject(label, dimension, nPriority),
	m_pRenderState	(nullptr),		// �����_�[�X�e�[�g�̏��
	m_pMat			(nullptr),		// �}�e���A���ւ̃|�C���^
	m_modelData		({}),			// ���f�����
	m_mtxWorld		(MTX_IDENT),	// ���[���h�}�g���b�N�X
	m_pos			(VEC3_ZERO),	// �ʒu
	m_rot			(VEC3_ZERO),	// ����
	m_scale			(VEC3_ZERO),	// �g�嗦
	m_nModelIdx		(0)				// ���f���C���f�b�N�X
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectModel::~CObjectModel()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectModel::Init()
{
	// �����o�ϐ���������
	m_pRenderState	= nullptr;		// �����_�[�X�e�[�g�̏��
	m_pMat			= nullptr;		// �}�e���A���ւ̃|�C���^
	m_modelData		= {};			// ���f�����
	m_mtxWorld		= MTX_IDENT;	// ���[���h�}�g���b�N�X
	m_pos			= VEC3_ZERO;	// �ʒu
	m_rot			= VEC3_ZERO;	// ����
	m_scale			= VEC3_ONE;		// �g�嗦
	m_nModelIdx		= NONE_IDX;		// ���f���C���f�b�N�X

	// �����_�[�X�e�[�g�̐���
	m_pRenderState = CRenderState::Create();
	if (m_pRenderState == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectModel::Uninit()
{
	// �����_�[�X�e�[�g�̔j��
	SAFE_REF_RELEASE(m_pRenderState);

	// �}�e���A���̔j��
	SAFE_DEL_ARRAY(m_pMat);

	// �I�u�W�F�N�g���f����j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CObjectModel::Update(const float fDeltaTime)
{

}

//============================================================
//	�`�揈��
//============================================================
void CObjectModel::Draw(CShader* pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^
	D3DMATERIAL9 matDef;	// ���݂̃}�e���A���ۑ��p

	// �����_�[�X�e�[�g��ݒ�
	m_pRenderState->Set();

	// �`��}�g���b�N�X�̌v�Z
	CalcDrawMatrix();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	if (pShader == nullptr)
	{ // �V�F�[�_�[���g�p����Ă��Ȃ��ꍇ

		// �ʏ�`��
		DrawNormal();
	}
	else
	{ // �V�F�[�_�[���g�p����Ă���ꍇ

		// �V�F�[�_�[�`��
		DrawShader(pShader);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	// �����_�[�X�e�[�g���Đݒ�
	m_pRenderState->Reset();
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CObjectModel::SetVec3Position(const VECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectModel::SetVec3Rotation(const VECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_rot = rRot;

	// �����̐��K��
	useful::NormalizeRot(m_rot);
}

//============================================================
//	�g�嗦�̐ݒ菈��
//============================================================
void CObjectModel::SetVec3Scale(const VECTOR3& rScale)
{
	// �����̊g�嗦����
	m_scale = rScale;
}

//============================================================
//	��������
//============================================================
CObjectModel* CObjectModel::Create(const VECTOR3& rPos, const VECTOR3& rRot, const VECTOR3& rScale)
{
	// �I�u�W�F�N�g���f���̐���
	CObjectModel* pModel = new CObjectModel;
	if (pModel == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g���f���̏�����
		if (FAILED(pModel->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g���f���̔j��
			SAFE_DELETE(pModel);
			return nullptr;
		}

		// �ʒu��ݒ�
		pModel->SetVec3Position(rPos);

		// ������ݒ�
		pModel->SetVec3Rotation(rRot);

		// �g�嗦��ݒ�
		pModel->SetVec3Scale(rScale);

		// �m�ۂ����A�h���X��Ԃ�
		return pModel;
	}
}

//============================================================
//	�}�e���A���ݒ菈��
//============================================================
void CObjectModel::SetMaterial(const D3DXMATERIAL& rMat, const int nMatIdx)
{
	if (nMatIdx > NONE_IDX && nMatIdx < (int)m_modelData.dwNumMat)
	{ // �����C���f�b�N�X���}�e���A���̍ő吔�𒴂��Ă��Ȃ��ꍇ

		// �����C���f�b�N�X�̃}�e���A����ݒ�
		m_pMat[nMatIdx] = rMat;
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	�}�e���A���擾����
//============================================================
D3DXMATERIAL CObjectModel::GetMaterial(const int nMatIdx) const
{
	if (nMatIdx > NONE_IDX && nMatIdx < (int)m_modelData.dwNumMat)
	{ // �����C���f�b�N�X���}�e���A���̍ő吔�𒴂��Ă��Ȃ��ꍇ

		// �����C���f�b�N�X�̃}�e���A����Ԃ�
		return m_pMat[nMatIdx];
	}
	else
	{ // �����C���f�b�N�X���}�e���A���̍ő吔�𒴂��Ă���ꍇ

		// ��O���̃}�e���A����Ԃ�
		return material::White();
	}
}

//============================================================
//	�����x�̐ݒ菈��
//============================================================
void CObjectModel::SetAlpha(const float fAlpha)
{
	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pOriginMat;	// �}�e���A���f�[�^�ւ̃|�C���^
	pOriginMat = (D3DXMATERIAL*)m_modelData.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_modelData.dwNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		float fSetAlpha = fAlpha;	// �ݒ肷�铧���x

		// �����x�̕␳
		useful::LimitNum(fSetAlpha, 0.0f, pOriginMat[nCntMat].MatD3D.Diffuse.a);

		// �����x��ݒ�
		m_pMat[nCntMat].MatD3D.Diffuse.a = fSetAlpha;
	}
}

//============================================================
//	�����x�擾����
//============================================================
float CObjectModel::GetAlpha() const
{
	// �ł��s�����ȓ����x��T��
	float fAlpha = 0.0f;	// �ł��s�����ȃ}�e���A���̓����x
	for (int nCntMat = 0; nCntMat < (int)m_modelData.dwNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		if (m_pMat[nCntMat].MatD3D.Diffuse.a > fAlpha)
		{ // �}�e���A���̓����x�����s�����������ꍇ

			// ���݂̃}�e���A���̓����x��ۑ�
			fAlpha = m_pMat[nCntMat].MatD3D.Diffuse.a;
		}
	}

	// �S�p�[�c���ōł��s�����������}�e���A���̓����x��Ԃ�
	return fAlpha;
}

//============================================================
//	�ő哧���x�擾����
//============================================================
float CObjectModel::GetMaxAlpha() const
{
	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pOriginMat;	// �}�e���A���f�[�^�ւ̃|�C���^
	pOriginMat = (D3DXMATERIAL*)m_modelData.pBuffMat->GetBufferPointer();

	float fAlpha = 0.0f;	// �ł��s�����ȃ}�e���A���̓����x
	for (int nCntMat = 0; nCntMat < (int)m_modelData.dwNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		if (pOriginMat[nCntMat].MatD3D.Diffuse.a > fAlpha)
		{ // �}�e���A���̓����x�����s�����������ꍇ

			// ���݂̃}�e���A���̓����x��ۑ�
			fAlpha = pOriginMat[nCntMat].MatD3D.Diffuse.a;
		}
	}

	// �S�p�[�c���ōł��s�����������}�e���A���̓����x��Ԃ�
	return fAlpha;
}

//============================================================
//	�����_�[�X�e�[�g���̎擾����
//============================================================
CRenderState* CObjectModel::GetRenderState()
{
	// �C���X�^���X���g�p
	assert(m_pRenderState != nullptr);

	// �����_�[�X�e�[�g�̏���Ԃ�
	return m_pRenderState;
}

//============================================================
//	���f���������� (�C���f�b�N�X)
//============================================================
void CObjectModel::BindModel(const int nModelIdx)
{
	if (nModelIdx > NONE_IDX)
	{ // ���f���C���f�b�N�X���g�p�\�ȏꍇ

		CModel* pModel = GET_MANAGER->GetModel();	// ���f���ւ̃|�C���^

		// ���f���C���f�b�N�X����
		m_nModelIdx = nModelIdx;

		// ���f�������蓖��
		m_modelData = *pModel->GetInfo(nModelIdx);

		// ���}�e���A���̐ݒ�
		if (FAILED(SetOriginMaterial(m_modelData.pBuffMat, (int)m_modelData.dwNumMat)))
		{ assert(false); }	// �ݒ莸�s
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	���f���������� (�p�X)
//============================================================
void CObjectModel::BindModel(const char* pModelPath)
{
	if (pModelPath != nullptr)
	{ // ���蓖�Ă郂�f���p�X�����݂���ꍇ

		CModel* pModel = GET_MANAGER->GetModel();	// ���f���ւ̃|�C���^

		// ���f���C���f�b�N�X����
		m_nModelIdx = pModel->Regist(pModelPath);

		// ���f�������蓖��
		m_modelData = *pModel->GetInfo(m_nModelIdx);

		// ���}�e���A���̐ݒ�
		if (FAILED(SetOriginMaterial(m_modelData.pBuffMat, (int)m_modelData.dwNumMat)))
		{ assert(false); }	// �ݒ莸�s
	}
	else { assert(false); }	// ���f���p�X����
}

//============================================================
//	�}�e���A���̑S�ݒ菈��
//============================================================
void CObjectModel::SetAllMaterial(const D3DXMATERIAL& rMat)
{
	// �����̃}�e���A����S�}�e���A���ɐݒ�
	for (int nCntMat = 0; nCntMat < (int)m_modelData.dwNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		m_pMat[nCntMat] = rMat;
	}
}

//============================================================
//	�}�e���A���̍Đݒ菈��
//============================================================
void CObjectModel::ResetMaterial()
{
	// ����ł���ꍇ������
	if (IsDeath()) { return; }

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pOriginMat;	// �}�e���A���f�[�^�ւ̃|�C���^
	pOriginMat = (D3DXMATERIAL*)m_modelData.pBuffMat->GetBufferPointer();

	// �S�}�e���A���ɏ����}�e���A�����Đݒ�
	if (m_pMat != nullptr)
	{ // �g�p����Ă���ꍇ

		for (int nCntMat = 0; nCntMat < (int)m_modelData.dwNumMat; nCntMat++)
		{ // �}�e���A���̐����J��Ԃ�

			m_pMat[nCntMat] = pOriginMat[nCntMat];
		}
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	���f�����̐ݒ菈��
//============================================================
void CObjectModel::SetModelData(const CModel::SModel& rModel)
{
	// �����̃��f��������
	m_modelData = rModel;
}

//============================================================
//	�`��}�g���b�N�X�̌v�Z����
//============================================================
void CObjectModel::CalcDrawMatrix()
{
	MATRIX mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	m_mtxWorld.Identity();

	// �g�嗦�𔽉f
	mtxScale.Scaling(m_scale);
	m_mtxWorld.Multiply(m_mtxWorld, mtxScale);

	// �����𔽉f
	mtxRot.Rotation(m_rot);
	m_mtxWorld.Multiply(m_mtxWorld, mtxRot);

	// �ʒu�𔽉f
	mtxTrans.Translation(m_pos);
	m_mtxWorld.Multiply(m_mtxWorld, mtxTrans);
}

//============================================================
//	�}�e���A���|�C���^�擾����
//============================================================
D3DXMATERIAL* CObjectModel::GetPtrMaterial(const int nIdx) const
{
	if (nIdx > NONE_IDX && nIdx < (int)m_modelData.dwNumMat)
	{ // �����C���f�b�N�X���}�e���A���̍ő吔�𒴂��Ă��Ȃ��ꍇ

		// �����C���f�b�N�X�̃}�e���A����Ԃ�
		return &m_pMat[nIdx];
	}
	else
	{ // �����C���f�b�N�X���}�e���A���̍ő吔�𒴂��Ă���ꍇ

		// nullptr��Ԃ�
		return nullptr;
	}
}

//============================================================
//	���}�e���A���̐ݒ菈��
//============================================================
HRESULT CObjectModel::SetOriginMaterial(const LPD3DXBUFFER pBuffMat, const int nNumMat)
{
	//--------------------------------------------------------
	//	�������J���E�m��
	//--------------------------------------------------------
	// �}�e���A���̔j��
	SAFE_DEL_ARRAY(m_pMat);

	if (m_pMat == nullptr)
	{ // �|�C���^���g�p����Ă��Ȃ��ꍇ

		// �}�e���A�������̃������m��
		m_pMat = new D3DXMATERIAL[nNumMat];

		if (m_pMat != nullptr)
		{ // �m�ۂɐ��������ꍇ

			// �������N���A
			memset(m_pMat, 0, sizeof(D3DXMATERIAL) * nNumMat);
		}
		else { assert(false); return E_FAIL; }	// �m�ێ��s
	}
	else { assert(false); return E_FAIL; }	// �g�p��

	//--------------------------------------------------------
	//	�}�e���A������ݒ�
	//--------------------------------------------------------
	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pOriginMat;	// �}�e���A���f�[�^�ւ̃|�C���^
	pOriginMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < nNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		// �}�e���A���f�[�^���R�s�[
		m_pMat[nCntMat] = pOriginMat[nCntMat];
	}

	return S_OK;
}

//============================================================
//	�ʏ�`�揈��
//============================================================
void CObjectModel::DrawNormal()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;			// �f�o�C�X�̃|�C���^
	CTexture* pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`�����

	if (m_scale != VEC3_ONE)
	{ // �g�嗦���ύX����Ă���ꍇ

		// ���_�@���̎������K����L���ɂ���
		pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	}

	for (int nCntMat = 0; nCntMat < (int)m_modelData.dwNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&m_pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTexture->GetPtr(m_modelData.pTextureIdx[nCntMat]));

		// ���f���̕`��
		m_modelData.pMesh->DrawSubset(nCntMat);
	}

	// ���_�@���̎������K���𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, false);
}

//============================================================
//	�V�F�[�_�[�`�揈��
//============================================================
void CObjectModel::DrawShader(CShader* pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;			// �f�o�C�X�̃|�C���^
	CTexture* pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`�����

	// �`��J�n
	pShader->Begin();
	pShader->BeginPass(0);

	// �}�g���b�N�X����ݒ�
	pShader->SetMatrix(&m_mtxWorld);

	// ���C�g������ݒ�
	pShader->SetLightDirect(&m_mtxWorld, 0);

	if (m_scale != VEC3_ONE)
	{ // �g�嗦���ύX����Ă���ꍇ

		// ���_�@���̎������K����L���ɂ���
		pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	}

	for (int nCntMat = 0; nCntMat < (int)m_modelData.dwNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&m_pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTexture->GetPtr(m_modelData.pTextureIdx[nCntMat]));

		// �}�e���A����ݒ�
		pShader->SetMaterial(m_pMat[nCntMat].MatD3D);

		// �e�N�X�`����ݒ�
		pShader->SetTexture(m_modelData.pTextureIdx[nCntMat]);

		// ��ԕύX�̓`�B
		pShader->CommitChanges();

		// ���f���̕`��
		m_modelData.pMesh->DrawSubset(nCntMat);
	}

	// ���_�@���̎������K���𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, false);

	// �`��I��
	pShader->EndPass();
	pShader->End();
}
