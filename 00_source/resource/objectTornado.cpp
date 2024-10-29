//============================================================
//
//	�I�u�W�F�N�g�������� [objectTornado.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectTornado.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int MAX_OFFSET = 2;	// �I�t�Z�b�g�̐�
}

//************************************************************
//	�q�N���X [CObjectTornado] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectTornado::CObjectTornado() : CObject(CObject::LABEL_NONE, CObject::DIM_3D, CObject::DEFAULT_PRIO),
	m_pVtxBuff		(nullptr),			// ���_�o�b�t�@
	m_pRenderState	(nullptr),			// �����_�[�X�e�[�g�̏��
	m_pMtxParent	(nullptr),			// �e�̃}�g���b�N�X
	m_mtxWorld		(MTX_IDENT),		// ���[���h�}�g���b�N�X
	m_pos			(VEC3_ZERO),		// �ʒu
	m_rot			(VEC3_ZERO),		// ����
	m_growRot		(VEC3_ZERO),		// ��������
	m_col			(color::White()),	// �F
	m_fMoveRot		(0.0f),				// �����̕ύX��
	m_fThickness	(0.0f),				// �|���S���̑���
	m_fOuterPlusY	(0.0f),				// �|���S���O����Y���W���Z��
	m_fSetWidth		(0.0f),				// �������̉������
	m_fSetAlpha		(0.0f),				// �������̓����x
	m_fAddWidth		(0.0f),				// ������̉��Z��
	m_fAddHeight	(0.0f),				// �c����̉��Z��
	m_fSubAlpha		(0.0f),				// �����x�̌��Z��
	m_fGrowWidth	(0.0f),				// ������̐�����
	m_fGrowHeight	(0.0f),				// �c����̐�����
	m_fGrowAlpha	(0.0f),				// �����x�̐�����
	m_nNumVtx		(0),				// �K�v���_��
	m_nNumAround	(0),				// �Q�̎���
	m_nPattern		(0),				// �Q�̕�����
	m_nTextureIdx	(0)					// �e�N�X�`���C���f�b�N�X
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectTornado::~CObjectTornado()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectTornado::Init()
{
	// �����o�ϐ���������
	m_pVtxBuff		= nullptr;			// ���_�o�b�t�@
	m_pRenderState	= nullptr;			// �����_�[�X�e�[�g�̏��
	m_pMtxParent	= nullptr;			// �e�̃}�g���b�N�X
	m_mtxWorld		= MTX_IDENT;		// ���[���h�}�g���b�N�X
	m_pos			= VEC3_ZERO;		// �ʒu
	m_rot			= VEC3_ZERO;		// ����
	m_growRot		= VEC3_ZERO;		// ��������
	m_col			= color::White();	// �F
	m_fMoveRot		= 0.0f;				// �����̕ύX��
	m_fThickness	= 0.0f;				// �|���S���̑���
	m_fOuterPlusY	= 0.0f;				// �|���S���O����Y���W���Z��
	m_fSetWidth		= 0.0f;				// �������̉������
	m_fSetAlpha		= 0.0f;				// �������̓����x
	m_fAddWidth		= 0.0f;				// ������̉��Z��
	m_fAddHeight	= 0.0f;				// �c����̉��Z��
	m_fSubAlpha		= 0.0f;				// �����x�̌��Z��
	m_fGrowWidth	= 0.0f;				// ������̐�����
	m_fGrowHeight	= 0.0f;				// �c����̐�����
	m_fGrowAlpha	= 0.0f;				// �����x�̐�����
	m_nNumVtx		= 0;				// �K�v���_��
	m_nNumAround	= 0;				// �Q�̎���
	m_nPattern		= 0;				// �Q�̕�����
	m_nTextureIdx	= NONE_IDX;			// �e�N�X�`���C���f�b�N�X

	// �Q��ݒ�
	if (FAILED(SetVortex(1, 1)))
	{ // �Q�̐ݒ�Ɏ��s�����ꍇ

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

	// �����_�[�X�e�[�g�̏����擾
	CRenderState* pRenderState = GetRenderState();

	// ���e�X�g�̐ݒ�
	pRenderState->SetAlphaTest(true);			// ���e�X�g�̗L�� / �����̐ݒ�
	pRenderState->SetAlphaFunc(D3DCMP_GREATER);	// ���e�X�g�̐ݒ�

	// �|���S���̗��ʂ�\����Ԃɂ���
	pRenderState->SetCulling(D3DCULL_NONE);

	// ���C�e�B���O��OFF�ɂ���
	pRenderState->SetLighting(false);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectTornado::Uninit()
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);

	// �����_�[�X�e�[�g�̔j��
	SAFE_REF_RELEASE(m_pRenderState);

	// �I�u�W�F�N�g������j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CObjectTornado::Update(const float fDeltaTime)
{
	// �����̌�����ύX
	m_rot.y -= m_fMoveRot;

	// �����𐳋K��
	useful::NormalizeRot(m_rot.y);

	// �����𐬒�������
	m_fSetWidth  += m_fGrowWidth * m_nNumVtx;	// ���_����̉�����ʂ����Z
	m_fAddWidth  += m_fGrowWidth;	// �����̉��̍L��������Z
	m_fAddHeight += m_fGrowHeight;	// �����̏c�̍L��������Z
	m_fSetAlpha  -= m_fGrowAlpha;	// �����̓����x�����Z (�����ɂ��Ă���)

	// ���_���̐ݒ�
	SetVtx();

	if (m_fSetAlpha <= 0.0f)
	{ // �����������ɂȂ����ꍇ

		// �����I�u�W�F�N�g�̏I��
		Uninit();

		// �����𔲂���
		return;
	}
}

//============================================================
//	�`�揈��
//============================================================
void CObjectTornado::Draw(CShader* pShader)
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
//	�ʒu�̐ݒ菈��
//============================================================
void CObjectTornado::SetVec3Position(const VECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;
}

//============================================================
//	��������
//============================================================
CObjectTornado* CObjectTornado::Create
(
	const VECTOR3& rPos,		// �ʒu
	const VECTOR3& rGrowRot,	// ��������
	const COLOR& rCol,			// �F
	MATRIX*		pMtxParent,		// �e�̃}�g���b�N�X
	const int	nNumAround,		// �Q�̎���
	const int	nPattern,		// �Q�̕�����
	const float	fMoveRot,		// �����̕ύX��
	const float	fThickness,		// �|���S���̑���
	const float	fOuterPlusY,	// �|���S���O����Y���W���Z��
	const float	fSetWidth,		// �������̉������
	const float	fSetAlpha,		// �������̓����x
	const float	fAddWidth,		// ������̉��Z��
	const float	fAddHeight,		// �c����̉��Z��
	const float	fSubAlpha,		// �����x�̌��Z��
	const float	fGrowWidth,		// ������̐�����
	const float	fGrowHeight,	// �c����̐�����
	const float	fGrowAlpha		// �����x�̐�����
)
{
	// �I�u�W�F�N�g�����̐���
	CObjectTornado* pTornado = new CObjectTornado;
	if (pTornado == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g�����̏�����
		if (FAILED(pTornado->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g�����̔j��
			SAFE_DELETE(pTornado);
			return nullptr;
		}

		// �ʒu��ݒ�
		pTornado->SetVec3Position(rPos);

		// ������ݒ�
		pTornado->SetRotationGrow(rGrowRot);

		// �F��ݒ�
		pTornado->SetColor(rCol);

		// �e�̃}�g���b�N�X��ݒ�
		pTornado->SetMatrixParent(pMtxParent);

		// �|���S���̑�����ݒ�
		pTornado->SetThickness(fThickness);

		// �|���S���O����Y���W���Z�ʂ�ݒ�
		pTornado->SetOuterPlusY(fOuterPlusY);

		// �������̉�����ʂ�ݒ�
		pTornado->SetCreateWidth(fSetWidth);

		// �������̓����x��ݒ�
		pTornado->SetCreateAlpha(fSetAlpha);

		// ������̉��Z�ʂ�ݒ�
		pTornado->SetAddWidth(fAddWidth);

		// �c����̉��Z�ʂ�ݒ�
		pTornado->SetAddHeight(fAddHeight);

		// �����x�̌��Z�ʂ�ݒ�
		pTornado->SetSubAlpha(fSubAlpha);

		// ��������ݒ�
		pTornado->SetGrow(fMoveRot, fGrowWidth, fGrowHeight, fGrowAlpha);

		// �Q��ݒ�
		if (FAILED(pTornado->SetVortex(nNumAround, nPattern)))
		{ // �Q�̐ݒ�Ɏ��s�����ꍇ

			// �I�u�W�F�N�g�����̔j��
			SAFE_DELETE(pTornado);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pTornado;
	}
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectTornado::SetGrow
(
	const float fMoveRot,		// �����̕ύX��
	const float fGrowWidth,		// ������̐�����
	const float fGrowHeight,	// �c����̐�����
	const float fGrowAlpha		// �����x�̐�����
)
{
	// �����̏���ݒ�
	m_fMoveRot		= fMoveRot;		// �����̕ύX��
	m_fGrowWidth	= fGrowWidth;	// ������̐�����
	m_fGrowHeight	= fGrowHeight;	// �c����̐�����
	m_fGrowAlpha	= fGrowAlpha;	// �����x�̐�����
}

//============================================================
//	�Q�̐ݒ菈��
//============================================================
HRESULT CObjectTornado::SetVortex(const int nNumAround, const int nPattern)
{
	// �����̉Q��ݒ�
	m_nNumAround = nNumAround;
	m_nPattern = nPattern;

	// �K�v���_�������߂�
	m_nNumVtx = m_nNumAround * m_nPattern * MAX_OFFSET;

	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);
	assert(m_pVtxBuff == nullptr);

	// ���_�o�b�t�@�̐���
	if (FAILED(GET_DEVICE->CreateVertexBuffer
	( // ����
		sizeof(VERTEX_3D) * m_nNumVtx,	// �K�v���_��
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

	// ���_���̐ݒ�
	SetVtx();

	return S_OK;
}

//============================================================
//	�����_�[�X�e�[�g���̎擾����
//============================================================
CRenderState* CObjectTornado::GetRenderState()
{
	// �C���X�^���X���g�p
	assert(m_pRenderState != nullptr);

	// �����_�[�X�e�[�g�̏���Ԃ�
	return m_pRenderState;
}

//============================================================
//	�e�N�X�`���������� (�C���f�b�N�X)
//============================================================
void CObjectTornado::BindTexture(const int nTextureIdx)
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
void CObjectTornado::BindTexture(const char* pTexturePath)
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
//	�e�}�g���b�N�X�폜����
//============================================================
void CObjectTornado::DeleteMatrixParent()
{
	// �e�}�g���b�N�X��nullptr�ɂ���
	m_pMtxParent = nullptr;
}

//============================================================
//	�e�̃}�g���b�N�X�̐ݒ菈��
//============================================================
void CObjectTornado::SetMatrixParent(MATRIX* pMtxParent)
{
	// �����̐e�}�g���b�N�X��ݒ�
	m_pMtxParent = pMtxParent;
}

//============================================================
//	�����x�̐ݒ菈��
//============================================================
void CObjectTornado::SetAlpha(const float fAlpha)
{
	// �����̓����x��ݒ�
	m_col.a = fAlpha;

	// �F�̐ݒ�
	SetColor(m_col);
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CObjectTornado::SetColor(const COLOR& rCol)
{
	// �����̐F��ݒ�
	m_col = rCol;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	���������̐ݒ菈��
//============================================================
void CObjectTornado::SetRotationGrow(const VECTOR3& rRot)
{
	// �����̐���������ݒ�
	m_growRot = rRot;

	// ���������̐��K��
	useful::NormalizeRot(m_growRot);
}

//============================================================
//	�|���S���̑����̐ݒ菈��
//============================================================
void CObjectTornado::SetThickness(const float fThickness)
{
	// �����̃|���S���̑�����ݒ�
	m_fThickness = fThickness;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�|���S���O����Y���W���Z�ʂ̐ݒ菈��
//============================================================
void CObjectTornado::SetOuterPlusY(const float fOuterPlusY)
{
	// �����̃|���S���O����Y���W���Z�ʂ�ݒ�
	m_fOuterPlusY = fOuterPlusY;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�������̉�����ʂ̐ݒ菈��
//============================================================
void CObjectTornado::SetCreateWidth(const float fSetWidth)
{
	// �����̐������̉�����ʂ�ݒ�
	m_fSetWidth = fSetWidth;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�������̓����x�̐ݒ菈��
//============================================================
void CObjectTornado::SetCreateAlpha(const float fSetAlpha)
{
	// �����̐������̓����x��ݒ�
	m_fSetAlpha = fSetAlpha;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	������̉��Z�ʂ̐ݒ菈��
//============================================================
void CObjectTornado::SetAddWidth(const float fAddWidth)
{
	// �����̉�����̉��Z�ʂ�ݒ�
	m_fAddWidth = fAddWidth;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�c����̉��Z�ʂ̐ݒ菈��
//============================================================
void CObjectTornado::SetAddHeight(const float fAddHeight)
{
	// �����̏c����̉��Z�ʂ�ݒ�
	m_fAddHeight = fAddHeight;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�����x�̌��Z�ʂ̐ݒ菈��
//============================================================
void CObjectTornado::SetSubAlpha(const float fSubAlpha)
{
	// �����̓����x�̌��Z�ʂ�ݒ�
	m_fSubAlpha = fSubAlpha;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�`��}�g���b�N�X�̌v�Z����
//============================================================
void CObjectTornado::CalcDrawMatrix()
{
	MATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	MATRIX mtxOrigin;			// �������̃}�g���b�N�X

	//--------------------------------------------------------
	//	�������̃}�g���b�N�X�����߂�
	//--------------------------------------------------------
	// �������̃}�g���b�N�X�̏�����
	mtxOrigin.Identity();

	// �����𔽉f
	mtxRot.Rotation(m_growRot);
	mtxOrigin.Multiply(mtxOrigin, mtxRot);	// ��������

	// �ʒu�𔽉f
	mtxTrans.Translation(m_pos);
	mtxOrigin.Multiply(mtxOrigin, mtxTrans);	// �����ʒu

	//--------------------------------------------------------
	//	���[���h�}�g���b�N�X�����߂�
	//--------------------------------------------------------
	// ���[���h�}�g���b�N�X�̏�����
	m_mtxWorld.Identity();

	// �����𔽉f
	mtxRot.Rotation(m_rot);
	m_mtxWorld.Multiply(m_mtxWorld, mtxRot);	// ��]��

	//--------------------------------------------------------
	//	�}�g���b�N�X���|�����킹��
	//--------------------------------------------------------
	if (m_pMtxParent != nullptr)
	{ // �e�̃}�g���b�N�X�����݂���ꍇ

		// �e�̃}�g���b�N�X�Ɗ|�����킹��
		mtxOrigin.Multiply(mtxOrigin, *m_pMtxParent);
	}

	// �������̃}�g���b�N�X�Ɗ|�����킹��
	m_mtxWorld.Multiply(m_mtxWorld, mtxOrigin);
}

//============================================================
//	���_���̐ݒ菈��
//============================================================
void CObjectTornado::SetVtx()
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	VECTOR3 vecPos;		// �����̒��_�����x�N�g��
	float fWidth  = m_fSetWidth;	// ���_�����̉������
	float fHeight = 0.0f;			// ���_�����̏c�����
	float fAlpha  = m_fSetAlpha;	// ���_�J���[�̓����x
	if (m_pVtxBuff != nullptr)
	{ // �����̒��_�o�b�t�@���g�p���̏ꍇ

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntWidth = 0; nCntWidth < m_nNumAround; nCntWidth++)
		{ // �Q�̎���̑������J��Ԃ�

			for (int nCntHeight = 0; nCntHeight < m_nPattern; nCntHeight++)
			{ // �Q�̕��������J��Ԃ�

				// ���_�����x�N�g�������߂�
				vecPos.x = sinf(nCntHeight * ((D3DX_PI * 2.0f) / m_nPattern));
				vecPos.y = 1.0f;
				vecPos.z = cosf(nCntHeight * ((D3DX_PI * 2.0f) / m_nPattern));

				for (int nCntSet = 0; nCntSet < MAX_OFFSET; nCntSet++)
				{ // �I�t�Z�b�g�̑������J��Ԃ�

					// ���_���W�̐ݒ�
					pVtx[0].pos.x = 0.0f + vecPos.x * (fWidth + (nCntSet * m_fThickness));		// x
					pVtx[0].pos.y = 0.0f + vecPos.y * (fHeight + (nCntSet * m_fOuterPlusY));	// y
					pVtx[0].pos.z = 0.0f + vecPos.z * (fWidth + (nCntSet * m_fThickness));		// z

					// �@���x�N�g���̐ݒ�
					pVtx[0].nor = VEC3_ZERO;

					if (fAlpha < 0.0f)
					{ // �����x���͈͊O�̏ꍇ

						// �����x��␳
						fAlpha = 0.0f;
					}

					// ���_�J���[�̐ݒ�
					pVtx[0].col = COLOR(m_col.r, m_col.g, m_col.b, fAlpha);

					// �e�N�X�`�����W�̐ݒ�
					pVtx[0].tex = VECTOR2
					( // ����
						1.0f,			// u
						1.0f * nCntSet	// v
					);

					// ���_�f�[�^�̃|�C���^��i�߂�
					pVtx += 1;
				}

				// �c�����L����
				fWidth  += m_fAddWidth;
				fHeight += m_fAddHeight;

				// ���l�����Z
				fAlpha -= m_fSubAlpha;
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	�ʏ�`�揈��
//============================================================
void CObjectTornado::DrawNormal()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_nTextureIdx));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumVtx - 2);
}

//============================================================
//	�V�F�[�_�[�`�揈��
//============================================================
void CObjectTornado::DrawShader(CShader* pShader)
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
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumVtx - 2);

	// �`��I��
	pShader->EndPass();
	pShader->End();
}
