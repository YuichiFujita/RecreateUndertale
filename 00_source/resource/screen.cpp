//============================================================
//
//	�X�N���[������ [screen.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "screen.h"
#include "manager.h"
#include "renderer.h"

//************************************************************
//	�q�N���X [CScreen] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CScreen::CScreen()
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CScreen::~CScreen()
{

}

//============================================================
//	����������
//============================================================
HRESULT CScreen::Init(void)
{
	// �I�u�W�F�N�g2D�̏�����
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �ʒu���X�N���[�������ɂ���
	SetVec3Position(SCREEN_CENT);

	// �傫�����X�N���[���T�C�Y�ɂ���
	SetVec3Sizing(SCREEN_SIZE);

	// �����X�V�E�����`���OFF�ɂ���
	SetEnableUpdate(false);
	SetEnableDraw(false);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CScreen::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I��
	CObject2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CScreen::Update(const float fDeltaTime)
{
	// �I�u�W�F�N�g2D�̍X�V
	CObject2D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CScreen::Draw(CShader *pShader)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �T���v���[�X�e�[�g��ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);	// U�����̃��b�s���O�𖳌���
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);	// V�����̃��b�s���O�𖳌���

	// �I�u�W�F�N�g2D�̕`��
	CObject2D::Draw(pShader);

	// �T���v���[�X�e�[�g��ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// U�����̃��b�s���O��L����
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// V�����̃��b�s���O��L����
}

//============================================================
//	��������
//============================================================
CScreen *CScreen::Create(const int nScreenTexID)
{
	// �X�N���[���̐���
	CScreen *pScreen = new CScreen;
	if (pScreen == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �X�N���[���̏�����
		if (FAILED(pScreen->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �X�N���[���̔j��
			SAFE_DELETE(pScreen);
			return nullptr;
		}

		// �e�N�X�`����o�^�E����
		pScreen->BindTexture(nScreenTexID);

		// �m�ۂ����A�h���X��Ԃ�
		return pScreen;
	}
}
