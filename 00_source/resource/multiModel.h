//============================================================
//
//	�}���`���f���w�b�_�[ [multiModel.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MULTIMODEL_H_
#define _MULTIMODEL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectModel.h"

//************************************************************
//	�N���X��`
//************************************************************
// �}���`���f���N���X
class CMultiModel : public CObjectModel
{
public:
	// �R���X�g���N�^
	explicit CMultiModel(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CMultiModel() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CMultiModel* Create	// ����
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const VECTOR3& rScale = VEC3_ONE	// �傫��
	);

	// �����o�֐�
	inline CObject* GetParentObject() const { return m_pParent; }	// �e�I�u�W�F�N�g�擾
	void SetParentObject(CObject* pObject);	// �e�I�u�W�F�N�g�ݒ�
	void DeleteParentObject();				// �e�I�u�W�F�N�g�폜

private:
	// �I�[�o�[���C�h�֐�
	void CalcDrawMatrix() override;	// �`��}�g���b�N�X�v�Z

	// �����o�ϐ�
	CObject* m_pParent;	// �e�I�u�W�F�N�g�ւ̃|�C���^
};

#endif	// _MULTIMODEL_H_
