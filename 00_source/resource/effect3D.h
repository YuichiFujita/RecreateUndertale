//============================================================
//
//	�G�t�F�N�g3D�w�b�_�[ [effect3D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectBillboard.h"
#include "renderState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �G�t�F�N�g3D�N���X
class CEffect3D : public CObjectBillboard
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_NORMAL = 0,	// �ʏ�e�N�X�`��
		TYPE_BUBBLE,		// �o�u���e�N�X�`��
		TYPE_SMOKE,			// ���e�N�X�`��
		TYPE_HEAL,			// �񕜃e�N�X�`��
		TYPE_LEAF,			// �t���σe�N�X�`��
		TYPE_PIECE_S,		// ������e�N�X�`�� (��)
		TYPE_PIECE_M,		// ������e�N�X�`�� (��)
		TYPE_PIECE_L,		// ������e�N�X�`�� (��)
		TYPE_FIRE,			// ���e�N�X�`��
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CEffect3D(const EType type, const CObject::ELabel label = LABEL_NONE);

	// �f�X�g���N�^
	~CEffect3D() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �����o�֐�
	void SetAlphaBlend(const CRenderState::EBlend blend);	// ���u�����h�ݒ�

	// �ÓI�����o�֐�
	static CEffect3D* Create	// ����
	( // ����
		const VECTOR3&	rPos,		// �ʒu
		const float		fRadius,	// ���a
		const EType		type		= TYPE_NORMAL,		// �e�N�X�`��
		const int		nLife		= 10,				// ����
		const VECTOR3&	rMove		= VEC3_ZERO,		// �ړ���
		const VECTOR3&	rRot		= VEC3_ZERO,		// ����
		const COLOR&	rCol		= color::White(),	// �F
		const float		fSubSize	= 0.0f,				// ���a�̌��Z��
		const CRenderState::EBlend	blend	= CRenderState::BLEND_ADD,	// ���u�����h��
		const CObject::ELabel		label	= LABEL_EFFECT				// �I�u�W�F�N�g���x��
	);

private:
	// �����o�ϐ�
	VECTOR3 m_move;			// �ړ���
	const EType m_type;		// ��ޒ萔
	int		m_nLife;		// ����
	float	m_fSubSize;		// �傫���̌��Z��
	float	m_fSubAlpha;	// �����x�̌��Z��
	CRenderState::EBlend	m_blend;	// ���u�����h��
};

#endif	// _EFFECT3D_H_
