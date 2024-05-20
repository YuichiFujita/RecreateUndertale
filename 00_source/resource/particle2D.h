//============================================================
//
//	�p�[�e�B�N��2D�w�b�_�[ [particle2D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PARTICLE2D_H_
#define _PARTICLE2D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�N���X��`
//************************************************************
// �p�[�e�B�N��2D�N���X
class CParticle2D : public CObject
{
public:
	// �R���X�g���N�^
	CParticle2D();

	// �f�X�g���N�^
	~CParticle2D() override;

	// ��ޗ�
	enum EType
	{
		TYPE_NONE = 0,	// �Ȃ�
		TYPE_DAMAGE,	// �_���[�W
		TYPE_ITEM,		// �A�C�e��
		TYPE_GETITEM,	// �A�C�e���擾
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override { return m_pos; }	// �ʒu�擾

	// �ÓI�����o�֐�
	static CParticle2D *Create	// ����
	( // ����
		const EType type,					// ���
		const D3DXVECTOR3& rPos,			// �ʒu
		const D3DXCOLOR& rCol = XCOL_WHITE	// �F
	);

	// �����o�֐�
	void SetColor(const D3DXCOLOR& rCol);	// �F�ݒ�
	void SetType(const EType type);			// ��ސݒ�
	D3DXCOLOR GetColor(void) const	{ return m_col; }	// �F�擾
	EType GetType(void) const		{ return m_type; }	// ��ގ擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void Damage(const D3DXVECTOR3& rPos, const D3DXCOLOR& rCol);	// �_���[�W
	void Item(const D3DXVECTOR3& rPos, const D3DXCOLOR& rCol);		// �A�C�e��
	void GetItem(const D3DXVECTOR3& rPos, const D3DXCOLOR& rCol);	// �A�C�e���擾

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXCOLOR m_col;	// �F
	EType m_type;		// ���
	int m_nLife;		// ����
};

#endif	// _PARTICLE2D_H_
