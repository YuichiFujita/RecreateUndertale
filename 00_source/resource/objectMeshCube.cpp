//============================================================
//
//	�I�u�W�F�N�g���b�V���L���[�u���� [objectMeshCube.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectMeshCube.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const VECTOR3 SET_POS_DATA[] =	// ���_���W�ݒ�p
	{
		VECTOR3(-1.0f, +1.0f, -1.0f), VECTOR3(-1.0f, -1.0f, -1.0f),
		VECTOR3(+1.0f, +1.0f, -1.0f), VECTOR3(+1.0f, -1.0f, -1.0f),
		VECTOR3(+1.0f, +1.0f, +1.0f), VECTOR3(+1.0f, -1.0f, +1.0f),
		VECTOR3(-1.0f, +1.0f, +1.0f), VECTOR3(-1.0f, -1.0f, +1.0f),
	};

	const VECTOR3 SET_NOR_DATA[] =	// �@���x�N�g���ݒ�p
	{
		VECTOR3(-1.0f, 0.0f, 0.0f), VECTOR3(-1.0f, 0.0f, 0.0f),
		VECTOR3(+1.0f, 0.0f, 0.0f), VECTOR3(+1.0f, 0.0f, 0.0f),
		VECTOR3(+1.0f, 0.0f, 0.0f), VECTOR3(+1.0f, 0.0f, 0.0f),
		VECTOR3(-1.0f, 0.0f, 0.0f), VECTOR3(-1.0f, 0.0f, 0.0f),
		VECTOR3(0.0f, +1.0f, 0.0f), VECTOR3(0.0f, -1.0f, 0.0f),
		VECTOR3(0.0f, +1.0f, 0.0f), VECTOR3(0.0f, -1.0f, 0.0f),
		VECTOR3(0.0f, +1.0f, 0.0f), VECTOR3(0.0f, -1.0f, 0.0f),
		VECTOR3(0.0f, +1.0f, 0.0f), VECTOR3(0.0f, -1.0f, 0.0f),
		VECTOR3(0.0f, 0.0f, -1.0f), VECTOR3(0.0f, 0.0f, -1.0f),
		VECTOR3(0.0f, 0.0f, -1.0f), VECTOR3(0.0f, 0.0f, -1.0f),
		VECTOR3(0.0f, 0.0f, +1.0f), VECTOR3(0.0f, 0.0f, +1.0f),
		VECTOR3(0.0f, 0.0f, +1.0f), VECTOR3(0.0f, 0.0f, +1.0f),
	};

	const VECTOR2 SET_TEX_DATA[] =	// �e�N�X�`�����W�ݒ�p
	{
		VECTOR2(1.0f, 0.0f), VECTOR2(1.0f, 1.0f), VECTOR2(0.0f, 0.0f), VECTOR2(0.0f, 1.0f),
		VECTOR2(1.0f, 0.0f), VECTOR2(1.0f, 1.0f), VECTOR2(0.0f, 0.0f), VECTOR2(0.0f, 1.0f),
		VECTOR2(0.0f, 1.0f), VECTOR2(1.0f, 1.0f), VECTOR2(1.0f, 1.0f), VECTOR2(0.0f, 1.0f),
		VECTOR2(1.0f, 0.0f), VECTOR2(0.0f, 0.0f), VECTOR2(0.0f, 0.0f), VECTOR2(1.0f, 0.0f),
		VECTOR2(0.0f, 0.0f), VECTOR2(0.0f, 1.0f), VECTOR2(1.0f, 0.0f), VECTOR2(1.0f, 1.0f),
		VECTOR2(0.0f, 0.0f), VECTOR2(0.0f, 1.0f), VECTOR2(1.0f, 0.0f), VECTOR2(1.0f, 1.0f),
	};

	const int SET_IDX_DATA[] =	// �C���f�b�N�X�ݒ�p
	{
		8, 14, 10, 12, 4, 5, 2, 3, 18, 19, 16, 17, 0, 1, 6, 7, 22, 23, 20, 21, 13, 15, 11, 9,
	};

	const int NUM_SET_CUBE	= 2;	// ��̃L���[�u�Ɏg�p����L���[�u�̐�
	const int NUM_VTX_CUBE	= 8;	// �l�p�`�̒��_��
	const int NEED_VTX_CUBE	= 24;	// ���b�V���L���[�u�ɕK�v�Ȓ��_�E�C���f�b�N�X��
	const int NUM_CUBE_FACE	= 6;	// �l�p�`�̖ʂ̐�
	const int NUM_VTX_FACE	= 4;	// �l�p�`�̈�ʂ̒��_��
}

