//============================================================
//
//	�I�u�W�F�N�g�L�����N�^�[2D���� [objectChara2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectChara2D.h"
#include "manager.h"
#include "renderer.h"
#include "character2D.h"

//************************************************************
//	�q�N���X [CObjectChara2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CObjectChara2D::CObjectChara2D(const CObject::ELabel label, const CObject::EDim dimension, const int nPriority) : CAnim3D(label, dimension, nPriority)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CObjectChara2D::~CObjectChara2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CObjectChara2D::Init(void)
{
	// �A�j���[�V����3D�̏�����
	if (FAILED(CAnim3D::Init()))
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
void CObjectChara2D::Uninit(void)
{
	// �A�j���[�V����3D�̏I��
	CAnim3D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CObjectChara2D::Update(const float fDeltaTime)
{
	// ���[�V�������Ȃ��ꍇ������
	if (m_info.vecMotion.empty()) { assert(false); return; }

	// �A�j���[�V����3D�̍X�V
	CAnim3D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CObjectChara2D::Draw(CShader *pShader)
{
	// �A�j���[�V����3D�̕`��
	CAnim3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CObjectChara2D *CObjectChara2D::Create(const D3DXVECTOR3 &rPos, const D3DXVECTOR3 &rRot)
{
	// �I�u�W�F�N�g�L�����N�^�[2D�̐���
	CObjectChara2D *pObjectChara2D = new CObjectChara2D;
	if (pObjectChara2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �I�u�W�F�N�g�L�����N�^�[2D�̏�����
		if (FAILED(pObjectChara2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �I�u�W�F�N�g�L�����N�^�[2D�̔j��
			SAFE_DELETE(pObjectChara2D);
			return nullptr;
		}

		// �ʒu��ݒ�
		pObjectChara2D->SetVec3Position(rPos);

		// ������ݒ�
		pObjectChara2D->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pObjectChara2D;
	}
}

//============================================================
//	�L�����N�^�[��񊄓�
//============================================================
void CObjectChara2D::BindCharaData(const char *pCharaPass)
{
	// ���蓖�Ă郂�[�V�����p�X�����݂��Ȃ��ꍇ������
	if (pCharaPass == nullptr) { assert(false); return; }

	// ���[�V�������̑S�ݒ�
	SetAllInfo(GET_MANAGER->GetCharacter2D()->Regist(pCharaPass));
}

//============================================================
//	���[�V�����̐ݒ菈��
//============================================================
void CObjectChara2D::SetMotion(const int nType)
{
	// �w�肳�ꂽ���[�V���������݂��Ȃ��ꍇ������
	if (nType <= NONE_IDX || nType >= m_info.GetNumMotion()) { assert(false); return; }

	// �����̃��[�V�����̎�ނ�ݒ�
	m_info.nType = nType;

	// �ϐ����|�C���^�����ȗ���
	SChara *pInfoChara = &m_info.vecMotion[nType].infoChara;	// �L�����N�^�[���

	// �w��e�N�X�`���̊���
	BindTexture(pInfoChara->sPassTexture.c_str());

	// �L�����N�^�[����ݒ�
	SetTexPtrn(pInfoChara->ptrnTexture);	// �e�N�X�`��������
	SetEnableLoop(pInfoChara->bLoop);		// ���[�vON/OFF
	SetVec3Sizing(pInfoChara->sizeChara);	// �傫��

	assert((int)pInfoChara->vecNextTime.size() == pInfoChara->nMaxPtrn);
	for (int i = 0; i < pInfoChara->nMaxPtrn; i++)
	{
		// �p�^�[���ύX���Ԃ�ݒ�
		SetNextTime(pInfoChara->vecNextTime[i]);
	}

	// �L�����N�^�[����������
	ResetCurPtrn();	// �J�n�p�^�[��
	ResetNumLoop();	// �J��Ԃ���
}

//============================================================
//	���[�V�������̒ǉ�����
//============================================================
void CObjectChara2D::AddInfo(const SMotion& rMotion)
{
	int nSetMotionID = m_info.GetNumMotion();	// ���[�V������ݒ肷��z��ԍ�

	// ��̗v�f���Ō���ɒǉ�
	m_info.vecMotion.emplace_back();

	// �����̃��[�V��������ݒ�
	m_info.vecMotion[nSetMotionID] = rMotion;
}

//============================================================
//	���[�V�������S�ݒ菈��
//============================================================
void CObjectChara2D::SetAllInfo(const SInfo& rInfo)
{
	// ���[�V���������N���A
	m_info.vecMotion.clear();

	for (auto& rVec : rInfo.vecMotion)
	{ // �ǂݍ��񂾃��[�V���������J��Ԃ�

		// ���[�V�������̒ǉ�
		AddInfo(rVec);
	}
}

//============================================================
//	�L�����Z���擾����
//============================================================
bool CObjectChara2D::IsCancel(void) const
{
	float fCancelTime = m_info.vecMotion[m_info.nType].fCancelTime;	// �L�����Z���\����
	if (fCancelTime >= 0.0f)
	{ // �L�����Z���\���Ԃ��ݒ肳��Ă���ꍇ

		// ���[�V�����̃L�����Z���󋵂�Ԃ�
		return (GetCurWholeTime() >= fCancelTime);
	}

	// �L�����Z���s��Ԃ�
	return false;
}

//============================================================
//	�R���{�擾����
//============================================================
bool CObjectChara2D::IsCombo(void) const
{
	float fComboTime = m_info.vecMotion[m_info.nType].fComboTime;	// �R���{�\����
	if (fComboTime >= 0.0f)
	{ // �R���{�\���Ԃ��ݒ肳��Ă���ꍇ

		// ���[�V�����̃R���{�󋵂�Ԃ�
		return (GetCurWholeTime() >= fComboTime);
	}

	// �R���{�s��Ԃ�
	return false;
}
