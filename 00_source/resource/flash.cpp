//============================================================
//
//	�t���b�V������ [flash.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "flash.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 7;	// �t���b�V���̗D�揇��
}

//************************************************************
//	�e�N���X [CFlash] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFlash::CFlash() :
	m_pObject2D	(nullptr),		// �t���b�V���\���̏��
	m_flash		(FLASH_NONE),	// �t���b�V�����
	m_fSubAlpha	(0.0f)			// �����x�̌��Z��
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFlash::~CFlash()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFlash::Init(void)
{
	// �����o�ϐ���������
	m_pObject2D = nullptr;		// �t���b�V���\���̏��
	m_flash		= FLASH_IN;		// �t���b�V�����
	m_fSubAlpha	= 0.0f;			// �����x�̌��Z��

	// �I�u�W�F�N�g2D�̐���
	m_pObject2D = CObject2D::Create
	( // ����
		SCREEN_CENT,	// �ʒu
		SCREEN_SIZE,	// �傫��
		VEC3_ZERO,		// ����
		XCOL_AWHITE		// �F
	);
	if (m_pObject2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ̐ݒ�
	m_pObject2D->SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFlash::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I��
	SAFE_UNINIT(m_pObject2D);
}

//============================================================
//	�X�V����
//============================================================
void CFlash::Update(const float fDeltaTime)
{
	if (m_flash != FLASH_NONE)
	{ // �������Ȃ���Ԃł͂Ȃ��ꍇ

		// �ϐ���錾
		D3DXCOLOR colFlash = m_pObject2D->GetColor();	// �t���b�V���F

		switch (m_flash)
		{ // �t���b�V����Ԃ��Ƃ̏���
		case FLASH_IN:	// �t���b�V���C�����

			// ���l�����Z
			colFlash.a -= m_fSubAlpha;

			if (colFlash.a <= 0.0f)
			{ // ���l�� 0.0f����������ꍇ

				// ���l��␳
				colFlash.a = 0.0f;

				// �t���b�V����Ԃ�ݒ�
				m_flash = FLASH_NONE;	// �������Ȃ����
			}

			break;

		default:	// ��O����
			assert(false);
			break;
		}

		// �F�̔��f
		m_pObject2D->SetColor(colFlash);

		// �I�u�W�F�N�g2D�̍X�V
		m_pObject2D->Update(fDeltaTime);
	}
}

//============================================================
//	�t���b�V���̐ݒ菈��
//============================================================
void CFlash::Set(const float fStartAlpha, const float fSubAlpha)
{
	// �����̓����x��ݒ�
	D3DXCOLOR colFlash = m_pObject2D->GetColor();	// �t���b�V���F
	colFlash.a = fStartAlpha;			// �����x��ݒ�
	m_pObject2D->SetColor(colFlash);	// �����x�𔽉f

	// �����x�̌��Z�ʂ�ݒ�
	m_fSubAlpha = fSubAlpha;

	// �t���b�V���C����Ԃɂ���
	m_flash = FLASH_IN;
}

//============================================================
//	��������
//============================================================
CFlash *CFlash::Create(void)
{
	// �t���b�V���̐���
	CFlash *pFlash = new CFlash;
	if (pFlash == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �t���b�V���̏�����
		if (FAILED(pFlash->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �t���b�V���̔j��
			SAFE_DELETE(pFlash);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pFlash;
	}
}

//============================================================
//	�j������
//============================================================
void CFlash::Release(CFlash *&prFlash)
{
	// �t���b�V���̏I��
	assert(prFlash != nullptr);
	prFlash->Uninit();

	// �������J��
	SAFE_DELETE(prFlash);
}