//************************************************************
//	�q�N���X [CObjectMeshCube] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectMeshCube::CObjectMeshCube(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObject(label, dimension, nPriority),
	m_pVtxBuff		(nullptr),			// ���_�o�b�t�@
	m_pIdxBuff		(nullptr),			// �C���f�b�N�X�o�b�t�@
	m_pRenderState	(nullptr),			// �����_�[�X�e�[�g�̏��
	m_mtxWorld		(MTX_IDENT),		// ���[���h�}�g���b�N�X
	m_pos			(VEC3_ZERO),		// �ʒu
	m_rot			(VEC3_ZERO),		// ����
	m_size			(VEC3_ZERO),		// �傫��
	m_bordState		(BORDER_OFF),		// �����g�p���
	m_fBordThick	(0.0f),				// ����葾��
	m_texState		(TEXSTATE_ONE),		// �e�N�X�`���g�p���
	m_texIdx		(SFaceTex(0)),		// �e�N�X�`�����
	m_origin		(ORIGIN_CENTER),	// ���_
	m_nNumVtx		(0),				// �K�v���_��
	m_nNumIdx		(0)					// �K�v�C���f�b�N�X��
{
	// �����o�ϐ����N���A
	memset(&m_aCol[0], 0, sizeof(m_aCol));			// �F
	memset(&m_aTexPart[0], 0, sizeof(m_aTexPart));	// �e�N�X�`��������
}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectMeshCube::~CObjectMeshCube()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectMeshCube::Init()
{
	// �����o�ϐ���������
	m_pVtxBuff		= nullptr;			// ���_�o�b�t�@
	m_pIdxBuff		= nullptr;			// �C���f�b�N�X�o�b�t�@
	m_pRenderState	= nullptr;			// �����_�[�X�e�[�g�̏��
	m_mtxWorld		= MTX_IDENT;		// ���[���h�}�g���b�N�X
	m_pos			= VEC3_ZERO;		// �ʒu
	m_rot			= VEC3_ZERO;		// ����
	m_size			= VEC3_ZERO;		// �傫��
	m_bordState		= BORDER_OFF;		// �����g�p���
	m_fBordThick	= 0.0f;				// ����葾��
	m_texState		= TEXSTATE_ONE;		// �e�N�X�`���̎g�p���
	m_origin		= ORIGIN_CENTER;	// ���_
	m_nNumVtx		= 0;				// �K�v���_��
	m_nNumIdx		= 0;				// �K�v�C���f�b�N�X��

	// �F�̏�����
	m_aCol[CUBECOL_CUBE]	= color::White();	// �L���[�u�F
	m_aCol[CUBECOL_BORDER]	= color::Black();	// �����F

	// �e�N�X�`���������̏�����
	m_aTexPart[CUBEPART_X] = VEC2_ONE;	// ������X
	m_aTexPart[CUBEPART_Y] = VEC2_ONE;	// ������Y
	m_aTexPart[CUBEPART_Z] = VEC2_ONE;	// ������Z

	// �e�N�X�`���C���f�b�N�X�̏�����
	m_texIdx = SFaceTex
	( // ����
		NONE_IDX,	// �S�ʂ̃e�N�X�`���C���f�b�N�X
		NONE_IDX,	// ���̃e�N�X�`���C���f�b�N�X
		NONE_IDX,	// �E�̃e�N�X�`���C���f�b�N�X
		NONE_IDX,	// ���̃e�N�X�`���C���f�b�N�X
		NONE_IDX,	// ��̃e�N�X�`���C���f�b�N�X
		NONE_IDX,	// �O�̃e�N�X�`���C���f�b�N�X
		NONE_IDX	// ��̃e�N�X�`���C���f�b�N�X
	);

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
void CObjectMeshCube::Uninit()
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);

	// �C���f�b�N�X�o�b�t�@�̔j��
	SAFE_RELEASE(m_pIdxBuff);

	// �����_�[�X�e�[�g�̔j��
	SAFE_REF_RELEASE(m_pRenderState);

	// �I�u�W�F�N�g���b�V���L���[�u��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CObjectMeshCube::Update(const float fDeltaTime)
{

}

