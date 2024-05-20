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
	const D3DXVECTOR3 SET_POS_DATA[] =	// ���_���W�ݒ�p
	{
		D3DXVECTOR3(-1.0f, +1.0f, -1.0f), D3DXVECTOR3(-1.0f, -1.0f, -1.0f),
		D3DXVECTOR3(+1.0f, +1.0f, -1.0f), D3DXVECTOR3(+1.0f, -1.0f, -1.0f),
		D3DXVECTOR3(+1.0f, +1.0f, +1.0f), D3DXVECTOR3(+1.0f, -1.0f, +1.0f),
		D3DXVECTOR3(-1.0f, +1.0f, +1.0f), D3DXVECTOR3(-1.0f, -1.0f, +1.0f),
	};

	const D3DXVECTOR3 SET_NOR_DATA[] =	// �@���x�N�g���ݒ�p
	{
		D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f),
		D3DXVECTOR3(+1.0f, 0.0f, 0.0f), D3DXVECTOR3(+1.0f, 0.0f, 0.0f),
		D3DXVECTOR3(+1.0f, 0.0f, 0.0f), D3DXVECTOR3(+1.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, +1.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),
		D3DXVECTOR3(0.0f, +1.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),
		D3DXVECTOR3(0.0f, +1.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),
		D3DXVECTOR3(0.0f, +1.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f),
		D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f),
		D3DXVECTOR3(0.0f, 0.0f, +1.0f), D3DXVECTOR3(0.0f, 0.0f, +1.0f),
		D3DXVECTOR3(0.0f, 0.0f, +1.0f), D3DXVECTOR3(0.0f, 0.0f, +1.0f),
	};

	const D3DXVECTOR2 SET_TEX_DATA[] =	// �e�N�X�`�����W�ݒ�p
	{
		D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f),
		D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f),
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
	m_pVtxBuff		(nullptr),		// ���_�o�b�t�@
	m_pIdxBuff		(nullptr),		// �C���f�b�N�X�o�b�t�@
	m_pRenderState	(nullptr),		// �����_�[�X�e�[�g�̏��
	m_nNumVtx		(0),			// �K�v���_��
	m_nNumIdx		(0),			// �K�v�C���f�b�N�X��
	m_origin		(ORIGIN_CENTER)	// ���_
{
	// �����o�ϐ����N���A
	memset(&m_meshCube, 0, sizeof(m_meshCube));	// ���b�V���L���[�u�̏��
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
HRESULT CObjectMeshCube::Init(void)
{
	// �����o�ϐ���������
	m_pVtxBuff		= nullptr;	// ���_�o�b�t�@
	m_pIdxBuff		= nullptr;	// �C���f�b�N�X�o�b�t�@
	m_pRenderState	= nullptr;	// �����_�[�X�e�[�g�̏��
	m_nNumVtx		= 0;		// �K�v���_��
	m_nNumIdx		= 0;		// �K�v�C���f�b�N�X��
	m_origin		= ORIGIN_CENTER;	// ���_

	// ��{���̏�����
	m_meshCube.pos	= VEC3_ZERO;	// �ʒu
	m_meshCube.rot	= VEC3_ZERO;	// ����
	m_meshCube.size	= VEC3_ZERO;	// �傫��
	m_meshCube.aCol[CUBECOL_CUBE]	= XCOL_WHITE;	// �L���[�u�F
	m_meshCube.aCol[CUBECOL_BORDER]	= XCOL_BLACK;	// �����F
	m_meshCube.bordState	= BORDER_OFF;	// �����g�p���
	m_meshCube.fBordThick	= 0.0f;			// ����葾��
	m_meshCube.texState		= TEXSTATE_ONE;	// �e�N�X�`���̎g�p���

	// �e�N�X�`���C���f�b�N�X�̏�����
	m_meshCube.texID = SFaceTex
	( // ����
		NONE_IDX,	// �S�ʂ̃e�N�X�`���C���f�b�N�X
		NONE_IDX,	// ���̃e�N�X�`���C���f�b�N�X
		NONE_IDX,	// �E�̃e�N�X�`���C���f�b�N�X
		NONE_IDX,	// ���̃e�N�X�`���C���f�b�N�X
		NONE_IDX,	// ��̃e�N�X�`���C���f�b�N�X
		NONE_IDX,	// �O�̃e�N�X�`���C���f�b�N�X
		NONE_IDX	// ��̃e�N�X�`���C���f�b�N�X
	);

	// �e�N�X�`���������̏�����
	m_meshCube.aTexPart[CUBEPART_X] = VEC2_ONE;	// ������X
	m_meshCube.aTexPart[CUBEPART_Y] = VEC2_ONE;	// ������Y
	m_meshCube.aTexPart[CUBEPART_Z] = VEC2_ONE;	// ������Z

	// �����_�[�X�e�[�g�̐���
	m_pRenderState = CRenderState::Create();
	if (m_pRenderState == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectMeshCube::Uninit(void)
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
void CObjectMeshCube::Draw(CShader *pShader)
{
	// �ϐ���錾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_meshCube.mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_meshCube.rot.y, m_meshCube.rot.x, m_meshCube.rot.z);
	D3DXMatrixMultiply(&m_meshCube.mtxWorld, &m_meshCube.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_meshCube.pos.x, m_meshCube.pos.y, m_meshCube.pos.z);
	D3DXMatrixMultiply(&m_meshCube.mtxWorld, &m_meshCube.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_meshCube.mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

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
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_meshCube.pos = rPos;
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectMeshCube::SetVec3Rotation(const D3DXVECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_meshCube.rot = rRot;

	// �����̐��K��
	useful::NormalizeRot(m_meshCube.rot);
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CObjectMeshCube::SetVec3Sizing(const D3DXVECTOR3& rSize)
{
	// �����̑傫����ݒ�
	m_meshCube.size = rSize;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	��������
//============================================================
CObjectMeshCube *CObjectMeshCube::Create
(
	const D3DXVECTOR3& rPos,		// �ʒu
	const D3DXVECTOR3& rRot,		// ����
	const D3DXVECTOR3& rSize,		// �傫��
	const D3DXCOLOR& rCubeCol,		// �L���[�u�F
	const D3DXCOLOR& rBorderCol,	// �����F
	const EBorder bordState,		// �������
	const float fBordThick,			// ����葾��
	const ETexState texState,		// �e�N�X�`�����
	const SFaceTex& rTexID,			// �e�N�X�`�����
	const EOrigin origin,			// ���_
	const D3DXVECTOR2& rTexPartX,	// �e�N�X�`��������X
	const D3DXVECTOR2& rTexPartY,	// �e�N�X�`��������Y
	const D3DXVECTOR2& rTexPartZ	// �e�N�X�`��������Z
)
{
	// �I�u�W�F�N�g���b�V���L���[�u�̐���
	CObjectMeshCube *pMeshCube = new CObjectMeshCube;
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
		pMeshCube->BindTexture(rTexID);

		// ���_��ݒ�
		pMeshCube->SetOrigin(origin);

		// �ʒu��ݒ�
		pMeshCube->SetVec3Position(rPos);

		// ������ݒ�
		pMeshCube->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pMeshCube->SetVec3Sizing(rSize);

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
CRenderState *CObjectMeshCube::GetRenderState(void)
{
	// �C���X�^���X���g�p
	assert(m_pRenderState != nullptr);

	// �����_�[�X�e�[�g�̏���Ԃ�
	return m_pRenderState;
}

//============================================================
//	�e�N�X�`����������
//============================================================
void CObjectMeshCube::BindTexture(const SFaceTex textureID)
{
	// �e�N�X�`���C���f�b�N�X����
	m_meshCube.texID = textureID;
}

//============================================================
//	�L���[�u�F�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetCubeColor(const D3DXCOLOR& rCol)
{
	// �����̃L���[�u�F��ݒ�
	m_meshCube.aCol[CUBECOL_CUBE] = rCol;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�����F�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetBorderColor(const D3DXCOLOR& rCol)
{
	// �����̉����F��ݒ�
	m_meshCube.aCol[CUBECOL_BORDER] = rCol;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�����̏�Ԃ̐ݒ菈��
//============================================================
HRESULT CObjectMeshCube::SetBorderState(const EBorder bordState)
{
	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �����̉����̏�Ԃ�ݒ�
	m_meshCube.bordState = bordState;

	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);
	assert(m_pVtxBuff == nullptr);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	( // ����
		sizeof(VERTEX_3D) * (NEED_VTX_CUBE + ((int)bordState * NEED_VTX_CUBE)),	// �K�v���_��
		D3DUSAGE_WRITEONLY	,	// �g�p���@
		object::FVF_VERTEX_3D,	// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		// �������̎w��
		&m_pVtxBuff,			// ���_�o�b�t�@�ւ̃|�C���^
		nullptr
	)))
	{ // ���_�o�b�t�@�̐����Ɏ��s�����ꍇ

		// ���s��Ԃ�
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

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���_�E�C���f�b�N�X���̐ݒ�
	SetVtx();
	SetIdx();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�����̑����̐ݒ菈��
//============================================================
void CObjectMeshCube::SetBorderThick(const float fBordThick)
{
	// �����̉����̑�����ݒ�
	m_meshCube.fBordThick = fBordThick;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�e�N�X�`���̏�Ԃ̐ݒ菈��
//============================================================
void CObjectMeshCube::SetTextureState(const ETexState texState)
{
	// �����̃e�N�X�`���̏�Ԃ�ݒ�
	m_meshCube.texState = texState;
}

//============================================================
//	�e�N�X�`���̕�����X�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetTexturePatternX(const D3DXVECTOR2& rTexPart)
{
	// �����̃e�N�X�`���̕�����X��ݒ�
	m_meshCube.aTexPart[CUBEPART_X] = rTexPart;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�e�N�X�`���̕�����Y�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetTexturePatternY(const D3DXVECTOR2& rTexPart)
{
	// �����̃e�N�X�`���̕�����Y��ݒ�
	m_meshCube.aTexPart[CUBEPART_Y] = rTexPart;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�e�N�X�`���̕�����Z�̐ݒ菈��
//============================================================
void CObjectMeshCube::SetTexturePatternZ(const D3DXVECTOR2& rTexPart)
{
	// �����̃e�N�X�`���̕�����Z��ݒ�
	m_meshCube.aTexPart[CUBEPART_Z] = rTexPart;

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
//	���_���̐ݒ菈��
//============================================================
void CObjectMeshCube::SetVtx(void)
{
	// �ϐ���錾
	int nLoop = 0;	// �L���[�u�̕`�搔
	float fSetBord = 0.0f, fUseBord = 0.0f;	// ���_���W�v�Z�p
	D3DXVECTOR2 texPart = VEC2_ZERO;		// �e�N�X�`���������̌v�Z�p

	// �|�C���^��錾
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �����̗L���ŕ`�搔��ύX
		nLoop = (int)m_meshCube.bordState + 1;

		for (int nCntBorder = 0; nCntBorder < nLoop; nCntBorder++)
		{ // ����肪ON�̏ꍇ���J��Ԃ�

			// ���_���W�̌v�Z�p�̒l��ݒ�
			fSetBord = (float)(nCntBorder - 1) * m_meshCube.fBordThick;
			fUseBord = (float)m_meshCube.bordState;

			for (int nCntSet = 0; nCntSet < NEED_VTX_CUBE; nCntSet++)
			{ // �K�v���_�E�C���f�b�N�X�����J��Ԃ�

				// �ϐ���錾
				int nVtxID = nCntSet % NUM_VTX_CUBE;	// ���݂̔��̒��_�ԍ�
				int nBoxID = nCntSet / NUM_VTX_CUBE;	// ���݂̔��ԍ�

				if (nVtxID == 0)
				{ // ���_�̐ݒ肪�ꏄ�����ꍇ

					// �e�N�X�`����������ύX
					texPart = D3DXVECTOR2
					( // ����
						m_meshCube.aTexPart[nBoxID].x,	// x
						m_meshCube.aTexPart[nBoxID].y	// y
					);
				}

				switch (m_origin)
				{ // ���_���Ƃ̏���
				case ORIGIN_CENTER:	// ����

					// ���_���W�̐ݒ�
					pVtx[0].pos.x = (m_meshCube.size.x * SET_POS_DATA[nVtxID].x) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxID].x);
					pVtx[0].pos.y = (m_meshCube.size.y * SET_POS_DATA[nVtxID].y) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxID].y);
					pVtx[0].pos.z = (m_meshCube.size.z * SET_POS_DATA[nVtxID].z) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxID].z);

					break;

				case ORIGIN_DOWN:	// ��

					// ���_���W�̐ݒ�
					pVtx[0].pos.x = (m_meshCube.size.x * SET_POS_DATA[nVtxID].x) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxID].x);
					pVtx[0].pos.y = (m_meshCube.size.y * SET_POS_DATA[nVtxID].y * 2.0f) * -((nVtxID % 2) - 1) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxID].y);
					pVtx[0].pos.z = (m_meshCube.size.z * SET_POS_DATA[nVtxID].z) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxID].z);

					break;

				case ORIGIN_UP:		// �㌴�_

					// ���_���W�̐ݒ�
					pVtx[0].pos.x = (m_meshCube.size.x * SET_POS_DATA[nVtxID].x) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxID].x);
					pVtx[0].pos.y = (m_meshCube.size.y * SET_POS_DATA[nVtxID].y * 2.0f) * (nVtxID % 2) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxID].y);
					pVtx[0].pos.z = (m_meshCube.size.z * SET_POS_DATA[nVtxID].z) - (fSetBord * fUseBord * -SET_POS_DATA[nVtxID].z);

					break;

				default:	// ��O����
					assert(false);
					break;
				}

				// �@���x�N�g���̐ݒ�
				pVtx[0].nor = SET_NOR_DATA[nCntSet];

				// ���_�J���[�̐ݒ�
				pVtx[0].col = m_meshCube.aCol[nCntBorder];

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
void CObjectMeshCube::SetIdx(void)
{
	// �ϐ���錾
	int nNumVtx = 0;	// ���_���̌v���p
	int nLoop = 0;		// �L���[�u�̕`�搔

	// �|�C���^��錾
	WORD *pIdx;	// �C���f�b�N�X���ւ̃|�C���^

	if (m_pIdxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// �C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
		m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		// �����̗L���ŕ`�搔��ύX
		nLoop = (int)m_meshCube.bordState + 1;

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
void CObjectMeshCube::DrawNormal(void)
{
	// �ϐ��z���錾
	int aTexType[NUM_CUBE_FACE];	// �e�N�X�`���ݒ�p

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	//--------------------------------------------------------
	//	�L���[�u�̕`��
	//--------------------------------------------------------
	// �����_�[�X�e�[�g��ݒ�
	m_pRenderState->Set();

	switch (m_meshCube.texState)
	{ // �e�N�X�`���g�p��Ԃ��Ƃ̏���
	case TEXSTATE_ONE:		// ����e�N�X�`��

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_meshCube.texID.All));

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
		aTexType[0] = m_meshCube.texID.Top;		// ��̃e�N�X�`��
		aTexType[1] = m_meshCube.texID.Right;	// �E�̃e�N�X�`��
		aTexType[2] = m_meshCube.texID.Near;	// �O�̃e�N�X�`��
		aTexType[3] = m_meshCube.texID.Left;	// ���̃e�N�X�`��
		aTexType[4] = m_meshCube.texID.Far;		// ��̃e�N�X�`��
		aTexType[5] = m_meshCube.texID.Bottom;	// ���̃e�N�X�`��

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
	if (m_meshCube.bordState == BORDER_ON)
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
void CObjectMeshCube::DrawShader(CShader *pShader)
{
	// �ϐ��z���錾
	int aTexType[NUM_CUBE_FACE];	// �e�N�X�`���ݒ�p

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �`��J�n
	pShader->Begin();
	pShader->BeginPass(0);

	// �}�g���b�N�X����ݒ�
	pShader->SetMatrix(&m_meshCube.mtxWorld);

	// ���C�g������ݒ�
	pShader->SetLightDirect(&m_meshCube.mtxWorld, 0);

	//--------------------------------------------------------
	//	�L���[�u�̕`��
	//--------------------------------------------------------
	// �����_�[�X�e�[�g��ݒ�
	m_pRenderState->Set();

	// �g�U����ݒ�
	pShader->SetOnlyDiffuse(m_meshCube.aCol[CUBECOL_CUBE]);

	switch (m_meshCube.texState)
	{ // �e�N�X�`���g�p��Ԃ��Ƃ̏���
	case TEXSTATE_ONE:		// ����e�N�X�`��

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_meshCube.texID.All));

		// �e�N�X�`����ݒ�
		pShader->SetTexture(m_meshCube.texID.All);

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
		aTexType[0] = m_meshCube.texID.Top;		// ��̃e�N�X�`��
		aTexType[1] = m_meshCube.texID.Right;	// �E�̃e�N�X�`��
		aTexType[2] = m_meshCube.texID.Near;	// �O�̃e�N�X�`��
		aTexType[3] = m_meshCube.texID.Left;	// ���̃e�N�X�`��
		aTexType[4] = m_meshCube.texID.Far;		// ��̃e�N�X�`��
		aTexType[5] = m_meshCube.texID.Bottom;	// ���̃e�N�X�`��

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
	if (m_meshCube.bordState == BORDER_ON)
	{ // ����肪ON�̏ꍇ

		// �|���S���̗��ʂ݂̂�\����Ԃɂ���
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		// ���C�e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, false);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, nullptr);

		// �g�U����ݒ�
		pShader->SetOnlyDiffuse(m_meshCube.aCol[CUBECOL_BORDER]);

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
