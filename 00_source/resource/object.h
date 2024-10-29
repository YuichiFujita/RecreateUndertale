//============================================================
//
//	�I�u�W�F�N�g�w�b�_�[ [object.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_H_
#define _OBJECT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "shader.h"
#include "shaderToon.h"
#include "shaderMono.h"

//************************************************************
//	�\���̒�`
//************************************************************
// ���_��� [2D]
struct VERTEX_2D
{
	VECTOR3	 pos;	// ���_���W
	float	 rhw;	// ���W�ϊ��p�W�� (1.0f�ŌŒ�)
	D3DCOLOR col;	// ���_�J���[
	VECTOR2	 tex;	// �e�N�X�`�����W
};

// ���_��� [3D]
struct VERTEX_3D
{
	VECTOR3	 pos;	// ���_���W
	VECTOR3	 nor;	// �@���x�N�g��
	D3DCOLOR col;	// ���_�J���[
	VECTOR2	 tex;	// �e�N�X�`�����W
};

// ���_��� [MULTEX3D]
struct VERTEX_MULTEX3D
{
	VECTOR3	 pos;	// ���_���W
	VECTOR3	 nor;	// �@���x�N�g��
	D3DCOLOR col;	// ���_�J���[
	VECTOR2	 tex0;	// �e�N�X�`�����W_0����
	VECTOR2	 tex1;	// �e�N�X�`�����W_1����
};

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�N���X
class CObject
{
public:
	// �萔
	static constexpr DWORD FVF_VERTEX_2D		= (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);				// ���_�t�H�[�}�b�g [2D]
	static constexpr DWORD FVF_VERTEX_3D		= (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);	// ���_�t�H�[�}�b�g [3D]
	static constexpr DWORD FVF_VERTEX_MULTEX3D	= (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2);	// ���_�t�H�[�}�b�g [MULTEX3D]

	static constexpr int MAX_PRIO		= 8;	// �D�揇�ʂ̑���
	static constexpr int DEFAULT_PRIO	= 3;	// �f�t�H���g�̗D�揇��

	// ������
	enum EDim
	{
		DIM_3D = 0,	// 3D�`��
		DIM_2D,		// 2D�`��
		DIM_MAX		// ���̗񋓌^�̑���
	};

