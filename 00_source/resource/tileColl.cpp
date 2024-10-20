//============================================================
//
//	����^�C������ [tileColl.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "tileColl.h"
#include "collision.h"
#include "objectChara2D.h"

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
static_assert(NUM_ARRAY(TEXTURE_FILE) == CTileColl::TYPE_MAX, "ERROR : Type Count Mismatch");

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CListManager<CTileColl> *CTileColl::m_pList = nullptr;	// �I�u�W�F�N�g���X�g

//************************************************************
//	�q�N���X [CTileColl] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTileColl::CTileColl() : CObject3D(CObject::LABEL_TILE, CObject::DIM_3D, PRIORITY),
	m_type	((EType)0)	// ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CTileColl::~CTileColl()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTileColl::Init(void)
{
	// �����o�ϐ���������
	m_type = TYPE_BOX;	// ���

	// �I�u�W�F�N�g3D�̏�����
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �傫����ݒ�
	SetVec3Size(VECTOR3(SIZE_TILE, SIZE_TILE, 0.0f));

	if (m_pList == nullptr)
	{ // ���X�g�}�l�[�W���[�����݂��Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̐���
		m_pList = CListManager<CTileColl>::Create();
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
void CTileColl::Uninit(void)
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
void CTileColl::Update(const float fDeltaTime)
{
	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CTileColl::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g3D�̕`��
	CObject3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CTileColl *CTileColl::Create(const EType type, const VECTOR3& rPos)
{
	// ����^�C���̐���
	CTileColl *pTileColl = new CTileColl;
	if (pTileColl == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ����^�C���̏�����
		if (FAILED(pTileColl->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ����^�C���̔j��
			SAFE_DELETE(pTileColl);
			return nullptr;
		}

		// ��ނ�ݒ�
		pTileColl->SetType(type);

		// �ʒu��ݒ�
		pTileColl->SetVec3Position(rPos);

		// �m�ۂ����A�h���X��Ԃ�
		return pTileColl;
	}
}

//============================================================
//	���X�g�擾����
//============================================================
CListManager<CTileColl> *CTileColl::GetList(void)
{
	// �I�u�W�F�N�g���X�g��Ԃ�
	return m_pList;
}

//============================================================
//	�J�ڃ^�C���Ƃ̓����蔻��
//============================================================
void CTileColl::CollisionTile
(
	VECTOR3& rPosCur,				// ���݈ʒu
	const VECTOR3& rPosOld,			// �ߋ��ʒu
	const VECTOR3& rRot,			// ����
	const CObjectChara2D *pChara2D	// �L�����N�^�[2D���
)
{
	// �L�����N�^�[2D�����݂��Ȃ��ꍇ������
	if (pChara2D == nullptr) { assert(false); return; }

	VECTOR3 posCur = pChara2D->CalcCollOffsetPosition(rPosCur, rRot);	// ���茴�_�̌��݈ʒu
	VECTOR3 posOld = pChara2D->CalcCollOffsetPosition(rPosOld, rRot);	// ���茴�_�̉ߋ��ʒu
	VECTOR3 sizeColl = pChara2D->GetCollSize() * 0.5f;					// ����傫��

	// ���茴�_�̌��݈ʒu��ۑ�
	VECTOR3 posSave = posCur;

	// �J�ڃ^�C���Ƃ̓����蔻��
	CollisionTile(posCur, posOld, sizeColl, sizeColl);

	// �����̕␳�ʂ����݈ʒu�ɓK��
	rPosCur -= posSave - posCur;
}

//============================================================
//	�J�ڃ^�C���Ƃ̓����蔻��
//============================================================
void CTileColl::CollisionTile
(
	VECTOR3& rPosCur,			// ���݈ʒu
	const VECTOR3& rPosOld,		// �ߋ��ʒu
	const VECTOR3& rSizeUp,		// �傫�� (�E/��/��)
	const VECTOR3& rSizeDown	// �傫�� (��/��/�O)
)
{
	// �J�ڃ^�C�����Ȃ��ꍇ������
	if (m_pList == nullptr) { return; }

	std::list<CTileColl*> list = m_pList->GetList();	// �������X�g
	for (const auto& rList : list)
	{ // �v�f�����J��Ԃ�

		VECTOR3 posTile  = rList->GetVec3Position();	// �^�C���ʒu
		VECTOR3 sizeTile = rList->GetVec3Size() * 0.5f;	// �^�C���傫��

		// XY���ʂ̊p���̏Փ˔���
		collision::ResponseBoxPillarXY
		( // ����
			rPosCur,	// ���茻�݈ʒu
			rPosOld,	// ����ߋ��ʒu
			posTile,	// �^�C���ʒu
			rSizeUp,	// ����傫�� (�E/��/��)
			rSizeDown,	// ����傫�� (��/��/�O)
			sizeTile,	// �^�C���傫�� (�E/��/��)
			sizeTile	// �^�C���傫�� (��/��/�O)
		);
	}
}

//============================================================
//	��ސݒ菈��
//============================================================
void CTileColl::SetType(const EType type)
{
	// ��ނ�ۑ�
	m_type = type;

	// �e�N�X�`��������
	BindTexture(TEXTURE_FILE[type]);
}
