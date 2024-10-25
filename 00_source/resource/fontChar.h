//============================================================
//
//	�t�H���g�����w�b�_�[ [fontChar.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FONT_CHAR_H_
#define _FONT_CHAR_H_

//************************************************************
//	�N���X��`
//************************************************************
// �t�H���g�����N���X
class CFontChar
{
public:
	// �R���X�g���N�^
	CFontChar(const HFONT hFont, const std::string& rFilePath, const bool bItalic);

	// �f�X�g���N�^
	~CFontChar();

	// ��`�̍��W���
	struct SRectangle
	{
		POSGRID2 lu;	// ������W
		POSGRID2 rd;	// �E�����W
	};

	// �t�H���g�����\����
	struct SChar
	{
		// �R���X�g���N�^
		SChar() { memset(this, 0, sizeof(*this)); }

		// �����o�ϐ�
		GLYPHMETRICS glyph;			// �t�H���g�O���t�̏��
		OUTLINETEXTMETRIC outline;	// �t�H���g�A�E�g���C���̏��
		TEXTMETRIC text;			// �t�H���g�e�L�X�g�̏��
		SRectangle offsetBlackBox;	// �u���b�N�{�b�N�X�̒��S����̃I�t�Z�b�g
		int nTexIdx;				// �e�N�X�`���C���f�b�N�X
		bool bEmpty;				// �e�N�X�`�������t���O
	};

	// �����o�֐�
	HRESULT Init();	// �t�H���g����������
	void Uninit();	// �t�H���g�����I��
	SChar Regist(const wchar_t wcChar);		// �t�H���g�����o�^
	inline const HFONT GetFont()			{ return m_hFont; }		// �t�H���g�ւ̃|�C���^
	inline const std::string GetFilePath()	{ return m_sFilePath; }	// �t�H���g�p�X
	inline const bool GetItalic()			{ return m_bItalic; }	// �C�^���b�N

	// �ÓI�����o�֐�
	static CFontChar* Create(const HFONT hFont, const std::string& rFilePath, const bool bItalic);	// ����
	static void Release(CFontChar*& prFontChar);	// �j��

private:
	// �����o�֐�
	BYTE* CreateBitMap(SChar* pChar, HDC hDC, const wchar_t wcChar);	// �r�b�g�}�b�v�����E�������ۑ�
	HRESULT CreateTexture(SChar* pChar, BYTE* pBitMap);					// �e�N�X�`�������E�쐬

	// �����o�ϐ�
	std::map<wchar_t, SChar> m_mapChar;	// �t�H���g�����A�z�z��
	const HFONT m_hFont;				// �t�H���g�ւ̃|�C���^
	const std::string m_sFilePath;		// �t�H���g�p�X
	const bool m_bItalic;				// �C�^���b�N
};

#endif	// _FONT_CHAR_H_
