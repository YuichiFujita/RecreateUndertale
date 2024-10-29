//============================================================
//
//	�A�j���[�V����2D�w�b�_�[ [anim2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ANIM2D_H_
#define _ANIM2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �A�j���[�V����2D�N���X
class CAnim2D : public CObject2D
{
public:
	// �R���X�g���N�^
	explicit CAnim2D(const CObject::ELabel label = LABEL_NONE, const EDim dimension = DIM_2D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CAnim2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Size(const VECTOR3& rSize) override;	// �傫���ݒ�

	// �ÓI�����o�֐�
	static CAnim2D* Create	// ����
	( // ����
		const int nWidthPtrn,	// �e�N�X�`���̉��̕�����
		const int nHeightPtrn,	// �e�N�X�`���̏c�̕�����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rSize = VEC3_ONE,	// �傫��
		const VECTOR3& rRot = VEC3_ZERO,	// ����
		const COLOR& rCol = color::White()	// �F
	);

	// �����o�֐�
	void SetAlpha(const float fAlpha);				// �����x�ݒ�
	void SetColor(const COLOR& rCol);				// �F�ݒ�
	void SetPattern(const int nPattern);			// �p�^�[���̐ݒ�
	void SetMaxPattern(const int nMaxPtrn);			// �p�^�[���̑����̐ݒ�
	void SetWidthPattern(const int nWidthPtrn);		// �e�N�X�`���̉��������̐ݒ�
	void SetHeightPattern(const int nHeightPtrn);	// �e�N�X�`���̏c�������̐ݒ�
	void SetCounter(const int nCntChange);			// �J�E���^�[�̐ݒ�
	void SetEnableStop(const bool bStop);			// ��~�󋵂̐ݒ�
	void SetEnablePlayBack(const bool bPlayBack);	// �t�Đ��󋵂̐ݒ�
	inline int GetPattern() const		{ return m_nPattern; }	// �p�^�[���̎擾
	inline int GetLoopAnimation() const	{ return m_nNumLoop; }	// �p�^�[���J��Ԃ����̎擾

private:
	// �����o�ϐ�
	int m_nCounter;		// �A�j���[�V�����J�E���^�[
	int m_nCntChange;	// �p�^�[���ύX�J�E���g
	int m_nPattern;		// �A�j���[�V�����p�^�[��
	int m_nMaxPtrn;		// �p�^�[���̑���
	int m_nWidthPtrn;	// �e�N�X�`���̉��̕�����
	int m_nHeightPtrn;	// �e�N�X�`���̏c�̕�����
	int m_nNumLoop;		// �p�^�[���J��Ԃ���
	bool m_bStop;		// ��~��
	bool m_bPlayBack;	// �t�Đ���
};

#endif	// _ANIM2D_H_
