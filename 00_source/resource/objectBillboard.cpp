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
	m_pos			(VEC3_ZERO),		// �ʒu
	m_rot			(VEC3_ZERO),		// ����
	m_size			(VEC3_ZERO),		// �傫��
	m_col			(XCOL_WHITE),		// �F
	m_origin		(ORIGIN_CENTER),	// ���_
	m_rotate		(ROTATE_NORMAL),	// ��]
	m_fAngle		(0.0f),				// �Ίp���̊p�x
	m_fLength		(0.0f),				// �Ίp���̒���
	m_nTextureID	(0)					// �e�N�X�`���C���f�b�N�X
{
	// �����o�ϐ����N���A
	D3DXMatrixIdentity(&m_mtxWorld);	// ���[���h�}�g���b�N�X
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
HRESULT CObjectBillboard::Init(void)
{
	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �����o�ϐ���������
	D3DXMatrixIdentity(&m_mtxWorld);	// ���[���h�}�g���b�N�X
	m_pVtxBuff		= nullptr;			// ���_�o�b�t�@�ւ̃|�C���^
	m_pRenderState	= nullptr;			// �����_�[�X�e�[�g�̏��
	m_pos			= VEC3_ZERO;		// �ʒu
	m_rot			= VEC3_ZERO;		// ����
	m_size			= VEC3_ZERO;		// �傫��
	m_col			= XCOL_WHITE;		// �F
	m_origin		= ORIGIN_CENTER;	// ���_
	m_rotate		= ROTATE_NORMAL;	// ��]
	m_fAngle		= 0.0f;				// �Ίp���̊p�x
	m_fLength		= 0.0f;				// �Ίp���̒���
	m_nTextureID	= NONE_IDX;			// �e�N�X�`���C���f�b�N�X

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	( // ����
		sizeof(VERTEX_3D) * MAX_VERTEX,	// �K�v���_��
		D3DUSAGE_WRITEONLY,				// �g�p���@
		object::FVF_VERTEX_3D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// �������̎w��
		&m_pVtxBuff,					// ���_�o�b�t�@�ւ̃|�C���^
		nullptr
	)))
	{ // ���_�o�b�t�@�̐����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �����_�[�X�e�[�g�̐���
	m_pRenderState = CRenderState::Create();
	if (m_pRenderState == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���C�e�B���O��OFF�ɂ���
	m_pRenderState->SetLighting(false);

	// ���_���̐ݒ�
	SetVtx();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectBillboard::Uninit(void)
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
void CObjectBillboard::Draw(CShader *pShader)
{
	// �ϐ���錾
	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;		// �r���[�}�g���b�N�X

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �����_�[�X�e�[�g��ݒ�
	m_pRenderState->Set();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, nullptr, &mtxView);	// �t�s������߂�

	// �}�g���b�N�X�̃��[���h���W�����_�ɂ���
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	switch (m_rotate)
	{ // ��]���Ƃ̏���
	case ROTATE_NORMAL:		// �ʏ��]

		// ����

		break;

	case ROTATE_LATERAL:	// ����]

		m_mtxWorld._21 = 0.0f;
		m_mtxWorld._23 = 0.0f;
		m_mtxWorld._24 = 0.0f;

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(object::FVF_VERTEX_3D);

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
CObjectBillboard *CObjectBillboard::Create
(
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rSize,	// �傫��
	const D3DXVECTOR3& rRot,	// ����
	const D3DXCOLOR& rCol,		// �F
	const EOrigin origin,		// ���_
	const ERotate rotate		// ��]
)
{
	// �I�u�W�F�N�g�r���{�[�h�̐���
	CObjectBillboard *pBillboard = new CObjectBillboard;
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
		pBillboard->SetVec3Sizing(rSize);

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
void CObjectBillboard::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectBillboard::SetVec3Rotation(const D3DXVECTOR3& rRot)
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
void CObjectBillboard::SetVec3Sizing(const D3DXVECTOR3& rSize)
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
CRenderState *CObjectBillboard::GetRenderState(void)
{
	// �C���X�^���X���g�p
	assert(m_pRenderState != nullptr);

	// �����_�[�X�e�[�g�̏���Ԃ�
	return m_pRenderState;
}

//============================================================
//	�e�N�X�`���������� (�C���f�b�N�X)
//============================================================
void CObjectBillboard::BindTexture(const int nTextureID)
{
	if (nTextureID >= NONE_IDX)
	{ // �e�N�X�`���C���f�b�N�X���g�p�\�ȏꍇ

		// �e�N�X�`���C���f�b�N�X����
		m_nTextureID = nTextureID;
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	�e�N�X�`���������� (�p�X)
//============================================================
void CObjectBillboard::BindTexture(const char *pTexturePass)
{
	// �|�C���^��錾
	CTexture *pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	if (pTexturePass != nullptr)
	{ // ���蓖�Ă�e�N�X�`���p�X������ꍇ

		// �e�N�X�`���C���f�b�N�X��ݒ�
		m_nTextureID = pTexture->Regist(pTexturePass);
	}
	else
	{ // ���蓖�Ă�e�N�X�`���p�X���Ȃ��ꍇ

		// �e�N�X�`���Ȃ��C���f�b�N�X��ݒ�
		m_nTextureID = NONE_IDX;
	}
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CObjectBillboard::SetColor(const D3DXCOLOR& rCol)
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
//	���_���̐ݒ菈��
//============================================================
void CObjectBillboard::SetVtx(void)
{
	// �|�C���^��錾
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================================
//	�ʏ�`�揈��
//============================================================
void CObjectBillboard::DrawNormal(void)
{
	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_nTextureID));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//============================================================
//	�V�F�[�_�[�`�揈��
//============================================================
void CObjectBillboard::DrawShader(CShader *pShader)
{
	// �|�C���^��錾
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
	pShader->SetTexture(m_nTextureID);

	// ��ԕύX�̓`�B
	pShader->CommitChanges();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_nTextureID));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �`��I��
	pShader->EndPass();
	pShader->End();
}