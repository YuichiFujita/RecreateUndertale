//============================================================
//
//	�I�u�W�F�N�g���f���w�b�_�[ [objectModel.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECTMODEL_H_
#define _OBJECTMODEL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "model.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g���f���N���X
class CObjectModel : public CObject
{
public:
	// �R���X�g���N�^
	explicit CObjectModel(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectModel() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Scale(const VECTOR3& rScale) override;	// �g�嗦�ݒ�
	inline VECTOR3 GetVec3Position() const override	{ return m_pos; }		// �ʒu�擾
	inline VECTOR3 GetVec3Rotation() const override	{ return m_rot; }		// �����擾
	inline VECTOR3 GetVec3Scale() const override	{ return m_scale; }		// �g�嗦�擾
	inline MATRIX* GetPtrMtxWorld() override		{ return &m_mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	inline MATRIX GetMtxWorld() const override		{ return m_mtxWorld; }	// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectModel* Create	// ����
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const VECTOR3& rScale = VEC3_ONE	// �傫��
	);

	// �����o�֐�
	void SetMaterial(const D3DXMATERIAL& rMat, const int nMatIdx);	// �}�e���A���ݒ�
	D3DXMATERIAL GetMaterial(const int nMatIdx) const;	// �}�e���A���擾
	void SetAlpha(const float fAlpha);	// �����x�ݒ�
	float GetAlpha() const;				// �����x�擾
	float GetMaxAlpha() const;			// �ő哧���x�擾

	CRenderState* GetRenderState();						// �����_�[�X�e�[�g���擾
	void BindModel(const int nModelIdx);				// ���f������ (�C���f�b�N�X)
	void BindModel(const char* pModelPath);				// ���f������ (�p�X)
	void SetAllMaterial(const D3DXMATERIAL& rMat);		// �}�e���A���S�ݒ�
	void ResetMaterial();								// �}�e���A���Đݒ�
	void SetModelData(const CModel::SModel& rModel);	// ���f�����ݒ�
	inline int GetModelIdx() const				{ return m_nModelIdx; }	// ���f���C���f�b�N�X�擾
	inline CModel::SModel GetModelData() const	{ return m_modelData; }	// ���f�����擾

protected:
	// ���z�֐�
	virtual void CalcDrawMatrix();	// �`��}�g���b�N�X�v�Z

	// �����o�֐�
	D3DXMATERIAL* GetPtrMaterial(const int nIdx) const;	// �}�e���A���|�C���^�擾

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	HRESULT SetOriginMaterial(const LPD3DXBUFFER pBuffMat, const int nNumMat);	// ���}�e���A���ݒ�
	void DrawNormal();					// �ʏ�`��
	void DrawShader(CShader* pShader);	// �V�F�[�_�[�`��

	// �����o�ϐ�
	CRenderState*	m_pRenderState;	// �����_�[�X�e�[�g�̏��
	D3DXMATERIAL*	m_pMat;			// �}�e���A���ւ̃|�C���^
	CModel::SModel	m_modelData;	// ���f�����
	MATRIX	m_mtxWorld;		// ���[���h�}�g���b�N�X
	VECTOR3	m_pos;			// �ʒu
	VECTOR3	m_rot;			// ����
	VECTOR3	m_scale;		// �g�嗦
	int		m_nModelIdx;	// ���f���C���f�b�N�X
};

#endif	// _OBJECTMODEL_H_
