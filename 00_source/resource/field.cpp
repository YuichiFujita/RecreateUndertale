//============================================================
//
//	�n�ʏ��� [field.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// �e�N�X�`���t�@�C��
	{
		"data\\TEXTURE\\field000.png",	// �ΎR�D�e�N�X�`��
	};
	const int PRIORITY = 0;	// �n�ʂ̗D�揇��
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CField::TEXTURE_MAX, "ERROR : Texture Count Mismatch");

//************************************************************
//	�q�N���X [CField] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CField::CField() : CObjectMeshField(CObject::LABEL_FIELD, CObject::DIM_3D, PRIORITY)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CField::~CField()
{

}

//============================================================
//	����������
//============================================================
HRESULT CField::Init(void)
{
	// �I�u�W�F�N�g���b�V���t�B�[���h�̏�����
	if (FAILED(CObjectMeshField::Init()))
	{ // �������Ɏ��s�����ꍇ

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
void CField::Uninit(void)
{
	// �I�u�W�F�N�g���b�V���t�B�[���h�̏I��
	CObjectMeshField::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CField::Update(const float fDeltaTime)
{
	// �I�u�W�F�N�g���b�V���t�B�[���h�̍X�V
	CObjectMeshField::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CField::Draw(CShader *pShader)
{
	// �I�u�W�F�N�g���b�V���t�B�[���h�̕`��
	CObjectMeshField::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CField *CField::Create
(
	const ETexture texture,		// ���
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot,	// ����
	const D3DXVECTOR2& rSize,	// �傫��
	const D3DXCOLOR& rCol,		// �F
	const POSGRID2& rPart		// ������
)
{
	// �n�ʂ̐���
	CField *pField = new CField;
	if (pField == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �n�ʂ̏�����
		if (FAILED(pField->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �n�ʂ̔j��
			SAFE_DELETE(pField);
			return nullptr;
		}

		// �e�N�X�`����o�^�E����
		pField->BindTexture(GET_MANAGER->GetTexture()->Regist(TEXTURE_FILE[texture]));

		// �ʒu��ݒ�
		pField->SetVec3Position(rPos);

		// ������ݒ�
		pField->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pField->SetVec2Sizing(rSize);

		// �F��ݒ�
		pField->SetColor(rCol);

		// ��������ݒ�
		if (FAILED(pField->SetPattern(rPart)))
		{ // �������̐ݒ�Ɏ��s�����ꍇ

			// �n�ʂ̔j��
			SAFE_DELETE(pField);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pField;
	}
}
