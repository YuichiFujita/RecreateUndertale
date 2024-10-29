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
	explicit CAnim3D(const CObject::ELabel label = LABEL_NONE, const EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CAnim3D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Size(const VECTOR3& rSize) override;	// �傫���ݒ�

	// �ÓI�����o�֐�
	static CAnim3D* Create	// ����
	( // ����
		const POSGRID2& rPtrn,	// �e�N�X�`��������
		const VECTOR3& rPos,	// �ʒu
		const float fNextTime = DEF_NEXT,	// �p�^�[���ύX����
		const VECTOR3& rSize = VEC3_ONE,	// �傫��
		const VECTOR3& rRot = VEC3_ZERO,	// ����
		const COLOR& rCol = color::White()	// �F
	);

	// �����o�֐�
	void SetAlpha(const float fAlpha);				// �����x�ݒ�
	void SetColor(const COLOR& rCol);				// �F�ݒ�
	void SetCurPtrn(const int nPtrn);				// ���݃p�^�[���ݒ�
	void SetTexPtrn(const POSGRID2& rPtrn);			// �e�N�X�`���������ݒ�
	void SetTexPtrnWidth(const int nTexPtrnW);		// �e�N�X�`�����������ݒ�
	void SetTexPtrnHeight(const int nTexPtrnH);		// �e�N�X�`���c�������ݒ�
	void SetEnablePlay(const bool bPlay);			// �Đ��t���O�ݒ�
	void SetEnablePlayBack(const bool bPlayBack);	// �t�Đ��t���O�ݒ�
	void SetEnableLoop(const bool bLoop);			// ���[�v�t���O�ݒ�
	void ResetCurPtrn();							// ���݃p�^�[��������
	void SetNextTime(const int nPtrnIdx, const float fNextTime);	// �p�^�[���ύX���Ԑݒ� (�p�^�[���w��)
	void SetNextTime(const float fNextTime);						// �p�^�[���ύX���Ԑݒ� (�S�p�^�[��)

	inline int GetCurPtrn() const	{ return m_nCurPtrn; }	// ���݃p�^�[���擾
	inline void ResetNumLoop()		{ m_nNumLoop = 0; }		// �p�^�[���J��Ԃ���������
	inline int GetLoopAnim() const	{ return m_nNumLoop; }	// �p�^�[���J��Ԃ����擾
	inline bool IsPlay() const		{ return m_bPlay; }		// �Đ��t���O�擾
	inline bool IsPlayBack() const	{ return m_bPlayBack; }	// �t�Đ��t���O�擾
	inline bool IsLoop() const		{ return m_bLoop; }		// ���[�v�t���O�擾
	inline bool IsFinish() const	{ return m_bFinish; }	// �I���t���O�擾
	inline float GetCurTime() const			{ return m_fCurTime; }		// ���݂̑ҋ@����
	inline float GetCurWholeTime() const	{ return m_fCurWholeTime; }	// ���݂̑S�̎���
	inline float GetMaxWholeTime() const	{ return m_fMaxWholeTime; }	// ���S�̎���

private:
	// �����o�֐�
	HRESULT SetMaxPtrn(const int nMaxPtrn);	// �p�^�[�������ݒ�
	void NextPtrn(const float fDeltaTime);	// �p�^�[�����Z
	void BackPtrn(const float fDeltaTime);	// �p�^�[�����Z

	// �����o�ϐ�
	std::function<void(float)> m_funcPattern;	// �p�^�[���ύX�֐��|�C���^
	POSGRID2 m_ptrn;		// �e�N�X�`��������
	float* m_pNextTime;		// �p�^�[���ύX����
	float m_fCurTime;		// ���݂̑ҋ@����
	float m_fCurWholeTime;	// ���݂̑S�̎���
	float m_fMaxWholeTime;	// ���S�̎���
	int m_nCurPtrn;			// ���݂̃p�^�[��
	int m_nMaxPtrn;			// �p�^�[������
	int m_nNumLoop;			// �p�^�[���J��Ԃ���
	bool m_bPlay;			// �Đ��t���O
	bool m_bPlayBack;		// �t�Đ��t���O
	bool m_bLoop;			// ���[�v�t���O
	bool m_bFinish;			// �I���t���O
};

#endif	// _ANIM3D_H_
