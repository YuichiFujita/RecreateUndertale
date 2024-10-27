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
HRESULT CObjectMeshTube::Init()
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
			color::White(),	// �F
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
		color::White(),	// �F
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

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectMeshTube::Uninit()
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
void CObjectMeshTube::Draw(CShader* pShader)
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
void CObjectMeshTube::SetVec3Position(const VECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pCylinder->SetVec3Position(rPos);

	// ���Έʒu��ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectMeshTube::SetVec3Rotation(const VECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_pCylinder->SetVec3Rotation(rRot);

	// ���Έʒu��ݒ�
	SetPositionRelative();
}

//============================================================
//	��������
//============================================================
CObjectMeshTube* CObjectMeshTube::Create
(
	const VECTOR3& rPos,		// �ʒu
	const VECTOR3& rRot,		// ����
	const COLOR& rCol,			// �F
	const POSGRID2& rPart,		// ������
	const POSGRID2& rTexPart,	// �e�N�X�`��������
	const float fRadius,		// ���a
	const float fHeight			// �c��
)
{
	// �I�u�W�F�N�g���b�V���`���[�u�̐���
	CObjectMeshTube* pMeshTube = new CObjectMeshTube;
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
	CRenderState* pTempRenderState = nullptr;	// �����_�[�X�e�[�g���

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
void CObjectMeshTube::BindTexture(const int nTextureIdx)
{
	if (nTextureIdx >= NONE_IDX)
	{ // �e�N�X�`���C���f�b�N�X���g�p�\�ȏꍇ

		for (int i = 0; i < COVER_MAX; i++)
		{ // �W�̑������J��Ԃ�

			// �e�N�X�`���C���f�b�N�X������
			m_apCover[i]->BindTexture(nTextureIdx);
		}

		// �e�N�X�`���C���f�b�N�X������
		m_pCylinder->BindTexture(nTextureIdx);
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	�e�N�X�`���������� (�p�X)
//============================================================
void CObjectMeshTube::BindTexture(const char* pTexturePath)
{
	if (pTexturePath != nullptr)
	{ // ���蓖�Ă�e�N�X�`���p�X������ꍇ

		CTexture* pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`���ւ̃|�C���^
		for (int i = 0; i < COVER_MAX; i++)
		{ // �W�̑������J��Ԃ�

			// �e�N�X�`���C���f�b�N�X������
			m_apCover[i]->BindTexture(pTexture->Regist(pTexturePath));
		}

		// �e�N�X�`���C���f�b�N�X������
		m_pCylinder->BindTexture(pTexture->Regist(pTexturePath));
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
//	�����x�̐ݒ菈��
//============================================================
void CObjectMeshTube::SetAlpha(const float fAlpha)
{
	// �����̓����x��ݒ�
	m_pCylinder->SetAlpha(fAlpha);

	for (int i = 0; i < COVER_MAX; i++)
	{ // �W�̑������J��Ԃ�

		// �����̓����x��ݒ�
		m_apCover[i]->SetAlpha(fAlpha);
	}
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CObjectMeshTube::SetColor(const COLOR& rCol)
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

		assert(false);
		return E_FAIL;
	}

	for (int i = 0; i < COVER_MAX; i++)
	{ // �W�̑������J��Ԃ�

		// �����̕�������ݒ�
		if (FAILED(m_apCover[i]->SetPattern(rPart)))
		{ // �ݒ�Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}
	}

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
void CObjectMeshTube::SetPositionRelative()
{
	MATRIX mtxOffset, mtxBottom, mtxTop;	// �}�g���b�N�X�v�Z�p
	MATRIX mtxCylinder = CalcCylinderMtxWorld();	// �V�����_�[�}�g���b�N�X
	VECTOR3 posCylinder = m_pCylinder->GetVec3Position();	// �V�����_�[�ʒu
	VECTOR3 rotCylinder = m_pCylinder->GetVec3Rotation();	// �V�����_�[����
	float fHeightCylinder = m_pCylinder->GetHeight();		// �V�����_�[�c��

	// �����I�t�Z�b�g�}�g���b�N�X���쐬�E�|�����킹��
	mtxBottom.Rotation(0.0f, D3DX_PI, 0.0f);
	mtxBottom.Multiply(mtxBottom, mtxCylinder);

	// ���W�̈ʒu�E������ݒ�
	m_apCover[COVER_BOTTOM]->SetVec3Position(posCylinder);
	m_apCover[COVER_BOTTOM]->SetVec3Rotation(mtxBottom.GetRotation());

	// �ʒu�I�t�Z�b�g�}�g���b�N�X���쐬�E�|�����킹��
	mtxTop.Translation(0.0f, fHeightCylinder, 0.0f);
	mtxTop.Multiply(mtxTop, mtxCylinder);

	// ��W�̈ʒu�E������ݒ�
	m_apCover[COVER_TOP]->SetVec3Position(mtxTop.GetPosition());
	m_apCover[COVER_TOP]->SetVec3Rotation(rotCylinder);
}

//============================================================
//	�V�����_�[�}�g���b�N�X�̌v�Z���ʂ̎擾����
//============================================================
MATRIX CObjectMeshTube::CalcCylinderMtxWorld() const
{
	MATRIX  mtxRot, mtxTrans, mtxWorld;	// �v�Z�p�}�g���b�N�X
	VECTOR3 posCylinder = m_pCylinder->GetVec3Position();	// �V�����_�[�ʒu
	VECTOR3 rotCylinder = m_pCylinder->GetVec3Rotation();	// �V�����_�[����

	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld.Identity();

	// �����𔽉f
	mtxRot.Rotation(rotCylinder);
	mtxWorld.Multiply(mtxWorld, mtxRot);

	// �ʒu�𔽉f
	mtxTrans.Translation(posCylinder);
	mtxWorld.Multiply(mtxWorld, mtxTrans);

	// ���[���h�}�g���b�N�X��Ԃ�
	return mtxWorld;
}
