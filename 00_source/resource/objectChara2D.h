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
#include "character.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I�u�W�F�N�g�L�����N�^�[2D�N���X
class CObjectChara2D : public CAnim3D
{
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
	static CObjectChara2D *Create(const D3DXVECTOR3 &rPos, const D3DXVECTOR3 &rRot = VEC3_ZERO);	// ����

	// �����o�֐�
	void SetPartsInfo	// �p�[�c���ݒ�
	( // ����
		const int nID,				// �p�[�c�C���f�b�N�X
		const int nParentID,		// �e�C���f�b�N�X
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const char *pFileName		// �t�@�C����
	);

	void BindCharaData(const char *pCharaPass);				// �L�����N�^�[��񊄓�
	void SetPartsInfo(CCharacter::SPartsInfo& rInfo);		// �p�[�c���ݒ�
	void SetMotion(const int nType);						// ���[�V�����ݒ�
	CMotion2D *GetMotion(void) const { return m_pMotion; }	// ���[�V�����擾

	void AddMotionInfo(const CMotion2D::SMotion& rInfo)	{ m_pMotion->AddInfo(rInfo); }					// ���[�V�������ǉ�
	void SetEnableMotionUpdate(const bool bUpdate)		{ m_pMotion->SetEnableUpdate(bUpdate); }		// �X�V�󋵐ݒ�
	int GetMotionType(void) const			{ return m_pMotion->GetType(); }							// ���[�V������ގ擾
	int GetMotionNumType(void) const		{ return m_pMotion->GetNumType(); }							// ���[�V������ޑ����擾
	int GetMotionKey(void) const			{ return m_pMotion->GetKey();}								// ���[�V�����L�[�ԍ��擾
	int GetMotionNumKey(void) const			{ return m_pMotion->GetNumKey(m_pMotion->GetType()); }		// ���[�V�����L�[�����擾
	int GetMotionKeyCounter(void) const		{ return m_pMotion->GetKeyCounter(); }						// ���[�V�����L�[�J�E���^�[�擾
	int GetMotionWholeCounter(void) const	{ return m_pMotion->GetWholeCounter(); }					// ���[�V�����S�̃J�E���^�[�擾
	int GetMotionWholeFrame(void) const		{ return m_pMotion->GetWholeFrame(m_pMotion->GetType()); }	// ���[�V�����S�̃t���[�����擾
	int GetMotionCancelFrame(void) const	{ return m_pMotion->GetCancelFrame(m_pMotion->GetType()); }	// ���[�V�����L�����Z���t���[���擾
	int GetMotionComboFrame(void) const		{ return m_pMotion->GetComboFrame(m_pMotion->GetType()); }	// ���[�V�����R���{�t���[���擾
	bool IsMotionFinish(void) const			{ return m_pMotion->IsFinish(); }							// ���[�V�����I���擾
	bool IsMotionLoop(void) const			{ return m_pMotion->IsLoop(m_pMotion->GetType()); }			// ���[�V�������[�v�擾
	bool IsMotionCancel(void) const			{ return m_pMotion->IsCancel(m_pMotion->GetType()); }		// ���[�V�����L�����Z���擾
	bool IsMotionCombo(void) const			{ return m_pMotion->IsCombo(m_pMotion->GetType()); }		// ���[�V�����R���{�擾

private:
	// �����o�ϐ�
	CMotion2D *m_pMotion;	// ���[�V����2D���
};

#endif	// _OBJECTCHARA2D_H_
