//============================================================
//
//	�J�ڃ^�C������ [tileTrans.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "tileTrans.h"
#include "collision.h"
#include "sceneGame.h"
#include "stage.h"
#include "objectChara2D.h"

// TODO
#include "manager.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE_FILE = "data\\TEXTURE\\DEBUG\\trans000.png";
	const int PRIORITY = 3;	// �J�ڃ^�C���̗D�揇��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CListManager<CTileTrans> *CTileTrans::m_pList = nullptr;	// �I�u�W�F�N�g���X�g

//************************************************************
//	�q�N���X [CTileTrans] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTileTrans::CTileTrans(const char *pNextPass) : CObject3D(CObject::LABEL_TILE, CObject::DIM_3D, PRIORITY),
	m_sNextStagePass	(pNextPass)	// �J�ڐ�X�e�[�W�p�X
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CTileTrans::~CTileTrans()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTileTrans::Init(void)
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
	SetVec3Sizing(D3DXVECTOR3(SIZE_TILE, SIZE_TILE, 0.0f));

	if (m_pList == nullptr)
	{ // ���X�g�}�l�[�W���[�����݂��Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̐���
		m_pList = CListManager<CTileTrans>::Create();
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
void CTileTrans::Uninit(void)
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
void CTileTrans::Update(const float fDeltaTime)
{
	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CTileTrans::Draw(CShader *pShader)
{
	// �I�u�W�F�N�g3D�̕`��
	CObject3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CTileTrans *CTileTrans::Create(const char *pNextPass, const D3DXVECTOR3& rPos)
{
	// �J�ڃ^�C���̐���
	CTileTrans *pTileTrans = new CTileTrans(pNextPass);
	if (pTileTrans == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �J�ڃ^�C���̏�����
		if (FAILED(pTileTrans->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �J�ڃ^�C���̔j��
			SAFE_DELETE(pTileTrans);
			return nullptr;
		}

		// �ʒu��ݒ�
		pTileTrans->SetVec3Position(rPos);

		// �m�ۂ����A�h���X��Ԃ�
		return pTileTrans;
	}
}

//============================================================
//	���X�g�擾����
//============================================================
CListManager<CTileTrans> *CTileTrans::GetList(void)
{
	// �I�u�W�F�N�g���X�g��Ԃ�
	return m_pList;
}

//============================================================
//	�J�ڃ^�C���Ƃ̓����蔻��
//============================================================
bool CTileTrans::CollisionTile
(
	const D3DXVECTOR3& rPos,		// �ʒu
	const D3DXVECTOR3& rRot,		// ����
	const CObjectChara2D *pChara2D	// �L�����N�^�[2D���
)
{
	// �L�����N�^�[2D�����݂��Ȃ��ꍇ������
	if (pChara2D == nullptr) { assert(false); return false; }

	// �J�ڃ^�C���Ƃ̓����蔻��
	D3DXVECTOR3 posOffset = pChara2D->CalcCollOffsetPosition(rPos, rRot);	// ���茴�_�ʒu
	D3DXVECTOR3 sizeColl  = pChara2D->GetCollSizing() * 0.5f;				// ����傫��
	return CollisionTile(posOffset, sizeColl, sizeColl);
}

//============================================================
//	�J�ڃ^�C���Ƃ̓����蔻��
//============================================================
bool CTileTrans::CollisionTile
(
	const D3DXVECTOR3& rPos,		// �ʒu
	const D3DXVECTOR3& rSizeUp,		// �傫�� (�E/��/��)
	const D3DXVECTOR3& rSizeDown	// �傫�� (��/��/�O)
)
{
	// �J�ڃ^�C�����Ȃ��ꍇ������
	if (m_pList == nullptr) { return false; }

	std::list<CTileTrans*> list = m_pList->GetList();	// �������X�g
	for (const auto& rList : list)
	{ // �v�f�����J��Ԃ�

		D3DXVECTOR3 posTile  = rList->GetVec3Position();		// �^�C���ʒu
		D3DXVECTOR3 sizeTile = rList->GetVec3Sizing() * 0.5f;	// �^�C���傫��

		// XY���ʂ̋�`�̓����蔻��
		bool bHit = collision::BoxXY
		( // ����
			rPos,		// ����ʒu
			posTile,	// �^�C���ʒu
			rSizeUp,	// ����傫�� (�E/��/��)
			rSizeDown,	// ����傫�� (��/��/�O)
			sizeTile,	// �^�C���傫�� (�E/��/��)
			sizeTile	// �^�C���傫�� (��/��/�O)
		);
		if (bHit)
		{ // �������Ă���ꍇ

			// ���񂾃^�C���̃��[���p�X�ɑJ�ڂ���
			//CSceneGame::GetStage()->SetFadeRoom(rList->m_sNextStagePass.c_str());
			GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_CENTER, "[�������Ă��]");	// TODO
			return true;
		}
	}

	return false;
}
