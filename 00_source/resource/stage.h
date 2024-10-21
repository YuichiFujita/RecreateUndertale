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
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void LimitPosition(VECTOR3& rPos, const float fRadius);				// �ʒu�͈͕␳
	inline void SetLimit(const SLimit& rLimit)	{ m_limit = rLimit; }	// �X�e�[�W�͈͐ݒ�
	inline SLimit GetLimit() const				{ return m_limit; }		// �X�e�[�W�͈͎擾

	void SetFadeRoom(const char* pStagePath);	// �J�ڐ惋�[���ݒ�
	inline HRESULT BindNextRoom() { return BindStage(m_sNextRoomPath.c_str()); }	// �J�ڐ惋�[������

	// �ÓI�����o�֐�
	static CStage* Create();				// ����
	static void Release(CStage*& prStage);	// �j��

private:
	// �����o�֐�
	HRESULT BindStage(const char* pStagePath);	// �X�e�[�W����
	HRESULT LoadLimit(std::ifstream* pFile, std::string& rString);	// �X�e�[�W�͈͏��̓Ǎ�
	HRESULT LoadMap(std::ifstream* pFile, std::string& rString);	// �}�b�v�^�C�����̓Ǎ�
	HRESULT LoadSpawn(std::ifstream* pFile, std::string& rString);	// �o���^�C�����̓Ǎ�
	HRESULT LoadTrans(std::ifstream* pFile, std::string& rString);	// �J�ڃ^�C�����̓Ǎ�

	// �����o�ϐ�
	std::string m_sNextRoomPath;	// �J�ڐ惋�[���p�X
	std::string m_sPrevRoomPath;	// �J�ڌ����[���p�X
	SLimit m_limit;	// �X�e�[�W�͈͏��
};

#endif	// _STAGE_H_
