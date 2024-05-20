//============================================================
//
//	�v���C���[�w�b�_�[ [player.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectChara.h"
#include "scene.h"
#include "retentionManager.h"

//************************************************************
//	�O���錾
//************************************************************
class CShadow;	// �e�N���X
class COrbit;	// �O�ՃN���X

//************************************************************
//	�N���X��`
//************************************************************
// �v���C���[�N���X
class CPlayer : public CObjectChara
{
public:
	// ���f����
	enum EModel
	{
		MODEL_WAIST = 0,	// ��
		MODEL_BODY,			// ��
		MODEL_HEAD,			// ��
		MODEL_ARMUL,		// ����r
		MODEL_ARMUR,		// �E��r
		MODEL_ARMDL,		// �����r
		MODEL_ARMDR,		// �E���r
		MODEL_HANDL,		// ����
		MODEL_HANDR,		// �E��
		MODEL_LEGUL,		// ��������
		MODEL_LEGUR,		// �E������
		MODEL_LEGDL,		// ����
		MODEL_LEGDR,		// �E��
		MODEL_FOOTL,		// ����
		MODEL_FOOTR,		// �E��
		MODEL_SWORDL,		// ����
		MODEL_SWORDR,		// �E��
		MODEL_MAX			// ���̗񋓌^�̑���
	};

	// ���[�V������
	enum EMotion
	{
		MOTION_IDOL = 0,	// �ҋ@���[�V����
		MOTION_MAX			// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,	// �������Ȃ����
		STATE_SPAWN,	// �X�|�[�����
		STATE_NORMAL,	// �ʏ���
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CPlayer();

	// �f�X�g���N�^
	~CPlayer() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader *pShader = nullptr) override;		// �`��
	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�

	// �ÓI�����o�֐�
	static CPlayer *Create(CScene::EMode mode);		// ����
	static CListManager<CPlayer> *GetList(void);	// ���X�g�擾

	// �����o�֐�
	void SetDestRotation(const D3DXVECTOR3& rRot)	{ m_destRot = rRot; }	// �ڕW�����ݒ�
	D3DXVECTOR3 GetDestRotation(void) const			{ return m_destRot; }	// �ڕW�����擾
	bool HitKnockBack(const int nDamage, const D3DXVECTOR3& rVecKnock);		// �m�b�N�o�b�N�q�b�g
	bool Hit(const int nDamage);		// �q�b�g
	void SetSpawn(void);				// �o���ݒ�
	void SetState(const EState state);	// ��Ԑݒ�
	EState GetState(void) const;		// ��Ԏ擾
	float GetRadius(void) const;		// ���a�擾
	float GetHeight(void) const;		// �c���擾

private:
	// �����o�֐�
	EMotion UpdateSpawn(void);		// �X�|�[����Ԏ��̍X�V
	EMotion UpdateNormal(void);		// �ʏ��Ԏ��̍X�V
	void UpdateOldPosition(void);	// �ߋ��ʒu�̍X�V
	EMotion UpdateMove(void);		// �ړ��ʁE�ڕW�����̍X�V
	void UpdateGravity(void);		// �d�͂̍X�V

	bool UpdateLanding(D3DXVECTOR3& rPos);				// ���n�󋵂̍X�V
	void UpdatePosition(D3DXVECTOR3& rPos);				// �ʒu�̍X�V
	void UpdateRotation(D3DXVECTOR3& rRot);				// �����̍X�V
	void UpdateMotion(int nMotion, const float fDeltaTime);	// ���[�V�����E�I�u�W�F�N�g�L�����N�^�[�̍X�V
	bool UpdateFadeOut(const float fAdd);				// �t�F�[�h�A�E�g��Ԏ��̍X�V
	bool UpdateFadeIn(const float fSub);				// �t�F�[�h�C����Ԏ��̍X�V

	// �ÓI�����o�ϐ�
	static CListManager<CPlayer> *m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CPlayer>::AIterator m_iterator;	// �C�e���[�^�[
	CShadow		*m_pShadow;			// �e�̏��
	COrbit		*m_pOrbit;			// �O�Ղ̏��
	D3DXVECTOR3	m_oldPos;			// �ߋ��ʒu
	D3DXVECTOR3	m_move;				// �ړ���
	D3DXVECTOR3	m_destRot;			// �ڕW����
	EState		m_state;			// ���
	int			m_nCounterState;	// ��ԊǗ��J�E���^�[
	bool		m_bJump;			// �W�����v��
};

#endif	// _PLAYER_H_
