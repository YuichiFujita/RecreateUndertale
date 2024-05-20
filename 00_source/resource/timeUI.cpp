//============================================================
//
//	�^�C��UI���� [timeUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "timeUI.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "timer.h"
#include "value.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// �e�N�X�`���t�@�C��
	{
		"data\\TEXTURE\\timePart000.png",	// �ʏ��؂�
	};

	const int PRIORITY = 6;	// �^�C��UI�̗D�揇��
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CValue::TYPE_MAX, "ERROR : Type Count Mismatch");

//************************************************************
//	�q�N���X [CTimeUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTimeUI::CTimeUI() : CObject(CObject::LABEL_UI, CObject::DIM_2D, PRIORITY),
	m_type			(CValue::TYPE_NORMAL),	// �������
	m_pos			(VEC3_ZERO),			// ���_�ʒu
	m_rot			(VEC3_ZERO),			// ���_����
	m_sizeValue		(VEC3_ZERO),			// �����̑傫��
	m_sizePart		(VEC3_ZERO),			// ��؂�̑傫��
	m_spaceValue	(VEC3_ZERO),			// �����̋�
	m_spacePart		(VEC3_ZERO),			// ��؂�̋�
	m_col			(XCOL_WHITE),			// �F
	m_alignX		(XALIGN_CENTER),		// ���z�u
	m_alignY		(YALIGN_CENTER),		// �c�z�u
	m_fTime			(0.0f)					// �\������
{
	// �����o�ϐ����N���A
	memset(&m_apValue[0], 0, sizeof(m_apValue));	// ���l�̏��
	memset(&m_apPart[0], 0, sizeof(m_apPart));		// ��؂�̏��
}

//============================================================
//	�f�X�g���N�^
//============================================================
CTimeUI::~CTimeUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTimeUI::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apValue[0], 0, sizeof(m_apValue));	// ���l�̏��
	memset(&m_apPart[0], 0, sizeof(m_apPart));		// ��؂�̏��
	m_type			= CValue::TYPE_NORMAL;			// �������
	m_pos			= VEC3_ZERO;		// ���_�ʒu
	m_rot			= VEC3_ZERO;		// ���_����
	m_sizeValue		= VEC3_ZERO;		// �����̑傫��
	m_sizePart		= VEC3_ZERO;		// ��؂�̑傫��
	m_spaceValue	= VEC3_ZERO;		// �����̋�
	m_spacePart		= VEC3_ZERO;		// ��؂�̋�
	m_col			= XCOL_WHITE;		// �F
	m_alignX		= XALIGN_CENTER;	// ���z�u
	m_alignY		= YALIGN_CENTER;	// �c�z�u
	m_fTime			= 0.0f;				// �\������

	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̐���
		m_apValue[nCntValue] = CValue::Create();
		if (m_apValue[nCntValue] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}
	}

	for (int nCntPart = 0; nCntPart < timeUI::MAX_PART; nCntPart++)
	{ // ��؂�̐����J��Ԃ�

		// ��؂�̐���
		m_apPart[nCntPart] = CObject2D::Create(VEC3_ZERO);
		if (m_apPart[nCntPart] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}
	}

	// �D�揇�ʂ̐ݒ�
	SetPriority(PRIORITY);

	// �X�V�󋵂̐ݒ�
	SetEnableUpdate(false);
	CObject::SetEnableUpdate(true);	// ���g��ON�ɂ���

	// �`��󋵂̐ݒ�
	SetEnableDraw(false);
	CObject::SetEnableDraw(true);	// ���g��ON�ɂ���

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CTimeUI::Uninit(void)
{
	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̏I��
		SAFE_UNINIT(m_apValue[nCntValue]);
	}

	for (int nCntPart = 0; nCntPart < timeUI::MAX_PART; nCntPart++)
	{ // ��؂�̐����J��Ԃ�

		// ��؂�̏I��
		SAFE_UNINIT(m_apPart[nCntPart]);
	}

	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CTimeUI::Update(const float fDeltaTime)
{
	// ���Έʒu�̐ݒ�
	SetPositionRelative();

	// �����̃e�N�X�`�����W�̐ݒ�
	SetTexNum();

	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̍X�V
		assert(m_apValue[nCntValue] != nullptr);
		m_apValue[nCntValue]->Update(fDeltaTime);
	}

	for (int nCntPart = 0; nCntPart < timeUI::MAX_PART; nCntPart++)
	{ // ��؂�̐����J��Ԃ�

		// ��؂�̍X�V
		assert(m_apPart[nCntPart] != nullptr);
		m_apPart[nCntPart]->Update(fDeltaTime);
	}
}

