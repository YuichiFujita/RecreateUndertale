//============================================================
//
//	�Q�[�W3D���� [gauge3D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "gauge3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int MAX_VERTEX	= 12;	// ���_��
	const int PRIORITY		= 6;	// �Q�[�W3D�̗D�揇��
}

//************************************************************
//	�q�N���X [CGauge3D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGauge3D::CGauge3D(const int nFrame) : CObject(LABEL_UI, DIM_3D, PRIORITY),
	m_nFrame	(nFrame),		// �\���l�̕ϓ��t���[���萔
	m_pVtxBuff	(nullptr),		// ���_�o�b�t�@�ւ̃|�C���^
	m_pos		(VEC3_ZERO),	// �ʒu
	m_sizeGauge	(VEC3_ZERO),	// �Q�[�W�傫��
	m_sizeFrame	(VEC3_ZERO),	// �g�傫��
	m_colFront	(XCOL_WHITE),	// �\�Q�[�W�F
	m_colBack	(XCOL_WHITE),	// ���Q�[�W�F
	m_state		(STATE_NONE),	// ���
	m_nNumGauge	(0),			// �\���l
	m_fChange	(0.0f),			// �Q�[�W�ϓ���
	m_fAddRight	(0.0f),			// �������Z��
	m_fPosUp	(0.0f),			// �\��Y�ʒu�̉��Z��
	m_nCounterState		(0),	// ��ԊǗ��J�E���^�[
	m_nMaxNumGauge		(0),	// �\���l�̍ő�l
	m_fCurrentNumGauge	(0.0f),	// ���ݕ\���l
	m_bDrawFrame		(false)	// �g�\����
{
	// �����o�ϐ����N���A
	memset(&m_aTextureID[0], 0, sizeof(m_aTextureID));	// �e�N�X�`���C���f�b�N�X
}

