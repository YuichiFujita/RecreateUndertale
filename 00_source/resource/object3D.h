//============================================================
//
//	�I�u�W�F�N�g3D�w�b�_�[ [object3D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g3D�N���X
class CObject3D : public CObject
{
public:
	// ���_��
	enum EOrigin
	{
		ORIGIN_CENTER = 0,	// ���S���_
		ORIGIN_DOWN,		// �����_
		ORIGIN_MAX,			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CObject3D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObject3D() override;

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
	static CObject3D* Create	// ����
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rSize,	// �傫��
		const VECTOR3& rRot = VEC3_ZERO,		// ����
		const COLOR& rCol = color::White(),		// �F
		const EOrigin origin = ORIGIN_CENTER	// ���_
	);

	// �����o�֐�
	CRenderState* GetRenderState();				// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureIdx);	// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char* pTexturePath);	// �e�N�X�`������ (�p�X)
	void SetAlpha(const float fAlpha);			// �����x�ݒ�
	void SetColor(const COLOR& rCol);			// �F�ݒ�
	void SetOrigin(const EOrigin origin);		// ���_�ݒ�
	inline int GetTextureIndex() const	{ return m_nTextureIdx; }	// �e�N�X�`���C���f�b�N�X�擾
	inline float GetAlpha() const		{ return m_col.a; }			// �����x�擾
	inline COLOR GetColor() const		{ return m_col; }			// �F�擾
	inline EOrigin GetOrigin() const	{ return m_origin; }		// ���_�擾
	void SetVertexPosition(const int nIdx, const VECTOR3& rPos);	// ���_�ʒu�ݒ�
	VECTOR3 GetVertexPosition(const int nIdx);						// ���_�ʒu�擾
	void SetGapPosition(const int nIdx, const VECTOR3& rPos);		// ���W�̂���ݒ�
	VECTOR3 GetGapPosition(const int nIdx);							// ���W�̂���擾
	float GetPositionHeight(const VECTOR3&rPos);					// �|���S���̒��n�擾

protected:
	// ���z�֐�
	virtual void CalcDrawMatrix();	// �`��}�g���b�N�X�v�Z

	// �����o�֐�
	void SetVtx();	// ���_���̐ݒ�
	void SetAnimTex	// �A�j���[�V�����̃e�N�X�`�����W�̐ݒ�
	( // ����
		const int nPattern,		// �A�j���[�V�����p�^�[��
		const int nWidthPtrn,	// �e�N�X�`���̉��̕�����
		const int nHeightPtrn	// �e�N�X�`���̏c�̕�����
	);
	void SetScrollTex	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	( // ����
		const float fTexU,		// �e�N�X�`���̉����W�̊J�n�ʒu
		const float fTexV,		// �e�N�X�`���̏c���W�̊J�n�ʒu
		const float fOffsetU,	// �e�N�X�`���̉����W�̃I�t�Z�b�g�ʒu
		const float fOffsetV	// �e�N�X�`���̏c���W�̃I�t�Z�b�g�ʒu
	);

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void DrawNormal();					// �ʏ�`��
	void DrawShader(CShader* pShader);	// �V�F�[�_�[�`��
	void NormalizeNormal();				// �@���̐��K��

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	CRenderState* m_pRenderState;		// �����_�[�X�e�[�g�̏��
	VECTOR3* m_pPosGapBuff;	// ���W�̂���o�b�t�@�ւ̃|�C���^
	MATRIX	m_mtxWorld;		// ���[���h�}�g���b�N�X
	VECTOR3	m_pos;			// �ʒu
	VECTOR3	m_rot;			// ����
	VECTOR3	m_size;			// �傫��
	COLOR	m_col;			// �F
	EOrigin	m_origin;		// ���_
	int		m_nTextureIdx;	// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT3D_H_
