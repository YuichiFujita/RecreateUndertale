//============================================================
//
//	�I�u�W�F�N�g�\��A�j���[�V����2D���� [objectFaceAnim2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectFaceAnim2D.h"
#include "manager.h"
#include "renderer.h"
#include "faceAnim2D.h"

//************************************************************
//	�q�N���X [CObjectFaceAnim2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectFaceAnim2D::CObjectFaceAnim2D(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CAnim2D(label, dimension, nPriority),
	m_pos		(VEC3_ZERO),	// ���_�ʒu
	m_info		({}),			// �\����
	m_nTypeEmo	(0)				// �\����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectFaceAnim2D::~CObjectFaceAnim2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectFaceAnim2D::Init()
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
void CObjectFaceAnim2D::Uninit()
{
	// �A�j���[�V����2D�̏I��
	CAnim2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CObjectFaceAnim2D::Update(const float fDeltaTime)
{
	// �\��Ȃ��ꍇ������
	if (m_info.vecEmotion.empty()) { assert(false); return; }

	// �A�j���[�V����2D�̍X�V
	CAnim2D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CObjectFaceAnim2D::Draw(CShader* pShader)
{
	// �A�j���[�V����2D�̕`��
	CAnim2D::Draw(pShader);
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CObjectFaceAnim2D::SetVec3Position(const VECTOR3& rPos)
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
CObjectFaceAnim2D* CObjectFaceAnim2D::Create(const int nIdxFace, const int nTypeEmo, const VECTOR3& rPos, const VECTOR3& rRot)
{
	// �I�u�W�F�N�g�\��A�j���[�V����2D�̐���
	CObjectFaceAnim2D* pObjectFaceAnim2D = new CObjectFaceAnim2D;
	if (pObjectFaceAnim2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g�\��A�j���[�V����2D�̏�����
		if (FAILED(pObjectFaceAnim2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g�\��A�j���[�V����2D�̔j��
			SAFE_DELETE(pObjectFaceAnim2D);
			return nullptr;
		}

		// �������
		pObjectFaceAnim2D->BindFaceData(nIdxFace);

		// �\���ݒ�
		pObjectFaceAnim2D->SetEmotion(nTypeEmo);

		// �ʒu��ݒ�
		pObjectFaceAnim2D->SetVec3Position(rPos);

		// ������ݒ�
		pObjectFaceAnim2D->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pObjectFaceAnim2D;
	}
}

//============================================================
//	��̊�������
//============================================================
void CObjectFaceAnim2D::BindFaceData(const int nIdxFace)
{
	// ���[�V�������̑S�ݒ�
	SetAllInfo(GET_MANAGER->GetFaceAnim2D()->GetInfo(nIdxFace));

	// �\��̏�����
	SetEmotion(0);
}

//============================================================
//	�\��̐ݒ菈��
//============================================================
void CObjectFaceAnim2D::SetEmotion(const int nTypeEmo)
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

	// TODO
	SetEnablePlayBack(true);

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
void CObjectFaceAnim2D::AddInfo(const AEmotion& rEmotion)
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
void CObjectFaceAnim2D::SetAllInfo(const AFace& rFace)
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
void CObjectFaceAnim2D::SetPositionRelative()
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
