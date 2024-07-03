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
	m_pNextStagePass	(pNextPass)	// �J�ڐ�X�e�[�W�p�X
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
