//============================================================
//
//	�I�u�W�F�N�g�L�����N�^�[2D�w�b�_�[ [objectChara2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBJECTCHARA2D_H_
#define _OBJECTCHARA2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "anim3D.h"
#include "motion2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�L�����N�^�[2D�N���X
class CObjectChara2D : public CAnim3D
{
public:
	// �R���X�g���N�^
	explicit CObjectChara2D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CObjectChara2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CObjectChara2D *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot = VEC3_ZERO);	// ����

	// �����o�֐�
	void BindCharaData(const char *pCharaPass);				// �L�����N�^�[��񊄓�
	void SetMotion(const int nType);						// ���[�V�����ݒ�
	CMotion2D *GetMotion(void) const { return m_pMotion; }	// ���[�V�����擾

	void AddMotionInfo(const CMotion2D::SMotion& rInfo)	{ m_pMotion->AddInfo(rInfo); }					// ���[�V�������ǉ�
	float GetMotionCancelTime(void) const	{ return m_pMotion->GetCancelTime(m_pMotion->GetType()); }	// ���[�V�����L�����Z�����Ԏ擾
	float GetMotionComboTime(void) const	{ return m_pMotion->GetComboTime(m_pMotion->GetType()); }	// ���[�V�����R���{���Ԏ擾
	int GetMotionType(void) const			{ return m_pMotion->GetType(); }	// ���[�V������ގ擾
	int GetMotionNumType(void) const		{ return m_pMotion->GetNumType(); }	// ���[�V������ޑ����擾
	bool IsMotionCancel(void) const			{ return m_pMotion->IsCancel(); }	// ���[�V�����L�����Z���擾
	bool IsMotionCombo(void) const			{ return m_pMotion->IsCombo(); }	// ���[�V�����R���{�擾

private:
	// �����o�ϐ�
	CMotion2D *m_pMotion;	// ���[�V����2D���
};

#endif	// _OBJECTCHARA2D_H_