//============================================================
//	�f�X�g���N�^
//============================================================
CGauge3D::~CGauge3D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CGauge3D::Init(void)
{
	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �����o�ϐ���������
	m_pVtxBuff	= nullptr;			// ���_�o�b�t�@�ւ̃|�C���^
	m_pos		= VEC3_ZERO;		// �ʒu
	m_sizeGauge	= VEC3_ZERO;		// �Q�[�W�傫��
	m_sizeFrame	= VEC3_ZERO;		// �g�傫��
	m_colFront	= XCOL_WHITE;		// �\�Q�[�W�F
	m_colBack	= XCOL_WHITE;		// ���Q�[�W�F
	m_state		= STATE_NONE;		// ���
	m_nNumGauge	= 0;				// �\���l
	m_fChange	= 0.0f;				// �Q�[�W�ϓ���
	m_fAddRight	= 0.0f;				// �������Z��
	m_fPosUp	= 0.0f;				// �\��Y�ʒu�̉��Z��
	m_nCounterState		= 0;		// ��ԊǗ��J�E���^�[
	m_nMaxNumGauge		= 0;		// �\���l�̍ő�l
	m_fCurrentNumGauge	= 0.0f;		// ���ݕ\���l
	m_bDrawFrame		= false;	// �g�\����

	for (int nCntTexture = 0; nCntTexture < POLYGON_MAX; nCntTexture++)
	{ // �g�p����l�p�`�|���S�������J��Ԃ�

		// �e�N�X�`���C���f�b�N�X���N���A
		m_aTextureID[nCntTexture] = NONE_IDX;
	}

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

	// ���_���̐ݒ�
	SetVtx();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CGauge3D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE(m_pVtxBuff);

	// �Q�[�W�\���I�u�W�F�N�g�̍폜
	DeleteGauge();

	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CGauge3D::Update(const float fDeltaTime)
{
	// �ϐ���錾
	D3DXMATRIX mtxGauge;	// �Q�[�W�\���I�u�W�F�N�g�̃}�g���b�N�X

	// �Q�[�W�̐ݒ�
	if (m_state == STATE_CHANGE)
	{ // �̗͂��ϓ����̏ꍇ

		// �J�E���^�[�����Z
		m_nCounterState--;

		// ���݂̃Q�[�W�ɕϓ��ʂ����Z
		m_fCurrentNumGauge += m_fChange;

		// ���݂̕\���l��␳
		useful::LimitNum(m_fCurrentNumGauge, 0.0f, (float)m_nMaxNumGauge);

		// �Q�[�W�̉������Z�ʂ�ݒ�
		m_fAddRight = (m_fCurrentNumGauge * ((m_sizeGauge.x * 2.0f) / (float)m_nMaxNumGauge)) - m_sizeGauge.x;

		// ���_���̐ݒ�
		SetVtx();

		if (m_nCounterState <= 0)
		{ // �J�E���^�[�� 0�ȉ��ɂȂ����ꍇ

			// �ʏ��Ԃɂ���
			m_state = STATE_NONE;
		}
	}

	// �ʒu�̐ݒ�
	for (int nCntGauge = 0; nCntGauge < POLYGON_MAX; nCntGauge++)
	{ // �g�p����l�p�`�|���S�������J��Ԃ�

		if (m_pGauge != nullptr)
		{ // �Q�[�W�\���Ώۂ��g�p����Ă����ꍇ

			// ���[���h�}�g���b�N�X���擾
			mtxGauge = m_pGauge->GetMtxWorld();

			// �ʒu��ݒ�
			m_pos = D3DXVECTOR3(mtxGauge._41, mtxGauge._42 + m_fPosUp, mtxGauge._43);
		}
		else
		{ // �Q�[�W�\���Ώۂ��g�p����Ă��Ȃ������ꍇ

			// �Q�[�W�\�����Ă���I�u�W�F�N�g�̏���������
			m_pGauge = nullptr;

			// �I�u�W�F�N�g�̏I��
			Uninit();

			// �֐��𔲂���
			return;
		}
	}
}

//============================================================
//	�`�揈��
//============================================================
void CGauge3D::Draw(CShader *pShader)
{
	// �ϐ���錾
	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;		// �r���[�}�g���b�N�X

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	// Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);		// Z�o�b�t�@�X�V�̗L�� / �����̐ݒ�

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

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, true);

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);		// Z�o�b�t�@�X�V�̗L�� / �����̐ݒ�
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CGauge3D::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	��������
//============================================================
CGauge3D *CGauge3D::Create
(
	CObject *pObject,				// �Q�[�W�\���I�u�W�F�N�g
	const int nMax,					// �ő�\���l
	const int nFrame,				// �\���l�ϓ��t���[��
	const float fPosUp,				// �\��Y�ʒu�̉��Z��
	const D3DXVECTOR3& rSizeGauge,	// �Q�[�W�傫��
	const D3DXCOLOR& rColFront,		// �\�Q�[�W�F
	const D3DXCOLOR& rColBack,		// ���Q�[�W�F
	const bool bDrawFrame,			// �g�`���
	const char *pPassTex,			// �t���[���e�N�X�`���p�X
	const D3DXVECTOR3& rSizeFrame	// �g�傫��
)
{
	// �Q�[�W3D�̐���
	CGauge3D *pGauge3D = new CGauge3D(nFrame);
	if (pGauge3D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �Q�[�W3D�̏�����
		if (FAILED(pGauge3D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �Q�[�W3D�̔j��
			SAFE_DELETE(pGauge3D);
			return nullptr;
		}

		// �e�N�X�`����o�^�E����
		pGauge3D->BindTexture(POLYGON_FRAME, pPassTex);

		// �Q�[�W�\���I�u�W�F�N�g��ݒ�
		pGauge3D->SetGaugeObject(pObject);

		// Y�ʒu���Z�ʂ�ݒ�
		pGauge3D->SetPositionUp(fPosUp);

		// �Q�[�W�ő�l��ݒ�
		pGauge3D->SetMaxNum(nMax);

		// �傫����ݒ�
		pGauge3D->SetSizingGauge(rSizeGauge);	// �Q�[�W�傫��
		pGauge3D->SetSizingFrame(rSizeFrame);	// �g�傫��

		// �F��ݒ�
		pGauge3D->SetColorFront(rColFront);	// �\�Q�[�W�F
		pGauge3D->SetColorBack(rColBack);	// ���Q�[�W�F

		// �g�̕\���󋵂�ݒ�
		pGauge3D->SetEnableDrawFrame(bDrawFrame);

		// �m�ۂ����A�h���X��Ԃ�
		return pGauge3D;
	}
}

//============================================================
//	�e�N�X�`���������� (�C���f�b�N�X)
//============================================================
void CGauge3D::BindTexture(const int nPolygonID, const int nTextureID)
{
	if (nPolygonID > NONE_IDX && nPolygonID < POLYGON_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		if (nTextureID >= NONE_IDX)
		{ // �e�N�X�`���C���f�b�N�X���g�p�\�ȏꍇ

			// �e�N�X�`���C���f�b�N�X����
			m_aTextureID[nPolygonID] = nTextureID;
		}
		else { assert(false); }	// �͈͊O
	}
}

//============================================================
//	�e�N�X�`���������� (�p�X)
//============================================================
void CGauge3D::BindTexture(const int nPolygonID, const char *pTexturePass)
{
	// �|�C���^��錾
	CTexture *pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	if (nPolygonID > NONE_IDX && nPolygonID < POLYGON_MAX)
	{ // ���K�C���f�b�N�X�̏ꍇ

		if (pTexturePass != nullptr)
		{ // ���蓖�Ă�e�N�X�`���p�X������ꍇ
	
			// �e�N�X�`���C���f�b�N�X��ݒ�
			m_aTextureID[nPolygonID] = pTexture->Regist(pTexturePass);
		}
		else
		{ // ���蓖�Ă�e�N�X�`���p�X���Ȃ��ꍇ

			// �e�N�X�`���Ȃ��C���f�b�N�X��ݒ�
			m_aTextureID[nPolygonID] = NONE_IDX;
		}
	}
}

//============================================================
//	�e�N�X�`���C���f�b�N�X�擾����
//============================================================
int CGauge3D::GetTextureIndex(const int nPolygonID) const
{
	// �񐳋K�ȃ|���S���̃C���f�b�N�X�̏ꍇ������
	if (nPolygonID <= NONE_IDX || nPolygonID >= POLYGON_MAX) { assert(false); return NONE_IDX; }

	// �e�N�X�`���C���f�b�N�X��Ԃ�
	return m_aTextureID[nPolygonID];
}

//============================================================
//	�Q�[�W�̉��Z����
//============================================================
void CGauge3D::AddNum(const int nAdd)
{
	// ���݂̕\���l��ݒ�
	m_fCurrentNumGauge = (float)m_nNumGauge;

	// �\���l�̕ϓ��ʂ����߂�
	m_fChange = ((float)nAdd / (float)m_nFrame);

	// ����ݒ�
	m_state = STATE_CHANGE;		// �Q�[�W�ϓ����
	m_nCounterState = m_nFrame;	// ��ԊǗ��J�E���^�[

	// �\���l�����������Z
	m_nNumGauge += nAdd;

	// �\���l�̐���
	useful::LimitNum(m_nNumGauge, 0, m_nMaxNumGauge);
}

//============================================================
//	�Q�[�W�̐ݒ菈��
//============================================================
void CGauge3D::SetNum(const int nNum)
{
	// �����̕\���l��ݒ�
	m_nNumGauge = nNum;
	useful::LimitNum(m_nNumGauge, 0, m_nMaxNumGauge);	// �\���l�̐���

	// ���݂̕\���l��ݒ�
	m_fCurrentNumGauge = (float)m_nNumGauge;
	useful::LimitNum(m_fCurrentNumGauge, 0.0f, (float)m_nMaxNumGauge);	// ���݂̕\���l�̐���

	// ����ݒ�
	m_state = STATE_NONE;	// �Q�[�W�ϓ����
	m_nCounterState = 0;	// ��ԊǗ��J�E���^�[

	// �Q�[�W�̉������Z�ʂ�ݒ�
	m_fAddRight = (m_fCurrentNumGauge * ((m_sizeGauge.x * 2.0f) / (float)m_nMaxNumGauge)) - m_sizeGauge.x;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�Q�[�W�ő�l�̐ݒ菈��
//============================================================
void CGauge3D::SetMaxNum(const int nMax)
{
	// �����̕\���ő�l��ݒ�
	m_nMaxNumGauge = nMax;

	// �Q�[�W�̐ݒ�
	SetNum(m_nMaxNumGauge);
}

//============================================================
//	�Q�[�W�\���I�u�W�F�N�g�̐ݒ菈��
//============================================================
void CGauge3D::SetGaugeObject(CObject *pObject)
{
	// �����̃I�u�W�F�N�g��ݒ�
	m_pGauge = pObject;
}

//============================================================
//	�Q�[�W�\���I�u�W�F�N�g�̍폜����
//============================================================
void CGauge3D::DeleteGauge(void)
{
	// �Q�[�W3D�\���I�u�W�F�N�g��nullptr�ɂ���
	m_pGauge = nullptr;
}

//============================================================
//	�Q�[�W�傫���̐ݒ菈��
//============================================================
void CGauge3D::SetSizingGauge(const D3DXVECTOR3& rSize)
{
	// �����̃Q�[�W�傫������
	m_sizeGauge = rSize;

	// �Q�[�W�̐ݒ�
	SetNum(m_nNumGauge);

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�g�傫���̐ݒ菈��
//============================================================
void CGauge3D::SetSizingFrame(const D3DXVECTOR3& rSize)
{
	// �����̔w�i�傫������
	m_sizeFrame = rSize;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	�\�Q�[�W�F�̐ݒ菈��
//============================================================
void CGauge3D::SetColorFront(const D3DXCOLOR& rCol)
{
	// �����̕\�Q�[�W�F����
	m_colFront = rCol;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	���Q�[�W�F�̐ݒ菈��
//============================================================
void CGauge3D::SetColorBack(const D3DXCOLOR& rCol)
{
	// �����̗��Q�[�W�F����
	m_colBack = rCol;

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================
//	Y�ʒu���Z�ʂ̐ݒ菈��
//============================================================
void CGauge3D::SetPositionUp(const float fUp)
{
	// ������Y�ʒu���Z�ʂ�ݒ�
	m_fPosUp = fUp;
}

//============================================================
//	�g�\���󋵐ݒ菈��
//============================================================
void CGauge3D::SetEnableDrawFrame(const bool bDraw)
{
	// �����̘g�̕\���󋵂�ݒ�
	m_bDrawFrame = bDraw;
}

//============================================================
//	���_���̐ݒ菈��
//============================================================
void CGauge3D::SetVtx(void)
{
	// �|�C���^��錾
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	if (m_pVtxBuff != nullptr)
	{ // �g�p���̏ꍇ

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntGauge = 0; nCntGauge < POLYGON_MAX; nCntGauge++)
		{ // �g�p����l�p�`�|���S�������J��Ԃ�

			switch (nCntGauge)
			{ // �l�p�`�|���S�����Ƃ̏���
			case POLYGON_BACK:	// �w�i

				// ���_���W��ݒ�
				pVtx[0].pos = D3DXVECTOR3(-m_sizeGauge.x * 0.5f,  m_sizeGauge.y * 0.5f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3( m_sizeGauge.x * 0.5f,  m_sizeGauge.y * 0.5f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-m_sizeGauge.x * 0.5f, -m_sizeGauge.y * 0.5f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3( m_sizeGauge.x * 0.5f, -m_sizeGauge.y * 0.5f, 0.0f);

				// ���_�J���[�̐ݒ�
				pVtx[0].col = m_colBack;
				pVtx[1].col = m_colBack;
				pVtx[2].col = m_colBack;
				pVtx[3].col = m_colBack;

				break;

			case POLYGON_FRONT:	// �Q�[�W

				// ���_���W��ݒ�
				pVtx[0].pos = D3DXVECTOR3(-m_sizeGauge.x * 0.5f,  m_sizeGauge.y * 0.5f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3( m_fAddRight   * 0.5f,  m_sizeGauge.y * 0.5f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-m_sizeGauge.x * 0.5f, -m_sizeGauge.y * 0.5f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3( m_fAddRight   * 0.5f, -m_sizeGauge.y * 0.5f, 0.0f);

				// ���_�J���[�̐ݒ�
				pVtx[0].col = m_colFront;
				pVtx[1].col = m_colFront;
				pVtx[2].col = m_colFront;
				pVtx[3].col = m_colFront;

				break;

			case POLYGON_FRAME:	// �g

				// ���_���W��ݒ�
				pVtx[0].pos = D3DXVECTOR3(-m_sizeFrame.x * 0.5f,  m_sizeFrame.y * 0.5f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3( m_sizeFrame.x * 0.5f,  m_sizeFrame.y * 0.5f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-m_sizeFrame.x * 0.5f, -m_sizeFrame.y * 0.5f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3( m_sizeFrame.x * 0.5f, -m_sizeFrame.y * 0.5f, 0.0f);

				// ���_�J���[�̐ݒ�
				pVtx[0].col = XCOL_WHITE;
				pVtx[1].col = XCOL_WHITE;
				pVtx[2].col = XCOL_WHITE;
				pVtx[3].col = XCOL_WHITE;

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

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// ���_�f�[�^�̃|�C���^�� 4���i�߂�
			pVtx += 4;
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//============================================================
//	�ʏ�`�揈��
//============================================================
void CGauge3D::DrawNormal(void)
{
	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	for (int nCntGauge = 0; nCntGauge < POLYGON_MAX; nCntGauge++)
	{ // �g�p����l�p�`�|���S�������J��Ԃ�

		if (nCntGauge == POLYGON_FRAME)
		{ // �`�悷��l�p�`�|���S�����g�̏ꍇ

			if (m_bDrawFrame)
			{ // �g��\������ꍇ

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_aTextureID[nCntGauge]));

				// �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGauge * 4, 2);
			}
		}
		else
		{ // �`�悷��l�p�`�|���S�����g�ȊO�̏ꍇ

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_aTextureID[nCntGauge]));

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGauge * 4, 2);
		}
	}
}

//============================================================
//	�V�F�[�_�[�`�揈��
//============================================================
void CGauge3D::DrawShader(CShader *pShader)
{
	// �ϐ��z���錾
	D3DXCOLOR aCol[POLYGON_MAX] =	// �F���
	{
		m_colBack,	// �w�i
		m_colFront,	// �Q�[�W
		XCOL_WHITE	// �g
	};

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �`��J�n
	pShader->Begin();
	pShader->BeginPass(0);

	// �}�g���b�N�X����ݒ�
	pShader->SetMatrix(&m_mtxWorld);

	// ���C�g������ݒ�
	pShader->SetLightDirect(&m_mtxWorld, 0);

	for (int nCntGauge = 0; nCntGauge < POLYGON_MAX; nCntGauge++)
	{ // �g�p����l�p�`�|���S�������J��Ԃ�

		// �g�U����ݒ�
		pShader->SetOnlyDiffuse(aCol[nCntGauge]);

		// �e�N�X�`����ݒ�
		pShader->SetTexture(m_aTextureID[nCntGauge]);

		// ��ԕύX�̓`�B
		pShader->CommitChanges();

		if (nCntGauge == POLYGON_FRAME)
		{ // �`�悷��l�p�`�|���S�����g�̏ꍇ

			if (m_bDrawFrame)
			{ // �g��\������ꍇ

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_aTextureID[nCntGauge]));

				// �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGauge * 4, 2);
			}
		}
		else
		{ // �`�悷��l�p�`�|���S�����g�ȊO�̏ꍇ

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, GET_MANAGER->GetTexture()->GetPtr(m_aTextureID[nCntGauge]));

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGauge * 4, 2);
		}
	}

	// �`��I��
	pShader->EndPass();
	pShader->End();
}