//============================================================
//
//	�L�����N�^�[�A�j���[�V����3D�w�b�_�[ [characterAnim3D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _CHARACTER_ANIM3D_H_
#define _CHARACTER_ANIM3D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectCharaAnim3D.h"
#include "extension.h"

//************************************************************
//	�N���X��`
//************************************************************
// �L�����N�^�[�A�j���[�V����3D�N���X
class CCharacterAnim3D
{
public:
	// �R���X�g���N�^
	CCharacterAnim3D();

	// �f�X�g���N�^
	~CCharacterAnim3D();

	// ���[�V�������^�G�C���A�X��`
	using AMotion = CObjectCharaAnim3D::SInfo;

	// �����o�֐�
	HRESULT Init();		// �L�����N�^�[������
	void Uninit();		// �L�����N�^�[�I��
	HRESULT LoadAll();	// �L�����N�^�[�S�Ǎ�
	AMotion Regist(const char* pCharaPath);	// �L�����N�^�[�o�^

	// �ÓI�����o�֐�
	static CCharacterAnim3D* Create();	// ����
	static void Release(CCharacterAnim3D*& prCharacterAnim3D);	// �j��

private:
	// �����o�֐�
	HRESULT SearchFolderAll(std::string sFolderPath);	// �t�H���_�S����

	// �����o�֐�
	HRESULT LoadSetup(AMotion* pInfoChara, const char* pCharaPath);			// �L�����N�^�[���Z�b�g�A�b�v
	HRESULT LoadMotionSetup(AMotion* pInfoChara, const char* pMotionPath);	// ���[�V�������Z�b�g�A�b�v

	// �����o�ϐ�
	std::map<std::string, AMotion> m_mapCharacter;	// �L�����N�^�[�A�j���[�V����3D�A�z�z��
	extension::ALoad m_load;	// �ǂݍ��݉\�g���q
};

#endif	// _CHARACTER_ANIM3D_H_
