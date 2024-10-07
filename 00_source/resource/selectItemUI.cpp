//============================================================
//
//	�A�C�e�����j���[���� [selectItemUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "selectItemUI.h"
#include "manager.h"
#include "string2D.h"
#include "text2D.h"
#include "frameText2D.h"
#include "item.h"
#include "loadtext.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char	*FONT	 = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
	const char	*PASS	 = "data\\TEXT\\selectItem.txt";				// �e�L�X�g�p�X
	const bool	ITALIC	 = false;	// �C�^���b�N
	const float	HEIGHT	 = 42.0f;	// �����c��
	const int	PRIORITY = 6;		// �A�C�e�����j���[�̗D�揇��
	const D3DXVECTOR3 CURSOR_OFFSET = D3DXVECTOR3(22.0f, 0.0f, 0.0f);	// �J�[�\���I�t�Z�b�g

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(545.0f, 347.5f, 0.0f);	// �t���[���ʒu
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// �t���[������
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(500.0f, 520.0f, 0.0f);	// �t���[���傫��
	}

	namespace select
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;	// ���z�u
		const D3DXVECTOR3 POS	= D3DXVECTOR3(380.0f, 555.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3 SPACE	= D3DXVECTOR3(160.0f, 0.0f, 0.0f);		// ��
		const D3DXVECTOR3 ROT	= VEC3_ZERO;	// ����
		const D3DXCOLOR COL		= XCOL_WHITE;	// �ʏ�F
	}

	namespace item
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// ���z�u
		const D3DXVECTOR3 POS	= D3DXVECTOR3(360.0f, 145.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3 SPACE	= D3DXVECTOR3(0.0f, 49.0f, 0.0f);		// ��
		const D3DXVECTOR3 ROT	= VEC3_ZERO;	// ����
		const D3DXCOLOR COL		= XCOL_WHITE;	// �ʏ�F
	}
}

//************************************************************
//	�q�N���X [CSelectItemUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSelectItemUI::CSelectItemUI(AFuncUninit funcUninit, CObject2D *pSoul) : CSelect(funcUninit, pSoul),
	m_pTextBox		 (nullptr),	// �e�L�X�g�{�b�N�X���
	m_pSelectItem	 (nullptr),	// �I�𒆃A�C�e�����
	m_nCurTextIdx	 (0),		// ���݂̃e�L�X�g�C���f�b�N�X
	m_nCurSelectItem (0),		// ���݂̑I���A�C�e��
	m_nCurSelect	 (0)		// ���݂̑I����
{
	// �����o�ϐ����N���A
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I�����
	m_vecItemName.clear();	// �A�C�e�����
}

