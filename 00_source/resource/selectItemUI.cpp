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
#include "loadtext.h"
#include "item.h"
#include "itemUseUI.h"
#include "itemInfoUI.h"
#include "itemDropUI.h"
#include "sceneGame.h"
#include "player.h"
#include "playerItem.h"

// TODO�F�f�o�b�O
#if 0
#define RAND_ITEM
#endif

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char	*FONT	 = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
	const char	*PATH	 = "data\\TEXT\\selectItem.txt";				// �e�L�X�g�p�X
	const bool	ITALIC	 = false;	// �C�^���b�N
	const float	HEIGHT	 = 42.0f;	// �����c��
	const int	PRIORITY = 6;		// �A�C�e�����j���[�̗D�揇��
	const VECTOR3 CURSOR_OFFSET = VECTOR3(22.0f, 0.0f, 0.0f);	// �J�[�\���I�t�Z�b�g

	namespace frame
	{
		const VECTOR3 POS	= VECTOR3(545.0f, 347.5f, 0.0f);	// �t���[���ʒu
		const VECTOR3 ROT	= VEC3_ZERO;						// �t���[������
		const VECTOR3 SIZE	= VECTOR3(500.0f, 520.0f, 0.0f);	// �t���[���傫��
	}

	namespace select
	{
		const VECTOR3	POS		= VECTOR3(380.0f, 555.0f, 0.0f);	// �ʒu
		const VECTOR3	SPACE	= VECTOR3(160.0f, 0.0f, 0.0f);		// ��
		const VECTOR3	ROT		= VEC3_ZERO;		// ����
		const COLOR		COL		= color::White();	// �ʏ�F
		const EAlignX	ALIGN_X = XALIGN_CENTER;	// ���z�u
	}

	namespace item
	{
		const VECTOR3	POS		= VECTOR3(360.0f, 145.0f, 0.0f);	// �ʒu
		const VECTOR3	SPACE	= VECTOR3(0.0f, 49.0f, 0.0f);		// ��
		const VECTOR3	ROT		= VEC3_ZERO;		// ����
		const COLOR		COL		= color::White();	// �ʏ�F
		const EAlignX	ALIGN_X = XALIGN_LEFT;		// ���z�u
	}
}

