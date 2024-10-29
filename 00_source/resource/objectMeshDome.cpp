//============================================================
//
//	�I�u�W�F�N�g���b�V���h�[������ [objectMeshDome.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectMeshDome.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const float CALC_TEXDIR[]	= { -1.0f, 1.0f };	// �e�N�X�`�������̌v�Z�W��
	const POSGRID2 MIN_PART		= POSGRID2(1, 2);	// �������̍ŏ��l
	const POSGRID2 MIN_TEXPART	= GRID2_ONE;		// �e�N�X�`���������̍ŏ��l
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(CALC_TEXDIR) == CObjectMeshDome::TEXDIR_MAX, "ERROR : Array Count Mismatch");

//************************************************************
//	�q�N���X [CObjectMeshDome] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectMeshDome::CObjectMeshDome(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObject(label, dimension, nPriority),
	m_pVtxBuff		(nullptr),			// ���_�o�b�t�@
	m_pIdxBuff		(nullptr),			// �C���f�b�N�X�o�b�t�@
	m_pRenderState	(nullptr),			// �����_�[�X�e�[�g�̏��
	m_mtxWorld		(MTX_IDENT),		// ���[���h�}�g���b�N�X
	m_pos			(VEC3_ZERO),		// �ʒu
	m_rot			(VEC3_ZERO),		// ����
	m_col			(color::White()),	// �F
	m_part			(GRID2_ZERO),		// ������
	m_texPart		(GRID2_ZERO),		// �e�N�X�`��������
	m_texDir		(TEXDIR_OUTSIDE),	// �e�N�X�`������
	m_fRadius		(0.0f),				// ���a
	m_nNumVtx		(0),				// �K�v���_��
	m_nNumIdx		(0),				// �K�v�C���f�b�N�X��
	m_nTextureIdx	(0)					// �e�N�X�`���C���f�b�N�X
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectMeshDome::~CObjectMeshDome()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectMeshDome::Init()
{
	// �����o�ϐ���������
	m_pVtxBuff		= nullptr;			// ���_�o�b�t�@
	m_pIdxBuff		= nullptr;			// �C���f�b�N�X�o�b�t�@
	m_pRenderState	= nullptr;			// �����_�[�X�e�[�g�̏��
	m_mtxWorld		= MTX_IDENT;		// ���[���h�}�g���b�N�X
	m_pos			= VEC3_ZERO;		// �ʒu
	m_rot			= VEC3_ZERO;		// ����
	m_col			= color::White();	// �F
	m_part			= MIN_PART;			// ������
	m_texPart		= GRID2_ONE;		// �e�N�X�`��������
	m_texDir		= TEXDIR_OUTSIDE;	// �e�N�X�`������
	m_fRadius		= 0.0f;				// ���a
	m_nNumVtx		= 0;				// �K�v���_��
	m_nNumIdx		= 0;				// �K�v�C���f�b�N�X��
	m_nTextureIdx	= NONE_IDX;			// �e�N�X�`���C���f�b�N�X

	// ��������ݒ�
	if (FAILED(SetPattern(MIN_PART)))
	{ // �������̐ݒ�Ɏ��s�����ꍇ

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

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectMeshDome::Uninit()
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);

	// �C���f�b�N�X�o�b�t�@�̔j��
	SAFE_RELEASE(m_pIdxBuff);

	// �����_�[�X�e�[�g�̔j��
	SAFE_REF_RELEASE(m_pRenderState);

	// �I�u�W�F�N�g���b�V���h�[����j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CObjectMeshDome::Update(const float fDeltaTime)
{

}

//============================================================
//	�`�揈��
//============================================================
void CObjectMeshDome::Draw(CShader* pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^
	MATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �����_�[�X�e�[�g��ݒ�
	m_pRenderState->Set();

	// �`��}�g���b�N�X�̌v�Z
	CalcDrawMatrix();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

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
void CObjectMeshDome::SetVec3Position(const VECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectMeshDome::SetVec3Rotation(const VECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_rot = rRot;

	// �����̐��K��
	useful::NormalizeRot(m_rot);
}

//============================================================
//	��������
//============================================================
CObjectMeshDome* CObjectMeshDome::Create
(
	const VECTOR3& rPos,		// �ʒu
	const VECTOR3& rRot,		// ����
	const COLOR& rCol,			// �F
	const POSGRID2& rPart,		// ������
	const POSGRID2& rTexPart,	// �e�N�X�`��������
	const float fRadius			// ���a
)
{
	// �I�u�W�F�N�g���b�V���h�[���̐���
	CObjectMeshDome* pMeshDome = new CObjectMeshDome;
	if (pMeshDome == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g���b�V���h�[���̏�����
		if (FAILED(pMeshDome->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g���b�V���h�[���̔j��
			SAFE_DELETE(pMeshDome);
			return nullptr;
		}

		// �ʒu��ݒ�
		pMeshDome->SetVec3Position(rPos);

		// ������ݒ�
		pMeshDome->SetVec3Rotation(rRot);

		// �F��ݒ�
		pMeshDome->SetColor(rCol);

		// ���a��ݒ�
		pMeshDome->SetRadius(fRadius);

		// ��������ݒ�
		if (FAILED(pMeshDome->SetPattern(rPart)))
		{ // �������̐ݒ�Ɏ��s�����ꍇ

			// �I�u�W�F�N�g���b�V���h�[���̔j��
			SAFE_DELETE(pMeshDome);
			return nullptr;
		}

		// �e�N�X�`����������ݒ�
		pMeshDome->SetTexPattern(rTexPart);

		// �m�ۂ����A�h���X��Ԃ�
		return pMeshDome;
	}
}

//============================================================
//	�����_�[�X�e�[�g���̎擾����
//============================================================
CRenderState* CObjectMeshDome::GetRenderState()
{
	// �C���X�^���X���g�p
	assert(m_pRenderState != nullptr);

	// �����_�[�X�e�[�g�̏���Ԃ�
	return m_pRenderState;
}

//============================================================
//	�e�N�X�`���������� (�C���f�b�N�X)
//============================================================
void CObjectMeshDome::BindTexture(const int nTextureIdx)
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
void CObjectMeshDome::BindTexture(const char* pTexturePath)
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
void CObjectMeshDome::SetAlpha(const float fAlpha)
{
	// �����̓����x��ݒ�
	m_col.a = fAlpha;

	// �F�̐ݒ�
	SetColor(m_col);
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CObjectMeshDome::SetColor(const COLOR& rCol)
{
	// �����̐F��ݒ�
	m_col = rCol;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	���a�̐ݒ菈��
//============================================================
void CObjectMeshDome::SetRadius(const float fRadius)
{
	// �����̔��a��ݒ�
	m_fRadius = fRadius;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�e�N�X�`�������̐ݒ菈��
//============================================================
void CObjectMeshDome::SetTexDir(const ETexDir texDir)
{
	// �e�N�X�`��������ݒ�
	m_texDir = texDir;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�������̐ݒ菈��
//============================================================
HRESULT CObjectMeshDome::SetPattern(const POSGRID2& rPart)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �������̐ݒ�s��
	assert(rPart.x >= MIN_PART.x);
	assert(rPart.y >= MIN_PART.y);

	// �����̕�������ݒ�
	m_part = rPart;

	// �K�v���_�E�C���f�b�N�X�������߂�
	m_nNumVtx = ((m_part.x + 1) * (m_part.y + 1)) - m_part.x; // �K�v���_��
	m_nNumIdx = ((m_part.x + 1) * (((m_part.y + 1) * 2) - 2) + (m_part.y * 2) - 2) - (m_part.x + 2); // �K�v�C���f�b�N�X��

	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);
	assert(m_pVtxBuff == nullptr);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
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

	// �C���f�b�N�X�o�b�t�@�̔j��
	SAFE_RELEASE(m_pIdxBuff);
	assert(m_pIdxBuff == nullptr);

	// �C���f�b�N�X�o�b�t�@�̐���
	if (FAILED(pDevice->CreateIndexBuffer
	( // ����
		sizeof(WORD) * m_nNumIdx,	// �K�v�C���f�b�N�X��
		D3DUSAGE_WRITEONLY,	// �g�p���@
		D3DFMT_INDEX16,		// �C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g
		D3DPOOL_MANAGED,	// �������̎w��
		&m_pIdxBuff,		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
		nullptr
	)))
	{ // �C���f�b�N�X�o�b�t�@�̐����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// ���_�E�C���f�b�N�X���̐ݒ�
	SetVtx();
	SetIdx();

	return S_OK;
}

//============================================================
//	�e�N�X�`���������̐ݒ菈��
//============================================================
void CObjectMeshDome::SetTexPattern(const POSGRID2& rTexPart)
{
	if (rTexPart.x >= MIN_TEXPART.x
	&&  rTexPart.y >= MIN_TEXPART.y)
	{ // �e�N�X�`�����������Œ�l�ȏ�̏ꍇ

		// �����̃e�N�X�`����������ݒ�
		m_texPart = rTexPart;

		// ���_���̐ݒ�
		SetVtx();
	}
	else { assert(false); }	// �Œ�l����
}

//============================================================
//	�`��}�g���b�N�X�̌v�Z����
//============================================================
void CObjectMeshDome::CalcDrawMatrix()
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
void CObjectMeshDome::SetVtx()
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	VECTOR3 vecPos;		// ���_�ʒu�̌v�Z�p
	VECTOR3 vecNor;		// �@���x�N�g���̌v�Z�p
	float fRotWidth, fRotHeight;	// ���_�ʒu�̕����̌v�Z�p
	float fRateWidth  = ((float)(m_texPart.x) / (float)(m_part.x));		// �e�N�X�`�����������̊���
	float fRateHeight = ((float)(m_texPart.y) / (float)(m_part.y - 1));	// �e�N�X�`���c�������̊���
	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntHeight = 0; nCntHeight < m_part.y + 1; nCntHeight++)
		{ // �c�̕����� +1��J��Ԃ�

			// �J��Ԃ��������߂�
			int nLoop = (m_part.x * (1 - (nCntHeight / m_part.y))) + 1;

			for (int nCntWidth = 0; nCntWidth < nLoop; nCntWidth++)
			{ // ���̕����� +1��J��Ԃ� (�V�ӂ̒��_���͌J��Ԃ��� 1��ɂ���)

				// ���_�̌������v�Z
				fRotWidth  = nCntWidth  * ((D3DX_PI * 2.0f) / m_part.x);
				fRotHeight = (m_part.y - nCntHeight) * ((D3DX_PI * 0.5f) / m_part.y);

				// ���_���W�̕�����ݒ�
				vecPos = VECTOR3
				( // ����
					m_fRadius * sinf(fRotHeight) * sinf(fRotWidth),	// x
					m_fRadius * cosf(fRotHeight),					// y
					m_fRadius * sinf(fRotHeight) * cosf(fRotWidth)	// z
				);

				// ���_���W�̐ݒ�
				pVtx[0].pos = vecPos;

				// �@���x�N�g���̕�����ݒ�
				vecNor = vecPos;

				// �x�N�g���𐳋K��
				D3DXVec3Normalize(&vecNor, &vecNor);

				// �@���x�N�g���̐ݒ�
				pVtx[0].nor = vecNor;

				// ���_�J���[�̐ݒ�
				pVtx[0].col = m_col;

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = VECTOR2
				( // ����
					fRateWidth  * (nCntWidth  - m_part.x) * CALC_TEXDIR[m_texDir],	// u
					fRateHeight * (nCntHeight - m_part.y + 1) * -1.0f				// v
				);

				// ���_�f�[�^�̃|�C���^�� 1���i�߂�
				pVtx += 1;
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//============================================================
//	�C���f�b�N�X���̐ݒ菈��
//============================================================
void CObjectMeshDome::SetIdx()
{
	WORD* pIdx;	// �C���f�b�N�X���ւ̃|�C���^
	if (m_pIdxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// �C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
		m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCntHeight = 0, nCntWidth = 0; nCntHeight < m_part.y - 1; nCntHeight++)
		{ // �c�̕����� +1��J��Ԃ�

			for (nCntWidth = 0; nCntWidth < m_part.x + 1; nCntWidth++)
			{ // ���̕����� +1��J��Ԃ�

				pIdx[0] = (WORD)((m_part.x + 1) * (nCntHeight + 1) + nCntWidth);
				pIdx[1] = (WORD)((m_part.x + 1) * nCntHeight + nCntWidth);

				// �C���f�b�N�X�f�[�^�̃|�C���^�� 2���i�߂�
				pIdx += 2;
			}

			if (nCntHeight != m_part.y - 2)
			{ // ��Ԏ�O�̕����ꏊ�ł͂Ȃ��ꍇ

				pIdx[0] = (WORD)((m_part.x + 1) * nCntHeight + nCntWidth - 1);
				pIdx[1] = (WORD)((m_part.x + 1) * (nCntHeight + 2));

				// �C���f�b�N�X�f�[�^�̃|�C���^�� 2���i�߂�
				pIdx += 2;
			}
		}

		// �����̓V�ӂ̒��_���w��
		pIdx[0] = (WORD)(m_nNumVtx - 1);

		// �C���f�b�N�X�f�[�^�̃|�C���^�� 1���i�߂�
		pIdx += 1;

		for (int nCntWidth = 0; nCntWidth < m_part.x + 1; nCntWidth++)
		{ // ���̕����� +1��J��Ԃ�

			pIdx[0] = (WORD)(((m_part.x + 1) * (m_part.y - 1)) + nCntWidth);

			// �C���f�b�N�X�f�[�^�̃|�C���^�� 1���i�߂�
			pIdx += 1;
		}

		// �C���f�b�N�X�o�b�t�@���A�����b�N����
		m_pIdxBuff->Unlock();
	}
}

//============================================================
//	�X�N���[���̃e�N�X�`�����W�̐ݒ菈��
//============================================================
void CObjectMeshDome::SetScrollTex(const float fTexU, const float fTexV)
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	float fRateWidth  = ((float)(m_texPart.x) / (float)(m_part.x));		// �e�N�X�`�����������̊���
	float fRateHeight = ((float)(m_texPart.y) / (float)(m_part.y - 1));	// �e�N�X�`���c�������̊���
	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntHeight = 0; nCntHeight < m_part.y + 1; nCntHeight++)
		{ // �c�̕����� +1��J��Ԃ�

			// �J��Ԃ��������߂�
			int nLoop = (m_part.x * (1 - (nCntHeight / m_part.y))) + 1;

			for (int nCntWidth = 0; nCntWidth < nLoop; nCntWidth++)
			{ // ���̕����� +1��J��Ԃ� (�V�ӂ̒��_���͌J��Ԃ��� 1��ɂ���)

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = VECTOR2
				( // ����
					fTexU + fRateWidth  * (nCntWidth  - m_part.x) * CALC_TEXDIR[m_texDir],	// u
					fTexV + fRateHeight * (nCntHeight - m_part.y + 1) * -1.0f				// v
				);

				// ���_�f�[�^�̃|�C���^�� 1���i�߂�
				pVtx += 1;
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//============================================================
//	�ʏ�`�揈��
//============================================================
void CObjectMeshDome::DrawNormal()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	//--------------------------------------------------------
	//	�����|���S���̕`��
	//--------------------------------------------------------
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_nTextureIdx));

	// �����|���S���̕`��
	pDevice->DrawIndexedPrimitive
	( // ����
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,
		0,
		m_nNumVtx - 1,						// �g�p���钸�_��
		0,									// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
		(m_nNumIdx - (m_part.x + 1)) - 3	// �v���~�e�B�u (�|���S��) ��
	);

	//--------------------------------------------------------
	//	��W�|���S���̕`��
	//--------------------------------------------------------
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);

	// ��W�|���S���̕`��
	pDevice->DrawIndexedPrimitive
	( // ����
		D3DPT_TRIANGLEFAN,	// �v���~�e�B�u�̎��
		0,
		0,
		m_part.x + 1,				// �g�p���钸�_��
		m_nNumIdx - (m_part.x + 2),	// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
		m_part.x					// �v���~�e�B�u (�|���S��) ��
	);
}

//============================================================
//	�V�F�[�_�[�`�揈��
//============================================================
void CObjectMeshDome::DrawShader(CShader* pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	//--------------------------------------------------------
	//	�����|���S���̕`��
	//--------------------------------------------------------
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

	// �����|���S���̕`��
	pDevice->DrawIndexedPrimitive
	( // ����
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,
		0,
		m_nNumVtx - 1,						// �g�p���钸�_��
		0,									// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
		(m_nNumIdx - (m_part.x + 1)) - 3	// �v���~�e�B�u (�|���S��) ��
	);

	// �`��I��
	pShader->EndPass();
	pShader->End();

	//--------------------------------------------------------
	//	��W�|���S���̕`��
	//--------------------------------------------------------
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
	pShader->SetTexture(NONE_IDX);

	// ��ԕύX�̓`�B
	pShader->CommitChanges();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);

	// ��W�|���S���̕`��
	pDevice->DrawIndexedPrimitive
	( // ����
		D3DPT_TRIANGLEFAN,	// �v���~�e�B�u�̎��
		0,
		0,
		m_part.x + 1,				// �g�p���钸�_��
		m_nNumIdx - (m_part.x + 2),	// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
		m_part.x					// �v���~�e�B�u (�|���S��) ��
	);

	// �`��I��
	pShader->EndPass();
	pShader->End();
}
