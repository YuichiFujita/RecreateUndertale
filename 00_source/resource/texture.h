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
		// �R���X�g���N�^
		SInfo() {}
		SInfo(const UINT nWidth, const UINT nHeight, const UINT nMip, const DWORD dwUsage, const D3DFORMAT format, const D3DPOOL pool)
			: Width(nWidth), Height(nHeight), MipLevels(nMip), Usage(dwUsage), Format(format), Pool(pool) {}

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
		LPDIRECT3DTEXTURE9 pTexture;	// �e�N�X�`���ւ̃|�C���^
		D3DXIMAGE_INFO status;			// �e�N�X�`���X�e�[�^�X�ւ̃|�C���^
		D3DXVECTOR2 aspect;				// �A�X�y�N�g��
	};

	// �}�b�v���\����
	struct SMapInfo
	{
		STexture textureData;		// �e�N�X�`�����
		std::string sFilePassName;	// �t�@�C���p�X��
	};

	// �����o�֐�
	HRESULT Init(void);		// �e�N�X�`��������
	void Uninit(void);		// �e�N�X�`���I��
	HRESULT LoadAll(void);	// �e�N�X�`���S�Ǎ�
	int Regist(const SInfo info);				// �e�N�X�`���o�^ (����)
	int Regist(std::string sFilePass);			// �e�N�X�`���o�^ (�p�X)
	STexture GetInfo(const int nID);			// �e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 GetPtr(const int nID);	// �e�N�X�`���|�C���^�擾

	// �ÓI�����o�֐�
	static CTexture *Create(void);				// ����
	static void Release(CTexture *&pTexture);	// �j��

private:
	// �����o�֐�
	HRESULT SearchFolderAll(std::string sFolderPath);	// �t�H���_�S����

	// �����o�ϐ�
	std::map<int, SMapInfo> m_mapTexture;	// �e�N�X�`���A�z�z��

	// �ÓI�����o�ϐ�
	static int m_nNumAll;	// �e�N�X�`���̑���
};

#endif	// _TEXTURE_H_