//============================================================
//	�`�揈��
//============================================================
void CObjectMeshCube::Draw(CShader* pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^
	MATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

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
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetVec3Position(const VECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectMeshCube::SetVec3Rotation(const VECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_rot = rRot;

	// �����̐��K��
	useful::NormalizeRot(m_rot);
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CObjectMeshCube::SetVec3Size(const VECTOR3& rSize)
{
	// �����̑傫����ݒ�
	m_size = rSize;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	��������
//============================================================
CObjectMeshCube* CObjectMeshCube::Create
(
	const VECTOR3& rPos,		// �ʒu
	const VECTOR3& rRot,		// ����
	const VECTOR3& rSize,		// �傫��
	const COLOR& rCubeCol,		// �L���[�u�F
	const COLOR& rBorderCol,	// �����F
	const EBorder bordState,	// �������
	const float fBordThick,		// ����葾��
	const ETexState texState,	// �e�N�X�`�����
	const SFaceTex& rTexIdx,	// �e�N�X�`�����
	const EOrigin origin,		// ���_
	const VECTOR2& rTexPartX,	// �e�N�X�`��������X
	const VECTOR2& rTexPartY,	// �e�N�X�`��������Y
	const VECTOR2& rTexPartZ	// �e�N�X�`��������Z
)
{
	// �I�u�W�F�N�g���b�V���L���[�u�̐���
	CObjectMeshCube* pMeshCube = new CObjectMeshCube;
	if (pMeshCube == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g���b�V���L���[�u�̏�����
		if (FAILED(pMeshCube->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g���b�V���L���[�u�̔j��
			SAFE_DELETE(pMeshCube);
			return nullptr;
		}

		// �e�N�X�`��������
		pMeshCube->BindTexture(rTexIdx);

		// ���_��ݒ�
		pMeshCube->SetOrigin(origin);

		// �ʒu��ݒ�
		pMeshCube->SetVec3Position(rPos);

		// ������ݒ�
		pMeshCube->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pMeshCube->SetVec3Size(rSize);

		// �L���[�u�F��ݒ�
		pMeshCube->SetCubeColor(rCubeCol);

		// �����F��ݒ�
		pMeshCube->SetBorderColor(rBorderCol);

		// �����̏�Ԃ�ݒ�
		if (FAILED(pMeshCube->SetBorderState(bordState)))
		{ // �������̐ݒ�Ɏ��s�����ꍇ

			// �I�u�W�F�N�g���b�V���L���[�u�̔j��
			SAFE_DELETE(pMeshCube);
			return nullptr;
		}

		// �����̑�����ݒ�
		pMeshCube->SetBorderThick(fBordThick);

		// �e�N�X�`���̏�Ԃ�ݒ�
		pMeshCube->SetTextureState(texState);

		// �e�N�X�`���̕�����X��ݒ�
		pMeshCube->SetTexturePatternX(rTexPartX);

		// �e�N�X�`���̕�����Y��ݒ�
		pMeshCube->SetTexturePatternY(rTexPartY);

		// �e�N�X�`���̕�����Z��ݒ�
		pMeshCube->SetTexturePatternZ(rTexPartZ);

		// �m�ۂ����A�h���X��Ԃ�
		return pMeshCube;
	}
}

//============================================================
//	�����_�[�X�e�[�g���̎擾����
//============================================================
CRenderState* CObjectMeshCube::GetRenderState()
{
	// �C���X�^���X���g�p
	assert(m_pRenderState != nullptr);

	// �����_�[�X�e�[�g�̏���Ԃ�
	return m_pRenderState;
}

//============================================================
//	�e�N�X�`����������
//============================================================
void CObjectMeshCube::BindTexture(const SFaceTex textureIdx)
{
	// �e�N�X�`���C���f�b�N�X����
	m_texIdx = textureIdx;
}

//============================================================
//	�L���[�u�����x�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetCubeAlpha(const float fAlpha)
{
	// �����̓����x��ݒ�
	m_aCol[CUBECOL_CUBE].a = fAlpha;

	// �L���[�u�F�̐ݒ�
	SetCubeColor(m_aCol[CUBECOL_CUBE]);
}

//============================================================
//	�L���[�u�F�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetCubeColor(const COLOR& rCol)
{
	// �����̃L���[�u�F��ݒ�
	m_aCol[CUBECOL_CUBE] = rCol;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	����蓧���x�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetBorderAlpha(const float fAlpha)
{
	// �����̓����x��ݒ�
	m_aCol[CUBECOL_BORDER].a = fAlpha;

	// �����F�̐ݒ�
	SetBorderColor(m_aCol[CUBECOL_BORDER]);
}

//============================================================
//	�����F�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetBorderColor(const COLOR& rCol)
{
	// �����̉����F��ݒ�
	m_aCol[CUBECOL_BORDER] = rCol;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�����̏�Ԃ̐ݒ菈��
//============================================================
HRESULT CObjectMeshCube::SetBorderState(const EBorder bordState)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �����̉����̏�Ԃ�ݒ�
	m_bordState = bordState;

	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);
	assert(m_pVtxBuff == nullptr);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	( // ����
		sizeof(VERTEX_3D) * (NEED_VTX_CUBE + ((int)bordState * NEED_VTX_CUBE)),	// �K�v���_��
		D3DUSAGE_WRITEONLY	,	// �g�p���@
		CObject::FVF_VERTEX_3D,	// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		// �������̎w��
		&m_pVtxBuff,			// ���_�o�b�t�@�ւ̃|�C���^
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
		sizeof(WORD) * (NEED_VTX_CUBE + ((int)bordState * NEED_VTX_CUBE)),	// �K�v�C���f�b�N�X��
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
//	�����̑����̐ݒ菈��
//============================================================
void CObjectMeshCube::SetBorderThick(const float fBordThick)
{
	// �����̉����̑�����ݒ�
	m_fBordThick = fBordThick;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�e�N�X�`���̏�Ԃ̐ݒ菈��
//============================================================
void CObjectMeshCube::SetTextureState(const ETexState texState)
{
	// �����̃e�N�X�`���̏�Ԃ�ݒ�
	m_texState = texState;
}

//============================================================
//	�e�N�X�`���̕�����X�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetTexturePatternX(const VECTOR2& rTexPart)
{
	// �����̃e�N�X�`���̕�����X��ݒ�
	m_aTexPart[CUBEPART_X] = rTexPart;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�e�N�X�`���̕�����Y�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetTexturePatternY(const VECTOR2& rTexPart)
{
	// �����̃e�N�X�`���̕�����Y��ݒ�
	m_aTexPart[CUBEPART_Y] = rTexPart;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�e�N�X�`���̕�����Z�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetTexturePatternZ(const VECTOR2& rTexPart)
{
	// �����̃e�N�X�`���̕�����Z��ݒ�
	m_aTexPart[CUBEPART_Z] = rTexPart;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	���_�ݒ菈��
//============================================================
void CObjectMeshCube::SetOrigin(const EOrigin origin)
{
	// �����̌��_��ݒ�
	m_origin = origin;
}

//============================================================
//	�`��}�g���b�N�X�̌v�Z����
//============================================================
void CObjectMeshCube::CalcDrawMatrix()
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
void CObjectMeshCube::SetVtx()
{
	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^
	int nLoop = 0;		// �L���[�u�̕`�搔
	float fSetBord = 0.0f, fUseBord = 0.0f;	// ���_���W�v�Z�p
	VECTOR2 texPart = VEC2_ZERO;			// �e�N�X�`���������̌v�Z�p
	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �����̗L���ŕ`�搔��ύX
		nLoop = (int)m_bordState + 1;

		for (int nCntBorder = 0; nCntBorder < nLoop; nCntBorder++)
		{ // ����肪ON�̏ꍇ���J��Ԃ�

			// ���_���W�̌v�Z�p�̒l��ݒ�
			fSetBord = (float)(nCntBorder - 1) * m_fBordThick;
			fUseBord = (float)m_bordState;

			for (int nCntSet = 0; nCntSet < NEED_VTX_CUBE; nCntSet++)
			{ // �K�v���_�E�C���f�b�N�X�����J��Ԃ�

				int nVtxIdx = nCntSet % NUM_VTX_CUBE;	// ���݂̔��̒��_�ԍ�
				int nBoxIdx = nCntSet / NUM_VTX_CUBE;	// ���݂̔��ԍ�
				if (nVtxIdx == 0)
				{ // ���_�̐ݒ肪�ꏄ�����ꍇ

					// �e�N�X�`����������ύX
					texPart = VECTOR2
					( // ����
						m_aTexPart[nBoxIdx].x,	// x
						m_aTexPart[nBoxIdx].y	// y
					);
				}

				switch (m_origin)
				{ // ���_���Ƃ̏���
				case ORIGIN_CENTER:	// �������_

					// ���_���W�̐ݒ�
					pVtx[0].pos.x = (m_size.x * SET_POS_DATA[nVtxIdx].x) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxIdx].x);
					pVtx[0].pos.y = (m_size.y * SET_POS_DATA[nVtxIdx].y) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxIdx].y);
					pVtx[0].pos.z = (m_size.z * SET_POS_DATA[nVtxIdx].z) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxIdx].z);

					break;

				case ORIGIN_DOWN:	// �����_

					// ���_���W�̐ݒ�
					pVtx[0].pos.x = (m_size.x * SET_POS_DATA[nVtxIdx].x) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxIdx].x);
					pVtx[0].pos.y = (m_size.y * SET_POS_DATA[nVtxIdx].y * 2.0f) * -((nVtxIdx % 2) - 1) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxIdx].y);
					pVtx[0].pos.z = (m_size.z * SET_POS_DATA[nVtxIdx].z) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxIdx].z);

					break;

				case ORIGIN_UP:		// �㌴�_

					// ���_���W�̐ݒ�
					pVtx[0].pos.x = (m_size.x * SET_POS_DATA[nVtxIdx].x) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxIdx].x);
					pVtx[0].pos.y = (m_size.y * SET_POS_DATA[nVtxIdx].y * 2.0f) * (nVtxIdx % 2) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxIdx].y);
					pVtx[0].pos.z = (m_size.z * SET_POS_DATA[nVtxIdx].z) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxIdx].z);

					break;

				default:	// ��O����
					assert(false);
					break;
				}

				// �@���x�N�g���̐ݒ�
				pVtx[0].nor = SET_NOR_DATA[nCntSet];

				// ���_�J���[�̐ݒ�
				pVtx[0].col = m_aCol[nCntBorder];

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex.x = texPart.x * SET_TEX_DATA[nCntSet].x;
				pVtx[0].tex.y = texPart.y * SET_TEX_DATA[nCntSet].y;

				// ���_�f�[�^�̃|�C���^���ړ�
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
void CObjectMeshCube::SetIdx()
{
	WORD* pIdx;			// �C���f�b�N�X���ւ̃|�C���^
	int nNumVtx = 0;	// ���_���̌v���p
	int nLoop = 0;		// �L���[�u�̕`�搔
	if (m_pIdxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// �C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
		m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		// �����̗L���ŕ`�搔��ύX
		nLoop = (int)m_bordState + 1;

		for (int nCntBorder = 0; nCntBorder < nLoop; nCntBorder++)
		{ // ����肪ON�̏ꍇ���J��Ԃ�

			for (int nCntSet = 0; nCntSet < NEED_VTX_CUBE; nCntSet++)
			{ // �K�v���_�E�C���f�b�N�X�����J��Ԃ�

				// �C���f�b�N�X�̐ݒ�
				pIdx[0] = (WORD)(SET_IDX_DATA[nCntSet] + nNumVtx);

				// �C���f�b�N�X�f�[�^�̃|�C���^���ړ�
				pIdx += 1;
			}

			// ���_�o�b�t�@�̊J�n�n�_��K�v�������炷
			nNumVtx += NEED_VTX_CUBE;
		}

		// �C���f�b�N�X�o�b�t�@���A�����b�N����
		m_pIdxBuff->Unlock();
	}
}

