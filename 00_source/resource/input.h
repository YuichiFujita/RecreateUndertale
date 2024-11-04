//============================================================
//
//	���̓w�b�_�[ [input.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

//************************************************************
//	�N���X��`
//************************************************************
// ���̓N���X
class CInput
{
public:
	// �R���X�g���N�^
	CInput();

	// �f�X�g���N�^
	virtual ~CInput();

	// ���z�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	virtual void Uninit();	// �I��

	// �������z�֐�
	virtual void Update() = 0;	// �X�V

protected:
	// �����o�ϐ�
	static int m_nNumAll;				// ���̓f�o�C�X�̑���
	static LPDIRECTINPUT8 m_pInput;		// DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8  m_pDevice;	// DirectInput�f�o�C�X
};

// �L�[�{�[�h�N���X
class CInputKeyboard : public CInput
{
public:
	// �萔
	static constexpr int MAX_KEY = 256;	// �L�[�̍ő吔

	// �R���X�g���N�^
	CInputKeyboard();

	// �f�X�g���N�^
	~CInputKeyboard();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V

	// �ÓI�����o�֐�
	static CInputKeyboard* Create(HINSTANCE hInstance, HWND hWnd);	// ����
	static void Release(CInputKeyboard*& prKeyboard);				// �j��

	// �����o�֐�
	void InitPress();			// �v���X������
	void InitTrigger();			// �g���K�[������
	void InitRelease();			// �����[�X������
	bool IsPress(int nKey);		// �v���X�擾
	bool IsTrigger(int nKey);	// �g���K�[�擾
	bool IsRelease(int nKey);	// �����[�X�擾
	bool IsAnyPress();			// �S�v���X�擾
	bool IsAnyTrigger();		// �S�g���K�[�擾
	bool IsAnyRelease();		// �S�����[�X�擾

private:
	// �����o�ϐ�
	BYTE m_aKeyStatePress[MAX_KEY];		// �v���X���
	BYTE m_aKeyStateTrigger[MAX_KEY];	// �g���K�[���
	BYTE m_aKeyStateRelease[MAX_KEY];	// �����[�X���
};

// �}�E�X�N���X
class CInputMouse : public CInput
{
public:
	// �R���X�g���N�^
	CInputMouse();

	// �f�X�g���N�^
	~CInputMouse();

	// �}�E�X�L�[��
	enum EKey
	{
		KEY_LEFT = 0,	// �}�E�X�E�N���b�N
		KEY_RIGHT,		// �}�E�X���N���b�N
		KEY_WHEEL,		// �}�E�X�z�C�[����������
		KEY_MAX			// ���̗񋓌^�̑���
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V

	// �ÓI�����o�֐�
	static CInputMouse* Create(HINSTANCE hInstance, HWND hWnd);	// ����
	static void Release(CInputMouse*& prMouse);					// �j��

	// �����o�֐�
	bool IsPress(EKey mouKey);		// �v���X�擾
	bool IsTrigger(EKey mouKey);	// �g���K�[�擾
	bool IsRelease(EKey mouKey);	// �����[�X�擾
	bool IsAnyPress();				// �S�v���X�擾
	bool IsAnyTrigger();			// �S�g���K�[�擾
	bool IsAnyRelease();			// �S�����[�X�擾
	VECTOR3 GetMove();				// �ړ��ʎ擾

private:
	// �����o�ϐ�
	DIMOUSESTATE m_keyStatePress;	// �v���X���
	DIMOUSESTATE m_keyStateTrigger;	// �g���K�[���
	DIMOUSESTATE m_keyStateRelease;	// �����[�X���
};

// �p�b�h�N���X
class CInputPad
{
public:
	static constexpr int	MAX_NUM = 4;	// �p�b�h�̍ő吔
	static constexpr float	DEAD_ZONE = (float)USHRT_MAX * 0.1f;	// �X�e�B�b�N�̖�������X����

	// �R���X�g���N�^
	CInputPad();

	// �f�X�g���N�^
	~CInputPad();

