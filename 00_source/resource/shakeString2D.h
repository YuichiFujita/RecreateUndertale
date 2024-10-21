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
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�

	// �ÓI�����o�֐�
	static CShakeString2D* Create	// ���� (�}���`�o�C�g������)
	( // ����
		const std::string& rFilePath,	// �t�H���g�p�X
		const bool bItalic,				// �C�^���b�N
		const std::string& rStr,		// �w�蕶����
		const VECTOR3& rPos,			// ���_�ʒu
		const float fNextTime = 0.1f,			// �����U���̑ҋ@����
		const float fMove = 1.0f,				// �U���ړ���
		const float fHeight = 100.0f,			// �����c��
		const EAlignX alignX = XALIGN_CENTER,	// ���z�u
		const VECTOR3& rRot = VEC3_ZERO,		// ���_����
		const COLOR& rCol = color::White()		// �F
	);
	static CShakeString2D* Create	// ���� (���C�h������)
	( // ����
		const std::string& rFilePath,	// �t�H���g�p�X
		const bool bItalic,				// �C�^���b�N
		const std::wstring& rStr,		// �w�蕶����
		const VECTOR3& rPos,			// ���_�ʒu
		const float fNextTime = 0.1f,			// �����U���̑ҋ@����
		const float fMove = 1.0f,				// �U���ړ���
		const float fHeight = 100.0f,			// �����c��
		const EAlignX alignX = XALIGN_CENTER,	// ���z�u
		const VECTOR3& rRot = VEC3_ZERO,		// ���_����
		const COLOR& rCol = color::White()		// �F
	);

	// �����o�֐�
	inline void SetNextTime(const float fNextTime)		{ m_fNextTime = fNextTime; }	// �����U���̑ҋ@���Ԑݒ�
	inline float GetNextTime() const					{ return m_fNextTime; }			// �����U���̑ҋ@���Ԏ擾
	inline void SetShakeMove(const float fShakeMove)	{ m_fShakeMove = fShakeMove; }	// �U���̈ړ��ʐݒ�
	inline float GetShakeMove() const					{ return m_fShakeMove; }		// �U���̈ړ��ʎ擾

private:
	// �����o�֐�
	void UpdateShake(const float fDeltaTime);	// �U���X�V

	// �����o�ϐ�
	VECTOR3 m_posSave;	// �ۑ��ʒu
	float m_fShakeMove;	// �U���̈ړ���
	float m_fNextTime;	// ���U���܂ł̑ҋ@����
	float m_fCurTime;	// ���݂̑ҋ@����
};

#endif	// _SHAKE_STRING2D_H_