//************************************************************
//	�q�N���X [CSelectItemUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSelectItemUI::CSelectItemUI(AFuncUninit funcUninit, CObject2D* pSoul) : CSelectUI(funcUninit, pSoul),
	m_pItemMenu		 (nullptr),		// �A�C�e�����j���[���
	m_state			 (STATE_ITEM),	// ���
	m_nCurSelectItem (0),			// ���݂̑I���A�C�e��
	m_nCurSelectAct	 (0)			// ���݂̑I���s��
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
HRESULT CSelectItemUI::Init()
{
	// �����o�ϐ���������
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I�����
	m_vecItemName.clear();			// �A�C�e�����
	m_pItemMenu		 = nullptr;		// �A�C�e�����j���[���
	m_state			 = STATE_ITEM;	// ���
	m_nCurSelectItem = 0;			// ���݂̑I���A�C�e��
	m_nCurSelectAct	 = 0;			// ���݂̑I���s��

	//--------------------------------------------------------
	//	�e�N���X�̏����� / �ݒ�
	//--------------------------------------------------------
	// �Z���N�gUI�̏�����
	if (FAILED(CSelectUI::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �t���[���̈ʒu��ݒ�
	SetFramePosition(frame::POS);

	// �t���[���̌�����ݒ�
	SetFrameRotation(frame::ROT);

	// �t���[���̑傫����ݒ�
	SetFrameSize(frame::SIZE);

	//--------------------------------------------------------
	//	�I���̏����� / �ݒ�
	//--------------------------------------------------------
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �����ʒu�I�t�Z�b�g���v�Z
		VECTOR3 offset = select::SPACE * (float)i;

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

			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(PRIORITY);

		// �����������
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(PATH, TEXT_USE + i));
	}

	//--------------------------------------------------------
	//	�A�C�e���̏����� / �ݒ�
	//--------------------------------------------------------
	CPlayerItem itemArray = *CSceneGame::GetPlayer()->GetItem();	// �v���C���[�����A�C�e�����
	CItem* pItem = GET_MANAGER->GetItem();	// �A�C�e�����
#ifdef RAND_ITEM
	for (int i = 0; i < SPlayerItem::MAX_ITEM; i++)
	{ // �A�C�e�������J��Ԃ�
#else
	int nNumItem = itemArray.GetNumItem();	// �����A�C�e����
	for (int i = 0; i < nNumItem; i++)
	{ // �����A�C�e�������J��Ԃ�
#endif

		// ��̗v�f���Ō���ɒǉ�
		m_vecItemName.emplace_back();

#ifdef RAND_ITEM
		// �A�C�e���C���f�b�N�X��ۑ�
		m_vecItemName[i].nItemIdx = rand() % 6;
#else
		// �A�C�e���C���f�b�N�X��ۑ�
		m_vecItemName[i].nItemIdx = itemArray.GetItemIdx(i);
#endif

		// �����ʒu�I�t�Z�b�g���v�Z
		VECTOR3 offset = item::SPACE * (float)i;

		// �A�C�e�����̐���
		m_vecItemName[i].pName = CString2D::Create
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
		if (m_vecItemName[i].pName == nullptr)
		{ // �����Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_vecItemName[i].pName->SetPriority(PRIORITY);

		// �A�C�e�����ݒ�
		m_vecItemName[i].pName->SetString(pItem->GetInfo(m_vecItemName[i].nItemIdx).GetName());
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSelectItemUI::Uninit()
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I���̏I��
		SAFE_UNINIT(m_apSelect[i]);
	}

	for (auto& rVec : m_vecItemName)
	{ // �v�f�����J��Ԃ�

		// �A�C�e�����̏I��
		SAFE_UNINIT(rVec.pName);
	}

	// �A�C�e�����̃N���A
	m_vecItemName.clear();

	// �A�C�e�����j���[�̏I��
	SAFE_UNINIT(m_pItemMenu);

	// �Z���N�gUI�̏I��
	CSelectUI::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSelectItemUI::Update(const float fDeltaTime)
{
	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_ITEM:

		// �A�C�e���I���̍X�V
		UpdateSelectItem();

		// �A�C�e������̍X�V
		UpdateDecideItem();

		// �Z���N�gUI�̍X�V
		CSelectUI::Update(fDeltaTime);
		break;

	case STATE_ACT:

		// �s���I���̍X�V
		UpdateSelectAct();

		// �s������̍X�V
		UpdateDecideAct();
		break;

	case STATE_TEXT:

		// �A�C�e�����j���[�̍X�V
		assert(m_pItemMenu != nullptr);
		m_pItemMenu->Update(fDeltaTime);
		break;

	default:
		assert(false);
		break;
	}
}

//============================================================
//	�`�揈��
//============================================================
void CSelectItemUI::Draw(CShader* pShader)
{
	// �Z���N�gUI�̕`��
	CSelectUI::Draw(pShader);
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CSelectItemUI::SetEnableDraw(const bool bDraw)
{
	// ���g�̕`��󋵂̐ݒ�
	CSelectUI::SetEnableDraw(bDraw);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I���̕`��󋵂̐ݒ�
		m_apSelect[i]->SetEnableDraw(bDraw);
	}

	for (auto& rVec : m_vecItemName)
	{ // �v�f�����J��Ԃ�

		// �A�C�e�����̕`��󋵂̐ݒ�
		rVec.pName->SetEnableDraw(bDraw);
	}
}

//============================================================
//	���j���[�����\�t���O�̎擾����
//============================================================
bool CSelectItemUI::IsCreateOK()
{
	CPlayerItem itemArray = *CSceneGame::GetPlayer()->GetItem();	// �v���C���[�����A�C�e�����

	// �A�C�e���������Ă���Ȃ琶���\
	return (itemArray.GetNumItem() > 0);
}

//============================================================
//	�A�C�e���I���̍X�V����
//============================================================
void CSelectItemUI::UpdateSelectItem()
{
	// �I��������
	CInputKeyboard* pKey = GET_INPUTKEY;		// �L�[�{�[�h���
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
	SetSoulPosition(m_vecItemName[m_nCurSelectItem].pName->GetVec3Position() - CURSOR_OFFSET);
}

//============================================================
//	�A�C�e������̍X�V����
//============================================================
void CSelectItemUI::UpdateDecideItem()
{
	if (input::Decide())
	{
		// �s���I����Ԃɂ���
		m_state = STATE_ACT;
	}
}

//============================================================
//	�s���I���̍X�V����
//============================================================
void CSelectItemUI::UpdateSelectAct()
{
	// �I��������
	CInputKeyboard* pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// �E�ɑI�������炷
		m_nCurSelectAct = (m_nCurSelectAct + 1) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// ���ɑI�������炷
		m_nCurSelectAct = (m_nCurSelectAct + (SELECT_MAX - 1)) % SELECT_MAX;
	}

	// �\�E���J�[�\���̈ʒu���ړ�
	const VECTOR3 offset = VECTOR3(m_apSelect[m_nCurSelectAct]->GetStrWidth() * 0.5f, 0.0f, 0.0f) + CURSOR_OFFSET;	// �J�[�\���I�t�Z�b�g
	SetSoulPosition(m_apSelect[m_nCurSelectAct]->GetVec3Position() - offset);
}

//============================================================
//	�s������̍X�V����
//============================================================
void CSelectItemUI::UpdateDecideAct()
{
	if (input::Decide())
	{
		// �A�C�e�����j���[�̐���
		m_pItemMenu = CItemUI::Create
		( // ����
			(ESelect)m_nCurSelectAct,					// �I�𒆍s��
			m_vecItemName[m_nCurSelectItem].nItemIdx,	// �I�𒆃A�C�e���C���f�b�N�X
			m_nCurSelectItem							// �I�𒆃o�b�O�C���f�b�N�X
		);

		// �A�C�e�����j���[�̕`���OFF�ɂ���
		SetEnableDraw(false);

		// �\�E���J�[�\���̕`���OFF�ɂ���
		SetSoulCursorDraw(false);

		// �e�L�X�g�\����Ԃɂ���
		m_state = STATE_TEXT;
	}

	if (input::Cancel())
	{
		// �I������������
		m_nCurSelectAct = 0;

		// �A�C�e���I����Ԃɂ���
		m_state = STATE_ITEM;
	}
}

//************************************************************
//	�q�N���X [CItemUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CItemUI::CItemUI(const int nChoiceItemIdx, const int nChoiceBagIdx) : CObject(CObject::LABEL_NONE, CObject::DIM_3D, PRIORITY),
	m_nChoiceItemIdx	(nChoiceItemIdx),	// �I�𒆃A�C�e���C���f�b�N�X
	m_nChoiceBagIdx		(nChoiceBagIdx),	// �I�𒆃o�b�O�C���f�b�N�X
	m_pTextBox			(nullptr),			// �e�L�X�g�{�b�N�X���
	m_nCurTextIdx		(0)					// ���݂̃e�L�X�g�C���f�b�N�X
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CItemUI::~CItemUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CItemUI::Init()
{
	// �����o�ϐ���������
	m_pTextBox = nullptr;	// �e�L�X�g�{�b�N�X���
	m_nCurTextIdx = 0;		// ���݂̃e�L�X�g�C���f�b�N�X

	// �e�L�X�g�{�b�N�X�̐���
	m_pTextBox = CFrame2D::Create(CFrame2D::PRESET_DOWN);	// TODO�F������ƕ|���A���ԍ���ău���[�N�|�C���g
	if (m_pTextBox == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �e�L�X�g�\���@�\��ݒ�
	m_pTextBox->ChangeModule(new CFrame2DModuleText);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CItemUI::Uninit()
{
	// �e�L�X�g�{�b�N�X�̏I��
	SAFE_UNINIT(m_pTextBox);

	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CItemUI::Update(const float fDeltaTime)
{
	if (input::Decide())
	{
		if (IsTextBoxScroll())
		{ // �������蒆�̏ꍇ

			// ������S�\��������
			SetTextBoxEnableDraw(true);
			return;
		}

		// �e�L�X�g���e�̐i�s
		NextText();
	}
}

//============================================================
//	�`�揈��
//============================================================
void CItemUI::Draw(CShader* /*pShader*/)
{

}

//============================================================
//	��������
//============================================================
CItemUI* CItemUI::Create
(
	const CSelectItemUI::ESelect choiceAct,	// �I�𒆍s��
	const int nChoiceItemIdx,				// �I�𒆃A�C�e���C���f�b�N�X
	const int nChoiceBagIdx					// �I�𒆃o�b�O�C���f�b�N�X
)
{
	// �A�C�e��UI�̐���
	CItemUI* pItemUI = nullptr;	// �A�C�e��UI���
	switch (choiceAct)
	{ // �I�������Ƃ̏���
	case CSelectItemUI::SELECT_USE:
		pItemUI = new CItemUseUI(nChoiceItemIdx, nChoiceBagIdx);
		break;

	case CSelectItemUI::SELECT_INFO:
		pItemUI = new CItemInfoUI(nChoiceItemIdx, nChoiceBagIdx);
		break;

	case CSelectItemUI::SELECT_DROP:
		pItemUI = new CItemDropUI(nChoiceItemIdx, nChoiceBagIdx);
		break;

	default:	// ��O����
		assert(false);
		break;
	}

	if (pItemUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �A�C�e���̏�����
		if (FAILED(pItemUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �A�C�e���̔j��
			SAFE_DELETE(pItemUI);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pItemUI;
	}
}
