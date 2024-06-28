//============================================================
//
//	�L�����N�^�[2D�w�b�_�[ [character2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _CHARACTER2D_H_
#define _CHARACTER2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "motion2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �L�����N�^�[2D�N���X
class CCharacter2D
{
public:
	// �R���X�g���N�^
	CCharacter2D();

	// �f�X�g���N�^
	~CCharacter2D();

	// �A�j���[�V�����\����
	struct SAnim
	{
		// �R���X�g���N�^
		SAnim() :
			ptrnTexture	(GRID2_ZERO),	// �e�N�X�`��������
			sizeChara	(VEC3_ZERO)		// �L�����N�^�[�傫��
		{
			sPassTexture.clear();	// �e�N�X�`���p�X���N���A
		}

		// �����o�ϐ�
		std::string sPassTexture;	// �e�N�X�`���p�X
		POSGRID2 ptrnTexture;		// �e�N�X�`��������
		D3DXVECTOR3 sizeChara;		// �L�����N�^�[�傫��
		float fNextTime;			// �p�^�[���ύX����
	};

	// �A�j���[�V�������\����
	struct SAnimInfo
	{
		// �R���X�g���N�^
		SAnimInfo()
		{
			vecAnim.clear();	// �A�j���[�V���������N���A
		}

		// �����o�֐�
		int GetNumAnim(void) { return vecAnim.size(); }	// �A�j���[�V�������̑����擾

		// �����o�ϐ�
		std::vector<SAnim> vecAnim;	// �A�j���[�V�������
	};

	// �L�����N�^�[���\����
	struct SCharaData
	{
		// �R���X�g���N�^
		SCharaData() {}

		// �����o�ϐ�
		CMotion2D::SInfo infoMotion;	// ���[�V�������
		SAnimInfo infoAnim;				// �A�j���[�V�������
	};

	// �����o�֐�
	HRESULT Init(void);		// �L�����N�^�[������
	void Uninit(void);		// �L�����N�^�[�I��
	HRESULT LoadAll(void);	// �L�����N�^�[�S�Ǎ�
	SCharaData Regist(const char *pCharaPass);	// �L�����N�^�[�o�^

	// �ÓI�����o�֐�
	static CCharacter2D *Create(void);	// ����
	static void Release(CCharacter2D *&prCharacter2D);	// �j��

private:
	// �����o�֐�
	HRESULT SearchFolderAll(std::string sFolderPath);	// �t�H���_�S����

	// �����o�֐�
	HRESULT LoadSetup(SCharaData *pInfoChara, const char *pCharaPass);			// �L�����N�^�[���Z�b�g�A�b�v
	HRESULT LoadMotionSetup(SCharaData *pInfoChara, const char *pMotionPass);	// ���[�V�������Z�b�g�A�b�v

	// �����o�ϐ�
	std::map<std::string, SCharaData> m_mapCharacter;	// �L�����N�^�[2D�A�z�z��
};

#endif	// _CHARACTER2D_H_
