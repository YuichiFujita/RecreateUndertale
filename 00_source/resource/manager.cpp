//============================================================
//
//	�}�l�[�W���[���� [manager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "manager.h"
#include "object.h"
#include "deltaTime.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "fade.h"
#include "loading.h"
#include "texture.h"
#include "model.h"
#include "font.h"
#include "character.h"
#include "shader.h"
#include "retentionManager.h"
#include "debug.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CManager *CManager::m_pManager = nullptr;	// �}�l�[�W���[�I�u�W�F�N�g

//************************************************************
//	�e�N���X [CManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CManager::CManager() :
	m_hInstance		(nullptr),	// �C���X�^���X�n���h��
	m_hWnd			(nullptr),	// �E�C���h�E�n���h��
	m_pDeltaTime	(nullptr),	// �f���^�^�C���C���X�^���X
	m_pRenderer		(nullptr),	// �����_���[�C���X�^���X
	m_pKeyboard		(nullptr),	// �L�[�{�[�h�C���X�^���X
	m_pMouse		(nullptr),	// �}�E�X�C���X�^���X
	m_pPad			(nullptr),	// �p�b�h�C���X�^���X
	m_pSound		(nullptr),	// �T�E���h�C���X�^���X
	m_pCamera		(nullptr),	// �J�����C���X�^���X
	m_pLight		(nullptr),	// ���C�g�C���X�^���X
	m_pTexture		(nullptr),	// �e�N�X�`���C���X�^���X
	m_pModel		(nullptr),	// ���f���C���X�^���X
	m_pFont			(nullptr),	// �t�H���g�C���X�^���X
	m_pCharacter	(nullptr),	// �L�����N�^�[�C���X�^���X
	m_pFade			(nullptr),	// �t�F�[�h�C���X�^���X
	m_pLoading		(nullptr),	// ���[�f�B���O�C���X�^���X
	m_pScene		(nullptr),	// �V�[���C���X�^���X
	m_pRetention	(nullptr),	// �f�[�^�ۑ��}�l�[�W���[
	m_pDebugProc	(nullptr),	// �f�o�b�O�\��
	m_pDebug		(nullptr)	// �f�o�b�O
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CManager::~CManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//--------------------------------------------------------
	//	�����o�ϐ���������
	//--------------------------------------------------------
	m_hInstance		= hInstance;	// �C���X�^���X�n���h��
	m_hWnd			= hWnd;			// �E�C���h�E�n���h��
	m_pDeltaTime	= nullptr;		// �f���^�^�C���C���X�^���X
	m_pRenderer		= nullptr;		// �����_���[�C���X�^���X
	m_pKeyboard		= nullptr;		// �L�[�{�[�h�C���X�^���X
	m_pMouse		= nullptr;		// �}�E�X�C���X�^���X
	m_pPad			= nullptr;		// �p�b�h�C���X�^���X
	m_pSound		= nullptr;		// �T�E���h�C���X�^���X
	m_pCamera		= nullptr;		// �J�����C���X�^���X
	m_pLight		= nullptr;		// ���C�g�C���X�^���X
	m_pTexture		= nullptr;		// �e�N�X�`���C���X�^���X
	m_pModel		= nullptr;		// ���f���C���X�^���X
	m_pFont			= nullptr;		// �t�H���g�C���X�^���X
	m_pCharacter	= nullptr;		// �L�����N�^�[�C���X�^���X
	m_pFade			= nullptr;		// �t�F�[�h�C���X�^���X
	m_pLoading		= nullptr;		// ���[�f�B���O�C���X�^���X
	m_pScene		= nullptr;		// �V�[���C���X�^���X
	m_pRetention	= nullptr;		// �f�[�^�ۑ��}�l�[�W���[
	m_pDebugProc	= nullptr;		// �f�o�b�O�\��
	m_pDebug		= nullptr;		// �f�o�b�O

	//--------------------------------------------------------
	//	�V�X�e���̐���
	//--------------------------------------------------------
	// �f���^�^�C���̐���
	m_pDeltaTime = CDeltaTime::Create();
	if (m_pDeltaTime == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �����_���[�̐���
	m_pRenderer = CRenderer::Create(hWnd, bWindow);
	if (m_pRenderer == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �L�[�{�[�h�̐���
	m_pKeyboard = CInputKeyboard::Create(hInstance, hWnd);
	if (m_pKeyboard == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �}�E�X�̐���
	m_pMouse = CInputMouse::Create(hInstance, hWnd);
	if (m_pMouse == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �p�b�h�̐���
	m_pPad = CInputPad::Create();
	if (m_pPad == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �T�E���h�̐���
	m_pSound = CSound::Create(hWnd);
	if (m_pSound == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �J�����̐���
	m_pCamera = CCamera::Create();
	if (m_pCamera == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���C�g�̐���
	m_pLight = CLight::Create();
	if (m_pLight == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �f�[�^�ۑ��}�l�[�W���[�̐���
	m_pRetention = CRetentionManager::Create();
	if (m_pRetention == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	���̓Ǎ��E�ݒ�
	//--------------------------------------------------------
	// �e�N�X�`���̐���
	m_pTexture = CTexture::Create();
	if (m_pTexture == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���f���̐���
	m_pModel = CModel::Create();
	if (m_pModel == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �t�H���g�̐���
	m_pFont = CFont::Create();
	if (m_pFont == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �L�����N�^�[�̐���
	m_pCharacter = CCharacter::Create();
	if (m_pCharacter == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �����_�[�e�N�X�`���[�̐���
	if (FAILED(m_pRenderer->CreateRenderTexture()))
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �V�F�[�_�[�̐���
	if (FAILED(CShader::Create()))
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���[�f�B���O�̐���
	m_pLoading = CLoading::Create();
	if (m_pLoading == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �t�F�[�h�̐����E�V�[���̐ݒ�
	m_pFade = CFade::Create();
	if (m_pFade == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	�f�o�b�O�p
	//--------------------------------------------------------
	// �f�o�b�O�\���̐���
	m_pDebugProc = CDebugProc::Create();
	if (m_pDebugProc == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �f�o�b�O�̐���
	m_pDebug = CDebug::Create();
	if (m_pDebug == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�Ǎ�����
//============================================================
HRESULT CManager::Load(void)
{
#if NDEBUG	// Release�ňȊO�ł͑S�Ǎ����s��Ȃ�

	// �e�N�X�`���̑S�Ǎ�
	assert(m_pTexture != nullptr);
	if (FAILED(m_pTexture->LoadAll()))
	{ // �S�Ǎ��Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���f���̑S�Ǎ�
	assert(m_pModel != nullptr);
	if (FAILED(m_pModel->LoadAll()))
	{ // �S�Ǎ��Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �L�����N�^�[�̑S�Ǎ�
	assert(m_pCharacter != nullptr);
	if (FAILED(m_pCharacter->LoadAll()))
	{ // �S�Ǎ��Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

#endif	// NDEBUG

	// �t�H���g�̑S�Ǎ�
	assert(m_pFont != nullptr);
	if (FAILED(m_pFont->LoadAll()))
	{ // �S�Ǎ��Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �T�E���h�̑S�Ǎ�
	assert(m_pSound != nullptr);
	if (FAILED(m_pSound->LoadAll(m_hWnd)))
	{ // �S�Ǎ��Ɏ��s�����ꍇ

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
void CManager::Uninit(void)
{
	//--------------------------------------------------------
	//	�f�o�b�O�p
	//--------------------------------------------------------
	// �f�o�b�O�\���̔j��
	SAFE_REF_RELEASE(m_pDebugProc);

	// �f�o�b�O�̔j��
	SAFE_REF_RELEASE(m_pDebug);

	//--------------------------------------------------------
	//	�X���b�h�̔j��
	//--------------------------------------------------------
	// ���[�f�B���O�̔j��
	SAFE_REF_RELEASE(m_pLoading);

	//--------------------------------------------------------
	//	���̔j��
	//--------------------------------------------------------
	// �e�N�X�`���̔j��
	SAFE_REF_RELEASE(m_pTexture);

	// ���f���̔j��
	SAFE_REF_RELEASE(m_pModel);

	// �t�H���g�̔j��
	SAFE_REF_RELEASE(m_pFont);

	// �L�����N�^�[�̔j��
	SAFE_REF_RELEASE(m_pCharacter);

	// �V�F�[�_�[�̔j��
	CShader::Release();

	//--------------------------------------------------------
	//	�V�X�e���̔j��
	//--------------------------------------------------------
	// �f�[�^�ۑ��}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pRetention);

	// �V�[���̔j��
	SAFE_REF_RELEASE(m_pScene);

	// �t�F�[�h�̔j��
	SAFE_REF_RELEASE(m_pFade);

	// ���C�g�̔j��
	SAFE_REF_RELEASE(m_pLight);

	// �J�����̔j��
	SAFE_REF_RELEASE(m_pCamera);

	// �T�E���h�̔j��
	SAFE_REF_RELEASE(m_pSound);

	// �p�b�h�̔j��
	SAFE_REF_RELEASE(m_pPad);

	// �}�E�X�̔j��
	SAFE_REF_RELEASE(m_pMouse);

	// �L�[�{�[�h�̔j��
	SAFE_REF_RELEASE(m_pKeyboard);

	// �����_���[�̔j��
	SAFE_REF_RELEASE(m_pRenderer);

	// �f���^�^�C���̔j��
	SAFE_REF_RELEASE(m_pDeltaTime);

	// �I�u�W�F�N�g�̑S�j��
	CObject::ReleaseAll();

	// ��O����
	assert(CObject::GetNumAll() == 0);	// �j���̎��s
}

//============================================================
//	�X�V����
//============================================================
void CManager::Update(void)
{
	// �f�o�b�O���̍X�V�E�`��
	assert(m_pDebug != nullptr);
	m_pDebug->UpdateDebugControl();
	m_pDebug->DrawDebugControl();
	m_pDebug->DrawDebugData();

	// �f���^�^�C���̍X�V
	assert(m_pDeltaTime != nullptr);
	m_pDeltaTime->Update();

	// �f���^�^�C�����擾
	const float fDeltaTime = m_pDeltaTime->GetTime();

	// �p�b�h�̍X�V
	assert(m_pPad != nullptr);
	m_pPad->Update();

	// �}�E�X�̍X�V
	assert(m_pMouse != nullptr);
	m_pMouse->Update();

	// �L�[�{�[�h�̍X�V
	assert(m_pKeyboard != nullptr);
	m_pKeyboard->Update();

	// ���[�f�B���O�̍X�V
	assert(m_pLoading != nullptr);
	m_pLoading->Update(fDeltaTime);

	// �t�F�[�h�̍X�V
	assert(m_pFade != nullptr);
	m_pFade->Update(fDeltaTime);

	if (m_pLoading->GetState() == CLoading::LOAD_NONE)
	{ // ���[�h���Ă��Ȃ��ꍇ

		// �V�[���̍X�V
		assert(m_pScene != nullptr);
		m_pScene->Update(fDeltaTime);
	}

	// �f�o�b�O�\���̍X�V
	assert(m_pDebugProc != nullptr);
	m_pDebugProc->Update();
}

//============================================================
//	�`�揈��
//============================================================
void CManager::Draw(void)
{
	// �����_���[�̕`��
	assert(m_pRenderer != nullptr);
	m_pRenderer->Draw();
}

//============================================================
//	��������
//============================================================
CManager *CManager::Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �C���X�^���X�g�p��
	assert(m_pManager == nullptr);

	// �}�l�[�W���[�̐���
	m_pManager = new CManager;
	if (m_pManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �}�l�[�W���[�̏�����
		if (FAILED(m_pManager->Init(hInstance, hWnd, bWindow)))
		{ // �������Ɏ��s�����ꍇ

			// �}�l�[�W���[�̔j��
			SAFE_DELETE(m_pManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return m_pManager;
	}
}

//============================================================
//	�擾����
//============================================================
CManager *CManager::GetInstance(void)
{
	// �C���X�^���X���g�p
	assert(m_pManager != nullptr);

	// �}�l�[�W���[�̃|�C���^��Ԃ�
	return m_pManager;
}

//============================================================
//	�j������
//============================================================
void CManager::Release(CManager *&prManager)
{
	// �}�l�[�W���[�̏I��
	assert(prManager != nullptr);
	prManager->Uninit();

	// �������J��
	SAFE_DELETE(prManager);
}

//============================================================
//	�E�C���h�E�j������
//============================================================
void CManager::ReleaseWindow(void)
{
	// �E�C���h�E��j������
	DestroyWindow(m_pManager->m_hWnd);	// WM_DESTROY���b�Z�[�W�𑗂�
}

//============================================================
//	�V�[���̐ݒ菈�� (�t�F�[�h�FON)
//============================================================
void CManager::SetFadeScene(const CScene::EMode mode, const int nWait)
{
	// �C���X�^���X���g�p
	assert(m_pFade != nullptr);

	// ���̃V�[����ݒ�
	m_pFade->Set(mode, nWait);
}

//============================================================
//	�V�[���̐ݒ菈�� (�t�F�[�h�FOFF)
//============================================================
HRESULT CManager::SetScene(const CScene::EMode mode)
{
	// �T�E���h���~
	assert(m_pSound != nullptr);
	m_pSound->Stop();

	// �V�[����j��
	SAFE_REF_RELEASE(m_pScene);

	// �I�u�W�F�N�g�̑S�j��
	CObject::ReleaseAll();

	// �V�[���̐���
	assert(m_pScene == nullptr);
	m_pScene = CScene::Create(mode);
	if (m_pScene == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �V�[���̏�����
	if (FAILED(m_pScene->Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�V�[���̏���������
//============================================================
HRESULT CManager::InitScene(const CScene::EMode mode)
{
	// �V�[���̐���
	assert(m_pScene == nullptr);
	m_pScene = CScene::Create(mode);
	if (m_pScene == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �����_���̍쐬
	auto func = [this](bool *pFuncEnd) -> HRESULT
	{
		// ��O����
		assert(pFuncEnd != nullptr);	// �t���O�A�h���X���w��Ȃ�
		assert(!(*pFuncEnd));			// �t���O�����ɃI��

		// �}�l�[�W���[�̓Ǎ�
		if (FAILED(m_pManager->Load()))
		{ // �Ǎ��Ɏ��s�����ꍇ

			*pFuncEnd = true;	// �����̏I����ݒ�
			return E_FAIL;
		}

		// �V�[���̏�����
		if (FAILED(m_pScene->Init()))
		{ // �������Ɏ��s�����ꍇ

			*pFuncEnd = true;	// �����̏I����ݒ�
			return E_FAIL;
		}

		*pFuncEnd = true;	// �����̏I����ݒ�
		return S_OK;
	};

	// ���s���鏉�����֐���n�����[�h�J�n
	assert(m_pLoading != nullptr);
	if (FAILED(m_pLoading->Set(func)))
	{ // ���[�f�B���O�J�n�Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	���[�h�̐ݒ菈��
//============================================================
HRESULT CManager::SetMode(const CScene::EMode mode)
{
	// �T�E���h���~
	assert(m_pSound != nullptr);
	m_pSound->Stop();

	// �V�[����j��
	SAFE_REF_RELEASE(m_pScene);

	// �I�u�W�F�N�g�̑S�j��
	CObject::ReleaseAll();

	// �V�[���̐���
	assert(m_pScene == nullptr);
	m_pScene = CScene::Create(mode);
	if (m_pScene == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �����_���̍쐬
	auto func = [this](bool *pFuncEnd) -> HRESULT
	{
		// ��O����
		assert(pFuncEnd != nullptr);	// �t���O�A�h���X���w��Ȃ�
		assert(!(*pFuncEnd));			// �t���O�����ɃI��

		// �V�[���̏�����
		if (FAILED(m_pScene->Init()))
		{ // �������Ɏ��s�����ꍇ

			*pFuncEnd = true;	// �����̏I����ݒ�
			return E_FAIL;
		}

		*pFuncEnd = true;	// �����̏I����ݒ�
		return S_OK;
	};

	// ���s���鏉�����֐���n�����[�h�J�n
	assert(m_pLoading != nullptr);
	if (FAILED(m_pLoading->Set(func)))
	{ // ���[�f�B���O�J�n�Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	���[�h�̎擾����
//============================================================
CScene::EMode CManager::GetMode(void)
{
	// �C���X�^���X���g�p
	assert(m_pScene != nullptr);

	// ���݂̃��[�h��Ԃ�
	return m_pScene->GetMode();
}

//============================================================
//	�f���^�^�C���擾����
//============================================================
CDeltaTime *CManager::GetDeltaTime(void)
{
	// �C���X�^���X���g�p
	assert(m_pDeltaTime != nullptr);

	// �f���^�^�C���̃|�C���^��Ԃ�
	return m_pDeltaTime;
}

//============================================================
//	�����_���[�擾����
//============================================================
CRenderer *CManager::GetRenderer(void)
{
	// �C���X�^���X���g�p
	assert(m_pRenderer != nullptr);

	// �����_���[�̃|�C���^��Ԃ�
	return m_pRenderer;
}

//============================================================
//	�L�[�{�[�h�擾����
//============================================================
CInputKeyboard *CManager::GetKeyboard(void)
{
	// �C���X�^���X���g�p
	assert(m_pKeyboard != nullptr);

	// �L�[�{�[�h�̃|�C���^��Ԃ�
	return m_pKeyboard;
}

//============================================================
//	�}�E�X�擾����
//============================================================
CInputMouse *CManager::GetMouse(void)
{
	// �C���X�^���X���g�p
	assert(m_pMouse != nullptr);

	// �}�E�X�̃|�C���^��Ԃ�
	return m_pMouse;
}

//============================================================
//	�p�b�h�擾����
//============================================================
CInputPad *CManager::GetPad(void)
{
	// �C���X�^���X���g�p
	assert(m_pPad != nullptr);

	// �p�b�h�̃|�C���^��Ԃ�
	return m_pPad;
}

//============================================================
//	�T�E���h�擾����
//============================================================
CSound *CManager::GetSound(void)
{
	// �C���X�^���X���g�p
	assert(m_pSound != nullptr);

	// �T�E���h�̃|�C���^��Ԃ�
	return m_pSound;
}

//============================================================
//	�J�����擾����
//============================================================
CCamera *CManager::GetCamera(void)
{
	// �C���X�^���X���g�p
	assert(m_pCamera != nullptr);

	// �J�����̃|�C���^��Ԃ�
	return m_pCamera;
}

//============================================================
//	���C�g�擾����
//============================================================
CLight *CManager::GetLight(void)
{
	// �C���X�^���X���g�p
	assert(m_pLight != nullptr);

	// ���C�g�̃|�C���^��Ԃ�
	return m_pLight;
}

//============================================================
//	�e�N�X�`���擾����
//============================================================
CTexture *CManager::GetTexture(void)
{
	// �C���X�^���X���g�p
	assert(m_pTexture != nullptr);

	// �e�N�X�`���̃|�C���^��Ԃ�
	return m_pTexture;
}

//============================================================
//	���f���擾����
//============================================================
CModel *CManager::GetModel(void)
{
	// �C���X�^���X���g�p
	assert(m_pModel != nullptr);

	// ���f���̃|�C���^��Ԃ�
	return m_pModel;
}

//============================================================
//	�t�H���g�擾����
//============================================================
CFont *CManager::GetFont(void)
{
	// �C���X�^���X���g�p
	assert(m_pFont != nullptr);

	// �t�H���g�̃|�C���^��Ԃ�
	return m_pFont;
}

//============================================================
//	�L�����N�^�[�擾����
//============================================================
CCharacter *CManager::GetCharacter(void)
{
	// �C���X�^���X���g�p
	assert(m_pCharacter != nullptr);

	// �L�����N�^�[��Ԃ�
	return m_pCharacter;
}

//============================================================
//	�t�F�[�h�擾����
//============================================================
CFade *CManager::GetFade(void)
{
	// �C���X�^���X���g�p
	assert(m_pFade != nullptr);

	// �t�F�[�h�̃|�C���^��Ԃ�
	return m_pFade;
}

//============================================================
//	���[�f�B���O�擾����
//============================================================
CLoading *CManager::GetLoading(void)
{
	// �C���X�^���X���g�p
	assert(m_pLoading != nullptr);

	// ���[�f�B���O�̃|�C���^��Ԃ�
	return m_pLoading;
}

//============================================================
//	�V�[���擾����
//============================================================
CScene *CManager::GetScene(void)
{
	// �C���X�^���X���g�p
	assert(m_pScene != nullptr);

	// �V�[���̃|�C���^��Ԃ�
	return m_pScene;
}

//============================================================
//	�f�[�^�ۑ��}�l�[�W���[�擾����
//============================================================
CRetentionManager *CManager::GetRetention(void)
{
	// �C���X�^���X���g�p
	assert(m_pRetention != nullptr);

	// �f�[�^�ۑ��}�l�[�W���[��Ԃ�
	return m_pRetention;
}

//============================================================
//	�f�o�b�O�\���擾����
//============================================================
CDebugProc *CManager::GetDebugProc(void)
{
	// �C���X�^���X���g�p
	assert(m_pDebugProc != nullptr);

	// �f�o�b�O�\���̃|�C���^��Ԃ�
	return m_pDebugProc;
}

//============================================================
//	�f�o�b�O�擾����
//============================================================
CDebug *CManager::GetDebug(void)
{
	// �C���X�^���X���g�p
	assert(m_pDebug != nullptr);

	// �f�o�b�O�̃|�C���^��Ԃ�
	return m_pDebug;
}
