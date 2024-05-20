//============================================================
//
//	�^�C�}�[�w�b�_�[ [timer.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TIMER_H_
#define _TIMER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace timer
{
	const float	TIME_MIN = 0.0f;	// �ŏ��^�C��
	const float	TIME_MAX = 60.0f * 99.0f + 59.0f + 0.999f;	// �ő�^�C��
}

//************************************************************
//	�N���X��`
//************************************************************
// �^�C�}�[�N���X
class CTimer : public CObject
{
public:
	// �v����
	enum EState
	{
		STATE_NONE = 0,	// �����Ȃ�
		STATE_COUNT,	// �v����
		STATE_END,		// �v���I�� 
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CTimer();

	// �f�X�g���N�^
	~CTimer() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CTimer *Create	// ����
	( // ����
		const float fTime,	// �J�n����
		const float fLimit	// ��������
	);
	static CListManager<CTimer> *GetList(void);	// ���X�g�擾

	// �����o�֐�
	void Start(void);	// �v���J�n
	void End(void);		// �v���I��
	void EnableStop(const bool bStop);	// �v����~�ݒ�
	void AddTime(const float fTime);	// ���ԉ��Z
	void SetTime(const float fTime);	// ���Ԑݒ�
	void SetLimit(const float fLimit);	// �������Ԑݒ�
	float GetTime(void) const	{ return m_fTime; }		// ���Ԏ擾
	float GetLimit(void) const	{ return m_fLimit; }	// �������Ԏ擾
	EState GetState(void) const	{ return m_state; }		// �v����Ԏ擾
	int GetMin(void) const		{ return m_nMin; }		// ���擾
	int GetSec(void) const		{ return m_nSec; }		// �b�擾
	int GetMSec(void) const		{ return m_nMSec; }		// �~���b�擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void CountUp(const float fDeltaTime);	// �J�E���g�A�b�v
	void CountDown(const float fDeltaTime);	// �J�E���g�_�E��
	void CalcTime(void);	// ���Ԍv�Z

	// �ÓI�����o�ϐ�
	static CListManager<CTimer> *m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CTimer>::AIterator m_iterator;		// �C�e���[�^�[
	std::function<void(const float)> m_funcCount;	// �v���֐��|�C���^
	EState	m_state;	// �v�����
	float	m_fTime;	// �v������
	float	m_fLimit;	// ��������
	bool	m_bStop;	// �v����~��
	long	m_lTime;	// �v���~���b
	int		m_nMin;		// ��
	int		m_nSec;		// �b
	int		m_nMSec;	// �~���b
};

#endif	// _TIMER_H_
