//============================================================
//
//	�����L���O�}�l�[�W���[�w�b�_�[ [rankingManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RANKINGMANAGER_H_
#define _RANKINGMANAGER_H_

//************************************************************
//	�萔�錾
//************************************************************
namespace ranking
{
	const int NUM_DISP = 5;	// �����L���O�̏�ʕ\����
}

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X
class CAnim2D;		// �A�j���[�V����2D�N���X
class CTimeUI;		// �^�C��UI�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �����L���O�}�l�[�W���[�N���X
class CRankingManager
{
public:
	// �e�N�X�`����
	enum ETexture
	{
		TEXTURE_LOGO = 0,	// �����L���O���S�e�N�X�`��
		TEXTURE_RANK,		// �����L���O���ʃe�N�X�`��
		TEXTURE_MAX			// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,		// �������Ȃ����
		STATE_FADEIN,		// �t�F�[�h�C�����
		STATE_LOGO,			// �����L���O���S�\�����
		STATE_RANK,			// ���ʕ\�����
		STATE_TIME_WAIT,	// �N���A�^�C���\���ҋ@���
		STATE_TIME,			// �N���A�^�C���\�����
		STATE_WAIT,			// �J�ڑҋ@���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CRankingManager();

	// �f�X�g���N�^
	~CRankingManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);	// �X�V

	// �ÓI�����o�֐�
	static void Set(const float fValue);	// �ݒ�
	static CRankingManager *Create(void);	// ����
	static void Release(CRankingManager *&prRankingManager);	// �j��

private:
	// �����o�֐�
	void UpdateFade(void);		// �t�F�[�h�C���̍X�V
	void RevisionFade(void);	// �t�F�[�h�C���̕␳
	void InitLogo(void);		// �����L���O���S�\���̏�����
	void UpdateLogo(void);		// �����L���O���S�\���̍X�V
	void RevisionLogo(void);	// �����L���O���S�\���̕␳
	void InitRank(void);		// ���ʕ\���̏�����
	void UpdateRank(void);		// ���ʕ\���̍X�V
	void RevisionRank(void);	// ���ʕ\���̕␳
	void InitTime(void);		// �N���A�^�C���\���̏�����
	void UpdateTime(void);		// �N���A�^�C���\���̍X�V
	void RevisionTime(void);	// �N���A�^�C���\���̕␳
	void UpdateTransition(void);			// �J�ڌ���
	void SkipStaging(void);					// ���o�X�L�b�v
	bool UpdateDrawWait(const int nWait);	// �\���ҋ@

	// �ÓI�����o�֐�
	static void Sort(const float fValue);		// �\�[�g
	static void SetNewRank(const float fValue);	// �X�R�A�ϓ��C���f�b�N�X�ݒ�
	static void Save(void);	// �ۑ�
	static void Load(void);	// �Ǎ�

	// �ÓI�����o�ϐ�
	static float m_aRanking[ranking::NUM_DISP];	// �����L���O���
	static int m_nNewRankID;	// �ϓ������X�R�A�̃C���f�b�N�X

	// �����o�ϐ�
	CTimeUI *m_apTime[ranking::NUM_DISP];	// �N���A�^�C���̏��
	CAnim2D *m_apRank[ranking::NUM_DISP];	// ���ʂ̏��
	CObject2D *m_pLogo;		// �����L���O���S�̏��
	CObject2D *m_pFade;		// �t�F�[�h�̏��
	EState m_state;			// ���
	int m_nCounterState;	// ��ԊǗ��J�E���^�[
	int m_nCounterDraw;		// �`��Ǘ��J�E���^�[
	float m_fScale;			// �|���S���g�嗦
};

#endif	// _RANKINGMANAGER_H_