//============================================================
//	�ʏ�`�揈��
//============================================================
void CObjectMeshCube::DrawNormal()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^
	int aTexType[NUM_CUBE_FACE];			// �e�N�X�`���ݒ�p

	//--------------------------------------------------------
	//	�L���[�u�̕`��
	//--------------------------------------------------------
	// �����_�[�X�e�[�g��ݒ�
	m_pRenderState->Set();

	switch (m_texState)
	{ // �e�N�X�`���g�p��Ԃ��Ƃ̏���
	case TEXSTATE_ONE:		// ����e�N�X�`��

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_texIdx.All));

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive
		( // ����
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			0,
			0,
			NEED_VTX_CUBE,			// �g�p���钸�_��
			0,						// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
			NEED_VTX_CUBE - 2		// �v���~�e�B�u (�|���S��) ��
		);

		// �����𔲂���
		break;

	case TEXSTATE_SELECT:	// �S�I���e�N�X�`��

		// �e�N�X�`���̎�ނ�ݒ�
		aTexType[0] = m_texIdx.Top;		// ��̃e�N�X�`��
		aTexType[1] = m_texIdx.Right;	// �E�̃e�N�X�`��
		aTexType[2] = m_texIdx.Near;	// �O�̃e�N�X�`��
		aTexType[3] = m_texIdx.Left;	// ���̃e�N�X�`��
		aTexType[4] = m_texIdx.Far;		// ��̃e�N�X�`��
		aTexType[5] = m_texIdx.Bottom;	// ���̃e�N�X�`��

		for (int nCntFace = 0; nCntFace < NUM_CUBE_FACE; nCntFace++)
		{ // �ʂ̑������J��Ԃ�

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(aTexType[nCntFace]));

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive
			( // ����
				D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
				0,
				0,
				NUM_VTX_FACE,				// �g�p���钸�_��
				nCntFace * NUM_VTX_FACE,	// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
				NUM_VTX_FACE - 2			// �v���~�e�B�u (�|���S��) ��
			);
		}

		// �����𔲂���
		break;
	}

	// �����_�[�X�e�[�g���Đݒ�
	m_pRenderState->Reset();

	//--------------------------------------------------------
	//	�����̕`��
	//--------------------------------------------------------
	if (m_bordState == BORDER_ON)
	{ // ����肪ON�̏ꍇ

		// �|���S���̗��ʂ݂̂�\����Ԃɂ���
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		// ���C�e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, false);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, nullptr);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive
		( // ����
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			0,
			0,
			NEED_VTX_CUBE,			// �g�p���钸�_��
			NEED_VTX_CUBE,			// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
			NEED_VTX_CUBE - 2		// �v���~�e�B�u (�|���S��) ��
		);

		// �|���S���̕\�ʂ݂̂�\����Ԃɂ���
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// ���C�e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, true);
	}
}

