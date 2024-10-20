//============================================================
//
//	�o���^�C������ [tileSpawn.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "tileSpawn.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE_FILE = "data\\TEXTURE\\DEBUG\\spawn000.png";
	const int PRIORITY = 3;	// �o���^�C���̗D�揇��
}

//************************************************************
//	�q�N���X [CTileSpawn] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTileSpawn::CTileSpawn(const char *pPrevPath) : CObject3D(CObject::LABEL_TILE, CObject::DIM_3D, PRIORITY),
	m_sPrevStagePath	(pPrevPath)	// �J�ڌ��X�e�[�W�p�X
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CTileSpawn::~CTileSpawn()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTileSpawn::Init(void)
{
	// �I�u�W�F�N�g3D�̏�����
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`��������
	BindTexture(TEXTURE_FILE);

	// �傫����ݒ�
	SetVec3Size(VECTOR3(SIZE_TILE, SIZE_TILE, 0.0f));

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CTileSpawn::Uninit(void)
{
	// �I�u�W�F�N�g3D�̏I��
	CObject3D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CTileSpawn::Update(const float fDeltaTime)
{
	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CTileSpawn::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g3D�̕`��
	CObject3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CTileSpawn *CTileSpawn::Create(const char *pPrevPath, const VECTOR3& rPos)
{
	// �o���^�C���̐���
	CTileSpawn *pTileSpawn = new CTileSpawn(pPrevPath);
	if (pTileSpawn == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �o���^�C���̏�����
		if (FAILED(pTileSpawn->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �o���^�C���̔j��
			SAFE_DELETE(pTileSpawn);
			return nullptr;
		}

		// �ʒu��ݒ�
		pTileSpawn->SetVec3Position(rPos);

		// �m�ۂ����A�h���X��Ԃ�
		return pTileSpawn;
	}
}
