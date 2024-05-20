//============================================================
//
//	�V�l�}�X�R�[�v���� [cinemaScope.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "cinemaScope.h"
#include "renderer.h"
#include "manager.h"
#include "sceneGame.h"
#include "sound.h"
#include "fade.h"
#include "texture.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 5;	// �V�l�}�X�R�[�v�\���̗D�揇��

	namespace scope
	{
		const D3DXVECTOR3	SIZE	= D3DXVECTOR3(SCREEN_SIZE.x, 94.0f, 0.0f);	// �X�R�[�v�̑傫��
		const D3DXVECTOR3	POS		= D3DXVECTOR3(SCREEN_SIZE.x + SIZE.x * 0.5f, SIZE.y * 0.5f, 0.0f);	// �X�R�[�v�̈ʒu
		const D3DXVECTOR3	SPACE	= D3DXVECTOR3(-SIZE.x * 2.0f, SCREEN_SIZE.y - SIZE.y, 0.0f);		// �X�R�[�v�̋�
		const D3DXCOLOR		COL		= XCOL_BLACK;	// �X�R�[�v�̐F

		const D3DXVECTOR3	STOP_POS	= D3DXVECTOR3(SCREEN_CENT.x, SIZE.y * 0.5f, 0.0f);	// �X�R�[�v��~�̈ʒu
		const D3DXVECTOR3	STOP_SPACE	= D3DXVECTOR3(0.0f, SCREEN_SIZE.y - SIZE.y, 0.0f);	// �X�R�[�v��~�̋�

		const D3DXVECTOR3	END_POS		= D3DXVECTOR3(-SIZE.x * 0.5f, SIZE.y * 0.5f, 0.0f);			// �X�R�[�v�I���̈ʒu
		const D3DXVECTOR3	END_SPACE	= D3DXVECTOR3(SIZE.x * 2.0f, SCREEN_SIZE.y - SIZE.y, 0.0f);	// �X�R�[�v�I���̋�

		const int SCOPE_FRAME = 65;	// �X�R�[�v�ړ��t���[��
	}
}

//************************************************************
//	�q�N���X [CCinemaScope] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CCinemaScope::CCinemaScope() :
	m_state			(STATE_NONE),	// ���
	m_nCounterScope	(0)				// �X�R�[�v�ړ��Ǘ��J�E���^�[
{
	// �����o�ϐ����N���A
	memset(&m_apBrack[0], 0, sizeof(m_apBrack));	// ���|���S���̏��
}

//============================================================
//	�f�X�g���N�^
//============================================================
CCinemaScope::~CCinemaScope()
{

}

