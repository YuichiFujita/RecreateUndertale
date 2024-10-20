//============================================================
//
//	�}���`�����w�b�_�[ [multiValue.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MULTIVALUE_H_
#define _MULTIVALUE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "value.h"

//************************************************************
//	�N���X��`
//************************************************************
// �}���`�����N���X
class CMultiValue : public CObject
{
public:
	// �R���X�g���N�^
	CMultiValue();

	// �f�X�g���N�^
	~CMultiValue() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Size(const VECTOR3& rSize) override;	// �傫���ݒ�
	VECTOR3 GetVec3Position(void) const override	{ return m_pos; }	// �ʒu�擾
	VECTOR3 GetVec3Rotation(void) const override	{ return m_rot; }	// �����擾
	VECTOR3 GetVec3Size(void) const override		{ return m_size; }	// �傫���擾

	// �ÓI�����o�֐�
	static CMultiValue* Create	// ����
	( // ����
		const CValue::EType type,	// �������
		const int nNum,				// ����
		const int nDigit,			// ����
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rSize,		// �傫��
		const VECTOR3& rSpace,		// ��
		const EAlignX alignX = XALIGN_CENTER,	// ���z�u
		const EAlignY alignY = YALIGN_CENTER,	// �c�z�u
		const VECTOR3& rRot = VEC3_ZERO,		// ����
		const COLOR& rCol = color::White()		// �F
	);

	// �����o�֐�
	void AddNum(const int nNum);			// ���l���Z
	void SetNum(const int nNum);			// ���l�ݒ�
	void SetMin(const int nMin);			// �ŏ��l�ݒ�
	void SetMax(const int nMax);			// �ő�l�ݒ�
	HRESULT SetDigit(const int nDigit);		// �����ݒ�
	void SetAlignX(const EAlignX align);	// ���z�u�ݒ�
	void SetAlignY(const EAlignY align);	// �c�z�u�ݒ�
	void SetType(const CValue::EType type);	// ��ސݒ�
	void SetAlpha(const float fAlpha);		// �����x�ݒ�
	void SetColor(const COLOR& rCol);		// �F�ݒ�
	void SetSpace(const VECTOR3& rSpace);	// �󔒐ݒ�
	float GetValueWidth(void) const;		// �����S�̂̉����擾
	float GetValueHeight(void) const;		// �����S�̂̏c���擾
	VECTOR3 GetValueSize(void) const;		// �����S�̂̑傫���擾

	int GetNum(void) const		{ return m_nNum; }	// ���l�擾
	int GetMin(void) const		{ return m_nMin; }	// �ŏ��l�擾
	int GetMax(void) const		{ return m_nMax; }	// �ő�l�擾
	int GetDigit(void) const	{ return (int)m_listValue.size(); }	// �����擾
	EAlignX GetAlignX(void) const	{ return m_alignX; }	// ���z�u�擾
	EAlignY GetAlignY(void) const	{ return m_alignY; }	// �c�z�u�擾
	float GetAlpha(void) const		{ return m_col.a; }		// �����x�擾
	COLOR GetColor(void) const		{ return m_col; }		// �F�擾
	VECTOR3 GetSpace(void) const	{ return m_space; }		// �󔒎擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetPositionRelative(void);	// ���Έʒu�ݒ�
	void SetTexNum(void);			// �����̃e�N�X�`�����W�ݒ�

	// �����o�ϐ�
	std::list<CValue*> m_listValue;	// �������X�g
	VECTOR3 m_pos;		// ���_�ʒu
	VECTOR3 m_rot;		// ���_����
	VECTOR3 m_size;		// �傫��
	VECTOR3 m_space;	// ��
	COLOR m_col;		// �F
	EAlignX m_alignX;	// ���z�u
	EAlignY m_alignY;	// �c�z�u
	int m_nNum;			// ����
	int m_nMin;			// �ŏ��l
	int m_nMax;			// �ő�l
};

#endif	// _MULTIVALUE_H_
