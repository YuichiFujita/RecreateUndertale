//============================================================
//
//	�}�b�v�^�C������ [tileMap.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "tileMap.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// �e�N�X�`���t�@�C��
	{
		nullptr,	// �e�N�X�`���Ȃ�
		"data\\TEXTURE\\RUINS\\spr_fallpoint.png",		// ���������n�_
		"data\\TEXTURE\\RUINS\\spr_ruinsgate.png",		// ���C���Y�����O
		"data\\TEXTURE\\RUINS\\spr_ruinsstairs.png",	// ���C���Y��K�i
	};
	const int PRIORITY = 3;	// �}�b�v�^�C���̗D�揇��
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CTileMap::TYPE_MAX, "ERROR : Type Count Mismatch");

//************************************************************
//	�q�N���X [CTileMap] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTileMap::CTileMap() : CObject3D(CObject::LABEL_TILE, CObject::DIM_3D, PRIORITY),
	m_type	((EType)0)	// ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CTileMap::~CTileMap()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTileMap::Init(void)
{
	// �����o�ϐ���������
	m_type = TYPE_NONE;	// ���

	// �I�u�W�F�N�g3D�̏�����
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �傫����ݒ�
	SetVec3Sizing(D3DXVECTOR3(SIZE_TILE, SIZE_TILE, 0.0f));

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CTileMap::Uninit(void)
{
	// �I�u�W�F�N�g3D�̏I��
	CObject3D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CTileMap::Update(const float fDeltaTime)
{
	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CTileMap::Draw(CShader *pShader)
{
	// �I�u�W�F�N�g3D�̕`��
	CObject3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CTileMap *CTileMap::Create(const EType type, const D3DXVECTOR3& rPos)
{
	// �}�b�v�^�C���̐���
	CTileMap *pTileMap = new CTileMap;
	if (pTileMap == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �}�b�v�^�C���̏�����
		if (FAILED(pTileMap->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �}�b�v�^�C���̔j��
			SAFE_DELETE(pTileMap);
			return nullptr;
		}

		// ��ނ�ݒ�
		pTileMap->SetType(type);

		// �ʒu��ݒ�
		pTileMap->SetVec3Position(rPos);

		// �m�ۂ����A�h���X��Ԃ�
		return pTileMap;
	}
}

//============================================================
//	��ސݒ菈��
//============================================================
void CTileMap::SetType(const EType type)
{
	// ��ނ�ۑ�
	m_type = type;

	// �e�N�X�`��������
	BindTexture(TEXTURE_FILE[type]);

	if (m_type == TYPE_FALL_POINT)
	{
		// �傫����ݒ�
		SetVec3Sizing(D3DXVECTOR3(SIZE_TILE * 34.0f, SIZE_TILE * 13.0f, 0.0f));	// TODO�F�ǂ��ɂ����悤
	}
	if (m_type == TYPE_RUINS_GATE)
	{
		// �傫����ݒ�
		SetVec3Sizing(D3DXVECTOR3(SIZE_TILE * 16.0f, SIZE_TILE * 17.0f, 0.0f));	// TODO�F�ǂ��ɂ����悤
	}
	if (m_type == TYPE_RUINS_STAIRS)
	{
		// �傫����ݒ�
		SetVec3Sizing(D3DXVECTOR3(SIZE_TILE * 14.0f, SIZE_TILE * 6.4f, 0.0f));	// TODO�F�ǂ��ɂ����悤
	}
}