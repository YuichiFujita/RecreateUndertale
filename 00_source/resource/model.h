//============================================================
//
//	���f���w�b�_�[ [model.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MODEL_H_
#define _MODEL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "extension.h"

//************************************************************
//	�N���X��`
//************************************************************
// ���f���N���X
class CModel
{
public:
	// �R���X�g���N�^
	CModel();

	// �f�X�g���N�^
	~CModel();

	// ���f���\����
	struct SModel
	{
		// �f�t�H���g�R���X�g���N�^
		SModel() :
			pMesh		(nullptr),				// ���b�V�� (���_���) �ւ̃|�C���^
			pBuffMat	(nullptr),				// �}�e���A���ւ̃|�C���^
			dwNumMat	(0),					// �}�e���A���̐�
			vtxMin		(VECTOR3( 9999.0f)),	// �ŏ��̒��_���W
			vtxMax		(VECTOR3(-9999.0f)),	// �ő�̒��_���W
			size		(VEC3_ZERO),			// �傫��
			fRadius		(0.0f),					// ���a
			pTextureIdx	(nullptr)				// �e�N�X�`���C���f�b�N�X
		{}

		// �f�X�g���N�^
		~SModel() {}

		// �����o�ϐ�
		LPD3DXMESH pMesh;		// ���b�V�� (���_���) �ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;	// �}�e���A���ւ̃|�C���^
		DWORD dwNumMat;			// �}�e���A���̐�
		VECTOR3 vtxMin;			// �ŏ��̒��_���W
		VECTOR3 vtxMax;			// �ő�̒��_���W
		VECTOR3 size;			// �傫��
		float fRadius;			// ���a
		int* pTextureIdx;		// �e�N�X�`���C���f�b�N�X
	};

	// �}�b�v���\����
	struct SMapInfo
	{
		// �f�t�H���g�R���X�g���N�^
		SMapInfo() :
			modelData		({}),	// ���f�����
			sFilePathName	("")	// �t�@�C���p�X��
		{}

		// �f�X�g���N�^
		~SMapInfo() {}

		// �����o�ϐ�
		SModel modelData;			// ���f�����
		std::string sFilePathName;	// �t�@�C���p�X��
	};

	// �����o�֐�
	HRESULT Init();		// ���f��������
	void Uninit();		// ���f���I��
	HRESULT LoadAll();	// ���f���S�Ǎ�
	int Regist(std::string sFilePath);	// ���f���o�^
	SModel* GetInfo(const int nIdx);	// ���f�����擾

	// �ÓI�����o�֐�
	static CModel* Create();				// ����
	static void Release(CModel* &pModel);	// �j��

private:
	// �����o�֐�
	HRESULT LoadXFileModel(SMapInfo* pMapInfo, std::string sFilePath);	// x�t�@�C���̓Ǎ�
	HRESULT LoadTextureModel(SMapInfo* pMapInfo);		// �e�N�X�`���̓Ǎ�
	HRESULT SetCollisionModel(SMapInfo* pMapInfo);		// �����蔻��̍쐬
	HRESULT SearchFolderAll(std::string sFolderPath);	// �t�H���_�S����

	// �����o�ϐ�
	std::map<int, SMapInfo> m_mapModel;	// ���f���A�z�z��
	extension::ALoad m_load;			// �ǂݍ��݉\�g���q
};

#endif	// _MODEL_H_
