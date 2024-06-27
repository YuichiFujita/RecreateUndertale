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
		// �R���X�g���N�^
		SParts() :
			pos			(VEC3_ZERO),	// �ʒu
			rot			(VEC3_ZERO),	// ����
			nParentID	(NONE_IDX)		// �e�C���f�b�N�X
		{
			strPass.clear();	// ���f���p�X���N���A
		}

		// �����o�ϐ�
		std::string strPass;	// ���f���p�X
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
		int nParentID;			// �e�C���f�b�N�X
	};

	// �p�[�c���\����
	struct SPartsInfo
	{
		// �R���X�g���N�^
		SPartsInfo()
		{
			vecParts.clear();	// �p�[�c�����N���A
		}

		// �����o�֐�
		int GetNumParts(void) { return vecParts.size(); }	// �p�[�c���̑����擾

		// �����o�ϐ�
		std::vector<SParts> vecParts;	// �p�[�c���
	};

	// �L�����N�^�[���\����
	struct SCharaData
	{
		// �R���X�g���N�^
		SCharaData() {}

		// �����o�ϐ�
		CMotion::SInfo infoMotion;	// ���[�V�������
		SPartsInfo infoParts;		// �p�[�c���
	};

	// �����o�֐�
	HRESULT Init(void);		// �L�����N�^�[������
	void Uninit(void);		// �L�����N�^�[�I��
	HRESULT LoadAll(void);	// �L�����N�^�[�S�Ǎ�
	SCharaData Regist(const char *pCharaPass);	// �L�����N�^�[�o�^

	// �ÓI�����o�֐�
	static CCharacter *Create(void);	// ����
	static void Release(CCharacter *&prCharacter);	// �j��

private:
	// �����o�֐�
	HRESULT SearchFolderAll(std::string sFolderPath);	// �t�H���_�S����

	// �����o�֐�
	HRESULT LoadSetup(SCharaData *pInfoChara, const char *pCharaPass);	// �L�����N�^�[���Z�b�g�A�b�v
	HRESULT LoadMotionSetup(CMotion::SInfo *pInfoMotion, const SPartsInfo *pInfoParts, const char *pMotionPass);	// ���[�V�������Z�b�g�A�b�v

	// �����o�ϐ�
	std::map<std::string, SCharaData> m_mapCharacter;	// �L�����N�^�[�A�z�z��
};

#endif	// _CHARACTER_H_
