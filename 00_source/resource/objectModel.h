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
	explicit CObjectModel(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectModel() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;				// �X�V
	void Draw(CShader *pShader = nullptr) override;				// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;		// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;		// �����ݒ�
	void SetVec3Scaling(const D3DXVECTOR3& rScale) override;	// �g�嗦�ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override	{ return m_pos; }		// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override	{ return m_rot; }		// �����擾
	D3DXVECTOR3 GetVec3Scaling(void) const override		{ return m_scale; }		// �g�嗦�擾
	D3DXMATRIX *GetPtrMtxWorld(void) override			{ return &m_mtxWorld; }	// �}�g���b�N�X�|�C���^�擾
	D3DXMATRIX GetMtxWorld(void) const override			{ return m_mtxWorld; }	// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CObjectModel *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const D3DXVECTOR3& rScale = VEC3_ONE	// �傫��
	);

	// �����o�֐�
	void SetMaterial(const D3DXMATERIAL& rMat, const int nMatID);	// �}�e���A���ݒ�
	D3DXMATERIAL GetMaterial(const int nMatID) const;	// �}�e���A���擾
	void SetAlpha(const float fAlpha);	// �����x�ݒ�
	float GetAlpha(void) const;			// �����x�擾
	float GetMaxAlpha(void) const;		// �ő哧���x�擾

	CRenderState *GetRenderState(void);					// �����_�[�X�e�[�g���擾
	void BindModel(const int nModelID);					// ���f������ (�C���f�b�N�X)
	void BindModel(const char *pModelPass);				// ���f������ (�p�X)
	void SetAllMaterial(const D3DXMATERIAL& rMat);		// �}�e���A���S�ݒ�
	void ResetMaterial(void);							// �}�e���A���Đݒ�
	void SetModelData(const CModel::SModel& rModel);	// ���f�����ݒ�
	void SetMtxWorld(const D3DXMATRIX& rMtxWorld);		// �}�g���b�N�X�ݒ�
	int GetModelID(void) const				{ return m_nModelID; }	// ���f���C���f�b�N�X�擾
	CModel::SModel GetModelData(void) const	{ return m_modelData; }	// ���f�����擾

protected:
	// �����o�֐�
	D3DXMATERIAL *GetPtrMaterial(const int nID) const;	// �}�e���A���|�C���^�擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	HRESULT SetOriginMaterial(const LPD3DXBUFFER pBuffMat, const int nNumMat);	// ���}�e���A���ݒ�
	void DrawNormal(void);	// �ʏ�`��
	void DrawShader(CShader *pShader);	// �V�F�[�_�[�`��

	// �����o�ϐ�
	CRenderState	*m_pRenderState;	// �����_�[�X�e�[�g�̏��
	D3DXMATERIAL	*m_pMat;			// �}�e���A���ւ̃|�C���^
	CModel::SModel	m_modelData;		// ���f�����
	D3DXMATRIX		m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3		m_pos;				// �ʒu
	D3DXVECTOR3		m_rot;				// ����
	D3DXVECTOR3		m_scale;			// �g�嗦
	int				m_nModelID;			// ���f���C���f�b�N�X
};

#endif	// _OBJECTMODEL_H_
