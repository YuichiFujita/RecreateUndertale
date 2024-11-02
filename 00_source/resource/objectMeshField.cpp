//============================================================
//
//	�I�u�W�F�N�g���b�V���t�B�[���h���� [objectMeshField.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectMeshField.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "collision.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int	NUM_VTX_TRIANGLE = 3;		// �O�p�`�|���S���̒��_��
	const float	COLL_RADIUS = 100.0f;		// �����蔻����s������
	const POSGRID2 MIN_PART = GRID2_ONE;	// �������̍ŏ��l
	const POSGRID2 MIN_TEXPART = GRID2_ONE;	// �e�N�X�`���������̍ŏ��l
}

//************************************************************
//	�q�N���X [CObjectMeshField] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectMeshField::CObjectMeshField(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObject(label, dimension, nPriority),
	m_pVtxBuff		(nullptr),			// ���_�o�b�t�@
	m_pIdxBuff		(nullptr),			// �C���f�b�N�X�o�b�t�@
	m_pRenderState	(nullptr),			// �����_�[�X�e�[�g�̏��
	m_pPosGapBuff	(nullptr),			// ���W�̂���o�b�t�@
	m_pNorBuff		(nullptr),			// �@���o�b�t�@
	m_pNumNorBuff	(nullptr),			// �@���̎g�p���o�b�t�@
	m_mtxWorld		(MTX_IDENT),		// ���[���h�}�g���b�N�X
	m_pos			(VEC3_ZERO),		// �ʒu
	m_rot			(VEC3_ZERO),		// ����
	m_size			(VEC2_ZERO),		// �傫��
	m_col			(color::White()),	// �F
	m_part			(GRID2_ZERO),		// ������
	m_texPart		(GRID2_ZERO),		// �e�N�X�`��������
	m_nNumVtx		(0),				// �K�v���_��
	m_nNumIdx		(0),				// �K�v�C���f�b�N�X��
	m_nTextureIdx	(0)					// �e�N�X�`���C���f�b�N�X
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectMeshField::~CObjectMeshField()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectMeshField::Init()
{
	// �����o�ϐ���������
	m_pVtxBuff		= nullptr;			// ���_�o�b�t�@
	m_pIdxBuff		= nullptr;			// �C���f�b�N�X�o�b�t�@
	m_pRenderState	= nullptr;			// �����_�[�X�e�[�g�̏��
	m_pPosGapBuff	= nullptr;			// ���W�̂���o�b�t�@
	m_pNorBuff		= nullptr;			// �@���o�b�t�@
	m_pNumNorBuff	= nullptr;			// �@���̎g�p���o�b�t�@
	m_mtxWorld		= MTX_IDENT;		// ���[���h�}�g���b�N�X
	m_pos			= VEC3_ZERO;		// �ʒu
	m_rot			= VEC3_ZERO;		// ����
	m_size			= VEC2_ZERO;		// �傫��
	m_col			= color::White();	// �F
	m_part			= GRID2_ZERO;		// ������
	m_texPart		= GRID2_ZERO;		// �e�N�X�`��������
	m_nNumVtx		= 0;				// �K�v���_��
	m_nNumIdx		= 0;				// �K�v�C���f�b�N�X��
	m_nTextureIdx	= NONE_IDX;			// �e�N�X�`���C���f�b�N�X

	// ��������ݒ�
	if (FAILED(SetPattern(GRID2_ONE)))
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
void CObjectMeshField::Uninit()
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);

	// �C���f�b�N�X�o�b�t�@�̔j��
	SAFE_RELEASE(m_pIdxBuff);

	// �����_�[�X�e�[�g�̔j��
	SAFE_REF_RELEASE(m_pRenderState);

	// ���W�̂���o�b�t�@�̔j��
	SAFE_DEL_ARRAY(m_pPosGapBuff);

	// �@���o�b�t�@�̔j��
	SAFE_DEL_ARRAY(m_pNorBuff);

	// �@���̎g�p���o�b�t�@�̔j��
	SAFE_DEL_ARRAY(m_pNumNorBuff);

	// �I�u�W�F�N�g���b�V���t�B�[���h��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CObjectMeshField::Update(const float fDeltaTime)
{

}

