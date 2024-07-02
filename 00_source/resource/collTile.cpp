//============================================================
//
//	����^�C������ [collTile.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "collTile.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// �e�N�X�`���t�@�C��
	{
		"data\\TEXTURE\\collision000.png",	// ��`
		"data\\TEXTURE\\collision001.png",	// �O�p
	};
	const int PRIORITY = 3;	// ����^�C���̗D�揇��
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CCollTile::TYPE_MAX, "ERROR : Type Count Mismatch");

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CListManager<CCollTile> *CCollTile::m_pList = nullptr;	// �I�u�W�F�N�g���X�g

//************************************************************
//	�q�N���X [CCollTile] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CCollTile::CCollTile() : CObject3D(CObject::LABEL_MAPTILE, CObject::DIM_3D, PRIORITY),
	m_type	((EType)0)	// ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CCollTile::~CCollTile()
{

}

//============================================================
//	����������
//============================================================
HRESULT CCollTile::Init(void)
{
	// �����o�ϐ���������
	m_type = TYPE_TRIANGLE;	// ���	// TODO

	// �I�u�W�F�N�g3D�̏�����
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �傫����ݒ�
	SetVec3Sizing(D3DXVECTOR3(SIZE_TILE, SIZE_TILE, 0.0f));

	if (m_pList == nullptr)
	{ // ���X�g�}�l�[�W���[�����݂��Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̐���
		m_pList = CListManager<CCollTile>::Create();
		if (m_pList == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}
	}

	// ���X�g�Ɏ��g�̃I�u�W�F�N�g��ǉ��E�C�e���[�^�[���擾
	m_iterator = m_pList->AddList(this);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CCollTile::Uninit(void)
{
	// ���X�g���玩�g�̃I�u�W�F�N�g���폜
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // �I�u�W�F�N�g������Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̔j��
		m_pList->Release(m_pList);
	}

	// �I�u�W�F�N�g3D�̏I��
	CObject3D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CCollTile::Update(const float fDeltaTime)
{
	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CCollTile::Draw(CShader *pShader)
{
	// �I�u�W�F�N�g3D�̕`��
	CObject3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CCollTile *CCollTile::Create(const EType type, const D3DXVECTOR3& rPos)
{
	// ����^�C���̐���
	CCollTile *pCollTile = new CCollTile;
	if (pCollTile == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ����^�C���̏�����
		if (FAILED(pCollTile->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ����^�C���̔j��
			SAFE_DELETE(pCollTile);
			return nullptr;
		}

		// ��ނ�ݒ�
		pCollTile->SetType(type);

		// �ʒu��ݒ�
		pCollTile->SetVec3Position(rPos);

		// �m�ۂ����A�h���X��Ԃ�
		return pCollTile;
	}
}

//============================================================
//	���X�g�擾����
//============================================================
CListManager<CCollTile> *CCollTile::GetList(void)
{
	// �I�u�W�F�N�g���X�g��Ԃ�
	return m_pList;
}

//============================================================
//	��ސݒ菈��
//============================================================
void CCollTile::SetType(const EType type)
{
	// ��ނ�ۑ�
	m_type = type;

	// �e�N�X�`��������
	BindTexture(TEXTURE_FILE[type]);
}
