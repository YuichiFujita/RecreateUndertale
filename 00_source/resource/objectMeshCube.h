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
	explicit CObjectMeshCube(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

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
		// �f�t�H���g�R���X�g���N�^
		SFaceTex() :
			All		(0),	// �S�ʂ̃e�N�X�`���C���f�b�N�X
			Left	(0),	// ���̃e�N�X�`���C���f�b�N�X
			Right	(0),	// �E�̃e�N�X�`���C���f�b�N�X
			Bottom	(0),	// ���̃e�N�X�`���C���f�b�N�X
			Top		(0),	// ��̃e�N�X�`���C���f�b�N�X
			Near	(0),	// �O�̃e�N�X�`���C���f�b�N�X
			Far		(0)		// ��̃e�N�X�`���C���f�b�N�X
		{}

		// �����t���R���X�g���N�^
		SFaceTex(const int in_nAll) :
			All		(in_nAll),		// �S�ʂ̃e�N�X�`���C���f�b�N�X
			Left	(0),			// ���̃e�N�X�`���C���f�b�N�X
			Right	(0),			// �E�̃e�N�X�`���C���f�b�N�X
			Bottom	(0),			// ���̃e�N�X�`���C���f�b�N�X
			Top		(0),			// ��̃e�N�X�`���C���f�b�N�X
			Near	(0),			// �O�̃e�N�X�`���C���f�b�N�X
			Far		(0)				// ��̃e�N�X�`���C���f�b�N�X
		{}
		SFaceTex(const int in_nLeft, const int in_nRight, const int in_nBottom, const int in_nTop, const int in_nNear, const int in_nFar) :
			All		(0),			// �S�ʂ̃e�N�X�`���C���f�b�N�X
			Left	(in_nLeft),		// ���̃e�N�X�`���C���f�b�N�X
			Right	(in_nRight),	// �E�̃e�N�X�`���C���f�b�N�X
			Bottom	(in_nBottom),	// ���̃e�N�X�`���C���f�b�N�X
			Top		(in_nTop),		// ��̃e�N�X�`���C���f�b�N�X
			Near	(in_nNear),		// �O�̃e�N�X�`���C���f�b�N�X
			Far		(in_nFar)		// ��̃e�N�X�`���C���f�b�N�X
		{}
		SFaceTex(const int in_nAll, const int in_nLeft, const int in_nRight, const int in_nBottom, const int in_nTop, const int in_nNear, const int in_nFar) :
			All		(in_nAll),		// �S�ʂ̃e�N�X�`���C���f�b�N�X
			Left	(in_nLeft),		// ���̃e�N�X�`���C���f�b�N�X
			Right	(in_nRight),	// �E�̃e�N�X�`���C���f�b�N�X
			Bottom	(in_nBottom),	// ���̃e�N�X�`���C���f�b�N�X
			Top		(in_nTop),		// ��̃e�N�X�`���C���f�b�N�X
			Near	(in_nNear),		// �O�̃e�N�X�`���C���f�b�N�X
			Far		(in_nFar)		// ��̃e�N�X�`���C���f�b�N�X
		{}

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

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Size(const VECTOR3& rSize) override;	// �傫���ݒ�
	inline VECTOR3 GetVec3Position() const override	{ return m_pos; }		// �ʒu�擾
	inline VECTOR3 GetVec3Rotation() const override	{ return m_rot; }		// �����擾
	inline VECTOR3 GetVec3Size() const override		{ return m_size; }		// �傫���擾
	inline MATRIX* GetPtrMtxWorld() override		{ return &m_mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	inline MATRIX GetMtxWorld() const override		{ return m_mtxWorld; }	// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshCube* Create	// ����
	( // ����
		const VECTOR3&	rPos,		// �ʒu
		const VECTOR3&	rRot,		// ����
		const VECTOR3&	rSize,		// �傫��
		const COLOR&	rCubeCol,	// �L���[�u�F
		const COLOR&	rBorderCol	= color::Black(),		// �����F
		const EBorder	bordState	= BORDER_OFF,			// �������
		const float		fBordThick	= 0.0f,					// ����葾��
		const ETexState	texState	= TEXSTATE_ONE,			// �e�N�X�`�����
		const SFaceTex&	rTexIdx		= SFaceTex(NONE_IDX),	// �e�N�X�`�����
		const EOrigin	origin		= ORIGIN_CENTER,		// ���_
		const VECTOR2&	rTexPartX	= VEC2_ONE,				// �e�N�X�`��������X
		const VECTOR2&	rTexPartY	= VEC2_ONE,				// �e�N�X�`��������Y
		const VECTOR2&	rTexPartZ	= VEC2_ONE				// �e�N�X�`��������Z
	);

	// �����o�֐�
	CRenderState* GetRenderState();						// �����_�[�X�e�[�g���擾
	void BindTexture(const SFaceTex textureIdx);		// �e�N�X�`������
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
	inline SFaceTex GetTextureIndex() const		{ return m_texIdx; }					// �e�N�X�`���C���f�b�N�X�擾
	inline float GetCubeAlpha() const			{ return m_aCol[CUBECOL_CUBE].a; }		// �����x�擾
	inline COLOR GetCubeColor() const			{ return m_aCol[CUBECOL_CUBE]; }		// �L���[�u�F�擾
	inline float GetBorderAlpha() const			{ return m_aCol[CUBECOL_BORDER].a; }	// �����x�擾
	inline COLOR GetBorderColor() const			{ return m_aCol[CUBECOL_BORDER]; }		// �����F�擾
	inline EBorder GetBorderState() const		{ return m_bordState; }					// ������Ԏ擾
	inline float GetBorderThick() const			{ return m_fBordThick; }				// ����葾���擾
	inline ETexState GetTextureState() const	{ return m_texState; }					// �e�N�X�`����Ԏ擾
	inline VECTOR2 GetTexturePatternX() const	{ return m_aTexPart[CUBEPART_X]; }		// �e�N�X�`��������X�擾
	inline VECTOR2 GetTexturePatternY() const	{ return m_aTexPart[CUBEPART_Y]; }		// �e�N�X�`��������Y�擾
	inline VECTOR2 GetTexturePatternZ() const	{ return m_aTexPart[CUBEPART_Z]; }		// �e�N�X�`��������Z�擾
	inline EOrigin GetOrigin() const			{ return m_origin; }					// ���_�擾

protected:
	// ���z�֐�
	virtual void CalcDrawMatrix();	// �`��}�g���b�N�X�v�Z

	// �����o�֐�
	void SetVtx();	// ���_���̐ݒ�
	void SetIdx();	// �C���f�b�N�X���̐ݒ�

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void DrawNormal();	// �ʏ�`��
	void DrawShader(CShader* pShader);	// �V�F�[�_�[�`��

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	CRenderState* m_pRenderState;		// �����_�[�X�e�[�g�̏��
	COLOR m_aCol[CUBECOL_MAX];			// �F
	VECTOR2 m_aTexPart[CUBEPART_MAX];	// �e�N�X�`��������
	MATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	VECTOR3 m_pos;			// �ʒu
	VECTOR3 m_rot;			// ����
	VECTOR3 m_size;			// �傫��
	EBorder m_bordState;	// �����g�p���
	float m_fBordThick;		// ����葾��
	ETexState m_texState;	// �e�N�X�`���g�p���
	SFaceTex m_texIdx;		// �e�N�X�`�����
	EOrigin m_origin;		// ���_
	int m_nNumVtx;			// �K�v���_��
	int m_nNumIdx;			// �K�v�C���f�b�N�X��
};

#endif	// _OBJECT_MESHCUBE_H_
