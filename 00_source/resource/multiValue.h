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
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Size(const VECTOR3& rSize) override;	// �傫���ݒ�
	inline VECTOR3 GetVec3Position() const override	{ return m_pos; }	// �ʒu�擾
	inline VECTOR3 GetVec3Rotation() const override	{ return m_rot; }	// �����擾
	inline VECTOR3 GetVec3Size() const override		{ return m_size; }	// �傫���擾

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
	float GetValueWidth() const;			// �����S�̂̉����擾
	float GetValueHeight() const;			// �����S�̂̏c���擾
	VECTOR3 GetValueSize() const;			// �����S�̂̑傫���擾

	inline int GetNum() const	{ return m_nNum; }	// ���l�擾
	inline int GetMin() const	{ return m_nMin; }	// �ŏ��l�擾
	inline int GetMax() const	{ return m_nMax; }	// �ő�l�擾

	inline int GetDigit() const			{ return (int)m_listValue.size(); }	// �����擾
	inline EAlignX GetAlignX() const	{ return m_alignX; }	// ���z�u�擾
	inline EAlignY GetAlignY() const	{ return m_alignY; }	// �c�z�u�擾
	inline float GetAlpha() const		{ return m_col.a; }		// �����x�擾
	inline COLOR GetColor() const		{ return m_col; }		// �F�擾
	inline VECTOR3 GetSpace() const		{ return m_space; }		// �󔒎擾

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetPositionRelative();	// ���Έʒu�ݒ�
	void SetTexNum();			// �����̃e�N�X�`�����W�ݒ�

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
