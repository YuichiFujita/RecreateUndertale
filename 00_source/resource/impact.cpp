//============================================================
//
//	�Ռ��g���� [impact.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "impact.h"
#include "player.h"
#include "collision.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const POSGRID2	PART			= POSGRID2(64, 1);	// ������
	const POSGRID2	TEX_PART		= POSGRID2(32, 1);	// �e�N�X�`��������
	const float		SUB_HEIGHT		= 2.0f;				// �Ռ��g�̊O���������Z��
	const float		MOVE_TEXU		= 0.05f;			// �e�N�X�`�����ړ���
	const int		DMG_IMPACT		= 15;				// �Ռ��g�̃_���[�W��
	const int		ALPHA_NUMREF	= 10;				// ���e�X�g�̎Q�ƒl
}

//************************************************************
//	�q�N���X [CImpact] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CImpact::CImpact() :
	m_fMaxGrowRadius	(0.0f),						// ���a�̍ő听����
	m_addGrow			(SGrow(0.0f, 0.0f, 0.0f))	// ����������
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CImpact::~CImpact()
{

}

//============================================================
//	����������
//============================================================
HRESULT CImpact::Init(void)
{
	// �����o�ϐ���������
	m_fMaxGrowRadius = 0.0f;				// ���a�̍ő听����
	m_addGrow = SGrow(0.0f, 0.0f, 0.0f);	// ����������

	// �g���̏�����
	if (FAILED(CWave::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �������̐ݒ�
	if (FAILED(SetPattern(PART)))
	{ // �������̐ݒ�Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`���������̐ݒ�
	SetTexPattern(TEX_PART);

	// �����W�̈ړ��ʂ�ݒ�
	SetMoveU(MOVE_TEXU);

	// �����_�[�X�e�[�g�̏����擾
	CRenderState *pRenderState = GetRenderState();

	// ���u�����h�̐ݒ�
	pRenderState->SetAlphaBlend(CRenderState::BLEND_ADD);

	// ���e�X�g�̐ݒ�
	pRenderState->SetAlphaTest(true);			// ���e�X�g�̗L�� / �����̐ݒ�
	pRenderState->SetAlphaFunc(D3DCMP_GREATER);	// ���e�X�g�̐ݒ�
	pRenderState->SetAlphaNumRef(ALPHA_NUMREF);	// ���e�X�g�̎Q�ƒl�ݒ�

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CImpact::Uninit(void)
{
	// �g���̏I��
	CWave::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CImpact::Update(const float fDeltaTime)
{
	// �g���̍X�V
	CWave::Update(fDeltaTime);

	// �v���C���[�Ƃ̓����蔻��
	CollisionPlayer();

	// ����������������
	SGrow curGrow = GetGrow();	// ���݂̐������
	SetGrow(SGrow
	( // ����
		curGrow.fAddHoleRadius	+ m_addGrow.fAddHoleRadius,	// ���̔��a�̐�����
		curGrow.fAddThickness	+ m_addGrow.fAddThickness,	// �����̐�����
		curGrow.fSubAlpha		+ m_addGrow.fSubAlpha		// �����x�̐�����
	));

	if (GetHoleRadius() + GetThickness() > m_fMaxGrowRadius)
	{ // ���a�̍ő�l�ɓ��B�����ꍇ

		float fHeight = GetOuterPlusY();	// �O���̍���

		// �O���̍�����������
		fHeight -= SUB_HEIGHT;
		if (fHeight <= 0.0f)
		{ // �����Ȃ��Ȃ����ꍇ

			// ���g�̏I��
			Uninit();
			return;
		}

		// �O���̍����𔽉f
		SetOuterPlusY(fHeight);
	}
}

//============================================================
//	�`�揈��
//============================================================
void CImpact::Draw(CShader *pShader)
{
	// �g���̕`��
	CWave::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CImpact *CImpact::Create
(
	const ETexture texture,		// ���
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXCOLOR& rCol,		// �F
	const SGrow& rGrow,			// ������
	const SGrow& rAddGrow,		// ����������
	const float fHoleRadius,	// ���̔��a
	const float fThickness,		// ����
	const float fOuterPlusY,	// �O����Y���W���Z��
	const float fMaxGrowRadius	// ���a�̍ő听����
)
{
	// �Ռ��g�̐���
	CImpact *pImpact = new CImpact;
	if (pImpact == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �Ռ��g�̏�����
		if (FAILED(pImpact->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �Ռ��g�̔j��
			SAFE_DELETE(pImpact);
			return nullptr;
		}

		// �e�N�X�`����ݒ�
		pImpact->SetTexture(texture);

		// �ʒu��ݒ�
		pImpact->SetVec3Position(rPos);

		// �F��ݒ�
		pImpact->SetColor(rCol);

		// ��������ݒ�
		pImpact->SetGrow(rGrow);

		// ������������ݒ�
		pImpact->SetAddGrow(rAddGrow);

		// ���̔��a��ݒ�
		pImpact->SetHoleRadius(fHoleRadius);

		// ������ݒ�
		pImpact->SetThickness(fThickness);

		// �O����Y���W���Z�ʂ�ݒ�
		pImpact->SetOuterPlusY(fOuterPlusY);

		// ���a�̍ő听���ʂ�ݒ�
		pImpact->SetMaxGrowRadius(fMaxGrowRadius);

		// �m�ۂ����A�h���X��Ԃ�
		return pImpact;
	}
}

//============================================================
//	�v���C���[�Ƃ̓����蔻��
//============================================================
void CImpact::CollisionPlayer(void)
{
	CListManager<CPlayer> *pList = CPlayer::GetList();		// �v���C���[���X�g
	if (pList == nullptr)		 { assert(false); return; }	// ���X�g���g�p
	if (pList->GetNumAll() != 1) { assert(false); return; }	// �v���C���[��1�l����Ȃ�
	auto player = pList->GetList().front();					// �v���C���[���

	D3DXVECTOR3 posPlayer	= player->GetVec3Position();	// �v���C���[�̈ʒu
	D3DXVECTOR3 posImpact	= GetVec3Position();			// �Ռ��g�̈ʒu
	float fRadiusPlayer		= player->GetRadius();			// �v���C���[�̔��a
	float fRadiusInImpact	= GetHoleRadius() - fRadiusPlayer;					// �Ռ��g�̓������a
	float fRadiusOutImpact	= GetHoleRadius() + GetThickness() + fRadiusPlayer;	// �Ռ��g�̊O�����a

	bool bHitIn  = !collision::Circle2D(posImpact, posPlayer, fRadiusInImpact,  0.0f);	// �Ռ��g�̓��~�̊O���ɂ���
	bool bHitOut =  collision::Circle2D(posImpact, posPlayer, fRadiusOutImpact, 0.0f);	// �Ռ��g�̊O�~�̓����ɂ���
	if (bHitIn && bHitOut)
	{ // �Ռ��g�ɓ������Ă���ꍇ

		float fPlayerFoot = posPlayer.y;						// �v���C���[���ʒu
		float fPlayerHead = posPlayer.y + player->GetHeight();	// �v���C���[���ʒu
		float fImpactDown = posImpact.y;						// �Ռ��g���ʒu
		float fImpactUp   = posImpact.y + GetOuterPlusY();		// �Ռ��g��ʒu
		if (fPlayerFoot <= fImpactUp
		&&  fPlayerHead >= fImpactDown)
		{ // �㉺�͈͓̔��̏ꍇ

			// �v���C���[�̃q�b�g����
			D3DXVECTOR3 vecKnock = posPlayer - posImpact;
			player->HitKnockBack(DMG_IMPACT, vecKnock);
		}
	}
}
