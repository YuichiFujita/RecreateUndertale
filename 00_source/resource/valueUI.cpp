//============================================================
//
//	����UI���� [valueUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "valueUI.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"
#include "multiValue.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// ����UI�\���̗D�揇��
}

//************************************************************
//	�q�N���X [CValueUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CValueUI::CValueUI() : CObject(CObject::LABEL_NONE, CObject::DIM_2D, PRIORITY),
	m_pTitle	(nullptr),		// �^�C�g�����
	m_pValue	(nullptr),		// �������
	m_pos		(VEC3_ZERO),	// �ʒu
	m_space		(VEC3_ZERO)		// �s��
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CValueUI::~CValueUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CValueUI::Init(void)
{
	// �����o�ϐ���������
	m_pTitle	= nullptr;		// �^�C�g�����
	m_pValue	= nullptr;		// �������
	m_pos		= VEC3_ZERO;	// �ʒu
	m_space		= VEC3_ZERO;	// �s��

	// �^�C�g�����̐���
	m_pTitle = CObject2D::Create(VEC3_ZERO);
	if (m_pTitle == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pTitle->SetPriority(PRIORITY);

	// �������̐���
	m_pValue = CMultiValue::Create
	( // ����
		CValue::TYPE_NORMAL,	// �������
		0,			// ����
		1,			// ����
		VEC3_ZERO,	// �ʒu
		VEC3_ONE,	// �傫��
		VEC3_ZERO	// ���
	);
	if (m_pValue == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pValue->SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CValueUI::Uninit(void)
{
	// �^�C�g�����̏I��
	SAFE_UNINIT(m_pTitle);

	// ���g�̃I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CValueUI::Update(const float fDeltaTime)
{
	// �^�C�g�����̍X�V
	m_pTitle->Update(fDeltaTime);

	// �������̍X�V
	m_pValue->Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CValueUI::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CValueUI::SetPriority(const int nPriority)
{
	// �����̗D�揇�ʂ�ݒ�
	CObject::SetPriority(nPriority);	// ���g
	m_pTitle->SetPriority(nPriority);	// �^�C�g�����
	m_pValue->SetPriority(nPriority);	// �������
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CValueUI::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);	// ���g
	m_pTitle->SetEnableDraw(bDraw);	// �^�C�g�����
	m_pValue->SetEnableDraw(bDraw);	// �������
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CValueUI::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�������� (�e�N�X�`���w��Ȃ�)
//============================================================
CValueUI *CValueUI::Create
(
	const CValue::EType type,		// �������
	const int nDigit,				// ����
	const D3DXVECTOR3& rPos,		// �ʒu
	const D3DXVECTOR3& rSpace,		// �s��
	const D3DXVECTOR3& rSpaceValue,	// �����s��
	const D3DXVECTOR3& rSizeTitle,	// �^�C�g���傫��
	const D3DXVECTOR3& rSizeValue,	// �����傫��
	const D3DXVECTOR3& rRotTitle,	// �^�C�g������
	const D3DXVECTOR3& rRotValue,	// ��������
	const D3DXCOLOR& rColTitle,		// �^�C�g���F
	const D3DXCOLOR& rColValue		// �����F
)
{
	// ����UI�̐���
	CValueUI *pValueUI = new CValueUI;
	if (pValueUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		CMultiValue *pMultiModel = pValueUI->GetMultiValue();	// �����I�u�W�F�N�g

		// ����UI�̏�����
		if (FAILED(pValueUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ����UI�̔j��
			SAFE_DELETE(pValueUI);
			return nullptr;
		}

		// �����̌�����ݒ�
		pMultiModel->SetDigit(nDigit);

		// �����e�N�X�`����ݒ�
		pMultiModel->SetType(type);

		// �^�C�g��������ݒ�
		pValueUI->SetRotationTitle(rRotTitle);

		// ����������ݒ�
		pMultiModel->SetVec3Rotation(rRotValue);

		// �^�C�g���傫����ݒ�
		pValueUI->SetSizingTitle(rSizeTitle);

		// �����傫����ݒ�
		pMultiModel->SetVec3Sizing(rSizeValue);

		// �^�C�g���F��ݒ�
		pValueUI->SetColorTitle(rColTitle);

		// �����F��ݒ�
		pMultiModel->SetColor(rColValue);

		// �����̍s�Ԃ�ݒ�
		pMultiModel->SetSpace(rSpaceValue);

		// �s�Ԃ�ݒ�
		pValueUI->SetSpace(rSpace);

		// �ʒu��ݒ�
		pValueUI->SetVec3Position(rPos);

		// �m�ۂ����A�h���X��Ԃ�
		return pValueUI;
	}
}

//============================================================
//	�������� (�e�N�X�`���C���f�b�N�X�w��)
//============================================================
CValueUI *CValueUI::Create
(
	const int nTextureID,			// �^�C�g���e�N�X�`���C���f�b�N�X
	const CValue::EType type,		// �������
	const int nDigit,				// ����
	const D3DXVECTOR3& rPos,		// �ʒu
	const D3DXVECTOR3& rSpace,		// �s��
	const D3DXVECTOR3& rSpaceValue,	// �����s��
	const D3DXVECTOR3& rSizeTitle,	// �^�C�g���傫��
	const D3DXVECTOR3& rSizeValue,	// �����傫��
	const D3DXVECTOR3& rRotTitle,	// �^�C�g������
	const D3DXVECTOR3& rRotValue,	// ��������
	const D3DXCOLOR& rColTitle,		// �^�C�g���F
	const D3DXCOLOR& rColValue		// �����F
)
{
	// ����UI�̐���
	CValueUI *pValueUI = CValueUI::Create
	( // ����
		type,			// �������
		nDigit,			// ����
		rPos,			// �ʒu
		rSpace,			// �s��
		rSpaceValue,	// �����s��
		rSizeTitle,		// �^�C�g���傫��
		rSizeValue,		// �����傫��
		rRotTitle,		// �^�C�g������
		rRotValue,		// ��������
		rColTitle,		// �^�C�g���F
		rColValue		// �����F
	);
	if (pValueUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �e�N�X�`��������
		pValueUI->BindTextureTitle(nTextureID);

		// �m�ۂ����A�h���X��Ԃ�
		return pValueUI;
	}
}

//============================================================
//	�������� (�e�N�X�`���p�X�w��)
//============================================================
CValueUI *CValueUI::Create
(
	const char *pTexturePass,		// �^�C�g���e�N�X�`���p�X
	const CValue::EType type,		// �������
	const int nDigit,				// ����
	const D3DXVECTOR3& rPos,		// �ʒu
	const D3DXVECTOR3& rSpace,		// �s��
	const D3DXVECTOR3& rSpaceValue,	// �����s��
	const D3DXVECTOR3& rSizeTitle,	// �^�C�g���傫��
	const D3DXVECTOR3& rSizeValue,	// �����傫��
	const D3DXVECTOR3& rRotTitle,	// �^�C�g������
	const D3DXVECTOR3& rRotValue,	// ��������
	const D3DXCOLOR& rColTitle,		// �^�C�g���F
	const D3DXCOLOR& rColValue		// �����F
)
{
	// ����UI�̐���
	CValueUI *pValueUI = CValueUI::Create
	( // ����
		type,			// �������
		nDigit,			// ����
		rPos,			// �ʒu
		rSpace,			// �s��
		rSpaceValue,	// �����s��
		rSizeTitle,		// �^�C�g���傫��
		rSizeValue,		// �����傫��
		rRotTitle,		// �^�C�g������
		rRotValue,		// ��������
		rColTitle,		// �^�C�g���F
		rColValue		// �����F
	);
	if (pValueUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �e�N�X�`��������
		pValueUI->BindTextureTitle(pTexturePass);

		// �m�ۂ����A�h���X��Ԃ�
		return pValueUI;
	}
}

//============================================================
//	�s�Ԃ̐ݒ菈��
//============================================================
void CValueUI::SetSpace(const D3DXVECTOR3& rSpace)
{
	// �����̍s�Ԃ�ݒ�
	m_space = rSpace;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�^�C�g���̃e�N�X�`���������� (�C���f�b�N�X)
//============================================================
void CValueUI::BindTextureTitle(const int nTextureID)
{
	if (nTextureID >= NONE_IDX)
	{ // �e�N�X�`���C���f�b�N�X���g�p�\�ȏꍇ

		// �e�N�X�`���C���f�b�N�X����
		m_pTitle->BindTexture(nTextureID);
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	�^�C�g���̃e�N�X�`���������� (�p�X)
//============================================================
void CValueUI::BindTextureTitle(const char *pTexturePass)
{
	// �|�C���^��錾
	CTexture *pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	if (pTexturePass != nullptr)
	{ // ���蓖�Ă�e�N�X�`���p�X������ꍇ

		// �e�N�X�`���C���f�b�N�X��ݒ�
		m_pTitle->BindTexture(pTexture->Regist(pTexturePass));
	}
	else
	{ // ���蓖�Ă�e�N�X�`���p�X���Ȃ��ꍇ

		// �e�N�X�`���Ȃ��C���f�b�N�X��ݒ�
		m_pTitle->BindTexture(NONE_IDX);
	}
}

//============================================================
//	�^�C�g�������̐ݒ菈��
//============================================================
void CValueUI::SetRotationTitle(const D3DXVECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_pTitle->SetVec3Rotation(rRot);
}

//============================================================
//	�^�C�g���傫���̐ݒ菈��
//============================================================
void CValueUI::SetSizingTitle(const D3DXVECTOR3& rSize)
{
	// �����̑傫����ݒ�
	m_pTitle->SetVec3Sizing(rSize);
}

//============================================================
//	�^�C�g���F�̐ݒ菈��
//============================================================
void CValueUI::SetColorTitle(const D3DXCOLOR& rCol)
{
	// �����̐F��ݒ�
	m_pTitle->SetColor(rCol);
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CValueUI::SetPositionRelative(void)
{
	// �^�C�g���̈ʒu��ݒ�
	m_pTitle->SetVec3Position(m_pos);

	// �����̈ʒu��ݒ�
	m_pValue->SetVec3Position(m_pTitle->GetVec3Position() + m_space);
}
