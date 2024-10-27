//============================================================
//
//	�V�F�[�_�[���� [shader.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "shader.h"
#include "shaderToon.h"
#include "shaderMono.h"
#include "manager.h"
#include "renderer.h"

//************************************************************
//	�e�N���X [CShader] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CShader::CShader() :
	m_pEffect			(nullptr),	// �G�t�F�N�g�|�C���^
	m_pTechnique		(nullptr),	// �e�N�j�b�N�֐�
	m_pMtxWorld			(nullptr),	// ���[���h�}�g���b�N�X
	m_pMtxView			(nullptr),	// �r���[�}�g���b�N�X
	m_pMtxProjection	(nullptr)	// �v���W�F�N�V�����}�g���b�N�X
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CShader::~CShader()
{

}

//============================================================
//	����������
//============================================================
HRESULT CShader::Init()
{
	// �����o�ϐ���������
	m_pEffect			= nullptr;	// �G�t�F�N�g�|�C���^
	m_pTechnique		= nullptr;	// �e�N�j�b�N�֐�
	m_pMtxWorld			= nullptr;	// ���[���h�}�g���b�N�X
	m_pMtxView			= nullptr;	// �r���[�}�g���b�N�X
	m_pMtxProjection	= nullptr;	// �v���W�F�N�V�����}�g���b�N�X

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CShader::Uninit()
{
	// �G�t�F�N�g�̔j��
	SAFE_RELEASE(m_pEffect);
}

//============================================================
//	���C�g�����x�N�g���̐ݒ菈��
//============================================================
void CShader::SetLightDirect(MATRIX* /*pMtxWorld*/, const int /*nLightIdx*/)
{

}

//============================================================
//	�e�N�X�`���̐ݒ菈�� (�|�C���^)
//============================================================
void CShader::SetTexture(const CTexture::STexture& /*rTexture*/)
{

}

//============================================================
//	�e�N�X�`���̐ݒ菈�� (�C���f�b�N�X)
//============================================================
void CShader::SetTexture(const int /*nTextureIdx*/)
{

}

//============================================================
//	�}�e���A���̐ݒ菈��
//============================================================
void CShader::SetMaterial(const D3DMATERIAL9& /*rMaterial*/)
{

}

//============================================================
//	�g�U���̐ݒ菈��
//============================================================
void CShader::SetDiffuse(const COLOR& /*rDiffuse*/)
{

}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CShader::SetAmbient(const COLOR& /*rAmbient*/)
{

}

//============================================================
//	���ˌ��̐ݒ菈��
//============================================================
void CShader::SetEmissive(const COLOR& /*rEmissive*/)
{

}

//============================================================
//	�g�U���̂ݐݒ菈��
//============================================================
void CShader::SetOnlyDiffuse(const COLOR& /*rDiffuse*/)
{

}

//============================================================
//	�J�n����
//============================================================
void CShader::Begin()
{
	if (m_pEffect == nullptr) { assert(false); return; }	// �G�t�F�N�g���g�p

	// �J�n
	m_pEffect->Begin(nullptr, 0);
}

//============================================================
//	�p�X�J�n����
//============================================================
void CShader::BeginPass(const BYTE pass)
{
	if (m_pEffect == nullptr) { assert(false); return; }	// �G�t�F�N�g���g�p

	// �p�X�̊J�n
	m_pEffect->BeginPass(pass);
}

//============================================================
//	�p�X�I������
//============================================================
void CShader::EndPass()
{
	if (m_pEffect == nullptr) { assert(false); return; }	// �G�t�F�N�g���g�p

	// �p�X�̏I��
	m_pEffect->EndPass();
}

//============================================================
//	�I������
//============================================================
void CShader::End()
{
	if (m_pEffect == nullptr) { assert(false); return; }	// �G�t�F�N�g���g�p

	// �I��
	m_pEffect->End();
}

//============================================================
//	�}�g���b�N�X�̐ݒ菈��
//============================================================
void CShader::SetMatrix(MATRIX* pMtxWorld)
{
	if (m_pEffect == nullptr) { assert(false); return; }	// �G�t�F�N�g���g�p

	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X���
	MATRIX mtxView;			// �r���[�}�g���b�N�X
	MATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X

	// �r���[�}�g���b�N�X�E�v���W�F�N�V�����}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);

	// �e�}�g���b�N�X��ݒ�
	m_pEffect->SetMatrix(m_pMtxWorld, pMtxWorld);
	m_pEffect->SetMatrix(m_pMtxView, &mtxView);
	m_pEffect->SetMatrix(m_pMtxProjection, &mtxProjection);
}

//============================================================
//	��ԕύX�̓`�B����
//============================================================
void CShader::CommitChanges()
{
	if (m_pEffect == nullptr) { assert(false); return; }	// �G�t�F�N�g���g�p

	// ��ԕύX�̓`�B
	m_pEffect->CommitChanges();
}

//============================================================
//	�G�t�F�N�g�g�p�\�󋵂̎擾����
//============================================================
bool CShader::IsEffectOK() const
{
	// �G�t�F�N�g�|�C���^�̎g�p�󋵂�Ԃ�
	return (m_pEffect != nullptr) ? true : false;
}

//============================================================
//	�G�t�F�N�g�|�C���^�擾����
//============================================================
LPD3DXEFFECT CShader::GetEffect() const
{
	// �G�t�F�N�g�|�C���^��Ԃ�
	return m_pEffect;
}

//============================================================
//	��������
//============================================================
HRESULT CShader::Create()
{
	// �g�D�[���V�F�[�_�[�̐���
	CToonShader* pToonShader = CToonShader::Create();
	if (pToonShader == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �P�F�`��V�F�[�_�[�̐���
	CMonoShader* pMonoShader = CMonoShader::Create();
	if (pMonoShader == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�j������
//============================================================
void CShader::Release()
{
	// �g�D�[���V�F�[�_�[�̔j��
	CToonShader::Release();

	// �P�F�`��V�F�[�_�[�̔j��
	CMonoShader::Release();
}

//============================================================
//	�G�t�F�N�g�|�C���^�̐ݒ菈��
//============================================================
void CShader::SetEffect(const LPD3DXEFFECT pEffect)
{
	// �G�t�F�N�g�|�C���^��ݒ�
	m_pEffect = pEffect;
}

//============================================================
//	�e�N�j�b�N�֐��̐ݒ菈��
//============================================================
void CShader::SetTechnique(const D3DXHANDLE pTechnique)
{
	// �e�N�j�b�N�֐���ݒ�
	m_pTechnique = pTechnique;

	if (m_pEffect != nullptr)
	{ // �G�t�F�N�g���g�p����Ă���ꍇ

		// �G�t�F�N�g�Ƀe�N�j�b�N�֐���ݒ�
		m_pEffect->SetTechnique(m_pTechnique);
	}
	else { assert(false); }	// �G�t�F�N�g�g�p�s��
}
