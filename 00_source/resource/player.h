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
#include "objectCharaAnim3D.h"
#include "playerStatus.h"
#include "playerItem.h"

//************************************************************
//	�O���錾
//************************************************************
class CPlayerState;	// �v���C���[��ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// �v���C���[�N���X
class CPlayer : public CObjectCharaAnim3D
{
public:
	// �p�x��
	enum EAngle
	{
		ANGLE_UP = 0,	// ��
		ANGLE_DOWN,		// ��
		ANGLE_LEFT,		// ��
		ANGLE_RIGHT,	// �E
		ANGLE_MAX		// ���̗񋓌^�̑���
	};

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
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��
	HRESULT ChangeState(CPlayerState* pState);		// ��ԕύX

	// �ÓI�����o�֐�
	static CPlayer* Create(const VECTOR3& rPos);	// ����
	static CListManager<CPlayer>* GetList();		// ���X�g�擾

	// �����o�֐�
	void TransRoom(const VECTOR3& rPos, const EAngle angle);			// �����J��
	inline void SetAngle(const EAngle angle)	{ m_angle = angle; }	// �����ݒ�
	inline EAngle GetAngle() const				{ return m_angle; }		// �����擾
	inline VECTOR3 GetOldPosition() const		{ return m_oldPos; }	// �ߋ��ʒu�擾
	inline SPlayerStatus GetStatus() const		{ return m_status; }	// �X�e�[�^�X���擾
	inline SPlayerItem GetItem() const			{ return m_item; }		// �A�C�e�����擾

private:
	// �����o�֐�
	void UpdateOldPosition();	// �ߋ��ʒu�̍X�V
	void UpdateMotion(int nCurMotion, const float fDeltaTime);	// ���[�V�����E�L�����N�^�[2D�̍X�V

	// �ÓI�����o�ϐ�
	static CListManager<CPlayer>* m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CPlayer>::AIterator m_iterator;	// �C�e���[�^�[
	SPlayerStatus m_status;	// �X�e�[�^�X���
	SPlayerItem m_item;		// �A�C�e�����
	CPlayerState* m_pState;	// ���
	VECTOR3 m_oldPos;		// �ߋ��ʒu
	EAngle m_angle;			// ����
};

#endif	// _PLAYER_H_
