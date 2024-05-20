//============================================================
//
//	�t�̃w�b�_�[ [liquid.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _LIQUID_H_
#define _LIQUID_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "scrollMeshField.h"

//************************************************************
//	�N���X��`
//************************************************************
// �t�̃N���X
class CLiquid : public CObject
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_LAVA = 0,	// �}�O�}
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// �㉺��
	enum ELiquid
	{
		LIQUID_LOW = 0,	// ��
		LIQUID_HIGH,	// ��
		LIQUID_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CLiquid();

	// �f�X�g���N�^
	~CLiquid() override;

	// �e�N�X�`���ړ��ʍ\����
	struct STexMove
	{
	public:
		// �R���X�g���N�^
		STexMove() {}
		STexMove(const D3DXVECTOR2 TexMoveLow, const D3DXVECTOR2 TexMoveHigh)
		{ texMoveLow = TexMoveLow; texMoveHigh = TexMoveHigh; }

		// �f�X�g���N�^
		~STexMove() {}

		// �����o�ϐ�
		D3DXVECTOR2 texMoveLow;		// ���t�̂̃e�N�X�`���ړ���
		D3DXVECTOR2 texMoveHigh;	// ��t�̂̃e�N�X�`���ړ���
	};

	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;			// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	void SetVec2Sizing(const D3DXVECTOR2& rSize) override;	// �傫���ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override	{ return m_apLiquid[LIQUID_LOW]->GetVec3Position(); }	// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const override	{ return m_apLiquid[LIQUID_LOW]->GetVec3Rotation(); }	// �����擾
	D3DXVECTOR2 GetVec2Sizing(void) const override		{ return m_apLiquid[LIQUID_LOW]->GetVec2Sizing(); }		// �傫���擾
	D3DXMATRIX *GetPtrMtxWorld(void) override			{ return m_apLiquid[LIQUID_LOW]->GetPtrMtxWorld(); }	// �}�g���b�N�X�|�C���^�擾
	D3DXMATRIX GetMtxWorld(void) const override			{ return m_apLiquid[LIQUID_LOW]->GetMtxWorld(); }		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CLiquid *Create	// ����
	( // ����
		const EType type,			// ���
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const D3DXVECTOR2& rSize,	// �傫��
		const D3DXCOLOR& rCol,		// �F
		const POSGRID2& rPart,		// ������
		const STexMove& rTexMove,	// �e�N�X�`���ړ���
		const float fMaxUp,			// �g�̍ō��㏸��
		const float fAddSinRot,		// �g�ł��������Z��
		const float fAddVtxRot		// �הg�̌������Z��
	);

	// �����o�֐�
	void SetColor(const D3DXCOLOR& rCol);		// �F�ݒ�
	HRESULT SetPattern(const POSGRID2& rPart);	// �������ݒ�
	void SetType(const EType type);				// ��ސݒ�
	void SetTexMove(const STexMove texMove);	// �e�N�X�`���ړ��ʐݒ�
	void SetMaxUp(const float fMaxUp);			// �g�̍ō��㏸�ʐݒ�
	void SetAddSinRot(const float fAddSinRot);	// �g�ł��������Z�ʐݒ�
	void SetAddVtxRot(const float fAddVtxRot);	// �הg�̌������Z�ʐݒ�
	D3DXCOLOR GetColor(void) const	{ return m_apLiquid[LIQUID_LOW]->GetColor(); }		// �F�擾
	POSGRID2 GetPattern(void) const	{ return m_apLiquid[LIQUID_LOW]->GetPattern(); }	// �������擾
	EType GetType(void) const		{ return m_type; }			// ��ގ擾
	float GetMaxUp(void) const		{ return m_fMaxUp; }		// �g�̍ō��㏸�ʎ擾
	float GetAddSinRot(void) const	{ return m_fAddSinRot; }	// �g�ł��������Z�ʎ擾
	float GetAddVtxRot(void) const	{ return m_fAddVtxRot; }	// �הg�̌������Z�ʎ擾

	STexMove GetTexMove(void) const;	// �e�N�X�`���ړ��ʎ擾
	CScrollMeshField *GetMeshField(const int nID) const;	// ���b�V���t�B�[���h�擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	CScrollMeshField *m_apLiquid[LIQUID_MAX];	// �t�̂̏��
	EType m_type;		// ���
	float m_fMaxUp;		// �g�̍ō��㏸��
	float m_fSinRot;	// �g�ł�����
	float m_fAddSinRot;	// �g�ł��������Z��
	float m_fAddVtxRot;	// �הg�̌������Z��
};

#endif	// _LIQUID_H_
