//============================================================
//
//	�I�u�W�F�N�g�r���{�[�h�w�b�_�[ [objectBillboard.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECTBILLBOARD_H_
#define _OBJECTBILLBOARD_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�r���{�[�h�N���X
class CObjectBillboard : public CObject
{
public:
	// ���_��
	enum EOrigin
	{
		ORIGIN_CENTER = 0,	// ���S���_
		ORIGIN_DOWN,		// �����_
		ORIGIN_MAX,			// ���̗񋓌^�̑���
	};

	// ��]��
	enum ERotate
	{
		ROTATE_NORMAL = 0,	// �ʏ��]
		ROTATE_LATERAL,		// ����]
		ROTATE_MAX,			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CObjectBillboard(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectBillboard() override;

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
	static CObjectBillboard* Create	// ����
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rSize,	// �傫��
		const VECTOR3& rRot = VEC3_ZERO,		// ����
		const COLOR& rCol = color::White(),		// �F
		const EOrigin origin = ORIGIN_CENTER,	// ���_
		const ERotate rotate = ROTATE_NORMAL	// ��]
	);

	// �����o�֐�
	CRenderState* GetRenderState();				// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureIdx);	// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char* pTexturePath);	// �e�N�X�`������ (�p�X)
	void SetAlpha(const float fAlpha);			// �����x�ݒ�
	void SetColor(const COLOR& rCol);			// �F�ݒ�
	void SetOrigin(const EOrigin origin);		// ���_�ݒ�
	void SetRotate(const ERotate rotate);		// ��]�ݒ�
	inline int GetTextureIndex() const	{ return m_nTextureIdx; }	// �e�N�X�`���C���f�b�N�X�擾
	inline float GetAlpha() const		{ return m_col.a; }			// �����x�擾
	inline COLOR GetColor() const		{ return m_col; }			// �F�擾
	inline EOrigin GetOrigin() const	{ return m_origin; }		// ���_�擾
	inline ERotate GetRotate() const	{ return m_rotate; }		// ��]�擾

protected:
	// ���z�֐�
	virtual void CalcDrawMatrix();	// �`��}�g���b�N�X�v�Z

	// �����o�֐�
	void SetVtx();	// ���_���̐ݒ�

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void DrawNormal();	// �ʏ�`��
	void DrawShader(CShader* pShader);	// �V�F�[�_�[�`��

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	CRenderState* m_pRenderState;		// �����_�[�X�e�[�g�̏��
	MATRIX	m_mtxWorld;		// ���[���h�}�g���b�N�X
	VECTOR3	m_pos;			// �ʒu
	VECTOR3	m_rot;			// ����
	VECTOR3	m_size;			// �傫��
	COLOR	m_col;			// �F
	EOrigin	m_origin;		// ���_
	ERotate	m_rotate;		// ��]
	float	m_fAngle;		// �Ίp���̊p�x
	float	m_fLength;		// �Ίp���̒���
	int		m_nTextureIdx;	// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECTBILLBOARD_H_
