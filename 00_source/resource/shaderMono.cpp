//============================================================
//
//	�P�F�`��V�F�[�_�[�w�b�_�[ [shaderMono.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "shaderMono.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* EFFECT_FX = "data\\SHADER\\shaderMono.fx";	// �P�F�`��V�F�[�_�[�̃G�t�F�N�g�t�@�C��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CMonoShader *CMonoShader::m_pShader = nullptr;	// �V�F�[�_�[���

//************************************************************
//	�e�N���X [CMonoShader] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CMonoShader::CMonoShader() :
	m_pColDraw	(nullptr)	// �s�N�Z���`��F

{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CMonoShader::~CMonoShader()
{

}

//============================================================
//	����������
//============================================================
HRESULT CMonoShader::Init(void)
{
	// �ϐ���錾
	D3DCAPS9 caps;	// �n�[�h�E�F�A�@�\
	HRESULT hr;		// �ُ�I���̊m�F�p

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X���
	LPD3DXBUFFER pError  = nullptr;	// �R���p�C���G���[���
	LPD3DXEFFECT pEffect = nullptr;	// �G�t�F�N�g�ݒ�p

	// �����o�ϐ���������
	m_pColDraw = nullptr;	// �s�N�Z���`��F

	// �V�F�[�_�[�̏�����
	if (FAILED(CShader::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �n�[�h�E�F�A�@�\���擾
	pDevice->GetDeviceCaps(&caps);

	if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1)
	&&  caps.PixelShaderVersion  >= D3DPS_VERSION(2, 0))
	{ // ���_�E�s�N�Z���V�F�[�_�̃o�[�W�������g�p�\�ȏꍇ

		// �G�t�F�N�g�t�@�C���̓Ǎ�
		hr = D3DXCreateEffectFromFile
		( // ����
			pDevice,	// �f�o�C�X�ւ̃|�C���^
			EFFECT_FX,	// �G�t�F�N�g�t�@�C��
			nullptr,	// �v���v���Z�b�T��`
			nullptr,	// �C���N���[�h����
			0,			// �Ǎ��I�v�V�����t���O
			nullptr,	// �O���[�o���ϐ��C���^�[�t�F�[�X
			&pEffect,	// �G�t�F�N�g�C���^�[�t�F�[�X
			&pError		// �R���p�C���G���[���
		);
		if (SUCCEEDED(hr))
		{ // �Ǎ��ɐ��������ꍇ

			// �G�t�F�N�g����ݒ�
			SetEffect(pEffect);

			// �e�N�j�b�N�֐����擾�E�ݒ�
			SetTechnique(pEffect->GetTechniqueByName("TShader"));

			// �e�}�g���b�N�X�̃O���[�o���ϐ����擾�E�ݒ�
			SetMatrixWorld(pEffect->GetParameterByName(nullptr, "g_mtxWorld"));		// ���[���h�}�g���b�N�X
			SetMatrixView(pEffect->GetParameterByName(nullptr, "g_mtxView"));		// �r���[�}�g���b�N�X
			SetMatrixProjection(pEffect->GetParameterByName(nullptr, "g_mtxProj"));	// �v���W�F�N�V�����}�g���b�N�X

			// �O���[�o���ϐ����擾
			m_pColDraw = pEffect->GetParameterByName(nullptr, "g_colDraw");	// �s�N�Z���`��F
		}
		else
		{ // �Ǎ��Ɏ��s�����ꍇ

			// �ǂݍ��ݎ��s��Ԃ�
			assert(false);
			return E_FAIL;
		}
	}
	else
	{ // �o�[�W�������g�p�s�ȏꍇ

		// �Â��o�[�W�����ɂ�鎸�s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CMonoShader::Uninit(void)
{
	// �V�F�[�_�[�̏I��
	CShader::Uninit();
}

//============================================================
//	�s�N�Z���`��F�̐ݒ菈��
//============================================================
void CMonoShader::SetColor(const D3DXCOLOR& rCol)
{
	if (!IsEffectOK()) { assert(false); return; }	// �G�t�F�N�g���g�p

	// �ϐ���錾
	D3DXVECTOR4 col = D3DXVECTOR4(rCol.r, rCol.g, rCol.b, rCol.a);	// �s�N�Z���`��F

	// �G�t�F�N�g�Ƀs�N�Z���`��F��ݒ�
	GetEffect()->SetVector(m_pColDraw, &col);
}

//============================================================
//	��������
//============================================================
CMonoShader *CMonoShader::Create(void)
{
	// �C���X�^���X�g�p��
	assert(m_pShader == nullptr);

	// �P�F�`��V�F�[�_�[�̐���
	m_pShader = new CMonoShader;
	if (m_pShader == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �P�F�`��V�F�[�_�[�̏�����
		if (FAILED(m_pShader->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �P�F�`��V�F�[�_�[�̔j��
			SAFE_DELETE(m_pShader);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return m_pShader;
	}
}

//============================================================
//	�擾����
//============================================================
CMonoShader *CMonoShader::GetInstance(void)
{
	// �C���X�^���X���g�p
	assert(m_pShader != nullptr);

	// �P�F�`��V�F�[�_�[�̃|�C���^��Ԃ�
	return m_pShader;
}

//============================================================
//	�j������
//============================================================
void CMonoShader::Release(void)
{
	// �P�F�`��V�F�[�_�[�̏I��
	assert(m_pShader != nullptr);
	m_pShader->Uninit();

	// �������J��
	SAFE_DELETE(m_pShader);
}
