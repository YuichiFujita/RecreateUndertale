//============================================================
//
//	�X�N���[��2D�w�b�_�[ [scroll2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCROLL2D_H_
#define _SCROLL2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "object2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �X�N���[��2D�N���X
class CScroll2D : public CObject2D
{
public:
	// �R���X�g���N�^
	explicit CScroll2D(const CObject::ELabel label = LABEL_NONE, const CObject::EDim dimension = DIM_2D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CScroll2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Size(const VECTOR3& rSize) override;	// �傫���ݒ�

	// �ÓI�����o�֐�
	static CScroll2D* Create	// ����
	( // ����
		const float fMoveU,		// �����W�̈ړ���
		const float fMoveV,		// �c���W�̈ړ���
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rSize = VEC3_ONE,	// �傫��
		const VECTOR3& rRot = VEC3_ZERO,	// ����
		const COLOR& rCol = color::White()	// �F
	);

	// �����o�֐�
	void SetAlpha(const float fAlpha);		// �����x�ݒ�
	void SetColor(const COLOR& rCol);		// �F�ݒ�
	void SetTexU(const float fTexU);		// �����W�̊J�n�ʒu�ݒ�
	void SetTexV(const float fTexV);		// �c���W�̊J�n�ʒu�ݒ�
	void SetOffsetU(const float fOffsetU);	// �����W�̃I�t�Z�b�g�ʒu�ݒ�
	void SetOffsetV(const float fOffsetV);	// �c���W�̃I�t�Z�b�g�ʒu�ݒ�
	void SetMoveU(const float fMoveU);		// �����W�̈ړ��ʐݒ�
	void SetMoveV(const float fMoveV);		// �c���W�̈ړ��ʐݒ�
	inline float GetTexU()		{ return m_fTexU; }		// �����W�̊J�n�ʒu�擾
	inline float GetTexV()		{ return m_fTexV; }		// �c���W�̊J�n�ʒu�擾
	inline float GetOffsetU()	{ return m_fOffsetU; }	// �����W�̃I�t�Z�b�g�ʒu�擾
	inline float GetOffsetV()	{ return m_fOffsetV; }	// �c���W�̃I�t�Z�b�g�ʒu�擾
	inline float GetMoveU()		{ return m_fMoveU; }	// �����W�̈ړ��ʎ擾
	inline float GetMoveV()		{ return m_fMoveV; }	// �c���W�̈ړ��ʎ擾
	inline int GetNumLoopU()	{ return m_nNumLoopU; }	// ���p�^�[���J��Ԃ����擾
	inline int GetNumLoopV()	{ return m_nNumLoopV; }	// �c�p�^�[���J��Ԃ����擾

private:
	// �����o�֐�
	bool NormalizeTexPos(float* pTexPos);	// �e�N�X�`�����W���K��

	// �����o�ϐ�
	float m_fTexU;		// �e�N�X�`�������W�̊J�n�ʒu
	float m_fTexV;		// �e�N�X�`���c���W�̊J�n�ʒu
	float m_fOffsetU;	// �e�N�X�`�������W�̃I�t�Z�b�g�ʒu
	float m_fOffsetV;	// �e�N�X�`���c���W�̃I�t�Z�b�g�ʒu
	float m_fMoveU;		// �e�N�X�`�������W�̈ړ���
	float m_fMoveV;		// �e�N�X�`���c���W�̈ړ���
	int m_nNumLoopU;	// ���p�^�[���J��Ԃ���
	int m_nNumLoopV;	// �c�p�^�[���J��Ԃ���
};

#endif	// _SCROLL2D_H_