//============================================================
//	����������
//============================================================
HRESULT CCinemaScope::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apBrack[0], 0, sizeof(m_apBrack));	// ���|���S���̏��
	m_state = STATE_NONE;	// ���
	m_nCounterScope = 0;	// �X�R�[�v�ړ��Ǘ��J�E���^�[

	for (int nCntScope = 0; nCntScope < POLYGON_MAX; nCntScope++)
	{ // �|���S�������J��Ԃ�

		// ���|���S���̐���
		m_apBrack[nCntScope] = CObject2D::Create
		( // ����
			scope::POS + (scope::SPACE * (float)nCntScope),	// �ʒu
			scope::SIZE,	// �傫��
			VEC3_ZERO,		// ����
			scope::COL		// �F
		);
		if (m_apBrack[nCntScope] == nullptr)
		{ // ��g�p���̏ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_apBrack[nCntScope]->SetPriority(PRIORITY);
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CCinemaScope::Uninit(void)
{
	for (int nCntScope = 0; nCntScope < POLYGON_MAX; nCntScope++)
	{ // �|���S�������J��Ԃ�

		// ���|���S���̏I��
		SAFE_UNINIT(m_apBrack[nCntScope]);
	}
}

//============================================================
//	�X�V����
//============================================================
void CCinemaScope::Update(const float fDeltaTime)
{
	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:
		break;

	case STATE_SCOPE_IN:

		// �X�R�[�v�C���̍X�V
		UpdateScopeIn();

		break;

	case STATE_SCOPE_OUT:

		// �X�R�[�v�A�E�g�̍X�V
		UpdateScopeOut();

		break;

	default:
		assert(false);
		break;
	}

	for (int nCntScope = 0; nCntScope < POLYGON_MAX; nCntScope++)
	{ // �|���S�������J��Ԃ�

		// ���|���S���̍X�V
		m_apBrack[nCntScope]->Update(fDeltaTime);
	}
}

//============================================================
//	�`�揈��
//============================================================
void CCinemaScope::Draw(void)
{

}

//============================================================
//	�X�R�[�v�C���̐ݒ菈��
//============================================================
void CCinemaScope::SetScopeIn(void)
{
	if (m_state == STATE_SCOPE_IN) { return; }	// �X�R�[�v�C���̏ꍇ������

	// �J�E���^�[��������
	m_nCounterScope = 0;

	// �X�R�[�v�C����Ԃɂ���
	m_state = STATE_SCOPE_IN;
}

//============================================================
//	�X�R�[�v�A�E�g�̐ݒ菈��
//============================================================
void CCinemaScope::SetScopeOut(void)
{
	if (m_state == STATE_SCOPE_OUT) { return; }	// �X�R�[�v�A�E�g�̏ꍇ������

	// �J�E���^�[��������
	m_nCounterScope = 0;

	// �X�R�[�v�A�E�g��Ԃɂ���
	m_state = STATE_SCOPE_OUT;
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CCinemaScope::SetEnableDraw(const bool bDraw)
{
	for (int nCntScope = 0; nCntScope < POLYGON_MAX; nCntScope++)
	{ // �|���S�������J��Ԃ�

		// ���|���S���̕`��󋵂�ݒ�
		m_apBrack[nCntScope]->SetEnableDraw(bDraw);
	}
}

//============================================================
//	��������
//============================================================
CCinemaScope *CCinemaScope::Create(void)
{
	// �V�l�}�X�R�[�v�̐���
	CCinemaScope *pCinemaScope = new CCinemaScope;
	if (pCinemaScope == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �V�l�}�X�R�[�v�̏�����
		if (FAILED(pCinemaScope->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �V�l�}�X�R�[�v�̔j��
			SAFE_DELETE(pCinemaScope);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pCinemaScope;
	}
}

//============================================================
//	�j������
//============================================================
void CCinemaScope::Release(CCinemaScope *&prCinemaScope)
{
	// �V�l�}�X�R�[�v�̏I��
	assert(prCinemaScope != nullptr);
	prCinemaScope->Uninit();

	// �������J��
	SAFE_DELETE(prCinemaScope);
}

//============================================================
//	�X�R�[�v�C���̍X�V����
//============================================================
void CCinemaScope::UpdateScopeIn(void)
{
	// �J�E���^�[�����Z
	m_nCounterScope++;
	if (m_nCounterScope <= scope::SCOPE_FRAME)
	{ // �X�R�[�v��~�O�̏ꍇ

		for (int nCntScope = 0; nCntScope < POLYGON_MAX; nCntScope++)
		{ // �|���S�������J��Ԃ�

			D3DXVECTOR3 posPoly = m_apBrack[nCntScope]->GetVec3Position();					// �|���S���ʒu
			float fStartPos = scope::POS.x + (scope::SPACE.x * (float)nCntScope);			// ����J�n�ʒu
			float fStopPos = scope::STOP_POS.x + (scope::STOP_SPACE.x * (float)nCntScope);	// �����~�ʒu

			float fRate = easeing::InOutQuad(m_nCounterScope, 0, scope::SCOPE_FRAME);	// ���݃t���[���̃C�[�W���O�l�擾
			float fPosX = (fStopPos - fStartPos) * fRate;								// X���W�����߂�

			// �ʒu�𔽉f
			posPoly.x = fStartPos + fPosX;	// ���݂�X���W���X�V
			m_apBrack[nCntScope]->SetVec3Position(posPoly);
		}
	}
	else
	{ // �X�R�[�v��~��̏ꍇ

		// �J�E���^�[��������
		m_nCounterScope = 0;

		// �Ȃɂ����Ȃ���Ԃɂ���
		m_state = STATE_NONE;
	}
}

//============================================================
//	�X�R�[�v�A�E�g�̍X�V����
//============================================================
void CCinemaScope::UpdateScopeOut(void)
{
	// �J�E���^�[�����Z
	m_nCounterScope++;
	if (m_nCounterScope <= scope::SCOPE_FRAME)
	{ // �X�R�[�v�I���O�̏ꍇ

		for (int nCntScope = 0; nCntScope < POLYGON_MAX; nCntScope++)
		{ // �|���S�������J��Ԃ�

			D3DXVECTOR3 posPoly = m_apBrack[nCntScope]->GetVec3Position();					// �|���S���ʒu
			float fStopPos = scope::STOP_POS.x + (scope::STOP_SPACE.x * (float)nCntScope);	// ����J�n�ʒu
			float fEndPos = scope::END_POS.x + (scope::END_SPACE.x * (float)nCntScope);		// �����~�ʒu

			float fRate = easeing::InOutQuad(m_nCounterScope, 0, scope::SCOPE_FRAME);	// ���݃t���[���̃C�[�W���O�l�擾
			float fPosX = (fEndPos - fStopPos) * fRate;									// X���W�����߂�

			// �ʒu�𔽉f
			posPoly.x = fStopPos + fPosX;	// ���݂�X���W���X�V
			m_apBrack[nCntScope]->SetVec3Position(posPoly);
		}
	}
	else
	{ // �X�R�[�v�I����̏ꍇ

		// �J�E���^�[��������
		m_nCounterScope = 0;

		// �Ȃɂ����Ȃ���Ԃɂ���
		m_state = STATE_NONE;
	}
}
