//============================================================
//
//	�����_�[�X�e�[�g�w�b�_�[ [renderState.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RENDER_STATE_H_
#define _RENDER_STATE_H_

//************************************************************
//	�N���X��`
//************************************************************
// �����_�[�X�e�[�g�N���X
class CRenderState
{
public:
	// ���u�����h��
	enum EBlend
	{
		BLEND_NORMAL = 0,	// �ʏ퍇��
		BLEND_ADD,			// ���Z����
		BLEND_SUB,			// ���Z����
		BLEND_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CRenderState();

	// �f�X�g���N�^
	~CRenderState();

	// ���u�����h���
	struct SBlendAlpha
	{
	public:
		// �f�t�H���g�R���X�g���N�^
		SBlendAlpha() :
			op		(D3DBLENDOP_ADD),	// ���u�����h���
			scr		(D3DBLEND_ZERO),	// SCR�u�����h
			dest	(D3DBLEND_ZERO),	// DEST�u�����h
			bBlend	(false)				// ���u�����h��
		{}

		// �����t���R���X�g���N�^
		SBlendAlpha(const D3DBLENDOP in_op, const D3DBLEND in_scr, const D3DBLEND in_dest) :
			op		(in_op),	// ���u�����h���
			scr		(in_scr),	// SCR�u�����h
			dest	(in_dest),	// DEST�u�����h
			bBlend	(true)		// ���u�����h��
		{}

		// �f�X�g���N�^
		~SBlendAlpha() {}

		// �����o�ϐ�
		D3DBLENDOP	op;		// ���u�����h���
		D3DBLEND	scr;	// SCR�u�����h
		D3DBLEND	dest;	// DEST�u�����h
		bool		bBlend;	// ���u�����h��
	};

	// ���e�X�g���
	struct STestAlpha
	{
		// �f�t�H���g�R���X�g���N�^
		STestAlpha() :
			func	(D3DCMP_NEVER),	// ���e�X�g���
			nRef	(0),			// ���e�X�g�Q�ƒl
			bTest	(false)			// ���e�X�g��
		{}

		// �f�X�g���N�^
		~STestAlpha() {}

		// �����o�ϐ�
		D3DCMPFUNC	func;	// ���e�X�g���
		int			nRef;	// ���e�X�g�Q�ƒl
		bool		bTest;	// ���e�X�g��
	};

	// Z�e�X�g���
	struct STestZ
	{
		// �f�t�H���g�R���X�g���N�^
		STestZ() :
			func	(D3DCMP_NEVER),	// Z�e�X�g���
			bUpdate	(false)			// Z�o�b�t�@�X�V��
		{}

		// �f�X�g���N�^
		~STestZ() {}

		// �����o�ϐ�
		D3DCMPFUNC	func;		// Z�e�X�g���
		bool		bUpdate;	// Z�o�b�t�@�X�V��
	};

	// �����_�[�X�e�[�g���
	struct SInfo
	{
		// �f�t�H���g�R���X�g���N�^
		SInfo() :
			blendAlpha	({}),			// ���u�����h���
			testAlpha	({}),			// ���e�X�g���
			testZ		({}),			// Z�e�X�g���
			cull		(D3DCULL_NONE),	// �J�����O���
			bLight		(false)			// ���C�e�B���O��
		{}

		// �f�X�g���N�^
		~SInfo() {}

		// �����o�ϐ�
		SBlendAlpha	blendAlpha;	// ���u�����h���
		STestAlpha	testAlpha;	// ���e�X�g���
		STestZ		testZ;		// Z�e�X�g���
		D3DCULL		cull;		// �J�����O���
		bool		bLight;		// ���C�e�B���O��
	};

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Set();		// �ݒ�
	void Reset();	// �Đݒ�
	void SetInfoRenderState(const SInfo& rInfo);	// �����_�[�X�e�[�g���ݒ�
	SInfo GetInfoRenderState();						// �����_�[�X�e�[�g���擾
	void SetAlphaBlend(const EBlend blend);			// ���u�����h���ݒ�

	inline void SetAlphaFunc(const D3DCMPFUNC func)	{ m_info.testAlpha.func	 = func; }		// ���e�X�g�̏��ݒ�
	inline void SetAlphaNumRef(const int nRef)		{ m_info.testAlpha.nRef	 = nRef; }		// ���e�X�g�̎Q�ƒl�ݒ�
	inline void SetAlphaTest(const bool bTest)		{ m_info.testAlpha.bTest = bTest; }		// ���e�X�g�̏󋵐ݒ�
	inline void SetZFunc(const D3DCMPFUNC func)		{ m_info.testZ.func		 = func; }		// Z�e�X�g�̏��ݒ�
	inline void SetZUpdate(const bool bUpdate)		{ m_info.testZ.bUpdate	 = bUpdate; }	// Z�e�X�g�̃o�b�t�@�X�V�ݒ�
	inline void SetCulling(const D3DCULL cull)		{ m_info.cull	= cull; }	// �J�����O�ݒ�
	inline void SetLighting(const bool bLight)		{ m_info.bLight	= bLight; }	// ���C�e�B���O�ݒ�

	// �ÓI�����o�֐�
	static CRenderState* Create();	// ����
	static void Release(CRenderState*& prRenderState);		// �j��
	static void BindDevice(LPDIRECT3DDEVICE9* ppDevice);	// �f�o�C�X����
	static void InitRenderState();		// �����_�[�X�e�[�g��񏉊���
	static SInfo GetSaveRenderState();	// �ۑ������_�[�X�e�[�g���擾

private:
	// �ÓI�����o�֐�
	static void SetRenderState(const SInfo& rInfo);	// �����_�[�X�e�[�g���f

	// �ÓI�����o�ϐ�
	static LPDIRECT3DDEVICE9* m_ppDevice;	// Direct3D�f�o�C�X�ւ̃|�C���^
	static SInfo m_save;	// �ۑ������_�[�X�e�[�g���

	// �����o�ϐ�
	SInfo m_info;	// �����_�[�X�e�[�g���
};

#endif	// _RENDER_STATE_H_
