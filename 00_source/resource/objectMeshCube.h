//============================================================
//
//	�I�u�W�F�N�g���b�V���L���[�u�w�b�_�[ [objectMeshCube.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_MESHCUBE_H_
#define _OBJECT_MESHCUBE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g���b�V���L���[�u�N���X
class CObjectMeshCube : public CObject
{
public:
	// �R���X�g���N�^
	explicit CObjectMeshCube(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshCube() override;

	// ���_��
	enum EOrigin
	{
		ORIGIN_CENTER = 0,	// ���S���_
		ORIGIN_DOWN,		// �����_
		ORIGIN_UP,			// �㌴�_
		ORIGIN_MAX,			// ���̗񋓌^�̑���
	};

	// ������
	enum EBorder
	{
		BORDER_OFF = 0,		// �����Ȃ�
		BORDER_ON,			// ����肠��
		BORDER_MAX,			// ���̗񋓌^�̑���
	};

	// �e�N�X�`���g�p��
	enum ETexState
	{
		TEXSTATE_ONE = 0,	// ����e�N�X�`��
		TEXSTATE_SELECT,	// �S�I���e�N�X�`��
		TEXSTATE_MAX,		// ���̗񋓌^�̑���
	};

	// �L���[�u�F��
	enum ECubeCol
	{
		CUBECOL_CUBE = 0,	// �L���[�u�F
		CUBECOL_BORDER,		// �����F
		CUBECOL_MAX			// ���̗񋓌^�̑���
	};

	// �L���[�u��������
	enum ECubePart
	{
		CUBEPART_X = 0,		// �e�N�X�`��������X
		CUBEPART_Y,			// �e�N�X�`��������Y
		CUBEPART_Z,			// �e�N�X�`��������Z
		CUBEPART_MAX		// ���̗񋓌^�̑���
	};

	// �e�N�X�`���\����
	struct SFaceTex
	{
	public:
		// �R���X�g���N�^
		SFaceTex() {}

		SFaceTex(const int nAll)
		{ All = nAll; Left = 0; Right = 0; Bottom = 0; Top = 0; Near = 0; Far = 0; }

		SFaceTex(const int nLeft, const int nRight, const int nBottom, const int nTop, const int nNear, const int nFar)
		{ All = 0; Left = nLeft; Right = nRight; Bottom = nBottom; Top = nTop; Near = nNear; Far = nFar; }

		SFaceTex(const int nAll, const int nLeft, const int nRight, const int nBottom, const int nTop, const int nNear, const int nFar)
		{ All = nAll; Left = nLeft; Right = nRight; Bottom = nBottom; Top = nTop; Near = nNear; Far = nFar; }

		// �f�X�g���N�^
		~SFaceTex() {}

		// �����o�ϐ�
		int All;	// �S�ʂ̃e�N�X�`���C���f�b�N�X
		int Left;	// ���̃e�N�X�`���C���f�b�N�X
		int Right;	// �E�̃e�N�X�`���C���f�b�N�X
		int Bottom;	// ���̃e�N�X�`���C���f�b�N�X
		int Top;	// ��̃e�N�X�`���C���f�b�N�X
		int Near;	// �O�̃e�N�X�`���C���f�b�N�X
		int Far;	// ��̃e�N�X�`���C���f�b�N�X
	};

	// ���b�V���L���[�u�\����
	struct SMeshCube
	{
		VECTOR3		pos;					// �ʒu
		VECTOR3		rot;					// ����
		VECTOR3		size;					// �傫��
		COLOR		aCol[CUBECOL_MAX];		// �F
		MATRIX		mtxWorld;				// ���[���h�}�g���b�N�X
		EBorder		bordState;				// �����g�p���
		float		fBordThick;				// ����葾��
		ETexState	texState;				// �e�N�X�`���g�p���
		SFaceTex	texID;					// �e�N�X�`�����
		VECTOR2		aTexPart[CUBEPART_MAX];	// �e�N�X�`��������
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader *pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Size(const VECTOR3& rSize) override;	// �傫���ݒ�
	VECTOR3 GetVec3Position(void) const override	{ return m_meshCube.pos; }			// �ʒu�擾
	VECTOR3 GetVec3Rotation(void) const override	{ return m_meshCube.rot; }			// �����擾
	VECTOR3 GetVec3Size(void) const override		{ return m_meshCube.size; }			// �傫���擾
	MATRIX *GetPtrMtxWorld(void) override			{ return &m_meshCube.mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	MATRIX GetMtxWorld(void) const override			{ return m_meshCube.mtxWorld; }		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshCube *Create	// ����
	( // ����
		const VECTOR3&	rPos,		// �ʒu
		const VECTOR3&	rRot,		// ����
		const VECTOR3&	rSize,		// �傫��
		const COLOR&	rCubeCol,	// �L���[�u�F
		const COLOR&	rBorderCol	= color::Black(),		// �����F
		const EBorder	bordState	= BORDER_OFF,			// �������
		const float		fBordThick	= 0.0f,					// ����葾��
		const ETexState	texState	= TEXSTATE_ONE,			// �e�N�X�`�����
		const SFaceTex&	rTexID		= SFaceTex(NONE_IDX),	// �e�N�X�`�����
		const EOrigin	origin		= ORIGIN_CENTER,		// ���_
		const VECTOR2&	rTexPartX	= VEC2_ONE,				// �e�N�X�`��������X
		const VECTOR2&	rTexPartY	= VEC2_ONE,				// �e�N�X�`��������Y
		const VECTOR2&	rTexPartZ	= VEC2_ONE				// �e�N�X�`��������Z
	);

	// �����o�֐�
	CRenderState *GetRenderState(void);					// �����_�[�X�e�[�g���擾
	void BindTexture(const SFaceTex textureID);			// �e�N�X�`������
	void SetCubeAlpha(const float fAlpha);				// �L���[�u�����x�ݒ�
	void SetCubeColor(const COLOR& rCol);				// �L���[�u�F�ݒ�
	void SetBorderAlpha(const float fAlpha);			// ����蓧���x�ݒ�
	void SetBorderColor(const COLOR& rCol);				// �����F�ݒ�
	HRESULT SetBorderState(const EBorder bordState);	// ������Ԑݒ�
	void SetBorderThick(const float fBordThick);		// ����葾���ݒ�
	void SetTextureState(const ETexState texState);		// �e�N�X�`����Ԑݒ�
	void SetTexturePatternX(const VECTOR2& rTexPart);	// �e�N�X�`��������X�ݒ�
	void SetTexturePatternY(const VECTOR2& rTexPart);	// �e�N�X�`��������Y�ݒ�
	void SetTexturePatternZ(const VECTOR2& rTexPart);	// �e�N�X�`��������Z�ݒ�
	void SetOrigin(const EOrigin origin);				// ���_�ݒ�
	SFaceTex GetTextureIndex(void) const	{ return m_meshCube.texID; }					// �e�N�X�`���C���f�b�N�X�擾
	float GetCubeAlpha(void) const			{ return m_meshCube.aCol[CUBECOL_CUBE].a; }		// �����x�擾
	COLOR GetCubeColor(void) const			{ return m_meshCube.aCol[CUBECOL_CUBE]; }		// �L���[�u�F�擾
	float GetBorderAlpha(void) const		{ return m_meshCube.aCol[CUBECOL_BORDER].a; }	// �����x�擾
	COLOR GetBorderColor(void) const		{ return m_meshCube.aCol[CUBECOL_BORDER]; }		// �����F�擾
	EBorder GetBorderState(void) const		{ return m_meshCube.bordState; }				// ������Ԏ擾
	float GetBorderThick(void) const		{ return m_meshCube.fBordThick; }				// ����葾���擾
	ETexState GetTextureState(void) const	{ return m_meshCube.texState; }					// �e�N�X�`����Ԏ擾
	VECTOR2 GetTexturePatternX(void) const	{ return m_meshCube.aTexPart[CUBEPART_X]; }		// �e�N�X�`��������X�擾
	VECTOR2 GetTexturePatternY(void) const	{ return m_meshCube.aTexPart[CUBEPART_Y]; }		// �e�N�X�`��������Y�擾
	VECTOR2 GetTexturePatternZ(void) const	{ return m_meshCube.aTexPart[CUBEPART_Z]; }		// �e�N�X�`��������Z�擾
	EOrigin GetOrigin(void) const			{ return m_origin; }							// ���_�擾

protected:
	// �����o�֐�
	void SetVtx(void);	// ���_���̐ݒ�
	void SetIdx(void);	// �C���f�b�N�X���̐ݒ�

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void DrawNormal(void);	// �ʏ�`��
	void DrawShader(CShader *pShader);	// �V�F�[�_�[�`��

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	CRenderState *m_pRenderState;		// �����_�[�X�e�[�g�̏��
	SMeshCube m_meshCube;	// ���b�V���L���[�u�̏��
	EOrigin m_origin;		// ���_
	int m_nNumVtx;			// �K�v���_��
	int m_nNumIdx;			// �K�v�C���f�b�N�X��
};

#endif	// _OBJECT_MESHCUBE_H_
