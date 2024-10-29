//============================================================
//
//	�I�u�W�F�N�g�r���{�[�h���� [objectBillboard.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectBillboard.h"
#include "manager.h"
#include "renderer.h"
#include "object3D.h"
#include "texture.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int MAX_VERTEX = 4;	// ���_��
}

//************************************************************
//	�q�N���X [CObjectBillboard] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectBillboard::CObjectBillboard(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObject(label, dimension, nPriority),
	m_pVtxBuff		(nullptr),			// ���_�o�b�t�@�ւ̃|�C���^
	m_pRenderState	(nullptr),			// �����_�[�X�e�[�g�̏��
	m_mtxWorld		(MTX_IDENT),		// ���[���h�}�g���b�N�X
	m_pos			(VEC3_ZERO),		// �ʒu
	m_rot			(VEC3_ZERO),		// ����
	m_size			(VEC3_ZERO),		// �傫��
	m_col			(color::White()),	// �F
	m_origin		(ORIGIN_CENTER),	// ���_
	m_rotate		(ROTATE_NORMAL),	// ��]
	m_fAngle		(0.0f),				// �Ίp���̊p�x
	m_fLength		(0.0f),				// �Ίp���̒���
	m_nTextureIdx	(0)					// �e�N�X�`���C���f�b�N�X
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectBillboard::~CObjectBillboard()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectBillboard::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �����o�ϐ���������
	m_pVtxBuff		= nullptr;			// ���_�o�b�t�@�ւ̃|�C���^
	m_pRenderState	= nullptr;			// �����_�[�X�e�[�g�̏��
	m_mtxWorld		= MTX_IDENT;		// ���[���h�}�g���b�N�X
	m_pos			= VEC3_ZERO;		// �ʒu
	m_rot			= VEC3_ZERO;		// ����
	m_size			= VEC3_ZERO;		// �傫��
	m_col			= color::White();	// �F
	m_origin		= ORIGIN_CENTER;	// ���_
	m_rotate		= ROTATE_NORMAL;	// ��]
	m_fAngle		= 0.0f;				// �Ίp���̊p�x
	m_fLength		= 0.0f;				// �Ίp���̒���
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

	// ���C�e�B���O��OFF�ɂ���
	m_pRenderState->SetLighting(false);

	// ���_���̐ݒ�
	SetVtx();

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectBillboard::Uninit()
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);

	// �����_�[�X�e�[�g�̔j��
	SAFE_REF_RELEASE(m_pRenderState);

	// �I�u�W�F�N�g�r���{�[�h��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CObjectBillboard::Update(const float fDeltaTime)
{
	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�`�揈��
//============================================================
void CObjectBillboard::Draw(CShader* pShader)
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
CObjectBillboard* CObjectBillboard::Create
(
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rSize,	// �傫��
	const VECTOR3& rRot,	// ����
	const COLOR& rCol,		// �F
	const EOrigin origin,	// ���_
	const ERotate rotate	// ��]
)
{
	// �I�u�W�F�N�g�r���{�[�h�̐���
	CObjectBillboard* pBillboard = new CObjectBillboard;
	if (pBillboard == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g�r���{�[�h�̏�����
		if (FAILED(pBillboard->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g�r���{�[�h�̔j��
			SAFE_DELETE(pBillboard);
			return nullptr;
		}

		// ���_��ݒ�
		pBillboard->SetOrigin(origin);

		// �ʒu��ݒ�
		pBillboard->SetVec3Position(rPos);

		// ������ݒ�
		pBillboard->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pBillboard->SetVec3Size(rSize);

		// �F��ݒ�
		pBillboard->SetColor(rCol);

		// ��]��ݒ�
		pBillboard->SetRotate(rotate);

		// �m�ۂ����A�h���X��Ԃ�
		return pBillboard;
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CObjectBillboard::SetVec3Position(const VECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectBillboard::SetVec3Rotation(const VECTOR3& rRot)
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
void CObjectBillboard::SetVec3Size(const VECTOR3& rSize)
{
	// �����̑傫������
	m_size = rSize;

	switch (m_origin)
	{ // ���_���Ƃ̏���
	case ORIGIN_CENTER:	// ����

		// �Ίp���̊p�x�����߂�
		m_fAngle = atan2f(m_size.x, m_size.y);

		// �Ίp���̒��������߂�
		m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;

		break;

	case ORIGIN_DOWN:	// ��

		// �Ίp���̊p�x�����߂�
		m_fAngle = atan2f(m_size.x, m_size.y);

		// �Ίp���̒��������߂�
		m_fLength = sqrtf(m_size.x * m_size.x + (m_size.y * 2.0f) * (m_size.y * 2.0f)) * 0.5f;

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�����_�[�X�e�[�g���̎擾����
//============================================================
CRenderState* CObjectBillboard::GetRenderState()
{
	// �C���X�^���X���g�p
	assert(m_pRenderState != nullptr);

	// �����_�[�X�e�[�g�̏���Ԃ�
	return m_pRenderState;
}

//============================================================
//	�e�N�X�`���������� (�C���f�b�N�X)
//============================================================
void CObjectBillboard::BindTexture(const int nTextureIdx)
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
void CObjectBillboard::BindTexture(const char* pTexturePath)
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
void CObjectBillboard::SetAlpha(const float fAlpha)
{
	// �����̓����x����
	m_col.a = fAlpha;

	// �F�̐ݒ�
	SetColor(m_col);
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CObjectBillboard::SetColor(const COLOR& rCol)
{
	// �����̐F����
	m_col = rCol;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	���_�̐ݒ菈��
//============================================================
void CObjectBillboard::SetOrigin(const EOrigin origin)
{
	// �����̌��_��ݒ�
	m_origin = origin;

	switch (m_origin)
	{ // ���_���Ƃ̏���
	case ORIGIN_CENTER:	// ����

		// �Ίp���̊p�x�����߂�
		m_fAngle = atan2f(m_size.x, m_size.y);

		// �Ίp���̒��������߂�
		m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;

		break;

	case ORIGIN_DOWN:	// ��

		// �Ίp���̊p�x�����߂�
		m_fAngle = atan2f(m_size.x, m_size.y);

		// �Ίp���̒��������߂�
		m_fLength = sqrtf(m_size.x * m_size.x + (m_size.y * 2.0f) * (m_size.y * 2.0f)) * 0.5f;

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	��]�̐ݒ菈��
//============================================================
void CObjectBillboard::SetRotate(const ERotate rotate)
{
	// �����̉�]��ݒ�
	m_rotate = rotate;
}

//============================================================
//	�`��}�g���b�N�X�̌v�Z����
//============================================================
void CObjectBillboard::CalcDrawMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^
	MATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &m_mtxWorld);

	// �r���[�}�g���b�N�X���t�s��ɕϊ�
	m_mtxWorld.Inverse();	// �|���S�����J�����ɑ΂��Đ��ʂɌ�����

	// �}�g���b�N�X�̃��[���h���W�����_�ɂ���
	m_mtxWorld._41 = m_mtxWorld._42 = m_mtxWorld._43 = 0.0f;

	switch (m_rotate)
	{ // ��]���Ƃ̏���
	case ROTATE_NORMAL:		// �ʏ��]
		break;

	case ROTATE_LATERAL:	// ����]
		m_mtxWorld._21 = m_mtxWorld._23 = m_mtxWorld._24 = 0.0f;
		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// �ʒu�𔽉f
	mtxTrans.Translation(m_pos);
	m_mtxWorld.Multiply(m_mtxWorld, mtxTrans);
}

//============================================================
//	���_���̐ݒ菈��
//============================================================
void CObjectBillboard::SetVtx()
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (m_origin)
	{ // ���_���Ƃ̏���
	case ORIGIN_CENTER:	// ����

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = 0.0f + sinf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
		pVtx[0].pos.y = 0.0f - cosf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.y = 0.0f - cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f + sinf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.y = 0.0f - cosf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f + sinf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.y = 0.0f - cosf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.z = 0.0f;

		break;

	case ORIGIN_DOWN:	// ��

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = 0.0f + sinf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
		pVtx[0].pos.y = 0.0f - cosf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.y = 0.0f - cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f + sinf(m_rot.z - (D3DX_PI * 0.5f)) * m_size.x;
		pVtx[2].pos.y = 0.0f - cosf(m_rot.z - (D3DX_PI * 0.5f)) * m_size.x;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f + sinf(m_rot.z + (D3DX_PI * 0.5f)) * m_size.x;
		pVtx[3].pos.y = 0.0f - cosf(m_rot.z + (D3DX_PI * 0.5f)) * m_size.x;
		pVtx[3].pos.z = 0.0f;

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = VEC3_ZERO;
	pVtx[1].nor = VEC3_ZERO;
	pVtx[2].nor = VEC3_ZERO;
	pVtx[3].nor = VEC3_ZERO;

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
//	�ʏ�`�揈��
//============================================================
void CObjectBillboard::DrawNormal()
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
void CObjectBillboard::DrawShader(CShader* pShader)
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
