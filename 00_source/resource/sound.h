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
		LABEL_NONE = NONE_IDX,	// ���x������
		LABEL_BGM_GENERAL,		// BGM (�ėp)
		LABEL_SE_INTRONOISE,	// �C���g���m�C�Y
		LABEL_SE_CYMBAL,		// �t�V���o��
		LABEL_SE_BALLCHIME,		// BALL���͌��ʉ�
		LABEL_SE_TEXT00,		// ��������\���� (�C���Q�[��)
		LABEL_SE_TEXT01,		// ��������\���� (�C���g��)
		LABEL_MAX				// ���̗񋓌^�̑���
	};

	// �����o�֐�
	HRESULT Init(HWND hWnd);	// ������
	void Uninit();				// �I��
	HRESULT LoadAll(HWND hWnd);	// �S�Ǎ�
	HRESULT Play(ELabel label);	// �Đ�
	void Stop(ELabel label);	// ��~
	void Stop();				// �S��~
	void SetVolume(const ELabel label, float fVolume);	// ���ʐݒ�
	float GetVolume(const ELabel label) const;			// ���ʎ擾
	void SetFrequency(const ELabel label, float fFreq);	// ���g���ݒ�
	float GetFrequency(const ELabel label) const;		// ���g���擾

	// �ÓI�����o�֐�
	static CSound* Create(HWND hWnd);		// ����
	static void Release(CSound*& prSound);	// �j��

private:
	// �����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);	// �`�����N�`�F�b�N
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// �`�����N�f�[�^�Ǎ�

	// �����o�ϐ�
	IXAudio2* m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif	// _SOUND_H_