//============================================================
//	�V�F�[�_�[�`�揈��
//============================================================
void CObjectMeshCube::DrawShader(CShader* pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^
	int aTexType[NUM_CUBE_FACE];			// �e�N�X�`���ݒ�p

	// �`��J�n
	pShader->Begin();
	pShader->BeginPass(0);

	// �}�g���b�N�X����ݒ�
	pShader->SetMatrix(&m_mtxWorld);

	// ���C�g������ݒ�
	pShader->SetLightDirect(&m_mtxWorld, 0);

	//--------------------------------------------------------
	//	�L���[�u�̕`��
	//--------------------------------------------------------
	// �����_�[�X�e�[�g��ݒ�
	m_pRenderState->Set();

	// �g�U����ݒ�
	pShader->SetOnlyDiffuse(m_aCol[CUBECOL_CUBE]);

	switch (m_texState)
	{ // �e�N�X�`���g�p��Ԃ��Ƃ̏���
	case TEXSTATE_ONE:		// ����e�N�X�`��

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_texIdx.All));

		// �e�N�X�`����ݒ�
		pShader->SetTexture(m_texIdx.All);

		// ��ԕύX�̓`�B
		pShader->CommitChanges();

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive
		( // ����
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			0,
			0,
			NEED_VTX_CUBE,			// �g�p���钸�_��
			0,						// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
			NEED_VTX_CUBE - 2		// �v���~�e�B�u (�|���S��) ��
		);

		// �����𔲂���
		break;

	case TEXSTATE_SELECT:	// �S�I���e�N�X�`��

		// �e�N�X�`���̎�ނ�ݒ�
		aTexType[0] = m_texIdx.Top;		// ��̃e�N�X�`��
		aTexType[1] = m_texIdx.Right;	// �E�̃e�N�X�`��
		aTexType[2] = m_texIdx.Near;	// �O�̃e�N�X�`��
		aTexType[3] = m_texIdx.Left;	// ���̃e�N�X�`��
		aTexType[4] = m_texIdx.Far;		// ��̃e�N�X�`��
		aTexType[5] = m_texIdx.Bottom;	// ���̃e�N�X�`��

		for (int nCntFace = 0; nCntFace < NUM_CUBE_FACE; nCntFace++)
		{ // �ʂ̑������J��Ԃ�

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(aTexType[nCntFace]));

			// �e�N�X�`����ݒ�
			pShader->SetTexture(aTexType[nCntFace]);

			// ��ԕύX�̓`�B
			pShader->CommitChanges();

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive
			( // ����
				D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
				0,
				0,
				NUM_VTX_FACE,				// �g�p���钸�_��
				nCntFace * NUM_VTX_FACE,	// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
				NUM_VTX_FACE - 2			// �v���~�e�B�u (�|���S��) ��
			);
		}

		// �����𔲂���
		break;
	}

	// �����_�[�X�e�[�g���Đݒ�
	m_pRenderState->Reset();

	//--------------------------------------------------------
	//	�����̕`��
	//--------------------------------------------------------
	if (m_bordState == BORDER_ON)
	{ // ����肪ON�̏ꍇ

		// �|���S���̗��ʂ݂̂�\����Ԃɂ���
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		// ���C�e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, false);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, nullptr);

		// �g�U����ݒ�
		pShader->SetOnlyDiffuse(m_aCol[CUBECOL_BORDER]);

		// �e�N�X�`����ݒ�
		pShader->SetTexture(NONE_IDX);

		// ��ԕύX�̓`�B
		pShader->CommitChanges();

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive
		( // ����
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			0,
			0,
			NEED_VTX_CUBE,			// �g�p���钸�_��
			NEED_VTX_CUBE,			// �C���f�b�N�X�o�b�t�@�̊J�n�n�_
			NEED_VTX_CUBE - 2		// �v���~�e�B�u (�|���S��) ��
		);

		// �|���S���̕\�ʂ݂̂�\����Ԃɂ���
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// ���C�e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, true);
	}

	// �`��I��
	pShader->EndPass();
	pShader->End();
}
