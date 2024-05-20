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
//	�萔�錾
//************************************************************
namespace object
{
	const DWORD FVF_VERTEX_2D		= (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);				// ���_�t�H�[�}�b�g [2D]
	const DWORD FVF_VERTEX_3D		= (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);	// ���_�t�H�[�}�b�g [3D]
	const DWORD FVF_VERTEX_MULTEX3D	= (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2);	// ���_�t�H�[�}�b�g [MULTEX3D]

	const int MAX_PRIO		= 8;	// �D�揇�ʂ̑���
	const int DEFAULT_PRIO	= 3;	// �f�t�H���g�̗D�揇��
}

//************************************************************
//	�\���̒�`
//************************************************************
// ���_��� [2D]
struct VERTEX_2D
{
	D3DXVECTOR3	pos;	// ���_���W
	float		rhw;	// ���W�ϊ��p�W�� (1.0f�ŌŒ�)
	D3DCOLOR	col;	// ���_�J���[
	D3DXVECTOR2	tex;	// �e�N�X�`�����W
};

// ���_��� [3D]
struct VERTEX_3D
{
	D3DXVECTOR3	pos;	// ���_���W
	D3DXVECTOR3	nor;	// �@���x�N�g��
	D3DCOLOR	col;	// ���_�J���[
	D3DXVECTOR2	tex;	// �e�N�X�`�����W
};

