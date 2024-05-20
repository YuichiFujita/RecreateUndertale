//============================================================
//
//	�I�u�W�F�N�g���b�V���`���[�u���� [objectMeshTube.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectMeshTube.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "objectMeshCircle.h"
#include "objectMeshCylinder.h"
#include "renderState.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const POSGRID2 MIN_PART		= POSGRID2(1, 2);	// �������̍ŏ��l
	const POSGRID2 MIN_TEXPART	= GRID2_ONE;		// �e�N�X�`���������̍ŏ��l
}

//************************************************************
//	�q�N���X [CObjectMeshTube] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectMeshTube::CObjectMeshTube(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObject(label, dimension, nPriority),
	m_pCylinder	(nullptr),		// ���̏��
	m_part		(GRID2_ZERO),	// ������
	m_texPart	(GRID2_ZERO)	// �e�N�X�`��������
{
	// �����o�ϐ����N���A
	memset(&m_apCover[0], 0, sizeof(m_apCover));	// �W�̏��
}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectMeshTube::~CObjectMeshTube()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectMeshTube::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apCover[0], 0, sizeof(m_apCover));	// �W�̏��
	m_pCylinder	= nullptr;		// ���̏��
	m_part		= MIN_PART;		// ������
	m_texPart	= MIN_TEXPART;	// �e�N�X�`��������

	for (int i = 0; i < COVER_MAX; i++)
	{ // �W�̑������J��Ԃ�

		// ���b�V���T�[�N���̐���
		m_apCover[i] = CObjectMeshCircle::Create
		( // ����
			VEC3_ZERO,		// �ʒu
			VEC3_ZERO,		// ����
			XCOL_WHITE,		// �F
			MIN_PART,		// ������
			0.0f			// ���a
		);

		// �����X�V�E�����`���OFF�ɂ���
		m_apCover[i]->SetEnableUpdate(false);
		m_apCover[i]->SetEnableDraw(false);
	}

	// ���b�V���V�����_�[�̐���
	m_pCylinder = CObjectMeshCylinder::Create
	( // ����
		VEC3_ZERO,		// �ʒu
		VEC3_ZERO,		// ����
		XCOL_WHITE,		// �F
		MIN_PART,		// ������
		MIN_TEXPART,	// �e�N�X�`��������
		0.0f,			// ���a
		0.0f			// �c��
	);

	// �����X�V�E�����`���OFF�ɂ���
	m_pCylinder->SetEnableUpdate(false);
	m_pCylinder->SetEnableDraw(false);

	// ��������ݒ�
	if (FAILED(SetPattern(MIN_PART)))
	{ // �������̐ݒ�Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectMeshTube::Uninit(void)
{
	for (int i = 0; i < COVER_MAX; i++)
	{ // �W�̑������J��Ԃ�

		// ���b�V���T�[�N���̏I��
		SAFE_UNINIT(m_apCover[i]);
	}

	// ���b�V���V�����_�[�̏I��
	SAFE_UNINIT(m_pCylinder);

	// �I�u�W�F�N�g���b�V���`���[�u��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CObjectMeshTube::Update(const float fDeltaTime)
{
	for (int i = 0; i < COVER_MAX; i++)
	{ // �W�̑������J��Ԃ�

		// ���b�V���T�[�N���̍X�V
		m_apCover[i]->Update(fDeltaTime);
	}

	// ���b�V���V�����_�[�̍X�V
	m_pCylinder->Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CObjectMeshTube::Draw(CShader *pShader)
{
	for (int i = 0; i < COVER_MAX; i++)
	{ // �W�̑������J��Ԃ�

		// ���b�V���T�[�N���̕`��
		m_apCover[i]->Draw(pShader);
	}

	// ���b�V���V�����_�[�̕`��
	m_pCylinder->Draw(pShader);
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CObjectMeshTube::SetPriority(const int nPriority)
{
	// �����̗D�揇�ʂ�ݒ�
	CObject::SetPriority(nPriority);		// ���g
	m_pCylinder->SetPriority(nPriority);	// ��
	for (int i = 0; i < COVER_MAX; i++)
	{ // �W�̑������J��Ԃ�

		m_apCover[i]->SetPriority(nPriority);	// �W
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CObjectMeshTube::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pCylinder->SetVec3Position(rPos);

	// ���Έʒu��ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectMeshTube::SetVec3Rotation(const D3DXVECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_pCylinder->SetVec3Rotation(rRot);

	// ���Έʒu��ݒ�
	SetPositionRelative();
}

//============================================================
//	��������
//============================================================
CObjectMeshTube *CObjectMeshTube::Create
(
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot,	// ����
	const D3DXCOLOR& rCol,		// �F
	const POSGRID2& rPart,		// ������
	const POSGRID2& rTexPart,	// �e�N�X�`��������
	const float fRadius,		// ���a
	const float fHeight			// �c��
)
{
	// �I�u�W�F�N�g���b�V���`���[�u�̐���
	CObjectMeshTube *pMeshTube = new CObjectMeshTube;
	if (pMeshTube == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g���b�V���`���[�u�̏�����
		if (FAILED(pMeshTube->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g���b�V���`���[�u�̔j��
			SAFE_DELETE(pMeshTube);
			return nullptr;
		}

		// �ʒu��ݒ�
		pMeshTube->SetVec3Position(rPos);

		// ������ݒ�
		pMeshTube->SetVec3Rotation(rRot);

		// �F��ݒ�
		pMeshTube->SetColor(rCol);

		// ���a��ݒ�
		pMeshTube->SetRadius(fRadius);

		// �c����ݒ�
		pMeshTube->SetHeight(fHeight);

		// ��������ݒ�
		if (FAILED(pMeshTube->SetPattern(rPart)))
		{ // �������̐ݒ�Ɏ��s�����ꍇ

			// �I�u�W�F�N�g���b�V���`���[�u�̔j��
			SAFE_DELETE(pMeshTube);
			return nullptr;
		}

		// �e�N�X�`����������ݒ�
		pMeshTube->SetTexPattern(rTexPart);

		// �m�ۂ����A�h���X��Ԃ�
		return pMeshTube;
	}
}

//============================================================
//	�����_�[�X�e�[�g���̐ݒ菈��
//============================================================
void CObjectMeshTube::SetRenderState(CRenderState renderState)
{
	CRenderState *pTempRenderState = nullptr;	// �����_�[�X�e�[�g���

	// �����̃����_�[�X�e�[�g��ݒ�
	pTempRenderState = m_pCylinder->GetRenderState();
	*pTempRenderState = renderState;

	for (int i = 0; i < COVER_MAX; i++)
	{ // �W�̑������J��Ԃ�

		// �����̃����_�[�X�e�[�g��ݒ�
		pTempRenderState = m_apCover[i]->GetRenderState();
		*pTempRenderState = renderState;
	}
}

//============================================================
//	�e�N�X�`���������� (�C���f�b�N�X)
//============================================================
void CObjectMeshTube::BindTexture(const int nTextureID)
{
	if (nTextureID >= NONE_IDX)
	{ // �e�N�X�`���C���f�b�N�X���g�p�\�ȏꍇ

		for (int i = 0; i < COVER_MAX; i++)
		{ // �W�̑������J��Ԃ�

			// �e�N�X�`���C���f�b�N�X������
			m_apCover[i]->BindTexture(nTextureID);
		}

		// �e�N�X�`���C���f�b�N�X������
		m_pCylinder->BindTexture(nTextureID);
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	�e�N�X�`���������� (�p�X)
//============================================================
void CObjectMeshTube::BindTexture(const char *pTexturePass)
{
	if (pTexturePass != nullptr)
	{ // ���蓖�Ă�e�N�X�`���p�X������ꍇ

		CTexture *pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`���ւ̃|�C���^
		for (int i = 0; i < COVER_MAX; i++)
		{ // �W�̑������J��Ԃ�

			// �e�N�X�`���C���f�b�N�X������
			m_apCover[i]->BindTexture(pTexture->Regist(pTexturePass));
		}

		// �e�N�X�`���C���f�b�N�X������
		m_pCylinder->BindTexture(pTexture->Regist(pTexturePass));
	}
	else
	{ // ���蓖�Ă�e�N�X�`���p�X���Ȃ��ꍇ

		for (int i = 0; i < COVER_MAX; i++)
		{ // �W�̑������J��Ԃ�

			// �e�N�X�`���Ȃ��C���f�b�N�X������
			m_apCover[i]->BindTexture(NONE_IDX);
		}

		// �e�N�X�`���Ȃ��C���f�b�N�X������
		m_pCylinder->BindTexture(NONE_IDX);
	}
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CObjectMeshTube::SetColor(const D3DXCOLOR& rCol)
{
	// �����̐F��ݒ�
	m_pCylinder->SetColor(rCol);

	for (int i = 0; i < COVER_MAX; i++)
	{ // �W�̑������J��Ԃ�

		// �����̐F��ݒ�
		m_apCover[i]->SetColor(rCol);
	}
}

//============================================================
//	���a�̐ݒ菈��
//============================================================
void CObjectMeshTube::SetRadius(const float fRadius)
{
	// �����̔��a��ݒ�
	m_pCylinder->SetRadius(fRadius);

	for (int i = 0; i < COVER_MAX; i++)
	{ // �W�̑������J��Ԃ�

		// �����̔��a��ݒ�
		m_apCover[i]->SetRadius(fRadius);
	}
}

//============================================================
//	�c���̐ݒ菈��
//============================================================
void CObjectMeshTube::SetHeight(const float fHeight)
{
	// �����̏c����ݒ�
	m_pCylinder->SetHeight(fHeight);

	// ���Έʒu��ݒ�
	SetPositionRelative();
}

//============================================================
//	�������̐ݒ菈��
//============================================================
HRESULT CObjectMeshTube::SetPattern(const POSGRID2& rPart)
{
	// �����̕�������ݒ�
	if (FAILED(m_pCylinder->SetPattern(rPart)))
	{ // �ݒ�Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return S_OK;
	}

	for (int i = 0; i < COVER_MAX; i++)
	{ // �W�̑������J��Ԃ�

		// �����̕�������ݒ�
		if (FAILED(m_apCover[i]->SetPattern(rPart)))
		{ // �ݒ�Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return S_OK;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�e�N�X�`���������̐ݒ菈��
//============================================================
void CObjectMeshTube::SetTexPattern(const POSGRID2& rTexPart)
{
	if (rTexPart.x >= MIN_TEXPART.x
	&&  rTexPart.y >= MIN_TEXPART.y)
	{ // �e�N�X�`�����������Œ�l�ȏ�̏ꍇ

		// �����̃e�N�X�`����������ݒ�
		m_pCylinder->SetTexPattern(rTexPart);
	}
	else { assert(false); }	// �Œ�l����
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CObjectMeshTube::SetPositionRelative(void)
{
	D3DXMATRIX  mtxOffset, mtxBottom, mtxTop;	// �}�g���b�N�X�v�Z�p
	D3DXMATRIX  mtxCylinder = CalcCylinderMtxWorld();	// �V�����_�[�}�g���b�N�X
	D3DXVECTOR3 posCylinder = m_pCylinder->GetVec3Position();	// �V�����_�[�ʒu
	D3DXVECTOR3 rotCylinder = m_pCylinder->GetVec3Rotation();	// �V�����_�[����
	float fHeightCylinder   = m_pCylinder->GetHeight();			// �V�����_�[�c��

	// �����I�t�Z�b�g�}�g���b�N�X���쐬�E�|�����킹��
	D3DXMatrixRotationYawPitchRoll(&mtxOffset, 0.0f, D3DX_PI, 0.0f);
	D3DXMatrixMultiply(&mtxBottom, &mtxOffset, &mtxCylinder);

	// ���W�̈ʒu�E������ݒ�
	m_apCover[COVER_BOTTOM]->SetVec3Position(posCylinder);
	m_apCover[COVER_BOTTOM]->SetVec3Rotation(useful::GetMatrixRotation(mtxBottom));

	// �ʒu�I�t�Z�b�g�}�g���b�N�X���쐬�E�|�����킹��
	D3DXMatrixTranslation(&mtxOffset, 0.0f, fHeightCylinder, 0.0f);
	D3DXMatrixMultiply(&mtxTop, &mtxOffset, &mtxCylinder);

	// ��W�̈ʒu�E������ݒ�
	m_apCover[COVER_TOP]->SetVec3Position(useful::GetMatrixPosition(mtxTop));
	m_apCover[COVER_TOP]->SetVec3Rotation(rotCylinder);
}

//============================================================
//	�V�����_�[�}�g���b�N�X�̌v�Z���ʂ̎擾����
//============================================================
D3DXMATRIX CObjectMeshTube::CalcCylinderMtxWorld(void) const
{
	// �ϐ���錾
	D3DXMATRIX  mtxRot, mtxTrans, mtxWorld;	// �v�Z�p�}�g���b�N�X
	D3DXVECTOR3 posCylinder = m_pCylinder->GetVec3Position();	// �V�����_�[�ʒu
	D3DXVECTOR3 rotCylinder = m_pCylinder->GetVec3Rotation();	// �V�����_�[����

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotCylinder.y, rotCylinder.x, rotCylinder.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, posCylinder.x, posCylinder.y, posCylinder.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X��Ԃ�
	return mtxWorld;
}
