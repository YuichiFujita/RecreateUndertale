//============================================================
//
//	�u���[���� [blur.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "blur.h"
#include "objectChara.h"
#include "objectModel.h"
#include "multiModel.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// �u���[�̗D�揇��
}

//************************************************************
//	�e�N���X [CBlur] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CBlur::CBlur() : CObject(LABEL_BLUR, DIM_3D, PRIORITY),
	m_pParent		(nullptr),		// �e�I�u�W�F�N�g
	m_fStartAlpha	(0.0f),			// �u���[�̊J�n�����x
	m_nMaxLength	(0),			// �ێ�����e�I�u�W�F�N�g�̍ő吔
	m_state			(STATE_NONE),	// ���
	m_nCounterState	(0)				// ��ԊǗ��J�E���^�[
{
	// �����o�ϐ����N���A
	m_oldObject.clear();		// �ߋ��I�u�W�F�N�g���
	m_mat = material::White();	// �u���[���f�}�e���A��
}

//============================================================
//	�f�X�g���N�^
//============================================================
CBlur::~CBlur()
{

}

//============================================================
//	����������
//============================================================
HRESULT CBlur::Init(void)
{
	// �����o�ϐ���������
	m_oldObject.clear();			// �ߋ��I�u�W�F�N�g���
	m_mat = material::White();		// �u���[���f�}�e���A��
	m_pParent		= nullptr;		// �e�I�u�W�F�N�g
	m_fStartAlpha	= 0.0f;			// �u���[�̊J�n�����x
	m_nMaxLength	= 0;			// �ێ�����e�I�u�W�F�N�g�̍ő吔
	m_state			= STATE_NORMAL;	// ���
	m_nCounterState	= 0;			// ��ԊǗ��J�E���^�[

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CBlur::Uninit(void)
{
	for (auto& rVecObj : m_oldObject)
	{ // �ۑ��I�u�W�F�N�g�����J��Ԃ�

		for (auto& rVecParts : rVecObj)
		{ // �p�[�c�����J��Ԃ�

			// �p�[�c�̏I��
			SAFE_UNINIT(rVecParts);
		}

		// �p�[�c�i�[�����N���A
		rVecObj.clear();
	}

	// �ۑ��I�u�W�F�N�g�����N���A
	m_oldObject.clear();

	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CBlur::Update(const float fDeltaTime)
{
	// �c���̐���
	if (m_state == STATE_NORMAL)
	{ // �ʏ��Ԃ̏ꍇ

		// �I�u�W�F�N�g�ۑ��p�̓��I�z��𐶐�
		std::vector<CObjectModel*> tempBlur;
		tempBlur.resize((size_t)m_pParent->GetNumParts());	// �p�[�c�����z�񐶐�

		int nCntParts = 0;	// �p�[�c�C���f�b�N�X
		for (auto& rVecParts : tempBlur)
		{ // �p�[�c�����J��Ԃ�

			// �p�[�c�̐���
			rVecParts = CObjectModel::Create(VEC3_ZERO, VEC3_ZERO);
			if (rVecParts != nullptr)
			{ // �p�[�c�̐����ɐ��������ꍇ

				CObjectModel *pBlurParts = rVecParts;	// �c���p�[�c
				CMultiModel *pOriginParts = m_pParent->GetParts(nCntParts);		// ���_�p�[�c
				D3DXMATRIX mtxParts = pOriginParts->GetMtxWorld();				// �c���������̃}�g���b�N�X

				// ���𐶐����ƈ�v������
				pBlurParts->BindModel(pOriginParts->GetModelID());	// ���ꃂ�f��������
				pBlurParts->SetMtxWorld(mtxParts);					// ����}�g���b�N�X��ݒ�

				// �ʒu�E�����E�傫�����}�g���b�N�X����擾���ݒ�
				pBlurParts->SetVec3Position(useful::GetMatrixPosition(mtxParts));
				pBlurParts->SetVec3Rotation(useful::GetMatrixRotation(mtxParts));
				pBlurParts->SetVec3Scaling(useful::GetMatrixScaling(mtxParts));

				// ���Z�����ɂ���
				pBlurParts->GetRenderState()->SetAlphaBlend(CRenderState::BLEND_ADD);
			}

			// �p�[�c�C���f�b�N�X��i�߂�
			nCntParts++;
		}

		// �z��̍Ō���Ɏc����ǉ�
		m_oldObject.push_back(tempBlur);
	}

	// �c���̐F���f
	{
		int nCntBlur = 0;	// �u���[�C���f�b�N�X
		for (auto& rVecObj : m_oldObject)
		{ // �ۑ��I�u�W�F�N�g�����J��Ԃ�

			// �}�e���A���̓����x�����ɂȂ�ɂ�ĉ����Ă���
			D3DXMATERIAL matSet = m_mat;	// �ݒ�}�e���A��
			matSet.MatD3D.Diffuse.a = (m_fStartAlpha / m_nMaxLength) * nCntBlur;

			for (auto& rVecParts : rVecObj)
			{ // �p�[�c�����J��Ԃ�

				// �p�[�c�̑S�}�e���A����ύX
				rVecParts->SetAllMaterial(matSet);
			}

			// �u���[�C���f�b�N�X��i�߂�
			nCntBlur++;
		}
	}

	// �c���̍폜
	{
		bool bDelete = false;	// �폜��
		switch (m_state)
		{ // ��Ԃ��Ƃ̏���
		case STATE_NONE:
			break;

		case STATE_NORMAL:

			// �폜�������w�� (�c�����ő吔�𒴂����ꍇ�폜)
			bDelete = (int)m_oldObject.size() > m_nMaxLength;
			break;

		case STATE_VANISH:

			// �폜�������w�� (�m��폜)
			bDelete = true;
			break;

		default:
			assert(false);
			break;
		}

		if (bDelete)
		{ // �폜���s���ꍇ

			if (m_oldObject.size() <= 0)
			{ // �z��v�f���Ȃ��ꍇ
			
				// �������Ȃ���Ԃɂ���
				m_state = STATE_NONE;

				// �����𔲂���
				return;
			}

			std::vector<CObjectModel*> objFront = m_oldObject.front();	// �c���z��̐擪
			for (auto& rVecParts : objFront)
			{ // �p�[�c�����J��Ԃ�

				// �p�[�c�̏I��
				SAFE_UNINIT(rVecParts);
			}

			// �p�[�c�i�[�����N���A
			objFront.clear();

			// �c���̍Ō����z�񂩂�폜
			m_oldObject.erase(m_oldObject.begin());
		}
	}
}

//============================================================
//	�`�揈��
//============================================================
void CBlur::Draw(CShader *pShader)
{
	// �������Ȃ���Ԃ̏ꍇ������
	if (m_state == STATE_NONE) { return; }

	for (auto& rVecObj : m_oldObject)
	{ // �ۑ��I�u�W�F�N�g�����J��Ԃ�

		for (auto& rVecParts : rVecObj)
		{ // �p�[�c�����J��Ԃ�

			// �p�[�c�̕`��
			rVecParts->Draw(pShader);
		}
	}
}

//============================================================
//	��������
//============================================================
CBlur *CBlur::Create
(
	CObjectChara *pParent,		// �e�I�u�W�F�N�g
	D3DXMATERIAL& rMat,			// �u���[�}�e���A��
	const float fStartAlpha,	// �u���[�J�n�����x
	const int nMaxLength		// �ێ��I�u�W�F�N�g�ő吔
)
{
	// �u���[�̐���
	CBlur *pBlur = new CBlur;
	if (pBlur == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �u���[�̏�����
		if (FAILED(pBlur->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �u���[�̔j��
			SAFE_DELETE(pBlur);
			return nullptr;
		}

		// �e�I�u�W�F�N�g��ݒ�
		pBlur->m_pParent = pParent;

		// �u���[�}�e���A����ݒ�
		pBlur->SetMaterial(rMat);

		// �u���[�̊J�n�����x��ݒ�
		pBlur->SetStartAlpha(fStartAlpha);

		// �ێ��I�u�W�F�N�g�̍ő吔��ݒ�
		pBlur->SetMaxLength(nMaxLength);

		// �m�ۂ����A�h���X��Ԃ�
		return pBlur;
	}
}

//============================================================
//	��Ԃ̐ݒ菈��
//============================================================
void CBlur::SetState(const EState state)
{
	if (state == m_state && state != STATE_NORMAL)
	{ // �ݒ肷���Ԃ����݂̏�Ԋ��A�ݒ肷���Ԃ��ʏ��Ԃ̏ꍇ

		// �����𔲂���
		return;
	}

	if (m_state == STATE_NONE && state == STATE_VANISH)
	{ // ���łɏ����Ă���̂ɏ��������悤�Ƃ��Ă���ꍇ

		// �����𔲂���
		return;
	}

	// �����̏�Ԃ�ݒ�
	m_state = state;

	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:	// �������Ȃ����
	case STATE_VANISH:	// �������
	case STATE_NORMAL:	// �ʏ���
		break;

	default:	// ��O���
		assert(false);
		break;
	}
}
