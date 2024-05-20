//============================================================
//
//	�I�u�W�F�N�g���b�V���X�t�B�A���� [objectMeshSphere.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectMeshSphere.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "objectMeshDome.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const POSGRID2 MIN_PART		= POSGRID2(1, 2);	// �������̍ŏ��l
	const POSGRID2 MIN_TEXPART	= GRID2_ONE;		// �e�N�X�`���������̍ŏ��l
}

//************************************************************
//	�q�N���X [CObjectMeshSphere] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectMeshSphere::CObjectMeshSphere(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CObject(label, dimension, nPriority),
	m_part		(GRID2_ZERO),	// ������
	m_texPart	(GRID2_ZERO)	// �e�N�X�`��������
{
	// �����o�ϐ����N���A
	memset(&m_apDome[0], 0, sizeof(m_apDome));	// �����̏��
}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectMeshSphere::~CObjectMeshSphere()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectMeshSphere::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apDome[0], 0, sizeof(m_apDome));	// �����̏��
	m_part		= MIN_PART;		// ������
	m_texPart	= MIN_TEXPART;	// �e�N�X�`��������

	for (int i = 0; i < DOME_MAX; i++)
	{ // �����̑������J��Ԃ�

		// ���b�V���h�[���̐���
		m_apDome[i] = CObjectMeshDome::Create
		( // ����
			VEC3_ZERO,		// �ʒu
			VEC3_ZERO,		// ����
			XCOL_WHITE,		// �F
			MIN_PART,		// ������
			MIN_TEXPART,	// �e�N�X�`��������
			0.0f			// ���a
		);

		// �����X�V�E�����`���OFF�ɂ���
		m_apDome[i]->SetEnableUpdate(false);
		m_apDome[i]->SetEnableDraw(false);
	}

	// ��������ݒ�
	if (FAILED(SetPattern(MIN_PART)))
	{ // �������̐ݒ�Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CObjectMeshSphere::Uninit(void)
{
	for (int i = 0; i < DOME_MAX; i++)
	{ // �����̑������J��Ԃ�

		// ���b�V���h�[���̏I��
		SAFE_UNINIT(m_apDome[i]);
	}

	// �I�u�W�F�N�g���b�V���X�t�B�A��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CObjectMeshSphere::Update(const float fDeltaTime)
{
	for (int i = 0; i < DOME_MAX; i++)
	{ // �����̑������J��Ԃ�

		// ���b�V���h�[���̍X�V
		m_apDome[i]->Update(fDeltaTime);
	}
}

//============================================================
//	�`�揈��
//============================================================
void CObjectMeshSphere::Draw(CShader *pShader)
{
	for (int i = 0; i < DOME_MAX; i++)
	{ // �����̑������J��Ԃ�

		// ���b�V���h�[���̕`��
		m_apDome[i]->Draw(pShader);
	}
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CObjectMeshSphere::SetPriority(const int nPriority)
{
	// �����̗D�揇�ʂ�ݒ�
	CObject::SetPriority(nPriority);	// ���g
	for (int i = 0; i < DOME_MAX; i++)
	{ // �����̑������J��Ԃ�

		m_apDome[i]->SetPriority(nPriority);	// ����
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CObjectMeshSphere::SetVec3Position(const D3DXVECTOR3& rPos)
{
	for (int i = 0; i < DOME_MAX; i++)
	{ // �����̑������J��Ԃ�

		// �����̈ʒu��ݒ�
		m_apDome[i]->SetVec3Position(rPos);
	}
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CObjectMeshSphere::SetVec3Rotation(const D3DXVECTOR3& rRot)
{
	for (int i = 0; i < DOME_MAX; i++)
	{ // �����̑������J��Ԃ�

		// �����̌�����ݒ�
		D3DXVECTOR3 rot = rRot;
		rot.x += ((float)i * D3DX_PI);
		m_apDome[i]->SetVec3Rotation(rot);
	}
}

//============================================================
//	��������
//============================================================
CObjectMeshSphere *CObjectMeshSphere::Create
(
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot,	// ����
	const D3DXCOLOR& rCol,		// �F
	const POSGRID2& rPart,		// ������
	const POSGRID2& rTexPart,	// �e�N�X�`��������
	const float fRadius			// ���a
)
{
	// �I�u�W�F�N�g���b�V���X�t�B�A�̐���
	CObjectMeshSphere *pMeshSphere = new CObjectMeshSphere;
	if (pMeshSphere == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g���b�V���X�t�B�A�̏�����
		if (FAILED(pMeshSphere->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g���b�V���X�t�B�A�̔j��
			SAFE_DELETE(pMeshSphere);
			return nullptr;
		}

		// �ʒu��ݒ�
		pMeshSphere->SetVec3Position(rPos);

		// ������ݒ�
		pMeshSphere->SetVec3Rotation(rRot);

		// �F��ݒ�
		pMeshSphere->SetColor(rCol);

		// ���a��ݒ�
		pMeshSphere->SetRadius(fRadius);

		// ��������ݒ�
		if (FAILED(pMeshSphere->SetPattern(rPart)))
		{ // �������̐ݒ�Ɏ��s�����ꍇ

			// �I�u�W�F�N�g���b�V���X�t�B�A�̔j��
			SAFE_DELETE(pMeshSphere);
			return nullptr;
		}

		// �e�N�X�`����������ݒ�
		pMeshSphere->SetTexPattern(rTexPart);

		// �m�ۂ����A�h���X��Ԃ�
		return pMeshSphere;
	}
}

//============================================================
//	�����_�[�X�e�[�g���̐ݒ菈��
//============================================================
void CObjectMeshSphere::SetRenderState(CRenderState renderState)
{
	CRenderState *pTempRenderState = nullptr;	// �����_�[�X�e�[�g���
	for (int i = 0; i < DOME_MAX; i++)
	{ // �����̑������J��Ԃ�

		// �����̃����_�[�X�e�[�g��ݒ�
		pTempRenderState = m_apDome[i]->GetRenderState();
		*pTempRenderState = renderState;
	}
}

//============================================================
//	�e�N�X�`���������� (�C���f�b�N�X)
//============================================================
void CObjectMeshSphere::BindTexture(const int nTextureID)
{
	if (nTextureID >= NONE_IDX)
	{ // �e�N�X�`���C���f�b�N�X���g�p�\�ȏꍇ

		for (int i = 0; i < DOME_MAX; i++)
		{ // �����̑������J��Ԃ�

			// �e�N�X�`���C���f�b�N�X������
			m_apDome[i]->BindTexture(nTextureID);
		}
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	�e�N�X�`���������� (�p�X)
//============================================================
void CObjectMeshSphere::BindTexture(const char *pTexturePass)
{
	if (pTexturePass != nullptr)
	{ // ���蓖�Ă�e�N�X�`���p�X������ꍇ

		CTexture *pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`���ւ̃|�C���^
		for (int i = 0; i < DOME_MAX; i++)
		{ // �����̑������J��Ԃ�

			// �e�N�X�`���C���f�b�N�X������
			m_apDome[i]->BindTexture(pTexture->Regist(pTexturePass));
		}
	}
	else
	{ // ���蓖�Ă�e�N�X�`���p�X���Ȃ��ꍇ

		for (int i = 0; i < DOME_MAX; i++)
		{ // �����̑������J��Ԃ�

			// �e�N�X�`���Ȃ��C���f�b�N�X������
			m_apDome[i]->BindTexture(NONE_IDX);
		}
	}
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CObjectMeshSphere::SetColor(const D3DXCOLOR& rCol)
{
	for (int i = 0; i < DOME_MAX; i++)
	{ // �����̑������J��Ԃ�

		// �����̐F��ݒ�
		m_apDome[i]->SetColor(rCol);
	}
}

//============================================================
//	���a�̐ݒ菈��
//============================================================
void CObjectMeshSphere::SetRadius(const float fRadius)
{
	for (int i = 0; i < DOME_MAX; i++)
	{ // �����̑������J��Ԃ�

		// �����̔��a��ݒ�
		m_apDome[i]->SetRadius(fRadius);
	}
}

//============================================================
//	�������̐ݒ菈��
//============================================================
HRESULT CObjectMeshSphere::SetPattern(const POSGRID2& rPart)
{
	for (int i = 0; i < DOME_MAX; i++)
	{ // �����̑������J��Ԃ�

		// �����̕�������ݒ�
		if (FAILED(m_apDome[i]->SetPattern(rPart)))
		{ // �ݒ�Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return S_OK;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�e�N�X�`���������̐ݒ菈��
//============================================================
void CObjectMeshSphere::SetTexPattern(const POSGRID2& rTexPart)
{
	if (rTexPart.x >= MIN_TEXPART.x
	&&  rTexPart.y >= MIN_TEXPART.y)
	{ // �e�N�X�`�����������Œ�l�ȏ�̏ꍇ

		for (int i = 0; i < DOME_MAX; i++)
		{ // �����̑������J��Ԃ�

			// �����̃e�N�X�`����������ݒ�
			m_apDome[i]->SetTexPattern(rTexPart);
		}
	}
	else { assert(false); }	// �Œ�l����
}
