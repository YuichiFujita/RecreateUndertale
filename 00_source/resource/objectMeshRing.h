//============================================================
//
//	�I�u�W�F�N�g���b�V�������O�w�b�_�[ [objectMeshRing.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECT_MESHRING_H_
#define _OBJECT_MESHRING_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g���b�V�������O�N���X
class CObjectMeshRing : public CObject
{
public:
	// �e�N�X�`��������
	enum ETexDir
	{
		TEXDIR_OUTSIDE = 0,	// �e�N�X�`���O������
		TEXDIR_INSIDE,		// �e�N�X�`����������
		TEXDIR_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CObjectMeshRing(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectMeshRing() override;

	// ���b�V�������O�\����
	struct SMeshRing
	{
		VECTOR3	pos;			// �ʒu
		VECTOR3	rot;			// ����
		COLOR	col;			// �F
		MATRIX	mtxWorld;		// ���[���h�}�g���b�N�X
		ETexDir	texDir;			// �e�N�X�`������
		float	fHoleRadius;	// ���̔��a
		float	fThickness;		// ����
		float	fOuterPlusY;	// �O����Y���W���Z��
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	inline VECTOR3 GetVec3Position() const override	{ return m_meshRing.pos; }			// �ʒu�擾
	inline VECTOR3 GetVec3Rotation() const override	{ return m_meshRing.rot; }			// �����擾
	inline MATRIX* GetPtrMtxWorld() override		{ return &m_meshRing.mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	inline MATRIX GetMtxWorld() const override		{ return m_meshRing.mtxWorld; }		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectMeshRing* Create	// ����
	( // ����
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rRot,		// ����
		const COLOR& rCol,			// �F
		const POSGRID2& rPart,		// ������
		const POSGRID2& rTexPart,	// �e�N�X�`��������
		const float fHoleRadius,	// ���̔��a
		const float fThickness,		// ����
		const float fOuterPlusY		// �O����Y���W���Z��
	);

	// �����o�֐�
	CRenderState* GetRenderState();					// �����_�[�X�e�[�g���擾
	void BindTexture(const int nTextureID);			// �e�N�X�`������ (�C���f�b�N�X)
	void BindTexture(const char* pTexturePath);		// �e�N�X�`������ (�p�X)
	void SetAlpha(const float fAlpha);				// �����x�ݒ�
	void SetColor(const COLOR& rCol);				// �F�ݒ�
	void SetTexDir(const ETexDir texDir);			// �e�N�X�`�������ݒ�
	void SetHoleRadius(const float fHoleRadius);	// ���̔��a�ݒ�
	void SetThickness(const float fThickness);		// �����ݒ�
	void SetOuterPlusY(const float fOuterPlusY);	// �O����Y���W���Z�ʐݒ�
	HRESULT SetPattern(const POSGRID2& rPart);		// �������ݒ�
	void SetTexPattern(const POSGRID2& rTexPart);	// �e�N�X�`���������ݒ�
	inline int GetTextureIndex() const		{ return m_nTextureID; }			// �e�N�X�`���C���f�b�N�X�擾
	inline float GetAlpha() const			{ return m_meshRing.col.a; }		// �����x�擾
	inline COLOR GetColor() const			{ return m_meshRing.col; }			// �F�擾
	inline ETexDir GetTexDir() const		{ return m_meshRing.texDir; }		// �e�N�X�`�������擾
	inline float GetHoleRadius() const		{ return m_meshRing.fHoleRadius; }	// ���̔��a�擾
	inline float GetThickness() const		{ return m_meshRing.fThickness; }	// �����擾
	inline float GetOuterPlusY() const		{ return m_meshRing.fOuterPlusY; }	// �O����Y���W���Z�ʎ擾
	inline POSGRID2 GetPattern() const		{ return m_part; }					// �������擾
	inline POSGRID2 GetTexPattern() const	{ return m_texPart; }				// �e�N�X�`���������擾

protected:
	// �����o�֐�
	void SetVtx();		// ���_���̐ݒ�
	void SetIdx();		// �C���f�b�N�X���̐ݒ�
	void SetScrollTex	// �X�N���[���̃e�N�X�`�����W�̐ݒ�
	( // ����
		const float fTexU,	// �e�N�X�`���̉����W�̊J�n�ʒu
		const float fTexV	// �e�N�X�`���̏c���W�̊J�n�ʒu
	);

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
	SMeshRing m_meshRing;	// ���b�V�������O�̏��
	POSGRID2 m_part;		// ������
	POSGRID2 m_texPart;		// �e�N�X�`��������
	int m_nNumVtx;			// �K�v���_��
	int m_nNumIdx;			// �K�v�C���f�b�N�X��
	int m_nTextureID;		// �e�N�X�`���C���f�b�N�X
};

#endif	// _OBJECT_MESHRING_H_