//============================================================
//	�f�X�g���N�^
//============================================================
CSelectItemUI::~CSelectItemUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSelectItemUI::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I�����
	m_vecItemName.clear();		// �A�C�e�����
	m_pTextBox		 = nullptr;	// �e�L�X�g�{�b�N�X���
	m_pSelectItem	 = nullptr;	// �I�𒆃A�C�e�����
	m_nCurTextIdx	 = 0;		// ���݂̃e�L�X�g�C���f�b�N�X
	m_nCurSelectItem = 0;		// ���݂̑I���A�C�e��
	m_nCurSelect	 = 0;		// ���݂̑I����

	//--------------------------------------------------------
	//	�e�N���X�̏����� / �ݒ�
	//--------------------------------------------------------
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

	//--------------------------------------------------------
	//	�I���̏����� / �ݒ�
	//--------------------------------------------------------
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �����ʒu�I�t�Z�b�g���v�Z
		D3DXVECTOR3 offset = select::SPACE * (float)i;

		// �I���̐���
		m_apSelect[i] = CString2D::Create
		( // ����
			FONT,					// �t�H���g�p�X
			ITALIC,					// �C�^���b�N
			L"",					// �w�蕶����
			select::POS + offset,	// ���_�ʒu
			HEIGHT,					// �����c��
			select::ALIGN_X,		// ���z�u
			select::ROT,			// ���_����
			select::COL				// �F
		);
		if (m_apSelect[i] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(PRIORITY);

		// �����������
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(PASS, TEXT_USE + i));
	}

	//--------------------------------------------------------
	//	�A�C�e���̏����� / �ݒ�
	//--------------------------------------------------------
	CItem* pItem = GET_MANAGER->GetItem();	// �A�C�e�����
	for (int i = 0; i < 8; i++)	// TODO�F�A�C�e�����ɉ������񐔎w��
	{ // �����A�C�e�������J��Ԃ�

		// ��̗v�f���Ō���ɒǉ�
		m_vecItemName.emplace_back();

		// TODO�F�����ŃA�C�e���f�[�^�̃C���f�b�N�X��ۑ�����
#if 1
		// �A�C�e���C���f�b�N�X��ۑ�
		m_vecItemName[i].nItemID = rand() % 2;
#endif

		// �����ʒu�I�t�Z�b�g���v�Z
		D3DXVECTOR3 offset = item::SPACE * (float)i;

		// �A�C�e�����̐���
		m_vecItemName[i].m_pName = CString2D::Create
		( // ����
			FONT,				// �t�H���g�p�X
			ITALIC,				// �C�^���b�N
			L"",				// �w�蕶����
			item::POS + offset,	// ���_�ʒu
			HEIGHT,				// �����c��
			item::ALIGN_X,		// ���z�u
			item::ROT,			// ���_����
			item::COL			// �F
		);
		if (m_vecItemName[i].m_pName == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_vecItemName[i].m_pName->SetPriority(PRIORITY);

		// �A�C�e�����ݒ�
		std::string sName = pItem->GetInfo(m_vecItemName[i].nItemID).GetName();	// �A�C�e����
		std::wstring wsName = useful::MultiByteToWide(sName);	// ���C�h�ϊ��A�C�e����
		m_vecItemName[i].m_pName->SetString(wsName);	// �������ݒ�
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSelectItemUI::Uninit(void)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I���̏I��
		SAFE_UNINIT(m_apSelect[i]);
	}

	for (auto& rVec : m_vecItemName)
	{ // �v�f�����J��Ԃ�

		// �A�C�e�����̏I��
		SAFE_UNINIT(rVec.m_pName);
	}

	// �A�C�e�����̃N���A
	m_vecItemName.clear();

	// �Z���N�g�̏I��
	CSelect::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSelectItemUI::Update(const float fDeltaTime)
{
	// TODO�F�����͏�ԊǗ��ɂ���
	if (m_pSelectItem == nullptr)
	{ // �A�C�e�����I������Ă��Ȃ��ꍇ

		// �A�C�e���I���̍X�V
		UpdateSelectItem();

		// �A�C�e������̍X�V
		UpdateDecideItem();

		// �Z���N�g�̍X�V
		CSelect::Update(fDeltaTime);
	}
	else
	{ // �A�C�e�����I������Ă���ꍇ

		// �I���̍X�V
		UpdateSelect();

		// ����̍X�V
		UpdateDecide();
	}
}

//============================================================
//	�`�揈��
//============================================================
void CSelectItemUI::Draw(CShader *pShader)
{
	// �Z���N�g�̕`��
	CSelect::Draw(pShader);
}

//============================================================
//	�A�C�e���I���̍X�V����
//============================================================
void CSelectItemUI::UpdateSelectItem(void)
{
	// �I��������
	CInputKeyboard *pKey = GET_INPUTKEY;		// �L�[�{�[�h���
	int nMaxItem = (int)m_vecItemName.size();	// �A�C�e���̑���
	if (pKey->IsTrigger(DIK_DOWN))
	{
		// ��ɑI�������炷
		m_nCurSelectItem = (m_nCurSelectItem + 1) % nMaxItem;
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		// ���ɑI�������炷
		m_nCurSelectItem = (m_nCurSelectItem + (nMaxItem - 1)) % nMaxItem;
	}

	// �\�E���J�[�\���̈ʒu���ړ�
	SetSoulPosition(m_vecItemName[m_nCurSelectItem].m_pName->GetVec3Position() - CURSOR_OFFSET);
}

//============================================================
//	�A�C�e������̍X�V����
//============================================================
void CSelectItemUI::UpdateDecideItem(void)
{
	if (input::Decide())
	{
		// ���ݑI�𒆂̃A�C�e����ۑ�
		m_pSelectItem = &m_vecItemName[m_nCurSelectItem];	// TODO�F�I�𒆂����m�F����ʂ̕��@��͍����悤

		// �e�L�X�g�C���f�b�N�X��������
		m_nCurTextIdx = 0;
	}
}

//============================================================
//	�I���̍X�V����
//============================================================
void CSelectItemUI::UpdateSelect(void)
{
	// �I��������
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// �E�ɑI�������炷
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// ���ɑI�������炷
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}

	// �\�E���J�[�\���̈ʒu���ړ�
	const D3DXVECTOR3 offset = D3DXVECTOR3(m_apSelect[m_nCurSelect]->GetStrWidth() * 0.5f, 0.0f, 0.0f) + CURSOR_OFFSET;	// �J�[�\���I�t�Z�b�g
	SetSoulPosition(m_apSelect[m_nCurSelect]->GetVec3Position() - offset);
}

