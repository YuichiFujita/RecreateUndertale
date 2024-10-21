//============================================================
//
//	�p�[�e�B�N��3D�w�b�_�[ [particle3D.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PARTICLE3D_H_
#define _PARTICLE3D_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�N���X��`
//************************************************************
// �p�[�e�B�N��3D�N���X
class CParticle3D : public CObject
{
public:
	// �R���X�g���N�^
	CParticle3D();

	// �f�X�g���N�^
	~CParticle3D() override;

	// ��ޗ�
	enum EType
	{
		TYPE_NONE = 0,			// �Ȃ�
		TYPE_DAMAGE,			// �_���[�W
		TYPE_HEAL,				// ��
		TYPE_FIRE,				// ��
		TYPE_SMALL_EXPLOSION,	// ������
		TYPE_BIG_EXPLOSION,		// �唚��
		TYPE_PLAYER_DAMAGE,		// �v���C���[�_���[�W
		TYPE_MAX				// ���̗񋓌^�̑���
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetVec3Position(const VECTOR3& rPos) override;	// �ʒu�ݒ�
	inline VECTOR3 GetVec3Position() const override { return m_pos; }	// �ʒu�擾

	// �ÓI�����o�֐�
	static CParticle3D* Create	// ����
	( // ����
		const EType type,		// ���
		const VECTOR3& rPos,	// �ʒu
		const COLOR& rCol = color::White()	// �F
	);

	// �����o�֐�
	void SetAlpha(const float fAlpha);	// �����x�ݒ�
	void SetColor(const COLOR& rCol);	// �F�ݒ�
	void SetType(const EType type);		// ��ސݒ�
	inline float GetAlpha() const	{ return m_col.a; }	// �����x�擾
	inline COLOR GetColor() const	{ return m_col; }	// �F�擾
	inline EType GetType() const	{ return m_type; }	// ��ގ擾

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�֐�
	void Damage(const VECTOR3& rPos, const COLOR& rCol);	// �_���[�W
	void Heal(const VECTOR3& rPos, const COLOR& rCol);		// ��

	void Fire(const VECTOR3& rPos);				// ��
	void SmallExplosion(const VECTOR3& rPos);	// ������
	void BigExplosion(const VECTOR3& rPos);		// �唚��
	void PlayerDamage(const VECTOR3& rPos);		// �v���C���[�_���[�W

	// �����o�ϐ�
	VECTOR3 m_pos;	// �ʒu
	COLOR m_col;	// �F
	EType m_type;	// ���
	int m_nLife;	// ����
};

#endif	// _PARTICLE3D_H_
