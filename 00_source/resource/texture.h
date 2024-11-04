//============================================================
//
//	�e�N�X�`���w�b�_�[ [texture.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "extension.h"

//************************************************************
//	�N���X��`
//************************************************************
// �e�N�X�`���N���X
class CTexture
{
public:
	// �R���X�g���N�^
	CTexture();

	// �f�X�g���N�^
	~CTexture();

	// �e�N�X�`���������\����
	struct SInfo
	{
	public:
		// �f�t�H���g�R���X�g���N�^
		SInfo() :
			Width		(0),	// �e�N�X�`������
			Height		(0),	// �e�N�X�`���c��
			MipLevels	(0),	// �~�b�v�}�b�v���x��
			Usage		(0),	// �����E�m�ۃI�v�V����
			Format		(D3DFMT_UNKNOWN),	// �s�N�Z���t�H�[�}�b�g
			Pool		(D3DPOOL_DEFAULT)	// �i�[������
		{}

		// �����t���R���X�g���N�^
		SInfo(const UINT in_nWidth, const UINT in_nHeight, const UINT in_nMip, const DWORD in_dwUsage, const D3DFORMAT in_format, const D3DPOOL in_pool) :
			Width		(in_nWidth),	// �e�N�X�`������
			Height		(in_nHeight),	// �e�N�X�`���c��
			MipLevels	(in_nMip),		// �~�b�v�}�b�v���x��
			Usage		(in_dwUsage),	// �����E�m�ۃI�v�V����
			Format		(in_format),	// �s�N�Z���t�H�[�}�b�g
			Pool		(in_pool)		// �i�[������
		{}

		// �f�X�g���N�^
		~SInfo() {}

		// �����o�ϐ�
		UINT		Width;		// �e�N�X�`������
		UINT		Height;		// �e�N�X�`���c��
		UINT		MipLevels;	// �~�b�v�}�b�v���x��
		DWORD		Usage;		// �����E�m�ۃI�v�V����
		D3DFORMAT	Format;		// �s�N�Z���t�H�[�}�b�g
		D3DPOOL		Pool;		// �i�[������
	};

	// �e�N�X�`���\����
	struct STexture
	{
		// �f�t�H���g�R���X�g���N�^
		STexture() :
			pTexture (nullptr),		// �e�N�X�`���ւ̃|�C���^
			status	 ({}),			// �e�N�X�`���X�e�[�^�X�ւ̃|�C���^
			aspect	 (VEC2_ZERO)	// �A�X�y�N�g��
		{}

		// �f�X�g���N�^
		~STexture() {}

		// �����o�ϐ�
		LPDIRECT3DTEXTURE9 pTexture;	// �e�N�X�`���ւ̃|�C���^
		D3DXIMAGE_INFO status;			// �e�N�X�`���X�e�[�^�X�ւ̃|�C���^
		VECTOR2 aspect;					// �A�X�y�N�g��
	};

	// �}�b�v���\����
	struct SMapInfo
	{
		// �f�t�H���g�R���X�g���N�^
		SMapInfo() :
			textureData		({}),	// �e�N�X�`�����
			sFilePathName	("")	// �t�@�C���p�X��
		{}

		// �f�X�g���N�^
		~SMapInfo() {}

		// �����o�ϐ�
		STexture textureData;		// �e�N�X�`�����
		std::string sFilePathName;	// �t�@�C���p�X��
	};

	// �����o�֐�
	HRESULT Init();		// �e�N�X�`��������
	void Uninit();		// �e�N�X�`���I��
	HRESULT LoadAll();	// �e�N�X�`���S�Ǎ�
	int Regist(const SInfo info);				// �e�N�X�`���o�^ (����)
	int Regist(std::string sFilePath);			// �e�N�X�`���o�^ (�p�X)
	STexture GetInfo(const int nIdx);			// �e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 GetPtr(const int nIdx);	// �e�N�X�`���|�C���^�擾

	// �ÓI�����o�֐�
	static CTexture* Create();					// ����
	static void Release(CTexture*& prTexture);	// �j��

private:
	// �����o�֐�
	HRESULT SearchFolderAll(std::string sFolderPath);	// �t�H���_�S����

	// �����o�ϐ�
	std::map<int, SMapInfo> m_mapTexture;	// �e�N�X�`���A�z�z��
	extension::ALoad m_load;				// �ǂݍ��݉\�g���q
};

#endif	// _TEXTURE_H_
