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
#include "objectChara2D.h"

//************************************************************
//	�O���錾
//************************************************************
class CPlayerState;	// �v���C���[��ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// �v���C���[�N���X
class CPlayer : public CObjectChara2D
{
public:
	// ���[�V������
	enum EMotion
	{
		MOTION_IDOL_U = 0,	// ��ҋ@���[�V����
		MOTION_IDOL_D,		// ���ҋ@���[�V����
		MOTION_IDOL_L,		// ���ҋ@���[�V����
		MOTION_IDOL_R,		// �E�ҋ@���[�V����
		MOTION_MOVE_U,		// ��ړ����[�V����
		MOTION_MOVE_D,		// ���ړ����[�V����
		MOTION_MOVE_L,		// ���ړ����[�V����
		MOTION_MOVE_R,		// �E�ړ����[�V����
		MOTION_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CPlayer();

	// �f�X�g���N�^
	~CPlayer();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��
	HRESULT ChangeState(CPlayerState *pState);		// ��ԕύX

	// �ÓI�����o�֐�
	static CPlayer *Create(const D3DXVECTOR3& rPos);	// ����
	static CListManager<CPlayer> *GetList(void);		// ���X�g�擾

private:
	// �����o�֐�
	void UpdateOldPosition(void);	// �ߋ��ʒu�̍X�V
	void UpdateMotion(int nCurMotion, const float fDeltaTime);	// ���[�V�����E�L�����N�^�[2D�̍X�V

	// �ÓI�����o�ϐ�
	static CListManager<CPlayer> *m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CPlayer>::AIterator m_iterator;	// �C�e���[�^�[
	CPlayerState *m_pState;	// ���
	D3DXVECTOR3	m_oldPos;	// �ߋ��ʒu
};

#endif	// _PLAYER_H_
