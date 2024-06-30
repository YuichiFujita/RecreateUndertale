//============================================================
//
//	�A�j���[�V����3D�w�b�_�[ [anim3D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ANIM3D_H_
#define _ANIM3D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object3D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �A�j���[�V����3D�N���X
class CAnim3D : public CObject3D
{
public:
	// �萔
	static constexpr float DEF_NEXT = 1.0f;	// �p�^�[���ύX���� (�f�t�H���g)

	// �R���X�g���N�^
	explicit CAnim3D(const CObject::ELabel label = LABEL_NONE, const EDim dimension = DIM_3D, const int nPriority = object::DEFAULT_PRIO);

	// �f�X�g���N�^
	~CAnim3D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Sizing(const D3DXVECTOR3& rSize) override;	// �傫���ݒ�

	// �ÓI�����o�֐�
	static CAnim3D *Create	// ����
	( // ����
		const POSGRID2& rPtrn,		// �e�N�X�`��������
		const D3DXVECTOR3& rPos,	// �ʒu
		const float fNextTime = DEF_NEXT,		// �p�^�[���ύX����
		const D3DXVECTOR3& rSize = VEC3_ONE,	// �傫��
		const D3DXVECTOR3& rRot = VEC3_ZERO,	// ����
		const D3DXCOLOR& rCol = XCOL_WHITE		// �F
	);

	// �����o�֐�
	void SetColor(const D3DXCOLOR& rCol);				// �F�ݒ�
	void SetCurPtrn(const int nPtrn);					// ���݃p�^�[���ݒ�
	void SetTexPtrn(const POSGRID2& rPtrn);				// �e�N�X�`���������ݒ�
	void SetTexPtrnWidth(const int nTexPtrnW);			// �e�N�X�`�����������ݒ�
	void SetTexPtrnHeight(const int nTexPtrnH);			// �e�N�X�`���c�������ݒ�
	void SetEnablePlay(const bool bPlay);				// �Đ��t���O�ݒ�
	void SetEnablePlayBack(const bool bPlayBack);		// �t�Đ��t���O�ݒ�
	void ResetCurPtrn(void);							// ���݃p�^�[��������
	int GetCurPtrn(void) const	{ return m_nCurPtrn; }	// ���݃p�^�[���擾
	void ResetNumLoop(void)		{ m_nNumLoop = 0; }		// �p�^�[���J��Ԃ���������
	int GetLoopAnim(void) const	{ return m_nNumLoop; }	// �p�^�[���J��Ԃ����擾

	float GetCurTime(void) const		{ return m_fCurTime; }		// ���݂̑ҋ@����
	float GetCurWholeTime(void) const	{ return m_fCurWholeTime; }	// ���݂̑S�̎���
	float GetMaxWholeTime(void) const	{ return m_fMaxWholeTime; }	// ���S�̎���
	void SetNextTime(const int nPtrnID, const float fNextTime);		// �p�^�[���ύX���Ԑݒ� (�p�^�[���w��)
	void SetNextTime(const float fNextTime);						// �p�^�[���ύX���Ԑݒ� (�S�p�^�[��)

private:
	// �����o�֐�
	HRESULT SetMaxPtrn(const int nMaxPtrn);	// �p�^�[�������ݒ�
	void NextPtrn(const float fDeltaTime);	// �p�^�[�����Z
	void BackPtrn(const float fDeltaTime);	// �p�^�[�����Z

	// �����o�ϐ�
	std::function<void(float)> m_funcNext;	// �p�^�[���ύX�֐��|�C���^
	POSGRID2 m_ptrn;		// �e�N�X�`��������
	float *m_pNextTime;		// �p�^�[���ύX����
	float m_fCurTime;		// ���݂̑ҋ@����
	float m_fCurWholeTime;	// ���݂̑S�̎���
	float m_fMaxWholeTime;	// ���S�̎���
	int m_nCurPtrn;			// ���݂̃p�^�[��
	int m_nMaxPtrn;			// �p�^�[������
	int m_nNumLoop;			// �p�^�[���J��Ԃ���
	bool m_bPlay;			// �Đ���
	bool m_bPlayBack;		// �t�Đ���
	bool m_bLoop;			// ���[�v��
};

#endif	// _ANIM3D_H_