// ���_��� [MULTEX3D]
struct VERTEX_MULTEX3D
{
	D3DXVECTOR3	pos;	// ���_���W
	D3DXVECTOR3	nor;	// �@���x�N�g��
	D3DCOLOR	col;	// ���_�J���[
	D3DXVECTOR2	tex0;	// �e�N�X�`�����W_0����
	D3DXVECTOR2	tex1;	// �e�N�X�`�����W_1����
};

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�N���X
class CObject
{
public:
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
		LABEL_TIMER,		// �^�C�}�[
		LABEL_WAVE,			// �g��
		LABEL_FIRE,			// ��
		LABEL_THUNDER,		// ��
		LABEL_BLUR,			// �u���[
		LABEL_EFFECT,		// �G�t�F�N�g
		LABEL_PARTICLE,		// �p�[�e�B�N��
		LABEL_PLAYER,		// �v���C���[
		LABEL_ENEMY,		// �G
		LABEL_MAGIC_CIRCLE,	// ���@�w
		LABEL_MAP,			// �}�b�v
		LABEL_FIELD,		// �n��
		LABEL_WALL,			// ��
		LABEL_SCENERY,		// �i�F
		LABEL_SKY,			// ��
		LABEL_LIQUID,		// �t��
		LABEL_DEBUG,		// �f�o�b�O
		LABEL_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CObject(const ELabel label = LABEL_NONE, const EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	virtual ~CObject();

	// �������z�֐�
	virtual HRESULT Init(void)	= 0;	// ������
	virtual void Uninit(void)	= 0;	// �I��
	virtual void Release(void)	= 0;	// �j��
	virtual void Update(const float fDeltaTime)		= 0;	// �X�V
	virtual void Draw(CShader *pShader = nullptr)	= 0;	// �`��

	// ���z�֐�
	virtual void SetLabel(const ELabel label);				// ���x���ݒ�
	virtual void SetDimension(const EDim dimension);		// �����ݒ�
	virtual void SetPriority(const int nPriority);			// �D�揇�ʐݒ�
	virtual void SetEnableUpdate(const bool bUpdate);		// �X�V�󋵐ݒ�
	virtual void SetEnableDraw(const bool bDraw);			// �`��󋵐ݒ�
	virtual void SetVec2Position(const D3DXVECTOR2& rPos);	// �񎲂̈ʒu�ݒ�
	virtual void SetVec3Position(const D3DXVECTOR3& rPos);	// �O���̈ʒu�ݒ�
	virtual void SetVec3Rotation(const D3DXVECTOR3& rRot);	// �����ݒ�
	virtual void SetVec2Sizing(const D3DXVECTOR2& rSize);	// �񎲂̑傫���ݒ�
	virtual void SetVec3Sizing(const D3DXVECTOR3& rSize);	// �O���̑傫���ݒ�
	virtual void SetVec3Scaling(const D3DXVECTOR3& rSacle);	// �g�嗦�ݒ�
	virtual D3DXVECTOR2 GetVec2Position(void) const;		// �񎲂̈ʒu�擾
	virtual D3DXVECTOR3 GetVec3Position(void) const;		// �O���̈ʒu�擾
	virtual D3DXVECTOR3 GetVec3Rotation(void) const;		// �����擾
	virtual D3DXVECTOR2 GetVec2Sizing(void) const;			// �񎲂̑傫���擾
	virtual D3DXVECTOR3 GetVec3Sizing(void) const;			// �O���̑傫���擾
	virtual D3DXVECTOR3 GetVec3Scaling(void) const;			// �g�嗦�擾
	virtual D3DXMATRIX *GetPtrMtxWorld(void);				// �}�g���b�N�X�|�C���^�擾
	virtual D3DXMATRIX GetMtxWorld(void) const;				// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static void	ReleaseAll(const std::vector<ELabel> label);	// �S�j�� (���x���w��)
	static void	ReleaseAll(void);						// �S�j��
	static void	UpdateAll(const float fDeltaTime);		// �S�X�V
	static void	DrawAll(void);							// �S�`��
	static int	GetNumAll(void) { return m_nNumAll; }	// �����擾
	static CObject *GetTop(const EDim dimension, const int nPriority) { return m_apTop[dimension][nPriority]; }	// �擪�I�u�W�F�N�g�擾
	static CObject *GetCur(const EDim dimension, const int nPriority) { return m_apCur[dimension][nPriority]; }	// �Ō���I�u�W�F�N�g�擾

	// �����o�֐�
	ELabel	GetLabel(void) const		{ return m_label; }		// ���x���擾
	EDim	GetDimension(void) const	{ return m_dimension; }	// �����擾
	int		GetPriority(void) const		{ return m_nPriority; }	// �D�揇�ʎ擾
	DWORD	GetUniqueID(void) const		{ return m_dwID; }		// ���j�[�NID�擾
	bool	IsUpdate(void) const		{ return m_bUpdate; }	// �X�V�󋵎擾
	bool	IsDraw(void) const			{ return m_bDraw; }		// �`��󋵎擾
	bool	IsDeath(void) const			{ return m_bDeath; }	// ���S�t���O�擾
	CObject	*GetObject(void)			{ return this; }		// �I�u�W�F�N�g�擾
	CObject	*GetPrev(void) const		{ return m_pPrev; }		// �O�I�u�W�F�N�g�擾
	CObject	*GetNext(void) const		{ return m_pNext; }		// ���I�u�W�F�N�g�擾

#ifdef _DEBUG

	// �ÓI�����o�֐�
	static void	SetEnableDebugDispAll(const bool bDisp2D, const bool bDisp3D);	// �S�\���󋵐ݒ�

	// �����o�֐�
	void SetEnableDebugDisp(const bool bDisp)	{ m_bDebugDisp = bDisp; }	// �\���󋵐ݒ�
	bool IsDebugDisp(void) const				{ return m_bDebugDisp; }	// �\���󋵎擾

#endif	// _DEBUG

private:
	// �ÓI�����o�֐�
	static void DeathAll(void);	// �S���S

	// �ÓI�����o�ϐ�
	static CObject	*m_apTop[DIM_MAX][object::MAX_PRIO];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject	*m_apCur[DIM_MAX][object::MAX_PRIO];	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	static DWORD	m_dwNextID;	// ���̃��j�[�NID
	static int		m_nNumAll;	// �I�u�W�F�N�g�̑���

	// �����o�ϐ�
	ELabel	m_label;		// ���g�̃I�u�W�F�N�g���x��
	EDim	m_dimension;	// ���g�̎���
	int		m_nPriority;	// ���g�̗D�揇��
	DWORD	m_dwID;			// ���g�̃��j�[�NID
	bool	m_bUpdate;		// ���g�̍X�V��
	bool	m_bDraw;		// ���g�̕`���
	bool	m_bDeath;		// ���g�̎��S�t���O
	CObject	*m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject	*m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^

#ifdef _DEBUG

	bool m_bDebugDisp;	// ���g�̕\����

#endif	// _DEBUG

};

#endif	// _OBJECT_H_
