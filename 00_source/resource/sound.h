//============================================================
//
//	�T�E���h�w�b�_�[ [sound.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//************************************************************
//	�N���X��`
//************************************************************
// �T�E���h�N���X
class CSound
{
public:
	// �R���X�g���N�^
	CSound();

	// �f�X�g���N�^
	~CSound();

	// �T�E���h��
	enum ELabel
	{
		LABEL_BGM_GENERAL = 0,		// BGM (�ėp)
		LABEL_BGM_TUTORIAL,			// BGM (�`���[�g���A��)
		LABEL_BGM_GAME,				// BGM (�Q�[��)

		LABEL_SE_SELECT_000,		// �I�𑀍쉹00
		LABEL_SE_SELECT_001,		// �I�𑀍쉹01
		LABEL_SE_DECISION_000,		// ���艹00
		LABEL_SE_DECISION_001,		// ���艹01
		LABEL_SE_DECISION_002,		// ���艹02
		LABEL_SE_SWORD_SWING_000,	// ���̕��؂艹00
		LABEL_SE_SWORD_SWING_001,	// ���̕��؂艹01
		LABEL_SE_SWORD_SWING_002,	// ���̕��؂艹02
		LABEL_SE_PLAYER_HIT,		// �v���C���[�̃q�b�g��
		LABEL_SE_SWORD_HIT,			// ���̃q�b�g��
		LABEL_SE_PLAYER_DEATH,		// �v���C���[�̎��S��
		LABEL_SE_SWORD_APPEAL,		// ���̃A�s�[����
		LABEL_SE_LAST_ATTACK,		// �ŏI�U����
		LABEL_SE_WALK,				// ����
		LABEL_SE_LAND_S,			// ���n�� (��)
		LABEL_SE_LAND_B,			// ���n�� (��)
		LABEL_SE_PLAYER_ACTION,		// �v���C���[�̃A�N�V������
		LABEL_SE_DRAGON_ROAR_L,		// �h���S�����K (��)
		LABEL_SE_DRAGON_ROAR_S,		// �h���S�����K (�Z)
		LABEL_SE_WING,				// �H�΂�����
		LABEL_SE_TELEPORT,			// �e���|�[�g��
		LABEL_SE_PUNCH,				// �p���`��
		LABEL_SE_CLAW,				// �Ђ�������
		LABEL_SE_TAIL,				// �����ۉ�
		LABEL_SE_NOISE,				// �m�C�Y��
		LABEL_SE_EXPLOSION,			// ������
		LABEL_SE_FIRE,				// ����
		LABEL_SE_THUNDER,			// ����
		LABEL_SE_THUNDER_WARN,		// ���x����
		LABEL_MAX					// ���̗񋓌^�̑���
	};

	// �T�E���h���\����
	struct SSoundInfo
	{
		const char *pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
	};

	// �����o�֐�
	HRESULT Init(HWND hWnd);	// ������
	void Uninit(void);			// �I��
	HRESULT LoadAll(HWND hWnd);	// �S�Ǎ�
	HRESULT Play(ELabel label);	// �Đ�
	void Stop(ELabel label);	// ��~
	void Stop(void);			// �S��~
	void SetVolume(const ELabel label, float fVolume);	// ���ʐݒ�
	float GetVolume(const ELabel label) const;			// ���ʎ擾
	void SetFrequency(const ELabel label, float fFreq);	// ���g���ݒ�
	float GetFrequency(const ELabel label) const;		// ���g���擾

	// �ÓI�����o�֐�
	static CSound *Create(HWND hWnd);		// ����
	static void Release(CSound *&pSound);	// �j��

private:
	// �����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);	// �`�����N�`�F�b�N
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// �`�����N�f�[�^�Ǎ�

	// �����o�ϐ�
	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif	// _SOUND_H_
