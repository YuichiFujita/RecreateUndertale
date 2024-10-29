//==========================================================
//
//�f�o�b�O�\������ [debugproc.h]
//Author Ibuki Okusada
//
//==========================================================
#ifndef _DEBUGPROC_H_		//���̃}�N������`����Ă��Ȃ��ꍇ
#define _DEBUGPROC_H_

//**********************************************************
//�N���X�̒�`
//**********************************************************
class CDebugProc
{
public:
	// �萔
	static constexpr int MAX_STR = 2048;	// �f�o�b�O�\���̍ő啶����

	// �f�o�b�O�ʒu��
	enum EPoint
	{
		POINT_CENTER = 0,	// ����
		POINT_LEFT,			// ��
		POINT_RIGHT,		// �E
		POINT_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CDebugProc();

	// �f�X�g���N�^
	~CDebugProc();

	// �����o�֐�
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void Print(const EPoint point, const char* fmt, ...);
	
	inline void SetDisp(const bool bDisp)	{ m_bDisp = bDisp; }	// �\���ݒ�
	inline bool IsDisp() const				{ return m_bDisp; }		// �\���擾

	// �ÓI�����o�֐�
	static CDebugProc* Create();					// ����
	static void Release(CDebugProc*& prDebugProc);	// �j��

private:
	static LPD3DXFONT m_pFont;	// �t�H���g�ւ̃|�C���^
	bool m_bDisp;				// �f�o�b�O�\����ON/OFF
	char m_aStr[POINT_MAX][MAX_STR];	// �f�o�b�O�\���p�̕�����
};

#endif	// _DEBUGPROC_H_
