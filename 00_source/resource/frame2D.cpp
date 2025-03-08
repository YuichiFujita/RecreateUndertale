//============================================================
//
//	�t���[��2D���� [frame2D.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2D.h"
#include "frame2DModule.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const VECTOR3 FRAME_POS[] =		// �t���[���ʒu�v���Z�b�g
	{
		VECTOR3(SCREEN_CENT.x, SCREEN_CENT.y, 0.0f)	// �����z�u
	};
	const VECTOR3 FRAME_ROT[] =		// �t���[�������v���Z�b�g
	{
		VEC3_ZERO	// �����z�u
	};
	const VECTOR3 FRAME_SIZE[] =	// �t���[���傫���v���Z�b�g
	{
		VECTOR3(850.0f, 210.0f, 0.0f)	// �����z�u
	};
	const COLOR	COL_FRAME[]	= { color::White(), color::Black() };	// �t���[���F
	const int	PRIORITY	= 6;		// �t���[��2D�̗D�揇��
	const float	BORD_THICK	= 18.0f;	// ����葾��
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(FRAME_POS)  == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");
static_assert(NUM_ARRAY(FRAME_ROT)  == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");
static_assert(NUM_ARRAY(FRAME_SIZE) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	�q�N���X [CFrame2D] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2D::CFrame2D() : CObject(LABEL_UI, DIM_2D, PRIORITY),
	m_pModule	(nullptr),		// �@�\
	m_pos		(VEC3_ZERO),	// �ʒu
	m_rot		(VEC3_ZERO),	// ����
	m_size		(VEC3_ZERO),	// �傫��
	m_preset	(PRESET_NONE)	// �z�u�v���Z�b�g
{
	// �����o�ϐ����N���A
	memset(&m_apFrame[0], 0, sizeof(m_apFrame));	// �t���[�����
}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2D::~CFrame2D()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFrame2D::Init()
{
	// �����o�ϐ���������
	memset(&m_apFrame[0], 0, sizeof(m_apFrame));	// �t���[�����
	m_pModule	= nullptr;		// �@�\
	m_pos		= VEC3_ZERO;	// �ʒu
	m_rot		= VEC3_ZERO;	// ����
	m_size		= VEC3_ZERO;	// �傫��
	m_preset	= PRESET_NONE;	// �z�u�v���Z�b�g

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̐���
		m_apFrame[i] = CObject2D::Create(VEC3_ZERO);
		if (m_apFrame[i] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}

		// �F��ݒ�
		m_apFrame[i]->SetColor(COL_FRAME[i]);

		// �����X�V�E�����`���OFF�ɂ���
		m_apFrame[i]->SetEnableUpdate(false);
		m_apFrame[i]->SetEnableDraw(false);
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFrame2D::Uninit()
{
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̏I��
		SAFE_UNINIT(m_apFrame[i]);
	}

	// �@�\�̏I��
	SAFE_UNINIT(m_pModule);

	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CFrame2D::Update(const float fDeltaTime)
{
	// TODO
#if 1
	static float fOffsetRot = 0.0f;
	static float fRot = 0.0f;

	// ���Z
	fOffsetRot	+= 0.01f;
	fRot		+= 0.01f;

	// �␳
	useful::NormalizeRot(fOffsetRot);
	useful::NormalizeRot(fRot);

	// �ʒu���炷
	VECTOR3 pos = m_originPos;
	pos.x += sinf(fOffsetRot) * 300.0f;
	pos.y += cosf(fOffsetRot) * 300.0f;
	SetVec3Position(pos);

	// �������炷
	SetVec3Rotation(VECTOR3(0.0f, 0.0f, fRot));
#endif

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̍X�V
		m_apFrame[i]->Update(fDeltaTime);
	}

	if (m_pModule != nullptr)
	{ // �@�\�����蓖�Ă��Ă���ꍇ

		// �@�\�̍X�V
		m_pModule->Update(fDeltaTime);
	}
}

//============================================================
//	�`�揈��
//============================================================
void CFrame2D::Draw(CShader* pShader)
{
	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̕`��
		m_apFrame[i]->Draw(pShader);
	}
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CFrame2D::SetPriority(const int nPriority)
{
	// ���g�̗D�揇�ʂ�ݒ�
	CObject::SetPriority(nPriority);

	if (m_pModule != nullptr)
	{ // �@�\�����蓖�Ă��Ă���ꍇ

		// �@�\�̗D�揇�ʂ�ݒ�
		m_pModule->SetPriority(nPriority);
	}

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̗D�揇�ʂ�ݒ�
		m_apFrame[i]->SetPriority(nPriority);
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFrame2D::SetVec3Position(const VECTOR3& rPos)
{
	// ���g�̈ʒu��ݒ�
	m_pos = rPos;

	if (m_pModule != nullptr)
	{ // �@�\�����蓖�Ă��Ă���ꍇ

		// �@�\�̈ʒu��ݒ�
		m_pModule->SetVec3Position(rPos);
	}

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̈ʒu��ݒ�
		m_apFrame[i]->SetVec3Position(rPos);
	}
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFrame2D::SetVec3Rotation(const VECTOR3& rRot)
{
	// ���g�̌�����ݒ�
	m_rot = rRot;

	// �����̐��K��
	useful::NormalizeRot(m_rot);

	if (m_pModule != nullptr)
	{ // �@�\�����蓖�Ă��Ă���ꍇ

		// �@�\�̌�����ݒ�
		m_pModule->SetVec3Rotation(rRot);
	}

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̌�����ݒ�
		m_apFrame[i]->SetVec3Rotation(rRot);
	}
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CFrame2D::SetVec3Size(const VECTOR3& rSize)
{
	// �z�u�v���Z�b�g�̏�����
	m_preset = PRESET_NONE;

	// ���g�̑傫����ݒ�
	m_size = rSize;

	if (m_pModule != nullptr)
	{ // �@�\�����蓖�Ă��Ă���ꍇ

		// �@�\�̑傫����ݒ�
		m_pModule->SetVec3Size(rSize);
	}

	for (int i = 0; i < POLYGON_MAX; i++)
	{ // �|���S���̑������J��Ԃ�

		// �t���[���̑傫����ݒ�
		VECTOR3 bord = VECTOR3(BORD_THICK, BORD_THICK, 0.0f);	// ����葾��
		float fCalcScale = (-1.0f * (i - 1));					// �傫�������l
		m_apFrame[i]->SetVec3Size(rSize + fCalcScale * bord);	// �傫���ݒ�
	}
}

//============================================================
//	�������� (�z�u�v���Z�b�g)
//============================================================
CFrame2D* CFrame2D::Create(const EPreset preset)
{
	// �v���Z�b�g�͈͊O�G���[
	assert(preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX);

	// �t���[��2D�̐���
	CFrame2D* pFrame2D = CFrame2D::Create
	( // ����
		FRAME_POS[preset],	// �ʒu
		FRAME_ROT[preset],	// ����
		FRAME_SIZE[preset]	// �傫��
	);
	if (pFrame2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}

	// �z�u�v���Z�b�g�̏�����
	pFrame2D->m_preset = preset;

	// �m�ۂ����A�h���X��Ԃ�
	return pFrame2D;
}

//============================================================
//	�������� (�z�u�w��)
//============================================================
CFrame2D* CFrame2D::Create
(
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rRot,	// ����
	const VECTOR3& rSize	// �傫��
)
{
	// �t���[��2D�̐���
	CFrame2D* pFrame2D = new CFrame2D;
	if (pFrame2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �t���[��2D�̏�����
		if (FAILED(pFrame2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �t���[��2D�̔j��
			SAFE_DELETE(pFrame2D);
			return nullptr;
		}

		// �ʒu��ݒ�
		pFrame2D->SetVec3Position(rPos);
		pFrame2D->m_originPos = rPos;

		// ������ݒ�
		pFrame2D->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pFrame2D->SetVec3Size(rSize);

		// �m�ۂ����A�h���X��Ԃ�
		return pFrame2D;
	}
}

//============================================================
//	�@�\�̕ύX����
//============================================================
HRESULT CFrame2D::ChangeModule(CFrame2DModule* pModule)
{
	// �@�\�̐����Ɏ��s���Ă���ꍇ������
	if (pModule == nullptr) { assert(false); return E_FAIL; }

	// �@�\�C���X�^���X���I��
	SAFE_UNINIT(m_pModule);

	// �@�\�C���X�^���X��ύX
	assert(m_pModule == nullptr);
	m_pModule = pModule;

	// �@�\�ɃR���e�L�X�g��ݒ�
	m_pModule->SetContext(this);

	// �@�\�C���X�^���X��������
	if (FAILED(m_pModule->Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�z�u�v���Z�b�g�̐ݒ菈��
//============================================================
void CFrame2D::SetPreset(const EPreset preset)
{
	// �ʒu��ݒ�
	SetVec3Position(FRAME_POS[preset]);

	// ������ݒ�
	SetVec3Rotation(FRAME_ROT[preset]);

	// �傫����ݒ�
	SetVec3Size(FRAME_SIZE[preset]);

	// �z�u�v���Z�b�g�̕ۑ�
	m_preset = preset;
}
