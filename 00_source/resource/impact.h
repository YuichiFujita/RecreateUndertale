//============================================================
//
//	�Ռ��g�w�b�_�[ [impact.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _IMPACT_H_
#define _IMPACT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "wave.h"

//************************************************************
//	�N���X��`
//************************************************************
// �Ռ��g�N���X
class CImpact : public CWave
{
public:
	// �R���X�g���N�^
	CImpact();

	// �f�X�g���N�^
	~CImpact() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CImpact *Create	// ����
	( // ����
		const ETexture texture,		// ���
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXCOLOR& rCol,		// �F
		const SGrow& rGrow,			// ������
		const SGrow& rAddGrow,		// ����������
		const float fHoleRadius,	// ���̔��a
		const float fThickness,		// ����
		const float fOuterPlusY,	// �O����Y���W���Z��
		const float fMaxGrowRadius	// ���a�̍ő听����
	);

	void SetAddGrow(const SGrow &rGrow)		{ m_addGrow = rGrow; }			// �������ݒ�
	SGrow GetAddGrow(void) const			{ return m_addGrow; }			// �������擾
	void SetMaxGrowRadius(const float fMax)	{ m_fMaxGrowRadius = fMax; }	// �������ݒ�
	float GetMaxGrowRadius(void) const		{ return m_fMaxGrowRadius; }	// �������擾

private:
	// �����o�֐�
	void CollisionPlayer(void);	// �v���C���[�Ƃ̓����蔻��

	// �����o�ϐ�
	float m_fMaxGrowRadius;	// ���a�̍ő听����
	SGrow m_addGrow;		// ����������
};

#endif	// _IMPACT_H_
