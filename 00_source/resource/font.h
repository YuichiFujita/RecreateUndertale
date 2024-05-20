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
		// �R���X�g���N�^
		SKey(std::string FontName, bool Italic) :
			sFilePass	(FontName),	// �t�H���g�t�@�C���p�X
			bItalic		(Italic)	// �C�^���b�N
		{}

		// ��r���Z�q�I�[�o�[���[�h
		bool operator<(const SKey& rKey) const
		{
			// �����܂Ƃ߂Ĕ�r
			return std::tie(sFilePass, bItalic) < std::tie(rKey.sFilePass, rKey.bItalic);
		}

		// �����o�ϐ�
		std::string sFilePass;	// �t�H���g�t�@�C���p�X
		bool bItalic;			// �C�^���b�N
	};

	// �t�H���g�\����
	struct SFont
	{
		// �R���X�g���N�^
		SFont() :
			pFontChar	(nullptr),	// �t�H���g�����C���X�^���X
			pFont		(nullptr)	// �t�H���g�ւ̃|�C���^
		{
			sFontName.clear();	// �t�H���g�����N���A
		}

		// �����o�ϐ�
		std::string sFontName;	// �t�H���g��
		CFontChar *pFontChar;	// �t�H���g�����C���X�^���X
		HFONT pFont;			// �t�H���g�ւ̃|�C���^
	};

	// �����o�֐�
	HRESULT Init(void);		// �t�H���g������
	void Uninit(void);		// �t�H���g�I��
	HRESULT LoadAll(void);	// �t�H���g�S�Ǎ�
	HRESULT Load(const std::string &rFilePass);	// �t�H���g�Ǎ�
	SFont Regist(const std::string &rFilePass, const bool bItalic = false);	// �t�H���g�o�^
	CFontChar::SChar RegistChar	// �t�H���g�����o�^
	( // ����
		const wchar_t wcChar,			// �w�蕶��
		const std::string &rFilePass,	// �t�@�C���p�X
		const bool bItalic = false		// �C�^���b�N
	);

	// �ÓI�����o�֐�
	static CFont *Create(void);				// ����
	static void Release(CFont *&prFont);	// �j��

private:
	// �����o�֐�
	void RegistPrepare(const std::string &rFilePass);			// �t�H���g�E�t�H���g�����̎��O�o�^
	HRESULT SearchFolderAll(const std::string &rFolderPath);	// �t�H���_�S����

	// �����o�ϐ�
	std::map<SKey, SFont> m_mapFont;		// �t�H���g�A�z�z��
	std::vector<std::string> m_vecFilePass;	// �Ǎ��ς݃t�@�C���p�X
};

#endif	// _FONT_H_
