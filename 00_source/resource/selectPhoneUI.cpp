//============================================================
//
//	�d�b���j���[���� [selectPhoneUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "selectPhoneUI.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// �d�b���j���[�̗D�揇��

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(560.0f, 362.5f, 0.0f);	// �t���[���ʒu
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// �t���[������
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(380.0f, 450.0f, 0.0f);	// �t���[���傫��
	}
}

//************************************************************
//	�q�N���X [CSelectPhoneUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSelectPhoneUI::CSelectPhoneUI(AFuncUninit funcUninit, CObject2D *pSoul) : CSelect(funcUninit, pSoul)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CSelectPhoneUI::~CSelectPhoneUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSelectPhoneUI::Init(void)
{
	// �Z���N�g�̏�����
	if (FAILED(CSelect::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �t���[���̈ʒu��ݒ�
	SetFramePosition(frame::POS);

	// �t���[���̌�����ݒ�
	SetFrameRotation(frame::ROT);

	// �t���[���̑傫����ݒ�
	SetFrameSizing(frame::SIZE);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSelectPhoneUI::Uninit(void)
{
	// �Z���N�g�̏I��
	CSelect::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSelectPhoneUI::Update(const float fDeltaTime)
{
	// �Z���N�g�̍X�V
	CSelect::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CSelectPhoneUI::Draw(CShader *pShader)
{
	// �Z���N�g�̕`��
	CSelect::Draw(pShader);
}