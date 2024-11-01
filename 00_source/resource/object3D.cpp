//============================================================
//
//	�I�u�W�F�N�g3D���� [object3D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "collision.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int MAX_VERTEX = 4;	// ���_��
}

//************************************************************
//	�q�N���X [CObject3D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObject3D::CObject3D(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObject(label, dimension, nPriority),
	m_pVtxBuff		(nullptr),			// ���_�o�b�t�@�ւ̃|�C���^
	m_pRenderState	(nullptr),			// �����_�[�X�e�[�g�̏��
	m_pPosGapBuff	(nullptr),			// ���W�̂���o�b�t�@
	m_mtxWorld		(MTX_IDENT),		// ���[���h�}�g���b�N�X
	m_pos			(VEC3_ZERO),		// �ʒu
	m_rot			(VEC3_ZERO),		// ����
	m_size			(VEC3_ZERO),		// �傫��
	m_col			(color::White()),	// �F
	m_origin		(ORIGIN_CENTER),	// ���_
	m_nTextureIdx	(0)					// �e�N�X�`���C���f�b�N�X
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CObject3D::~CObject3D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObject3D::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �����o�ϐ���������
	m_pVtxBuff		= nullptr;			// ���_�o�b�t�@�ւ̃|�C���^
	m_pRenderState	= nullptr;			// �����_�[�X�e�[�g�̏��
	m_pPosGapBuff	= nullptr;			// ���W�̂���o�b�t�@
	m_mtxWorld		= MTX_IDENT;		// ���[���h�}�g���b�N�X
	m_pos			= VEC3_ZERO;		// �ʒu
	m_rot			= VEC3_ZERO;		// ����
	m_size			= VEC3_ZERO;		// �傫��
	m_col			= color::White();	// �F
	m_origin		= ORIGIN_CENTER;	// ���_
	m_nTextureIdx	= NONE_IDX;			// �e�N�X�`���C���f�b�N�X

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	( // ����
		sizeof(VERTEX_3D) * MAX_VERTEX,	// �K�v���_��
		D3DUSAGE_WRITEONLY,				// �g�p���@
		CObject::FVF_VERTEX_3D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// �������̎w��
		&m_pVtxBuff,					// ���_�o�b�t�@�ւ̃|�C���^
		nullptr
	)))
	{ // ���_�o�b�t�@�̐����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �����_�[�X�e�[�g�̐���
	m_pRenderState = CRenderState::Create();
	if (m_pRenderState == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// ���W�̂���o�b�t�@�̃������m��
	m_pPosGapBuff = new VECTOR3[MAX_VERTEX];
	if (m_pPosGapBuff != nullptr)
	{ // �m�ۂɐ��������ꍇ

		// �������N���A
		memset(m_pPosGapBuff, 0, sizeof(VECTOR3) * MAX_VERTEX);
	}
	else
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// ���_���̐ݒ�
	SetVtx();

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObject3D::Uninit()
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);

	// �����_�[�X�e�[�g�̔j��
	SAFE_REF_RELEASE(m_pRenderState);

	// ���W�̂���o�b�t�@�̔j��
	SAFE_DEL_ARRAY(m_pPosGapBuff);

	// �I�u�W�F�N�g3D��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CObject3D::Update(const float fDeltaTime)
{

}

//============================================================
//	�`�揈��
//============================================================
void CObject3D::Draw(CShader* pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �����_�[�X�e�[�g��ݒ�
	m_pRenderState->Set();

	// �`��}�g���b�N�X�̌v�Z
	CalcDrawMatrix();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(CObject::FVF_VERTEX_3D);

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

	// �����_�[�X�e�[�g���Đݒ�
	m_pRenderState->Reset();
}

//============================================================
//	��������
//============================================================
CObject3D* CObject3D::Create
(
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rSize,	// �傫��
	const VECTOR3& rRot,	// ����
	const COLOR& rCol,		// �F
	const EOrigin origin	// ���_
)
{
	// �I�u�W�F�N�g3D�̐���
	CObject3D* pObject3D = new CObject3D;
	if (pObject3D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g3D�̏�����
		if (FAILED(pObject3D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g3D�̔j��
			SAFE_DELETE(pObject3D);
			return nullptr;
		}

		// ���_��ݒ�
		pObject3D->SetOrigin(origin);

		// �ʒu��ݒ�
		pObject3D->SetVec3Position(rPos);

		// ������ݒ�
		pObject3D->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pObject3D->SetVec3Size(rSize);

		// �F��ݒ�
		pObject3D->SetColor(rCol);

		// �m�ۂ����A�h���X��Ԃ�
		return pObject3D;
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CObject3D::SetVec3Position(const VECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObject3D::SetVec3Rotation(const VECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_rot = rRot;

	// �����̐��K��
	useful::NormalizeRot(m_rot);

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CObject3D::SetVec3Size(const VECTOR3& rSize)
{
	// �����̑傫������
	m_size = rSize;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�����_�[�X�e�[�g���̎擾����
//============================================================
CRenderState* CObject3D::GetRenderState()
{
	// �C���X�^���X���g�p
	assert(m_pRenderState != nullptr);

	// �����_�[�X�e�[�g�̏���Ԃ�
	return m_pRenderState;
}

//============================================================
//	�e�N�X�`���������� (�C���f�b�N�X)
//============================================================
void CObject3D::BindTexture(const int nTextureIdx)
{
	if (nTextureIdx >= NONE_IDX)
	{ // �e�N�X�`���C���f�b�N�X���g�p�\�ȏꍇ

		// �e�N�X�`���C���f�b�N�X����
		m_nTextureIdx = nTextureIdx;
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	�e�N�X�`���������� (�p�X)
//============================================================
void CObject3D::BindTexture(const char* pTexturePath)
{
	if (pTexturePath != nullptr)
	{ // ���蓖�Ă�e�N�X�`���p�X������ꍇ

		// �e�N�X�`���C���f�b�N�X��ݒ�
		CTexture* pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`���ւ̃|�C���^
		m_nTextureIdx = pTexture->Regist(pTexturePath);
	}
	else
	{ // ���蓖�Ă�e�N�X�`���p�X���Ȃ��ꍇ

		// �e�N�X�`���Ȃ��C���f�b�N�X��ݒ�
		m_nTextureIdx = NONE_IDX;
	}
}

//============================================================
//	�����x�̐ݒ菈��
//============================================================
void CObject3D::SetAlpha(const float fAlpha)
{
	// �����̓����x����
	m_col.a = fAlpha;

	// �F�̐ݒ�
	SetColor(m_col);
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CObject3D::SetColor(const COLOR& rCol)
{
	// �����̐F����
	m_col = rCol;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	���_�̐ݒ菈��
//============================================================
void CObject3D::SetOrigin(const EOrigin origin)
{
	// �����̌��_��ݒ�
	m_origin = origin;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	���_�ʒu�̐ݒ菈��
//============================================================
void CObject3D::SetVertexPosition(const int nIdx, const VECTOR3& rPos)
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		if (nIdx < MAX_VERTEX)
		{ // �C���f�b�N�X���g�p�\�ȏꍇ

			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�f�[�^�̃|�C���^���������i�߂�
			pVtx += nIdx;

			// ���_���W�̐ݒ�
			pVtx[0].pos = rPos;

			// ���_�o�b�t�@���A�����b�N����
			m_pVtxBuff->Unlock();
		}
	}

	// �@���̐ݒ�E���K��
	NormalizeNormal();
}

//============================================================
//	���_�ʒu�擾����
//============================================================
VECTOR3 CObject3D::GetVertexPosition(const int nIdx)
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	VECTOR3 pos;		// ���_���W�̑���p
	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		if (nIdx < MAX_VERTEX)
		{ // �C���f�b�N�X���g�p�\�ȏꍇ

			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�f�[�^�̃|�C���^���������i�߂�
			pVtx += nIdx;

			// ���_���W����
			pos = pVtx[0].pos;

			// ���_�o�b�t�@���A�����b�N����
			m_pVtxBuff->Unlock();
		}
	}

	// �����̃C���f�b�N�X�̒��_���W��Ԃ�
	return pos;
}

//============================================================
//	���W�̂���̐ݒ菈��
//============================================================
void CObject3D::SetGapPosition(const int nIdx, const VECTOR3& rPos)
{
	if (m_pPosGapBuff != nullptr)
	{ // �g�p���̏ꍇ

		if (nIdx < MAX_VERTEX)
		{ // �C���f�b�N�X���g�p�\�ȏꍇ

			// ���_�̂����ݒ�
			m_pPosGapBuff[nIdx] = rPos;

			// ���_���̐ݒ�
			SetVtx();
		}
		else { assert(false); }	// �g�p�s��
	}
}

//============================================================
//	���W�̂���擾����
//============================================================
VECTOR3 CObject3D::GetGapPosition(const int nIdx)
{
	VECTOR3 pos = VEC3_ZERO;	// ���_�̂���̑���p
	if (m_pPosGapBuff != nullptr)
	{ // �g�p���̏ꍇ

		if (nIdx < MAX_VERTEX)
		{ // �C���f�b�N�X���g�p�\�ȏꍇ

			// ���_�̂����ݒ�
			pos = m_pPosGapBuff[nIdx];
		}
		else { assert(false); }	// �g�p�s��
	}

	// �����̃C���f�b�N�X�̒��_�̂����Ԃ�
	return pos;
}

//============================================================
//	�|���S���̒��n�擾����
//============================================================
float CObject3D::GetPositionHeight(const VECTOR3& rPos)
{
	VECTOR3 aVtxPos[MAX_VERTEX];	// �|���S���̒��_���W [��] 0�F���� 1�F�E�� 2�F���� 3�F�E��
	VECTOR3 nor;	// �@���x�N�g��
	for (int nCnt = 0; nCnt < MAX_VERTEX; nCnt++)
	{ // ���_�����J��Ԃ�

		MATRIX mtxWorld, mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X
		VECTOR3 pos = GetVertexPosition(nCnt);	// ���_���W
		
		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld.Identity();

		// ���_�ʒu�𔽉f
		mtxTrans.Translation(pos);
		mtxWorld.Multiply(mtxWorld, mtxTrans);

		// �|���S�������𔽉f
		mtxRot.Rotation(m_rot);
		mtxWorld.Multiply(mtxWorld, mtxRot);

		// �|���S���ʒu�𔽉f
		mtxTrans.Translation(m_pos);
		mtxWorld.Multiply(mtxWorld, mtxTrans);

		// �v�Z�����}�g���b�N�X������W��ݒ�
		aVtxPos[nCnt] = mtxWorld.GetPosition();
	}

	if (collision::TriangleOuterPillar(aVtxPos[0], aVtxPos[1], aVtxPos[2], rPos))
	{ // �|���S���͈͓̔��ɂ���ꍇ

		// �@�������߂�
		useful::NormalizeNormal(aVtxPos[1], aVtxPos[0], aVtxPos[2], nor);

		if (nor.y != 0.0f)
		{ // �@�����ݒ肳��Ă���ꍇ

			// �v���C���[�̒��n�_��Ԃ�
			return (((rPos.x - aVtxPos[0].x) * nor.x + (-aVtxPos[0].y) * nor.y + (rPos.z - aVtxPos[0].z) * nor.z) * -1.0f) / nor.y;
		}
	}

	if (collision::TriangleOuterPillar(aVtxPos[3], aVtxPos[1], aVtxPos[2], rPos))
	{ // �|���S���͈͓̔��ɂ���ꍇ

		// �@�������߂�
		useful::NormalizeNormal(aVtxPos[2], aVtxPos[3], aVtxPos[1], nor);

		if (nor.y != 0.0f)
		{ // �@�����ݒ肳��Ă���ꍇ

			// �v���C���[�̒��n�_��Ԃ�
			return (((rPos.x - aVtxPos[3].x) * nor.x + (-aVtxPos[3].y) * nor.y + (rPos.z - aVtxPos[3].z) * nor.z) * -1.0f) / nor.y;
		}
	}

	// ���n�͈͊O�̏ꍇ���݂�y���W��Ԃ�
	return rPos.y;
}

//============================================================
//	�`��}�g���b�N�X�̌v�Z����
//============================================================
void CObject3D::CalcDrawMatrix()
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

//============================================================
//	���_���̐ݒ菈��
//============================================================
void CObject3D::SetVtx()
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (m_origin)
	{ // ���_���Ƃ̏���
	case ORIGIN_CENTER:	// ����

		// ���_���W�̐ݒ�
		pVtx[0].pos = VECTOR3(-m_size.x * 0.5f,  m_size.y * 0.5f,  m_size.z * 0.5f);
		pVtx[1].pos = VECTOR3( m_size.x * 0.5f,  m_size.y * 0.5f,  m_size.z * 0.5f);
		pVtx[2].pos = VECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);
		pVtx[3].pos = VECTOR3( m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);

		break;

	case ORIGIN_DOWN:	// ��

		// ���_���W�̐ݒ�
		pVtx[0].pos = VECTOR3(-m_size.x * 0.5f, m_size.y,  m_size.z * 0.5f);
		pVtx[1].pos = VECTOR3( m_size.x * 0.5f, m_size.y,  m_size.z * 0.5f);
		pVtx[2].pos = VECTOR3(-m_size.x * 0.5f,     0.0f, -m_size.z * 0.5f);
		pVtx[3].pos = VECTOR3( m_size.x * 0.5f,     0.0f, -m_size.z * 0.5f);

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// ���_����̂���ʂ����Z
	for (int nCntVtx = 0; nCntVtx < MAX_VERTEX; nCntVtx++)
	{ // ���_�����J��Ԃ�

		pVtx[nCntVtx].pos += m_pPosGapBuff[nCntVtx];
	}

	// �@���̐ݒ�E���K��
	NormalizeNormal();

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = VECTOR2(0.0f, 0.0f);
	pVtx[1].tex = VECTOR2(1.0f, 0.0f);
	pVtx[2].tex = VECTOR2(0.0f, 1.0f);
	pVtx[3].tex = VECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================================
//	�A�j���[�V�����̃e�N�X�`�����W�̐ݒ菈��
//============================================================
void CObject3D::SetAnimTex
(
	const int nPattern,		// �A�j���[�V�����p�^�[��
	const int nWidthPtrn,	// �e�N�X�`���̉��̕�����
	const int nHeightPtrn	// �e�N�X�`���̏c�̕�����
)
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	float fWidthRate	= 1.0f / nWidthPtrn;	// ���̕������̊���
	float fHeightRate	= 1.0f / nHeightPtrn;	// �c�̕������̊���
	int nWidthCurrent	= nPattern % nWidthPtrn;					// ���݂̉��̃p�^�[��
	int nHeightCurrent	= (nPattern / nWidthPtrn) % nHeightPtrn;	// ���݂̏c�̃p�^�[��
	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = VECTOR2(fWidthRate *  nWidthCurrent,		fHeightRate *  nHeightCurrent);
		pVtx[1].tex = VECTOR2(fWidthRate * (nWidthCurrent + 1),	fHeightRate *  nHeightCurrent);
		pVtx[2].tex = VECTOR2(fWidthRate *  nWidthCurrent,		fHeightRate * (nHeightCurrent + 1));
		pVtx[3].tex = VECTOR2(fWidthRate * (nWidthCurrent + 1),	fHeightRate * (nHeightCurrent + 1));

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//============================================================
//	�X�N���[���̃e�N�X�`�����W�̐ݒ菈��
//============================================================
void CObject3D::SetScrollTex
(
	const float fTexU,		// �e�N�X�`���̉����W�̊J�n�ʒu
	const float fTexV,		// �e�N�X�`���̏c���W�̊J�n�ʒu
	const float fOffsetU,	// �e�N�X�`���̉����W�̃I�t�Z�b�g�ʒu
	const float fOffsetV	// �e�N�X�`���̏c���W�̃I�t�Z�b�g�ʒu
)
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = VECTOR2(fTexU,			fTexV);
		pVtx[1].tex = VECTOR2(fTexU + fOffsetU,	fTexV);
		pVtx[2].tex = VECTOR2(fTexU,			fTexV + fOffsetV);
		pVtx[3].tex = VECTOR2(fTexU + fOffsetU,	fTexV + fOffsetV);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//============================================================
//	�ʏ�`�揈��
//============================================================
void CObject3D::DrawNormal()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_nTextureIdx));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//============================================================
//	�V�F�[�_�[�`�揈��
//============================================================
void CObject3D::DrawShader(CShader* pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �`��J�n
	pShader->Begin();
	pShader->BeginPass(0);

	// �}�g���b�N�X����ݒ�
	pShader->SetMatrix(&m_mtxWorld);

	// ���C�g������ݒ�
	pShader->SetLightDirect(&m_mtxWorld, 0);

	// �g�U����ݒ�
	pShader->SetOnlyDiffuse(m_col);

	// �e�N�X�`����ݒ�
	pShader->SetTexture(m_nTextureIdx);

	// ��ԕύX�̓`�B
	pShader->CommitChanges();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_nTextureIdx));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �`��I��
	pShader->EndPass();
	pShader->End();
}

//============================================================
//	�@���̐��K������
//============================================================
void CObject3D::NormalizeNormal()
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �@���̐��K��
	useful::NormalizeNormal
	( // ����
		pVtx[1].pos,	// ���ʒu
		pVtx[0].pos,	// ���S�ʒu
		pVtx[2].pos,	// �E�ʒu
		pVtx[0].nor		// �@��
	);

	// �@���̐��K��
	useful::NormalizeNormal
	( // ����
		pVtx[2].pos,	// ���ʒu
		pVtx[3].pos,	// ���S�ʒu
		pVtx[1].pos,	// �E�ʒu
		pVtx[3].nor		// �@��
	);

	// �@���x�N�g���̐ݒ�
	pVtx[1].nor = (pVtx[0].nor + pVtx[3].nor) / 2;
	pVtx[2].nor = (pVtx[0].nor + pVtx[3].nor) / 2;

	// �@���𐳋K��
	D3DXVec3Normalize(&pVtx[1].nor, &pVtx[1].nor);
	D3DXVec3Normalize(&pVtx[2].nor, &pVtx[2].nor);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
