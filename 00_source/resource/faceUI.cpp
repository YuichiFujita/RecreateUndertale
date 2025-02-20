//============================================================
//
//	�\��UI���� [faceUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "faceUI.h"
#include "manager.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// �\��UI�̗D�揇��
}

//************************************************************
//	�q�N���X [CFaceUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFaceUI::CFaceUI() : CAnim2D(CObject::LABEL_UI, CObject::DIM_2D, PRIORITY),
	m_pos		(VEC3_ZERO),	// ���_�ʒu
	m_info		({}),			// �\����
	m_nTypeEmo	(0)				// �\����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFaceUI::~CFaceUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFaceUI::Init()
{
	// �����o�ϐ���������
	m_pos		= VEC3_ZERO;	// ���_�ʒu
	m_info		= {};			// �\����
	m_nTypeEmo	= 0;			// �\����

	// �A�j���[�V����2D�̏�����
	if (FAILED(CAnim2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFaceUI::Uninit()
{
	// �A�j���[�V����2D�̏I��
	CAnim2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CFaceUI::Update(const float fDeltaTime)
{
	// �\��Ȃ��ꍇ������
	if (m_info.vecEmotion.empty()) { assert(false); return; }

	// �A�j���[�V����2D�̍X�V
	CAnim2D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CFaceUI::Draw(CShader* pShader)
{
	// �A�j���[�V����2D�̕`��
	CAnim2D::Draw(pShader);
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFaceUI::SetVec3Position(const VECTOR3& rPos)
{
	// ���_�ʒu�̕ۑ�
	m_pos = rPos;

	// �ʒu�̐ݒ�
	CAnim2D::SetVec3Position(rPos);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	��������
//============================================================
CFaceUI* CFaceUI::Create(const int nIdxFace, const int nTypeEmo, const VECTOR3& rPos, const VECTOR3& rRot)
{
	// �\��UI�̐���
	CFaceUI* pFaceUI = new CFaceUI;
	if (pFaceUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �\��UI�̏�����
		if (FAILED(pFaceUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �\��UI�̔j��
			SAFE_DELETE(pFaceUI);
			return nullptr;
		}

		// �������
		pFaceUI->BindFaceData(nIdxFace);

		// �\���ݒ�
		pFaceUI->SetEmotion(nTypeEmo);

		// �ʒu��ݒ�
		pFaceUI->SetVec3Position(rPos);

		// ������ݒ�
		pFaceUI->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pFaceUI;
	}
}

//============================================================
//	��̊�������
//============================================================
void CFaceUI::BindFaceData(const int nIdxFace)
{
	// ���[�V�������̑S�ݒ�
	SetAllInfo(GET_MANAGER->GetFaceAnim2D()->GetInfo(nIdxFace));

	// �\��̏�����
	SetEmotion(0);
}

//============================================================
//	�\��̐ݒ菈��
//============================================================
void CFaceUI::SetEmotion(const int nTypeEmo)
{
	// �w�肳�ꂽ�\����݂��Ȃ��ꍇ������
	if (nTypeEmo <= NONE_IDX || nTypeEmo >= m_info.GetNumEmotion()) { assert(false); return; }

	// �����̕\��̎�ނ�ݒ�
	m_nTypeEmo = nTypeEmo;

	// �ϐ����|�C���^�����ȗ���
	AEmotion* pInfoEmo = &m_info.vecEmotion[nTypeEmo];	// �\����

	// �w��e�N�X�`���̊���
	BindTexture(pInfoEmo->sPathTexture.c_str());

	// �\�����ݒ�
	SetTexPtrn(pInfoEmo->ptrnTexture);			// �e�N�X�`��������
	SetEnableLoop(pInfoEmo->bLoop);				// ���[�vON/OFF
	SetLoopWaitTime(pInfoEmo->fLoopWaitTime);	// ���[�v�ҋ@����
	SetVec3Size(pInfoEmo->size);				// �傫��

	assert((int)pInfoEmo->vecNextTime.size() == pInfoEmo->nMaxPtrn);
	for (int i = 0; i < pInfoEmo->nMaxPtrn; i++)
	{
		// �p�^�[���ύX���Ԃ�ݒ�
		SetNextTime(pInfoEmo->vecNextTime[i]);
	}

	// �����������
	ResetCurPtrn();	// �J�n�p�^�[��
	ResetNumLoop();	// �J��Ԃ���
}

//============================================================
//	�\��̒ǉ�����
//============================================================
void CFaceUI::AddInfo(const AEmotion& rEmotion)
{
	int nSetEmotionIdx = m_info.GetNumEmotion();	// �\���ݒ肷��z��ԍ�

	// ��̗v�f���Ō���ɒǉ�
	m_info.vecEmotion.emplace_back();

	// �����̕\�����ݒ�
	m_info.vecEmotion[nSetEmotionIdx] = rEmotion;
}

//============================================================
//	�\��̑S�ݒ菈��
//============================================================
void CFaceUI::SetAllInfo(const AFace& rFace)
{
	// �\������N���A
	m_info.vecEmotion.clear();

	for (auto& rVec : rFace.vecEmotion)
	{ // �ǂݍ��񂾕\����J��Ԃ�

		// �\����̒ǉ�
		AddInfo(rVec);
	}
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CFaceUI::SetPositionRelative()
{
	VECTOR3 posThis = m_pos;				// ���g�̈ʒu
	VECTOR3 rotThis = GetVec3Rotation();	// ���g�̌���

	// �ϐ����|�C���^�����ȗ���
	AEmotion* pInfoEmo = &m_info.vecEmotion[m_nTypeEmo];	// �\����

	// X���W�I�t�Z�b�g�����炷
	posThis.x += sinf(rotThis.z + HALF_PI) * pInfoEmo->offset.x;
	posThis.y += cosf(rotThis.z + HALF_PI) * pInfoEmo->offset.x;

	// Y���W�I�t�Z�b�g�����炷
	posThis.x += sinf(rotThis.z) * pInfoEmo->offset.y;
	posThis.y += cosf(rotThis.z) * pInfoEmo->offset.y;

	// ���Έʒu�̔��f
	CAnim2D::SetVec3Position(posThis);
}
