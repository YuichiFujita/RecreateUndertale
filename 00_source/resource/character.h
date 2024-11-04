//============================================================
//
//	�L�����N�^�[�w�b�_�[ [character.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "motion.h"
#include "extension.h"

//************************************************************
//	�N���X��`
//************************************************************
// �L�����N�^�[�N���X
class CCharacter
{
public:
	// �R���X�g���N�^
	CCharacter();

	// �f�X�g���N�^
	~CCharacter();

	// �p�[�c�\����
	struct SParts
	{
		// �f�t�H���g�R���X�g���N�^
		SParts() :
			sPath		(""),			// ���f���p�X���N���A
			pos			(VEC3_ZERO),	// �ʒu
			rot			(VEC3_ZERO),	// ����
			nParentIdx	(NONE_IDX)		// �e�C���f�b�N�X
		{}

		// �f�X�g���N�^
		~SParts() {}

		// �����o�ϐ�
		std::string sPath;	// ���f���p�X
		VECTOR3 pos;		// �ʒu
		VECTOR3 rot;		// ����
		int nParentIdx;		// �e�C���f�b�N�X
	};

	// �p�[�c���\����
	struct SPartsInfo
	{
		// �f�t�H���g�R���X�g���N�^
		SPartsInfo() :
			vecParts ({})	// �p�[�c���
		{}

		// �f�X�g���N�^
		~SPartsInfo() {}

		// �����o�֐�
		inline int GetNumParts() { return vecParts.size(); }	// �p�[�c���̑����擾

		// �����o�ϐ�
		std::vector<SParts> vecParts;	// �p�[�c���
	};

	// �L�����N�^�[���\����
	struct SCharaData
	{
		// �f�t�H���g�R���X�g���N�^
		SCharaData() :
			infoMotion	({}),	// ���[�V�������
			infoParts	({})	// �p�[�c���
		{}

		// �f�X�g���N�^
		~SCharaData() {}

		// �����o�ϐ�
		CMotion::SInfo infoMotion;	// ���[�V�������
		SPartsInfo infoParts;		// �p�[�c���
	};

	// �����o�֐�
	HRESULT Init();		// �L�����N�^�[������
	void Uninit();		// �L�����N�^�[�I��
	HRESULT LoadAll();	// �L�����N�^�[�S�Ǎ�
	SCharaData Regist(const char* pCharaPath);	// �L�����N�^�[�o�^

	// �ÓI�����o�֐�
	static CCharacter* Create();	// ����
	static void Release(CCharacter*& prCharacter);	// �j��

private:
	// �����o�֐�
	HRESULT SearchFolderAll(std::string sFolderPath);	// �t�H���_�S����

	// �����o�֐�
	HRESULT LoadSetup(SCharaData* pInfoChara, const char* pCharaPath);	// �L�����N�^�[���Z�b�g�A�b�v
	HRESULT LoadMotionSetup(CMotion::SInfo* pInfoMotion, const SPartsInfo* pInfoParts, const char* pMotionPath);	// ���[�V�������Z�b�g�A�b�v

	// �����o�ϐ�
	std::map<std::string, SCharaData> m_mapCharacter;	// �L�����N�^�[�A�z�z��
	extension::ALoad m_load;	// �ǂݍ��݉\�g���q
};

#endif	// _CHARACTER_H_
