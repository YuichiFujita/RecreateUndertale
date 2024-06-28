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

	// �����o�֐�
	HRESULT Init(void);		// �L�����N�^�[������
	void Uninit(void);		// �L�����N�^�[�I��
	HRESULT LoadAll(void);	// �L�����N�^�[�S�Ǎ�
	CMotion2D::SInfo Regist(const char *pCharaPass);	// �L�����N�^�[�o�^

	// �ÓI�����o�֐�
	static CCharacter2D *Create(void);	// ����
	static void Release(CCharacter2D *&prCharacter2D);	// �j��

private:
	// �����o�֐�
	HRESULT SearchFolderAll(std::string sFolderPath);	// �t�H���_�S����

	// �����o�֐�
	HRESULT LoadSetup(CMotion2D::SInfo *pInfoChara, const char *pCharaPass);		// �L�����N�^�[���Z�b�g�A�b�v
	HRESULT LoadMotionSetup(CMotion2D::SInfo *pInfoChara, const char *pMotionPass);	// ���[�V�������Z�b�g�A�b�v

	// �����o�ϐ�
	std::map<std::string, CMotion2D::SInfo> m_mapCharacter;	// �L�����N�^�[2D�A�z�z��
};

#endif	// _CHARACTER2D_H_
