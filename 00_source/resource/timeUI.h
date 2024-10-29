//============================================================
//
//	�^�C��UI�w�b�_�[ [timeUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TIME_UI_H_
#define _TIME_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "value.h"

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �^�C��UI�N���X
class CTimeUI : public CObject
{
public:
	// �萔
	static constexpr int MAX_MIN	= 2;	// �^�C�}�[�̕��̌���
	static constexpr int MAX_SEC	= 2;	// �^�C�}�[�̕b�̌���
	static constexpr int MAX_MSEC	= 3;	// �^�C�}�[�̃~���b�̌���
	static constexpr int MAX_PART	= 2;	// ��؂�̍ő吔
	static constexpr int MAX_DIGIT	= (MAX_MIN + MAX_SEC + MAX_MSEC);	// �^�C�}�[�̌��� (���E�b�E�~���b)

	// �R���X�g���N�^
	CTimeUI();

	// �f�X�g���N�^
	~CTimeUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	inline VECTOR3 GetVec3Position() const override { return m_pos; }	// �ʒu�擾
	inline VECTOR3 GetVec3Rotation() const override { return m_rot; }	// �����擾

	// �ÓI�����o�֐�
	static CTimeUI* Create	// ����
	( // ����
		const float fTime,			// �\������
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rSizeValue,	// �����̑傫��
		const VECTOR3& rSizePart,	// ��؂�̑傫��
		const VECTOR3& rSpaceValue,	// �����̋�
		const VECTOR3& rSpacePart,	// ��؂�̋�
		const CValue::EType type = CValue::TYPE_NORMAL,	// �������
		const EAlignX alignX = XALIGN_CENTER,			// ���z�u
		const EAlignY alignY = YALIGN_CENTER,			// �c�z�u
		const VECTOR3& rRot = VEC3_ZERO,				// ����
		const COLOR& rCol = color::White()				// �F
	);

	// ���z�֐�
	virtual inline void SetTime(const float fTime);				// �\�����Ԑݒ�
	virtual inline float GetTime() const	{ return m_fTime; }	// �\�����Ԏ擾
	virtual inline int GetMin() const		{ return (int)((DWORD)(m_fTime * 1000.0f) / 60000); }		// ���擾
	virtual inline int GetSec() const		{ return (int)((DWORD)(m_fTime * 1000.0f) / 1000 % 60); }	// �b�擾
	virtual inline int GetMSec() const		{ return (int)((DWORD)(m_fTime * 1000.0f) % 1000); }		// �~���b�擾

	// �����o�֐�
	void SetValueType(const CValue::EType type);	// �����̎�ސݒ�
	void SetSizeValue(const VECTOR3& rSize);		// ��؂�̑傫���ݒ�
	void SetSizePart(const VECTOR3& rSize);			// �����̑傫���ݒ�
	void SetSpaceValue(const VECTOR3& rSpace);		// ��؂�̋󔒐ݒ�
	void SetSpacePart(const VECTOR3& rSpace);		// �����̋󔒐ݒ�
	void SetAlpha(const float fAlpha);				// �����x�̐ݒ�
	void SetColor(const COLOR& rCol);				// �F�̐ݒ�
	void SetAlignX(const EAlignX align);			// ���z�u�ݒ�
	void SetAlignY(const EAlignY align);			// �c�z�u�ݒ�
	float GetTimeWidth() const;						// �^�C���S�̂̉����擾
	float GetTimeHeight() const;					// �^�C���S�̂̏c���擾
	VECTOR3 GetTimeSize() const;					// �^�C���S�̂̑傫���擾
	inline CValue::EType GetValueType() const	{ return m_type; }			// �����̎�ގ擾
	inline VECTOR3 GetSizeValue() const			{ return m_sizeValue; }		// ��؂�̑傫���擾
	inline VECTOR3 GetSizePart() const			{ return m_sizePart; }		// �����̑傫���擾
	inline VECTOR3 GetSpaceValue() const		{ return m_spaceValue; }	// ��؂�̋󔒎擾
	inline VECTOR3 GetSpacePart() const			{ return m_spacePart; }		// �����̋󔒎擾
	inline float GetAlpha() const				{ return m_col.a; }			// �����x�̐ݒ�
	inline COLOR GetColor() const				{ return m_col;}			// �F�̐ݒ�
	inline EAlignX GetAlignX() const			{ return m_alignX; }		// ���z�u�擾
	inline EAlignY GetAlignY() const			{ return m_alignY; }		// �c�z�u�擾

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetPositionRelative();	// ���Έʒu�ݒ�
	void SetTexNum();			// �����̃e�N�X�`�����W�ݒ�

	// �����o�ϐ�
	CValue* m_apValue[MAX_DIGIT];	// ���l�̏��
	CObject2D* m_apPart[MAX_PART];	// ��؂�̏��
	CValue::EType m_type;	// �������
	VECTOR3 m_pos;			// ���_�ʒu
	VECTOR3 m_rot;			// ���_����
	VECTOR3 m_sizeValue;	// �����̑傫��
	VECTOR3 m_sizePart;		// ��؂�̑傫��
	VECTOR3 m_spaceValue;	// �����̋�
	VECTOR3 m_spacePart;	// ��؂�̋�
	COLOR m_col;			// �F
	EAlignX m_alignX;		// ���z�u
	EAlignY m_alignY;		// �c�z�u
	float m_fTime;			// �\������
};

#endif	// _TIME_UI_H_
