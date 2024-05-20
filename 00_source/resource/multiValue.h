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
	// ���z�u��
	enum EAlignX
	{
		XALIGN_LEFT = 0,	// ������
		XALIGN_CENTER,		// ��������
		XALIGN_RIGHT,		// �E����
		XALIGN_MAX,			// ���̗񋓌^�̑���
	};

	// �c�z�u��
	enum EAlignY
	{
		YALIGN_TOP = 0,	// �㑵��
		YALIGN_CENTER,	// ��������
		YALIGN_BOTTOM,	// ������
		YALIGN_MAX,		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CMultiValue();

	// �f�X�g���N�^
	~CMultiValue() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetPriority(const int nPriority) override;			// �D�揇�ʐݒ�
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	void SetVec3Sizing(const D3DXVECTOR3& rSize) override;	// �傫���ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override	{ return m_pos; }	// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override	{ return m_rot; }	// �����擾
	D3DXVECTOR3 GetVec3Sizing(void) const override		{ return m_size; }	// �傫���擾

	// �ÓI�����o�֐�
	static CMultiValue *Create	// ����
	( // ����
		const CValue::EType type,	// �������
		const int nNum,				// ����
		const int nDigit,			// ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rSize,	// �傫��
		const D3DXVECTOR3& rSpace,	// ��
		const EAlignX alignX = XALIGN_CENTER,	// ���z�u
		const EAlignY alignY = YALIGN_CENTER,	// �c�z�u
		const D3DXVECTOR3& rRot = VEC3_ZERO,	// ����
		const D3DXCOLOR& rCol = XCOL_WHITE		// �F
	);

	// �����o�֐�
	void AddNum(const int nNum);				// ���l���Z
	void SetNum(const int nNum);				// ���l�ݒ�
	void SetMin(const int nMin);				// �ŏ��l�ݒ�
	void SetMax(const int nMax);				// �ő�l�ݒ�
	HRESULT SetDigit(const int nDigit);			// �����ݒ�
	void SetAlignX(const EAlignX align);		// ���z�u�ݒ�
	void SetAlignY(const EAlignY align);		// �c�z�u�ݒ�
	void SetType(const CValue::EType type);		// ��ސݒ�
	void SetColor(const D3DXCOLOR& rCol);		// �F�ݒ�
	void SetSpace(const D3DXVECTOR3& rSpace);	// �󔒐ݒ�
	float GetValueWidth(void) const;			// �����S�̂̉����擾
	float GetValueHeight(void) const;			// �����S�̂̏c���擾
	D3DXVECTOR3 GetValueSize(void) const;		// �����S�̂̑傫���擾

	int GetNum(void) const		{ return m_nNum; }	// ���l�擾
	int GetMin(void) const		{ return m_nMin; }	// �ŏ��l�擾
	int GetMax(void) const		{ return m_nMax; }	// �ő�l�擾
	int GetDigit(void) const	{ return (int)m_listValue.size(); }	// �����擾
	EAlignX GetAlignX(void) const		{ return m_alignX; }		// ���z�u�擾
	EAlignY GetAlignY(void) const		{ return m_alignY; }		// �c�z�u�擾
	D3DXCOLOR GetColor(void) const		{ return m_col; }			// �F�擾
	D3DXVECTOR3 GetSpace(void) const	{ return m_space; }			// �󔒎擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetPositionRelative(void);	// ���Έʒu�ݒ�
	void SetTexNum(void);			// �����̃e�N�X�`�����W�ݒ�

	// �����o�ϐ�
	std::list<CValue*> m_listValue;	// �������X�g
	D3DXVECTOR3 m_pos;		// ���_�ʒu
	D3DXVECTOR3 m_rot;		// ���_����
	D3DXVECTOR3 m_size;		// �傫��
	D3DXVECTOR3 m_space;	// ��
	D3DXCOLOR m_col;		// �F
	EAlignX m_alignX;		// ���z�u
	EAlignY m_alignY;		// �c�z�u
	int m_nNum;				// ����
	int m_nMin;				// �ŏ��l
	int m_nMax;				// �ő�l
};

#endif	// _MULTIVALUE_H_