//============================================================
//	����̍X�V����
//============================================================
void CSelectItemUI::UpdateDecide(void)
{
	if (input::Decide())
	{
		if (m_pTextBox == nullptr)
		{
			// �e�L�X�g�{�b�N�X�̐���
			m_pTextBox = CFrameText2D::Create(SCREEN_CENT, VEC3_ZERO, D3DXVECTOR3(1000.0f, 1000.0f, 0.0f));
		}

		if (m_pTextBox->IsTextScroll())
		{
			m_pTextBox->SetTextEnableDraw(true);
		}
		else
		{
			int nItemIdx = m_vecItemName[m_nCurSelectItem].nItemID;	// �I�𒆃A�C�e���C���f�b�N�X
			CItem* pItem = GET_MANAGER->GetItem();	// �A�C�e�����

			// TODO�F�I�����Ƃɕ\����؂�ւ�
			switch (m_nCurSelect)
			{ // �I�����Ƃ̏���
			case SELECT_USE:
			{
				const ATextBox& rText = pItem->GetInfo(nItemIdx).GetUse();	// �e�L�X�g�{�b�N�X�ۑ����

				if (m_nCurTextIdx >= (int)rText.size())
				{ // �e�L�X�g���I�������ꍇ

					// �I�𒆃A�C�e���̎g�p
					pItem->GetInfo(nItemIdx).Use();

					// �I������������
					m_nCurSelect = 0;

					// ���ݑI�𒆂̃A�C�e�����폜
					m_pSelectItem = nullptr;

					// �e�L�X�g�{�b�N�X�̏I��
					SAFE_UNINIT(m_pTextBox);

					break;
				}

				// ���݂̃e�L�X�g�i�s�x�ɍ��킹���e�L�X�g�ɕύX
				m_pTextBox->ChangeText(rText[m_nCurTextIdx]);

				// �e�L�X�g�i�s�x��i�߂�
				m_nCurTextIdx++;
				break;
			}
			case SELECT_INFO:
			{
				const ATextBox& rText = pItem->GetInfo(nItemIdx).GetInfo();	// �e�L�X�g�{�b�N�X�ۑ����

				if (m_nCurTextIdx >= (int)rText.size())
				{ // �e�L�X�g���I�������ꍇ

					// �I�𒆃A�C�e���̏��
					pItem->GetInfo(nItemIdx).Info();

					// �I������������
					m_nCurSelect = 0;

					// ���ݑI�𒆂̃A�C�e�����폜
					m_pSelectItem = nullptr;

					// �e�L�X�g�{�b�N�X�̏I��
					SAFE_UNINIT(m_pTextBox);

					break;
				}

				// ���݂̃e�L�X�g�i�s�x�ɍ��킹���e�L�X�g�ɕύX
				m_pTextBox->ChangeText(rText[m_nCurTextIdx]);

				// �e�L�X�g�i�s�x��i�߂�
				m_nCurTextIdx++;
				break;
			}
			case SELECT_DROP:
			{
				// TODO�F�̂Ă�e�L�X�g�͂ق�Ƃɂ���ł����́H
#if 0
				const ATextBox& rText = pItem->GetInfo(nItemIdx).GetDrop();	// �e�L�X�g�{�b�N�X�ۑ����

				if (m_nCurTextIdx >= (int)rText.size())
				{ // �e�L�X�g���I�������ꍇ

					// �I�𒆃A�C�e���̔j��
					pItem->GetInfo(nItemIdx).Drop();

					// �I������������
					m_nCurSelect = 0;

					// ���ݑI�𒆂̃A�C�e�����폜
					m_pSelectItem = nullptr;

					// �e�L�X�g�{�b�N�X�̏I��
					SAFE_UNINIT(m_pTextBox);

					break;
				}

				// ���݂̃e�L�X�g�i�s�x�ɍ��킹���e�L�X�g�ɕύX
				m_pTextBox->ChangeText(rText[m_nCurTextIdx]);

				// �e�L�X�g�i�s�x��i�߂�
				m_nCurTextIdx++;
#endif
				break;
			}
			default:
				assert(false);
				break;
			}
		}
	}

	if (input::Cancel())
	{
		// �I������������
		m_nCurSelect = 0;

		// ���ݑI�𒆂̃A�C�e�����폜
		m_pSelectItem = nullptr;
	}
}
