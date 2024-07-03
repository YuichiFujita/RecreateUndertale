//============================================================
//
//	�v���C���[���� [player.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "player.h"
#include "manager.h"
#include "playerState.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* SETUP_TXT	= "data\\CHARACTER\\frisk.txt";	// �v���C���[�Z�b�g�A�b�v�e�L�X�g
	const int	PRIORITY	= 4;	// �v���C���[�̗D�揇��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CListManager<CPlayer> *CPlayer::m_pList = nullptr;	// �I�u�W�F�N�g���X�g

//************************************************************
//	�q�N���X [CPlayer] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPlayer::CPlayer() : CObjectChara2D(CObject::LABEL_PLAYER, CObject::DIM_3D, PRIORITY),
	m_pState	(nullptr),	// ���
	m_oldPos	(VEC3_ZERO)	// �ߋ��ʒu
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CPlayer::~CPlayer()
{

}

//============================================================
//	����������
//============================================================
HRESULT CPlayer::Init(void)
{
	// �����o�ϐ���������
	m_pState = nullptr;		// ���
	m_oldPos = VEC3_ZERO;	// �ߋ��ʒu

	// �ʏ��Ԃɂ���
	ChangeState(new CPlayerStateNormal);

	// �I�u�W�F�N�g�L�����N�^�[2D�̏�����
	if (FAILED(CObjectChara2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �L�����N�^�[���̊���
	BindCharaData(SETUP_TXT);

	if (m_pList == nullptr)
	{ // ���X�g�}�l�[�W���[�����݂��Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̐���
		m_pList = CListManager<CPlayer>::Create();
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
void CPlayer::Uninit(void)
{
	// ��Ԃ̏I��
	SAFE_UNINIT(m_pState);

	// ���X�g���玩�g�̃I�u�W�F�N�g���폜
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // �I�u�W�F�N�g������Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̔j��
		m_pList->Release(m_pList);
	}

	// �I�u�W�F�N�g�L�����N�^�[2D�̏I��
	CObjectChara2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CPlayer::Update(const float fDeltaTime)
{
	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

	// ��Ԃ��Ƃ̍X�V
	assert(m_pState != nullptr);
	int nCurMotion = m_pState->Update(fDeltaTime);	// ���݂̃��[�V�����擾

	// ���[�V�����E�L�����N�^�[2D�̍X�V
	UpdateMotion(nCurMotion, fDeltaTime);

	// �ʒu�\��
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[�v���C���[�ʒu]�F%f %f %f", GetVec3Position().x, GetVec3Position().y, GetVec3Position().z);
}

//============================================================
//	�`�揈��
//============================================================
void CPlayer::Draw(CShader *pShader)
{
	// �I�u�W�F�N�g�L�����N�^�[2D�̕`��
	CObjectChara2D::Draw(pShader);
}

//============================================================
//	��Ԃ̕ύX����
//============================================================
HRESULT CPlayer::ChangeState(CPlayerState *pState)
{
	// ��Ԃ̐����Ɏ��s���Ă���ꍇ������
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// ��ԃC���X�^���X���I��
	SAFE_UNINIT(m_pState);

	// ��ԃC���X�^���X��ύX
	assert(m_pState == nullptr);
	m_pState = pState;

	// ��ԂɃR���e�L�X�g��ݒ�
	m_pState->SetContext(this);

	// ��ԃC���X�^���X��������
	if (FAILED(m_pState->Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	��������
//============================================================
CPlayer *CPlayer::Create(const D3DXVECTOR3& rPos)
{
	// �v���C���[�̐���
	CPlayer *pPlayer = new CPlayer;
	if (pPlayer == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �v���C���[�̏�����
		if (FAILED(pPlayer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �v���C���[�̔j��
			SAFE_DELETE(pPlayer);
			return nullptr;
		}

		// �ʒu��ݒ�
		pPlayer->SetVec3Position(rPos);

		// �m�ۂ����A�h���X��Ԃ�
		return pPlayer;
	}
}

//============================================================
//	���X�g�擾����
//============================================================
CListManager<CPlayer> *CPlayer::GetList(void)
{
	// �I�u�W�F�N�g���X�g��Ԃ�
	return m_pList;
}

//============================================================
//	�ߋ��ʒu�̍X�V����
//============================================================
void CPlayer::UpdateOldPosition(void)
{
	// �ߋ��ʒu���X�V
	m_oldPos = GetVec3Position();
}

//============================================================
//	���[�V�����E�L�����N�^�[2D�̍X�V����
//============================================================
void CPlayer::UpdateMotion(int nCurMotion, const float fDeltaTime)
{
	// ����ł���ꍇ������
	if (IsDeath()) { return; }

	// ���[�V�������ݒ肳��Ă��Ȃ��ꍇ������
	if (nCurMotion == NONE_IDX) { return; }

	int nAnimMotion = GetMotion();	// ���ݍĐ����̃��[�V����
	if (IsLoop())
	{ // ���[�v���郂�[�V�����������ꍇ

		if (nAnimMotion != nCurMotion)
		{ // ���݂̃��[�V�������Đ����̃��[�V�����ƈ�v���Ȃ��ꍇ

			// ���݂̃��[�V�����̐ݒ�
			SetMotion(nCurMotion);
		}
	}

	// �I�u�W�F�N�g�L�����N�^�[2D�̍X�V
	CObjectChara2D::Update(fDeltaTime);

	switch (GetMotion())
	{ // ���[�V�����̎�ނ��Ƃ̏���
	case MOTION_IDOL_U:	// ��ҋ@���[�V����
	case MOTION_IDOL_D:	// ���ҋ@���[�V����
	case MOTION_IDOL_L:	// ���ҋ@���[�V����
	case MOTION_IDOL_R:	// �E�ҋ@���[�V����
	case MOTION_MOVE_U:	// ��ړ����[�V����
	case MOTION_MOVE_D:	// ���ړ����[�V����
	case MOTION_MOVE_L:	// ���ړ����[�V����
	case MOTION_MOVE_R:	// �E�ړ����[�V����
		break;
	}
}
