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
#include "objectChara2D.h"

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

	// ���[�V�������^�G�C���A�X��`
	using AMotion = CObjectChara2D::SInfo;

	// �����o�֐�
	HRESULT Init();		// �L�����N�^�[������
	void Uninit();		// �L�����N�^�[�I��
	HRESULT LoadAll();	// �L�����N�^�[�S�Ǎ�
	AMotion Regist(const char* pCharaPath);	// �L�����N�^�[�o�^

	// �ÓI�����o�֐�
	static CCharacter2D* Create();	// ����
	static void Release(CCharacter2D*& prCharacter2D);	// �j��

private:
	// �����o�֐�
	HRESULT SearchFolderAll(std::string sFolderPath);	// �t�H���_�S����

	// �����o�֐�
	HRESULT LoadSetup(AMotion* pInfoChara, const char* pCharaPath);			// �L�����N�^�[���Z�b�g�A�b�v
	HRESULT LoadMotionSetup(AMotion* pInfoChara, const char* pMotionPath);	// ���[�V�������Z�b�g�A�b�v

	// �����o�ϐ�
	std::map<std::string, AMotion> m_mapCharacter;	// �L�����N�^�[2D�A�z�z��
};

#endif	// _CHARACTER2D_H_
