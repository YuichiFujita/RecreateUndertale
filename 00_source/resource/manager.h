//============================================================
//
//	�}�l�[�W���[�w�b�_�[ [manager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scene.h"
#include "fade.h"

//************************************************************
//	�O���錾
//************************************************************
class CDeltaTime;		// �f���^�^�C���N���X
class CRenderer;		// �����_���[�N���X
class CInputKeyboard;	// �L�[�{�[�h�N���X
class CInputMouse;		// �}�E�X�N���X
class CInputPad;		// �p�b�h�N���X
class CSound;			// �T�E���h�N���X
class CCamera;			// �J�����N���X
class CLightManager;	// ���C�g�}�l�[�W���[�N���X
class CTexture;			// �e�N�X�`���N���X
class CModel;			// ���f���N���X
class CFont;			// �t�H���g�N���X
class CCharacter;		// �L�����N�^�[�N���X
class CCharacterAnim3D;	// �L�����N�^�[�A�j���[�V����3D�N���X
class CItem;			// �A�C�e���N���X
class CLoading;			// ���[�f�B���O�N���X
class CRetention;		// �f�[�^�ۑ��N���X
class CDebugProc;		// �f�o�b�O�\���N���X
class CDebug;			// �f�o�b�O�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �}�l�[�W���[�N���X
class CManager
{
public:
	// �R���X�g���N�^
	CManager();

	// �f�X�g���N�^
	~CManager();

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// ������
	HRESULT Load();	// �Ǎ�
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

	// �ÓI�����o�֐�
	static CManager* Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// ����
	static CManager* GetInstance();				// �擾
	static void Release(CManager*& prManager);	// �j��
	static void ReleaseWindow();				// �E�C���h�E�j��

	// �����o�֐�
	HRESULT InitScene(const CScene::EMode mode);	// �V�[��������
	HRESULT SetScene(const CScene::EMode mode);		// �V�[���ݒ� (�t�F�[�h����[�h�FOFF)

	void SetFadeScene	// �V�[���ݒ� (�t�F�[�h�FON, ���[�h�FOFF)
	( // ����
		const CScene::EMode mode,		// �J�ڐ惂�[�h
		const float fWaitTime	= 0.0f,	// �]�C����
		const float fAddOut		= CFade::DEF_LEVEL,		// �A�E�g�̃��l������
		const float fSubIn		= CFade::DEF_LEVEL,		// �C���̃��l������
		const COLOR colFade		= color::Black(0.0f)	// �t�F�[�h�F
	);
	void SetLoadScene	// �V�[���ݒ� (�t�F�[�h����[�h�FON)
	( // ����
		const CScene::EMode mode,		// �J�ڐ惂�[�h
		const float fWaitTime	= 0.0f,	// �]�C����
		const float fAddOut		= CFade::DEF_LEVEL,		// �A�E�g�̃��l������
		const float fSubIn		= CFade::DEF_LEVEL,		// �C���̃��l������
		const COLOR colFade		= color::Black(0.0f)	// �t�F�[�h�F
	);

	HRESULT SetMode();			// ���[�h�ݒ� (���[�h�FOFF)
	HRESULT SetLoadMode();		// ���[�h�ݒ� (���[�h�FON)
	CScene::EMode GetMode();	// ���[�h�擾

	CDeltaTime*			GetDeltaTime();			// �f���^�^�C���擾
	CRenderer*			GetRenderer();			// �����_���[�擾
	CInputKeyboard*		GetKeyboard();			// �L�[�{�[�h�擾
	CInputMouse*		GetMouse();				// �}�E�X�擾
	CInputPad*			GetPad();				// �p�b�h�擾
	CSound*				GetSound();				// �T�E���h�擾
	CCamera*			GetCamera();			// �J�����擾
	CLightManager*		GetLight();				// ���C�g�}�l�[�W���[�擾
	CTexture*			GetTexture();			// �e�N�X�`���擾
	CModel*				GetModel();				// ���f���擾
	CFont*				GetFont();				// �t�H���g�擾
	CCharacter*			GetCharacter();			// �L�����N�^�[�擾
	CCharacterAnim3D*	GetCharacterAnim3D();	// �L�����N�^�[�A�j���[�V����3D�擾
	CItem*				GetItem();				// �A�C�e���擾
	CFade*				GetFade();				// �t�F�[�h�擾
	CLoading*			GetLoading();			// ���[�f�B���O�擾
	CScene*				GetScene();				// �V�[���擾
	CRetention*			GetRetention();			// �f�[�^�ۑ��擾
	CDebugProc*			GetDebugProc();			// �f�o�b�O�\���擾
	CDebug*				GetDebug();				// �f�o�b�O�擾

private:
	// �ÓI�����o�ϐ�
	static CManager* m_pManager;	// �}�l�[�W���[

	// �����o�ϐ�
	HINSTANCE			m_hInstance;		// �C���X�^���X�n���h��
	HWND				m_hWnd;				// �E�C���h�E�n���h��
	CDeltaTime*			m_pDeltaTime;		// �f���^�^�C���C���X�^���X
	CRenderer*			m_pRenderer;		// �����_���[�C���X�^���X
	CInputKeyboard*		m_pKeyboard;		// �L�[�{�[�h�C���X�^���X
	CInputMouse*		m_pMouse;			// �}�E�X�C���X�^���X
	CInputPad*			m_pPad;				// �p�b�h�C���X�^���X
	CSound*				m_pSound;			// �T�E���h�C���X�^���X
	CCamera*			m_pCamera;			// �J�����C���X�^���X
	CLightManager*		m_pLight;			// ���C�g�}�l�[�W���[�C���X�^���X
	CTexture*			m_pTexture;			// �e�N�X�`���C���X�^���X
	CModel*				m_pModel;			// ���f���C���X�^���X
	CFont*				m_pFont;			// �t�H���g�C���X�^���X
	CCharacter*			m_pCharacter;		// �L�����N�^�[�C���X�^���X
	CCharacterAnim3D*	m_pCharacterAnim3D;	// �L�����N�^�[�A�j���[�V����3D�C���X�^���X
	CItem*				m_pItem;			// �A�C�e���C���X�^���X
	CFade*				m_pFade;			// �t�F�[�h�C���X�^���X
	CLoading*			m_pLoading;			// ���[�f�B���O�C���X�^���X
	CScene*				m_pScene;			// �V�[���C���X�^���X
	CRetention*			m_pRetention;		// �f�[�^�ۑ��C���X�^���X
	CDebugProc*			m_pDebugProc;		// �f�o�b�O�\��
	CDebug*				m_pDebug;			// �f�o�b�O
};

#endif	// _MANAGER_H_
