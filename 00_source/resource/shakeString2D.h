//============================================================
//
//	�U��������2D�w�b�_�[ [shakeString2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SHAKE_STRING2D_H_
#define _SHAKE_STRING2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "string2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �U��������2D�N���X
class CShakeString2D : public CString2D
{
public:
	// �R���X�g���N�^
	CShakeString2D();

	// �f�X�g���N�^
	~CShakeString2D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�

	// �ÓI�����o�֐�
	static CShakeString2D *Create	// ����
	( // ����
		const std::string &rFilePass,	// �t�H���g�p�X
		const bool bItalic,				// �C�^���b�N
		const std::wstring &rStr,		// �w�蕶����
		const D3DXVECTOR3 &rPos,		// ���_�ʒu
		const float fNextTime = 0.1f,			// �����U���̑ҋ@����
		const float fMove = 1.0f,				// �U���ړ���
		const float fHeight = 100.0f,			// �����c��
		const EAlignX alignX = XALIGN_CENTER,	// ���z�u
		const D3DXVECTOR3& rRot = VEC3_ZERO,	// ���_����
		const D3DXCOLOR& rCol = XCOL_WHITE		// �F
	);

	// �����o�֐�
	void SetNextTime(const float fNextTime)		{ m_fNextTime = fNextTime; }	// �����U���̑ҋ@���Ԑݒ�
	float GetNextTime(void) const				{ return m_fNextTime; }			// �����U���̑ҋ@���Ԏ擾
	void SetShakeMove(const float fShakeMove)	{ m_fShakeMove = fShakeMove; }	// �U���̈ړ��ʐݒ�
	float GetShakeMove(void) const				{ return m_fShakeMove; }		// �U���̈ړ��ʎ擾

private:
	// �����o�֐�
	void UpdateShake(const float fDeltaTime);	// �U���X�V

	// �����o�ϐ�
	D3DXVECTOR3 m_posSave;	// �ۑ��ʒu
	float m_fShakeMove;		// �U���̈ړ���
	float m_fNextTime;		// ���U���܂ł̑ҋ@����
	float m_fCurTime;		// ���݂̑ҋ@����
};

#endif	// _SHAKE_STRING2D_H_