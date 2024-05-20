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
//	�萔�錾
//************************************************************
namespace timeUI
{
	const int MAX_MIN	= 2;	// �^�C�}�[�̕��̌���
	const int MAX_SEC	= 2;	// �^�C�}�[�̕b�̌���
	const int MAX_MSEC	= 3;	// �^�C�}�[�̃~���b�̌���
	const int MAX_PART	= 2;	// ��؂�̍ő吔

	const int MAX_DIGIT = (MAX_MIN + MAX_SEC + MAX_MSEC);	// �^�C�}�[�̌��� (���E�b�E�~���b)
}

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
	CTimeUI();

	// �f�X�g���N�^
	~CTimeUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader *pShader = nullptr) override;		// �`��
	void SetPriority(const int nPriority) override;		// �D�揇�ʐݒ�
	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�
	void SetVec3Position(const D3DXVECTOR3& rPos) override;				// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;				// �����ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override { return m_pos; }	// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override { return m_rot; }	// �����擾

	// �ÓI�����o�֐�
	static CTimeUI *Create	// ����
	( // ����
		const float fTime,				// �\������
		const D3DXVECTOR3& rPos,		// �ʒu
		const D3DXVECTOR3& rSizeValue,	// �����̑傫��
		const D3DXVECTOR3& rSizePart,	// ��؂�̑傫��
		const D3DXVECTOR3& rSpaceValue,	// �����̋�
		const D3DXVECTOR3& rSpacePart,	// ��؂�̋�
		const CValue::EType type = CValue::TYPE_NORMAL,	// �������
		const EAlignX alignX = XALIGN_CENTER,			// ���z�u
		const EAlignY alignY = YALIGN_CENTER,			// �c�z�u
		const D3DXVECTOR3& rRot = VEC3_ZERO,			// ����
		const D3DXCOLOR& rCol = XCOL_WHITE				// �F
	);

	// ���z�֐�
	virtual void SetTime(const float fTime);				// �\�����Ԑݒ�
	virtual float GetTime(void) const	{ return m_fTime; }	// �\�����Ԏ擾
	virtual int GetMin(void) const		{ return (int)((DWORD)(m_fTime * 1000.0f) / 60000); }		// ���擾
	virtual int GetSec(void) const		{ return (int)((DWORD)(m_fTime * 1000.0f) / 1000 % 60); }	// �b�擾
	virtual int GetMSec(void) const		{ return (int)((DWORD)(m_fTime * 1000.0f) % 1000); }		// �~���b�擾

	// �����o�֐�
	void SetValueType(const CValue::EType type);	// �����̎�ސݒ�
	void SetSizingValue(const D3DXVECTOR3& rSize);	// ��؂�̑傫���ݒ�
	void SetSizingPart(const D3DXVECTOR3& rSize);	// �����̑傫���ݒ�
	void SetSpaceValue(const D3DXVECTOR3& rSpace);	// ��؂�̋󔒐ݒ�
	void SetSpacePart(const D3DXVECTOR3& rSpace);	// �����̋󔒐ݒ�
	void SetColor(const D3DXCOLOR& rCol);			// �F�̐ݒ�
	void SetAlignX(const EAlignX align);			// ���z�u�ݒ�
	void SetAlignY(const EAlignY align);			// �c�z�u�ݒ�
	float GetTimeWidth(void) const;					// �^�C���S�̂̉����擾
	float GetTimeHeight(void) const;				// �^�C���S�̂̏c���擾
	D3DXVECTOR3 GetTimeSize(void) const;			// �^�C���S�̂̑傫���擾
	CValue::EType GetValueType(void) const	{ return m_type; }			// �����̎�ގ擾
	D3DXVECTOR3 GetSizingValue(void) const	{ return m_sizeValue; }		// ��؂�̑傫���擾
	D3DXVECTOR3 GetSizingPart(void) const	{ return m_sizePart; }		// �����̑傫���擾
	D3DXVECTOR3 GetSpaceValue(void) const	{ return m_spaceValue; }	// ��؂�̋󔒎擾
	D3DXVECTOR3 GetSpacePart(void) const	{ return m_spacePart; }		// �����̋󔒎擾
	D3DXCOLOR GetColor(void) const			{ return m_col;}			// �F�̐ݒ�
	EAlignX GetAlignX(void) const			{ return m_alignX; }		// ���z�u�擾
	EAlignY GetAlignY(void) const			{ return m_alignY; }		// �c�z�u�擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetPositionRelative(void);	// ���Έʒu�ݒ�
	void SetTexNum(void);			// �����̃e�N�X�`�����W�ݒ�

	// �����o�ϐ�
	CValue *m_apValue[timeUI::MAX_DIGIT];	// ���l�̏��
	CObject2D *m_apPart[timeUI::MAX_PART];	// ��؂�̏��
	CValue::EType m_type;		// �������
	D3DXVECTOR3 m_pos;			// ���_�ʒu
	D3DXVECTOR3 m_rot;			// ���_����
	D3DXVECTOR3 m_sizeValue;	// �����̑傫��
	D3DXVECTOR3 m_sizePart;		// ��؂�̑傫��
	D3DXVECTOR3 m_spaceValue;	// �����̋�
	D3DXVECTOR3 m_spacePart;	// ��؂�̋�
	D3DXCOLOR m_col;			// �F
	EAlignX m_alignX;			// ���z�u
	EAlignY m_alignY;			// �c�z�u
	float m_fTime;				// �\������
};

#endif	// _TIME_UI_H_