	// ���x����
	enum ELabel
	{
		LABEL_NONE = 0,		// �Ȃ�
		LABEL_UI,			// UI
		LABEL_LIGHT,		// ���C�g
		LABEL_TIMER,		// �^�C�}�[
		LABEL_EFFECT,		// �G�t�F�N�g
		LABEL_PARTICLE,		// �p�[�e�B�N��
		LABEL_PLAYER,		// �v���C���[
		LABEL_TILE,			// �^�C��
#ifdef _DEBUG
		LABEL_DEBUG,		// �f�o�b�O
#endif // _DEBUG
		LABEL_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CObject(const ELabel label = LABEL_NONE, const EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	virtual ~CObject();

	// �������z�֐�
	virtual HRESULT Init()	= 0;	// ������
	virtual void Uninit()	= 0;	// �I��
	virtual void Release()	= 0;	// �j��
	virtual void Update(const float fDeltaTime)		= 0;	// �X�V
	virtual void Draw(CShader* pShader = nullptr)	= 0;	// �`��

	// ���z�֐�
	virtual void SetLabel(const ELabel label);				// ���x���ݒ�
	virtual void SetDimension(const EDim dimension);		// �����ݒ�
	virtual void SetPriority(const int nPriority);			// �D�揇�ʐݒ�
	virtual inline void SetEnableUpdate(const bool bUpdate)	{ m_bUpdate = bUpdate; }	// �X�V�󋵐ݒ�
	virtual inline void SetEnableDraw(const bool bDraw)		{ m_bDraw = bDraw; }		// �`��󋵐ݒ�
	virtual inline void SetVec2Position(const VECTOR2&)		{ assert(false); }			// �񎲂̈ʒu�ݒ�
	virtual inline void SetVec3Position(const VECTOR3&)		{ assert(false); }			// �O���̈ʒu�ݒ�
	virtual inline void SetVec3Rotation(const VECTOR3&)		{ assert(false); }			// �����ݒ�
	virtual inline void SetVec2Size(const VECTOR2&)			{ assert(false); }			// �񎲂̑傫���ݒ�
	virtual inline void SetVec3Size(const VECTOR3&)			{ assert(false); }			// �O���̑傫���ݒ�
	virtual inline void SetVec3Scale(const VECTOR3&)		{ assert(false); }			// �g�嗦�ݒ�
	virtual inline VECTOR2 GetVec2Position() const			{ assert(false); return VEC2_ZERO; }	// �񎲂̈ʒu�擾
	virtual inline VECTOR3 GetVec3Position() const			{ assert(false); return VEC3_ZERO; }	// �O���̈ʒu�擾
	virtual inline VECTOR3 GetVec3Rotation() const			{ assert(false); return VEC3_ZERO; }	// �����擾
	virtual inline VECTOR2 GetVec2Size() const				{ assert(false); return VEC2_ZERO; }	// �񎲂̑傫���擾
	virtual inline VECTOR3 GetVec3Size() const				{ assert(false); return VEC3_ZERO; }	// �O���̑傫���擾
	virtual inline VECTOR3 GetVec3Scale() const				{ assert(false); return VEC3_ZERO; }	// �g�嗦�擾
	virtual inline MATRIX* GetPtrMtxWorld()					{ assert(false); return nullptr; }		// �}�g���b�N�X�|�C���^�擾
	virtual inline MATRIX GetMtxWorld() const				{ assert(false); return {}; }			// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static void	ReleaseAll(const std::vector<ELabel> label);	// �S�j�� (�������x���w��)
	static void	ReleaseAll(const ELabel label);		// �S�j�� (���x���w��)
	static void	ReleaseAll();						// �S�j��
	static void	UpdateAll(const float fDeltaTime);	// �S�X�V
	static void	DrawAll();							// �S�`��
	static int	GetNumAll() { return m_nNumAll; }	// �����擾
	static inline CObject* GetTop(const EDim dimension, const int nPriority) { return m_apTop[dimension][nPriority]; }	// �擪�I�u�W�F�N�g�擾
	static inline CObject* GetCur(const EDim dimension, const int nPriority) { return m_apCur[dimension][nPriority]; }	// �Ō���I�u�W�F�N�g�擾

	// �����o�֐�
	inline ELabel	GetLabel() const		{ return m_label; }		// ���x���擾
	inline EDim		GetDimension() const	{ return m_dimension; }	// �����擾
	inline int		GetPriority() const		{ return m_nPriority; }	// �D�揇�ʎ擾
	inline DWORD	GetUniqueIdx() const	{ return m_dwIdx; }		// ���j�[�N�C���f�b�N�X�擾
	inline bool		IsUpdate() const		{ return m_bUpdate; }	// �X�V�󋵎擾
	inline bool		IsDraw() const			{ return m_bDraw; }		// �`��󋵎擾
	inline bool		IsDeath() const			{ return m_bDeath; }	// ���S�t���O�擾
	inline CObject*	GetObject()				{ return this; }		// �I�u�W�F�N�g�擾
	inline CObject*	GetPrev() const			{ return m_pPrev; }		// �O�I�u�W�F�N�g�擾
	inline CObject*	GetNext() const			{ return m_pNext; }		// ���I�u�W�F�N�g�擾

private:
	// �ÓI�����o�֐�
	static void DeathAll();	// �S���S

	// �ÓI�����o�ϐ�
	static CObject*	m_apTop[DIM_MAX][MAX_PRIO];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject*	m_apCur[DIM_MAX][MAX_PRIO];	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	static DWORD	m_dwNextIdx;	// ���̃��j�[�N�C���f�b�N�X
	static int		m_nNumAll;		// �I�u�W�F�N�g�̑���

	// �����o�ϐ�
	ELabel	 m_label;		// ���g�̃I�u�W�F�N�g���x��
	EDim	 m_dimension;	// ���g�̎���
	int		 m_nPriority;	// ���g�̗D�揇��
	DWORD	 m_dwIdx;		// ���g�̃��j�[�N�C���f�b�N�X
	bool	 m_bUpdate;		// ���g�̍X�V��
	bool	 m_bDraw;		// ���g�̕`���
	bool	 m_bDeath;		// ���g�̎��S�t���O
	CObject* m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^

#ifdef _DEBUG
public:
	// �ÓI�����o�֐�
	static void	SetEnableDebugDispAll(const bool bDisp2D, const bool bDisp3D);	// �S�\���󋵐ݒ�

	// �����o�֐�
	inline void SetEnableDebugDisp(const bool bDisp) { m_bDebugDisp = bDisp; }	// �\���󋵐ݒ�
	inline bool IsDebugDisp() const { return m_bDebugDisp; }	// �\���󋵎擾

private:
	// �����o�ϐ�
	bool m_bDebugDisp;	// ���g�̕\����
#endif	// _DEBUG
};

#endif	// _OBJECT_H_
