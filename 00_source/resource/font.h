//============================================================
//
//	�t�H���g�w�b�_�[ [font.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FONT_H_
#define _FONT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "fontChar.h"
#include "extension.h"

//************************************************************
//	�N���X��`
//************************************************************
// �t�H���g�N���X
class CFont
{
public:
	// �R���X�g���N�^
	CFont();

	// �f�X�g���N�^
	~CFont();

	// �L�[�\����
	struct SKey
	{
		// �f�t�H���g�R���X�g���N�^
		SKey() :
			sFilePath	(""),	// �t�H���g�t�@�C���p�X
			bItalic		(false)	// �C�^���b�N
		{}

		// �����t���R���X�g���N�^
		SKey(std::string in_sFontName, bool in_bItalic) :
			sFilePath	(in_sFontName),	// �t�H���g�t�@�C���p�X
			bItalic		(in_bItalic)	// �C�^���b�N
		{}

		// ��r���Z�q�I�[�o�[���[�h
		inline bool operator<(const SKey& rKey) const
		{
			// �����܂Ƃ߂Ĕ�r
			return std::tie(sFilePath, bItalic) < std::tie(rKey.sFilePath, rKey.bItalic);
		}

		// �����o�ϐ�
		std::string sFilePath;	// �t�H���g�t�@�C���p�X
		bool bItalic;			// �C�^���b�N
	};

	// �t�H���g�\����
	struct SFont
	{
		// �f�t�H���g�R���X�g���N�^
		SFont() :
			sFontName	(""),		// �t�H���g�����N���A
			pFontChar	(nullptr),	// �t�H���g�����C���X�^���X
			pFont		(nullptr)	// �t�H���g�ւ̃|�C���^
		{}

		// �����o�ϐ�
		std::string sFontName;	// �t�H���g��
		CFontChar* pFontChar;	// �t�H���g�����C���X�^���X
		HFONT pFont;			// �t�H���g�ւ̃|�C���^
	};

	// �����o�֐�
	HRESULT Init();		// �t�H���g������
	void Uninit();		// �t�H���g�I��
	HRESULT LoadAll();	// �t�H���g�S�Ǎ�
	HRESULT Load(const std::string& rFilePath);	// �t�H���g�Ǎ�
	SFont Regist(const std::string& rFilePath, const bool bItalic = false);	// �t�H���g�o�^
	CFontChar::SChar RegistChar	// �t�H���g�����o�^
	( // ����
		const wchar_t wcChar,			// �w�蕶��
		const std::string& rFilePath,	// �t�@�C���p�X
		const bool bItalic = false		// �C�^���b�N
	);

	// �ÓI�����o�֐�
	static CFont* Create();					// ����
	static void Release(CFont*& prFont);	// �j��

private:
	// �����o�֐�
	void RegistPrepare(const std::string& rFilePath);			// �t�H���g�E�t�H���g�����̎��O�o�^
	HRESULT SearchFolderAll(const std::string& rFolderPath);	// �t�H���_�S����

	// �����o�ϐ�
	std::map<SKey, SFont> m_mapFont;		// �t�H���g�A�z�z��
	std::vector<std::string> m_vecFilePath;	// �Ǎ��ς݃t�@�C���p�X
	extension::ALoad m_load;				// �ǂݍ��݉\�g���q
};

#endif	// _FONT_H_
