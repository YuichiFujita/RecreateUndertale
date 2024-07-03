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

// TODO
#include "manager.h"
#include "collision.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// �e�N�X�`���t�@�C��
	{
		"data\\TEXTURE\\DEBUG\\collision000.png",	// ��`
		"data\\TEXTURE\\DEBUG\\collision001.png",	// �O�p
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
CCollTile::CCollTile() : CObject3D(CObject::LABEL_TILE, CObject::DIM_3D, PRIORITY),
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
//	����^�C���Ƃ̓����蔻�菈��
//============================================================
bool CCollTile::CollisionTile
(
	D3DXVECTOR3& rPos,			// �ʒu
	const D3DXVECTOR3& rPosOld,	// �ߋ��ʒu
	const D3DXVECTOR3& rSize	// �傫��
)
{
	// ����^�C�����Ȃ��ꍇ������
	if (m_pList == nullptr) { return false; }

	std::list<CCollTile*> list = m_pList->GetList();	// �������X�g
	for (const auto& rList : list)
	{ // �v�f�����J��Ԃ�

#if 1
		D3DXVECTOR3 posTile = rList->GetVec3Position();
		D3DXVECTOR3 sizeTile = (rList->GetVec3Sizing() + D3DXVECTOR3(0.0f, 0.0f, 50.0f)) * 0.5f;

		bool bHit = collision::ResponseBox3D
		( // ����
			rPos,
			rPosOld,
			posTile,
			rSize,
			rSize,
			sizeTile,
			sizeTile
		);
		if (bHit)
		{ // �������Ă���ꍇ

			GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_CENTER, "[�������Ă��]");
		}
#else

#endif
	}

	return false;
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
