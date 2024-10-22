//============================================================
//
//	�f���^�^�C���w�b�_�[ [deltaTime.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _DELTATIME_H_
#define _DELTATIME_H_

//************************************************************
//	�N���X��`
//************************************************************
// �f���^�^�C���N���X
class CDeltaTime
{
public:
	// �R���X�g���N�^
	CDeltaTime();

	// �f�X�g���N�^
	~CDeltaTime();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	inline float GetDeltaTime() const			{ return m_fDeltaTime; }	// �o�ߎ��Ԏ擾
	inline float GetDeltaRate() const			{ return m_fDeltaRate; }	// �o�ߎ��Ԃ̊����擾
	inline float GetSlowRate() const			{ return m_fSlowRate; }		// ���x�ቺ�̊����擾
	inline void SetSlowRate(const float fRate)	{ m_fSlowRate = fRate; }	// ���x�ቺ�̊����ݒ�

	// �ÓI�����o�֐�
	static CDeltaTime* Create();					// ����
	static void Release(CDeltaTime*& prDeltaTime);	// �j��

private:
	// �����o�ϐ�
	DWORD m_dwOldTime;	// �O��̏����J�n����
	DWORD m_dwCurTime;	// ����̏����J�n����
	float m_fDeltaTime;	// �o�ߎ���
	float m_fDeltaRate;	// �o�ߎ��Ԃ̊���
	float m_fSlowRate;	// ���x�ቺ�̊���
};

#endif	// _DELTATIME_H_
