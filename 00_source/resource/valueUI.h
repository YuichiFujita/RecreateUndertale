//============================================================
//
//	����UI�w�b�_�[ [valueUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _VALUE_UI_H_
#define _VALUE_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "value.h"

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X
class CMultiValue;	// �}���`�����N���X

//************************************************************
//	�N���X��`
//************************************************************
// ����UI�N���X
class CValueUI : public CObject
{
public:
	// �R���X�g���N�^
	CValueUI();

	// �f�X�g���N�^
	~CValueUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��
	void SetPriority(const int nPriority) override;	// �D�揇�ʐݒ�
	void SetEnableDraw(const bool bDraw) override;	// �`��󋵐ݒ�
	void SetVec3Position(const D3DXVECTOR3& rPos) override;				// �ʒu�ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override { return m_pos; }	// �ʒu�擾

	// �ÓI�����o�֐�
	static CValueUI *Create	// ���� (�e�N�X�`���w��Ȃ�)
	( // ����
		const CValue::EType type,		// �������
		const int nDigit,				// ����
		const D3DXVECTOR3& rPos,		// �ʒu
		const D3DXVECTOR3& rSpace,		// �s��
		const D3DXVECTOR3& rSpaceValue,	// �����s��
		const D3DXVECTOR3& rSizeTitle,	// �^�C�g���傫��
		const D3DXVECTOR3& rSizeValue,	// �����傫��
		const D3DXVECTOR3& rRotTitle = VEC3_ZERO,	// �^�C�g������
		const D3DXVECTOR3& rRotValue = VEC3_ZERO,	// ��������
		const COLOR& rColTitle = color::White(),	// �^�C�g���F
		const COLOR& rColValue = color::White()		// �����F
	);
	static CValueUI *Create	// ���� (�e�N�X�`���C���f�b�N�X�w��)
	( // ����
		const int nTextureID,			// �^�C�g���e�N�X�`���C���f�b�N�X
		const CValue::EType type,		// �������
		const int nDigit,				// ����
		const D3DXVECTOR3& rPos,		// �ʒu
		const D3DXVECTOR3& rSpace,		// �s��
		const D3DXVECTOR3& rSpaceValue,	// �����s��
		const D3DXVECTOR3& rSizeTitle,	// �^�C�g���傫��
		const D3DXVECTOR3& rSizeValue,	// �����傫��
		const D3DXVECTOR3& rRotTitle = VEC3_ZERO,	// �^�C�g������
		const D3DXVECTOR3& rRotValue = VEC3_ZERO,	// ��������
		const COLOR& rColTitle = color::White(),	// �^�C�g���F
		const COLOR& rColValue = color::White()		// �����F
	);
	static CValueUI *Create	// ���� (�e�N�X�`���p�X�w��)
	( // ����
		const char *pTexturePass,		// �^�C�g���e�N�X�`���p�X
		const CValue::EType type,		// �������
		const int nDigit,				// ����
		const D3DXVECTOR3& rPos,		// �ʒu
		const D3DXVECTOR3& rSpace,		// �s��
		const D3DXVECTOR3& rSpaceValue,	// �����s��
		const D3DXVECTOR3& rSizeTitle,	// �^�C�g���傫��
		const D3DXVECTOR3& rSizeValue,	// �����傫��
		const D3DXVECTOR3& rRotTitle = VEC3_ZERO,	// �^�C�g������
		const D3DXVECTOR3& rRotValue = VEC3_ZERO,	// ��������
		const COLOR& rColTitle = color::White(),	// �^�C�g���F
		const COLOR& rColValue = color::White()		// �����F
	);

	// �����o�֐�
	void SetSpace(const D3DXVECTOR3& rSpace);			// �s�Ԑݒ�
	void BindTextureTitle(const int nTextureID);		// �^�C�g���e�N�X�`������ (�C���f�b�N�X)
	void BindTextureTitle(const char *pTexturePass);	// �^�C�g���e�N�X�`������ (�p�X)
	void SetRotationTitle(const D3DXVECTOR3& rRot);		// �^�C�g�������ݒ�
	void SetSizeTitle(const D3DXVECTOR3& rSize);		// �^�C�g���傫���ݒ�
	void SetAlphaTitle(const float fAlpha);				// �^�C�g�������x�ݒ�
	void SetColorTitle(const COLOR& rCol);				// �^�C�g���F�ݒ�
	D3DXVECTOR3 GetSpace(void) const			{ return m_space; }						// �s�Ԏ擾
	D3DXVECTOR3 GetRotationTitle(void) const	{ return m_pTitle->GetVec3Rotation(); }	// �^�C�g�������擾
	D3DXVECTOR3 GetSizeTitle(void) const		{ return m_pTitle->GetVec3Size(); }		// �^�C�g���傫���擾
	float GetAlphaTitle(void) const				{ return m_pTitle->GetAlpha(); }		// �^�C�g�������x�擾
	COLOR GetColorTitle(void) const				{ return m_pTitle->GetColor(); }		// �^�C�g���F�擾
	CMultiValue *GetMultiValue(void) const		{ return m_pValue; }					// �������擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetPositionRelative(void);	// ���Έʒu�ݒ�

	// �����o�ϐ�
	CObject2D *m_pTitle;	// �^�C�g�����
	CMultiValue *m_pValue;	// �������
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_space;	// �s��
};

#endif	// _VALUE_UI_H_
