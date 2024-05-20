//============================================================
//
//	�}���`�������� [multiValue.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "multiValue.h"
#include "manager.h"
#include "renderer.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// �}���`�����̗D�揇��
}

//************************************************************
//	�q�N���X [CMultiValue] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CMultiValue::CMultiValue() : CObject(CObject::LABEL_UI, CObject::DIM_2D, object::DEFAULT_PRIO),
	m_pos		(VEC3_ZERO),		// ���_�ʒu
	m_rot		(VEC3_ZERO),		// ���_����
	m_size		(VEC3_ZERO),		// �傫��
	m_space		(VEC3_ZERO),		// ��
	m_col		(XCOL_WHITE),		// �F
	m_alignX	(XALIGN_CENTER),	// ���z�u
	m_alignY	(YALIGN_CENTER),	// �c�z�u
	m_nNum		(0),				// ����
	m_nMin		(0),				// �ŏ��l
	m_nMax		(0)					// �ő�l
{
	// �������X�g���N���A
	m_listValue.clear();
}

//============================================================
//	�f�X�g���N�^
//============================================================
CMultiValue::~CMultiValue()
{

}

//============================================================
//	����������
//============================================================
HRESULT CMultiValue::Init(void)
{
	// �����o�ϐ���������
	m_pos		= VEC3_ZERO;		// ���_�ʒu
	m_rot		= VEC3_ZERO;		// ���_����
	m_size		= VEC3_ZERO;		// �傫��
	m_space		= VEC3_ZERO;		// ��
	m_col		= XCOL_WHITE;		// �F
	m_alignX	= XALIGN_CENTER;	// ���z�u
	m_alignY	= YALIGN_CENTER;	// �c�z�u
	m_nNum		= 0;				// ����
	m_nMin		= 0;				// �ŏ��l
	m_nMax		= 0;				// �ő�l

	// �������X�g��������
	m_listValue.clear();

	// �D�揇�ʂ�ݒ�
	SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CMultiValue::Uninit(void)
{
	for (auto& rList : m_listValue)
	{ // �����̌������J��Ԃ�

		// �����̏I��
		SAFE_UNINIT(rList);
	}

	// �������X�g���N���A
	m_listValue.clear();

	// ���g�̃I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CMultiValue::Update(const float fDeltaTime)
{
	for (auto& rList : m_listValue)
	{ // �����̌������J��Ԃ�

		// �����̍X�V
		assert(rList != nullptr);
		rList->Update(fDeltaTime);
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�`�揈��
//============================================================
void CMultiValue::Draw(CShader *pShader)
{
	for (auto& rList : m_listValue)
	{ // �����̌������J��Ԃ�

		// �����̕`��
		assert(rList != nullptr);
		rList->Draw(pShader);
	}
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CMultiValue::SetPriority(const int nPriority)
{
	// �����̗D�揇�ʂ�ݒ�
	CObject::SetPriority(nPriority);	// ���g
	for (auto& rList : m_listValue)
	{ // �����̌������J��Ԃ�

		// �����̗D�揇�ʂ̐ݒ�
		assert(rList != nullptr);
		rList->SetPriority(nPriority);
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CMultiValue::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CMultiValue::SetVec3Rotation(const D3DXVECTOR3& rRot)
{
	// �ݒ肷�������ۑ�
	m_rot = rRot;

	for (auto& rList : m_listValue)
	{ // �����̌������J��Ԃ�

		// ���������̐ݒ�
		assert(rList != nullptr);
		rList->SetVec3Rotation(rRot);
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CMultiValue::SetVec3Sizing(const D3DXVECTOR3& rSize)
{
	// �ݒ肷��傫����ۑ�
	m_size = rSize;

	for (auto& rList : m_listValue)
	{ // �����̌������J��Ԃ�

		// �����傫���̐ݒ�
		assert(rList != nullptr);
		rList->SetVec3Sizing(rSize);
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	��������
//============================================================
CMultiValue *CMultiValue::Create
(
	const CValue::EType type,	// �������
	const int nNum,				// ����
	const int nDigit,			// ����
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rSize,	// �傫��
	const D3DXVECTOR3& rSpace,	// ��
	const EAlignX alignX,		// ���z�u
	const EAlignY alignY,		// �c�z�u
	const D3DXVECTOR3& rRot,	// ����
	const D3DXCOLOR& rCol		// �F
)
{
	// �}���`�����̐���
	CMultiValue *pMultiValue = new CMultiValue;
	if (pMultiValue == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �}���`�����̏�����
		if (FAILED(pMultiValue->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �}���`�����̔j��
			SAFE_DELETE(pMultiValue);
			return nullptr;
		}

		// ������ݒ�
		if (FAILED(pMultiValue->SetDigit(nDigit)))
		{ // �ݒ�Ɏ��s�����ꍇ

			// �}���`�����̔j��
			SAFE_DELETE(pMultiValue);
			return nullptr;
		}

		// ������ݒ�
		pMultiValue->SetNum(nNum);

		// ������ނ�ݒ�
		pMultiValue->SetType(type);

		// �ʒu��ݒ�
		pMultiValue->SetVec3Position(rPos);

		// ������ݒ�
		pMultiValue->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pMultiValue->SetVec3Sizing(rSize);

		// �F��ݒ�
		pMultiValue->SetColor(rCol);

		// �󔒂�ݒ�
		pMultiValue->SetSpace(rSpace);

		// ���z�u��ݒ�
		pMultiValue->SetAlignX(alignX);

		// �c�z�u��ݒ�
		pMultiValue->SetAlignY(alignY);

		// �m�ۂ����A�h���X��Ԃ�
		return pMultiValue;
	}
}

//============================================================
//	���l�̉��Z����
//============================================================
void CMultiValue::AddNum(const int nNum)
{
	// ���������������Z
	m_nNum += nNum;

	// �����̕␳
	useful::LimitNum(m_nNum, m_nMin, m_nMax);

	// �����̃e�N�X�`�����W�̐ݒ�
	SetTexNum();
}

//============================================================
//	���l�̐ݒ菈��
//============================================================
void CMultiValue::SetNum(const int nNum)
{
	// �����������̒l�ɐݒ�
	m_nNum = nNum;

	// �����̕␳
	useful::LimitNum(m_nNum, m_nMin, m_nMax);

	// �����̃e�N�X�`�����W�̐ݒ�
	SetTexNum();
}

//============================================================
//	�ŏ��l�̐ݒ菈��
//============================================================
void CMultiValue::SetMin(const int nMin)
{
	// ��O����
	assert(nMin >= 0 && nMin <= m_nMax);

	// �����̍ŏ��l��ݒ�
	m_nMin = nMin;

	// �����̕␳
	useful::LimitNum(m_nNum, m_nMin, m_nMax);
}

//============================================================
//	�ő�l�̐ݒ菈��
//============================================================
void CMultiValue::SetMax(const int nMax)
{
#if _DEBUG	// �ő�l�����K���`�F�b�N

	int nLimit = 1;	// �ő�l�̌v�Z�p
	int nDigit = (int)m_listValue.size();	// ����
	for (int i = 0; i < nDigit; i++)
	{ // �����̌������J��Ԃ�

		// �����𑝂₷
		nLimit *= 10;
	}

	// ��O����
	assert(nMax <= nLimit - 1 && nMax >= m_nMin);

#endif	// _DEBUG

	// �����̍ő�l��ݒ�
	m_nMax = nMax;

	// �����̕␳
	useful::LimitNum(m_nNum, m_nMin, m_nMax);
}

//============================================================
//	�����̐ݒ菈��
//============================================================
HRESULT CMultiValue::SetDigit(const int nDigit)
{
	//--------------------------------------------------------
	//	�����I�u�W�F�N�g�̔j���E����
	//--------------------------------------------------------
	// �����I�u�W�F�N�g�̔j��
	for (auto& rList : m_listValue)
	{ // �����̌������J��Ԃ�

		// �����̏I��
		SAFE_UNINIT(rList);
	}

	// �������X�g���N���A
	m_listValue.clear();

	// �����I�u�W�F�N�g�̐���
	for (int nCntValue = 0; nCntValue < nDigit; nCntValue++)
	{ // �������J��Ԃ�

		// �����̐���
		CValue *pValue = CValue::Create(CValue::TYPE_NORMAL);
		if (pValue == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �����X�V�E�����`���OFF�ɂ���
		pValue->SetEnableUpdate(false);
		pValue->SetEnableDraw(false);

		// ���X�g�ɐ����I�u�W�F�N�g��ǉ�
		m_listValue.push_back(pValue);
	}

	//--------------------------------------------------------
	//	��{���̍Đݒ�
	//--------------------------------------------------------
	// ������ݒ�
	SetVec3Rotation(m_rot);

	// �傫����ݒ�
	SetVec3Sizing(m_size);

	// �F��ݒ�
	SetColor(m_col);

	//--------------------------------------------------------
	//	�����l�̐ݒ�
	//--------------------------------------------------------
	int nLimit = 1;	// �ő�l�̌v�Z�p
	for (int i = 0; i < nDigit; i++)
	{ // �����̌������J��Ԃ�

		// �����𑝂₷
		nLimit *= 10;
	}

	// �ŏ��l�̐ݒ�
	SetMin(0);

	// �ő�l�̐ݒ�
	SetMax(nLimit - 1);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	���z�u�̐ݒ菈��
//============================================================
void CMultiValue::SetAlignX(const EAlignX align)
{
	// �����̉��z�u��ݒ�
	m_alignX = align;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�c�z�u�̐ݒ菈��
//============================================================
void CMultiValue::SetAlignY(const EAlignY align)
{
	// �����̏c�z�u��ݒ�
	m_alignY = align;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	��ނ̐ݒ菈��
//============================================================
void CMultiValue::SetType(const CValue::EType type)
{
	for (auto& rList : m_listValue)
	{ // �����̌������J��Ԃ�

		// ������ނ̐ݒ�
		assert(rList != nullptr);
		rList->SetType(type);
	}
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CMultiValue::SetColor(const D3DXCOLOR& rCol)
{
	// �ݒ肷��F��ۑ�
	m_col = rCol;

	for (auto& rList : m_listValue)
	{ // �����̌������J��Ԃ�

		// �����F�̐ݒ�
		assert(rList != nullptr);
		rList->SetColor(rCol);
	}
}

//============================================================
//	�󔒂̐ݒ菈��
//============================================================
void CMultiValue::SetSpace(const D3DXVECTOR3& rSpace)
{
	// �����̋󔒂�ݒ�
	m_space = rSpace;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����S�̂̉����擾����
//============================================================
float CMultiValue::GetValueWidth(void) const
{
	// �������Ȃ��ꍇ������
	if ((int)m_listValue.size() <= 0) { assert(false); return 0.0f; }

	float fValueWidth = 0.0f;	// �����S�̂̏c��
	int nEndNumID = (int)m_listValue.size() - 1;	// �I�[�����̃C���f�b�N�X
	for (int i = 0; i < nEndNumID; i++)
	{ // �I�[�����𔲂����������J��Ԃ�

		// ���̐����܂ł̗�Ԃ����Z
		fValueWidth += m_space.x;
	}

	// �擪�ƏI�[�̐����̖������ꂽ�T�C�Y�����Z
	fValueWidth += m_listValue.front()->GetVec3Sizing().x * 0.5f;	// �擪�����̌��_���T�C�Y
	fValueWidth += m_listValue.back()->GetVec3Sizing().x * 0.5f;	// �I�[�����̌��_�E�T�C�Y

	// �����S�̂̏c����Ԃ�
	return fValueWidth;
}

//============================================================
//	�����S�̂̏c���擾����
//============================================================
float CMultiValue::GetValueHeight(void) const
{
	// �������Ȃ��ꍇ������
	if ((int)m_listValue.size() <= 0) { assert(false); return 0.0f; }

	float fValueHeight = 0.0f;	// �����S�̂̏c��
	int nEndNumID = (int)m_listValue.size() - 1;	// �I�[�����̃C���f�b�N�X
	for (int i = 0; i < nEndNumID; i++)
	{ // �I�[�����𔲂����������J��Ԃ�

		// ���̐����܂ł̍s�Ԃ����Z
		fValueHeight += m_space.y;
	}

	// �擪�ƏI�[�̐����̖������ꂽ�T�C�Y�����Z
	fValueHeight += m_listValue.front()->GetVec3Sizing().y * 0.5f;	// �擪�����̌��_��T�C�Y
	fValueHeight += m_listValue.back()->GetVec3Sizing().y * 0.5f;	// �I�[�����̌��_���T�C�Y

	// �����S�̂̏c����Ԃ�
	return fValueHeight;
}

//============================================================
//	�����S�̂̑傫���擾����
//============================================================
D3DXVECTOR3 CMultiValue::GetValueSize(void) const
{
	// �������Ȃ��ꍇ������
	if ((int)m_listValue.size() <= 0) { assert(false); return VEC3_ZERO; }

	// �����S�̂̑傫����Ԃ�
	return D3DXVECTOR3(GetValueWidth(), GetValueHeight(), 0.0f);
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CMultiValue::SetPositionRelative(void)
{
	// �������Ȃ��ꍇ������
	if ((int)m_listValue.size() <= 0) { return; }

	D3DXVECTOR3 sizeValue	= GetValueSize() * 0.5f;	// �����S�̂̑傫��
	D3DXVECTOR3 sizeHead	= m_listValue.front()->GetVec3Sizing() * 0.5f;		// �擪�����̑傫��
	D3DXVECTOR3 rotStart	= D3DXVECTOR3(m_rot.z + HALF_PI, m_rot.z, 0.0f);	// �����̊J�n����

	D3DXVECTOR3 posOffset = VEC3_ZERO;	// �����̊J�n�I�t�Z�b�g
	posOffset.x = -sizeValue.x + sizeHead.x - (sizeValue.x * (m_alignX - 1));
	posOffset.y = -sizeValue.y + sizeHead.y - (sizeValue.y * (m_alignY - 1));

	D3DXVECTOR3 posStart = VEC3_ZERO;	// �����̊J�n�ʒu
	posStart.x = m_pos.x + sinf(rotStart.x) * posOffset.x + sinf(rotStart.y) * posOffset.y;	// �J�n�ʒuX
	posStart.y = m_pos.y + cosf(rotStart.x) * posOffset.x + cosf(rotStart.y) * posOffset.y;	// �J�n�ʒuY

	for (auto& rList : m_listValue)
	{ // �����̌������J��Ԃ�

		// �ʒu�𔽉f
		assert(rList != nullptr);
		rList->SetVec3Position(posStart);

		// ���̐ݒ���W�̊J�n�_��ۑ�
		posStart.x += sinf(rotStart.x) * m_space.x + sinf(rotStart.y) * m_space.y;
		posStart.y += cosf(rotStart.x) * m_space.x + cosf(rotStart.y) * m_space.y;
	}
}

//============================================================
//	�����̃e�N�X�`�����W�̐ݒ菈��
//============================================================
void CMultiValue::SetTexNum(void)
{
	// �������������Ƃɕ���
	int nDigit = (int)m_listValue.size();	// ���l�̌���
	int *pNumDivide = new int[nDigit];		// ���l�̕���p�z��
	useful::ZeroClear(pNumDivide);			// �z��̃������N���A
	useful::DivideDigitNum
	( // ����
		pNumDivide,	// �������ʂ̊i�[�z��
		m_nNum,		// �������鐔�l
		nDigit - 1	// �������鐔���̌���
	);

	// �����������l�𔽉f
	int nCntDigit = 0;	// �����C���f�b�N�X
	for (auto& rList : m_listValue)
	{ // �����̌������J��Ԃ�

		// �����̐ݒ�
		assert(rList != nullptr);
		rList->SetNumber(pNumDivide[nCntDigit]);

		// ���������Z
		nCntDigit++;
	}

	// ���l�̕���p�z���j��
	SAFE_DEL_ARRAY(pNumDivide);
}