	// �p�b�h�L�[��
	enum EKey
	{
		KEY_UP = 0,		// �����L�[ ��
		KEY_DOWN,		// �����L�[ ��
		KEY_LEFT,		// �����L�[ ��
		KEY_RIGHT,		// �����L�[ �E
		KEY_START,		// START�{�^��
		KEY_BACK,		// BACK�{�^��
		KEY_LSTICKPUSH,	// ���X�e�B�b�N��������
		KEY_RSTICKPUSH,	// �E�X�e�B�b�N��������
		KEY_LB,			// LB�{�^��
		KEY_RB,			// RB�{�^��
		KEY_LT,			// LT�{�^��
		KEY_RT,			// RT�{�^��
		KEY_A,			// A�{�^��
		KEY_B,			// B�{�^��
		KEY_X,			// X�{�^��
		KEY_Y,			// Y�{�^��
		KEY_LSTICK_X,	// ���X�e�B�b�N ���E
		KEY_LSTICK_Y,	// ���X�e�B�b�N �㉺
		KEY_RSTICK_X,	// �E�X�e�B�b�N ���E
		KEY_RSTICK_Y,	// �E�X�e�B�b�N �㉺
		KEY_MAX			// ���̗񋓌^�̑���
	};
	
	// �U����ޗ�
	enum EType
	{
		TYPE_NONE = 0,		// �������Ă��Ȃ�
		TYPE_DAMAGE,		// �_���[�W
		TYPE_BIG_DAMAGE,	// ��_���[�W
		TYPE_DEATH,			// ���S
		TYPE_WALLDASH,		// �Ǒ���
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �U���\����
	struct SVibration
	{
		// �f�t�H���g�R���X�g���N�^
		SVibration() :
			vibration	({}),			// �o�C�u���
			type		(TYPE_NONE),	// �o�C�u���
			nTime		(0)				// �o�C�u����
		{}

		// �f�X�g���N�^
		~SVibration() {}

		// �����o�ϐ�
		_XINPUT_VIBRATION vibration;	// �o�C�u���
		EType type;	// �o�C�u���
		int nTime;	// �o�C�u����
	};

	// �ÓI�����o�֐�
	static CInputPad* Create();				// ����
	static void Release(CInputPad*& prPad);	// �j��

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void SetVibration(EType type, int nPadIdx = 0);	// �o�C�u�ݒ�
	bool IsPress(EKey joyKey, int nPadIdx = 0);		// �v���X�擾	(�{�^��)
	bool IsTrigger(EKey joyKey, int nPadIdx = 0);	// �g���K�[�擾	(�{�^��)
	bool IsRelease(EKey joyKey, int nPadIdx = 0);	// �����[�X�擾	(�{�^��)

	bool IsPressAll(EKey joyKey);		// �S�v���X�擾		(�{�^��)
	bool IsTriggerAll(EKey joyKey);		// �S�g���K�[�擾	(�{�^��)
	bool IsReleaseAll(EKey joyKey);		// �S�����[�X�擾	(�{�^��)
	bool IsAnyPress(int nPadIdx = 0);	// �S�v���X�擾		(�{�^��)
	bool IsAnyTrigger(int nPadIdx = 0);	// �S�g���K�[�擾	(�{�^��)
	bool IsAnyRelease(int nPadIdx = 0);	// �S�����[�X�擾	(�{�^��)
	void InitPress(int nPadIdx = 0);	// �v���X������		(�{�^��)
	void InitTrigger(int nPadIdx = 0);	// �g���K�[������	(�{�^��)
	void InitRelease(int nPadIdx = 0);	// �����[�X������	(�{�^��)

	SHORT GetPressLStickX(int nPadIdx = 0);		// �v���X�擾 (L�X�e�B�b�NX)
	SHORT GetPressLStickY(int nPadIdx = 0);		// �v���X�擾 (L�X�e�B�b�NY)
	SHORT GetPressRStickX(int nPadIdx = 0);		// �v���X�擾 (R�X�e�B�b�NX)
	SHORT GetPressRStickY(int nPadIdx = 0);		// �v���X�擾 (R�X�e�B�b�NY)
	float GetPressLStickRot(int nPadIdx = 0);	// �v���X�擾 (L�X�e�B�b�N����)
	float GetPressRStickRot(int nPadIdx = 0);	// �v���X�擾 (R�X�e�B�b�N����)
	float GetPressLStickTilt(int nPadIdx = 0);	// �v���X�擾 (L�X�e�B�b�N�X��)
	float GetPressRStickTilt(int nPadIdx = 0);	// �v���X�擾 (R�X�e�B�b�N�X��)

private:
	// �����o�֐�
	void UpdateVibration(SVibration* pVibration, int nPadIdx);	// �o�C�u���[�V�����X�V

	// �����o�ϐ�
	SVibration   m_aVibration[MAX_NUM];			// �o�C�u���
	XINPUT_STATE m_aKeyStatePress[MAX_NUM];		// �v���X���
	XINPUT_STATE m_aKeyStateTrigger[MAX_NUM];	// �g���K�[���
	XINPUT_STATE m_aKeyStateRelease[MAX_NUM];	// �����[�X���
};

#endif	// _INPUT_H_
