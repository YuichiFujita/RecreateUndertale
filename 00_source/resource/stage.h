//============================================================
//
//	�X�e�[�W�w�b�_�[ [stage.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _STAGE_H_
#define _STAGE_H_

//************************************************************
//	�N���X��`
//************************************************************
// �X�e�[�W�N���X
class CStage
{
public:
	// �R���X�g���N�^
	CStage();

	// �f�X�g���N�^
	~CStage();

	// �X�e�[�W�͈͍\����
	struct SLimit
	{
		float fUp;		// �����ʒu (��)
		float fDown;	// �����ʒu (��)
		float fLeft;	// �����ʒu (��)
		float fRight;	// �����ʒu (�E)
	};

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	HRESULT BindStage(const char *pStagePass);	// �X�e�[�W����
	void LimitPosition(D3DXVECTOR3& rPos, const float fRadius);	// �ʒu�͈͕␳
	void SetLimit(const SLimit& rLimit)	{ m_limit = rLimit; }	// �X�e�[�W�͈͐ݒ�
	SLimit GetLimit(void) const			{ return m_limit; }		// �X�e�[�W�͈͎擾

	// �ÓI�����o�֐�
	static CStage *Create(void);			// ����
	static void Release(CStage *&prStage);	// �j��

private:
	// �����o�֐�
	HRESULT LoadLimit(std::ifstream *pFile, std::string& rString);	// �X�e�[�W�͈͏��̓Ǎ�

	// �����o�ϐ�
	SLimit m_limit;	// �X�e�[�W�͈͏��
};

#endif	// _STAGE_H_
