//============================================================
//
//	�X�N���[�����b�V���t�B�[���h�w�b�_�[ [scrollMeshField.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCROLL_MESHFIELD_H_
#define _SCROLL_MESHFIELD_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "objectMeshField.h"

//************************************************************
//	�N���X��`
//************************************************************
// �X�N���[�����b�V���t�B�[���h�N���X
class CScrollMeshField : public CObjectMeshField
{
public:
	// �R���X�g���N�^
	explicit CScrollMeshField(const CObject::ELabel label = LABEL_NONE, const EDim dimension = DIM_3D, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CScrollMeshField() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const VECTOR3& rRot) override;	// �����ݒ�
	void SetVec2Size(const VECTOR2& rSize) override;	// �傫���ݒ�

	// �ÓI�����o�֐�
	static CScrollMeshField* Create	// ����
	( // ����
		const float fMoveU,		// �����W�̈ړ���
		const float fMoveV,		// �c���W�̈ړ���
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const VECTOR2& rSize,	// �傫��
		const COLOR& rCol,		// �F
		const POSGRID2& rPart	// ������
	);

	// �����o�֐�
	void SetTerrain(const POSGRID2& rPart, VECTOR3* pPosGap);	// �n�`�ݒ�
	void SetAlpha(const float fAlpha);			// �����x�ݒ�
	void SetColor(const COLOR& rCol);			// �F�ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);	// �������ݒ�
	void SetTexU(const float fTexU);	// �����W�̊J�n�ʒu�ݒ�
	void SetTexV(const float fTexV);	// �c���W�̊J�n�ʒu�ݒ�
	void SetMoveU(const float fMoveU);	// �����W�̈ړ��ʐݒ�
	float GetMoveU() const;				// �����W�̈ړ��ʎ擾
	void SetMoveV(const float fMoveV);	// �c���W�̈ړ��ʐݒ�
	float GetMoveV() const;				// �c���W�̈ړ��ʎ擾

private:
	// �����o�ϐ�
	float m_fTexU;	// �e�N�X�`�������W�̊J�n�ʒu
	float m_fTexV;	// �e�N�X�`���c���W�̊J�n�ʒu
	float m_fMoveU;	// �e�N�X�`�������W�̈ړ���
	float m_fMoveV;	// �e�N�X�`���c���W�̈ړ���
};

#endif	// _SCROLL_MESHFIELD_H_
