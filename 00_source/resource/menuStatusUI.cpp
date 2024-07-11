//============================================================
//
//	�X�e�[�^�X���j���[���� [menuStatusUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "menuStatusUI.h"
#include "frame2D.h"
#include "string2D.h"
#include "text2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 0;	// �X�e�[�^�X���j���[�̗D�揇��

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(155.0f, 160.0f, 0.0f);	// �t���[���ʒu
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// �t���[������
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(200.0f, 140.0f, 0.0f);	// �t���[���傫��
	}
}

//************************************************************
//	�q�N���X [CMenuStatusUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CMenuStatusUI::CMenuStatusUI() : CObject(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY),
	m_pFrame	(nullptr),	// �t���[�����
	m_pName		(nullptr),	// ���O���
	m_pStatus	(nullptr)	// �X�e�[�^�X���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CMenuStatusUI::~CMenuStatusUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CMenuStatusUI::Init(void)
{
	// �����o�ϐ���������
	m_pFrame	= nullptr;	// �t���[�����
	m_pName		= nullptr;	// ���O���
	m_pStatus	= nullptr;	// �X�e�[�^�X���

	// �t���[���̐���
	m_pFrame = CFrame2D::Create
	( // ����
		frame::POS,	// �ʒu
		frame::ROT,	// ����
		frame::SIZE	// �傫��
	);
	if (m_pFrame == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CMenuStatusUI::Uninit(void)
{
	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CMenuStatusUI::Update(const float fDeltaTime)
{

}

//============================================================
//	�`�揈��
//============================================================
void CMenuStatusUI::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	��������
//============================================================
CMenuStatusUI *CMenuStatusUI::Create(void)
{
	// �X�e�[�^�X���j���[�̐���
	CMenuStatusUI *pMenuStatusUI = new CMenuStatusUI;
	if (pMenuStatusUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �X�e�[�^�X���j���[�̏�����
		if (FAILED(pMenuStatusUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �X�e�[�^�X���j���[�̔j��
			SAFE_DELETE(pMenuStatusUI);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pMenuStatusUI;
	}
}
