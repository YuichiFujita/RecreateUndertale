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
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��
	void SetPriority(const int nPriority) override;	// �D�揇�ʐݒ�
	void SetEnableDraw(const bool bDraw) override;	// �`��󋵐ݒ�
	void SetVec3Position(const VECTOR3& rPos) override;					// �ʒu�ݒ�
	inline VECTOR3 GetVec3Position() const override { return m_pos; }	// �ʒu�擾

	// �ÓI�����o�֐�
	static CValueUI* Create	// ���� (�e�N�X�`���w��Ȃ�)
	( // ����
		const CValue::EType type,	// �������
		const int nDigit,			// ����
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rSpace,		// �s��
		const VECTOR3& rSpaceValue,	// �����s��
		const VECTOR3& rSizeTitle,	// �^�C�g���傫��
		const VECTOR3& rSizeValue,	// �����傫��
		const VECTOR3& rRotTitle = VEC3_ZERO,		// �^�C�g������
		const VECTOR3& rRotValue = VEC3_ZERO,		// ��������
		const COLOR& rColTitle = color::White(),	// �^�C�g���F
		const COLOR& rColValue = color::White()		// �����F
	);
	static CValueUI* Create	// ���� (�e�N�X�`���C���f�b�N�X�w��)
	( // ����
		const int nTextureIdx,		// �^�C�g���e�N�X�`���C���f�b�N�X
		const CValue::EType type,	// �������
		const int nDigit,			// ����
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rSpace,		// �s��
		const VECTOR3& rSpaceValue,	// �����s��
		const VECTOR3& rSizeTitle,	// �^�C�g���傫��
		const VECTOR3& rSizeValue,	// �����傫��
		const VECTOR3& rRotTitle = VEC3_ZERO,		// �^�C�g������
		const VECTOR3& rRotValue = VEC3_ZERO,		// ��������
		const COLOR& rColTitle = color::White(),	// �^�C�g���F
		const COLOR& rColValue = color::White()		// �����F
	);
	static CValueUI* Create	// ���� (�e�N�X�`���p�X�w��)
	( // ����
		const char* pTexturePath,	// �^�C�g���e�N�X�`���p�X
		const CValue::EType type,	// �������
		const int nDigit,			// ����
		const VECTOR3& rPos,		// �ʒu
		const VECTOR3& rSpace,		// �s��
		const VECTOR3& rSpaceValue,	// �����s��
		const VECTOR3& rSizeTitle,	// �^�C�g���傫��
		const VECTOR3& rSizeValue,	// �����傫��
		const VECTOR3& rRotTitle = VEC3_ZERO,		// �^�C�g������
		const VECTOR3& rRotValue = VEC3_ZERO,		// ��������
		const COLOR& rColTitle = color::White(),	// �^�C�g���F
		const COLOR& rColValue = color::White()		// �����F
	);

	// �����o�֐�
	void SetSpace(const VECTOR3& rSpace);				// �s�Ԑݒ�
	void BindTextureTitle(const int nTextureIdx);		// �^�C�g���e�N�X�`������ (�C���f�b�N�X)
	void BindTextureTitle(const char* pTexturePath);	// �^�C�g���e�N�X�`������ (�p�X)
	void SetRotationTitle(const VECTOR3& rRot);			// �^�C�g�������ݒ�
	void SetSizeTitle(const VECTOR3& rSize);			// �^�C�g���傫���ݒ�
	void SetAlphaTitle(const float fAlpha);				// �^�C�g�������x�ݒ�
	void SetColorTitle(const COLOR& rCol);				// �^�C�g���F�ݒ�
	inline VECTOR3 GetSpace() const				{ return m_space; }						// �s�Ԏ擾
	inline VECTOR3 GetRotationTitle() const		{ return m_pTitle->GetVec3Rotation(); }	// �^�C�g�������擾
	inline VECTOR3 GetSizeTitle() const			{ return m_pTitle->GetVec3Size(); }		// �^�C�g���傫���擾
	inline float GetAlphaTitle() const			{ return m_pTitle->GetAlpha(); }		// �^�C�g�������x�擾
	inline COLOR GetColorTitle() const			{ return m_pTitle->GetColor(); }		// �^�C�g���F�擾
	inline CMultiValue* GetMultiValue() const	{ return m_pValue; }					// �������擾

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void SetPositionRelative();	// ���Έʒu�ݒ�

	// �����o�ϐ�
	CObject2D* m_pTitle;	// �^�C�g�����
	CMultiValue* m_pValue;	// �������
	VECTOR3 m_pos;			// �ʒu
	VECTOR3 m_space;		// �s��
};

#endif	// _VALUE_UI_H_
