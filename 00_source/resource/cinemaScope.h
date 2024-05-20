//============================================================
//
//	�V�l�}�X�R�[�v�w�b�_�[ [cinemaScope.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _CINEMA_SCOPE_H_
#define _CINEMA_SCOPE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �V�l�}�X�R�[�v�N���X
class CCinemaScope
{
public:
	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,		// �Ȃɂ����Ȃ�
		STATE_SCOPE_IN,		// �X�R�[�v�C��
		STATE_SCOPE_OUT,	// �X�R�[�v�A�E�g
		STATE_MAX			// ���̗񋓌^�̑���
	};

	// �|���S����
	enum EPolygon
	{
		POLYGON_TOP = 0,	// �㍕�|���S��
		POLYGON_BOTTOM,		// �����|���S��
		POLYGON_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CCinemaScope();

	// �f�X�g���N�^
	~CCinemaScope();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);	// �X�V
	void Draw(void);		// �`��
	void SetScopeIn(void);	// �X�R�[�v�C���ݒ�
	void SetScopeOut(void);	// �X�R�[�v�A�E�g�ݒ�
	void SetEnableDraw(const bool bDraw);			// �`��󋵐ݒ�
	EState GetState(void) const { return m_state; }	// ��Ԏ擾

	// �ÓI�����o�֐�
	static CCinemaScope *Create(void);					// ����
	static void Release(CCinemaScope *&prCinemaScope);	// �j��

private:
	// �����o�֐�
	void UpdateScopeIn(void);	// �X�R�[�v�C���̍X�V
	void UpdateScopeOut(void);	// �X�R�[�v�A�E�g�̍X�V

	// �����o�ϐ�
	CObject2D *m_apBrack[POLYGON_MAX];	// ���|���S���̏��
	EState m_state;			// ���
	int m_nCounterScope;	// �X�R�[�v�ړ��Ǘ��J�E���^�[
};

#endif	// _CINEMA_SCOPE_H_