//============================================================
//	�`�揈��
//============================================================
void CTimeUI::Draw(CShader *pShader)
{
	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̍X�V
		assert(m_apValue[nCntValue] != nullptr);
		m_apValue[nCntValue]->Draw(pShader);
	}

	for (int nCntPart = 0; nCntPart < timeUI::MAX_PART; nCntPart++)
	{ // ��؂�̐����J��Ԃ�

		// ��؂�̍X�V
		assert(m_apPart[nCntPart] != nullptr);
		m_apPart[nCntPart]->Draw(pShader);
	}
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CTimeUI::SetPriority(const int nPriority)
{
	// ���g�̗D�揇�ʂ�ݒ�
	CObject::SetPriority(nPriority);

	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̗D�揇�ʂ�ݒ�
		assert(m_apValue[nCntValue] != nullptr);
		m_apValue[nCntValue]->SetPriority(nPriority);
	}

	for (int nCntPart = 0; nCntPart < timeUI::MAX_PART; nCntPart++)
	{ // ��؂�̐����J��Ԃ�

		// ��؂�̗D�揇�ʂ�ݒ�
		assert(m_apPart[nCntPart] != nullptr);
		m_apPart[nCntPart]->SetPriority(nPriority);
	}
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CTimeUI::SetEnableUpdate(const bool bUpdate)
{
	// ���g�̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);

	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̍X�V�󋵂�ݒ�
		assert(m_apValue[nCntValue] != nullptr);
		m_apValue[nCntValue]->SetEnableUpdate(bUpdate);
	}

	for (int nCntPart = 0; nCntPart < timeUI::MAX_PART; nCntPart++)
	{ // ��؂�̐����J��Ԃ�

		// ��؂�̍X�V�󋵂�ݒ�
		assert(m_apPart[nCntPart] != nullptr);
		m_apPart[nCntPart]->SetEnableUpdate(bUpdate);
	}
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CTimeUI::SetEnableDraw(const bool bDraw)
{
	// ���g�̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);

	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̕`��󋵂�ݒ�
		assert(m_apValue[nCntValue] != nullptr);
		m_apValue[nCntValue]->SetEnableDraw(bDraw);
	}

	for (int nCntPart = 0; nCntPart < timeUI::MAX_PART; nCntPart++)
	{ // ��؂�̐����J��Ԃ�

		// ��؂�̕`��󋵂�ݒ�
		assert(m_apPart[nCntPart] != nullptr);
		m_apPart[nCntPart]->SetEnableDraw(bDraw);
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CTimeUI::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CTimeUI::SetVec3Rotation(const D3DXVECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_rot = rRot;

	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̌�����ݒ�
		assert(m_apValue[nCntValue] != nullptr);
		m_apValue[nCntValue]->SetVec3Rotation(rRot);
	}

	for (int nCntPart = 0; nCntPart < timeUI::MAX_PART; nCntPart++)
	{ // ��؂�̐����J��Ԃ�

		// ��؂�̌�����ݒ�
		assert(m_apPart[nCntPart] != nullptr);
		m_apPart[nCntPart]->SetVec3Rotation(rRot);
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	��������
//============================================================
CTimeUI *CTimeUI::Create
(
	const float fTime,				// �\������
	const D3DXVECTOR3& rPos,		// �ʒu
	const D3DXVECTOR3& rSizeValue,	// �����̑傫��
	const D3DXVECTOR3& rSizePart,	// ��؂�̑傫��
	const D3DXVECTOR3& rSpaceValue,	// �����̋�
	const D3DXVECTOR3& rSpacePart,	// ��؂�̋�
	const CValue::EType type,		// �������
	const EAlignX alignX,			// ���z�u
	const EAlignY alignY,			// �c�z�u
	const D3DXVECTOR3& rRot,		// ����
	const D3DXCOLOR& rCol			// �F
)
{
	// �^�C��UI�̐���
	CTimeUI *pTimeUI = new CTimeUI;
	if (pTimeUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �^�C��UI�̏�����
		if (FAILED(pTimeUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �^�C��UI�̔j��
			SAFE_DELETE(pTimeUI);
			return nullptr;
		}

		// �\�����Ԃ�ݒ�
		pTimeUI->SetTime(fTime);

		// ������ނ�ݒ�
		pTimeUI->SetValueType(type);

		// ���_�ʒu��ݒ�
		pTimeUI->SetVec3Position(rPos);

		// ���_������ݒ�
		pTimeUI->SetVec3Rotation(rRot);

		// �����̑傫����ݒ�
		pTimeUI->SetSizingValue(rSizeValue);

		// ��؂�̑傫����ݒ�
		pTimeUI->SetSizingPart(rSizePart);

		// �����̋󔒂�ݒ�
		pTimeUI->SetSpaceValue(rSpaceValue);

		// ��؂�̋󔒂�ݒ�
		pTimeUI->SetSpacePart(rSpacePart);

		// �F��ݒ�
		pTimeUI->SetColor(rCol);

		// ���z�u��ݒ�
		pTimeUI->SetAlignX(alignX);

		// �c�z�u��ݒ�
		pTimeUI->SetAlignY(alignY);

		// �m�ۂ����A�h���X��Ԃ�
		return pTimeUI;
	}
}

//============================================================
//	�\�����Ԃ̐ݒ菈��
//============================================================
void CTimeUI::SetTime(const float fTime)
{
	// �����̕\�����Ԃ�ݒ�
	m_fTime = fTime;

	// �\�����Ԃ̕␳
	useful::LimitNum(m_fTime, timer::TIME_MIN, timer::TIME_MAX);
}

//============================================================
//	�����̎�ނ̐ݒ菈��
//============================================================
void CTimeUI::SetValueType(const CValue::EType type)
{
	// �ݒ肳�ꂽ�����̎�ނ�ۑ�
	m_type = type;

	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̎�ނ�ݒ�
		assert(m_apValue[nCntValue] != nullptr);
		m_apValue[nCntValue]->SetType(type);
	}

	for (int nCntPart = 0; nCntPart < timeUI::MAX_PART; nCntPart++)
	{ // ��؂�̐����J��Ԃ�

		// �e�N�X�`��������
		assert(m_apPart[nCntPart] != nullptr);
		m_apPart[nCntPart]->BindTexture(TEXTURE_FILE[(int)type]);
	}
}

//============================================================
//	�����̑傫���̐ݒ菈��
//============================================================
void CTimeUI::SetSizingValue(const D3DXVECTOR3& rSize)
{
	// �ݒ肳�ꂽ�����̑傫����ۑ�
	m_sizeValue = rSize;

	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̑傫����ݒ�
		assert(m_apValue[nCntValue] != nullptr);
		m_apValue[nCntValue]->SetVec3Sizing(rSize);
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	��؂�̑傫���̐ݒ菈��
//============================================================
void CTimeUI::SetSizingPart(const D3DXVECTOR3& rSize)
{
	// �ݒ肳�ꂽ��؂�̑傫����ۑ�
	m_sizePart = rSize;

	for (int nCntPart = 0; nCntPart < timeUI::MAX_PART; nCntPart++)
	{ // ��؂�̐����J��Ԃ�

		// ��؂�̑傫����ݒ�
		assert(m_apPart[nCntPart] != nullptr);
		m_apPart[nCntPart]->SetVec3Sizing(rSize);
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̋󔒂̐ݒ菈��
//============================================================
void CTimeUI::SetSpaceValue(const D3DXVECTOR3& rSpace)
{
	// �����̐����̋󔒂�ݒ�
	m_spaceValue = rSpace;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	��؂�̋󔒂̐ݒ菈��
//============================================================
void CTimeUI::SetSpacePart(const D3DXVECTOR3& rSpace)
{
	// �����̋�؂�̋󔒂�ݒ�
	m_spacePart = rSpace;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CTimeUI::SetColor(const D3DXCOLOR& rCol)
{
	// �ݒ肳�ꂽ�F��ۑ�
	m_col = rCol;

	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̐F��ݒ�
		assert(m_apValue[nCntValue] != nullptr);
		m_apValue[nCntValue]->SetColor(rCol);
	}

	for (int nCntPart = 0; nCntPart < timeUI::MAX_PART; nCntPart++)
	{ // ��؂�̐����J��Ԃ�

		// ��؂�̐F��ݒ�
		assert(m_apPart[nCntPart] != nullptr);
		m_apPart[nCntPart]->SetColor(rCol);
	}
}

//============================================================
//	���z�u�̐ݒ菈��
//============================================================
void CTimeUI::SetAlignX(const EAlignX align)
{
	// �����̉��z�u��ݒ�
	m_alignX = align;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�c�z�u�̐ݒ菈��
//============================================================
void CTimeUI::SetAlignY(const EAlignY align)
{
	// �����̏c�z�u��ݒ�
	m_alignY = align;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�^�C���S�̂̉����擾����
//============================================================
float CTimeUI::GetTimeWidth(void) const
{
	float fTimeWidth = 0.0f;				// �^�C���S�̂̉���
	int nEndNumID = timeUI::MAX_DIGIT - 1;	// �I�[�����̃C���f�b�N�X

	// �S�Ă̋󔒂����Z (�Ō�̕����͊܂܂Ȃ�)
	fTimeWidth += m_spaceValue.x * nEndNumID;
	fTimeWidth += m_spacePart.x * timeUI::MAX_PART;

	// �擪�����̉��������Z
	assert(m_apValue[0] != nullptr);
	fTimeWidth += m_apValue[0]->GetVec3Sizing().x * 0.5f;

	// �I�[�����̉��������Z
	assert(m_apValue[nEndNumID] != nullptr);
	fTimeWidth += m_apValue[nEndNumID]->GetVec3Sizing().x * 0.5f;

	// �^�C���S�̂̉�����Ԃ�
	return fTimeWidth;
}

//============================================================
//	�^�C���S�̂̏c���擾����
//============================================================
float CTimeUI::GetTimeHeight(void) const
{
	float fTimeHeight = 0.0f;				// �^�C���S�̂̏c��
	int nEndNumID = timeUI::MAX_DIGIT - 1;	// �I�[�����̃C���f�b�N�X

	// �S�Ă̋󔒂����Z (�Ō�̕����͊܂܂Ȃ�)
	fTimeHeight += m_spaceValue.y * nEndNumID;
	fTimeHeight += m_spacePart.y * timeUI::MAX_PART;

	// �擪�����̏c�������Z
	assert(m_apValue[0] != nullptr);
	fTimeHeight += m_apValue[0]->GetVec3Sizing().y * 0.5f;

	// �I�[�����̏c�������Z
	assert(m_apValue[nEndNumID] != nullptr);
	fTimeHeight += m_apValue[nEndNumID]->GetVec3Sizing().y * 0.5f;

	// �^�C���S�̂̏c����Ԃ�
	return fTimeHeight;
}

//============================================================
//	�����S�̂̑傫���擾����
//============================================================
D3DXVECTOR3 CTimeUI::GetTimeSize(void) const
{
	// �����S�̂̑傫����Ԃ�
	return D3DXVECTOR3(GetTimeWidth(), GetTimeHeight(), 0.0f);
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CTimeUI::SetPositionRelative(void)
{
	int nValueID = 0;	// �����̐�����
	int nPartID = 0;	// ��؂�̐�����
	D3DXVECTOR3 spaceValue = m_spaceValue * 0.5f;	// �����̋�
	D3DXVECTOR3 spacePart = m_spacePart * 0.5f;		// ��؂�̋�
	D3DXVECTOR3 sizeTime = GetTimeSize() * 0.5f;	// �^�C���S�̂̑傫��
	D3DXVECTOR3 sizeHead = m_apValue[0]->GetVec3Sizing() * 0.5f;	// �擪�����̑傫��
	D3DXVECTOR3 rotStart = D3DXVECTOR3(m_rot.z + HALF_PI, m_rot.z, 0.0f);	// �����̊J�n����

	D3DXVECTOR3 posOffset = VEC3_ZERO;	// �����̊J�n�I�t�Z�b�g
	posOffset.x = -sizeTime.x - spaceValue.x + sizeHead.x - (sizeTime.x * (m_alignX - 1));	// �J�n�I�t�Z�b�gX
	posOffset.y = -sizeTime.y - spaceValue.y + sizeHead.y - (sizeTime.y * (m_alignY - 1));	// �J�n�I�t�Z�b�gY

	D3DXVECTOR3 posStart = VEC3_ZERO;	// �����̊J�n�ʒu
	posStart.x = m_pos.x + sinf(rotStart.x) * posOffset.x + sinf(rotStart.y) * posOffset.y;	// �J�n�ʒuX
	posStart.y = m_pos.y + cosf(rotStart.x) * posOffset.x + cosf(rotStart.y) * posOffset.y;	// �J�n�ʒuY

	for (int nCntTimer = 0; nCntTimer < timeUI::MAX_DIGIT + timeUI::MAX_PART; nCntTimer++)
	{ // �����̐� + ��؂�̐����J��Ԃ�

		if (nCntTimer == timeUI::MAX_MIN || nCntTimer == timeUI::MAX_MIN + timeUI::MAX_SEC + 1)
		{ // ��؂�^�C�~���O�̏ꍇ

			assert(m_apPart[nValueID] != nullptr);

			// �|���S�������ʒu�����炷
			posStart.x += sinf(rotStart.x) * spacePart.x + sinf(rotStart.y) * spacePart.y;
			posStart.y += cosf(rotStart.x) * spacePart.x + cosf(rotStart.y) * spacePart.y;

			// ��؂�̈ʒu��ݒ�
			m_apPart[nValueID]->SetVec3Position(posStart);

			// �|���S�������ʒu�����炷
			posStart.x += sinf(rotStart.x) * spacePart.x + sinf(rotStart.y) * spacePart.y;
			posStart.y += cosf(rotStart.x) * spacePart.x + cosf(rotStart.y) * spacePart.y;

			// ��؂�̐����������Z
			nValueID++;
		}
		else
		{ // �����^�C�~���O�̏ꍇ

			assert(m_apValue[nPartID] != nullptr);

			// �|���S�������ʒu�����炷
			posStart.x += sinf(rotStart.x) * spaceValue.x + sinf(rotStart.y) * spaceValue.y;
			posStart.y += cosf(rotStart.x) * spaceValue.x + cosf(rotStart.y) * spaceValue.y;

			// �����̈ʒu��ݒ�
			m_apValue[nPartID]->SetVec3Position(posStart);

			// �|���S�������ʒu�����炷
			posStart.x += sinf(rotStart.x) * spaceValue.x + sinf(rotStart.y) * spaceValue.y;
			posStart.y += cosf(rotStart.x) * spaceValue.x + cosf(rotStart.y) * spaceValue.y;

			// �����̐����������Z
			nPartID++;
		}
	}
}

//============================================================
//	�����̃e�N�X�`�����W�̐ݒ菈��
//============================================================
void CTimeUI::SetTexNum(void)
{
	int aNumDivide[timeUI::MAX_DIGIT];	// ���l����p

	// �����������Ƃɕ���
	useful::DivideDigitNum(&aNumDivide[0], GetMin(), timeUI::MAX_MIN);

	// �b���������Ƃɕ���
	useful::DivideDigitNum(&aNumDivide[timeUI::MAX_MIN], GetSec(), timeUI::MAX_SEC);

	// �~���b���������Ƃɕ���
	useful::DivideDigitNum(&aNumDivide[timeUI::MAX_MIN + timeUI::MAX_SEC], GetMSec(), timeUI::MAX_MSEC);

	for (int nCntValue = 0; nCntValue < timeUI::MAX_DIGIT; nCntValue++)
	{ // �����̐����J��Ԃ�

		// �����̐ݒ�
		m_apValue[nCntValue]->SetNumber(aNumDivide[nCntValue]);
	}
}