//============================================================
//	�`�揈��
//============================================================
void CObjectMeshField::Draw(CShader* pShader)
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
void CObjectMeshField::SetVec3Position(const VECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectMeshField::SetVec3Rotation(const VECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_rot = rRot;

	// �����̐��K��
	useful::NormalizeRot(m_rot);
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CObjectMeshField::SetVec2Size(const VECTOR2& rSize)
{
	// �����̑傫����ݒ�
	m_size = rSize;

	// ���_���̐ݒ�
	SetVtx(false);
}

//============================================================
//	��������
//============================================================
CObjectMeshField* CObjectMeshField::Create
(
	const VECTOR3& rPos,		// �ʒu
	const VECTOR3& rRot,		// ����
	const VECTOR2& rSize,		// �傫��
	const COLOR& rCol,			// �F
	const POSGRID2& rPart,		// ������
	const POSGRID2& rTexPart	// �e�N�X�`��������
)
{
	// �I�u�W�F�N�g���b�V���t�B�[���h�̐���
	CObjectMeshField* pMeshField = new CObjectMeshField;
	if (pMeshField == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g���b�V���t�B�[���h�̏�����
		if (FAILED(pMeshField->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g���b�V���t�B�[���h�̔j��
			SAFE_DELETE(pMeshField);
			return nullptr;
		}

		// �ʒu��ݒ�
		pMeshField->SetVec3Position(rPos);

		// ������ݒ�
		pMeshField->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pMeshField->SetVec2Size(rSize);

		// �F��ݒ�
		pMeshField->SetColor(rCol);

		// ��������ݒ�
		if (FAILED(pMeshField->SetPattern(rPart)))
		{ // �������̐ݒ�Ɏ��s�����ꍇ

			// �I�u�W�F�N�g���b�V���t�B�[���h�̔j��
			SAFE_DELETE(pMeshField);
			return nullptr;
		}

		// �e�N�X�`����������ݒ�
		pMeshField->SetTexPattern(rTexPart);

		// �m�ۂ����A�h���X��Ԃ�
		return pMeshField;
	}
}

//============================================================
//	�����_�[�X�e�[�g���̎擾����
//============================================================
CRenderState* CObjectMeshField::GetRenderState()
{
	// �C���X�^���X���g�p
	assert(m_pRenderState != nullptr);

	// �����_�[�X�e�[�g�̏���Ԃ�
	return m_pRenderState;
}

//============================================================
//	�e�N�X�`���������� (�C���f�b�N�X)
//============================================================
void CObjectMeshField::BindTexture(const int nTextureIdx)
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
void CObjectMeshField::BindTexture(const char* pTexturePath)
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
void CObjectMeshField::SetAlpha(const float fAlpha)
{
	// �����̓����x��ݒ�
	m_col.a = fAlpha;

	// �F�̐ݒ�
	SetColor(m_col);
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CObjectMeshField::SetColor(const COLOR& rCol)
{
	// �����̐F��ݒ�
	m_col = rCol;

	// ���_���̐ݒ�
	SetVtx(false);
}

//============================================================
//	�������̐ݒ菈��
//============================================================
HRESULT CObjectMeshField::SetPattern(const POSGRID2& rPart)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^
	int nNorBuff = 0;	// �@���o�b�t�@�̊m�ې�

	//--------------------------------------------------------
	//	�ύX����ݒ�
	//--------------------------------------------------------
	// �������̐ݒ�s��
	assert(rPart.x >= MIN_PART.x);
	assert(rPart.y >= MIN_PART.y);

	// �����̕�������ݒ�
	m_part = rPart;

	// �K�v���_�E�C���f�b�N�X�������߂�
	m_nNumVtx = (m_part.x + 1) * (m_part.y + 1); // �K�v���_��
	m_nNumIdx = (m_part.x + 1) * (((m_part.y + 1) * 2) - 2) + (m_part.y * 2) - 2; // �K�v�C���f�b�N�X��

	// �@���o�b�t�@�̊m�ې������߂�
	nNorBuff  = 6 + (6 * (m_part.x - 1)) + (6 * (m_part.y - 1)) + (6 * ((m_part.x - 1) * (m_part.y - 1)));

	//--------------------------------------------------------
	//	���_�o�b�t�@�̔j���E����
	//--------------------------------------------------------
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

	//--------------------------------------------------------
	//	�C���f�b�N�X�o�b�t�@�̔j���E����
	//--------------------------------------------------------
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

	//--------------------------------------------------------
	//	���W�̂���o�b�t�@�̔j���E����
	//--------------------------------------------------------
	// ���W�̂���o�b�t�@�̔j��
	SAFE_DEL_ARRAY(m_pPosGapBuff);
	assert(m_pPosGapBuff == nullptr);

	// ���W�̂���o�b�t�@�̃������m��
	m_pPosGapBuff = new VECTOR3[m_nNumVtx];
	if (m_pPosGapBuff != nullptr)
	{ // �m�ۂɐ��������ꍇ

		// �������N���A
		memset(m_pPosGapBuff, 0, sizeof(VECTOR3) * m_nNumVtx);
	}
	else
	{ // �m�ۂɎ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	�@���o�b�t�@�̔j���E����
	//--------------------------------------------------------
	// �@���o�b�t�@�̔j��
	SAFE_DEL_ARRAY(m_pNorBuff);
	assert(m_pNorBuff == nullptr);

	// �@���o�b�t�@�̃������m��
	m_pNorBuff = new VECTOR3[nNorBuff];
	if (m_pNorBuff != nullptr)
	{ // �m�ۂɐ��������ꍇ
	
		// �������N���A
		memset(m_pNorBuff, 0, sizeof(VECTOR3) * nNorBuff);
	}
	else
	{ // �m�ۂɎ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	�@���̎g�p���o�b�t�@�̔j���E����
	//--------------------------------------------------------
	// �@���̎g�p���o�b�t�@�̔j��
	SAFE_DEL_ARRAY(m_pNumNorBuff);
	assert(m_pNumNorBuff == nullptr);

	// �@���̎g�p���o�b�t�@�̃������m��
	m_pNumNorBuff = new int[m_nNumVtx];
	if (m_pNumNorBuff != nullptr)
	{ // �m�ۂɐ��������ꍇ

		// �������N���A
		memset(m_pNumNorBuff, 0, sizeof(int) * m_nNumVtx);
	}
	else
	{ // �m�ۂɎ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	�������𔽉f
	//--------------------------------------------------------
	// ���_�E�C���f�b�N�X���̐ݒ�
	SetVtx(true);
	SetIdx();

	return S_OK;
}

//============================================================
//	�e�N�X�`���������̐ݒ菈��
//============================================================
void CObjectMeshField::SetTexPattern(const POSGRID2& rTexPart)
{
	if (rTexPart.x >= MIN_TEXPART.x
	&&  rTexPart.y >= MIN_TEXPART.y)
	{ // �e�N�X�`�����������Œ�l�ȏ�̏ꍇ

		// �����̃e�N�X�`����������ݒ�
		m_texPart = rTexPart;

		// ���_���̐ݒ�
		SetVtx(true);
	}
	else { assert(false); }	// �Œ�l����
}

//============================================================
//	���W�̂���̐ݒ菈��
//============================================================
void CObjectMeshField::SetGapPosition(const int nIdx, const VECTOR3& rPos)
{
	if (m_pPosGapBuff != nullptr)
	{ // �g�p���̏ꍇ

		if (nIdx < (m_part.x + 1) * (m_part.y + 1))
		{ // �C���f�b�N�X���g�p�\�ȏꍇ

			// ���_�̂����ݒ�
			m_pPosGapBuff[nIdx] = rPos;
		}
		else
		{ // �C���f�b�N�X���g�p�s�ȏꍇ

			// ��O����
			assert(false);
		}
	}
}

//============================================================
//	���W�̂���擾����
//============================================================
VECTOR3 CObjectMeshField::GetGapPosition(const int nIdx)
{
	VECTOR3 pos = VEC3_ZERO;	// ���_�̂���̑���p
	if (m_pPosGapBuff != nullptr)
	{ // �g�p���̏ꍇ

		if (nIdx < (m_part.x + 1) * (m_part.y + 1))
		{ // �C���f�b�N�X���g�p�\�ȏꍇ

			// ���_�̂����ݒ�
			pos = m_pPosGapBuff[nIdx];
		}
		else
		{ // �C���f�b�N�X���g�p�s�ȏꍇ

			// ��O����
			assert(false);
		}
	}

	// �����̃C���f�b�N�X�̒��_�̂����Ԃ�
	return pos;
}

//============================================================
//	���b�V���̒��_�ʒu�̐ݒ菈��
//============================================================
void CObjectMeshField::SetMeshVertexPosition(const int nIdx, const VECTOR3& rPos)
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		if (nIdx < (m_part.x + 1) * (m_part.y + 1))
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
}

//============================================================
//	���b�V���̒��_�ʒu�̐ݒ菈��
//============================================================
VECTOR3 CObjectMeshField::GetMeshVertexPosition(const int nIdx)
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	VECTOR3 pos;		// ���_���W�̑���p
	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		if (nIdx < (m_part.x + 1) * (m_part.y + 1))
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
//	���b�V���̒��n����
//============================================================
bool CObjectMeshField::LandPosition(VECTOR3& rPos, VECTOR3& rMove)
{
	float fLandHeight = GetPositionHeight(rPos);	// ���n�ʒu
	if (rPos.y < fLandHeight)
	{ // �ʒu���n�ʂ�艺�̏ꍇ

		// �ʒu��␳
		rPos.y = fLandHeight;

		// �ړ��ʂ�������
		rMove.y = 0.0f;

		// ���n���Ă���󋵂�Ԃ�
		return true;
	}

	// ���n���Ă��Ȃ��󋵂�Ԃ�
	return false;
}

//============================================================
//	�n�`�̐ݒ菈��
//============================================================
void CObjectMeshField::SetTerrain(const POSGRID2& rPart, VECTOR3* pPosGap)
{
	if (rPart != m_part)
	{ // ���������Ⴄ�ꍇ

		// ��������ݒ�
		SetPattern(rPart);
	}

	if (m_pPosGapBuff != nullptr && rPart == m_part)
	{ // ���W�̂���o�b�t�@���g�p�����A�����������̏ꍇ

		for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++, pPosGap++)
		{ // ���_�����J��Ԃ�

			// �����̍��W�̂���ʂ�ݒ�
			m_pPosGapBuff[nCntVtx] = *pPosGap;
		}
	}
	else { assert(false); }	// ��g�p��

	// ���_�E�C���f�b�N�X���̐ݒ�
	SetVtx(true);
	SetIdx();
}

//============================================================
//	���b�V���͈͓̔��擾����
//============================================================
bool CObjectMeshField::IsPositionRange(const VECTOR3&rPos)
{
	D3DXVECTOR3 aVtxPos[4];		// �|���S���̒��_���W
	D3DXVECTOR3 aVtxMtxPos[4];	// �|���S���̈ʒu�E�������f���s�������_���W

	// ���b�V���̒��_�ʒu��ݒ�
	aVtxPos[0] = D3DXVECTOR3(-m_size.x * 0.5f, 0.0f, +m_size.y * 0.5f);	// ����
	aVtxPos[1] = D3DXVECTOR3(-m_size.x * 0.5f, 0.0f, -m_size.y * 0.5f);	// ����
	aVtxPos[2] = D3DXVECTOR3(+m_size.x * 0.5f, 0.0f, -m_size.y * 0.5f);	// �E��
	aVtxPos[3] = D3DXVECTOR3(+m_size.x * 0.5f, 0.0f, +m_size.y * 0.5f);	// �E��

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{ // �O�p�`�|���S���̒��_�����J��Ԃ�

		MATRIX mtxWorld, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld.Identity();

		// ���_�ʒu�𔽉f
		mtxTrans.Translation(aVtxPos[nCntVtx]);
		mtxWorld.Multiply(mtxWorld, mtxTrans);

		// �|���S�������𔽉f
		mtxRot.Rotation(m_rot);
		mtxWorld.Multiply(mtxWorld, mtxRot);

		// �|���S���ʒu�𔽉f
		mtxTrans.Translation(m_pos);
		mtxWorld.Multiply(mtxWorld, mtxTrans);

		// �v�Z�����}�g���b�N�X������W��ݒ�
		aVtxMtxPos[nCntVtx] = mtxWorld.GetPosition();
	}

	// �����Ԃ�
	return collision::BoxOuterPillar(aVtxMtxPos[0], aVtxMtxPos[1], aVtxMtxPos[2], aVtxMtxPos[3], rPos);
}

//============================================================
//	���b�V���̒��n�ʒu�̎擾����
//============================================================
float CObjectMeshField::GetPositionHeight(const VECTOR3& rPos)
{
	VECTOR3 aVtxPos[NUM_VTX_TRIANGLE];		// �|���S���̒��_���W
	VECTOR3 aVtxMtxPos[NUM_VTX_TRIANGLE];	// �|���S���̈ʒu�E�������f���s�������_���W
	VECTOR3 pos;	// �^�[�Q�b�g�ʒu
	VECTOR3 nor;	// �@���x�N�g��
	int nNumVtx;	// �@�������߂钸�_�ԍ�
	int nNumCul;	// �@���x�N�g���p�̒��_�v�Z�p

	for (int nCntVtx = 0; nCntVtx < 2; nCntVtx++)
	{ // �l�p�|���S���Ɏg�p����O�p�̐����J��Ԃ�

		// �@���x�N�g���p�̒��_�v�Z�p�̒l��ݒ�
		nNumCul = (nCntVtx == 0) ? 1 : -1;

		for (int nCntHeight = 0; nCntHeight < m_part.y; nCntHeight++)
		{ // �c�̕��������J��Ԃ�

			for (int nCntWidth = 0; nCntWidth < m_part.x; nCntWidth++)
			{ // ���̕��������J��Ԃ�

				// �@�������߂钸�_�ԍ���ݒ�
				nNumVtx = ((nCntWidth + 1) + (nCntHeight * (m_part.x + 1))) + (nCntVtx * m_part.x);

				// �^�[�Q�b�g�ʒu��ݒ�
				pos = rPos;

				// �|���S���̒��_�ʒu���擾
				aVtxPos[0] = GetMeshVertexPosition(nNumVtx);
				aVtxPos[1] = GetMeshVertexPosition(nNumVtx - (1 * nNumCul));
				aVtxPos[2] = GetMeshVertexPosition(nNumVtx + ((m_part.x + 1) * nNumCul));

				for (int nCntTriangle = 0; nCntTriangle < NUM_VTX_TRIANGLE; nCntTriangle++)
				{ // �O�p�`�|���S���̒��_�����J��Ԃ�

					MATRIX mtxWorld, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

					// ���[���h�}�g���b�N�X�̏�����
					mtxWorld.Identity();

					// ���_�ʒu�𔽉f
					mtxTrans.Translation(aVtxPos[nCntTriangle]);
					mtxWorld.Multiply(mtxWorld, mtxTrans);

					// �|���S�������𔽉f
					mtxRot.Rotation(m_rot);
					mtxWorld.Multiply(mtxWorld, mtxRot);

					// �|���S���ʒu�𔽉f
					mtxTrans.Translation(m_pos);
					mtxWorld.Multiply(mtxWorld, mtxTrans);

					// �v�Z�����}�g���b�N�X������W��ݒ�
					aVtxMtxPos[nCntTriangle] = mtxWorld.GetPosition();
				}

				if (collision::TriangleOuterPillar(aVtxMtxPos[0], aVtxMtxPos[1], aVtxMtxPos[2], rPos))
				{ // �|���S���͈͓̔��ɂ���ꍇ

					// �@�������߂�
					useful::NormalizeNormal(aVtxMtxPos[1], aVtxMtxPos[0], aVtxMtxPos[2], nor);

					if (nor.y != 0.0f)
					{ // �@�����ݒ肳��Ă���ꍇ

						// �v���C���[�̒��n�_��Ԃ�
						return (((rPos.x - aVtxMtxPos[0].x) * nor.x + (-aVtxMtxPos[0].y) * nor.y + (rPos.z - aVtxMtxPos[0].z) * nor.z) * -1.0f) / nor.y;
					}
				}
			}
		}
	}

	// ���n�͈͊O�̏ꍇ���݂�y���W��Ԃ�
	return rPos.y;
}

//============================================================
//	�@���̐��K������
//============================================================
void CObjectMeshField::NormalizeNormal()
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	int nNumNor = 0;	// �@���f�[�^�i�[�p

	//--------------------------------------------------------
	//	�@���̐ݒ�
	//--------------------------------------------------------
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHeight = 0; nCntHeight < m_part.y + 1; nCntHeight++)
	{ // �c�̕����� +1��J��Ԃ�

		for (int nCntWidth = 0; nCntWidth < m_part.x + 1; nCntWidth++)
		{ // ���̕����� +1��J��Ԃ�

			int nNumVtx = nCntWidth + (nCntHeight * (m_part.x + 1));	// ���݂̒��_�ԍ�
			if (nNumVtx == 0)
			{ // ���_�ԍ�������̏ꍇ

				// �@���̎g�p���� 2�ɐݒ�
				m_pNumNorBuff[nNumVtx] = 2;

				// �@���̐ݒ�
				m_pNorBuff[nNumNor + 0] = GetNormalRightTop(pVtx);
				m_pNorBuff[nNumNor + 1] = GetNormalRightBottom(pVtx);

				// �@���f�[�^�� 2���i�߂�
				nNumNor += 2;
			}
			else if (nNumVtx == m_nNumVtx - 1)
			{ // ���_�ԍ����E���̏ꍇ

				// �@���̎g�p���� 2�ɐݒ�
				m_pNumNorBuff[nNumVtx] = 2;

				// �@���̐ݒ�
				m_pNorBuff[nNumNor + 0] = GetNormalLeftTop(pVtx);
				m_pNorBuff[nNumNor + 1] = GetNormalLeftBottom(pVtx);

				// �@���f�[�^�� 2���i�߂�
				nNumNor += 2;
			}
			else if (nNumVtx == m_part.x)
			{ // ���_�ԍ����E��̏ꍇ

				// �@���̎g�p���� 1�ɐݒ�
				m_pNumNorBuff[nNumVtx] = 1;

				// �@���̐ݒ�
				m_pNorBuff[nNumNor + 0] = GetNormalLeft(pVtx);

				// �@���f�[�^�� 1���i�߂�
				nNumNor += 1;
			}
			else if (nNumVtx == (m_nNumVtx - 1) - m_part.x)
			{ // ���_�ԍ��������̏ꍇ

				// �@���̎g�p���� 1�ɐݒ�
				m_pNumNorBuff[nNumVtx] = 1;

				// �@���̐ݒ�
				m_pNorBuff[nNumNor + 0] = GetNormalRight(pVtx);

				// �@���f�[�^�� 1���i�߂�
				nNumNor += 1;
			}
			else if (nNumVtx < m_part.x)
			{ // ���_�ԍ����p�����������s�̒��_�̏ꍇ

				// �@���̎g�p���� 3�ɐݒ�
				m_pNumNorBuff[nNumVtx] = 3;

				// �@���̐ݒ�
				m_pNorBuff[nNumNor + 0] = GetNormalRightTop(pVtx);
				m_pNorBuff[nNumNor + 1] = GetNormalRightBottom(pVtx);
				m_pNorBuff[nNumNor + 2] = GetNormalLeft(pVtx);

				// �@���f�[�^�� 3���i�߂�
				nNumNor += 3;
			}
			else if (nNumVtx > (m_part.x + 1) * m_part.y)
			{ // ���_�ԍ����p������������s�̒��_�̏ꍇ

				// �@���̎g�p���� 3�ɐݒ�
				m_pNumNorBuff[nNumVtx] = 3;

				// �@���̐ݒ�
				m_pNorBuff[nNumNor + 0] = GetNormalRight(pVtx);
				m_pNorBuff[nNumNor + 1] = GetNormalLeftTop(pVtx);
				m_pNorBuff[nNumNor + 2] = GetNormalLeftBottom(pVtx);

				// �@���f�[�^�� 3���i�߂�
				nNumNor += 3;
			}
			else if (nCntWidth == 0)
			{ // ���_�ԍ����p������������s�̒��_�̏ꍇ

				// �@���̎g�p���� 3�ɐݒ�
				m_pNumNorBuff[nNumVtx] = 3;

				// �@���̐ݒ�
				m_pNorBuff[nNumNor + 0] = GetNormalRight(pVtx);
				m_pNorBuff[nNumNor + 1] = GetNormalRightTop(pVtx);
				m_pNorBuff[nNumNor + 2] = GetNormalRightBottom(pVtx);

				// �@���f�[�^�� 3���i�߂�
				nNumNor += 3;
			}
			else if (nCntWidth == m_part.x)
			{ // ���_�ԍ����p���������E��s�̒��_�̏ꍇ

				// �@���̎g�p���� 3�ɐݒ�
				m_pNumNorBuff[nNumVtx] = 3;

				// �@���̐ݒ�
				m_pNorBuff[nNumNor + 0] = GetNormalLeft(pVtx);
				m_pNorBuff[nNumNor + 1] = GetNormalLeftTop(pVtx);
				m_pNorBuff[nNumNor + 2] = GetNormalLeftBottom(pVtx);

				// �@���f�[�^�� 3���i�߂�
				nNumNor += 3;
			}
			else
			{ // ���_�ԍ����O�����̒��_�̏ꍇ

				// �@���̎g�p���� 6�ɐݒ�
				m_pNumNorBuff[nNumVtx] = 6;

				// �@���̐ݒ�
				m_pNorBuff[nNumNor + 0] = GetNormalRight(pVtx);
				m_pNorBuff[nNumNor + 1] = GetNormalRightTop(pVtx);
				m_pNorBuff[nNumNor + 2] = GetNormalRightBottom(pVtx);
				m_pNorBuff[nNumNor + 3] = GetNormalLeft(pVtx);
				m_pNorBuff[nNumNor + 4] = GetNormalLeftTop(pVtx);
				m_pNorBuff[nNumNor + 5] = GetNormalLeftBottom(pVtx);

				// �@���f�[�^�� 6���i�߂�
				nNumNor += 6;
			}

			// ���_�f�[�^�̃|�C���^�� 1���i�߂�
			pVtx += 1;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//--------------------------------------------------------
	//	�@���̕��ω�
	//--------------------------------------------------------
	// �@���f�[�^�i�[�p�ϐ���������
	nNumNor = 0;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{ // ���_�����J��Ԃ�

		VECTOR3 nor = VEC3_ZERO;	// �@���ݒ�p
		for (int nCntNor = 0; nCntNor < m_pNumNorBuff[nCntVtx]; nCntNor++)
		{ // �ݒ肳��Ă���@�������J��Ԃ�

			// �@�������Z
			nor += m_pNorBuff[nNumNor];

			// �@���f�[�^�� 1���i�߂�
			nNumNor++;
		}

		// �@���𕽋ω�
		nor /= (float)m_pNumNorBuff[nCntVtx];

		// �@����ݒ�
		pVtx->nor = nor;

		// ���_�f�[�^�̃|�C���^�� 1���i�߂�
		pVtx += 1;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================================
//	�`��}�g���b�N�X�̌v�Z����
//============================================================
void CObjectMeshField::CalcDrawMatrix()
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
void CObjectMeshField::SetVtx(bool bNor)
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	int nNumVtx = 0;	// ���݂̒��_�ԍ�

	// �e�N�X�`���������̊������v�Z
	D3DXVECTOR2 texRate = D3DXVECTOR2
	(
		(float)m_texPart.x / (float)m_part.x,
		(float)m_texPart.y / (float)m_part.y
	);

	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntHeight = 0; nCntHeight < m_part.y + 1; nCntHeight++)
		{ // �c�̕����� +1��J��Ԃ�

			for (int nCntWidth = 0; nCntWidth < m_part.x + 1; nCntWidth++)
			{ // ���̕����� +1��J��Ԃ�

				// ���݂̒��_�ԍ���ݒ�
				nNumVtx = nCntWidth + (nCntHeight * (m_part.x + 1));

				// ���_���W�̐ݒ�
				pVtx[0].pos = VECTOR3
				( // ����
					nCntWidth * (m_size.x / (float)m_part.x) - (m_size.x * 0.5f),		// x
					0.0f,																// y
					-(nCntHeight * (m_size.y / (float)m_part.y) - (m_size.y * 0.5f))	// z
				);
				pVtx[0].pos += m_pPosGapBuff[nNumVtx];	// ���_����̂���ʂ����Z

				// ���_�J���[�̐ݒ�
				pVtx[0].col = m_col;

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(texRate.x * nCntWidth, texRate.y * nCntHeight);

				// ���_�f�[�^�̃|�C���^�� 1���i�߂�
				pVtx += 1;
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}

	if (bNor)
	{ // �@���̐��K�����s���ꍇ

		// �@���̐ݒ�E���K��
		NormalizeNormal();
	}
}

//============================================================
//	�C���f�b�N�X���̐ݒ菈��
//============================================================
void CObjectMeshField::SetIdx()
{
	WORD* pIdx;	// �C���f�b�N�X���ւ̃|�C���^
	if (m_pIdxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// �C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
		m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCntHeight = 0, nCntWidth = 0; nCntHeight < m_part.y; nCntHeight++)
		{ // �c�̕����� +1��J��Ԃ�

			for (nCntWidth = 0; nCntWidth < m_part.x + 1; nCntWidth++)
			{ // ���̕����� +1��J��Ԃ�

				pIdx[0] = (WORD)((m_part.x + 1) * (nCntHeight + 1) + nCntWidth);
				pIdx[1] = (WORD)((m_part.x + 1) * nCntHeight + nCntWidth);

				// �C���f�b�N�X�f�[�^�̃|�C���^�� 2���i�߂�
				pIdx += 2;
			}

			if (nCntHeight != m_part.y - 1)
			{ // ��Ԏ�O�̕����ꏊ�ł͂Ȃ��ꍇ

				pIdx[0] = (WORD)((m_part.x + 1) * nCntHeight + nCntWidth - 1);
				pIdx[1] = (WORD)((m_part.x + 1) * (nCntHeight + 2));

				// �C���f�b�N�X�f�[�^�̃|�C���^�� 2���i�߂�
				pIdx += 2;
			}
		}

		// �C���f�b�N�X�o�b�t�@���A�����b�N����
		m_pIdxBuff->Unlock();
	}
}

//============================================================
//	�X�N���[���̃e�N�X�`�����W�̐ݒ菈��
//============================================================
void CObjectMeshField::SetScrollTex(const float fTexU, const float fTexV)
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntHeight = 0; nCntHeight < m_part.y + 1; nCntHeight++)
		{ // �c�̕����� +1��J��Ԃ�

			for (int nCntWidth = 0; nCntWidth < m_part.x + 1; nCntWidth++)
			{ // ���̕����� +1��J��Ԃ�

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = VECTOR2((float)nCntWidth + fTexU, (float)nCntHeight + fTexV);

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
void CObjectMeshField::DrawNormal()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_nTextureIdx));

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive
	( // ����
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,
		0,
		m_nNumVtx,		// �g�p���钸�_��
		0,				// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
		m_nNumIdx - 2	// �v���~�e�B�u (�|���S��) ��
	);
}

//============================================================
//	�V�F�[�_�[�`�揈��
//============================================================
void CObjectMeshField::DrawShader(CShader* pShader)
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
	pDevice->DrawIndexedPrimitive
	( // ����
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,
		0,
		m_nNumVtx,		// �g�p���钸�_��
		0,				// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
		m_nNumIdx - 2	// �v���~�e�B�u (�|���S��) ��
	);

	// �`��I��
	pShader->EndPass();
	pShader->End();
}

//============================================================
//	�@���̎擾���� (��)
//============================================================
VECTOR3 CObjectMeshField::GetNormalLeft(VERTEX_3D* pVtx)
{
	// �@���̐��K��
	VECTOR3 nor;	// �@������p
	useful::NormalizeNormal
	( // ����
		pVtx[m_part.x + 1].pos,	// ���ʒu
		pVtx[0].pos,			// ���S�ʒu
		pVtx[-1].pos,			// �E�ʒu
		nor						// �@��
	);

	// �@����Ԃ�
	return nor;
}

//============================================================
//	�@���̎擾���� (����)
//============================================================
VECTOR3 CObjectMeshField::GetNormalLeftTop(VERTEX_3D* pVtx)
{
	// �@���̐��K��
	VECTOR3 nor;	// �@������p
	useful::NormalizeNormal
	( // ����
		pVtx[-(m_part.x + 2)].pos,	// ���ʒu
		pVtx[0].pos,				// ���S�ʒu
		pVtx[-(m_part.x + 1)].pos,	// �E�ʒu
		nor							// �@��
	);

	// �@����Ԃ�
	return nor;
}

//============================================================
//	�@���̎擾���� (����)
//============================================================
VECTOR3 CObjectMeshField::GetNormalLeftBottom(VERTEX_3D* pVtx)
{
	// �@���̐��K��
	VECTOR3 nor;	// �@������p
	useful::NormalizeNormal
	( // ����
		pVtx[-1].pos,				// ���ʒu
		pVtx[0].pos,				// ���S�ʒu
		pVtx[-(m_part.x + 2)].pos,	// �E�ʒu
		nor							// �@��
	);

	// �@����Ԃ�
	return nor;
}

//============================================================
//	�@���̎擾���� (�E)
//============================================================
VECTOR3 CObjectMeshField::GetNormalRight(VERTEX_3D* pVtx)
{
	// �@���̐��K��
	VECTOR3 nor;	// �@������p
	useful::NormalizeNormal
	( // ����
		pVtx[-(m_part.x + 1)].pos,	// ���ʒu
		pVtx[0].pos,				// ���S�ʒu
		pVtx[1].pos,				// �E�ʒu
		nor							// �@��
	);

	// �@����Ԃ�
	return nor;
}

//============================================================
//	�@���̎擾���� (�E��)
//============================================================
VECTOR3 CObjectMeshField::GetNormalRightTop(VERTEX_3D* pVtx)
{
	// �@���̐��K��
	VECTOR3 nor;	// �@������p
	useful::NormalizeNormal
	( // ����
		pVtx[1].pos,			// ���ʒu
		pVtx[0].pos,			// ���S�ʒu
		pVtx[m_part.x + 2].pos,	// �E�ʒu
		nor						// �@��
	);

	// �@����Ԃ�
	return nor;
}

//============================================================
//	�@���̎擾���� (�E��)
//============================================================
VECTOR3 CObjectMeshField::GetNormalRightBottom(VERTEX_3D* pVtx)
{
	// �@���̐��K��
	VECTOR3 nor;	// �@������p
	useful::NormalizeNormal
	( // ����
		pVtx[m_part.x + 2].pos,	// ���ʒu
		pVtx[0].pos,			// ���S�ʒu
		pVtx[m_part.x + 1].pos,	// �E�ʒu
		nor						// �@��
	);

	// �@����Ԃ�
	return nor;
}
